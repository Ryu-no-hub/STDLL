#include "patches.h"
#include "config.h"
#include "Shared/Common.h"
#include "Shared/Patcher.h"
#include <windows.h>
#include "winhttp.h"
#include <string>

using namespace Common;
using namespace Patcher;

WCHAR Buffer[MAX_PATH];
auto result = GetCurrentDirectoryW(MAX_PATH, Buffer);

std::wstring FileDirectory(Buffer);
std::wstring full_path = FileDirectory + L"\\plugins\\config.ini";
static LPCWSTR ini_file = full_path.c_str();

#pragma comment(lib, "winhttp.lib")


    
// Implement your patches here
static bool AutosaveIPXNetGame(Patcher::SPatch &patch)
{
    patch.WriteJumpSized(AutosaveCheckTick_Jmp, 5, (unsigned long)AutosaveCheckTick);
    patch.WriteJumpSized(AutosaveCheckMarker_Jmp, 8, (unsigned long)AutosaveCheckMarker);
    patch.WriteJumpSized(AutosaveMakeFileName_Jmp, 5, (unsigned long)AutosaveMakeFileName);
    patch.WriteJumpSized(AutosaveDontCheckIfFileExists_Jmp, 5, (unsigned long)AutosaveDontCheckIfFileExists);
    patch.WriteJumpSized(AutosaveSkipToggleMenu_Jmp, 7, (unsigned long)AutosaveSkipToggleMenu);
    patch.WriteJumpSized(DontResetHostFlag_Jmp, 8, (unsigned long)DontResetHostFlag);
    return true;
}

static bool FixesQoL(Patcher::SPatch &patch) {
    // 1. config check
    //if (PluginConfig.StartZoneName.empty())
    //    return false;

#ifdef _DEBUG
    //MessageBoxA(NULL, "FlagshipsPatch LOL Debug", "", MB_OK);
#endif // _DEBUG

    // GENERAL
    patch.WriteJumpSized(ChangeGameVersion_Jmp, 5, (unsigned long)ChangeGameVersion);

    patch.WriteU32((void *)0x004D4539, 0x8B04FAC1); // Take corium when finish building fix

    patch.WriteJumpSized(MinesDetectionWS_Jmp, 5, (unsigned long)MinesDetectionWS);
    patch.WriteJumpSized(MinesDetectionBO_Jmp, 5, (unsigned long)MinesDetectionBO);
    patch.WriteJumpSized(MinesDetectionSI_Jmp, 5, (unsigned long)MinesDetectionSI);


    patch.WriteJumpSized(OpenMap_Jmp, 6, (unsigned long)OpenMap);
    patch.WriteNops((void *)0x00553B9E, 13); // Call open cell view disable

    patch.WriteJumpSized(UpgBHEExpansionRate_Jmp, 10, (unsigned long)UpgBHEExpansionRate);
    patch.WriteJumpSized(UpgBHESpeed_Jmp, 10, (unsigned long)UpgBHESpeed);
    patch.WriteJumpSized(UpgBHEDotsAmount_Jmp, 6, (unsigned long)UpgBHEDotsAmount);

    patch.WriteJumpSized(UpgRepairSpeed_Jmp, 5, (unsigned long)UpgRepairSpeed);
    patch.WriteJumpSized(UpgRepairSpeed2_Jmp, 7, (unsigned long)UpgRepairSpeed2);
    patch.WriteJumpSized(UpgRepairSpeedPlatf_Jmp, 5, (unsigned long)UpgRepairSpeedPlatf);

    patch.WriteJumpSized(TargetingNoHpPriority_Jmp, 9, (unsigned long)TargetingNoHpPriority);

    patch.WriteNops((void *)0x004D86C3, 6); // No gold for Silicoids
    patch.WriteJumpSized(GoldForHumansOnly_Jmp, 7, (unsigned long)GoldForHumansOnly);

    patch.WriteJumpSized(NoEnergyOverflow_Jmp, 5, (unsigned long)NoEnergyOverflow);

    patch.WriteJumpSized(FOWConstruction_Jmp, 5, (unsigned long)FOWConstruction);

    patch.WriteJumpSized(RecycleSiliconHalfCoeff_Jmp, 7, (unsigned long)RecycleSiliconHalfCoeff);
    //patch.WriteJumpSized(RecycleMetalContainerQuarterCoeff_Jmp, 5, (unsigned long)RecycleMetalContainerQuarterCoeff);
    patch.WriteJumpSized(RecycleContainerCallUpdate_Jmp, 5, (unsigned long)RecycleContainerCallUpdate);
    patch.WriteJumpSized(RecycleContainerPushPlayer_Jmp, 6, (unsigned long)RecycleContainerPushPlayer);
    patch.WriteNops((void *)0x004B7EA7, 6); // Recycle container nop row

    patch.WriteJumpSized(BioassaulterAddMinesResearched_Jmp, 5, (unsigned long)BioassaulterAddMinesResearched);
    //patch.WriteJumpSized(AcousticMinesCheck_Jmp, 5, (unsigned long)AcousticMinesCheck);

    patch.WriteJumpSized(CyberNoArmor_Jmp, 5, (unsigned long)CyberNoArmor);

    patch.WriteJumpSized(PSGDamageReductionFix_Jmp, 5, (unsigned long)PSGDamageReductionFix);

    patch.WriteJumpSized(SplinterTorpedoRangex201_Jmp, 8, (unsigned long)SplinterTorpedoRangex201);
    patch.WriteJumpSized(SplinterTorpedoFixCalc_Jmp, 6, (unsigned long)SplinterTorpedoFixCalc);
    patch.WriteJumpSized(SplinterTorpedoAoEDamageCheckLvl_Jmp, 5, (unsigned long)SplinterTorpedoAoEDamageCheckLvl);

    patch.WriteNops((void *)0x0046C302, 10); // No move after build
    patch.WriteNops((void *)0x0046BF91, 10); // No move after build 2

    patch.WriteNops((void *)0x00640BEE, 12); // Medium torpedo no carrier type check
    //patch.WriteU32((void *)0x00467248, 10); // Resource load speed divisor (current)

    patch.WriteJumpSized(AltRMBForLineFormation_Jmp, 5, (unsigned long)AltRMBForLineFormation);
    patch.WriteJumpSized(AltRMBNoDoubleOrder_Jmp, 7, (unsigned long)AltRMBNoDoubleOrder);

    //patch.WriteJumpSized(PingMap_Jmp, 5, (unsigned long)PingMap);
    //patch.WriteJumpSized(PingMapSendMail_Jmp, 5, (unsigned long)PingMapSendMail);
    //patch.WriteJumpSized(PingMapInterceptCommand_Jmp, 5, (unsigned long)PingMapInterceptCommand);
    //patch.WriteByte((void *) 0x0054F116, 0); // New command (27(22 slot)) jumptable for command size = 12
    //patch.WriteByte((void *)0x00438715, 1);

    patch.WriteJumpSized(BoxCursorLoadCheck1_Jmp, 5, (unsigned long)BoxCursorLoadCheck1);
    patch.WriteJumpSized(BoxCursorLoadCheck2_Jmp, 10, (unsigned long)BoxCursorLoadCheck2);

    patch.WriteJumpSized(AlwaysShowHP_Jmp, 6, (unsigned long)AlwaysShowHP);
    patch.WriteJumpSized(DecreaseShowHPState_Jmp, 8, (unsigned long)DecreaseShowHPState);

    patch.WriteNops((void *)0x00489C36, 6); // No extra 200 priority to building targets in range
       
  
    patch.WriteU32((void *)0x005C8253, 0x0079C050); // Random map directory - custom
    patch.WriteU32((void *)0x005C851C, 0x0079C050); // Random map directory - custom 2
    patch.WriteU32((void *)0x005C7AE8, 0x0079C050); // Random map directory - custom 3

    patch.WriteU32((void *)0x0047A44E, 0); // Give ghost state teleport
    patch.WriteByte((void *)0x004ECC7D, GetPrivateProfileInt(L"Teleshield", L"Range", 8, ini_file));  // Increase teleshield range
    //patch.WriteJumpSized(SetMineInSubLocation_Jmp, 21, (unsigned long)SetMineInSubLocation);

    
    patch.WriteU16((void *)0x004767E3, 75); // Set mine in submarine location z
    patch.WriteU16((void *)0x004767EA, 73); // Set mine in submarine location y
    patch.WriteU16((void *)0x004767F1, 71); // Set mine in submarine location x    

    
    patch.WriteJumpSized(ReturnResourcesCanceledBuilding_Jmp, 7, (unsigned long)ReturnResourcesCanceledBuilding);
    
    patch.WriteJumpSized(FixIonFieldResist_Jmp, 6, (unsigned long)FixIonFieldResist);
    patch.WriteNops((void *)0x004BB442, 24); // Nops for prev script

    
    patch.WriteByte((void *)0x0041C533, 2); // View mode resident
    patch.WriteByte((void *)0x0041C534, 1); // View mode scout
    patch.WriteByte((void *)0x0041C4AF, 32); // Max sub id to not skip in defining view mode

    
    patch.WriteU32((void *)0x007D2220, GetPrivateProfileInt(L"Weap_ParalyzeRay", L"Time", 375, ini_file)); // Paralyze ray time
    patch.WriteU32((void *)0x007D2210, GetPrivateProfileInt(L"Weap_NeuroParalyzeShell", L"Time", 250, ini_file)); // NeuroParalyze shell time 
    

    patch.WriteJumpSized(MessageResearchComplete_Jmp, 6, (unsigned long)MessageResearchComplete);

    //patch.WriteJumpSized(PSGCreateStruct_Jmp, 5, (unsigned long)PSGCreateStruct);
    //patch.WriteJumpSized(PSGPlacingCheck_Jmp, 9, (unsigned long)PSGPlacingCheck);
    //patch.WriteJumpSized(PSGClearStruct_Jmp, 9, (unsigned long)PSGClearStruct);
    //patch.WriteJumpSized(PSGClearStruct2_Jmp, 5, (unsigned long)PSGClearStruct2);
    //patch.WriteJumpSized(PSGFuncClearForcefieldUse_Jmp, 7, (unsigned long)PSGFuncClearForcefieldUse);
    //patch.WriteJumpSized(PSGFuncClearForcefieldUse2_Jmp, 7, (unsigned long)PSGFuncClearForcefieldUse2);
    //patch.WriteJumpSized(PSGFuncClearForcefieldUse3_Jmp, 7, (unsigned long)PSGFuncClearForcefieldUse3);
    //patch.WriteJumpSized(PSGFuncClearForcefieldUse4_Jmp, 7, (unsigned long)PSGFuncClearForcefieldUse4);
    //patch.WriteJumpSized(PSGFuncClearForcefieldUse5_Jmp, 11, (unsigned long)PSGFuncClearForcefieldUse5);
    //patch.WriteJumpSized(PSGAddNumberBeforeComplete_Jmp, 5, (unsigned long)PSGAddNumberBeforeComplete);
    //patch.WriteJumpSized(PSGFuncMakePowerProtectorUse_Jmp, 7, (unsigned long)PSGFuncMakePowerProtectorUse);
    //patch.WriteJumpSized(PSGFuncMakePowerProtectorUse2_Jmp, 7, (unsigned long)PSGFuncMakePowerProtectorUse2);
    //patch.WriteJumpSized(PSGFuncMakePowerProtectorUse3_Jmp, 7, (unsigned long)PSGFuncMakePowerProtectorUse3);

    patch.WriteJumpSized(PrivateOrderSounds_Jmp, 5, (unsigned long)PrivateOrderSounds);    
    
    patch.WriteJumpSized(OrbitalLaserFasterBuild_Jmp, 5, (unsigned long)OrbitalLaserFasterBuild);
    
    //Capture tech
    patch.WriteZeros((void *)0x007E1218, 384); // ALL ZERO
    patch.WriteU32((void *)0x007E123C, 3000); // Techcenters
    patch.WriteU32((void *)0x007E1240, 3000); // Techcenters
    patch.WriteU32((void *)0x007E14F4, 0);    // Something else to zero
    patch.WriteU32((void *)0x007E14F8, 0);    // Something else to zero

    // Research implement upgrades
    patch.WriteJumpSized(UPGNRGACCUM_decrease_deposit_Jmp, 9, (unsigned long)UPGNRGACCUM_decrease_deposit);
    patch.WriteJumpSized(UPGNRGACCUM_increase_accum_Jmp, 9, (unsigned long)UPGNRGACCUM_increase_accum);

    patch.WriteJumpSized(CoriumMiningUpgrades_Jmp, 5, (unsigned long)CoriumMiningUpgrades);
    patch.WriteJumpSized(EnergyForSoliton_Jmp, 9, (unsigned long)EnergyForSoliton);


    // No dodge
    /* patch.WriteU32((void *)0x004612D5, 1); // Dodge flag set 1
    patch.WriteJumpSized(DodgeFlagSet2_Jmp, 6, (unsigned long)DodgeFlagSet2);
    patch.WriteJumpSized(DodgeFlagSet3_Jmp, 6, (unsigned long)DodgeFlagSet3);
    patch.WriteJumpSized(DodgeFlagSet4_Jmp, 6, (unsigned long)DodgeFlagSet4);
    patch.WriteU16((void *)0x00460BED, 0); // Dodge distance 1
    patch.WriteU16((void *)0x00460C95, 0); // Dodge distance 2
    patch.WriteU16((void *)0x00460C6A, 0); // Dodge distance 3
    */


    // Neccesary balance
    // UNITS-------
    patch.WriteU16((void *)0x00798F8C, 6000); // Recharge station frequency 1
    patch.WriteU16((void *)0x00798F90, 3000); // Recharge station frequency 2
    patch.WriteU16((void *)0x004DFB09, 125);  // Recharge station max charge (1)
    patch.WriteU16((void *)0x004DFB47, 125);  // Recharge station max charge (2)
    patch.WriteU16((void *)0x004DFB53, 125);  // Recharge station max charge (3)
    patch.WriteByte((void *)0x004C02F9, 3);   // Recharge station indicator adjust (x3)

    patch.WriteNops((void *)0x004AE542, 6); // Allow build on animals


    patch.WriteJumpSized(SiliconDumpWhenDepleted_Jmp, 6, (unsigned long)SiliconDumpWhenDepleted);

    // TURRETS RANGE
    patch.WriteU32((void *)0x00792498, GetPrivateProfileInt(L"Double_Plasma_Turret", L"Range_1", 8, ini_file));  // DPT range 1
    patch.WriteU32((void *)0x0079249C, GetPrivateProfileInt(L"Double_Plasma_Turret", L"Range_2", 10, ini_file)); // DPT range 2

    patch.WriteU32((void *)0x00792710, 121); // DPT range research id
    //

    patch.WriteU32((void *)0x007E6738, GetPrivateProfileInt(L"Weap_DoublePlasmaTurret", L"Damage_1", 100, ini_file)); // DPT turret damage T1
    patch.WriteU32((void *)0x007E673C, GetPrivateProfileInt(L"Weap_DoublePlasmaTurret", L"Damage_2", 120, ini_file)); // DPT turret damage T2
    patch.WriteU32((void *)0x007E6740, GetPrivateProfileInt(L"Weap_DoublePlasmaTurret", L"Damage_3", 160, ini_file)); // DPT turret damage T3

    patch.WriteU32((void *)0x007A8C90, 80); // Destroyer reload (vanilla 50)
    patch.WriteU32((void *)0x007E6620, 40);  // Destroyer T1 (vanilla 60)
    patch.WriteU32((void *)0x007E6624, 120); // Destroyer T2 (vanilla 150)

    patch.WriteU32((void *)0x007E0570, 280); // Mine-Layer corium
    patch.WriteU32((void *)0x007E05E0, 250); // Bio_Assaulter corium (vanilla 200)
    patch.WriteU32((void *)0x007E05A0, 280); // Defender corium
    // patch.WriteU32((void *)0x007E0A60, 900); // Bio_Assaulter silicon (vanilla 700)

    patch.WriteU32((void *)0x007E07B8, 400); // Repair platform WS metal
    patch.WriteU32((void *)0x007E07E8, 400); // Repair platform BO metal
    patch.WriteU32((void *)0x007DFBC8, 600); // Repair platf WS hp
    patch.WriteU32((void *)0x007DFBF8, 600); // Repair platf BO hp

    patch.WriteU32((void *)0x007DFC10, 200); // Module-Prototype hp

    patch.WriteU32((void *)0x007E0584, 500); // Terminator corium (600 vanila)


    //patch.WriteU32((void *)0x007E615C, 750); // Depth mine prodtime
    //patch.WriteU32((void *)0x007E6170, 750); // Laser snare prodtime
    //patch.WriteU32((void *)0x007E6328, 750); // Acoustic mines prodtime

    // patch.WriteU32((void *)0x007E6168, 10); // Depth mine storage arsenal
    // patch.WriteU32((void *)0x007E617C, 10); // Laser snare storage arsenal
    // patch.WriteU32((void *)0x007E6334, 10);  // Acoustic mines storage arsenal

    patch.WriteJumpSized(UpgParcherDmg_Jmp, 5, (unsigned long)UpgParcherDmg);



    // Multiplayer mode cheats
    // patch.WriteByte((void *)0x00521D4B, 2); // Cheat read gamemode check
    // patch.WriteByte((void *)0x00522898, 2); // Cheat read gamemode check 2

    // patch.WriteByte((void *)0x005F4CA3, ); // BHE base AoE

    // patch.WriteNops((void *)0x00642944, 2); // Medium torpedo 100% AOE dmg (vanilla  50%)
    // patch.WriteByte((void *)0x006382CB, 2); // Ripple effect strength (standard value)
    // patch.WriteU32((void *)0x007DFE00, 75); // STOLp reload (standard value)


    // BUILDINGS
    // BUILDTIME

    patch.WriteU32((void *)0x007E3DF4, 500); // sonar buildtime
    patch.WriteU32((void *)0x007E3DF8, 500); // sonar buildtime
    patch.WriteU32((void *)0x007E3E18, 500); // metal extractor buildtime
    patch.WriteU32((void *)0x007E3E1C, 500); // metal extractor buildtime
    patch.WriteU32((void *)0x007E3E20, 500); // metal extractor buildtime
    patch.WriteU32((void *)0x007E3E24, 500); // gold mine buildtime
    patch.WriteU32((void *)0x007E3E28, 500); // gold mine buildtime
    patch.WriteU32((void *)0x007E3F20, 500); // metal extractor buildtime
    patch.WriteU32((void *)0x007E3F24, 500); // metal extractor buildtime
    patch.WriteU32((void *)0x007E3F2C, 500); // oxygen generator buildtime
    patch.WriteU32((void *)0x007E3F30, 500); // oxygen generator buildtime


    patch.WriteU32((void *)0x007E3E54, 625); // HF_Canon buildtime
    patch.WriteU32((void *)0x007E3E58, 625); // HF_Canon buildtime
    patch.WriteU32((void *)0x007E3E5C, 625); // HF_Canon buildtime

    patch.WriteU32((void *)0x007E3E60, 1000); // STOLp buildtime
    patch.WriteU32((void *)0x007E3E64, 1000); // STOLp buildtime
    patch.WriteU32((void *)0x007E3E68, 1000); // STOLp buildtime

    patch.WriteU32((void *)0x007E3E84, 1000); // USG buildtime
    patch.WriteU32((void *)0x007E3E88, 1000); // USG buildtime
    patch.WriteU32((void *)0x007E3E8C, 1000); // USG buildtime

    patch.WriteU32((void *)0x007E3F38, 875); // Plasma_Canon buildtime
    patch.WriteU32((void *)0x007E3F3C, 875); // Plasma_Canon buildtime
    patch.WriteU32((void *)0x007E3F40, 875); // Plasma_Canon buildtime

    patch.WriteU32((void *)0x007E3EB4, 625); // Light_Laser buildtime
    patch.WriteU32((void *)0x007E3EB8, 625); // Light_Laser buildtime
    patch.WriteU32((void *)0x007E3EBC, 625); // Light_Laser buildtime

    patch.WriteU32((void *)0x007E3EE4, 875); // Heavy_Laser buildtime
    patch.WriteU32((void *)0x007E3EE8, 875); // Heavy_Laser buildtime
    patch.WriteU32((void *)0x007E3EEC, 875); // Heavy_Laser buildtime

    patch.WriteU32((void *)0x007E3EC0, 1125); // Magnetic_Mine_Launcher buildtime
    patch.WriteU32((void *)0x007E3EC4, 1125); // Magnetic_Mine_Launcher buildtime
    patch.WriteU32((void *)0x007E3EC8, 1125); // Magnetic_Mine_Launcher buildtime

    patch.WriteU32((void *)0x007E3EF0, 875); // EML launcher buildtime
    patch.WriteU32((void *)0x007E3EF4, 875); // EML launcher buildtime
    patch.WriteU32((void *)0x007E3EF8, 875); // EML launcher buildtime

    patch.WriteU32((void *)0x007E4070, 625); // Pulsar buildtime
    patch.WriteU32((void *)0x007E4074, 625); // Pulsar buildtime
    patch.WriteU32((void *)0x007E4078, 625); // Pulsar buildtime

    patch.WriteU32((void *)0x007E4028, 1000); // Soliton buildtime
    patch.WriteU32((void *)0x007E402C, 1000); // Soliton buildtime
    patch.WriteU32((void *)0x007E4030, 1000); // Soliton buildtime

    patch.WriteU32((void *)0x007E4040, 625); // DPT buildtime
    patch.WriteU32((void *)0x007E4044, 625); // DPT buildtime
    patch.WriteU32((void *)0x007E4048, 625); // DPT buildtime

    patch.WriteU32((void *)0x007E4034, 875); // Gas shell launcher buildtime
    patch.WriteU32((void *)0x007E4038, 875); // Gas shell launcher buildtime
    patch.WriteU32((void *)0x007E403C, 875); // Gas shell launcher buildtime

    patch.WriteU32((void *)0x007E40B8, 1000); // Parcher buildtime
    patch.WriteU32((void *)0x007E40BC, 1000); // Parcher buildtime
    patch.WriteU32((void *)0x007E40C0, 1000); // Parcher buildtime

    patch.WriteU32((void *)0x007C1620, 4); // Silicoids corium buy coeff
    patch.WriteU32((void *)0x007C1624, 3); // Silicoids corium sell coeff
    patch.WriteU32((void *)0x007C1628, 2); // Silicoids silicon coeff

    patch.WriteByte((void *)0x004D9A66, 20); // Gold mine storage
    patch.WriteJumpSized(GoldMineInterfaceAdjust_Jmp, 8, (unsigned long)GoldMineInterfaceAdjust);

    // Damage
    patch.WriteJumpSized(MediumTorpedoOnlyAoE_Jmp, 7, (unsigned long)MediumTorpedoOnlyAoE);

    patch.WriteU32((void *)0x007A8BF8, 20); // Invader torpedo stock

    patch.WriteU32((void *)0x007A8DA8, 15); // DC Bomber stock
    patch.WriteU32((void *)0x007A8DAC, 5);  // Mine-layer stock
    patch.WriteU32((void *)0x007A8DDC, 5);  // Defender stock
    patch.WriteU32((void *)0x007A8E1C, 1);  // Bio_Assaulter mine stock

    patch.WriteByte((void *)0x00645E92, 0); // Cassete subshell check upgrade
    patch.WriteU32((void *)0x007E66C0, 30); // Cassete subshell T1
    patch.WriteU32((void *)0x007E66C4, 45); // Cassete subshell T2
    patch.WriteU32((void *)0x007E66C8, 60); // Cassete subshell T3
    patch.WriteU32((void *)0x007E66CC, 75); // Cassete subshell T4
    patch.WriteU32((void *)0x007E66D0, 90); // Cassete subshell T5

    // REPAIR
    // WS
    patch.WriteU32((void *)0x007E29FC, 400);  // Docks repair cost WS
    patch.WriteU32((void *)0x007E093C, 125);  // Repair speed Transport dock
    patch.WriteU32((void *)0x007E0944, 500);  // Repair speed Terminator dock
    patch.WriteU32((void *)0x007E0920, 150);  // Repair speed Sentinel dock
    patch.WriteU32((void *)0x007E0938, 125);  // Repair speed Repair Platf dock
    patch.WriteU32((void *)0x007E0930, 325);  // Repair speed Minelayer dock
    patch.WriteU32((void *)0x007E0934, 325);  // Repair speed Marauder dock
    patch.WriteU32((void *)0x007E0948, 400);  // Repair speed Liberator dock
    patch.WriteU32((void *)0x007E0924, 225);  // Repair speed Hunter dock
    patch.WriteU32((void *)0x007E092C, 400);  // Repair speed DC Bomber dock
    patch.WriteU32((void *)0x007E094C, 250);  // Repair speed Builder WS dock
    patch.WriteU32((void *)0x007E0928, 550);  // Repair speed Cruiser dock
    patch.WriteU32((void *)0x007E08F4, 1500); // Repair speed Flagship WS dock

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
    patch.WriteU32((void *)0x007E0868, 550); // Repair cost Cruiser dock

    // BO
    patch.WriteU32((void *)0x007E2A00, 400);  // Docks repair cost BO
    patch.WriteU32((void *)0x007E096C, 125);  // Repair speed Transport dock
    patch.WriteU32((void *)0x007E0968, 125);  // Repair speed Repair Platf dock
    patch.WriteU32((void *)0x007E0964, 325);  // Repair speed Raider dock
    patch.WriteU32((void *)0x007E0974, 500);  // Repair speed Phantom dock
    patch.WriteU32((void *)0x007E095C, 400);  // Repair speed Invader dock
    patch.WriteU32((void *)0x007E0958, 600);  // Repair speed Heavy Cruiser dock
    patch.WriteU32((void *)0x007E0950, 150);  // Repair speed Fighter dock
    patch.WriteU32((void *)0x007E0954, 325);  // Repair speed Destroyer dock
    patch.WriteU32((void *)0x007E0960, 325);  // Repair speed Defender dock
    patch.WriteU32((void *)0x007E097C, 250);  // Repair speed Builder BO dock
    patch.WriteU32((void *)0x007E0978, 500);  // Repair speed Avenger dock
    patch.WriteU32((void *)0x007E08AC, 300);  // Repair cost Transport dock
    patch.WriteU32((void *)0x007E08A8, 200);  // Repair cost Repair Platf dock
    patch.WriteU32((void *)0x007E08A4, 350);  // Repair cost Raider dock
    patch.WriteU32((void *)0x007E08B4, 500);  // Repair cost Phantom dock
    patch.WriteU32((void *)0x007E089C, 400);  // Repair cost Invader dock
    patch.WriteU32((void *)0x007E0898, 600);  // Repair cost Heavy Cruiser dock
    patch.WriteU32((void *)0x007E0890, 300);  // Repair cost Fighter dock
    patch.WriteU32((void *)0x007E0894, 250);  // Repair cost Destroyer dock
    patch.WriteU32((void *)0x007E08A0, 350);  // Repair cost Defender dock
    patch.WriteU32((void *)0x007E08BC, 500);  // Repair cost Builder BO dock
    patch.WriteU32((void *)0x007E08B8, 600);  // Repair cost Avenger BO dock
    patch.WriteU32((void *)0x007E08F4, 1500); // Repair cost Flagship BO dock

    // BUILD TIMES
    patch.WriteU32((void *)0x007E04B8, 500); // Repair platform WS
    patch.WriteU32((void *)0x007E04E8, 500); // Repair platform BO
    //---------

    // REGEN
    patch.WriteJumpSized(Regen20Percent_Jmp, 7, (unsigned long)Regen20Percent); // Upgrage: +20% speed (vanilla 10%)
    
    patch.WriteU32((void *)0x007E0754, 40); // Skat regen speed
    patch.WriteU32((void *)0x007E0758, 20); // Dreadnaught regen speed
    // patch.WriteU32((void *)0x007E075C, ); // Escort regen speed
    patch.WriteU32((void *)0x007E0C70, 4500);  // Skat regen amount T1 (/1500)
    patch.WriteU32((void *)0x007E0C74, 6000);  // Skat regen amount T2 (/1500)
    patch.WriteU32((void *)0x007E0C78, 7500);  // Skat regen amount T3 (/1500)
    patch.WriteU32((void *)0x007E0C7C, 9000);  // Skat regen amount T4 (/1500)
    patch.WriteU32((void *)0x007E0C90, 10500); // Escort regen amount T1 (/1500)
    patch.WriteU32((void *)0x007E0C94, 13500); // Escort regen amount T2 (/1500)
    patch.WriteU32((void *)0x007E0C98, 16500); // Escort regen amount T3 (/1500)
    patch.WriteU32((void *)0x007E0C9C, 20500); // Escort regen amount T4 (/1500)
    patch.WriteU32((void *)0x007E0C80, 15000); // Dreadnaught regen amount T1 (/1500)
    patch.WriteU32((void *)0x007E0C84, 25500); // Dreadnaught regen amount T2 (/1500)
    patch.WriteU32((void *)0x007E0C88, 36000); // Dreadnaught regen amount T3 (/1500)
    patch.WriteU32((void *)0x007E0C8C, 45000); // Dreadnaught regen amount T4 (/1500)
    patch.WriteU32((void *)0x007E0C80, 7500); // Usurper regen amount T1 (/1500)
    patch.WriteU32((void *)0x007E0C84, 18000); // Usurper regen amount T2 (/1500)
    patch.WriteU32((void *)0x007E0C88, 27000); // Usurper regen amount T3 (/1500)
    patch.WriteU32((void *)0x007E0C8C, 36000); // Usurper regen amount T4 (/1500)

    // ECONOMICS
    patch.WriteU32((void *)0x007BF594, 7); // Gold level 1 (vanilla 5)

    patch.WriteU32((void *)0x007BF558, 100); // Starting gold t1
    patch.WriteU32((void *)0x007BF55C, 200); // Starting gold t2
    patch.WriteU32((void *)0x007BF560, 400); // Starting gold t2

    patch.WriteU32((void *)0x007BF564, 1000); // Starting energy t1
    patch.WriteU32((void *)0x007BF568, 3000); // Starting energy t2
    patch.WriteU32((void *)0x007BF56C, 5000); // Starting energy t2

    patch.WriteU32((void *)0x00550CB0, 500); // Starting trade amount

    patch.WriteJumpSized(TradeStep10_Jmp, 5, (unsigned long)TradeStep10);

    
    patch.WriteByte((void *)0x004F1203, 0x58); // Keep build panel on build
    patch.WriteNops((void *)0x004F1204, 4);   // Keep build panel on build

    //------
    patch.WriteByte((void *)0x0047A9D1, 0xEC); // Teleport charge use personal (-20)
    patch.WriteByte((void *)0x00487ED3, 0x14); // Teleport check charge to unlock button

    // patch.WriteJumpSized(CasseteShellExpl3CellsB4Target_Jmp, 6, (unsigned
    // long)CasseteShellExpl3CellsB4Target);
    patch.WriteJumpSized(CasseteShellExplMidWay_Jmp, 6, (unsigned long)CasseteShellExplMidWay);
    
    patch.WriteJumpSized(IonArmorBlockedDamageHalf_Jmp, 5, (unsigned long)IonArmorBlockedDamageHalf);
    patch.WriteNops((void *)0x00459E37, 2); // Ion armor nops

    patch.WriteJumpSized(InvisDetectionLoopAllies_Jmp, 5, (unsigned long)InvisDetectionLoopAllies);
    patch.WriteNops((void *)0x0041D1BE, 26); // Nops

    patch.WriteJumpSized(InvisDetectionLoopAlliesBoats_Jmp, 9, (unsigned long)InvisDetectionLoopAlliesBoats);
    patch.WriteNops((void *)0x0041C4CA, 40); // Nops
    
    patch.WriteJumpSized(LasMinesDetectionAllies_Jmp, 9, (unsigned long)LasMinesDetectionAllies);
    patch.WriteNops((void *)0x00494E47, 28); // Nops
    
    patch.WriteJumpSized(MinesDetectionAllies_Jmp, 9, (unsigned long)MinesDetectionAllies);
    patch.WriteNops((void *)0x00494E96, 28); // Nops

    patch.WriteJumpSized(ShowAllyMines_Jmp, 9, (unsigned long)ShowAllyMines);
    patch.WriteJumpSized(ShowAllyLasMines_Jmp, 9, (unsigned long)ShowAllyLasMines);
    patch.WriteJumpSized(MyMinesObservationForAllies_Jmp, 8, (unsigned long)MyMinesObservationForAllies);

    
    patch.WriteByte((void *)0x00799178, 18); // invis find in top research set
    patch.WriteByte((void *)0x0079917C, 1);  // invis find in top research set

    patch.WriteByte((void *)0x0058F0CB, 15); // Shark speed buff

    //patch.WriteU32((void *)0x007A8CB4, 100); // Avenger reload
    //patch.WriteJumpSized(AvengerNoAttackSpeedUpgrade_Jmp, 6,  (unsigned long)AvengerNoAttackSpeedUpgrade);
    //patch.WriteByte((void *)0x0048B975, 0);  // Avenger shot - side shift
    //patch.WriteByte((void *)0x0048BA09, 1);  // Avenger shot - shells number
    //patch.WriteU32((void *)0x007A8B74, 154); // Avenger weapon type

    patch.WriteByte((void *)0x00430881, 6); // Light torpedo jump to higher speed
    patch.WriteByte((void *)0x004308A3, 6); // Acid shell jump to higher speed (48 -> 60)
    
     // SPEED
    // WS
    // patch.WriteU32((void *)0x007DFC9C, 8); // Builder
    // patch.WriteU32((void *)0x007DFC8C, ); // Transport
    patch.WriteU32((void *)0x007DFC88, 12); // Repair platform

    // patch.WriteU32((void *)0x007DFD04, ); // Flagship
    // patch.WriteU32((void *)0x007DFC70, 15); // Setinel
    // patch.WriteU32((void *)0x007DFC74, 11); // Hunter
    // patch.WriteU32((void *)0x007DFC78, 7);  // Cruiser
    // patch.WriteU32((void *)0x007DFC7C, 6); // DC Bomber (standard)
    // patch.WriteU32((void *)0x007DFC80, ); // Minelayer
    // patch.WriteU32((void *)0x007DFC84, ); // Marauder
    // patch.WriteU32((void *)0x007DFC90, ); // Cyberworm
    // patch.WriteU32((void *)0x007DFC94, 8); // Terminator
    // patch.WriteU32((void *)0x007DFC98, ); // Liberator

    // BO
    // patch.WriteU32((void *)0x007DFCCC, 8); // Builder
    // patch.WriteU32((void *)0x007DFCBC, ); // Transport
    patch.WriteU32((void *)0x007DFCB8, 12); // Repair platform

    // patch.WriteU32((void *)0x007DFD08, ); // Flagship
    // patch.WriteU32((void *)0x007DFCA0, 15); // Fighter
    // patch.WriteU32((void *)0x007DFCA4, ); // Destroyer
    // patch.WriteU32((void *)0x007DFCA8, );  // Heavy Cruiser
    // patch.WriteU32((void *)0x007DFCAC, ); // Invader
    // patch.WriteU32((void *)0x007DFCB0, ); // Defender
    // patch.WriteU32((void *)0x007DFCB4, ); // Raider
    // patch.WriteU32((void *)0x007DFCC0, ); // Cyberdolphin
    // patch.WriteU32((void *)0x007DFCC4, 8); // Phantom
    // patch.WriteU32((void *)0x007DFCC8, ); // Avenger

    // SI
    // patch.WriteU32((void *)0x007DFCD0, 8); // Module-prototype
    // patch.WriteU32((void *)0x007DFCD4, ); // Transport
    patch.WriteU32((void *)0x007DFCD8, 12); // Supplier
    // patch.WriteU32((void *)0x007DFCE0, ); // Replenisher
    // patch.WriteU32((void *)0x007DFCFC, ); // Explorer

    // patch.WriteU32((void *)0x007DFD0C, 12); // Flagship
     patch.WriteU32((void *)0x007DFCE4, 13); // SHS
    // patch.WriteU32((void *)0x007DFCEC, ); // Escort
    // patch.WriteU32((void *)0x007DFCE8, ); // Drednaught
    // patch.WriteU32((void *)0x007DFCF4, ); // Usurper
    // patch.WriteU32((void *)0x007DFCF0, ); // Bio_Assaulter
    // patch.WriteU32((void *)0x007DFCF8, ); // Psi_Zond (Vermin)
    // patch.WriteU32((void *)0x007DFCDC, ); // Paralyzer

     
    patch.WriteByte((void *)0x004E4197, 5); // Replenish pod capacity (shift, result=4000)

    patch.WriteU16((void *)0x004DEBA6, 10000);       // Power protector charge 1
    patch.WriteU16((void *)0x004DED31, 10000);      // Power protector charge 2
    patch.WriteU16((void *)0x004DED21, 10000);       // Power protector charge 3
    patch.WriteU32((void *)0x004C0309, 0x346DC5D6); // Power protector indicator adjust (2^43/10000)

    //PANEL
    //patch.WriteByte((void *)0x0048798F, 6); // SI patrol instead of move Skat, Escort, Dreadnaught
    //patch.WriteByte((void *)0x00487EE8, 6); // SI patrol instead of move Bioassaulter
    patch.WriteByte((void *)0x004879DA, 6); // SI patrol instead of move Usurper
    //patch.WriteByte((void *)0x00488009, 6); // SI patrol instead of move Paralyser

    patch.WriteJumpSized(PatrolMidButtonSI_Jmp, 8, (unsigned long)PatrolMidButtonSI);
    patch.WriteJumpSized(PatrolMidButtonSIBIO_Jmp, 8, (unsigned long)PatrolMidButtonSIBIO);
    patch.WriteByte((void *)0x004881B1, 15); // Bio change slot for check mines ammo to deactivate button 1
    patch.WriteByte((void *)0x004881B7, 15); // Bio change slot for check mines ammo to deactivate button 2

    patch.WriteJumpSized(PatrolMidButtonSIPara_Jmp, 8, (unsigned long)PatrolMidButtonSIPara);
    patch.WriteJumpSized(PatrolMidButtonSIGroup_Jmp, 10, (unsigned long)PatrolMidButtonSIGroup);

    return true;
}

