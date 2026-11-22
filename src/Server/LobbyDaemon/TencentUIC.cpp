// TencentUIC.obj (LobbyDaemon 2019 + PDB).
#include "TencentUIC.h"
#include "Log.h"
#include <stdio.h>
#include <string.h>

namespace tss_sdk_if
{
    enum ETssSdkPluginId
    {
        ETSS_SDK_PLUGIN_ID_INVALID = -2,
        ETSS_SDK_PLUGIN_ID_ALL = -1,
        ETSS_SDK_PLUGIN_ID_BEGIN = 0,
        ETSS_SDK_PLUGIN_ID_CHANNEL = 1,
        ETSS_SDK_PLUGIN_ID_USER_CONTROL = 2,
        ETSS_SDK_PLUGIN_ID_PROTO_PROC = 3,
        ETSS_SDK_PLUGIN_ID_SAFEMODE = 4,
        ETSS_SDK_PLUGIN_ID_CAPTCHA = 5,
        ETSS_SDK_PLUGIN_ID_UIC = 6,
        ETSS_SDK_PLUGIN_ID_END = 7
    };

    struct STssSdkPluginInitData
    {
        ETssSdkPluginId plugin_id;
        int (__cdecl* callback_proc)(void*);
        void* init_data;
    };

    struct STssSdkPluginNotifyData
    {
        ETssSdkPluginId plugin_id;
        void* notify_data;
    };

    struct STssSdk
    {
        int (__cdecl* init)(STssSdkPluginInitData const*, unsigned int);
        int (__cdecl* fini)(ETssSdkPluginId);
        int (__cdecl* proc)();
        int (__cdecl* notify)(STssSdkPluginNotifyData);
        int (__cdecl* get_last_error_code)();
        char const* (__cdecl* get_last_error)();
    };

    HMODULE g_handle;
}

static_assert(sizeof(tss_sdk_if::STssSdk) == 0x30, "sizeof STssSdk");
static_assert(sizeof(tss_sdk_if::STssSdkPluginInitData) == 0x18, "sizeof STssSdkPluginInitData");
static_assert(sizeof(tss_sdk_if::STssSdkPluginNotifyData) == 0x10, "sizeof STssSdkPluginNotifyData");

enum EUserInputType
{
    EUITYPE_CHAT = 0,
    EUITYPE_NAME = 1,
    EUITYPE_IMAGE = 2,
    EUITYPE_VIDEO = 3
};

struct SUserMessage
{
    unsigned int uin;
    EUserInputType input_type;
    unsigned int message_len;
    unsigned char* message;
    unsigned short callback_data_len;
    unsigned char* callback_data;
    unsigned short game_data_len;
    unsigned char* game_data;
};
static_assert(sizeof(SUserMessage) == 0x38, "sizeof SUserMessage");

static int g_is_sdk_loaded;
static tss_sdk_if::STssSdk* g_tss_sdk;

#pragma comment(linker, "/INCLUDE:?Initialize@TencentUIC@@QEAA_NPEB_W@Z")  // LIFT: keep until the caller is lifted (0x7ad30).
#pragma comment(linker, "/INCLUDE:?CheckNameFilter@TencentUIC@@QEAA_NIPEB_W@Z")  // LIFT: keep until the callers are lifted (0x7ae80).

// 0x5a0a0. The linker folds UIC_CallBack_proc with other zero-return functions.
int UIC_CallBack_proc(void*)
{
    return 0;
}

// 0x7ac30
// LIFT: TencentUIC::Initialize calls tss_load_sdk out of line (0x7ad30).
extern "C" __declspec(noinline) tss_sdk_if::STssSdk* tss_load_sdk(char const* shared_lib_dir)
{
    char shared_lib_file[1024] = "";
#if defined(__clang__)
    // LIFT: the Wine headers have no _snprintf_s<1024> template overload (0x7b0a0). The clang build calls the 4-argument form
    // (count = array size). VS2010 compiles the 2-argument form below, which is the original (0x7ac30).
    _snprintf_s(shared_lib_file, sizeof(shared_lib_file), sizeof(shared_lib_file), "%s/%s.%s", shared_lib_dir, "tss_sdk", "dll");
#else
    _snprintf_s(shared_lib_file, sizeof(shared_lib_file), "%s/%s.%s", shared_lib_dir, "tss_sdk", "dll");  // 0x7b0a0
#endif
    if (g_is_sdk_loaded != 0)
        return g_tss_sdk;

    HMODULE handle = LoadLibraryExA(shared_lib_file, nullptr, 0);
    tss_sdk_if::g_handle = handle;
    tss_sdk_if::STssSdk* sdk = nullptr;
    if (handle != nullptr)
    {
        FARPROC proc = GetProcAddress(handle, "tss_get_sdk");
        if (proc != nullptr)
            sdk = reinterpret_cast<tss_sdk_if::STssSdk* (__cdecl*)()>(proc)();
    }
    g_tss_sdk = sdk;
    if (sdk != nullptr)
        g_is_sdk_loaded = 1;
    return sdk;
}

