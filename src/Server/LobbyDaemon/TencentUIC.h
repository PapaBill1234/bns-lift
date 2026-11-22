// TencentUIC.obj (LobbyDaemon 2019 + PDB).
#pragma once

namespace tss_sdk_if
{
struct STssSdk;
}

class TencentUIC
{
public:
    TencentUIC() : _tss_sdk(nullptr) {}
    virtual ~TencentUIC() {}
    bool Initialize(wchar_t const* configfile);  // 0x7ad30
    bool CheckNameFilter(unsigned int qqid, wchar_t const* name);  // 0x7ae80

private:
    tss_sdk_if::STssSdk* _tss_sdk;
};
static_assert(sizeof(TencentUIC) == 0x10, "sizeof TencentUIC");