static bool LobbyAnnouncements(Patcher::SPatch &patch)
{
    patch.WriteJumpSized(SetHostFlag_Jmp, 6, (unsigned long)SetHostFlag_AnnounceGameHost_Detour);
    patch.WriteJumpSized(AnnounceGameCancel_Jmp, 6, (unsigned long)AnnounceGameCancel_Detour);
    patch.WriteJumpSized(AnnounceGameStart_Jmp, 5, (unsigned long)AnnounceGameStart_Detour);
    patch.WriteJumpSized(AnnounceGamePlayerLeft_Jmp, 6, (unsigned long)AnnounceGamePlayerLeft_Detour);
    patch.WriteJumpSized(DontResetHostFlag_Jmp, 8, (unsigned long)DontResetHostFlag);

    return true;
}





static bool BalancingNormalTree(Patcher::SPatch &patch)
{

    // Research make unavailable
    // patch.WriteByte((void *)0x00798FF6, ); // Mining upgrade ws
    // patch.WriteByte((void *)0x00799062, ); // Mining upgrade bo
    patch.WriteByte((void *)0x0079902B, 0); // Mining upgrade silicon si

    // patch.WriteByte((void *)0x0079902C, ); // Mining upgrade corium si
    patch.WriteByte((void *)0x00799070, 0); // WS Capture upg
    patch.WriteByte((void *)0x0079906C, 0); // BO Capture upg
    patch.WriteByte((void *)0x007BFBF8, 0); // SI Capture upg
    patch.WriteByte((void *)0x007BFBD6, 0); // SI TRPEVADE unavailable
    patch.WriteByte((void *)0x007BFBCF, 0); // SI IONARMOR unavailable
    

    // RESEARCH
    patch.WriteByte((void *)0x007BFDAA, 6);  // WS ARMR T3 dep2
    patch.WriteByte((void *)0x007BFDAE, 2);  // WS ARMR T3 dep2
    patch.WriteByte((void *)0x007BFDF0, 6);  // WS ARMR T4 dep
    patch.WriteByte((void *)0x007BFDF4, 4);  // WS ARMR T4 dep lvl
    patch.WriteByte((void *)0x007C002F, 61); // WS CYBER dep
    patch.WriteByte((void *)0x007BFFE4, 22); // WS SHRKCNTRL dep
    patch.WriteByte((void *)0x007BFD8C, 15); // WS PSIFIELD dep
    patch.WriteByte((void *)0x007BFE22, 28); // WS CORIUM276 dep
    patch.WriteByte((void *)0x007BFD5A, 31); // WS UPG USG dep
    patch.WriteByte((void *)0x007BFE3B, 25); // WS NUKE dep
    patch.WriteByte((void *)0x007BFDD7, 4);  // WS LSRSCRN dep
    patch.WriteByte((void *)0x007BFDDB, 3);  // WS LSRSCRN dep lvl
    patch.WriteByte((void *)0x007BFCAB, 7);  // WS DMG T2 dep
    patch.WriteByte((void *)0x007BFD73, 15); // WS SENT DMG dep

    patch.WriteU32((void *)0x007E54D0, 6000); // WS SPD T4 time
    patch.WriteU32((void *)0x007E55C8, 5250); // WS PSIFIELD time
    patch.WriteU32((void *)0x007E5608, 7500); // WS NUKE time
    patch.WriteU32((void *)0x007E5528, 4500); // WS UPG HFCANN time
    patch.WriteU32((void *)0x007E5638, 4500); // WS UPG USG time
    patch.WriteU32((void *)0x007E55F8, 4500); // WS TERMINATOR time
    patch.WriteU32((void *)0x007E5668, 6000); // WS PLASMACANN time
    patch.WriteU32((void *)0x007E54DC, 6000); // WS DMG T2 time
    patch.WriteU32((void *)0x007E5828, 4500); // WS TELESHIELD time
    

    patch.WriteByte((void *)0x007C0402, 143); // BO LASMINEFIND dep
    patch.WriteByte((void *)0x007C04CA, 142); // BO PHANTOM dep
    patch.WriteByte((void *)0x007C0515, 39);  // BO DEFHACK dep
    patch.WriteByte((void *)0x007C04E3, 44);  // BO UPGRAIDER dep
    patch.WriteByte((void *)0x007C068C, 136); // BO UPG REPSPD dep
    patch.WriteByte((void *)0x007C0673, 139); // BO UPG MINESPD dep

    patch.WriteU32((void *)0x007E56A8, 5250); // BO HEAVYCRUISER time
    patch.WriteU32((void *)0x007E57D8, 3500); // BO HEAVYCRUISER time

    patch.WriteByte((void *)0x007C0D86, 0); // SI PARALYZE T3 dep2
    patch.WriteByte((void *)0x007C08B8, 109); // SI SPEED T3 dep
    // patch.WriteByte((void *)0x007C08BC, ); // SI SPEED T3 lvl
    patch.WriteByte((void *)0x007C0B42, 101); // SI ANTIPSI dep
    patch.WriteByte((void *)0x007C0980, 123); // SI IONFIELD dep
    patch.WriteByte((void *)0x007C0985, 0);   // SI IONFIELD dep2
    patch.WriteByte((void *)0x007C09FD, 82);  // SI UPGCORMINE dep
    patch.WriteByte((void *)0x007C06F6, 0);   // SI PORTAL dep
    patch.WriteByte((void *)0x007C06DD, 96);  // SI PERSONALTELE dep
    patch.WriteByte((void *)0x007C06E1, 1);  // SI PERSONALTELE dep lvl
    patch.WriteByte((void *)0x007C070F, 95);  // SI RESIDENT dep
    patch.WriteByte((void *)0x007C0A98, 106);   // SI ORBITLAS dep2
    patch.WriteU32((void *)0x007C0D9E, 1);    // SI NEUTRSHIELD dep lvl
    

    patch.WriteU32((void *)0x007E5B4C, 7500); // SI SPEED T3 time
    //patch.WriteU32((void *)0x007E5AC8, 6000); // SI ARMOR T2 time
    patch.WriteU32((void *)0x007E5ACC, 10500); // SI ARMOR T3 time
    patch.WriteU32((void *)0x007E5AD0, 15000); // SI ARMOR T4 time

    patch.WriteByte((void *)0x007990B5, 16); // Mobile platforms id in Tech2
    patch.WriteByte((void *)0x007990B9, 1);  // Mobile platforms lvl in Tech2


    // SUBMARINES
   
    // SPEED Upgrade
    // patch.WriteByte((void *)0x0045F737, 4); // Plus total at T2
    patch.WriteByte((void *)0x0045F733, 4); // Plus total at T3
    patch.WriteByte((void *)0x0045F72F, 6); // Plus total at T4
        
    // BUILDINGS
    
    // HP
    patch.WriteU32((void *)0x007E43DC, 700);  // Silicon_Extractor HP (+100)
    patch.WriteU32((void *)0x007E417C, 3000); // Dockyard_WS HP
    patch.WriteU32((void *)0x007E4180, 3000); // Dockyard_BO HP
    patch.WriteU32((void *)0x007E4188, 2250); // Docks_WS HP
    patch.WriteU32((void *)0x007E418C, 2250); // Docks_BO HP
    patch.WriteU32((void *)0x007E4194, 1800); // WS Arsenal HP
    patch.WriteU32((void *)0x007E4198, 1800); // BO Arsenal HP
    patch.WriteU32((void *)0x007E41A0, 1500); // Lab_WS HP
    patch.WriteU32((void *)0x007E41A4, 1500); // Lab_BO HP
    patch.WriteU32((void *)0x007E4310, 2500); // SI Core HP
    patch.WriteU32((void *)0x007E4370, 1500); // SI Arsenal HP
    patch.WriteU32((void *)0x007E437C, 2250); // SI Protoplasm_Generator HP

    patch.WriteU32((void *)0x007E420C, 1200); // HF_Canon HP
    patch.WriteU32((void *)0x007E4210, 1200); // HF_Canon HP
    patch.WriteU32((void *)0x007E4214, 1200); // HF_Canon HP
    patch.WriteU32((void *)0x007E4218, 1600); // STOLp HP
    patch.WriteU32((void *)0x007E421C, 1600); // STOLp HP
    patch.WriteU32((void *)0x007E4220, 1600); // STOLp HP
    patch.WriteU32((void *)0x007E426C, 1000);  // Light_Laser HP
    patch.WriteU32((void *)0x007E4270, 1000);  // Light_Laser HP
    patch.WriteU32((void *)0x007E4274, 1000);  // Light_Laser HP
    //patch.WriteU32((void *)0x007E429C, 1300); // Heavy_Laser HP
    //patch.WriteU32((void *)0x007E42A0, 1300); // Heavy_Laser HP
    //patch.WriteU32((void *)0x007E42A4, 1300); // Heavy_Laser HP
    patch.WriteU32((void *)0x007E4428, 1000);  // Pulsar HP
    patch.WriteU32((void *)0x007E442C, 1000);  // Pulsar HP
    patch.WriteU32((void *)0x007E4430, 1000);  // Pulsar HP
    //patch.WriteU32((void *)0x007E43EC, 1200); // Gas_Canon HP (vanilla 1100)
    //patch.WriteU32((void *)0x007E43F0, 1200); // Gas_Canon HP (vanilla 1100)
    //patch.WriteU32((void *)0x007E43F4, 1200); // Gas_Canon HP (vanilla 1100)
    patch.WriteU32((void *)0x007E441C, 900);  // Bio_Mine_Launcher HP
    patch.WriteU32((void *)0x007E4420, 900);  // Bio_Mine_Launcher HP
    patch.WriteU32((void *)0x007E4424, 900);  // Bio_Mine_Launcher HP
    //patch.WriteU32((void *)0x007E43E0, 600);  // Soliton oscilator HP
    //patch.WriteU32((void *)0x007E43E4, 600);  // Soliton oscilator HP
    //patch.WriteU32((void *)0x007E43E8, 600);  // Soliton oscilator HP

    // Corium
    // WS
    patch.WriteU32((void *)0x007E1CE0, 80); // HF_Canon corium
    patch.WriteU32((void *)0x007E1CE4, 80); // HF_Canon corium
    patch.WriteU32((void *)0x007E1CE8, 80); // HF_Canon corium

    patch.WriteU32((void *)0x007E1CEC, 120); // STOLp corium
    patch.WriteU32((void *)0x007E1CF0, 120); // STOLp corium

    patch.WriteU32((void *)0x007E1D1C, 1000); // Psychotron corium
    patch.WriteU32((void *)0x007E1D20, 1000); // Psychotron corium
    patch.WriteU32((void *)0x007E1D24, 1000); // Psychotron corium

    patch.WriteU32((void *)0x007E1D28, 2000); // Plasmotron corium
    patch.WriteU32((void *)0x007E1D2C, 2000); // Plasmotron corium
    patch.WriteU32((void *)0x007E1D30, 2000); // Plasmotron corium

    // patch.WriteU32((void *)0x007E1D34, ); // Nuclear_Launcher corium

    // BO 
    patch.WriteU32((void *)0x007E1D40, 60); // Light_Laser corium
    patch.WriteU32((void *)0x007E1D44, 60); // Light_Laser corium
    patch.WriteU32((void *)0x007E1D48, 60); // Light_Laser corium

    patch.WriteU32((void *)0x007E1D70, 200); // Heavy_Laser corium
    patch.WriteU32((void *)0x007E1D74, 200); // Heavy_Laser corium
    patch.WriteU32((void *)0x007E1D78, 200); // Heavy_Laser corium

    patch.WriteU32((void *)0x007E1D4C, 260); // Magnetic_Mine_Launcher corium
    patch.WriteU32((void *)0x007E1D50, 260); // Magnetic_Mine_Launcher corium
    patch.WriteU32((void *)0x007E1D54, 260); // Magnetic_Mine_Launcher corium

    patch.WriteU32((void *)0x007E1D7C, 240); // EM_Launcher corium
    patch.WriteU32((void *)0x007E1D80, 240); // EM_Launcher corium
    patch.WriteU32((void *)0x007E1D84, 240); // EM_Launcher corium

    patch.WriteU32((void *)0x007E1D88, 800); // Protective_Shield gen corium
    patch.WriteU32((void *)0x007E1D8C, 800); // Protective_Shield gen corium
    patch.WriteU32((void *)0x007E1D90, 800); // Protective_Shield gen corium

    // SI
    //patch.WriteU32((void *)0x007E1EC0, 250); // Gas_Canon corium
    //patch.WriteU32((void *)0x007E1EC4, 250); // Gas_Canon corium
    //patch.WriteU32((void *)0x007E1EC8, 250); // Gas_Canon corium

    patch.WriteU32((void *)0x007E1ECC, 150); // DPT corium
    patch.WriteU32((void *)0x007E1ED0, 150); // DPT corium
    patch.WriteU32((void *)0x007E1ED4, 150); // DPT corium

    patch.WriteU32((void *)0x007E1EFC, 70); // Pulsar corium
    patch.WriteU32((void *)0x007E1F00, 70); // Pulsar corium
    patch.WriteU32((void *)0x007E1F04, 70); // Pulsar corium

    patch.WriteU32((void *)0x007E1EF0, 200); // Bio_Mine_Launcher corium
    patch.WriteU32((void *)0x007E1EF4, 200); // Bio_Mine_Launcher corium
    patch.WriteU32((void *)0x007E1EF8, 200); // Bio_Mine_Launcher corium

    patch.WriteU32((void *)0x007E1EE4, 230); // Jump_Mine_Launcher corium
    patch.WriteU32((void *)0x007E1EE8, 230); // Jump_Mine_Launcher corium
    patch.WriteU32((void *)0x007E1EEC, 230); // Jump_Mine_Launcher corium

    patch.WriteU32((void *)0x007E1EE0, 200); // Ion_Reflector corium

    //patch.WriteU32((void *)0x007E1DE4, 0);   // Core corium

    // METAL/SILICON
    //patch.WriteU32((void *)0x007E2568, 800);  // Depot_WS
    //patch.WriteU32((void *)0x007E256C, 800);  // Depot_BO
    //patch.WriteU32((void *)0x007E3390, 600);  // Depot_SI
    patch.WriteU32((void *)0x007E33C0, 600); // Silicon_Extractor silicon
    
    patch.WriteU32((void *)0x007E2508, 1200); // Docks_WS
    patch.WriteU32((void *)0x007E250C, 1200); // Docks_BO
    // patch.WriteU32((void *)0x007E3414, );    // Pulsar silicon

    patch.WriteU32((void *)0x007E33D8, 1200); // Gas_Canon silicon
    patch.WriteU32((void *)0x007E33E4, 900); // DPT silicon
    //patch.WriteU32((void *)0x007E33F0, 600);  // Ion_Reflector silicon
    patch.WriteU32((void *)0x007E3408, 700);  // Bio_Mine_Launcher silicon
    patch.WriteU32((void *)0x007E345C, 1400); // Parcher silicon
    // patch.WriteU32((void *)0x007E3360, 1400); // Protoplasm_Generator silicon

    patch.WriteU32((void *)0x007E2598, 1000); // STOLp metal
    patch.WriteU32((void *)0x007E259C, 1000); // STOLp metal
    patch.WriteU32((void *)0x007E25A0, 1000); // STOLp metal

    patch.WriteU32((void *)0x007E2670, 1200); // Plasma_Canon metal
    patch.WriteU32((void *)0x007E2674, 1200); // Plasma_Canon metal
    patch.WriteU32((void *)0x007E2678, 1200); // Plasma_Canon metal

    patch.WriteU32((void *)0x007E25BC, 900); // USG metal
    patch.WriteU32((void *)0x007E25C0, 900); // USG metal
    patch.WriteU32((void *)0x007E25C4, 900); // USG metal

    patch.WriteU32((void *)0x007E25EC, 400); // Light_Laser metal
    patch.WriteU32((void *)0x007E25F0, 400); // Light_Laser metal
    patch.WriteU32((void *)0x007E25F4, 400); // Light_Laser metal

    patch.WriteU32((void *)0x007E25F8, 1400); // Magnetic_Mine_Launcher metal
    patch.WriteU32((void *)0x007E25FC, 1400); // Magnetic_Mine_Launcher metal
    patch.WriteU32((void *)0x007E2600, 1400); // Magnetic_Mine_Launcher metal

    patch.WriteU32((void *)0x007E261C, 1000); // Heavy_Laser metal
    patch.WriteU32((void *)0x007E2620, 1000); // Heavy_Laser metal
    patch.WriteU32((void *)0x007E2624, 1000); // Heavy_Laser metal

    patch.WriteU32((void *)0x007E2628, 1200); // EM_Launcher metal
    patch.WriteU32((void *)0x007E262C, 1200); // EM_Launcher metal
    patch.WriteU32((void *)0x007E2630, 1200); // EM_Launcher metal

    patch.WriteU32((void *)0x007E25D4, 1000); // Plasmotron metal
    patch.WriteU32((void *)0x007E25D8, 1000); // Plasmotron metal
    patch.WriteU32((void *)0x007E25DC, 1000); // Plasmotron metal

    patch.WriteU32((void *)0x007E25E0, 2000); // Nuclear_Launcher metal
    patch.WriteU32((void *)0x007E25E4, 2000); // Nuclear_Launcher metal
    patch.WriteU32((void *)0x007E25E8, 2000); // Nuclear_Launcher metal

    patch.WriteU32((void *)0x007E264C, 2000); // Laser_Bomb_Launcher metal
    patch.WriteU32((void *)0x007E2650, 2000); // Laser_Bomb_Launcher metal
    patch.WriteU32((void *)0x007E2654, 2000); // Laser_Bomb_Launcher metal

    patch.WriteU32((void *)0x007E3468, 2000); // Vacuum_Bomb launcher silicon


    // SUBMARINES
    // METAL/SILICON
    patch.WriteU32((void *)0x007E07D0, 300); // Fighter metal
    patch.WriteU32((void *)0x007E07D4, 600); // Destroyer metal
    
    patch.WriteU32((void *)0x007E07A4, 450); // Hunter metal
    patch.WriteU32((void *)0x007E07A8, 1100); // Cruiser metal
    patch.WriteU32((void *)0x007E07BC, 300); // Transport WS metal
    patch.WriteU32((void *)0x007E07EC, 300); // Transport BO metal
    // patch.WriteU32((void *)0x007E07E4, 300); // Raider metal

    //patch.WriteU32((void *)0x007E0A44, 200);  // Trailer silicon
    //patch.WriteU32((void *)0x007E0A50, 600); // Energizer silicon
    patch.WriteU32((void *)0x007E0A68, 900);  // Psi_Zond silicon
    // patch.WriteU32((void *)0x007E0A64, 1000);  // Usurper silicon
    patch.WriteU32((void *)0x007E0A54, 250);  // Skat silicon
    // patch.WriteU32((void *)0x007E0A4C, 0);  // Paralizator silicon
    // patch.WriteU32((void *)0x007E0A5C, 0);  // Escort silicon
    patch.WriteU32((void *)0x007E0A58, 1200);  // Dreadnaught silicon
    // patch.WriteU32((void *)0x007E0A40, 0); // Module-prototype silicon

    // CORIUM
    patch.WriteU32((void *)0x007E05DC, 150); // Escort corium
    patch.WriteU32((void *)0x007E05D4, 40);  // Skat corium
    //patch.WriteU32((void *)0x007E0590, 40);  // Fighter corium
    patch.WriteU32((void *)0x007E0564, 70); // Hunter corium
    patch.WriteU32((void *)0x007E05E8, 400); // Psi_Zond corium
    patch.WriteU32((void *)0x007E059C, 180); // Invader corium
    patch.WriteU32((void *)0x007E05D0, 200); // Energizer corium
    //patch.WriteU32((void *)0x007E05B8, 220); // Avenger corium
    patch.WriteU32((void *)0x007E0594, 90);  // Destroyer corium
    patch.WriteU32((void *)0x007E0598, 360); // Heavy Cruiser corium
    patch.WriteU32((void *)0x007E05B4, 280); // Phantom corium
    patch.WriteU32((void *)0x007E05A4, 120); // Raider corium

    patch.WriteU32((void *)0x007E05E0, 330); // Bio_Assaulter corium (vanilla 200)
    patch.WriteU32((void *)0x007E05C8, 100); // Supplier corium (vanilla 0)
    patch.WriteU32((void *)0x007E0A60, 900); // Bio_Assaulter silicon (vanilla 700)

    // BUILDTIME
    patch.WriteU32((void *)0x007E04D0, 600); // Fighter buildtime
    patch.WriteU32((void *)0x007E0514, 500); // Skat buildtime
    patch.WriteU32((void *)0x007E04B4, 1500); // Marauder buildtime
    patch.WriteU32((void *)0x007E04E4, 1500); // Raider buildtime
    patch.WriteU32((void *)0x007E0528, 1500); // Usurper buildtime
    //patch.WriteU32((void *)0x007E04D4, ); // Destroyer buildtime

    // HP
    patch.WriteU32((void *)0x007DFBB0, 210); // Sentinel hp
    patch.WriteU32((void *)0x007DFBB4, 540); // Hunter hp
    patch.WriteU32((void *)0x007DFBE0, 300); // Fighter hp
    patch.WriteU32((void *)0x007DFBBC, 1600); // DC Bomber hp
    
    // patch.WriteU32((void *)0x007DFBE4, 300); // Destroyer hp
    //patch.WriteU32((void *)0x007DFBEC, 700);  // Invader hp
    patch.WriteU32((void *)0x007DFBF4, 1100); // Raider hp
    patch.WriteU32((void *)0x007DFC24, 200);  // Skat hp
    // patch.WriteU32((void *)0x007DFC2C, ); // Escort hp
    patch.WriteU32((void *)0x007DFC38, 600);  // Psi_Zond hp
    patch.WriteU32((void *)0x007DFC28, 1400); // Dreadnaught hp
    patch.WriteU32((void *)0x007DFC30, 760); // Bio_Assaulter hp
    
    // patch.WriteU32((void *)0x007DFBC4, 1400); // Marauder hp
    patch.WriteU32((void *)0x007DFC34, 1000); // Usurper hp
    // patch.WriteU32((void *)0x007DFBC0, 1000); // Minelayer hp
    // patch.WriteU32((void *)0x007DFBBF0, ); // Defender hp
    patch.WriteU32((void *)0x007DFC00, 600); // Cyberdolphin hp
    patch.WriteU32((void *)0x007DFBD0, 600); // Cyberworm hp
    patch.WriteU32((void *)0x007DFC14, 400); // Transport SI hp


    // WEAPONS

    // DAMAGE
    patch.WriteU32((void *)0x007E6490, 120); // Cruiser T1 damage
    patch.WriteU32((void *)0x007E6494, 160); // Cruiser T2 damage
    patch.WriteU32((void *)0x007E6498, 200); // Cruiser T3 damage
    patch.WriteU32((void *)0x007E649C, 230); // Cruiser T4 damage
    patch.WriteU32((void *)0x007E64A0, 270); // Cruiser T5 damage
    // patch.WriteU32((void *)0x007E6520, 70); // Sentinel dmg T2
    patch.WriteU32((void *)0x007E65E4, 600); // DC Bomb damage
    

    patch.WriteU32((void *)0x007E64A4, 10); // Cassete shell
    patch.WriteU32((void *)0x007E66FC, 10); // Ion cassete t1
    patch.WriteU32((void *)0x007E6700, 10); // Ion cassete t2
    patch.WriteU32((void *)0x007E6704, 10); // Ion cassete t3
    //patch.WriteU32((void *)0x007E6724, 20); // Ion cassete subshell t1
    //patch.WriteU32((void *)0x007E6728, 30); // Ion cassete subshell t2
    //patch.WriteU32((void *)0x007E672C, 40); // Ion cassete subshell t3

    // patch.WriteU32((void *)0x007E6648, );  // Gas Shell Launcher damage

    patch.WriteU32((void *)0x007E6580, 800); // Plasma damage

    //patch.WriteU32((void *)0x00489C36, 0x9064EB83); // Less priority for buildings
    //patch.WriteNops((void *)0x00489C3A, 2);
    
    return true;
}




















