// SystemInformation.obj (SmartCouponDaemon PDB). Class SysInfo.
#include "SysInfo.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdlib.h>
#include <windows.h>

// Set by BloodDaemonMain (Daemon.cpp) from GetSystemInfo.
int SysInfo::_PageSize = 0;
int SysInfo::_ProcessorCount = 0;
int SysInfo::_Granularity = 0;

// Adds value to address[] if it is not there and there is space.  // LIFT: inline helper, no PDB name
static void addUniqueAddress(unsigned long* address, int capacity, int* found, unsigned long value)
{
    if (*found >= capacity)
        return;
    for (int i = 0; i < *found; ++i)
    {
        if (address[i] == value)
            return;
    }
    address[(*found)++] = value;
}

// 0x1FB80 (SmartCouponDaemon)
// LTCG folded address to 0 (the only caller is Daemon: Hostname(0, hostname, 256)).
int SysInfo::Hostname(unsigned long address, wchar_t* hostname, int length)
{
    sockaddr_in sockaddr = {};
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(0);
    sockaddr.sin_addr.S_un.S_addr = address;
    if (hostname == nullptr)
        return 3;
    WSADATA data;
    if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
        return 4;
    int result;
    char name[1025];
    if (address == 0)
    {
        if (gethostname(name, 1025) != 0)
        {
            result = 5;
        }
        else
        {
            hostname[length - 1] = L'\0';
            MultiByteToWideChar(CP_ACP, 0, name, -1, hostname, length - 1);
            result = 0;
        }
    }
    else
    {
        // ❓ LTCG removed the address != 0 branch. The binary has no code for it.
        result = 5;
    }
    WSACleanup();
    if (result != 0)
    {
        char* text = inet_ntoa(sockaddr.sin_addr);
        hostname[length - 1] = L'\0';
        MultiByteToWideChar(CP_ACP, 0, text, -1, hostname, length - 1);
        return result;
    }
    for (wchar_t* p = hostname; *p != L'\0'; ++p)
    {
        if (*p == L'.')
        {
            *p = L'\0';
            break;
        }
    }
    return 0;
}

// 0x1FCE0 (SmartCouponDaemon)
int SysInfo::IpAddress(wchar_t const* hostname, int* count, unsigned long* address)
{
    if (address == nullptr)
        return 3;
    int capacity = *count;
    if (capacity <= 0)
        return 3;
    *count = 0;
    int found = 0;
    WSADATA data;
    if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
        return 4;
    char name[1025];
    if (hostname != nullptr)
    {
        name[1023] = '\0';
        name[1024] = '\0';
        WideCharToMultiByte(CP_ACP, 0, hostname, -1, name, 1024, nullptr, nullptr);
    }
    // BUG: 0x1FCE0 (SmartCouponDaemon) gethostname returns 0 on success, but 0 is used as the failure.
    else if (gethostname(name, 1025) == 0)
    {
        WSACleanup();
        *count = 0;
        return 5;
    }

    addrinfo hint;
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = IPPROTO_TCP;
    addrinfo* addrList = nullptr;
    if (getaddrinfo(name, nullptr, &hint, &addrList) == 0)
    {
        for (addrinfo* info = addrList; info != nullptr; info = info->ai_next)
        {
            if (info->ai_addrlen == sizeof(sockaddr_in))
                addUniqueAddress(address, capacity, &found,
                                 reinterpret_cast<sockaddr_in*>(info->ai_addr)->sin_addr.S_un.S_addr);
        }
        freeaddrinfo(addrList);
    }

    hostent* host = gethostbyname(name);
    if (host != nullptr)
    {
        for (int i = 0; host->h_addr_list[i] != nullptr; ++i)
            addUniqueAddress(address, capacity, &found,
                             *reinterpret_cast<unsigned long*>(host->h_addr_list[i]));
    }

    ULONG outBufLen = 15360;
    IP_ADAPTER_ADDRESSES* adapters = nullptr;
    for (unsigned int retry = 0;;)
    {
        adapters = static_cast<IP_ADAPTER_ADDRESSES*>(malloc(outBufLen));
        if (adapters == nullptr)
            break;
        if (GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_PREFIX, nullptr, adapters, &outBufLen) != ERROR_BUFFER_OVERFLOW)
            break;
        free(adapters);
        adapters = nullptr;
        if (++retry >= 3)
            break;
    }
    if (adapters != nullptr)
    {
        for (IP_ADAPTER_ADDRESSES* adapter = adapters; adapter != nullptr; adapter = adapter->Next)
        {
            for (IP_ADAPTER_UNICAST_ADDRESS* unicast = adapter->FirstUnicastAddress; unicast != nullptr; unicast = unicast->Next)
            {
                if (unicast->Address.iSockaddrLength == sizeof(sockaddr_in))
                    addUniqueAddress(address, capacity, &found,
                                     reinterpret_cast<sockaddr_in*>(unicast->Address.lpSockaddr)->sin_addr.S_un.S_addr);
            }
        }
        free(adapters);
    }
    WSACleanup();
    *count = found;
    return 1;
}
