#include <Windows.h>
#include <math.h>
#include <cstdint>
#include "types.h"
#include "../shared/gameversion.h"
#include "../shared/file.h"
#include "injector.h"
#include <string>
#include <fstream>
//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/ini_parser.hpp>

#ifdef _DEBUG
	#pragma comment(lib, "../Debug/shared.lib")
#else
	#pragma comment(lib, "../Release/shared.lib")
#endif

#pragma comment(linker, "/EXPORT:D3DRMVectorModulus=_D3DRMVectorModulus@4")
extern "C" float __stdcall D3DRMVectorModulus(D3DVector3* vector)
{
	if (vector == nullptr)
		return 0.f;

	return static_cast<float>(sqrt(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z));
}

uint32_t GetSubTitansVersion()
{
	WCHAR applicationPath[MAX_PATH];
	GetModuleFileName(NULL, applicationPath, MAX_PATH);

	uint32_t checkSum = File::CalculateChecksum(applicationPath);
	
	switch (checkSum)
	{
		case Shared::ST_GAMEVERSION_RETAIL_UNPATCHED:
		case Shared::ST_GAMEVERSION_RETAIL_PATCHED:
		case Shared::ST_GAMEVERSION_GOG_MODIFIED:
		case Shared::ST_GAMEVERSION_DEMO:
			return checkSum;
		default:
			return 0;
	}
}


DWORD LoadPlugins(unsigned long gameVersion)
{
	DWORD result;
	void* v1;
	struct _WIN32_FIND_DATAA FindFileData;
	CHAR Buffer[264];
	CHAR String1[264];

	typedef int(__cdecl* procSetVar)(unsigned long version);

	result = GetCurrentDirectoryA(260, Buffer);
	if (result)
	{
		lstrcatA(Buffer, "\\plugins\\*.asi");
		auto file = FindFirstFileA(Buffer, &FindFileData);
		v1 = file;
		if (result != -1)
		{
			do
			{
				GetCurrentDirectoryA(260, String1);
				lstrcatA(String1, "\\plugins\\");
				lstrcatA(String1, FindFileData.cFileName);
				auto pluglib = LoadLibraryA(String1);
				if (!pluglib)
				{
					MessageBox(NULL, L"Failed to load any plugin!", L"D3DRM(Custom)", MB_ICONERROR);
					//ExitProcess(-1);
				}
				else {
					procSetVar procSetGameVer = (procSetVar)GetProcAddress(pluglib, "SetGameVer");
					if (!procSetGameVer(gameVersion)) {
						FreeLibrary(pluglib);
						MessageBox(NULL, L"Some plugin is not for this executable!", L"D3DRM(Custom)", MB_ICONERROR);
					}
				}
			} while (FindNextFileA(v1, &FindFileData));
			return FindClose(v1);
		}
	}
	return result;
}

//DWORD LoadPlugins(unsigned long gameVersion)
//{
//    DWORD result;
//    void *v1;
//    struct _WIN32_FIND_DATAA FindFileData;
//    CHAR Buffer[264];
//    CHAR String1[264];
//
//    typedef int(__cdecl * procSetVar)(unsigned long version);
//
//    result = GetCurrentDirectoryA(260, Buffer);
//    if (result)
//    {
//        std::ifstream patchListFile("patchlist.db");
//        std::string patch;
//
//        lstrcatA(Buffer, "\\plugins\\*.asi");
//        if (patchListFile.is_open())
//        {
//            do
//            {
//                std::getline(patchListFile, patch);
//
//                int bufferlen = ::MultiByteToWideChar(CP_ACP, 0, patch.c_str(), patch.size(), NULL,
//                                                      0);
//
//                if (bufferlen == 0)
//                {
//                    return FALSE;
//                }
//
//                LPWSTR widestr = new WCHAR[bufferlen + 1];
//
//                ::MultiByteToWideChar(CP_ACP, 0, patch.c_str(), patch.size(), widestr, bufferlen);
//
//                widestr[bufferlen] = 0;
//
//
//                MessageBox(NULL, widestr, L"D3DRM(Custom)", MB_ICONINFORMATION);
//
//                delete[] widestr;
//                if (!patch.empty())
//                {
//                    MessageBox(NULL, L"Patch list not empty!", L"D3DRM(Custom)", MB_ICONINFORMATION);
//                    GetCurrentDirectoryA(260, String1);
//                    lstrcatA(String1, "\\plugins\\");
//                    lstrcatA(String1, patch.c_str());
//                    auto pluglib = LoadLibraryA(String1);
//                    if (!pluglib)
//                    {
//                        MessageBox(NULL, L"Failed to load any plugin!", L"D3DRM(Custom)",
//                                   MB_ICONERROR);
//                        ExitProcess(-1);
//                    }
//                    else
//                    {
//                        procSetVar procSetGameVer = (procSetVar)GetProcAddress(pluglib, "SetGameVer");
//                        if (!procSetGameVer(gameVersion))
//                        {
//                            FreeLibrary(pluglib);
//                            MessageBox(NULL, L"Some plugin is not for this executable!",
//                                       L"D3DRM(Custom)", MB_ICONERROR);
//                        }
//                    }
//                }
//                else
//                {
//                    MessageBox(NULL, L"Patchlist.db is empty.", L"D3DRM(Custom)", MB_ICONINFORMATION);
//                    //MessageBox(NULL, widestr, L"D3DRM(Custom)", MB_ICONINFORMATION);
//                    //ExitProcess(-1);
//                }
//            } while (patchListFile);
//            return TRUE;
//        }
//        else
//        {
//            MessageBox(NULL, L"Patchlist.db is not found.", L"D3DRM(Custom)", MB_ICONINFORMATION);
//        }
//    }
//    return result;
//}