static bool BalancingTacticsTree(Patcher::SPatch &patch)
{
    // OTHER
    // patch.WriteU32((void *)0x007A8C98, ); // Invader reload


    //patch.WriteU32((void *)0x007E6544, 0); // Paralyze shell damage

    // Research make unavailable
    // patch.WriteByte((void *)0x00798FF6, ); // Mining upgrade ws
    // patch.WriteByte((void *)0x00799062, ); // Mining upgrade bo
    patch.WriteByte((void *)0x0079902B, 0); // Mining upgrade silicon si

    // patch.WriteByte((void *)0x0079902C, ); // Mining upgrade corium si
    patch.WriteByte((void *)0x00799070, 0); // WS Capture upg
    patch.WriteByte((void *)0x0079906C, 0); // BO Capture upg
    patch.WriteByte((void *)0x007BFBF8, 0); // SI Capture upg
    patch.WriteByte((void *)0x007BFBD6, 0); // SI TRPEVADE unavailable
    patch.WriteByte((void *)0x007BFBCF, 0); // SI IONARMOR unavailable
    patch.WriteByte((void *)0x007BFBB8, 0); // SI UPG NRG MINE unavailable

    //patch.WriteByte((void *)0x007BFB02, 0); // BO LIGHTLASRANGE unavailable
    //patch.WriteByte((void *)0x007BFB03, 0); // BO HEAVYLASRANGE unavailable
    patch.WriteByte((void *)0x007BFBE1, 0); // SI DPTRANGE unavailable


    // RESEARCH
    patch.WriteByte((void *)0x007BFC60, 0); // WS ARMR T2 dep
    patch.WriteByte((void *)0x007BFDAA, 0); // WS ARMR T3 dep2
    // patch.WriteByte((void *)0x007BFDAE, 2); // WS ARMR T3 dep2 lvl
    patch.WriteByte((void *)0x007BFDF0, 4);  // WS ARMR T4 dep
    patch.WriteByte((void *)0x007BFDF4, 2);  // WS ARMR T4 dep lvl
    patch.WriteByte((void *)0x007BFDF5, 0);  // WS ARMR T4 dep2
    patch.WriteByte((void *)0x007C002F, 5);  // WS CYBER dep
    patch.WriteByte((void *)0x007C0033, 2);  // WS CYBER dep lvl
    patch.WriteByte((void *)0x007C0034, 0);  // WS CYBER dep2
    patch.WriteByte((void *)0x007BFFE4, 22); // WS SHRKCNTRL dep
    patch.WriteByte((void *)0x007BFD8C, 15); // WS PSIFIELD dep
    patch.WriteByte((void *)0x007BFE22, 29); // WS CORIUM276 dep
    patch.WriteByte((void *)0x007BFE27, 21); // WS CORIUM276 dep2
    patch.WriteByte((void *)0x007BFE2B, 1); // WS CORIUM276 dep2 lvl
    patch.WriteByte((void *)0x007BFDBE, 8); // WS TERMINATOR dep
    patch.WriteByte((void *)0x007BFDC3, 31); // WS TERMINATOR dep2
    patch.WriteByte((void *)0x007BFDC7, 1);  // WS TERMINATOR dep2 lvl
    patch.WriteByte((void *)0x007BFD5A, 21); // WS UPG USG dep
    patch.WriteByte((void *)0x007BFE09, 11); // WS PLASMACANN dep
    patch.WriteByte((void *)0x007BFE0E, 0);  // WS PLASMACANN dep2
    patch.WriteByte((void *)0x007BFE3B, 25); // WS NUKE dep
    patch.WriteByte((void *)0x007BFDD7, 4);  // WS LSRSCRN dep
    patch.WriteByte((void *)0x007BFDDB, 3);  // WS LSRSCRN dep lvl
    patch.WriteByte((void *)0x007BFCAB, 0);  // WS DMG T2 dep
    patch.WriteByte((void *)0x007BFC79, 0);  // WS DPTHMINE dep
    patch.WriteByte((void *)0x007BFD73, 15); // WS SENT DMG dep
    patch.WriteByte((void *)0x007C00AC, 5);  // WS SPEED T3 dep
    // patch.WriteByte((void *)0x007C0048, 11); // WS SPEED T4 dep
    patch.WriteByte((void *)0x007C00F7, 0);  // WS UPGMINE dep
    patch.WriteByte((void *)0x007C00DE, 30);  // WS TORPPROD dep
    patch.WriteByte((void *)0x007C00E2, 1);  // WS TORPPROD dep lvl
    patch.WriteByte((void *)0x007C0093, 5);  // WS MOBILEPLATF dep
    //patch.WriteByte((void *)0x007BFC2E, 0);  // WS MEDTORP dep
    patch.WriteByte((void *)0x007BFD28, 1);  // WS HFCANNSPEED dep
    patch.WriteByte((void *)0x007BFC79, 0);  // WS MINELAYER dep
    patch.WriteByte((void *)0x007BFE6D, 0);  // WS FINDTELE dep
    patch.WriteByte((void *)0x007BFE54, 64); // WS TELEPORT dep
    // patch.WriteByte((void *)0x007BFF99, ); // WS UPGHACK dep
    patch.WriteByte((void *)0x007BFF1C, 63); // WS ANTINUKE dep
    // patch.WriteByte((void *)0x007BFF21, 0);  // WS ANTINUKE dep2
    patch.WriteByte((void *)0x007BFEEA, 2);  // WS DISPSCREEN dep
    patch.WriteByte((void *)0x007BFF03, 17); // WS LIBERATOR dep
    patch.WriteByte((void *)0x007C007A, 0);  // WS REPPLATF dep
    patch.WriteByte((void *)0x007BFFFD, 61); // WS UPGLOCATOR dep
    patch.WriteByte((void *)0x007C00C5, 3);  // WS REPUPG dep
    patch.WriteByte((void *)0x007C00C9, 1);  // WS REPUPG dep lvl
    patch.WriteByte((void *)0x007BFFCB, 13); // WS DEFHACK dep

    patch.WriteU32((void *)0x007E5868, 6000); // WS DEFHACK time
    patch.WriteU32((void *)0x007E5598, 6000); // WS LIBERATOR time
    patch.WriteU32((void *)0x007E54CC, 6000); // WS SPD T3 time
    patch.WriteU32((void *)0x007E54D0, 6000); // WS SPD T4 time
    patch.WriteU32((void *)0x007E55C8, 7500); // WS PSIFIELD time
    patch.WriteU32((void *)0x007E5608, 6000); // WS NUKE time
    patch.WriteU32((void *)0x007E5618, 7500); // WS CORIUM276 time
    patch.WriteU32((void *)0x007E5528, 7500); // WS UPG HFCANN time
    patch.WriteU32((void *)0x007E5638, 4500); // WS UPG USG time
    patch.WriteU32((void *)0x007E55F8, 9000); // WS TERMINATOR time
    patch.WriteU32((void *)0x007E5668, 7500); // WS PLASMACANN time
    //patch.WriteU32((void *)0x007E5898, 9000); // WS ANTINUKE time (vanilla 6 min)
    patch.WriteU32((void *)0x007E5578, 3000); // WS TURRETS FLOAT time
    patch.WriteU32((void *)0x007E5598, 4500); // WS LIBERATOR time

    patch.WriteU32((void *)0x007E54B8, 4500); // WS ARMOR T2 time
    patch.WriteU32((void *)0x007E54BC, 7500); // WS ARMOR T3 time
    patch.WriteU32((void *)0x007E54C0, 9000); // WS ARMOR T4 time

    patch.WriteU32((void *)0x007E54D8, 4500); // WS DMG T1 time
    patch.WriteU32((void *)0x007E54DC, 6000); // WS DMG T2 time
    patch.WriteU32((void *)0x007E5878, 6000); // WS TELEFIND time
    patch.WriteU32((void *)0x007E5838, 7500); // WS LASMINEFIND time
    patch.WriteU32((void *)0x007E5558, 3000); // WS MARAUDER time
    patch.WriteU32((void *)0x007E5628, 9000); // WS LSRSCRN time
    patch.WriteU32((void *)0x007E5658, 7500); // WS MINESPEED time
    patch.WriteU32((void *)0x007E54F8, 4500); // WS CRUISER time
    patch.WriteU32((void *)0x007E5678, 4500); // WS UPGREPAIR time
    //patch.WriteU32((void *)0x007E55A8, 6000); // WS TELEPORT time
    patch.WriteU32((void *)0x007E5688, 4500); // WS UPG TELEPORT time
    patch.WriteU32((void *)0x007E5828, 4500); // WS TELESHIELD time
    //patch.WriteU32((void *)0x007E5648, 3000); // WS UPG LOCATOR time
    patch.WriteU32((void *)0x007E5DE8, 6000); // WS SENT DMG time

    // patch.WriteU32((void *)0x007C028B, );   // BO PARALYZE dep
    // patch.WriteU32((void *)0x007C028F, );   // BO PARALYZE dep lvl
    patch.WriteU32((void *)0x007C0290, 54);   // BO PARALYZE dep2
    patch.WriteU32((void *)0x007C0294, 1);   // BO PARALYZE dep2 lvl
    patch.WriteByte((void *)0x007C04CA, 39);  // BO PHANTOM dep
    patch.WriteByte((void *)0x007C02A4, 43);   // BO UPGEM dep
    //patch.WriteByte((void *)0x007C02A8, 0);   // BO UPGEM dep lvl
    patch.WriteByte((void *)0x007C02A9, 0);  // BO UPGEM dep2
    patch.WriteByte((void *)0x007C0515, 132); // BO DEFHACK dep
    patch.WriteByte((void *)0x007C04E3, 132); // BO UPGRAIDER dep
    patch.WriteByte((void *)0x007C068C, 128); // BO UPG REPSPD dep
    patch.WriteByte((void *)0x007C01DC, 34);  // BO UPG DESTR dep
    patch.WriteByte((void *)0x007C01E1, 131); // BO UPG DESTR dep2
    patch.WriteByte((void *)0x007C01E5, 3);   // BO UPG DESTR dep2 lvl
    patch.WriteByte((void *)0x007C0628, 130); // BO SPEED T3 dep
    // patch.WriteByte((void *)0x007C06A5, ); // BO SPEED T4 dep
    patch.WriteByte((void *)0x007C04B1, 36); // BO SCOUT dep
    patch.WriteByte((void *)0x007C0146, 0);  // BO ARMOR T2 dep
    // patch.WriteByte((void *)0x007C014A, );  // BO ARMOR T2 dep lvl
    patch.WriteByte((void *)0x007C0213, 0);   // BO ARMOR T3 dep2
    patch.WriteByte((void *)0x007C022C, 0);   // BO ARMOR T4 dep2
    patch.WriteByte((void *)0x007C015F, 0);   // BO DMG T2 dep
    patch.WriteByte((void *)0x007C0592, 129); // BO USGSCREEN dep
    patch.WriteByte((void *)0x007C0596, 3);   // BO USGSCREEN dep lvl
    patch.WriteByte((void *)0x007C0597, 0);   // BO USGSCREEN dep2
    patch.WriteByte((void *)0x007C065A, 138); // BO TORPPROD dep
    patch.WriteByte((void *)0x007C065E, 1); // BO TORPPROD dep lvl
    patch.WriteByte((void *)0x007C0646, 0);   // BO CYBER dep
    patch.WriteByte((void *)0x007C060F, 130); // BO MOBILEPLATF dep
    patch.WriteByte((void *)0x007C025E, 0);   // BO Magnetic_Mine_LauncherAUNCHER dep2
    patch.WriteByte((void *)0x007C0272, 40);  // BO EMTORP dep
    patch.WriteByte((void *)0x007C0560, 137); // BO LASBOMB dep
    patch.WriteByte((void *)0x007C0565, 50);   // BO LASBOMB dep2
    patch.WriteByte((void *)0x007C0673, 0);   // BO UPG MINESPD dep
    patch.WriteByte((void *)0x007C033A, 51);  // BO LIGHTLASSPD dep
    patch.WriteByte((void *)0x007C02EF, 51);  // BO RUBY dep
    patch.WriteByte((void *)0x007C036C, 55);  // BO HEAVYLASRATE dep
    patch.WriteByte((void *)0x007C0353, 57);  // BO LASRATE dep
    //patch.WriteByte((void *)0x007C0357, 1);   // BO LASRATE dep lvl
    //patch.WriteByte((void *)0x007C0358, 57);  // BO LASRATE dep2
    //patch.WriteByte((void *)0x007C035C, 1);   // BO LASRATE dep2 lvl
    patch.WriteByte((void *)0x007C0385, 35);  // BO RECHARGEST dep
    patch.WriteByte((void *)0x007C0579, 42);  // BO SHIELDGEN dep
    patch.WriteByte((void *)0x007C05AB, 48);  // BO SHIELDGEN dep
    // patch.WriteByte((void *)0x007C0498, ); // BO UPGHACK dep
    patch.WriteByte((void *)0x007C052E, 127); // BO LOCSHIELD dep
    patch.WriteByte((void *)0x007C0466, 134); // BO STEALTH dep
    patch.WriteByte((void *)0x007C03B7, 0);   // BO TELEPORT dep
    patch.WriteByte((void *)0x007C0420, 0);   // BO UPGTELE dep2
    patch.WriteByte((void *)0x007C03D5, 0);   // BO FINDTELE dep2
    patch.WriteByte((void *)0x007C05F6, 0);   // BO TELEPORT dep
    patch.WriteByte((void *)0x007C0484, 0);   // BO RAIDER dep2
    patch.WriteByte((void *)0x007C0489, 0);   // BO RAIDER dep2
    patch.WriteU32((void *)0x007C0547, 141);  // BO UPGLOCATOR dep
    //patch.WriteU32((void *)0x007C05C4, 142);  // BO ANTISMP dep
    patch.WriteU32((void *)0x007C05C9, 142);  // BO ANTISMP dep2
    patch.WriteU32((void *)0x007C05CD, 1);    // BO ANTISMP dep2 lvl
    patch.WriteU32((void *)0x007C01F5, 0);    // BO DEFENDER dep
    patch.WriteU32((void *)0x007C0240, 34);   // BO CASSETE dep
    patch.WriteU32((void *)0x007C01C7, 3);    // BO TORPSPEED dep lvl
    patch.WriteU32((void *)0x007C01AA, 150);  // BO DMG T4 dep
    patch.WriteU32((void *)0x007C01AE, 1);    // BO DMG T4 dep lvl
    patch.WriteU32((void *)0x007C02D6, 56);   // BO LIGHTLASRANGE dep 
    

    patch.WriteU32((void *)0x007E5D08, 4500); // BO UPGLOCATOR time
    patch.WriteU32((void *)0x007E5C88, 6000); // BO ARMOR T2 time
    patch.WriteU32((void *)0x007E5C8C, 7500); // BO ARMOR T3 time
    patch.WriteU32((void *)0x007E5C90, 9000); // BO ARMOR T4 time
    patch.WriteU32((void *)0x007E56A8, 9000); // BO HEAVYCRUISER time
    // patch.WriteU32((void *)0x007E58A8, 9000); // BO ANTISMP time
    patch.WriteU32((void *)0x007E5748, 6000); // BO USGDEF time
    patch.WriteU32((void *)0x007E5D18, 7500); // BO UPGMINE time
    patch.WriteU32((void *)0x007E5C68, 4500); // BO RADAR time
    patch.WriteU32((void *)0x007E5CB8, 4500); // BO HACK time
    patch.WriteU32((void *)0x007E5D48, 3000); // BO UPGHACK time
    patch.WriteU32((void *)0x007E5D58, 6000); // BO DEFHACK time
    patch.WriteU32((void *)0x007E5D98, 7500); // BO PHANTOMUPG time
    patch.WriteU32((void *)0x007E56D8, 4500); // BO HEAVYLAS time
    patch.WriteU32((void *)0x007E57E8, 6000); // BO HEAVYLASRANGE time
    patch.WriteU32((void *)0x007E5818, 6000); // BO LASRATE time
    patch.WriteU32((void *)0x007E57B8, 3000); // BO RAIDER time
    patch.WriteU32((void *)0x007E5798, 6000); // BO FORCEFIELD time
    patch.WriteU32((void *)0x007E5888, 7500); // BO MINEFIND time
    patch.WriteU32((void *)0x007E5D28, 4500); // BO UPGREPAIR time
    patch.WriteU32((void *)0x007E5D38, 4500); // BO TELECHARGE time
    patch.WriteU32((void *)0x007E5698, 4500); // BO DESTROYER time
    patch.WriteU32((void *)0x007E57C8, 6000); // BO CYBER time
    patch.WriteU32((void *)0x007E5C98, 2500); // BO SPEED T1 time
    patch.WriteU32((void *)0x007E5C98, 2500); // BO SPEED T1 time
    patch.WriteU32((void *)0x007E5C9C, 6000); // BO SPEED T2 time
    patch.WriteU32((void *)0x007E5CA0, 7000); // BO SPEED T3 time
    patch.WriteU32((void *)0x007E56F8, 6000); // BO CASSETTE time
    patch.WriteU32((void *)0x007E5DA8, 6000); // BO UPG EMTORP time
    patch.WriteU32((void *)0x007E5788, 9000); // BO LASBOMB time
    patch.WriteU32((void *)0x007E57D8, 4500); // BO LIGHTLASRANGE time
    patch.WriteU32((void *)0x007E5CC8, 3000); // BO TURRETS FLOAT time
    //patch.WriteU32((void *)0x007E5708, 4500); // BO Magnetic_Mine_Launcher time
    patch.WriteU32((void *)0x007E5DD8, 4500); // BO TORPSPEED time
    patch.WriteU32((void *)0x007E57F8, 4500); // BO AVENGER time
    

    // patch.WriteByte((void *)0x007C0A2F, ); // SI ARMOR T3 dep
    // patch.WriteByte((void *)0x007C0ADE, ); // SI ARMOR T4 dep
    // patch.WriteByte((void *)0x007C0B10, ); // SI IONARMOR T2 dep
    // patch.WriteByte((void *)0x007C0B14, ); // SI IONARMOR T2 dep lvl
    // patch.WriteByte((void *)0x007C0B29, ); // SI IONARMOR T3 dep
    // patch.WriteByte((void *)0x007C0B2D, ); // SI IONARMOR T3 dep lvl
    // patch.WriteByte((void *)0x007C0B2E, ); // SI IONARMOR T3 dep 2
    // patch.WriteByte((void *)0x007C0B32, ); // SI IONARMOR T3 dep 2 lvl
    // patch.WriteByte((void *)0x007C0B2E, ); // SI IONARMOR T3 dep 2
    // patch.WriteByte((void *)0x007C0A7F, ); // SI LASDEFARM dep2
    // patch.WriteByte((void *)0x007C0A83, ); // SI LASDEFARM dep2 lvl

    patch.WriteByte((void *)0x007C08A3, 2);   // SI TRPEVADE dep lvl
    patch.WriteByte((void *)0x007C08A4, 78);  // SI TRPEVADE dep2
    patch.WriteByte((void *)0x007C08A8, 3);   // SI TRPEVADE dep2 lvl
    patch.WriteByte((void *)0x007C08B8, 109); // SI SPEED T3 dep
    // patch.WriteByte((void *)0x007C08BC, ); // SI SPEED T3 dep lvl
    patch.WriteByte((void *)0x007C0967, 109); // SI SPEED T4 dep
    // patch.WriteByte((void *)0x007C096B, ); // SI SPEED T4 dep lvl
    patch.WriteByte((void *)0x007C096C, 0);   // SI SPEED T4 dep2
    patch.WriteByte((void *)0x007C0970, 0);   // SI SPEED T4 dep2 lvl
    patch.WriteByte((void *)0x007C0D4F, 122); // SI UPGBHESHELLS dep
    patch.WriteByte((void *)0x007C0D53, 1); // SI UPGBHESHELLS dep lvl
    patch.WriteByte((void *)0x007C0903, 81);  // SI NRG T3 dep
    // patch.WriteByte((void *)0x007C0908, );  // SI NRG T3 dep2
    // patch.WriteByte((void *)0x007C090C, );  // SI NRG T3 dep2 lvl
    //patch.WriteByte((void *)0x007C094E, 78); // SI NRG T4 dep
    //patch.WriteByte((void *)0x007C0952, 2);  // SI NRG T4 dep lvl
    patch.WriteByte((void *)0x007C09CB, 84); // SI SHELLPROD dep
    //patch.WriteByte((void *)0x007C09CF, 2); // SI SHELLPROD dep lvl
    // patch.WriteByte((void *)0x007C0D9A, 2);    // SI NRGSHLDNEUTR dep
    patch.WriteByte((void *)0x007C0D9E, 1); // SI NRGSHLDNEUTR dep lvl
    patch.WriteByte((void *)0x007C091C, 78);  // SI NRGTRANSF dep
    patch.WriteByte((void *)0x007C0920, 1);   // SI NRGTRANSF dep lvl
    patch.WriteByte((void *)0x007C0A93, 119); // SI ORBITLAS dep
    patch.WriteByte((void *)0x007C0A98, 0);   // SI ORBITLAS dep2
    patch.WriteByte((void *)0x007C0999, 78);  // SI UPGNRGMINE dep
    patch.WriteByte((void *)0x007C099D, 2);   // SI UPGNRGMINE dep lvl
    patch.WriteByte((void *)0x007C0AAC, 71);  // SI ANTISMP dep
    //patch.WriteByte((void *)0x007C0AB1, 119);  // SI ANTISMP dep2
    //patch.WriteByte((void *)0x007C0AB5, 1);   // SI ANTISMP dep2 lvl
    // patch.WriteByte((void *)0x007C0AB0, 2);  // SI ANTISMP dep lvl
    // patch.WriteByte((void *)0x007C0B42, ); // SI PSISHIELD dep
    // patch.WriteByte((void *)0x007C0B46, ); // SI PSISHIELD dep lvl
    patch.WriteByte((void *)0x007C0A48, 101); // SI IONARMR dep
    patch.WriteByte((void *)0x007C0A4C, 3); // SI IONARMR dep lvl
    patch.WriteByte((void *)0x007C0B2E, 0); // SI IONARMR T4 dep2
    patch.WriteByte((void *)0x007C0B32, 0); // SI IONARMR T4 dep2 lvl
    // patch.WriteByte((void *)0x007C0C0A, 0);   // SI DMG T2 dep
    // patch.WriteByte((void *)0x007C0C0E, 0);   // SI DMG T2 dep lvl
    patch.WriteByte((void *)0x007C0C23, 124); // SI DMG T3 dep
    // patch.WriteByte((void *)0x007C0C27, ); // SI DMG T3 dep lvl 
    patch.WriteByte((void *)0x007C09B2, 78); // SI MOLECULAR dep
    patch.WriteByte((void *)0x007C09B6, 3);  // SI MOLECULAR dep lvl
    patch.WriteByte((void *)0x007C09B7, 0);  // SI MOLECULAR dep2
    patch.WriteByte((void *)0x007C09BB, 0);  // SI MOLECULAR dep2 lvl
    patch.WriteByte((void *)0x007C09FD, 0); // SI UPGCORMINE dep
    // patch.WriteByte((void *)0x007C0AC5, ); // SI VACBOMB dep
    patch.WriteByte((void *)0x007C0ACA, 107);   // SI VACBOMB dep2
    patch.WriteByte((void *)0x007C0ACE, 1);   // SI VACBOMB dep2 lvl
    patch.WriteByte((void *)0x007C0A7A, 101); // SI LASABSORB dep
    patch.WriteByte((void *)0x007C0A7E, 2);  // SI LASABSORB dep lvl
    patch.WriteByte((void *)0x007C0A61, 101); // SI REGEN dep
    patch.WriteByte((void *)0x007C0A65, 1);  // SI REGEN dep lvl
    patch.WriteByte((void *)0x007C0A66, 0);  // SI REGEN dep2
    patch.WriteByte((void *)0x007C0A6A, 0);  // SI REGEN dep2 lvl
    patch.WriteByte((void *)0x007C086D, 69); // SI USURPER dep
    patch.WriteByte((void *)0x007C0872, 0); // SI USURPER dep2
    patch.WriteByte((void *)0x007C07D7, 73); // SI RESIDENT dep
    patch.WriteByte((void *)0x007C07DC, 0);  // SI RESIDENT dep2
    // patch.WriteByte((void *)0x007C07E0, );  // SI RESIDENT dep2 lvl
    // patch.WriteByte((void *)0x007C07BE, ); // SI BIOLOCSCREEN dep
    patch.WriteByte((void *)0x007C07A5, 68);  // SI BIOLOCSCAN dep
    patch.WriteByte((void *)0x007C0809, 70);  // SI INVISFIND dep
    patch.WriteByte((void *)0x007C06DD, 96);  // SI TELELOC dep
    patch.WriteByte((void *)0x007C06E1, 1);   // SI TELELOC dep lvl
    patch.WriteByte((void *)0x007C06F6, 0);   // SI TELEPORTAL dep
    patch.WriteByte((void *)0x007C06FA, 0);   // SI TELEPORTAL dep lvl
    patch.WriteByte((void *)0x007C0728, 95);  // SI TELEPORTALSEC dep
    patch.WriteByte((void *)0x007C070F, 98);  // SI QUANTUMPAR dep
    patch.WriteByte((void *)0x007C0714, 77);  // SI QUANTUMPAR dep2
    patch.WriteByte((void *)0x007C0718, 1);   // SI QUANTUMPAR dep2 lvl
    patch.WriteByte((void *)0x007C0935, 108); // SI RECYCLE dep
    patch.WriteByte((void *)0x007C07F0, 96);  // SI TELEFIND dep
    patch.WriteByte((void *)0x007C0980, 123); // SI IONFIELD dep
    patch.WriteByte((void *)0x007C0985, 0);   // SI IONFIELD dep2
    // patch.WriteByte((void *)0x007C0989, );   // SI IONFIELD dep2 lvl
    patch.WriteByte((void *)0x007C0D09, 0);   // SI PARALYZE dep
    patch.WriteByte((void *)0x007C0D0D, 0);   // SI PARALYZE dep lvl
    patch.WriteByte((void *)0x007C078C, 69);  // SI DEFHACK dep
    patch.WriteByte((void *)0x007C0773, 114); // SI DEFHACK dep
    patch.WriteByte((void *)0x007C0B42, 106); // SI ANTIPSI dep
    patch.WriteByte((void *)0x007C0B46, 1);   // SI ANTIPSI dep lvl
    patch.WriteByte((void *)0x007C0BF1, 85);  // SI UPGPULSAR dep
    patch.WriteByte((void *)0x007C0B8D, 90);  // SI DPT dep
    patch.WriteByte((void *)0x007C0BA6, 90);  // SI GASLAUNCHER dep
    patch.WriteByte((void *)0x007C0C55, 89);  // SI PARCHER dep
    patch.WriteU32((void *)0x007C0D9E, 1);    // SI NEUTRSHIELD dep lvl
    
    

    //patch.WriteU32((void *)0x007E59D8, 6000);  // SI GASSHLLNCHR time
    //patch.WriteU32((void *)0x007E5A48, 7500);  // SI UPG GASSHLLNCHR time
    patch.WriteU32((void *)0x007E5B50, 10500); // SI SPEED T4 time
    patch.WriteU32((void *)0x007E5B48, 4500); // SI SPEED T2 time
    patch.WriteU32((void *)0x007E58E8, 4500);  // SI DEFHACK time
    patch.WriteU32((void *)0x007E5AA8, 10500); // SI ANTINUKE time
    patch.WriteU32((void *)0x007E58F8, 4500);  // SI DISPSCREEN time
    patch.WriteU32((void *)0x007E5918, 5250);  // SI INVISFIND time
    patch.WriteU32((void *)0x007E5B98, 3000);  // SI USURPER time
    patch.WriteU32((void *)0x007E5A38, 4500);  // SI IONREFLECTOR time
    patch.WriteU32((void *)0x007E5C28, 6000);  // SI UPGIONREFLECTOR time
    patch.WriteU32((void *)0x007E59E8, 6000);  // SI SOLITON time
    patch.WriteU32((void *)0x007E5C08, 3750);  // SI UPGDPT time
    patch.WriteU32((void *)0x007E5A78, 6000);  // SI PORTAL time
    patch.WriteU32((void *)0x007E5A98, 6000);  // SI PORTALCODE time
    patch.WriteU32((void *)0x007E5AB8, 6000);  // SI QUANTUMPAR time
    //patch.WriteU32((void *)0x007E5BE8, 3000);  // SI RESIDENT time
    patch.WriteU32((void *)0x007E59B8, 7500);  // SI CORMINESPEED time
    patch.WriteU32((void *)0x007E5BB8, 4500);  // SI ACOUSTICMINES time
    patch.WriteU32((void *)0x007E5BA8, 6000);  // SI BIOASSAULTER time
    patch.WriteU32((void *)0x007E5BD8, 7500);  // SI UPGBIO time
    // patch.WriteU32((void *)0x007E5C18, 6000); // SI DMG T2 time
    patch.WriteU32((void *)0x007E5C1C, 6000); // SI DMG T3 time
    patch.WriteU32((void *)0x007E5C18, 6000); // SI RECYCLE time
    patch.WriteU32((void *)0x007E5960, 6000); // SI NRG T4 time
    patch.WriteU32((void *)0x007E5B78, 5250); // SI DREADNAUGHT time
    patch.WriteU32((void *)0x007E5978, 5250); // SI UPGACCUM time
    patch.WriteU32((void *)0x007E5AF8, 4500); // SI LASABSORB time
    patch.WriteU32((void *)0x007E5B88, 7500); // SI PARALYZE time
    patch.WriteU32((void *)0x007E5B4C, 4500); // SI SPEED T3 time
    patch.WriteU32((void *)0x007E5AC8, 6000); // SI ARMOR T2 time
    //patch.WriteU32((void *)0x007E5ACC, 10500); // SI ARMOR T3 time
    //patch.WriteU32((void *)0x007E5AD0, 15000); // SI ARMOR T4 time
    patch.WriteU32((void *)0x007E5A88, 6750); // SI ORBITLAS time
    patch.WriteU32((void *)0x007E5BC8, 9000); // SI VACBOMB time
    patch.WriteU32((void *)0x007E5A18, 6000); // SI PULSARUPG time
    patch.WriteU32((void *)0x007E5A48, 7500); // SI PARCHER time
    patch.WriteU32((void *)0x007E5C38, 6000); // SI UPG DREDNAUGHT time
    patch.WriteU32((void *)0x007E58D8, 3000); // SI BIOLOCSCAN time
    patch.WriteU32((void *)0x007E5AE8, 6000); // SI IONARMOR time
    

    // SPEED Upgrade
    patch.WriteByte((void *)0x0045F737, 3); // Plus total at T2
    patch.WriteByte((void *)0x0045F733, 6); // Plus total at T3
    patch.WriteByte((void *)0x0045F72F, 9); // Plus total at T4

    // BUILDINGS // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

    // HP
    patch.WriteU32((void *)0x007E41D0, GetPrivateProfileInt(L"Metal_Mine_Humans", L"HP", 600, ini_file)); // WS Metal
    patch.WriteU32((void *)0x007E43DC, GetPrivateProfileInt(L"Silicon_Extractor", L"HP", 600, ini_file));  // Silicon_Extractor HP (+100) 700
    patch.WriteU32((void *)0x007E417C, GetPrivateProfileInt(L"Dockyard_WS", L"HP", 2000, ini_file)); // Dockyard_WS HP3000
    patch.WriteU32((void *)0x007E4180, GetPrivateProfileInt(L"Dockyard_BO", L"HP", 2000, ini_file)); // Dockyard_BO HP 3000
    patch.WriteU32((void *)0x007E4188, GetPrivateProfileInt(L"Docks_WS", L"HP", 123, ini_file)); // Docks_WS HP 2250
    patch.WriteU32((void *)0x007E418C, GetPrivateProfileInt(L"Docks_BO", L"HP", 123, ini_file)); // Docks_BO HP 2250
    patch.WriteU32((void *)0x007E4194, GetPrivateProfileInt(L"Arsenal_WS", L"HP", 123, ini_file)); // WS Arsenal HP 1800
    patch.WriteU32((void *)0x007E4198, GetPrivateProfileInt(L"Arsenal_BO", L"HP", 123, ini_file)); // BO Arsenal HP 1800
    patch.WriteU32((void *)0x007E41A0, GetPrivateProfileInt(L"Lab_WS", L"HP", 123, ini_file)); // Lab_WS HP 1500
    patch.WriteU32((void *)0x007E41A4, GetPrivateProfileInt(L"Lab_BO", L"HP", 123, ini_file)); // Lab_BO HP 1500
    patch.WriteU32((void *)0x007E4310, GetPrivateProfileInt(L"Core", L"HP", 123, ini_file)); // SI Core HP 2500
    patch.WriteU32((void *)0x007E4370, GetPrivateProfileInt(L"Arsenal_SI", L"HP", 123, ini_file)); // SI Arsenal HP 1500
    patch.WriteU32((void *)0x007E437C, GetPrivateProfileInt(L"Protoplasm_Generator", L"HP", 123, ini_file)); // SI Protoplasm_Generator HP 2250

    patch.WriteU32((void *)0x007E420C, GetPrivateProfileInt(L"HF_Canon", L"HP", 123, ini_file)); // HF_Canon HP 1200
    patch.WriteU32((void *)0x007E4210, GetPrivateProfileInt(L"HF_Canon", L"HP", 123, ini_file)); // HF_Canon HP 1200
    patch.WriteU32((void *)0x007E4214, GetPrivateProfileInt(L"HF_Canon", L"HP", 123, ini_file)); // HF_Canon HP
    patch.WriteU32((void *)0x007E4218, GetPrivateProfileInt(L"STOLp", L"HP", 123, ini_file)); // STOLp HP 1600
    patch.WriteU32((void *)0x007E421C, GetPrivateProfileInt(L"STOLp", L"HP", 123, ini_file)); // STOLp HP
    patch.WriteU32((void *)0x007E4220, GetPrivateProfileInt(L"STOLp", L"HP", 123, ini_file)); // STOLp HP
    patch.WriteU32((void *)0x007E42F0, GetPrivateProfileInt(L"Plasma_Canon", L"HP", 123, ini_file)); // Plasma_Canon HP 1500
    patch.WriteU32((void *)0x007E42F4, GetPrivateProfileInt(L"Plasma_Canon", L"HP", 123, ini_file)); // Plasma_Canon HP

    patch.WriteU32((void *)0x007E426C, GetPrivateProfileInt(L"Light_Laser", L"HP", 123, ini_file)); // Light_Laser HP 1000
    patch.WriteU32((void *)0x007E4270, GetPrivateProfileInt(L"Light_Laser", L"HP", 123, ini_file)); // Light_Laser HP
    patch.WriteU32((void *)0x007E4274, GetPrivateProfileInt(L"Light_Laser", L"HP", 123, ini_file)); // Light_Laser HP
    patch.WriteU32((void *)0x007E429C, GetPrivateProfileInt(L"Heavy_Laser", L"HP", 123, ini_file)); // Heavy_Laser HP 1300
    patch.WriteU32((void *)0x007E42A0, GetPrivateProfileInt(L"Heavy_Laser", L"HP", 123, ini_file)); // Heavy_Laser HP
    patch.WriteU32((void *)0x007E42A4, GetPrivateProfileInt(L"Heavy_Laser", L"HP", 123, ini_file)); // Heavy_Laser HP

    patch.WriteU32((void *)0x007E4428, GetPrivateProfileInt(L"Pulsar", L"HP", 123, ini_file)); // Pulsar HP 1000
    patch.WriteU32((void *)0x007E442C, GetPrivateProfileInt(L"Pulsar", L"HP", 123, ini_file)); // Pulsar HP 
    patch.WriteU32((void *)0x007E4430, GetPrivateProfileInt(L"Pulsar", L"HP", 123, ini_file)); // Pulsar HP
    patch.WriteU32((void *)0x007E43EC, GetPrivateProfileInt(L"Gas_Canon", L"HP", 123, ini_file)); // Gas_Canon HP (vanilla 1100) 1200
    patch.WriteU32((void *)0x007E43F0, GetPrivateProfileInt(L"Gas_Canon", L"HP", 123, ini_file)); // Gas_Canon HP (vanilla 1100)
    patch.WriteU32((void *)0x007E43F4, GetPrivateProfileInt(L"Gas_Canon", L"HP", 123, ini_file)); // Gas_Canon HP (vanilla 1100)
    patch.WriteU32((void *)0x007E441C, GetPrivateProfileInt(L"Bio_Mine_Launcher", L"HP", 123, ini_file)); // Bio_Mine_Launcher HP 900
    patch.WriteU32((void *)0x007E4420, GetPrivateProfileInt(L"Bio_Mine_Launcher", L"HP", 123, ini_file)); // Bio_Mine_Launcher HP 
    patch.WriteU32((void *)0x007E4424, GetPrivateProfileInt(L"Bio_Mine_Launcher", L"HP", 123, ini_file)); // Bio_Mine_Launcher HP
    patch.WriteU32((void *)0x007E43E0, GetPrivateProfileInt(L"Soliton", L"HP", 123, ini_file));  // Soliton oscilator HP 700
    patch.WriteU32((void *)0x007E43E4, GetPrivateProfileInt(L"Soliton", L"HP", 123, ini_file));  // Soliton oscilator HP
    patch.WriteU32((void *)0x007E43E8, GetPrivateProfileInt(L"Soliton", L"HP", 123, ini_file));  // Soliton oscilator HP

    // Corium
    // WS
    patch.WriteU32((void *)0x007E1CE0, GetPrivateProfileInt(L"HF_Canon", L"Corium", 123, ini_file)); // HF_Canon corium 8
    patch.WriteU32((void *)0x007E1CE4, GetPrivateProfileInt(L"HF_Canon", L"Corium", 123, ini_file)); // HF_Canon corium
    patch.WriteU32((void *)0x007E1CE8, GetPrivateProfileInt(L"HF_Canon", L"Corium", 123, ini_file)); // HF_Canon corium

    patch.WriteU32((void *)0x007E1CEC, GetPrivateProfileInt(L"STOLp", L"Corium", 123, ini_file)); // STOLp corium 12
    patch.WriteU32((void *)0x007E1CF0, GetPrivateProfileInt(L"STOLp", L"Corium", 123, ini_file)); // STOLp corium

    patch.WriteU32((void *)0x007E1DC4, GetPrivateProfileInt(L"Double_Plasma_Turret", L"Corium", 123, ini_file)); // Plasma_Canon corium 28
    patch.WriteU32((void *)0x007E1DC8, GetPrivateProfileInt(L"Double_Plasma_Turret", L"Corium", 123, ini_file)); // Plasma_Canon corium
    patch.WriteU32((void *)0x007E1DCC, GetPrivateProfileInt(L"Double_Plasma_Turret", L"Corium", 123, ini_file)); // Plasma_Canon corium

    patch.WriteU32((void *)0x007E1D1C, GetPrivateProfileInt(L"Psychotron", L"Corium", 123, ini_file)); // Psychotron corium 10
    patch.WriteU32((void *)0x007E1D20, GetPrivateProfileInt(L"Psychotron", L"Corium", 123, ini_file)); // Psychotron corium
    patch.WriteU32((void *)0x007E1D24, GetPrivateProfileInt(L"Psychotron", L"Corium", 123, ini_file)); // Psychotron corium

    patch.WriteU32((void *)0x007E1D28, GetPrivateProfileInt(L"Plasmotron", L"Corium", 123, ini_file)); // Plasmotron corium 40
    patch.WriteU32((void *)0x007E1D2C, GetPrivateProfileInt(L"Plasmotron", L"Corium", 123, ini_file)); // Plasmotron corium
    patch.WriteU32((void *)0x007E1D30, GetPrivateProfileInt(L"Plasmotron", L"Corium", 123, ini_file)); // Plasmotron corium

    patch.WriteU32((void *)0x007E1D34, GetPrivateProfileInt(L"Nuclear_Launcher", L"Corium", 123, ini_file)); // Nuclear_Launcher corium 20

    // BO
    patch.WriteU32((void *)0x007E1D40, GetPrivateProfileInt(L"Light_Laser", L"Corium", 123, ini_file)); // Light_Laser corium 06
    patch.WriteU32((void *)0x007E1D44, GetPrivateProfileInt(L"Light_Laser", L"Corium", 123, ini_file)); // Light_Laser corium
    patch.WriteU32((void *)0x007E1D48, GetPrivateProfileInt(L"Light_Laser", L"Corium", 123, ini_file)); // Light_Laser corium
    patch.WriteU32((void *)0x007940D8, GetPrivateProfileInt(L"Light_Laser", L"Ammo", 123, ini_file)); // Light_Laser Ammo 05 123 !!! йцу

    patch.WriteU32((void *)0x007E1D70, GetPrivateProfileInt(L"Heavy_Laser", L"Corium", 123, ini_file)); // Heavy_Laser corium 2
    patch.WriteU32((void *)0x007E1D74, GetPrivateProfileInt(L"Heavy_Laser", L"Corium", 123, ini_file)); // Heavy_Laser corium
    patch.WriteU32((void *)0x007E1D78, GetPrivateProfileInt(L"Heavy_Laser", L"Corium", 123, ini_file)); // Heavy_Laser corium

    patch.WriteU32((void *)0x007E1D4C, GetPrivateProfileInt(L"Magnetic_Mine_Launcher", L"Corium", 123, ini_file)); // Magnetic_Mine_Launcher corium 26
    patch.WriteU32((void *)0x007E1D50, GetPrivateProfileInt(L"Magnetic_Mine_Launcher", L"Corium", 123, ini_file)); // Magnetic_Mine_Launcher corium
    patch.WriteU32((void *)0x007E1D54, GetPrivateProfileInt(L"Magnetic_Mine_Launcher", L"Corium", 123, ini_file)); // Magnetic_Mine_Launcher corium

    patch.WriteU32((void *)0x007E1D7C, GetPrivateProfileInt(L"EM_Launcher", L"Corium", 123, ini_file)); // EM_Launcher corium 24
    patch.WriteU32((void *)0x007E1D80, GetPrivateProfileInt(L"EM_Launcher", L"Corium", 123, ini_file)); // EM_Launcher corium
    patch.WriteU32((void *)0x007E1D84, GetPrivateProfileInt(L"EM_Launcher", L"Corium", 123, ini_file)); // EM_Launcher corium

    patch.WriteU32((void *)0x007E1D88, GetPrivateProfileInt(L"Protective_Shield", L"Corium", 123, ini_file)); // Protective_Shield gen corium 8
    patch.WriteU32((void *)0x007E1D8C, GetPrivateProfileInt(L"Protective_Shield", L"Corium", 123, ini_file)); // Protective_Shield gen corium
    patch.WriteU32((void *)0x007E1D90, GetPrivateProfileInt(L"Protective_Shield", L"Corium", 123, ini_file)); // Protective_Shield gen corium

    patch.WriteU32((void *)0x007E1DA0, GetPrivateProfileInt(L"Laser_Bomb_Launcher", L"Corium", 123, ini_file)); // Laser_Bomb_Launcher corium 50
    patch.WriteU32((void *)0x007E1DA0, GetPrivateProfileInt(L"Laser_Bomb_Launcher", L"Corium", 123, ini_file)); // Laser_Bomb_Launcher corium
    patch.WriteU32((void *)0x007E1DA0, GetPrivateProfileInt(L"Laser_Bomb_Launcher", L"Corium", 123, ini_file)); // Laser_Bomb_Launcher corium

    // SI
    patch.WriteU32((void *)0x007E1EC0, GetPrivateProfileInt(L"Gas_Canon", L"Corium", 123, ini_file)); // Gas_Canon corium 300
    patch.WriteU32((void *)0x007E1EC4, GetPrivateProfileInt(L"Gas_Canon", L"Corium", 123, ini_file)); // Gas_Canon corium
    patch.WriteU32((void *)0x007E1EC8, GetPrivateProfileInt(L"Gas_Canon", L"Corium", 123, ini_file)); // Gas_Canon corium

    patch.WriteU32((void *)0x007E1ECC, GetPrivateProfileInt(L"DPT", L"Corium", 123, ini_file)); // DPT corium 15
    patch.WriteU32((void *)0x007E1ED0, GetPrivateProfileInt(L"DPT", L"Corium", 123, ini_file)); // DPT corium
    patch.WriteU32((void *)0x007E1ED4, GetPrivateProfileInt(L"DPT", L"Corium", 123, ini_file)); // DPT corium

    patch.WriteU32((void *)0x007E1EFC, GetPrivateProfileInt(L"Pulsar", L"Corium", 123, ini_file)); // Pulsar corium 7
    patch.WriteU32((void *)0x007E1F00, GetPrivateProfileInt(L"Pulsar", L"Corium", 123, ini_file)); // Pulsar corium
    patch.WriteU32((void *)0x007E1F04, GetPrivateProfileInt(L"Pulsar", L"Corium", 123, ini_file)); // Pulsar corium

    patch.WriteU32((void *)0x007E1EF0, GetPrivateProfileInt(L"Bio_Mine_Launcher", L"Corium", 123, ini_file)); // Bio_Mine_Launcher corium 2
    patch.WriteU32((void *)0x007E1EF4, GetPrivateProfileInt(L"Bio_Mine_Launcher", L"Corium", 123, ini_file)); // Bio_Mine_Launcher corium
    patch.WriteU32((void *)0x007E1EF8, GetPrivateProfileInt(L"Bio_Mine_Launcher", L"Corium", 123, ini_file)); // Bio_Mine_Launcher corium

    patch.WriteU32((void *)0x007E1EE4, GetPrivateProfileInt(L"Jump_Mine_Launcher", L"Corium", 123, ini_file)); // Jump_Mine_Launcher corium 23
    patch.WriteU32((void *)0x007E1EE8, GetPrivateProfileInt(L"Jump_Mine_Launcher", L"Corium", 123, ini_file)); // Jump_Mine_Launcher corium 23
    patch.WriteU32((void *)0x007E1EEC, GetPrivateProfileInt(L"Jump_Mine_Launcher", L"Corium", 123, ini_file)); // Jump_Mine_Launcher corium 23

    patch.WriteU32((void *)0x007E1EE0, GetPrivateProfileInt(L"Ion_Reflector", L"Corium", 123, ini_file)); // Ion_Reflector corium 2

    patch.WriteU32((void *)0x007E1EBC, GetPrivateProfileInt(L"Soliton", L"Corium", 123, ini_file)); // Soliton corium 7

    patch.WriteU32((void *)0x007E1F4C, GetPrivateProfileInt(L"Parcher", L"Corium", 123, ini_file)); // Parcher corium 25
    
    patch.WriteU32((void *)0x007E1F58, GetPrivateProfileInt(L"Vacuum_Bomb", L"Corium", 123, ini_file)); // Vacuum_Bomb launcher corium 50

    patch.WriteU32((void *)0x007E1DE4, GetPrivateProfileInt(L"Core", L"Corium", 123, ini_file)); // Core corium 3



    // METAL/SILICON
    patch.WriteU32((void *)0x007E2568, GetPrivateProfileInt(L"Depot_WS", L"Metal", 123, ini_file));  // Depot_WS 08
    patch.WriteU32((void *)0x007E256C, GetPrivateProfileInt(L"Depot_BO", L"Metal", 123, ini_file));  // Depot_BO 08
    patch.WriteU32((void *)0x007E3390, GetPrivateProfileInt(L"Depot_SI", L"Metal", 123, ini_file));  // Depot_SI 06
    patch.WriteU32((void *)0x007E33C0, GetPrivateProfileInt(L"Silicon_Extractor", L"Metal", 123, ini_file)); // Silicon_Extractor silicon 06

    patch.WriteU32((void *)0x007E2508, GetPrivateProfileInt(L"Docks_WS", L"Metal", 123, ini_file)); // Docks_WS 12
    patch.WriteU32((void *)0x007E250C, GetPrivateProfileInt(L"Docks_BO", L"Metal", 123, ini_file)); // Docks_BO 12
    patch.WriteU32((void *)0x007E3414, GetPrivateProfileInt(L"Pulsar", L"Metal", 123, ini_file)); // Pulsar silicon 05

    patch.WriteU32((void *)0x007E33D8, GetPrivateProfileInt(L"Gas_Canon", L"Metal", 123, ini_file)); // Gas_Canon silicon 12
    patch.WriteU32((void *)0x007E33E4, GetPrivateProfileInt(L"DPT", L"Metal", 123, ini_file));  // DPT silicon 09
    patch.WriteU32((void *)0x007E33F0, GetPrivateProfileInt(L"Ion_Reflector", L"Metal", 123, ini_file));  // Ion_Reflector silicon 06
    patch.WriteU32((void *)0x007E3408, GetPrivateProfileInt(L"Bio_Mine_Launcher", L"Metal", 123, ini_file));  // Bio_Mine_Launcher silicon 07
    patch.WriteU32((void *)0x007E345C, GetPrivateProfileInt(L"Parcher", L"Metal", 123, ini_file)); // Parcher silicon 14
    patch.WriteU32((void *)0x007E3360, GetPrivateProfileInt(L"Protoplasm_Generator", L"Metal", 123, ini_file)); // Protoplasm_Generator silicon 14

    patch.WriteU32((void *)0x007E2598, GetPrivateProfileInt(L"STOLp", L"Metal", 123, ini_file)); // STOLp metal 1
    patch.WriteU32((void *)0x007E259C, GetPrivateProfileInt(L"STOLp", L"Metal", 123, ini_file)); // STOLp metal 1
    patch.WriteU32((void *)0x007E25A0, GetPrivateProfileInt(L"STOLp", L"Metal", 123, ini_file)); // STOLp metal 1

    patch.WriteU32((void *)0x007E2670, GetPrivateProfileInt(L"Plasma_Canon", L"Metal", 123, ini_file)); // Plasma_Canon metal 12
    patch.WriteU32((void *)0x007E2674, GetPrivateProfileInt(L"Plasma_Canon", L"Metal", 123, ini_file)); // Plasma_Canon metal 12
    patch.WriteU32((void *)0x007E2678, GetPrivateProfileInt(L"Plasma_Canon", L"Metal", 123, ini_file)); // Plasma_Canon metal 12

    patch.WriteU32((void *)0x007E25BC, GetPrivateProfileInt(L"USG", L"Metal", 123, ini_file)); // USG metal 09
    patch.WriteU32((void *)0x007E25C0, GetPrivateProfileInt(L"USG", L"Metal", 123, ini_file)); // USG metal 09
    patch.WriteU32((void *)0x007E25C4, GetPrivateProfileInt(L"USG", L"Metal", 123, ini_file)); // USG metal 09

    patch.WriteU32((void *)0x007E25EC, GetPrivateProfileInt(L"Light_Laser", L"Metal", 123, ini_file)); // Light_Laser metal 04
    patch.WriteU32((void *)0x007E25F0, GetPrivateProfileInt(L"Light_Laser", L"Metal", 123, ini_file)); // Light_Laser metal 04
    patch.WriteU32((void *)0x007E25F4, GetPrivateProfileInt(L"Light_Laser", L"Metal", 123, ini_file)); // Light_Laser metal 04

    patch.WriteU32((void *)0x007E25F8, GetPrivateProfileInt(L"Magnetic_Mine_Launcher", L"Metal", 123, ini_file)); // Magnetic_Mine_Launcher metal 14
    patch.WriteU32((void *)0x007E25FC, GetPrivateProfileInt(L"Magnetic_Mine_Launcher", L"Metal", 123, ini_file)); // Magnetic_Mine_Launcher metal 14
    patch.WriteU32((void *)0x007E2600, GetPrivateProfileInt(L"Magnetic_Mine_Launcher", L"Metal", 123, ini_file)); // Magnetic_Mine_Launcher metal 14

    patch.WriteU32((void *)0x007E261C, GetPrivateProfileInt(L"Heavy_Laser", L"Metal", 123, ini_file)); // Heavy_Laser metal 1
    patch.WriteU32((void *)0x007E2620, GetPrivateProfileInt(L"Heavy_Laser", L"Metal", 123, ini_file)); // Heavy_Laser metal 1
    patch.WriteU32((void *)0x007E2624, GetPrivateProfileInt(L"Heavy_Laser", L"Metal", 123, ini_file)); // Heavy_Laser metal 1

    patch.WriteU32((void *)0x007E2628, GetPrivateProfileInt(L"EM_Launcher", L"Metal", 123, ini_file)); // EM_Launcher metal 12
    patch.WriteU32((void *)0x007E262C, GetPrivateProfileInt(L"EM_Launcher", L"Metal", 123, ini_file)); // EM_Launcher metal 12
    patch.WriteU32((void *)0x007E2630, GetPrivateProfileInt(L"EM_Launcher", L"Metal", 123, ini_file)); // EM_Launcher metal 12

    patch.WriteU32((void *)0x007E25D4, GetPrivateProfileInt(L"Plasmotron", L"Metal", 123, ini_file)); // Plasmotron metal 1
    patch.WriteU32((void *)0x007E25D8, GetPrivateProfileInt(L"Plasmotron", L"Metal", 123, ini_file)); // Plasmotron metal 1
    patch.WriteU32((void *)0x007E25DC, GetPrivateProfileInt(L"Plasmotron", L"Metal", 123, ini_file)); // Plasmotron metal 1

    patch.WriteU32((void *)0x007E25E0, GetPrivateProfileInt(L"Nuclear_Launcher", L"Metal", 123, ini_file)); // Nuclear_Launcher metal 2
    patch.WriteU32((void *)0x007E25E4, GetPrivateProfileInt(L"Nuclear_Launcher", L"Metal", 123, ini_file)); // Nuclear_Launcher metal 2
    patch.WriteU32((void *)0x007E25E8, GetPrivateProfileInt(L"Nuclear_Launcher", L"Metal", 123, ini_file)); // Nuclear_Launcher metal 2

    patch.WriteU32((void *)0x007E264C, GetPrivateProfileInt(L"Laser_Bomb_Launcher", L"Metal", 123, ini_file)); // Laser_Bomb_Launcher metal 2
    patch.WriteU32((void *)0x007E2650, GetPrivateProfileInt(L"Laser_Bomb_Launcher", L"Metal", 123, ini_file)); // Laser_Bomb_Launcher metal 2
    patch.WriteU32((void *)0x007E2654, GetPrivateProfileInt(L"Laser_Bomb_Launcher", L"Metal", 123, ini_file)); // Laser_Bomb_Launcher metal 2

    patch.WriteU32((void *)0x007E3468, GetPrivateProfileInt(L"Vacuum_Bomb", L"Metal", 123, ini_file)); // Vacuum_Bomb launcher silicon 2

    
     // TURRETS 
    // RANGE
    patch.WriteByte((void *)0x00792208, GetPrivateProfileInt(L"HF_Canon", L"Range", 8, ini_file)); // HF_Canon first range 7
    patch.WriteByte((void *)0x00792218, GetPrivateProfileInt(L"STOLp", L"Range", 8, ini_file)); // STOLp first range 8
    patch.WriteByte((void *)0x00792338, GetPrivateProfileInt(L"Plasma_Canon", L"Range", 8, ini_file)); // Plasma_Canon first range 9 

    patch.WriteByte((void *)0x00792288, GetPrivateProfileInt(L"Light_Laser", L"Range_1", 7, ini_file)); // Light_Laser first range 7
    patch.WriteByte((void *)0x0079228C, GetPrivateProfileInt(L"Light_Laser", L"Range_2", 9, ini_file)); // Light_Laser second range 8
    patch.WriteByte((void *)0x007922C8, GetPrivateProfileInt(L"Heavy_Laser", L"Range_1", 8, ini_file)); // Heavy_Laser first range 6
    patch.WriteByte((void *)0x007922CC, GetPrivateProfileInt(L"Heavy_Laser", L"Range_2	", 10, ini_file)); // Heavy_Laser second range 8 
    patch.WriteByte((void *)0x00792298, GetPrivateProfileInt(L"Magnetic_Mine_Launcher", L"Range", 8, ini_file)); // Magnetic_Mine_Launcher range 7 
    patch.WriteByte((void *)0x007922A0, GetPrivateProfileInt(L"Magnetic_Mine_Launcher", L"Range_Mines", 8, ini_file));  // Magnetic_Mine_Launcher mines range 8 
    patch.WriteByte((void *)0x007922D8, GetPrivateProfileInt(L"EM_Launcher", L"Range", 123, ini_file)); // EM_Launcher first range 9

    patch.WriteByte((void *)0x007924D8, GetPrivateProfileInt(L"Pulsar", L"Range", 8, ini_file)); // Pulsar first range 7
    patch.WriteByte((void *)0x00792488, GetPrivateProfileInt(L"Gas_Canon", L"Range", 8, ini_file));  // Gas_Canon first range 7
    patch.WriteU32((void *)0x00792498, GetPrivateProfileInt(L"Double_Plasma_Turret", L"Range_1", 8, ini_file));  // DPT range 1 8
    patch.WriteU32((void *)0x0079249C, GetPrivateProfileInt(L"Double_Plasma_Turret", L"Range_2", 10, ini_file)); // DPT range 2 10

    patch.WriteByte((void *)0x007924A8, GetPrivateProfileInt(L"Ion_Reflector", L"Range", 8, ini_file)); // Ion_Reflector first range 8
    patch.WriteByte((void *)0x00792538, GetPrivateProfileInt(L"Parcher", L"Range", 8, ini_file)); // Parcher first range 9
    //

    // Unlock Turrets Range 8->10
    patch.WriteByte((void *)0x004C3CC2, 246);
    patch.WriteByte((void *)0x004C3CF0, 246);
    patch.WriteByte((void *)0x004C3CF3, 10);
    patch.WriteByte((void *)0x004C3CC5, 10);
    patch.WriteByte((void *)0x004C426F, 10);
    patch.WriteByte((void *)0x004C4281, 10);
    //

    // ATTACK COOLDOWN
    patch.WriteU32((void *)0x007DFF20, GetPrivateProfileInt(L"Plasma_Canon", L"Metal", 123, ini_file)); // Plasma_Canon reload (vanilla 100 (4 sec))


    // SUBMARINES
    // METAL/SILICON
    patch.WriteU32((void *)0x007E07D0, GetPrivateProfileInt(L"Fighter", L"Metal", 123, ini_file)); // Fighter metal 300
    patch.WriteU32((void *)0x007E07D4, GetPrivateProfileInt(L"Destroyer", L"Metal", 500, ini_file)); // Destroyer metal
    patch.WriteU32((void *)0x007E07D8, GetPrivateProfileInt(L"Heavy_Сruiser", L"Metal", 123, ini_file)); // Heavy Cruiser metal 1400

    patch.WriteU32((void *)0x007E07A4, GetPrivateProfileInt(L"Hunter", L"Metal", 123, ini_file));  // Hunter metal 450
    patch.WriteU32((void *)0x007E07A8, GetPrivateProfileInt(L"Сruiser", L"Metal", 123, ini_file)); // Сruiser metal 1100
    patch.WriteU32((void *)0x007E07C8, GetPrivateProfileInt(L"Liberator", L"Metal", 123, ini_file)); // Liberator metal 900
    patch.WriteU32((void *)0x007E07C4, GetPrivateProfileInt(L"Terminator", L"Metal", 1000, ini_file)); // Terminator metal
    patch.WriteU32((void *)0x007E07BC, GetPrivateProfileInt(L"Transport_Humman", L"Metal", 123, ini_file));  // Transport WS metal 300
    patch.WriteU32((void *)0x007E07EC, GetPrivateProfileInt(L"Transport_Humman", L"Metal", 123, ini_file));  // Transport BO metal 300
    patch.WriteU32((void *)0x007E07E4, GetPrivateProfileInt(L"Raider", L"Metal", 123, ini_file)); // Raider metal 300

    patch.WriteU32((void *)0x007E0A44, GetPrivateProfileInt(L"Transport_SI", L"Metal", 123, ini_file));  // Trailer silicon 200
    patch.WriteU32((void *)0x007E0A50, GetPrivateProfileInt(L"Energizer", L"Metal", 123, ini_file)); // Energizer silicon 600
    patch.WriteU32((void *)0x007E0A68, GetPrivateProfileInt(L"Psi_Zond", L"Metal", 123, ini_file));  // Psi_Zond silicon 900
    patch.WriteU32((void *)0x007E0A64, GetPrivateProfileInt(L"Usurper", L"Metal", 123, ini_file));  // Usurper silicon 1000
    patch.WriteU32((void *)0x007E0A54, GetPrivateProfileInt(L"Skat", L"Metal", 123, ini_file));  // Skat silicon 250
    patch.WriteU32((void *)0x007E0A4C, GetPrivateProfileInt(L"Paralizator", L"Metal", 123, ini_file));  // Paralizator silicon 600
    patch.WriteU32((void *)0x007E0A5C, GetPrivateProfileInt(L"Escort", L"Metal", 123, ini_file));  // Escort silicon 800
    patch.WriteU32((void *)0x007E0A58, GetPrivateProfileInt(L"Dreadnaught", L"Metal", 123, ini_file)); // Dreadnaught silicon 1200
    patch.WriteU32((void *)0x007E0A40, GetPrivateProfileInt(L"Module_Prototype", L"Metal", 123, ini_file)); // Module_Prototype silicon  50
	patch.WriteU32((void *)0x007E0A60, GetPrivateProfileInt(L"Bio_Assaulter", L"Metal", 123, ini_file)); // Bio_Assaulter silicon (vanilla 700) 900
	
    // CORIUM
    patch.WriteU32((void *)0x007E05DC, GetPrivateProfileInt(L"Escort", L"Corium", 123, ini_file)); // Escort corium 150
    patch.WriteU32((void *)0x007E05D4, GetPrivateProfileInt(L"Skat", L"Corium", 123, ini_file));  // Skat corium 40
    patch.WriteU32((void *)0x007E0590, GetPrivateProfileInt(L"Fighter", L"Corium", 123, ini_file));  // Fighter corium 40
    patch.WriteU32((void *)0x007E0564, GetPrivateProfileInt(L"Hunter", L"Corium", 123, ini_file));  // Hunter corium 70
    patch.WriteU32((void *)0x007E05E8, GetPrivateProfileInt(L"Psi_Zond", L"Corium", 123, ini_file)); // Psi_Zond corium 400
    patch.WriteU32((void *)0x007E059C, GetPrivateProfileInt(L"Invader", L"Corium", 123, ini_file)); // Invader corium 180
    patch.WriteU32((void *)0x007E05D0, GetPrivateProfileInt(L"Energizer", L"Corium", 123, ini_file)); // Energizer corium 200
    patch.WriteU32((void *)0x007E05B8, GetPrivateProfileInt(L"Avenger", L"Corium", 123, ini_file)); // Avenger corium 220
    patch.WriteU32((void *)0x007E0594, GetPrivateProfileInt(L"Destroyer", L"Corium", 80, ini_file));  // Destroyer corium
    patch.WriteU32((void *)0x007E0598, GetPrivateProfileInt(L"Heavy_Сruiser", L"Corium", 123, ini_file)); // Heavy_Сruiser corium 360
    patch.WriteU32((void *)0x007E05B4, GetPrivateProfileInt(L"Phantom", L"Corium", 123, ini_file)); // Phantom corium 280
    patch.WriteU32((void *)0x007E05A4, GetPrivateProfileInt(L"Raider", L"Corium", 123, ini_file)); // Raider corium 120
    
    patch.WriteU32((void *)0x007E0570, GetPrivateProfileInt(L"Mine-layer", L"Corium", 90, ini_file)); // Mine-Layer corium
    patch.WriteU32((void *)0x007E05A0, GetPrivateProfileInt(L"Defender", L"Corium", 120, ini_file)); // Defender corium
    patch.WriteU32((void *)0x007E05E0, GetPrivateProfileInt(L"Bio-assaulter", L"Corium", 200, ini_file)); // Bio-acid assaulter corium 

    patch.WriteU32((void *)0x007E05C8, GetPrivateProfileInt(L"Supplier", L"Corium", 0, ini_file)); // Supplier corium
    

    // BUILDTIME
    //patch.WriteU32((void *)0x007E04C8, 600); // Fighter/Liberator buildtime //600

    patch.WriteU32((void *)0x007E04D0, GetPrivateProfileInt(L"Fighter", L"BuildTime", 123, ini_file));  // Fighter buildtime1 600
    patch.WriteU32((void *)0x007E0514, GetPrivateProfileInt(L"Skat", L"BuildTime", 123, ini_file));  // Skat buildtime  
    patch.WriteU32((void *)0x007E04B4, GetPrivateProfileInt(L"Marauder", L"BuildTime", 123, ini_file)); // Marauder buildtime
    patch.WriteU32((void *)0x007E04E4, GetPrivateProfileInt(L"Raider", L"BuildTime", 123, ini_file)); // Raider buildtime
    patch.WriteU32((void *)0x007E0528, GetPrivateProfileInt(L"Usurper", L"BuildTime", 123, ini_file)); // Usurper buildtime
    patch.WriteU32((void *)0x007E04D4, GetPrivateProfileInt(L"Destroyer", L"BuildTime", 1000, ini_file)); // Destroyer buildtime
    patch.WriteU32((void *)0x007E04D8, GetPrivateProfileInt(L"Heavy_Сruiser", L"BuildTime", 123, ini_file)); // Heavy_Сruiser buildtime

    // HP
    patch.WriteU32((void *)0x007DFBB0, GetPrivateProfileInt(L"Sentinel", L"HP", 123, ini_file));  // Sentinel hp
    patch.WriteU32((void *)0x007DFBC4, GetPrivateProfileInt(L"Marauder", L"HP", 123, ini_file)); // Marauder hp йцу 1400
    patch.WriteU32((void *)0x007DFBC0, GetPrivateProfileInt(L"Minelayer", L"HP", 123, ini_file)); // Minelayer hp йцу 1000
    patch.WriteU32((void *)0x007DFBB4, GetPrivateProfileInt(L"Hunter", L"HP", 123, ini_file));  // Hunter hp
    patch.WriteU32((void *)0x007DFBBC, GetPrivateProfileInt(L"Bomber", L"HP", 123, ini_file)); // DC Bomber hp
    patch.WriteU32((void *)0x007DFBD8, GetPrivateProfileInt(L"Liberator", L"HP", 123, ini_file)); // Liberator hp
    patch.WriteU32((void *)0x007DFBD0, GetPrivateProfileInt(L"Cyberworm", L"HP", 123, ini_file));  // Cyberworm hp

    patch.WriteU32((void *)0x007DFBE0, GetPrivateProfileInt(L"Fighter", L"HP", 123, ini_file));  // Fighter hp
    patch.WriteU32((void *)0x007DFBE4, GetPrivateProfileInt(L"Destroyer", L"HP", 600, ini_file));  // Destroyer hp
    patch.WriteU32((void *)0x007DFBEC, GetPrivateProfileInt(L"Invader", L"HP", 123, ini_file));  // Invader hp
    patch.WriteU32((void *)0x007DFBBF0, GetPrivateProfileInt(L"Defender", L"HP", 900, ini_file)); // Defender hp
    patch.WriteU32((void *)0x007DFBF4, GetPrivateProfileInt(L"Raider", L"HP", 123, ini_file)); // Raider hp
    patch.WriteU32((void *)0x007DFC00, GetPrivateProfileInt(L"Cyberdolphin", L"HP", 123, ini_file));  // Cyberdolphin hp
    patch.WriteU32((void *)0x007DFC24, GetPrivateProfileInt(L"Skat", L"HP", 123, ini_file));  // Skat hp
    patch.WriteU32((void *)0x007DFC2C, GetPrivateProfileInt(L"Escort", L"HP", 500, ini_file)); // Escort hp
    patch.WriteU32((void *)0x007DFC38, GetPrivateProfileInt(L"Psi_Zond", L"HP", 700, ini_file));  // Psi_Zond hp
    patch.WriteU32((void *)0x007DFC28, GetPrivateProfileInt(L"Dreadnaught", L"HP", 1500, ini_file)); // Dreadnaught hp
    patch.WriteU32((void *)0x007DFC30, GetPrivateProfileInt(L"Bio_Assaulter", L"HP", 900, ini_file));  // Bio_Assaulter hp
    patch.WriteU32((void *)0x007DFC34, GetPrivateProfileInt(L"Usurper", L"HP", 1200, ini_file)); // Usurper hp

    patch.WriteU32((void *)0x007DFC14, GetPrivateProfileInt(L"Transport_SI", L"HP", 500, ini_file)); // Transport SI hp

    // ATTACK COOLDOWN
    patch.WriteU32((void *)0x007A8C5C, GetPrivateProfileInt(L"Sentinel", L"Reload", 30, ini_file)); // Sentinel reload
    patch.WriteU32((void *)0x007A8C80, GetPrivateProfileInt(L"Terminator", L"Reload", 100, ini_file)); // Terminator reload
    patch.WriteU32((void *)0x007A8C90, GetPrivateProfileInt(L"Destroyer", L"Reload", 50, ini_file));  // Destroyer reload
    patch.WriteU32((void *)0x007A8CB4, GetPrivateProfileInt(L"Avenger", L"Reload", 50, ini_file)); // Aveger reload
    
    // SPECIAL
    patch.WriteByte((void *)0x0045094E, GetPrivateProfileInt(L"Phantom", L"Вischarge", 30, ini_file)); // Phantom discharge

    // DAMAGE     
    patch.WriteU32((void *)0x007E6490, GetPrivateProfileInt(L"Weap_HeavyTorpedo", L"Damage_1", 90, ini_file)); // Cruiser T1 damage
    patch.WriteU32((void *)0x007E6494, GetPrivateProfileInt(L"Weap_HeavyTorpedo", L"Damage_2", 120, ini_file)); // Cruiser T2 damage
    patch.WriteU32((void *)0x007E6498, GetPrivateProfileInt(L"Weap_HeavyTorpedo", L"Damage_3", 150, ini_file)); // Cruiser T3 damage
    patch.WriteU32((void *)0x007E649C, GetPrivateProfileInt(L"Weap_HeavyTorpedo", L"Damage_4", 170, ini_file)); // Cruiser T4 damage
    patch.WriteU32((void *)0x007E64A0, GetPrivateProfileInt(L"Weap_HeavyTorpedo", L"Damage_5", 200, ini_file)); // Cruiser T5 damage
    
    
    patch.WriteU32((void *)0x007E651C, GetPrivateProfileInt(L"Weap_LHF", L"Damage_1", 30, ini_file));  // Sentinel dmg T1
    patch.WriteU32((void *)0x007E6520, GetPrivateProfileInt(L"Weap_LHF", L"Damage_2", 80, ini_file));  // Sentinel dmg T2
    
    patch.WriteU32((void *)0x007E6530, GetPrivateProfileInt(L"Weap_HHF", L"Damage_1", 70, ini_file)); // HF heavy T1 damage
    patch.WriteU32((void *)0x007E6534, GetPrivateProfileInt(L"Weap_HHF", L"Damage_2", 120, ini_file)); // HF heavy T2 damage
    
    patch.WriteU32((void *)0x007E679C, GetPrivateProfileInt(L"Weap_Pulsar", L"Damage_1", 80, ini_file)); // Pulsar T1 damage
    patch.WriteU32((void *)0x007E67A0, GetPrivateProfileInt(L"Weap_Pulsar", L"Damage_2", 120, ini_file)); // Pulsar T2 damage
    patch.WriteU32((void *)0x007E67A4, GetPrivateProfileInt(L"Weap_Pulsar", L"Damage_3", 150, ini_file)); // Pulsar T3 damage
    
    patch.WriteU32((void *)0x007E65E4, GetPrivateProfileInt(L"Weap_DCBomb", L"Damage", 500, ini_file)); // DC Bomb damage

    
    patch.WriteU32((void *)0x007E6620, GetPrivateProfileInt(L"Weap_SplinterTorpedo", L"Damage_1", 60, ini_file)); // Destroyer T1 damage (vanilla 60)
    patch.WriteU32((void *)0x007E6624, GetPrivateProfileInt(L"Weap_SplinterTorpedo", L"Damage_2", 150, ini_file)); // Destroyer T2 damage (vanilla 150)

    patch.WriteU32((void *)0x007E6508, GetPrivateProfileInt(L"Weap_HeavyLaser", L"Damage", 200, ini_file)); // Heavy_Laser (vanilla 200)

    patch.WriteU32((void *)0x00464814, GetPrivateProfileInt(L"Cyberdolphin", L"Damage", 600, ini_file)); // Cyberdolphin damage

    patch.WriteU32((void *)0x007E64A4, GetPrivateProfileInt(L"Weap_CasseteShell", L"Damage", 120, ini_file)); // Weap_CasseteShell
    patch.WriteU32((void *)0x007E66FC, GetPrivateProfileInt(L"Weap_IonCassete", L"Damage_1", 120, ini_file)); // Ion cassete t1 
    patch.WriteU32((void *)0x007E6700, GetPrivateProfileInt(L"Weap_IonCassete", L"Damage_2", 140, ini_file)); // Ion cassete t2
    patch.WriteU32((void *)0x007E6704, GetPrivateProfileInt(L"Weap_IonCassete", L"Damage_3", 160, ini_file)); // Ion cassete t3

    patch.WriteU32((void *)0x007E6724, GetPrivateProfileInt(L"Weap_IonCasseteSubshell", L"Damage_1", 20, ini_file)); // Ion cassete subshell t1
    patch.WriteU32((void *)0x007E6728, GetPrivateProfileInt(L"Weap_IonCasseteSubshell", L"Damage_2", 30, ini_file)); // Ion cassete subshell t2
    patch.WriteU32((void *)0x007E672C, GetPrivateProfileInt(L"Weap_IonCasseteSubshell", L"Damage_3", 40, ini_file)); // Ion cassete subshell t3

	patch.WriteU32((void *)0x007E66E8, GetPrivateProfileInt(L"Weap_EnergyShell", L"Damage_1", 40, ini_file)); // Energy shell dmg t1 
	patch.WriteU32((void *)0x007E66EC, GetPrivateProfileInt(L"Weap_EnergyShell", L"Damage_2", 60, ini_file)); // Energy shell dmg t2 
    patch.WriteU32((void *)0x007E66F0, GetPrivateProfileInt(L"Weap_EnergyShell", L"Damage_3", 100, ini_file)); // Energy shell dmg t3 
    patch.WriteU32((void *)0x007E67C4, GetPrivateProfileInt(L"Weap_Soliton", L"Damage", 30, ini_file)); // Soliton dmg 
    

    patch.WriteU32((void *)0x007E6648, GetPrivateProfileInt(L"Weap_GasShell", L"Damage", 150, ini_file));  // Gas Shell Launcher damage

    patch.WriteU32((void *)0x007E6580, GetPrivateProfileInt(L"Weap_Plasma", L"Damage", 600, ini_file)); // Plasma damage          

    //--------------------------------------------------------------------------------------------------------------------

    //Submarines armor
    patch.WriteByte((void *)0x00459E86, 0x11); // Half armor T2 jump
    patch.WriteByte((void *)0x00459E9C, 0xC9); // Half armor T2 value (90%)
    patch.WriteNops((void *)0x00459E9D, 2);    // Half armor T2 nops

    patch.WriteByte((void *)0x00459E89, 0x17); // Half armor T3 jump

    patch.WriteByte((void *)0x00459E91, 0x89);  // Half armor T4
    patch.WriteU16((void *)0x00459E92, 0xCA01); // Half armor T4
    patch.WriteU16((void *)0x00459E94, 0xCA01); // Half armor T4
        
    //Buildings armor
    patch.WriteByte((void *)0x004BB5A1, 0x12); // Half armor T2 jump
    patch.WriteByte((void *)0x004BB5B9, 0xC9); // Half armor T2 value (90%)
    patch.WriteNops((void *)0x004BB5BA, 2);    // Half armor T2 nops

    patch.WriteByte((void *)0x004BB5A4, 0x19); // Half armor T3 jump

    patch.WriteByte((void *)0x004BB5AD, 0x89);  // Half armor T4
    patch.WriteU16((void *)0x004BB5AE, 0xCA01); // Half armor T4
    patch.WriteU16((void *)0x004BB5B0, 0xCA01); // Half armor T4

    //patch.WriteByte((void *)0x00642ABA, 3);   // Laser reflection % (25 -> 12.5)
    // Max blocked damage
    patch.WriteU32((void *)0x004BB5DF, 1000); // max blocked damage check
    patch.WriteU32((void *)0x004BB5E6, 1000); // max blocked damage replace

    //ECONOMICS
    //patch.WriteU32((void *)0x0043092D, 12); // Metal in 1/40 of Transport capacity load
    patch.WriteU32((void *)0x0043092D, 15); // Metal in 1/40 of Transport capacity load
    //patch.WriteByte((void *)0x00469347, 0x7F); // Metal in 1/40 of Transport capacity unload
    patch.WriteU32((void *)0x00469348, 0x51490C8D);  // Metal in 1/40 of Transport capacity unload
    //patch.WriteNops((void *)0x00469348, 3);    // No additional shl 2

    
    patch.WriteU32((void *)0x004E0156, 7); // energy mine tick timer
    
    // OTHER
    //patch.WriteU32((void *)0x0044F745, 7); // Submarines standard view range BO
    //patch.WriteU32((void *)0x0044F427, 7); // Submarines standard view range WS
    patch.WriteJumpSized(ChangeSubsRangeStd_Jmp, 7, (unsigned long)ChangeSubsRangeStd);
    

    return true;
}

