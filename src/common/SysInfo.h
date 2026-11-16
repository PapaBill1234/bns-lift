// SysInfo (SmartCouponDaemon PDB). Bodies: SystemInformation.cpp.
#pragma once

class SysInfo
{
public:
    // 0x1FB80 (SmartCouponDaemon)
    static int Hostname(unsigned long address, wchar_t* hostname, int length);
    // 0x1FCE0 (SmartCouponDaemon)
    static int IpAddress(wchar_t const* hostname, int* count, unsigned long* address);

private:
    static int _PageSize;
    static int _ProcessorCount;
    static int _Granularity;

    friend void BloodDaemonMain(int argc, wchar_t** argv);
    friend class LogBufferAllocator;  // ❓ access for initAllocator (0x20440)
    friend class PacketBufferAllocator;  // ❓ access for initAllocator (0x24100)
    friend class Network;
    friend class SmartCouponDaemon;  // ❓ access for initialize (0x150E0)
    friend class SessionPool;  // ❓ access for SessionPool::SessionPool (0x184E0)  // ❓ access for initWorkerThread (0xD8E0)
};
