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

    // GENERAL
    patch.WriteU32((void *)0x004D4539, 0x8B04FAC1); // Take corium fix
    patch.WriteByte((void *)0x004693A6, 1); // Transport waiting distance set after depot
    patch.WriteByte((void *)0x00467488, 1); // Transport waiting distance set after mine
    patch.WriteByte((void *)0x004696F9, 1); // Transport waiting distance 3
    patch.WriteByte((void *)0x004699A1, 1); // Transport waiting distance set after mine order
    patch.WriteByte((void *)0x004438BE, 0xF9); // Transport Decision cmp 1"
    patch.WriteByte((void *)0x004438E8, 0xF9); // Transport Decision cmp 2

    patch.WriteU32((void *)0x007BF594, 8); // Gold level t1
    patch.WriteNops((void *)0x00553B9E, 13); // Call open cell view disable
    patch.WriteByte((void *)0x004691B2, 2); // Resource unload speed divisor
     

    // UNITS
    patch.WriteU32((void *)0x0080148C, 899); // Flagships add to wargroups 899
    patch.WriteU32((void *)0x004E87F7, 2425393296); // nops to not overwrite
    patch.WriteByte((void *)0x004E87FB, 144);
    
    // Flagships not in special groups
    patch.WriteByte((void *)0x004E87D7, 137);
    patch.WriteByte((void *)0x004E87D8, 242);

    

    #pragma region WS
    // UNITS
    patch.WriteU32((void *)0x007E0584, 500); // Terminator corium

    // BUILDINGS

    // Mines detection
    patch.WriteByte((void *)0x007E6490, 120); // Cruiser T1 damage
    patch.WriteByte((void *)0x007E6494, 160); // Cruiser T2 damage
    patch.WriteByte((void *)0x007E6498, 200); // Cruiser T3 damage
    patch.WriteByte((void *)0x007E649C, 230); // Cruiser T4 damage
    patch.WriteByte((void *)0x007E64A0, 270); // Cruiser T5 damage


    // REPAIR
    patch.WriteU32((void *)0x007E29FC, 400); // Docks repair cost WS
    patch.WriteU32((void *)0x007E093C, 125); // Repair speed Transport dock
    patch.WriteU32((void *)0x007E0944, 500); // Repair speed Terminator dock
    patch.WriteU32((void *)0x007E0920, 150); // Repair speed Sentinel dock
    patch.WriteU32((void *)0x007E0938, 125); // Repair speed Repair Platf dock
    patch.WriteU32((void *)0x007E0930, 325); // Repair speed Minelayer dock
    patch.WriteU32((void *)0x007E0934, 325); // Repair speed Marauder dock
    patch.WriteU32((void *)0x007E0948, 400); // Repair speed Liberator dock
    patch.WriteU32((void *)0x007E0924, 225); // Repair speed Hunter dock
    patch.WriteU32((void *)0x007E092C, 400); // Repair speed DC Bomber dock
    patch.WriteU32((void *)0x007E094C, 250); // Repair speed Builder WS dock
    patch.WriteU32((void *)0x007E0928, 550); // Repair speed Cruiser dock


    patch.WriteU32((void *)0x007E087C, 300); // Repair cost Transport dock
    patch.WriteU32((void *)0x007E0878, 200); // Repair cost Repair Platf dock
    patch.WriteU32((void *)0x007E0884, 500); // Repair cost Terminator dock
    patch.WriteU32((void *)0x007E0860, 200); // Repair cost Sentinel dock
    patch.WriteU32((void *)0x007E0870, 350); // Repair cost Minelayer dock
    patch.WriteU32((void *)0x007E0874, 400); // Repair cost Marauder dock
    patch.WriteU32((void *)0x007E0888, 350); // Repair cost Liberator dock
    patch.WriteU32((void *)0x007E0864, 200); // Repair cost Hunter dock
    patch.WriteU32((void *)0x007E086C, 500); // Repair cost DC Bomber dock
    patch.WriteU32((void *)0x007E088C, 500); // Repair cost Builder WS dock
    patch.WriteU32((void *)0x007E0868, 500); // Repair cost Cruiser dock


    // BUILD TIMES
    patch.WriteU32((void *)0x007E04B8, 500); // Repair platform


    // RESEARCH
    patch.WriteByte((void *)0x007BFDAA, 6); // WS ARMR T3 dep
    patch.WriteByte((void *)0x007BFDAE, 2); // WS ARMR T3 dep lvl
    patch.WriteByte((void *)0x007BFDF0, 6); // WS ARMR T4 dep
    patch.WriteByte((void *)0x007BFDF4, 4); // WS ARMR T4 dep lvl
    patch.WriteByte((void *)0x007BFDD7, 4); // WS LSRSCRN dep
    patch.WriteByte((void *)0x007BFDDB, 3); // WS LSRSCRN dep lvl
    patch.WriteByte((void *)0x007BFCAB, 7); // WS TRP1 dep
    patch.WriteByte((void *)0x007BFC79, 8); // WS DPTHMINE dep
    patch.WriteByte((void *)0x007BFD73, 15); // WS SENT DMG dep
    patch.WriteByte((void *)0x007C002F, 61); // WS CYBER dep"
    patch.WriteByte((void *)0x007BFFE4, 22); // WS SHRKCNTRL dep
    patch.WriteByte((void *)0x007BFD8C, 15); // WS PSIFIELD dep
    patch.WriteByte((void *)0x007BFDBE, 21); // WS TERMINATOR dep
    patch.WriteByte((void *)0x007BFD5A, 31); // WS UPG USG dep
    patch.WriteByte((void *)0x007BFE09, 24); // WS PLASMACANN dep
    patch.WriteByte((void *)0x007BFE22, 28); // WS CORIUM276 dep
    patch.WriteByte((void *)0x007BFE3B, 25); // WS NUKE dep

    patch.WriteU32((void *)0x007E54D0, 6000); // WS SPD T4 time
    patch.WriteU32((void *)0x007E5528, 4500); // WS UPG HFCANN time
    patch.WriteU32((void *)0x007E5638, 4500); // WS UPG USG time
    patch.WriteU32((void *)0x007E55C8, 5250); // WS PSIFIELD time
    patch.WriteU32((void *)0x007E55F8, 4500); // WS TERMINATOR time
    patch.WriteU32((void *)0x007E5668, 6000); // WS PLASMACANN time
    patch.WriteU32((void *)0x007E5618, 9000); // WS CORIUM276 time
    patch.WriteU32((void *)0x007E5608, 7500); // WS NUKE time


    // Flagships
    patch.WriteByte((void *)0x007C0E44, 7); // Research ID
    patch.WriteByte((void *)0x004E8341, 128); // Belongs race
    patch.WriteU32((void *)0x007E0534, 4500); // Time
    patch.WriteU32((void *)0x007E0834, 6000); // Metal
    patch.WriteU32((void *)0x007E05F4, 1200); // Corium
    patch.WriteU32((void *)0x007A8BB0, 151); // Weapon type
    patch.WriteU32((void *)0x007A8CF0, 30); // Reload
    patch.WriteU32((void *)0x007A8C50, 40); // Ammo
    patch.WriteU16((void *)0x0048C31c, 40); // Side shift 
    patch.WriteU16((void *)0x0048C333, -40); // Side shift 2
    patch.WriteU32((void *)0x007DFC44, 3000); // HP
    #pragma endregion


    #pragma region BO

    patch.WriteU16((void *)0x00798F8C, 6000); // Recharge station frequency 1
    patch.WriteU16((void *)0x00798F90, 3000); // Recharge station frequency 2
    patch.WriteU16((void *)0x004DFB09, 250); // Recharge station max charge (1)
    patch.WriteU16((void *)0x004DFB47, 250); // Recharge station max charge (2)
    patch.WriteU16((void *)0x004DFB53, 250); // Recharge station max charge (3)
    patch.WriteU16((void *)0x0044F773, 0xD233); // Radio stutter make zero before period
    patch.WriteByte((void *)0x0044F77B, 75);    // Radio stutter new period
    patch.WriteNops((void *)0x0057A320, 6);     // cassete check num
    //patch.WriteU32((void *)0x0057B6D6, );      // Cassete conus 1/radius


    // UNITS
    patch.WriteByte((void *)0x0045094E, 25); // Phantom discharge

    // BUILDINGS
    
    // TURRETS RANGE
    patch.WriteByte((void *)0x007922C8, 6); // Heavy laser first range
    patch.WriteByte((void *)0x00792288, 6); // Light laser first range
    
    //REPAIR
    patch.WriteU32((void *)0x007E2A00, 400); // Docks repair cost BO
    patch.WriteU32((void *)0x007E096C, 125); // Repair speed Transport dock
    patch.WriteU32((void *)0x007E0968, 125); // Repair speed Repair Platf dock
    patch.WriteU32((void *)0x007E0964, 325); // Repair speed Raider dock
    patch.WriteU32((void *)0x007E0974, 500); // Repair speed Phantom dock
    patch.WriteU32((void *)0x007E095C, 400); // Repair speed Invader dock
    patch.WriteU32((void *)0x007E0958, 600); // Repair speed Heavy Cruiser dock
    patch.WriteU32((void *)0x007E0950, 150); // Repair speed Fighter dock
    patch.WriteU32((void *)0x007E0954, 325); // Repair speed Destroyer dock
    patch.WriteU32((void *)0x007E0960, 325); // Repair speed Defender dock
    patch.WriteU32((void *)0x007E097C, 250); // Repair speed Builder BO dock
    patch.WriteU32((void *)0x007E0978, 500); // Repair speed Avenger dock
    patch.WriteU32((void *)0x007E08AC, 300); // Repair cost Transport dock
    patch.WriteU32((void *)0x007E08A8, 200); // Repair cost Repair Platf dock
    patch.WriteU32((void *)0x007E08A4, 350); // Repair cost Raider dock
    patch.WriteU32((void *)0x007E08B4, 500); // Repair cost Phantom dock
    patch.WriteU32((void *)0x007E089C, 400); // Repair cost Invader dock
    patch.WriteU32((void *)0x007E0898, 600); // Repair cost Heavy Cruiser dock
    patch.WriteU32((void *)0x007E0890, 300); // Repair cost Fighter dock
    patch.WriteU32((void *)0x007E0894, 250); // Repair cost Destroyer dock
    patch.WriteU32((void *)0x007E08A0, 350); // Repair cost Defender dock
    patch.WriteU32((void *)0x007E0894, 500); // Repair cost Builder BO dock
    patch.WriteU32((void *)0x007E0894, 500); // Repair cost Avenger BO dock


    // BUILD TIMES
    // Repair platform
    patch.WriteU32((void *)0x007E04E8, 500);


    // RESEARCH
    patch.WriteByte((void *)0x007C04CA, 142); // BO PHANTOM dep
    patch.WriteByte((void *)0x007C02A9, 0); // BO UPGEM dep from upg attack speed
    patch.WriteByte((void *)0x007C02AD, 0); // BO UPGEM dep lvl from upg attack speed
    patch.WriteByte((void *)0x007C0515, 39); // BO UPGNETSEC dep
    patch.WriteByte((void *)0x007C04E3, 39); // BO UPGRAIDER dep
    patch.WriteByte((void *)0x007C01E0, 1); // BO UPGSPLTR dep lvl
    patch.WriteByte((void *)0x007C01DC, 150); // BO UPGSPLTR dep
    patch.WriteU32((void *)0x007E58A8, 12000); // BO UPG ANTI SMP time
    patch.WriteByte((void *)0x007C0673, 139); // BO UPG MINESPD dep
    patch.WriteByte((void *)0x007C068C, 136); // BO UPG REPSPD dep
    patch.WriteU32((void *)0x007C0547, 44); // BO UPGLOCATOR dep


    //Flagships

    patch.WriteByte((void *)0x007C0E47, 38); // Research ID
    // Belongs race
    patch.WriteU32((void *)0x00800F4C, 356); 
    patch.WriteByte((void *)0x004E8364, 12);//al or
    patch.WriteByte((void *)0x004E8365, 36);//36 (0x24 + 0x140) = 356
    patch.WriteByte((void *)0x004E8366, 144);//nop
    
    patch.WriteU32((void *)0x007E0538, 4500); // Time
    patch.WriteU32((void *)0x007E0838, 5500); // Metal
    patch.WriteU32((void *)0x007E05F8, 1300); // Corium
    patch.WriteU32((void *)0x007A8BB4, 158); // Weapon type
    patch.WriteU32((void *)0x007A8CF4, 25); // Reload
    patch.WriteU32((void *)0x007A8C54, 40); // Ammo
    patch.WriteU32((void *)0x007DFC48, 2300); // HP
    #pragma endregion


    #pragma region SI

    patch.WriteU32((void *)0x007C1620, 4); // Silicoids corium coeff
    patch.WriteU32((void *)0x007C1624, 3); // Silicoids corium sell coeff
    patch.WriteU32((void *)0x007C1628, 1); // Silicoids silicon coeff
    patch.WriteU32((void *)0x007E6334, 10); // Acoustic mines storage
    patch.WriteU32((void *)0x007E6328, 750); // Acoustic mines storage

    // UNITS
    patch.WriteByte((void *)0x005F4CA3, 6); // BHE base AoE

    // BUILDINGS
    patch.WriteU32((void *)0x007E43DC, 800); // Silicon extractor HP
    
    // TURRETS RANGE
    patch.WriteU32((void *)0x00792498, 6); // DPT attack range 1
    patch.WriteU32((void *)0x0079249C, 10); // DPT attack range 2
    patch.WriteU32((void *)0x00792710, 121); // DPT attack range research id
    patch.WriteU32((void *)0x007E6738, 150); // DPT turret damage T1
    patch.WriteU32((void *)0x007E673C, 180); // DPT turret damage T2
    patch.WriteU32((void *)0x007E6740, 240); // DPT turret damage T3

     //RESEARCH
    patch.WriteByte((void *)0x007C08A3, 2); // SI TRPEVADE dep lvl
    patch.WriteByte((void *)0x007C08A4, 78); // SI TRPEVADE dep2
    patch.WriteByte((void *)0x007C08A8, 3); // SI TRPEVADE dep2 lvl
    patch.WriteByte((void *)0x007C0D9A, 113); // SI NRGSHLDNEUTR dep
    patch.WriteByte((void *)0x007C0D9E, 1); // SI NRGSHLDNEUTR dep lvl
    patch.WriteByte((void *)0x007C08B8, 109); // SI SPEED T3 dep
    patch.WriteByte((void *)0x007C0967, 110); // SI SPEED T4 dep 
    patch.WriteByte((void *)0x007C0D4F, 115); // SI UPDBHESHLS dep
    patch.WriteU32((void *)0x007E5A48, 6000); // SI UPG GASSHLLNCHR time

    
    //Flagships
    patch.WriteByte((void *)0x007C0E4A, 109); // Research ID
    patch.WriteU32((void *)0x00800F5C, 575); // Belongs race
    patch.WriteU16((void *)0x004E83A2, 204);
    patch.WriteU32((void *)0x007E053C, 4500); // Time
    patch.WriteU32((void *)0x007E0A7C, 5000); // Silicon
    patch.WriteU32((void *)0x007E05FC, 900); // Corium
    patch.WriteU32((void *)0x007A8CF8, 5); // Reload
    patch.WriteU32((void *)0x007DFC4C, 2000); // HP
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