static bool Flagships(Patcher::SPatch &patch)
{
    // Flagships in wargroups and not in special groups
    patch.WriteU32((void *)0x0080148C, 899);        // Flagships add to wargroups 899
    patch.WriteU32((void *)0x004E87F7, 2425393296); // nops to not overwrite
    patch.WriteByte((void *)0x004E87FB, 144);
    patch.WriteByte((void *)0x004E87D7, 137);
    patch.WriteByte((void *)0x004E87D8, 242);

    patch.WriteJumpSized(NoPlatformLoadFlagships_Jmp, 5, (unsigned long)NoPlatformLoadFlagships);

    //WS
    patch.WriteByte((void *)0x007C0E44, 7);   // Research ID
    patch.WriteByte((void *)0x004E8341, 128); // Belongs race
    patch.WriteU32((void *)0x007E0534, 4500); // Time
    patch.WriteU32((void *)0x007E0834, 5200); // Metal
    patch.WriteU32((void *)0x007E05F4, 1200); // Corium
    patch.WriteU32((void *)0x007A8BB0, 151);  // Weapon type
    patch.WriteU32((void *)0x007A8CF0, 30);   // Reload
    patch.WriteU32((void *)0x007A8C50, 40);   // Ammo
    patch.WriteU16((void *)0x0048C31c, 40);   // Side shift
    patch.WriteI16((void *)0x0048C333, -40);  // Side shift 2
    patch.WriteU32((void *)0x007DFC44, 3000); // HP


    // BO
    patch.WriteByte((void *)0x007C0E47, 35); // Research ID
    // Belongs race
    patch.WriteByte((void *)0x004E8364, 12);  // al or
    patch.WriteByte((void *)0x004E8365, 36);  // 36 (0x24 + 0x140) = 356
    patch.WriteByte((void *)0x004E8366, 144); // nop

    patch.WriteU32((void *)0x007E0538, 3750); // Time
    patch.WriteU32((void *)0x007E0838, 3800); // Metal
    patch.WriteU32((void *)0x007E05F8, 1100); // Corium
    patch.WriteU32((void *)0x007A8BB4, 157);  // Weapon type
    patch.WriteU32((void *)0x007A8CF4, 20);   // Reload
    patch.WriteU32((void *)0x007A8C54, 20);   // Ammo
    patch.WriteU32((void *)0x007DFC48, 1900); // HP

    patch.WriteJumpSized(BOFlagshipRange6_Jmp, 5, (unsigned long)BOFlagshipRange6);

    //SI
    patch.WriteByte((void *)0x007C0E4A, 109); // Research ID
    patch.WriteU16((void *)0x004E83A2, 204);  // Belongs race
    patch.WriteU32((void *)0x007E053C, 4500); // Time
    patch.WriteU32((void *)0x007E0A7C, 4300); // Silicon
    patch.WriteU32((void *)0x007E05FC, 1000);  // Corium
    patch.WriteU32((void *)0x007A8CF8, 5);    // Reload
    patch.WriteU32((void *)0x007DFC4C, 2000); // HP
    // patch.WriteU32((void *)0x007A8BB8, ); // weapon
    patch.WriteJumpSized(SIFlagshipRange7_Jmp, 5, (unsigned long)SIFlagshipRange7);
    patch.WriteNops((void *)0x004622FF, 9); // No overwrite 5 range
    patch.WriteNops((void *)0x004653D8, 9); // No overwrite 5 range again    
    return true;
}
static bool AimPrediction(Patcher::SPatch &patch)
{
    patch.WriteJumpSized(ModifyAimGpsV2_Jmp, 7, (unsigned long)ModifyAimGpsV2);
    patch.WriteJumpSized(ModifyTurretTurnV2_Jmp, 5, (unsigned long)ModifyTurretTurnV2);
    patch.WriteJumpSized(ModifyTurretTurnCheckV2_Jmp, 5, (unsigned long)ModifyTurretTurnCheckV2);
    patch.WriteJumpSized(ModifyTurretFix_Jmp, 5, (unsigned long)ModifyTurretFix);
    patch.WriteJumpSized(ModifyTurretFix2_Jmp, 5, (unsigned long)ModifyTurretFix2);
    patch.WriteJumpSized(AimPredictionSubmarines_Jmp, 7, (unsigned long)AimPredictionSubmarines);
    return true;
}

