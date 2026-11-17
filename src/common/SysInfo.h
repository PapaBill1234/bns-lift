// SysInfo (SmartCouponDaemon PDB). Bodies: SystemInformation.cpp.
#pragma once

class SysInfo
{
public:
    // PDB type 0x333E: Get, ProcessorCount, MemoryPageSize and MemnoryAllocationGranularity are public static.
    // LIFT: no symbol for these 4; the compiler inlined them (Get into BloodDaemonMain 0xa690).
    static void Get();
    // 0x1FB80 (SmartCouponDaemon)
    static int Hostname(unsigned long address, wchar_t* hostname, int length);
    // 0x1FCE0 (SmartCouponDaemon)
    static int IpAddress(wchar_t const* hostname, int* count, unsigned long* address);
    static int ProcessorCount() { return _ProcessorCount; }
    static int MemoryPageSize() { return _PageSize; }
    static int MemnoryAllocationGranularity() { return _Granularity; }  // PDB spelling

private:
    static int _ProcessorCount;
    static int _PageSize;
    static int _Granularity;
};
