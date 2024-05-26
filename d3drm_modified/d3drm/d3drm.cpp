#include <Windows.h>
#include <math.h>
#include <cstdint>
#include "types.h"
#include "../shared/gameversion.h"
#include "../shared/file.h"
#include "injector.h"
#include <string>
#include <fstream>

using namespace std;

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
    void *v1;
    struct _WIN32_FIND_DATAA FindFileData;
    CHAR Buffer[MAX_PATH];
    CHAR FullPath[MAX_PATH];

    typedef int(__cdecl * procSetVar)(unsigned long version);

    auto result = GetCurrentDirectoryA(260, Buffer);

    string FileDirectory(Buffer);

    if (result)
    {
        lstrcatA(Buffer, "\\plugins\\*.asi");
        auto file = FindFirstFileA(Buffer, &FindFileData);
        v1 = file;
        if (result != -1)
        {
            do
            {
                GetCurrentDirectoryA(260, FullPath);
                lstrcatA(FullPath, "\\plugins\\");
                lstrcatA(FullPath, FindFileData.cFileName);
                auto pluglib = LoadLibraryA(FullPath);
                if (!pluglib)
                {
                    MessageBox(NULL, L"No plugins detected", L"d3drm", MB_ICONINFORMATION);
                    //ExitProcess(-1);
                }
                else
                {
                    procSetVar procSetGameVer = (procSetVar)GetProcAddress(pluglib, "SetGameVer");
                    if (!procSetGameVer(gameVersion))
                    {
                        FreeLibrary(pluglib);
                        MessageBox(NULL, L"Some plugin is not for this executable!",
                                   L"D3DRM(Custom)", MB_ICONERROR);
                    }
                }
            } while (FindNextFileA(v1, &FindFileData));
            return FindClose(v1);
        }
    }
    return result;
}

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