static bool OneDepotFor2Mines(Patcher::SPatch &patch)
{
    patch.WriteByte((void *)0x004693A6, 1);    // Transport waiting distance set after depot
    patch.WriteByte((void *)0x00467488, 1);    // Transport waiting distance set after mine
    patch.WriteByte((void *)0x004696F9, 1);    // Transport waiting distance 3
    patch.WriteByte((void *)0x004699A1, 1);    // Transport waiting distance set after mine order
    patch.WriteByte((void *)0x004438BE, 0xF9); // Transport Decision cmp 1"
    patch.WriteByte((void *)0x004438E8, 0xF9); // Transport Decision cmp 2
    patch.WriteByte((void *)0x004691B2, 2);    // Resource unload speed divisor
    patch.WriteJumpSized(Transport_waiting_depot_distance_Jmp, 6, (unsigned long)Transport_waiting_depot_distance);
    patch.WriteJumpSized(Transport_waiting_mine_distance2_Jmp, 6, (unsigned long)Transport_waiting_mine_distance2);
    return true;
}
static bool EconomicsAndOther(Patcher::SPatch &patch)
{
    // patch.WriteByte((void *)0x004E4794, 10); // Silicon excavation check (vanilla 10)
    // patch.WriteU32((void *)0x004E4798, 10);   // Silicon excavation (vanilla 10)
    // patch.WriteByte((void *)0x004E47DA, 10);  // Silicon excavation check 2 (vanilla 10)
    // patch.WriteU32((void *)0x007BF598, 10);  // Gold level t2
    // patch.WriteU32((void *)0x007BF57C, 5000); // Starting metal t1
    // patch.WriteU32((void *)0x007BF588, 5000); // Starting silicon t1


    patch.WriteJumpSized(RangeAllSubs6_Jmp, 6, (unsigned long)RangeAllSubs6);

    
    patch.WriteU16((void *)0x0044F773, 0xD233); // Radio stutter make zero before period
    patch.WriteByte((void *)0x0044F77B, 75);    // Radio stutter new period

    // patch.WriteNops((void *)0x0057A320, 6);     // cassete check num??
    // patch.WriteU32((void *)0x0057B6D6, );      // Cassete conus 1/radius

    // UNITS

        
    return true;
}