//DWORD LoadPlugins(unsigned long gameVersion)
//{
//    DWORD result;
//    void *v1;
//    struct _WIN32_FIND_DATAA FindFileData;
//    wchar_t Buffer[264];
//    CHAR String1[264];
//
//    typedef int(__cdecl * procSetVar)(unsigned long version);
//
//    result = GetCurrentDirectoryW(260, Buffer);
//    if (result)
//    {
//        std::ifstream configFile("plugins\\ConfigGame.ini");
//        wchar_t patch[100];
//        wchar_t flag_balance[5];
//        wchar_t flag_core[5];
//        wchar_t Buffer2[264];
//
//        lstrcatW(Buffer, L"\\plugins\\*.asi");
//        if (configFile.is_open())
//        {
//            GetCurrentDirectoryW(260, Buffer2);
//            LPWSTR path = lstrcatW(Buffer2, L"\\plugins\\ConfigGame.ini");
//
//            GetPrivateProfileString(L"Patches_active", L"activate", NULL, flag_balance, 5, path);
//            //MessageBox(NULL, flag_balance, L"debug", MB_ICONINFORMATION);
//            std::wstring ws(flag_balance);
//            std::string flag_balance_string(ws.begin(), ws.end());
//            if (flag_balance_string == "True")
//            {
//                GetPrivateProfileString(L"Patches_active", L"file", NULL, patch, 100, path);
//                //MessageBox(NULL, patch, L"D3DRM(Custom)", MB_ICONINFORMATION);
//                GetCurrentDirectoryW(260, Buffer2);
//                lstrcatW(Buffer2, L"\\plugins\\");
//                lstrcatW(Buffer2, patch);
//                auto pluglib = LoadLibraryW(Buffer2);
//                if (!pluglib)
//                {
//                    MessageBox(NULL, L"Failed to load plugin!", L"D3DRM(Custom)", MB_ICONERROR);
//                    ExitProcess(-1);
//                }
//                else
//                {
//                    procSetVar procSetGameVer = (procSetVar)GetProcAddress(pluglib, "SetGameVer");
//                    if (!procSetGameVer(gameVersion))
//                    {
//                        FreeLibrary(pluglib);
//                        MessageBox(NULL, L"Some plugin is not for this executable!", L"D3DRM(Custom)", MB_ICONERROR);
//                    }
//                }
//            }
//            GetCurrentDirectoryW(260, Buffer2);
//            path = lstrcatW(Buffer2, L"\\plugins\\ConfigGame.ini");
//            //MessageBox(NULL, path, L"D3DRM(Custom)", MB_ICONINFORMATION);
//            GetPrivateProfileString(L"Fix_release_version", L"activate", NULL, flag_core, 5, path);
//
//            //MessageBox(NULL, flag_core, L"D3DRM(Custom)", MB_ICONINFORMATION);
//            std::wstring ws2(flag_core);
//            std::string flag_core_string(ws2.begin(), ws2.end());
//            if (flag_core_string == "True")
//            {
//                GetPrivateProfileString(L"Fix_release_version", L"file", NULL, patch, 100, path);
//                //MessageBox(NULL, patch, L"D3DRM(Custom)", MB_ICONINFORMATION);
//                GetCurrentDirectoryW(260, Buffer2);
//                lstrcatW(Buffer2, L"\\plugins\\");
//                lstrcatW(Buffer2, patch);
//                //MessageBox(NULL, Buffer2, L"D3DRM(Custom)", MB_ICONINFORMATION);
//                auto pluglib = LoadLibraryW(Buffer2);
//                if (!pluglib)
//                {
//                    MessageBox(NULL, L"Failed to load plugin!", L"D3DRM(Custom)", MB_ICONERROR);
//                    ExitProcess(-1);
//                }
//                else
//                {
//                    //MessageBox(NULL, patch, L"D3DRM(Custom)", MB_ICONINFORMATION);
//                    procSetVar procSetGameVer = (procSetVar)GetProcAddress(pluglib, "SetGameVer");
//                    if (!procSetGameVer(gameVersion))
//                    {
//                        FreeLibrary(pluglib);
//                        MessageBox(NULL, L"Some plugin is not for this executable!",
//                                   L"D3DRM(Custom)", MB_ICONERROR);
//                    }
//                }
//            }
//            return TRUE;
//        }
//        else
//        {
//            //MessageBox(NULL, L"ConfigGame.ini not found", L"D3DRM(Custom)", MB_ICONINFORMATION);
//        }
//    }
//    return result;
//}

// Use d3drm for injecting custom DLL
BOOLEAN __stdcall DllMain(HINSTANCE handle, DWORD reason, LPVOID reserved)
{
	// Warning: Only use functions available in Kernel32
	if (reason == DLL_PROCESS_ATTACH)
	{
		uint32_t gameVersion = GetSubTitansVersion();
		if (gameVersion == 0)
			return FALSE;

		// Allow uninstalling patch by removing SubTitans.dll
		if (!File::Exists(L"SubTitans.dll"))
			return TRUE;

		LoadPlugins(gameVersion);

		return Injector::Apply(gameVersion);
	}

	return TRUE;
}