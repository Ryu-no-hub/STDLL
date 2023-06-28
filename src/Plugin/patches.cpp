#include "patches.h"
#include "config.h"
#include "Shared/Common.h"
#include "Shared/Patcher.h"
#include <windows.h>
//#include <string>

using namespace Common;
using namespace Patcher;

// Implement your patches here

static bool FlagshipsPatchs(Patcher::SPatch &patch) {
    // 1. config check
    //if (PluginConfig.StartZoneName.empty())
    //    return false;

#ifdef _DEBUG
    //MessageBoxA(NULL, "FlagshipsPatch LOL Debug", "", MB_OK);
#endif // _DEBUG

    //---------EXPERIMENTAL START-----
    // Fix max range 1
    //patch.WriteByte((void *)0x004C3CC2, 0xF6);
    // Fix max range 2
    //patch.WriteByte((void *)0x004C3CF0, 0xF6);
    // Fix max range 3
    //patch.WriteByte((void *)0x004C3CC2, 0xA);
    // Fix max range 4
    //patch.WriteByte((void *)0x004C3CC5, 0xA);
    // Fix max range 5
    //patch.WriteByte((void *)0x004C426F, 0xA);
    // Fix max range 6
    //patch.WriteByte((void *)0x004C4281, 0xA);
    //---------EXPERIMENTAL END -----

    //GENERAL
    // Take corium fix
    patch.WriteU32((void *)0x004D4539, 0x8B04FAC1);

    // Flagships add to wargroups 899
    patch.WriteU32((void *)0x0080148C, 899);
    //nops to not overwrite
    patch.WriteU32((void *)0x004E87F7, 2425393296);
    patch.WriteByte((void *)0x004E87FB, 144);
    
    // Flagships not in special groups
    patch.WriteByte((void *)0x004E87D7, 137);
    patch.WriteByte((void *)0x004E87D8, 242);

    // Fix max range for turrets

    #pragma region WS

    //Mines detection


    // Cruiser T1 damage
    patch.WriteByte((void *)0x007E6490, 120);
    // Cruiser T2 damage
    patch.WriteByte((void *)0x007E6494, 160);
    // Cruiser T3 damage
    patch.WriteByte((void *)0x007E6498, 200);
    // Cruiser T4 damage
    patch.WriteByte((void *)0x007E649C, 230);
    // Cruiser T5 damage
    patch.WriteByte((void *)0x007E64A0, 270);

    //__declspec ;


    // REPAIR
    // Repair speed Transport dock
    patch.WriteU32((void *)0x007E093C, 125);
    // Repair speed Terminator dock
    patch.WriteU32((void *)0x007E0944, 500);
    // Repair speed Sentinel dock
    patch.WriteU32((void *)0x007E0920, 150);
    // Repair speed Repair Platf dock
    patch.WriteU32((void *)0x007E0938, 125);
    // Repair speed Minelayer dock
    patch.WriteU32((void *)0x007E0930, 325);
    // Repair speed Marauder dock
    patch.WriteU32((void *)0x007E0934, 325);
    // Repair speed Liberator dock
    patch.WriteU32((void *)0x007E0948, 400);
    // Repair speed Hunter dock
    patch.WriteU32((void *)0x007E0924, 225);
    // Repair speed DC Bomber dock
    patch.WriteU32((void *)0x007E092C, 400);
    // Repair speed Builder WS dock
    patch.WriteU32((void *)0x007E094C, 250);
    // Repair speed Cruiser dock
    patch.WriteU32((void *)0x007E0928, 550);

    // Repair cost Transport dock
    patch.WriteU32((void *)0x007E087C, 300);
    // Repair cost Repair Platf dock
    patch.WriteU32((void *)0x007E0878, 200);
    // Repair cost Terminator dock
    patch.WriteU32((void *)0x007E0884, 500);
    // Repair cost Sentinel dock
    patch.WriteU32((void *)0x007E0860, 200);
    // Repair cost Minelayer dock
    patch.WriteU32((void *)0x007E0870, 350);
    // Repair cost Marauder dock
    patch.WriteU32((void *)0x007E0874, 400);
    // Repair cost Liberator dock
    patch.WriteU32((void *)0x007E0888, 350);
    // Repair cost Hunter dock
    patch.WriteU32((void *)0x007E0864, 200);
    // Repair cost DC Bomber dock
    patch.WriteU32((void *)0x007E086C, 500);
    // Repair cost Builder WS dock
    patch.WriteU32((void *)0x007E088C, 500);
    // Repair cost Cruiser dock
    patch.WriteU32((void *)0x007E0868, 500);


     // BUILD TIMES
    // Repair platform
    patch.WriteU32((void *)0x007E04B8, 500);


    // RESEARCH
    // WS ARMR T3 dep
    patch.WriteByte((void *)0x007BFDAA, 6);
    // WS ARMR T3 dep lvl
    patch.WriteByte((void *)0x007BFDAE, 2);
    // WS ARMR T4 dep
    patch.WriteByte((void *)0x007BFDF0, 6);
    // WS ARMR T4 dep lvl
    patch.WriteByte((void *)0x007BFDF4, 4);
    // WS LSRSCRN dep
    patch.WriteByte((void *)0x007BFDD7, 4);
    // WS LSRSCRN dep lvl
    patch.WriteByte((void *)0x007BFDDB, 3);
    // WS TRP1 dep
    patch.WriteByte((void *)0x007BFCAB, 7);


    // Flagships
    // Research ID
    patch.WriteByte((void *)0x007C0E44, 7);
    // Belongs race
    //patch.WriteU32((void *)0x00800F3C, 128);
    patch.WriteByte((void *)0x004E8341, 128);
    // Time
    patch.WriteU32((void *)0x007E0534, 4500);
    // Metal
    patch.WriteU32((void *)0x007E0834, 6000);
    // Corium
    patch.WriteU32((void *)0x007E05F4, 1200);
    // Weapon type
    patch.WriteU32((void *)0x007A8BB0, 151);
    // Reload
    patch.WriteU32((void *)0x007A8CF0, 30);
    // Ammo
    patch.WriteU32((void *)0x007A8C50, 40);
    // Side shift ??
    patch.WriteU16((void *)0x0048C31c, 40);
    // Side shift 2 ??
    patch.WriteU16((void *)0x0048C333, -40);
    // HP
    patch.WriteU32((void *)0x007DFC44, 3000);

    #pragma endregion


    #pragma region BO

    // Recharge station frequency 1
    patch.WriteU16((void *)0x00798F8C, 6000);
    // Recharge station frequency 2
    patch.WriteU16((void *)0x00798F90, 3000);
    // Recharge station max charge (1)
    patch.WriteU16((void *)0x004DFB09, 250);
    // Recharge station max charge (2)
    patch.WriteU16((void *)0x004DFB47, 250);
    // Recharge station max charge (3)
    patch.WriteU16((void *)0x004DFB53, 250);
    // Radio stutter make zero before period
    patch.WriteU16((void *)0x0044F773, 0xD233);
    // Radio stutter new period
    patch.WriteByte((void *)0x0044F77B, 75);

    
    //REPAIR
    // Repair speed Transport dock
    patch.WriteU32((void *)0x007E096C, 125);
    // Repair speed Repair Platf dock
    patch.WriteU32((void *)0x007E0968, 125);
    // Repair speed Raider dock
    patch.WriteU32((void *)0x007E0964, 325);
    // Repair speed Phantom dock
    patch.WriteU32((void *)0x007E0974, 500);
    // Repair speed Invader dock
    patch.WriteU32((void *)0x007E095C, 400);
    // Repair speed Heavy Cruiser dock
    patch.WriteU32((void *)0x007E0958, 600);
    // Repair speed Fighter dock
    patch.WriteU32((void *)0x007E0950, 150);
    // Repair speed Destroyer dock
    patch.WriteU32((void *)0x007E0954, 325);
    // Repair speed Defender dock
    patch.WriteU32((void *)0x007E0960, 325);
    // Repair speed Builder BO dock
    patch.WriteU32((void *)0x007E097C, 250);
    // Repair speed Avenger dock
    patch.WriteU32((void *)0x007E0978, 500);

    // Repair cost Transport dock
    patch.WriteU32((void *)0x007E08AC, 300);
    // Repair cost Repair Platf dock
    patch.WriteU32((void *)0x007E08A8, 200);
    // Repair cost Raider dock
    patch.WriteU32((void *)0x007E08A4, 350);
    // Repair cost Phantom dock
    patch.WriteU32((void *)0x007E08B4, 500);
    // Repair cost Invader dock
    patch.WriteU32((void *)0x007E089C, 400);
    // Repair cost Heavy Cruiser dock
    patch.WriteU32((void *)0x007E0898, 600);
    // Repair cost Fighter dock
    patch.WriteU32((void *)0x007E0890, 300);
    // Repair cost Destroyer dock
    patch.WriteU32((void *)0x007E0894, 250);
    // Repair cost Defender dock
    patch.WriteU32((void *)0x007E08A0, 350);
    // Repair cost Builder BO dock
    patch.WriteU32((void *)0x007E0894, 500);
    // Repair cost Avenger BO dock
    patch.WriteU32((void *)0x007E0894, 500);


    // BUILD TIMES
    // Repair platform
    patch.WriteU32((void *)0x007E04E8, 500);


    // RESEARCH
    // BO PHANTOM dep
    patch.WriteByte((void *)0x007C04CA, 142);
    // BO UPGEM dep from upg attack speed
    patch.WriteByte((void *)0x007C02A9, 0);
    // BO UPGEM dep lvl from upg attack speed
    patch.WriteByte((void *)0x007C02AD, 0);
    // BO UPGNETSEC dep
    patch.WriteByte((void *)0x007C0515, 39);
    // BO UPGRAIDER dep
    patch.WriteByte((void *)0x007C04E3, 39);
    // BO UPGSPLTR dep lvl
    patch.WriteByte((void *)0x007C01E0, 1);
    // BO UPGSPLTR dep
    patch.WriteByte((void *)0x007C01DC, 150);

    //Flagships
    // Research ID
    patch.WriteByte((void *)0x007C0E47, 38);
    // Belongs race
    //patch.WriteU32((void *)0x0080134C, 356);
    patch.WriteU32((void *)0x00800F4C, 356);
    patch.WriteByte((void *)0x004E8364, 12);//al or
    patch.WriteByte((void *)0x004E8365, 36);//36 (0x24 + 0x140) = 356
    patch.WriteByte((void *)0x004E8366, 144);//nop
    
    // Time
    patch.WriteU32((void *)0x007E0538, 4500);
    // Metal
    patch.WriteU32((void *)0x007E0838, 5500);
    // Corium
    patch.WriteU32((void *)0x007E05F8, 1300);
    // Weapon type
    patch.WriteU32((void *)0x007A8BB4, 158);
    // Reload
    patch.WriteU32((void *)0x007A8CF4, 25);
    // Ammo
    patch.WriteU32((void *)0x007A8C54, 40);
    //// Side shift ??
    //patch.WriteI16((void *)0x0048C31c, 40);
    //// Side shift 2 ??
    //patch.WriteI16((void *)0x0048C333, -40);
    // HP
    patch.WriteU32((void *)0x007DFC48, 2300);
    #pragma endregion


    #pragma region SI

    // Silicoids corium coeff
    patch.WriteU32((void *)0x007C1620, 4);
    // Silicoids corium sell coeff
    patch.WriteU32((void *)0x007C1624, 3);
    // Silicoids silicon coeff
    patch.WriteU32((void *)0x007C1628, 1);


    //Turrets range
    // DPT attack range 1
    patch.WriteU32((void *)0x00792498, 6);
    // DPT attack range 2
    patch.WriteU32((void *)0x0079249C, 10);
    // DPT attack range research id
    patch.WriteU32((void *)0x00792710, 121);
    // DPT turret damage T1
    patch.WriteU32((void *)0x007E6738, 150);
    // DPT turret damage T2
    patch.WriteU32((void *)0x007E673C, 180);
    // DPT turret damage T3
    patch.WriteU32((void *)0x007E6740, 240);


     //RESEARCH
    // SI TRPEVADE dep lvl
    patch.WriteByte((void *)0x007C08A3, 2);
    // SI TRPEVADE dep2
    patch.WriteByte((void *)0x007C08A4, 78);
    // SI TRPEVADE dep2 lvl
    patch.WriteByte((void *)0x007C08A8, 3);
    // SI NRGSHLDNEUTR dep
    patch.WriteByte((void *)0x007C0D9A, 113);
    // SI NRGSHLDNEUTR dep lvl
    patch.WriteByte((void *)0x007C0D9E, 1);
    // SI SPEED T3 dep
    patch.WriteByte((void *)0x007C08B8, 109);
    // SI SPEED T4 dep 
    patch.WriteByte((void *)0x007C0967, 110);
    // SI UPDBHESHLS dep
    patch.WriteByte((void *)0x007C0D4F, 115);

    
    //Flagships
    // Research ID
    patch.WriteByte((void *)0x007C0E4A, 109);
    // Belongs race
    patch.WriteU32((void *)0x00800F5C, 575);
    patch.WriteU16((void *)0x004E83A2, 204);
    // Time
    patch.WriteU32((void *)0x007E053C, 4500);
    // Silicon
    patch.WriteU32((void *)0x007E0A7C, 5000);
    // Corium
    patch.WriteU32((void *)0x007E05FC, 900);
    // Reload
    patch.WriteU32((void *)0x007A8CF8, 5);
    // HP
    patch.WriteU32((void *)0x007DFC4C, 2000);
    #pragma endregion
    
    return true;
}