static bool ResearchBuildingsLimit(Patcher::SPatch &patch)
{
    patch.WriteNops((void *)0x004E7EEB, 10); // Disable use of techcenters limit area
    patch.WriteJumpSized(ResearchBuildingsLimitCreateCommon_Jmp, 7, (unsigned long)ResearchBuildingsLimitCreateCommon);
    patch.WriteJumpSized(CheckHumanResearchCenters_Jmp, 5, (unsigned long)CheckHumanResearchCenters);
    patch.WriteJumpSized(CheckSIModules_Jmp, 5, (unsigned long)CheckSIModules);
    patch.WriteJumpSized(DestroyedModulesAndHumanCentersFinished_Jmp, 5, (unsigned long)DestroyedModulesAndHumanCentersFinished);
    patch.WriteJumpSized(DestroyedModulesAndHumanCentersBuilding_Jmp, 5, (unsigned long)DestroyedModulesAndHumanCentersBuilding);
    patch.WriteJumpSized(DismantledModulesAndHumanCenters_Jmp, 6, (unsigned long)DismantledModulesAndHumanCenters);
    patch.WriteJumpSized(CancelledModulesAndHumanCenters_Jmp, 6, (unsigned long)CancelledModulesAndHumanCenters);
    patch.WriteJumpSized(CapturedTechBuildings_Jmp, 6, (unsigned long)CapturedTechBuildings);
    patch.WriteJumpSized(AntiAbuseHumanCenters_Jmp, 13, (unsigned long)AntiAbuseHumanCenters);
    //patch.WriteNops((void *)AntiAbuseHumanCenters_Jmp, 10); // Disable use of techcenters limit area

    // MODULES RESEARCH LISTS
    patch.WriteU32((void *)0x0079A3FC, 109); // SI speed module
    patch.WriteU32((void *)0x0079A400, 110);
    patch.WriteU32((void *)0x0079A404, 101);
    patch.WriteU32((void *)0x0079A408, 106);
    patch.WriteU32((void *)0x0079A40C, 105);
    //patch.WriteU32((void *)0x0079A410, 102);
    //patch.WriteU32((void *)0x0079A414, 104);
    patch.WriteU32((void *)0x0079A418, 103);
    patch.WriteU32((void *)0x0079A41C, 0);
    patch.WriteU32((void *)0x0079A420, 0);
    patch.WriteU32((void *)0x0079A424, 0);

    patch.WriteU32((void *)0x0079A4B0, 101); // SI armor module
    patch.WriteU32((void *)0x0079A4B4, 103);
    patch.WriteU32((void *)0x0079A4B8, 106);
    patch.WriteU32((void *)0x0079A4BC, 105);
    patch.WriteU32((void *)0x0079A4C0, 0);
    patch.WriteU32((void *)0x0079A4C4, 0);
    patch.WriteU32((void *)0x0079A4C8, 0);
    patch.WriteU32((void *)0x0079A4CC, 0);

    patch.WriteU32((void *)0x0079A474, 78); // SI energy module
    patch.WriteU32((void *)0x0079A478, 79);
    patch.WriteU32((void *)0x0079A47C, 81);
    patch.WriteU32((void *)0x0079A480, 82);
    patch.WriteU32((void *)0x0079A484, 80);
    patch.WriteU32((void *)0x0079A488, 83);
    patch.WriteU32((void *)0x0079A48C, 84);
    patch.WriteU32((void *)0x0079A490, 108);
    patch.WriteU32((void *)0x0079A494, 120);
    patch.WriteU32((void *)0x0079A498, 104);
    patch.WriteU32((void *)0x0079A49C, 102);
    patch.WriteU32((void *)0x0079A4A0, 0);

    patch.WriteU32((void *)0x0079A564, 95); // SI supertech module
    patch.WriteU32((void *)0x0079A568, 96);
    patch.WriteU32((void *)0x0079A56C, 98);
    patch.WriteU32((void *)0x0079A570, 100);
    patch.WriteU32((void *)0x0079A574, 75);
    patch.WriteU32((void *)0x0079A578, 76);
    patch.WriteU32((void *)0x0079A57C, 77);

    patch.WriteU32((void *)0x0079A528, 68); // SI intelligence module
    patch.WriteU32((void *)0x0079A52C, 69);
    patch.WriteU32((void *)0x0079A530, 73);
    patch.WriteU32((void *)0x0079A534, 70);
    patch.WriteU32((void *)0x0079A538, 71);
    patch.WriteU32((void *)0x0079A53C, 72);
    patch.WriteU32((void *)0x0079A540, 114);
    patch.WriteU32((void *)0x0079A544, 119);
    patch.WriteU32((void *)0x0079A548, 74);
    patch.WriteU32((void *)0x0079A54C, 144);
    patch.WriteU32((void *)0x0079A550, 97);
    patch.WriteU32((void *)0x0079A554, 117);
    patch.WriteU32((void *)0x0079A558, 99);
    patch.WriteU32((void *)0x0079A55C, 0);
    patch.WriteU32((void *)0x0079A560, 0);

    //patch.WriteU32((void *)0x0079A4EC, 85); // SI structure module
    //patch.WriteU32((void *)0x0079A4F0, 88);
    //patch.WriteU32((void *)0x0079A4F4, 89);
    //patch.WriteU32((void *)0x0079A4F8, 86);
    //patch.WriteU32((void *)0x0079A4FC, 87);
    //patch.WriteU32((void *)0x0079A500, 91);
    //patch.WriteU32((void *)0x0079A504, 90);
    //patch.WriteU32((void *)0x0079A508, 93);
    //patch.WriteU32((void *)0x0079A50C, 92);
    //patch.WriteU32((void *)0x0079A510, 121);
    //patch.WriteU32((void *)0x0079A514, 123);
    //patch.WriteU32((void *)0x0079A518, 94);
    patch.WriteU32((void *)0x0079A51C, 107);

    return true;
}

