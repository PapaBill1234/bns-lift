// SysInfo (CacheGate PDB). Declarations only. The bodies are in a later card.
#pragma once

class SysInfo
{
public:
    // 0x14390 TODO(lift-sysinfo)
    static void Hostname(unsigned long address, wchar_t* hostname, int length);
    // 0x144f0 TODO(lift-sysinfo)
    static void IpAddress(wchar_t const* hostname, int* count, unsigned long* address);

private:
    static int _PageSize;
    static int _ProcessorCount;
    static int _Granularity;

    friend void BloodDaemonMain(int argc, wchar_t** argv);
};