typedef bool (*PatchFunction)(Patcher::SPatch &patch);
static const PatchFunction Patches[] = {
    // Put your patch functions here:
    FlagshipsPatchs,
};

// Below is a code to apply patches
#pragma region PatchesApplyingSystem

static DWORD _OldProtections[2];
static char *_BaseAddr = (char *)0x400000;
//static char *_BaseAddr = (char *)0x401000;

// TODO: check sections addreses
static void GameMemLock()
{
    DWORD tmp;
    // Lock .text
    if (!VirtualProtect(_BaseAddr + 0x1000, 0x33A000, _OldProtections[0], &tmp))
    //if (!VirtualProtect(_BaseAddr + 0x1000, 0x33A000, _OldProtections[0], &tmp))
        ErrorMsgBox(1, "Cannot lock game .text section. VirtualProtect failed: 0x%X",
                    (unsigned)GetLastError());
    //MessageBoxA(NULL, _BaseAddr, "", MB_OK);
    FlushInstructionCache(GetCurrentProcess(), _BaseAddr + 0x1000, 0x33A000);
    // Lock .rdata
    if (!VirtualProtect(_BaseAddr + 0x33B000, 0x48000, _OldProtections[1], &tmp))
        ErrorMsgBox(1, "Cannot lock game .rdata section. VirtualProtect failed: 0x%X",
                    (unsigned)GetLastError());
}

static void GameMemUnlock()
{
    // Unlock .text
    if (!VirtualProtect(_BaseAddr + 0x1000, 0x33A000, PAGE_EXECUTE_READWRITE, &_OldProtections[0]))
        ErrorMsgBox(1, "Cannot unlock game .text section. VirtualProtect failed: 0x%X",
                    (unsigned)GetLastError());
    // Unlock .rdata
    if (!VirtualProtect(_BaseAddr + 0x33B000, 0x48000, PAGE_READWRITE, &_OldProtections[1]))
        ErrorMsgBox(1, "Cannot unlock game .rdata section. VirtualProtect failed: 0x%X",
                    (unsigned)GetLastError());
}

void ApplyPatches()
{
    GameMemUnlock();
    for (size_t i = 0; i < _countof(Patches); i++)
    {
        Patcher::SPatch patch;
        if (!Patches[i](patch))
            continue; // Skip disabled patch

        for (auto it = patch.Chunks.cbegin(); it != patch.Chunks.cend(); ++it)
            memcpy(it->Addr, &it->Data[0], it->Data.size());
    }
    GameMemLock();
}
#pragma endregion
