#include "patches.h"
#include "config.h"
#include "VersionInfo.h"
#include "Shared/Common.h"
#include "Shared/Patcher.h"
#include <windows.h>
#include <iostream>
#include "GameVersions.h"

#if !defined(_M_IX86) && !defined(__i386__)
#error "Plugin supports only x86 systems"
#endif

// Calling convention used for plugin. Must be cdecl
#define PLUGIN_DECL __cdecl

using namespace Common;
using namespace Patcher;
using namespace Shared;

BOOL PLUGIN_DECL SetGameVer( unsigned long gameVersion)
{
    // Return true if gameVer is valid for plugin, else it be unload.
    // TODO: check versions diff
    switch (gameVersion)
    {
    case Shared::ST_GAMEVERSION_RETAIL_UNPATCHED:
        //MessageBox(NULL, L"This version of Submarine Titans is outdated, please update to v1.1.", L"SubTitans Patch", MB_ICONWARNING);
        return FALSE;
        break;
    case Shared::ST_GAMEVERSION_RETAIL_PATCHED:
        return FALSE;
        break;
    case Shared::ST_GAMEVERSION_GOG_MODIFIED:
        ApplyPatches();
        return TRUE;
        break;
    case Shared::ST_GAMEVERSION_DEMO:
        return FALSE;
        break;
    default:
        //MessageBox(NULL, L"Incompatible application", L"SubTitans Patch", MB_ICONERROR);
        return FALSE;
        break;
    }
}

const char *PLUGIN_DECL GetPluginVersion()
{
    // Return string version of plugin (is not used by addon yet)
    return PRODUCT_VERSION_STRING;
}

const char *PLUGIN_DECL GetPluginName()
{
    // Return name of plugin (is not used by addon yet)
    return PRODUCT_NAME;
}

SPluginConfig PluginConfig;

BOOL APIENTRY DllMain(HINSTANCE hInstanceDLL, DWORD fdwReason, LPVOID)
{
    switch (fdwReason)
    {
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_ATTACH: {
        DisableThreadLibraryCalls(hInstanceDLL);

        // Load config
        auto pluginDir = Common::GetDirectoryName(Common::GetCurrentModulePath());
        Common::AddTrailingSlash(pluginDir);
        PluginConfig.Load(Common::WideToAnsi(pluginDir) + "stdll.ini");

        break;
    }
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