// 0x7ad30
bool TencentUIC::Initialize(wchar_t const* configfile)
{
    _tss_sdk = tss_load_sdk(".");
    if (_tss_sdk == nullptr)
    {
        Log::Write(Log::LT_DEBUG, L"Tencent\\UIC\\TencentUIC.cpp", 135,
                   L"[tencent_uic], tencent uic initialize failed : %s, _tss_sdk == NULL", configfile);
        return false;
    }

    char config_file_path[1024] = "";
    config_file_path[1022] = 0;
    config_file_path[1023] = 0;
    WideCharToMultiByte(CP_ACP, 0, configfile, -1, config_file_path, 1023, nullptr, nullptr);
    tss_sdk_if::STssSdkPluginInitData plugin_init_data[tss_sdk_if::ETSS_SDK_PLUGIN_ID_END];
    plugin_init_data[0].callback_proc = UIC_CallBack_proc;
    plugin_init_data[0].init_data = config_file_path;
    plugin_init_data[0].plugin_id = tss_sdk_if::ETSS_SDK_PLUGIN_ID_UIC;
    int result = _tss_sdk->init(plugin_init_data, 1);
    if (result != 0)
    {
        Log::Write(Log::LT_ERROR, L"Tencent\\UIC\\TencentUIC.cpp", 151,
                   L"[tencent_uic], tencent uic initialize failed : (%s), _tss_sdk->init, result(%d)", configfile, result);
        return false;
    }
    Log::Write(Log::LT_DEBUG, L"Tencent\\UIC\\TencentUIC.cpp", 155,
               L"[tencent_uic], tencent uic initialize success : %s", configfile);
    return true;
}

// 0x7ae80
bool TencentUIC::CheckNameFilter(unsigned int qqid, wchar_t const* name)
{
    Log::Write(Log::LT_DEBUG, L"Tencent\\UIC\\TencentUIC.cpp", 161,
               L"[tencent_uic], CheckNameFilter : qqid(%u), name(%s)", qqid, name);
    if (name == nullptr)
        return false;

    char content[65536] = "";
    content[65534] = 0;
    content[65535] = 0;
    WideCharToMultiByte(CP_ACP, 0, name, -1, content, 65535, nullptr, nullptr);
    tss_sdk_if::STssSdkPluginNotifyData notify_data;
    SUserMessage user_message;
    notify_data.plugin_id = tss_sdk_if::ETSS_SDK_PLUGIN_ID_UIC;
    user_message.uin = qqid;
    user_message.callback_data_len = 0;
    user_message.callback_data = nullptr;  // LIFT: safety initialization; the original sets only the length (0x7ae80).
    user_message.message = reinterpret_cast<unsigned char*>(content);
    notify_data.notify_data = &user_message;
    user_message.message_len = static_cast<unsigned int>(strlen(content) + 1);
    user_message.game_data_len = 0;
    user_message.game_data = nullptr;  // LIFT: safety initialization; the original sets only the length (0x7ae80).
    user_message.input_type = EUITYPE_NAME;
    // BUG: the original requires prior SDK initialization and has no null check at 0x7ae80.
    int result = g_tss_sdk->notify(notify_data);
    if (result != 0)
        return false;

    Log::Write(Log::LT_DEBUG, L"Tencent\\UIC\\TencentUIC.cpp", 188,
               L"[tencent_uic], CheckNameFilter : qqid(%u), name(%s), ret(%d)", qqid, name, result);
    if (strstr(reinterpret_cast<char const*>(user_message.message), "*") != nullptr)
    {
        wchar_t debugName[1024] = L"";
        debugName[1023] = 0;
        MultiByteToWideChar(CP_ACP, 0, reinterpret_cast<char const*>(user_message.message), -1, debugName, 1023);
        Log::Write(Log::LT_ERROR, L"Tencent\\UIC\\TencentUIC.cpp", 193,
                   L"[tencent_uic], CheckNameFilter failed : qqid(%u), name(%s), ret(%d), name(%s)", qqid, name, result, debugName);
        return false;
    }
    return true;
}