static bool SiResearchModulesReduce(Patcher::SPatch &patch)
{
    patch.WriteByte((void *)0x004E7FE1, 25); // find module for research

    patch.WriteByte((void *)0x004C03F9, 25);        // find module for research
    patch.WriteByte((void *)0x004E7FF3, 100);       //
    patch.WriteByte((void *)0x004E7FF7, 100);       //
    patch.WriteU32((void *)0x004E7FFA, 0x0079A654); // upper adress limit check

    patch.WriteU32((void *)0x004E3272, 0xFFFE5C80); // module_id diff from base *3 -> *5
    patch.WriteU32((void *)0x004E328C, 0xFFFE5C80); // module_id diff from base *3 -> *5

    patch.WriteU32((void *)0x004C03CE, 0xFFFE5C80); // module_id diff from base *3 -> *5
    patch.WriteU32((void *)0x004C03E5, 0xFFFE5C80); // module_id diff from base *3 -> *5
    patch.WriteByte((void *)0x004E329E, 25);        //

    // MODULES RESEARCH LISTS BIG
    patch.WriteU32((void *)0x0079A3FC, 109); // SI speed module
    patch.WriteU32((void *)0x0079A400, 110);
    patch.WriteU32((void *)0x0079A404, 101);
    patch.WriteU32((void *)0x0079A408, 106);
    patch.WriteU32((void *)0x0079A40C, 105);
    patch.WriteU32((void *)0x0079A410, 102);
    patch.WriteU32((void *)0x0079A414, 104);
    patch.WriteU32((void *)0x0079A418, 103);
    patch.WriteU32((void *)0x0079A41C, 78);
    patch.WriteU32((void *)0x0079A420, 79);
    patch.WriteU32((void *)0x0079A424, 80);
    patch.WriteU32((void *)0x0079A428, 81);
    patch.WriteU32((void *)0x0079A42C, 82);
    patch.WriteU32((void *)0x0079A430, 83);
    patch.WriteU32((void *)0x0079A434, 84);
    patch.WriteU32((void *)0x0079A438, 108);
    patch.WriteU32((void *)0x0079A43C, 120);
    patch.WriteU32((void *)0x0079A440, 0);
    patch.WriteU32((void *)0x0079A448, 0);

    patch.WriteU32((void *)0x0079A58C, 85); // SI structure module
    patch.WriteU32((void *)0x0079A590, 86);
    patch.WriteU32((void *)0x0079A594, 87);
    patch.WriteU32((void *)0x0079A598, 88);
    patch.WriteU32((void *)0x0079A59C, 89);
    patch.WriteU32((void *)0x0079A5A0, 90);
    patch.WriteU32((void *)0x0079A5A4, 91);
    patch.WriteU32((void *)0x0079A5A8, 92);
    patch.WriteU32((void *)0x0079A5AC, 93);
    patch.WriteU32((void *)0x0079A5B0, 94);
    patch.WriteU32((void *)0x0079A5B4, 107);
    patch.WriteU32((void *)0x0079A5B8, 123);
    patch.WriteU32((void *)0x0079A5BC, 111);
    patch.WriteU32((void *)0x0079A5C0, 112);
    patch.WriteU32((void *)0x0079A5C4, 115);
    patch.WriteU32((void *)0x0079A5C8, 124);
    patch.WriteU32((void *)0x0079A5CC, 116);
    patch.WriteU32((void *)0x0079A5D0, 113);
    patch.WriteU32((void *)0x0079A5D4, 118);
    patch.WriteU32((void *)0x0079A5D8, 122);
    patch.WriteU32((void *)0x0079A5DC, 125);
    patch.WriteU32((void *)0x0079A5E0, 126);
    patch.WriteU32((void *)0x0079A5E4, 0);

    patch.WriteU32((void *)0x0079A654, 95); // SI supertech module
    patch.WriteU32((void *)0x0079A658, 96);
    patch.WriteU32((void *)0x0079A65C, 98);
    patch.WriteU32((void *)0x0079A660, 100);
    patch.WriteU32((void *)0x0079A664, 75);
    patch.WriteU32((void *)0x0079A668, 76);
    patch.WriteU32((void *)0x0079A66C, 77);
    patch.WriteU32((void *)0x0079A670, 68);
    patch.WriteU32((void *)0x0079A674, 69);
    patch.WriteU32((void *)0x0079A678, 70);
    patch.WriteU32((void *)0x0079A67C, 71);
    patch.WriteU32((void *)0x0079A680, 72);
    patch.WriteU32((void *)0x0079A684, 73);
    patch.WriteU32((void *)0x0079A688, 74);
    patch.WriteU32((void *)0x0079A68C, 114);
    patch.WriteU32((void *)0x0079A690, 119);
    patch.WriteU32((void *)0x0079A694, 97);
    patch.WriteU32((void *)0x0079A698, 99);
    patch.WriteU32((void *)0x0079A69C, 117);

    return true;
}

static bool SiResearchModulesReduce2(Patcher::SPatch &patch)
{
    patch.WriteByte((void *)0x004E7FE1, 75); // find module for research

    patch.WriteByte((void *)0x004C03F9, 75);        // find module for research

    //patch.WriteByte((void *)0x004E7FF3, 100);       //
    //patch.WriteByte((void *)0x004E7FF7, 100);       //
    patch.WriteJumpSized(SIModulesAllInOne_Jmp, 7, (unsigned long)SIModulesAllInOne);

    //patch.WriteU32((void *)0x004E7FFA, 0x0079A654);         // upper adress limit check
    patch.WriteU32((void *)0x004E7FFA, 0x0079A528); // upper adress limit check
    
    //patch.WriteU32((void *)0x004E3272, 0xFFFE5C80); // module_id diff from base *3 -> *5
    patch.WriteU32((void *)0x004E328B, 0xFB148084); // module_id diff from base *3 -> *5
    patch.WriteJumpSized(SIModulesAllInOne2_Jmp, 7, (unsigned long)SIModulesAllInOne2);

    //patch.WriteU32((void *)0x004C03CE, 0xFFFE5C80); // module_id diff from base *3 -> *5
    patch.WriteU32((void *)0x004C03E4, 0xFB148084); // module_id diff from base *3 -> *5
    patch.WriteJumpSized(SIModulesAllInOne3_Jmp, 7, (unsigned long)SIModulesAllInOne3);

    patch.WriteByte((void *)0x004E329E, 75);        //

    // MODULES RESEARCH LISTS BIG
    patch.WriteU32((void *)0x0079A3FC, 109); // SI speed module
    patch.WriteU32((void *)0x0079A400, 110);
    patch.WriteU32((void *)0x0079A404, 101);
    patch.WriteU32((void *)0x0079A408, 106);
    patch.WriteU32((void *)0x0079A40C, 105);
    patch.WriteU32((void *)0x0079A410, 102);
    patch.WriteU32((void *)0x0079A414, 104);
    patch.WriteU32((void *)0x0079A418, 103);
    patch.WriteU32((void *)0x0079A41C, 78);
    patch.WriteU32((void *)0x0079A420, 79);
    patch.WriteU32((void *)0x0079A424, 80);
    patch.WriteU32((void *)0x0079A428, 81);
    patch.WriteU32((void *)0x0079A42C, 82);
    patch.WriteU32((void *)0x0079A430, 83);
    patch.WriteU32((void *)0x0079A434, 84);
    patch.WriteU32((void *)0x0079A438, 108);
    patch.WriteU32((void *)0x0079A43C, 120);

    patch.WriteU32((void *)0x0079A440, 85); // SI structure module
    patch.WriteU32((void *)0x0079A444, 86);
    patch.WriteU32((void *)0x0079A448, 87);
    patch.WriteU32((void *)0x0079A44C, 88);
    patch.WriteU32((void *)0x0079A450, 89);
    patch.WriteU32((void *)0x0079A454, 90);
    patch.WriteU32((void *)0x0079A458, 91);
    patch.WriteU32((void *)0x0079A45C, 92);
    patch.WriteU32((void *)0x0079A460, 93);
    patch.WriteU32((void *)0x0079A464, 94);
    patch.WriteU32((void *)0x0079A468, 107);
    patch.WriteU32((void *)0x0079A46C, 123);
    patch.WriteU32((void *)0x0079A470, 111);
    patch.WriteU32((void *)0x0079A474, 112);
    patch.WriteU32((void *)0x0079A478, 115);
    patch.WriteU32((void *)0x0079A47C, 124);
    patch.WriteU32((void *)0x0079A480, 116);
    patch.WriteU32((void *)0x0079A484, 113);
    patch.WriteU32((void *)0x0079A488, 118);
    patch.WriteU32((void *)0x0079A48C, 122);
    patch.WriteU32((void *)0x0079A490, 125);
    patch.WriteU32((void *)0x0079A494, 126);
    patch.WriteU32((void *)0x0079A498, 117);

    patch.WriteU32((void *)0x0079A49C, 95); // SI supertech module
    patch.WriteU32((void *)0x0079A4A0, 96);
    patch.WriteU32((void *)0x0079A4A4, 98);
    patch.WriteU32((void *)0x0079A4A8, 100);
    patch.WriteU32((void *)0x0079A4AC, 75);
    patch.WriteU32((void *)0x0079A4B0, 76);
    patch.WriteU32((void *)0x0079A4B4, 77);
    patch.WriteU32((void *)0x0079A4B8, 68);
    patch.WriteU32((void *)0x0079A4BC, 69);
    patch.WriteU32((void *)0x0079A4C0, 70);
    patch.WriteU32((void *)0x0079A4C4, 71);
    patch.WriteU32((void *)0x0079A4C8, 72);
    patch.WriteU32((void *)0x0079A4CC, 73);
    patch.WriteU32((void *)0x0079A4D0, 74);
    patch.WriteU32((void *)0x0079A4D4, 114);
    patch.WriteU32((void *)0x0079A4D8, 119);
    patch.WriteU32((void *)0x0079A4DC, 97);
    patch.WriteU32((void *)0x0079A4E0, 99);

    // + script 

    return true;
}

static bool AI2021Сompatible(Patcher::SPatch &patch)
{
    // AI-2021 - compatible
patch.WriteU32((void *)0x007E59A8, 10); // Mining upgrade silicon si time
patch.WriteU32((void *)0x007E5DF8, 10); // WS Capture time
patch.WriteU32((void *)0x007E5DB8, 10); // BO Capture time
patch.WriteU32((void *)0x007E5D78, 10); // SI Capture time
patch.WriteU32((void *)0x007E5B58, 10); // SI TRPEVADE time

patch.WriteByte((void *)0x0079902B, 1); // Mining upgrade silicon si
patch.WriteByte((void *)0x00799070, 1); // WS Capture upg
patch.WriteByte((void *)0x0079906C, 1); // BO Capture upg
patch.WriteByte((void *)0x007BFBF8, 1); // SI Capture upg
patch.WriteByte((void *)0x007BFBD6, 1); // SI TRPEVADE unavailable
patch.WriteByte((void *)0x007BFBCF, 1); // SI IONARMOR unavailable
patch.WriteByte((void *)0x007BFBB8, 1); // SI UPG NRG MINE unavailable
patch.WriteByte((void *)0x007BFBE1, 1); // SI DPTRANGE unavailable

    return true;
}

static bool EnableFog(Patcher::SPatch &patch)
{
    patch.WriteU16((void *)OpenMap_Jmp, 0x558B);
    patch.WriteU32((void *)OpenMap_Jmp_2, 0x104D8B18);
    patch.WriteByte((void *)0x00553B9E, 0x52);      // Call open cell view disable
    patch.WriteU32((void *)0x00553B9F, 0x50575153); // Call open cell view disable
    patch.WriteU32((void *)0x00553BA3, 0xEAEFCEE8); // Call open cell view disable
    patch.WriteU32((void *)0x00553BA7, 0x14C483FF); // Call open cell view disable
    return true;
}

static bool Experimental2(Patcher::SPatch &patch)
{   
    // Unlock Turrets Range 8->10
    patch.WriteByte((void *)0x004C3CC2, 246);
    patch.WriteByte((void *)0x004C3CF0, 246);
    patch.WriteByte((void *)0x004C3CF3, 10);
    patch.WriteByte((void *)0x004C3CC5, 10);
    patch.WriteByte((void *)0x004C426F, 10);
    patch.WriteByte((void *)0x004C4281, 10);

    // No dodge
    patch.WriteU32((void *)0x004612D5, 1); // Dodge flag set 1
    patch.WriteJumpSized(DodgeFlagSet2_Jmp, 6, (unsigned long)DodgeFlagSet2);
    patch.WriteJumpSized(DodgeFlagSet3_Jmp, 6, (unsigned long)DodgeFlagSet3);
    patch.WriteJumpSized(DodgeFlagSet4_Jmp, 6, (unsigned long)DodgeFlagSet4);
    patch.WriteJumpSized(DodgeFlagSet5_Jmp, 10, (unsigned long)DodgeFlagSet5);
    patch.WriteJumpSized(DodgeFlagSet6_Jmp, 6, (unsigned long)DodgeFlagSet6);
    patch.WriteU16((void *)0x00460BED, 0); // Dodge distance 1
    patch.WriteU16((void *)0x00460C95, 0); // Dodge distance 2
    patch.WriteU16((void *)0x00460C6A, 0); // Dodge distance 3
    patch.WriteByte((void *)0x00489B49, 7); // Aggro distance 1
    patch.WriteByte((void *)0x00489B51, 7); // Aggro distance 2
    
    

    // TURRETS RANGE
    patch.WriteByte((void *)0x00792208, 10); // HF_Canon first range
    patch.WriteByte((void *)0x00792218, 10); // STOLp first range
    patch.WriteByte((void *)0x00792338, 10); // Plasma_Canon first range

    patch.WriteByte((void *)0x00792288, 10); // Light_Laser first range
    patch.WriteByte((void *)0x007922C8, 10); // Heavy_Laser first range
    patch.WriteByte((void *)0x00792298, 10); // Magnetic_Mine_Launcher first range
    patch.WriteByte((void *)0x007922A0, 7); // Magnetic_Mine_Launcher mines first range

    patch.WriteByte((void *)0x007922D8, 10); // EM_Launcher first range
    patch.WriteByte((void *)0x007924D8, 10); // Pulsar first range
    patch.WriteU32((void *)0x00792498, 10);  // DPT range 1
    patch.WriteByte((void *)0x00792488, 8); // Gas_Canon first range
    //patch.WriteByte((void *)0x007924A8, 8); // Ion_Reflector first range
    patch.WriteByte((void *)0x00792538, 10); // Parcher first range

    // TURRETS HP
    patch.WriteU32((void *)0x007E420C, 1300); // HF_Canon HP
    patch.WriteU32((void *)0x007E4210, 1300); // HF_Canon HP
    patch.WriteU32((void *)0x007E4218, 1700); // STOLp HP
    patch.WriteU32((void *)0x007E421C, 1700); // STOLp HP

    patch.WriteU32((void *)0x007E426C, 1200); // Light_Laser HP
    patch.WriteU32((void *)0x007E4270, 1200); // Light_Laser HP
    patch.WriteU32((void *)0x007E429C, 1600); // Heavy_Laser HP
    patch.WriteU32((void *)0x007E42A0, 1600); // Heavy_Laser HP
    patch.WriteU32((void *)0x007E4278, 1800); // Magnetic_Mine_Launcher HP
    patch.WriteU32((void *)0x007E427C, 1800); // Magnetic_Mine_Launcher HP
    patch.WriteU32((void *)0x007E25F8, 1500); // Magnetic_Mine_Launcher metal
    patch.WriteU32((void *)0x007E25FC, 1500); // Magnetic_Mine_Launcher metal
    patch.WriteU32((void *)0x007E2600, 1500); // Magnetic_Mine_Launcher metal

    patch.WriteU32((void *)0x007E42A8, 1400); // E/M HP
    patch.WriteU32((void *)0x007E42AC, 1400); // E/M HP

    patch.WriteU32((void *)0x007E4428, 1100); // Pulsar HP
    patch.WriteU32((void *)0x007E442C, 1100); // Pulsar HP
    patch.WriteU32((void *)0x007E4430, 1100); // Pulsar HP
    patch.WriteU32((void *)0x007E43EC, 1300); // Gas_Canon HP (vanilla 1100)
    patch.WriteU32((void *)0x007E43F0, 1300); // Gas_Canon HP (vanilla 1100)
    patch.WriteU32((void *)0x007E43F4, 1300); // Gas_Canon HP (vanilla 1100)
    patch.WriteU32((void *)0x007E429C, 1500); // DPT HP
    patch.WriteU32((void *)0x007E42A0, 1500); // DPT HP
    patch.WriteU32((void *)0x007E42A4, 1500); // DPT HP
    // patch.WriteU32((void *)0x007E43E0, 600);  // Soliton oscilator HP
    // patch.WriteU32((void *)0x007E43E4, 600);  // Soliton oscilator HP
    // patch.WriteU32((void *)0x007E43E8, 600);  // Soliton oscilator HP
   


    patch.WriteJumpSized(ChangeSubsRange_Jmp, 7, (unsigned long)ChangeSubsRange);

    return true;
}


static bool ShiftQueue(Patcher::SPatch &patch)
{   
    // Shift for order queue (desync issue)
 patch.WriteNops((void *)0x0040B570, 8); // 8 Null bytes
 //patch.WriteJumpSized(SkipStopResetOrderMove_Move_Jmp, 5, (unsigned long)SkipStopResetOrderMove_Move); 
 patch.WriteJumpSized(SkipStopResetOrderIdle_Build_Jmp, 5, (unsigned long)SkipStopResetOrderIdle_Build);
 patch.WriteJumpSized(SkipStopResetOrderBuild_Build_Jmp, 5, (unsigned long)SkipStopResetOrderBuild_Build);
 //patch.WriteJumpSized(EnableShiftAltInput_Jmp, 5, (unsigned long)EnableShiftAltInput); 
 patch.WriteJumpSized(FakeNoShiftForQueue_Jmp, 6, (unsigned long)FakeNoShiftForQueue); 
 patch.WriteJumpSized(DontEraseOldOrder_jmp, 6, (unsigned long)DontEraseOldOrder);
 patch.WriteJumpSized(AppendOrderInsteadOfReplace_Jmp, 8, (unsigned long)AppendOrderInsteadOfReplace); 
 patch.WriteJumpSized(OrderEndProcedure_Jmp, 7, (unsigned long)OrderEndProcedure); 
 patch.WriteNops((void *)0x0045FC0D, 32); // Don't destroy order after completion
 patch.WriteNops((void *)0x0045EFEB, 19); // Nop for new build order with shift
 patch.WriteJumpSized(NewBuildOrderWithShift_Jmp, 6, (unsigned long)NewBuildOrderWithShift);
 patch.WriteJumpSized(PtrDistanceToTargetWithShift_Jmp, 6, (unsigned long)PtrDistanceToTargetWithShift);
 patch.WriteJumpSized(DontResetOrderWhenChanged_Jmp, 8, (unsigned long)DontResetOrderWhenChanged);
 patch.WriteJumpSized(DontResetOrderWhenChanged2x2_Jmp, 9, (unsigned long)DontResetOrderWhenChanged2x2);
 patch.WriteJumpSized(CheckMyFlagToNotMakeNewOrder_Jmp, 5, (unsigned long)CheckMyFlagToNotMakeNewOrder);
 patch.WriteJumpSized(CheckNestedOrderToNotCheckDistance_Jmp, 7, (unsigned long)CheckNestedOrderToNotCheckDistance);
 patch.WriteJumpSized(CheckNestedOrderToNotDestroyNextStep_Jmp, 5, (unsigned long)CheckNestedOrderToNotDestroyNextStep);
 patch.WriteJumpSized(DontCalculateNextStep_Jmp, 5, (unsigned long)DontCalculateNextStep);
 patch.WriteJumpSized(DontOverwriteBuildState_Jmp, 6, (unsigned long)DontOverwriteBuildState);
 patch.WriteJumpSized(DontCheckCellOccupation_Jmp, 6, (unsigned long)DontCheckCellOccupation);
 patch.WriteJumpSized(ExitAfterWriteOrder_Jmp, 6, (unsigned long)ExitAfterWriteOrder);
 //patch.WriteJumpSized(DontCheckCellCenterFlag_Jmp, 6, (unsigned long)DontCheckCellCenterFlag);
 patch.WriteJumpSized(DontOverwriteTargetGPS_Jmp, 5, (unsigned long)DontOverwriteTargetGPS);
 patch.WriteJumpSized(DontOverwriteTargetCell_Jmp, 5, (unsigned long)DontOverwriteTargetCell);
 //patch.WriteJumpSized(DefineInitiateBuildingMoment_Jmp, 5, (unsigned long)DefineInitiateBuildingMoment);
 patch.WriteJumpSized(ReplaceSubGpsToOrderWithShift_Jmp, 8, (unsigned long)ReplaceSubGpsToOrderWithShift);
 patch.WriteJumpSized(ReplaceOrderGpsToOrderWithShift_Jmp, 5, (unsigned long)ReplaceOrderGpsToOrderWithShift);
 patch.WriteJumpSized(ReplaceOrderGpsToOrderWithShiftRmk_Jmp, 8, (unsigned long)ReplaceOrderGpsToOrderWithShiftRmk);
 patch.WriteNops((void *)0x0040B909, 6); // Nops
 patch.WriteJumpSized(AlwaysJumpToRightOrderCreation_Jmp, 6, (unsigned long)AlwaysJumpToRightOrderCreation); 
 

 patch.WriteJumpSized(PrepareMailNewCommandType_Jmp, 5, (unsigned long)PrepareMailNewCommandType);
 patch.WriteByte((void *)0x0054F127, 10); // New command (36) jumptable for command size = 16
 patch.WriteByte((void *)0x00438726, 10);
 patch.WriteByte((void *)0x00499498, 8);
 
 patch.WriteJumpSized(SendMailNewCommandType_Jmp, 5, (unsigned long)SendMailNewCommandType);
 patch.WriteJumpSized(AddInfoMailNewCommandType_Jmp, 7, (unsigned long)AddInfoMailNewCommandType);

    return true;
}


static bool BigBuildingHP(Patcher::SPatch &patch)
{
    patch.WriteU32((void *)0x007E41D0, 1000); // WS Metal
    patch.WriteU32((void *)0x007E417C, 4000); // Dockyard_WS HP
    patch.WriteU32((void *)0x007E4188, 3000); // Docks_WS HP
    patch.WriteU32((void *)0x007E4194, 2400); // WS Arsenal HP
    patch.WriteU32((void *)0x007E41A0, 2000); // Lab_WS HP
    patch.WriteU32((void *)0x007E41E8, 1600); // WS Depot
    patch.WriteU32((void *)0x007E41D0, 1000); // WS Corium extractor
    patch.WriteU32((void *)0x007E41DC, 1000); // WS Gold extractor
    patch.WriteU32((void *)0x007E41AC, 1600); // WS Sonar
    patch.WriteU32((void *)0x007E41B8, 3000); // WS Teleport
    patch.WriteU32((void *)0x007E41F4, 1400); // WS Infocenter
    patch.WriteU32((void *)0x007E4224, 1200); // WS Cybercenter
    patch.WriteU32((void *)0x007E4248, 1600); // WS Psychotron
    patch.WriteU32((void *)0x007E424C, 1600); // BO Psychotron
    patch.WriteU32((void *)0x007E4200, 1600); // WS Disperser
    patch.WriteU32((void *)0x007E4204, 1600); // BO Disperser
    patch.WriteU32((void *)0x007E4254, 1400); // WS Plasmatron
    patch.WriteU32((void *)0x007E4258, 1400); // BO Plasmatron
    patch.WriteU32((void *)0x007E425C, 1400); // SI Plasmatron
    patch.WriteU32((void *)0x007E4260, 1200); // WS Nuke
    patch.WriteU32((void *)0x007E4264, 1200); // BO Nuke
    patch.WriteU32((void *)0x007E4268, 1200); // SI Nuke
    patch.WriteU32((void *)0x007E42D8, 1000); // WS Metal extractor
    patch.WriteU32((void *)0x007E42DC, 1000); // BO Metal extractor
    patch.WriteU32((void *)0x007E42E4, 1000); // WS Oxygen generator
    patch.WriteU32((void *)0x007E42E8, 1000); // BO Oxygen generator
    patch.WriteU32((void *)0x007E42FC, 2000); // WS Market
    patch.WriteU32((void *)0x007E4300, 2000); // BO Market
    patch.WriteU32((void *)0x007E4230, 1000); // WS Shark control
    patch.WriteU32((void *)0x007E4234, 1000); // BO Shark control
    patch.WriteU32((void *)0x007E4458, 1400); // WS Teleshield
    patch.WriteU32((void *)0x007E445C, 1400); // BO Teleshield
    
    //patch.WriteU32((void *)0x007E423C, 1000); // WS USG

    
    patch.WriteU32((void *)0x007E41D4, 1000); // BO Metal
    patch.WriteU32((void *)0x007E4180, 4000); // Dockyard_BO HP
    patch.WriteU32((void *)0x007E418C, 3000); // Docks_BO HP
    patch.WriteU32((void *)0x007E4198, 2400); // BO Arsenal HP
    patch.WriteU32((void *)0x007E41A4, 2000); // Lab_BO HP
    patch.WriteU32((void *)0x007E41EC, 1600); // BO Depot
    patch.WriteU32((void *)0x007E41D4, 1000); // BO Corium extractor
    patch.WriteU32((void *)0x007E41E0, 1000); // BO Gold extractor
    patch.WriteU32((void *)0x007E41B0, 1600); // BO Sonar
    patch.WriteU32((void *)0x007E41BC, 3000); // BO Teleport
    patch.WriteU32((void *)0x007E41F8, 1400); // BO Infocenter
    patch.WriteU32((void *)0x007E42B4, 1000); // WS Protective field gen
    patch.WriteU32((void *)0x007E42B8, 1000); // BO Protective field gen
    patch.WriteU32((void *)0x007E42C0, 1600); // WS Force field
    patch.WriteU32((void *)0x007E42C4, 1600); // BO Force field
    patch.WriteU32((void *)0x007E4284, 1000); // WS Power station
    patch.WriteU32((void *)0x007E4288, 1000); // BO Power station
    patch.WriteU32((void *)0x007E4290, 1000); // WS Cyber laboratory dolphins
    patch.WriteU32((void *)0x007E4294, 1000); // BO Cyber laboratory dolphins
    patch.WriteU32((void *)0x007E42CC, 1000); // WS lasbomb launcher
    patch.WriteU32((void *)0x007E42D0, 1000); // BO lasbomb launcher
    patch.WriteU32((void *)0x007E42D4, 1000); // SI lasbomb launcher


    patch.WriteU32((void *)0x007E43DC, 1200); // Silicon_Extractor HP
    patch.WriteU32((void *)0x007E4310, 4000); // SI Command Hub HP
    patch.WriteU32((void *)0x007E4370, 2400); // SI Arsenal HP
    patch.WriteU32((void *)0x007E437C, 3600); // SI Protoplasm_Generator HP
    patch.WriteU32((void *)0x007E41D8, 1000); // SI Corium extractor
    patch.WriteU32((void *)0x007E41C0, 3000); // SI Teleport

    patch.WriteU32((void *)0x007E431C, 1000); // SI Module
    patch.WriteU32((void *)0x007E4328, 1000); // SI Module
    patch.WriteU32((void *)0x007E4334, 1000); // SI Module
    patch.WriteU32((void *)0x007E4340, 1000); // SI Module
    patch.WriteU32((void *)0x007E434C, 1000); // SI Module
    patch.WriteU32((void *)0x007E4358, 1000); // SI Module
    patch.WriteU32((void *)0x007E4364, 1000); // SI Module

    patch.WriteU32((void *)0x007E4388, 1400); // SI Biolocator
    patch.WriteU32((void *)0x007E438C, 1000); // SI Corium extractor
    patch.WriteU32((void *)0x007E4390, 1000); // SI Corium extractor
    patch.WriteU32((void *)0x007E4394, 1000); // SI Corium extractor
    patch.WriteU32((void *)0x007E43A0, 2400); // SI Energy converter
    patch.WriteU32((void *)0x007E43AC, 1000); // SI Corium silo
    patch.WriteU32((void *)0x007E43B8, 1600); // SI Energy accumulator
    patch.WriteU32((void *)0x007E43C4, 1400); // SI Replenish pod
    patch.WriteU32((void *)0x007E43D0, 2200); // SI Recyclotron
    patch.WriteU32((void *)0x007E443C, 2600); // SI Gate
    patch.WriteU32((void *)0x007E4448, 2000); // SI Ion field generator
    patch.WriteU32((void *)0x007E4454, 1800); // SI Molecular
    patch.WriteU32((void *)0x007E446C, 2400); // SI Orbital laser
    patch.WriteU32((void *)0x007E4484, 1400); // SI Vacuum_Bomb launcher
    patch.WriteU32((void *)0x007E4490, 1600); // SI Quantum Paralyzer
    
    //patch.WriteU32((void *)0x007E4478, 1400); // SI Parcher
    //patch.WriteU32((void *)0x007E43E0, 1400); // SI soliton oscillator
    
    
    
    
    return true;
}

typedef bool (*PatchFunction)(Patcher::SPatch &patch);
static const PatchFunction Patches[] = {
    //Yaml,
    //Put your patch functions here:     
    FixesQoL, 
    OneDepotFor2Mines,
    AimPrediction,
    BalancingTacticsTree,
    ResearchBuildingsLimit,
    Flagships,

    LobbyAnnouncements,
    
    AutosaveIPXNetGame,

    BigBuildingHP,
    SiResearchModulesReduce2,
    // ShiftQueue

    // Experimental2
    
    // EnableFog
    
    // EconomicsAndOther,
    
    // BalancingNormalTree,
   
    // AI2021Сompatible
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
    // Lock  .text
    if (!VirtualProtect(_BaseAddr + 0x1000, 0x33A000, _OldProtections[0], &tmp))
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
    if (!VirtualProtect(_BaseAddr + 0x33B000, 0x11F5F8, PAGE_READWRITE, &_OldProtections[1]))
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
