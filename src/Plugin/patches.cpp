#include "patches.h"
#include "config.h"
#include "Shared/Common.h"
#include "Shared/Patcher.h"
#include <windows.h>
#include "winhttp.h"
#include <string>

using namespace Common;
using namespace Patcher;


//std::wstring FileDirectory(Buffer);
//std::wstring full_path = FileDirectory + L"\\plugins\\config.ini";
//
//
//static LPCWSTR ini_file = full_path.c_str();

#pragma comment(lib, "winhttp.lib")

//wchar_t *convertCharArrayToLPCWSTR(const char *charArray)
//{
//    wchar_t *wString = new wchar_t[4096];
//    MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
//    return wString;
//}
//    
//LPCWSTR InitConfig()
//{
//    CHAR Buffer[MAX_PATH];
//    CHAR FullPath[MAX_PATH];
//    struct _WIN32_FIND_DATAA FindFileData;
//
//    auto result = GetCurrentDirectoryA(MAX_PATH, Buffer);
//    if (result)
//    {
//        lstrcatA(Buffer, "\\plugins\\*.ini");
//        auto hFind = FindFirstFileA(Buffer, &FindFileData);
//        if (hFind == INVALID_HANDLE_VALUE)
//        {
//            FullPath[0] = ' ';
//            FullPath[1] = '\0';
//        }
//        else
//        {
//            GetCurrentDirectoryA(MAX_PATH, FullPath);
//            lstrcatA(FullPath, "\\plugins\\");
//            lstrcatA(FullPath, FindFileData.cFileName);
//            FindClose(hFind);
//        }        
//    }
//    return convertCharArrayToLPCWSTR(FullPath);
//}

// Implement your patches here
//static bool AutosaveIPXNetGame(Patcher::SPatch &patch)
//{
//    
//    return true;
//}

static bool FixesQoL(Patcher::SPatch &patch) {
    // 1. config check
    //if (PluginConfig.StartZoneName.empty())
    //    return false;

#ifdef _DEBUG
    //MessageBoxA(NULL, "FlagshipsPatch LOL Debug", "", MB_OK);
#endif // _DEBUG

    auto ini_file = InitConfig();
    if (wcslen(ini_file) < 5)
        MessageBox(NULL, L"Config file not found, setting default unit parameters", L"d3drm", MB_ICONINFORMATION);
    

    // GENERAL
    patch.WriteJumpSized(ChangeGameVersion_Jmp, 5, (unsigned long)ChangeGameVersion);

    BYTE enable_autosave = GetPrivateProfileInt(L"Plugins", L"Autosave", FALSE, ini_file);
    if (enable_autosave)
    {
        patch.WriteJumpSized(AutosaveCheckTick_Jmp, 5, (unsigned long)AutosaveCheckTick);
        patch.WriteJumpSized(AutosaveCheckMarker_Jmp, 8, (unsigned long)AutosaveCheckMarker);
        patch.WriteJumpSized(AutosaveMakeFileName_Jmp, 5, (unsigned long)AutosaveMakeFileName);
        patch.WriteJumpSized(AutosaveDontCheckIfFileExists_Jmp, 5,(unsigned long)AutosaveDontCheckIfFileExists);
        // patch.WriteJumpSized(AutosaveCheckGameMode_Jmp, 7, (unsigned long)AutosaveCheckGameMode);
        patch.WriteJumpSized(AutosaveSkipToggleMenu_Jmp, 7, (unsigned long)AutosaveSkipToggleMenu);
        patch.WriteJumpSized(DontResetHostFlag_Jmp, 8, (unsigned long)DontResetHostFlag); 
    }

    patch.WriteU32((void *)0x004D4539, 0x8B04FAC1); // Take corium when finish building fix

    patch.WriteJumpSized(MinesDetectionWS_Jmp, 5, (unsigned long)MinesDetectionWS);
    patch.WriteJumpSized(MinesDetectionBO_Jmp, 5, (unsigned long)MinesDetectionBO);
    patch.WriteJumpSized(MinesDetectionSI_Jmp, 5, (unsigned long)MinesDetectionSI);

    bool enable_fog = GetPrivateProfileInt(L"Plugins", L"EnableFog", FALSE, ini_file);
    if (!enable_fog)
    {
        patch.WriteJumpSized(OpenMap_Jmp, 6, (unsigned long)OpenMap);
        patch.WriteNops((void *)0x00553B9E, 13); // Call open cell view disable
    }

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

    patch.WriteJumpSized(BoxCursorLoadCheck1_Jmp, 7, (unsigned long)BoxCursorLoadCheck1);
    patch.WriteJumpSized(BoxCursorLoadCheck2_Jmp, 10, (unsigned long)BoxCursorLoadCheck2);
    patch.WriteJumpSized(BoxCursorLoadCheck3_Jmp, 5, (unsigned long)BoxCursorLoadCheck3);

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
    patch.WriteJumpSized(FirstBuilderOxygen_Jmp, 6, (unsigned long)FirstBuilderOxygen);    
    
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
    patch.WriteJumpSized(OpenBldMenuOnSelection_Jmp, 5, (unsigned long)OpenBldMenuOnSelection);
    //patch.WriteNops((void *)0x0045FA94, 14); // fast rebuild waypoint on collision
    patch.WriteJumpSized(ContinueMoveSmallDelay_Jmp, 7, (unsigned long)ContinueMoveSmallDelay);
    patch.WriteJumpSized(NoCaptureAllyBuildings_Jmp, 6, (unsigned long)NoCaptureAllyBuildings);
    //patch.WriteJumpSized(AIGetMapSizeCase_Jmp, 5, (unsigned long)AIGetMapSizeCase);

    //patch.WriteJumpSized(NoOffsetFromMapBorderIfValue_Jmp, 5, (unsigned long)NoOffsetFromMapBorderIfValue);
    //patch.WriteJumpSized(AIPlaceBuildingNearUnsuitable_Jmp, 7, (unsigned long)AIPlaceBuildingNearUnsuitable);
    //patch.WriteNops((void *)0x00661221, 92); // AIPlaceBuildingNearUnsutable

    patch.WriteNops((void *)0x004BE758, 13); // DontChangeInterface object Name
    patch.WriteNops((void *)0x004BE768, 5); // DontChangeInterface object Name
    patch.WriteNops((void *)0x004BE773, 3); // DontChangeInterface object Name

    patch.WriteNops((void *)0x004623BF, 2); // fast change depth on attack


    // No dodge
    bool dodge = GetPrivateProfileInt(L"Dodge", L"Enabled", TRUE, ini_file);
    if (!dodge)
    {
        patch.WriteU32((void *)0x004612D5, 1); // Dodge flag set 1
        patch.WriteJumpSized(DodgeFlagSet2_Jmp, 6, (unsigned long)DodgeFlagSet2);
        patch.WriteJumpSized(DodgeFlagSet3_Jmp, 6, (unsigned long)DodgeFlagSet3);
        patch.WriteJumpSized(DodgeFlagSet4_Jmp, 6, (unsigned long)DodgeFlagSet4);
        patch.WriteJumpSized(DodgeFlagSet5_Jmp, 10, (unsigned long)DodgeFlagSet5);
        patch.WriteJumpSized(DodgeFlagSet6_Jmp, 6, (unsigned long)DodgeFlagSet6);
        patch.WriteU16((void *)0x00460BED, 0);  // Dodge distance 1
        patch.WriteU16((void *)0x00460C95, 0);  // Dodge distance 2
        patch.WriteU16((void *)0x00460C6A, 0);  // Dodge distance 3
        patch.WriteByte((void *)0x00489B49, 7); // Aggro distance 1
        patch.WriteByte((void *)0x00489B51, 7); // Aggro distance 2
    
    }

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
    patch.WriteJumpSized(AllySiliconMinesCheckPlacing_Jmp1, 6, (unsigned long)AllySiliconMinesCheckPlacing);
    patch.WriteJumpSized(AllySiliconMinesCheckPlacing_Jmp2, 6, (unsigned long)AllySiliconMinesCheckPlacing);
    patch.WriteJumpSized(AllySiliconMinesCheckPlacing_Jmp3, 5, (unsigned long)AllySiliconMinesCheckPlacing);

    // TURRETS RANGE
    patch.WriteU32((void *)0x00792498, GetPrivateProfileInt(L"Double_Plasma_Turret", L"Range_1", 8, ini_file));  // DPT range 1
    patch.WriteU32((void *)0x0079249C, GetPrivateProfileInt(L"Double_Plasma_Turret", L"Range_2", 10, ini_file)); // DPT range 2

    patch.WriteU32((void *)0x00792710, 121); // DPT range research id
    //
    
    patch.WriteU32((void *)0x007E6738, GetPrivateProfileInt(L"Weap_DoublePlasmaTurret", L"Damage_1", 100, ini_file)); // DPT turret damage T1
    patch.WriteU32((void *)0x007E673C, GetPrivateProfileInt(L"Weap_DoublePlasmaTurret", L"Damage_2", 120, ini_file)); // DPT turret damage T2
    patch.WriteU32((void *)0x007E6740, GetPrivateProfileInt(L"Weap_DoublePlasmaTurret", L"Damage_3", 160, ini_file)); // DPT turret damage T3

    patch.WriteU32((void *)0x007A8C90, 80); // Destroyer reload (vanilla 50)
    patch.WriteU32((void *)0x007E6620, 40);  // Destroyer damage T1 (vanilla 60)
    patch.WriteU32((void *)0x007E6624, 120); // Destroyer damage T2 (vanilla 150)

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


    patch.WriteU32((void *)0x007E615C, GetPrivateProfileInt(L"Depth_Mine", L"Production_time", 500, ini_file)); // Depth mine prodtime
    patch.WriteU32((void *)0x007E6170, GetPrivateProfileInt(L"Laser_Snare", L"Production_time", 500, ini_file)); // Laser snare prodtime
    patch.WriteU32((void *)0x007E6328, GetPrivateProfileInt(L"Acoustic_Mine", L"Production_time", 500, ini_file)); // Acoustic mines prodtime

     patch.WriteU32((void *)0x007E6168, GetPrivateProfileInt(L"Depth_Mine", L"Storage_arsenal", 20, ini_file)); // Depth mine storage arsenal
     patch.WriteU32((void *)0x007E617C, GetPrivateProfileInt(L"Laser_Snare", L"Storage_arsenal", 20, ini_file)); // Laser snare storage arsenal
     patch.WriteU32((void *)0x007E6334, GetPrivateProfileInt(L"Acoustic_Mine", L"Storage_arsenal", 20, ini_file));  // Acoustic mines storage arsenal

    patch.WriteJumpSized(UpgParcherDmg_Jmp, 5, (unsigned long)UpgParcherDmg);

    
    //patch.WriteU32((void *)0x004E5029, 2); // dispersion screen always detects invis (dep to radar)
    patch.WriteByte((void *)0x00483598, 0x74); // auto use paralyze ray
    

    // Multiplayer mode cheats
    // patch.WriteByte((void *)0x00521D4B, 2); // Cheat read gamemode check
    // patch.WriteByte((void *)0x00522898, 2); // Cheat read gamemode check 2

    // patch.WriteByte((void *)0x005F4CA3, ); // BHE base AoE

    // patch.WriteNops((void *)0x00642944, 2); // Medium torpedo 100% AOE dmg (vanilla  50%)
    // patch.WriteByte((void *)0x006382CB, 2); // Ripple effect strength (standard value)
    // patch.WriteU32((void *)0x007DFE00, 75); // STOLp reload (standard value)


    // BUILDINGS
    // BUILDTIME
    patch.WriteU32((void *)0x007E3E54, 625); // HF canon buildtime
    patch.WriteU32((void *)0x007E3E58, 625); // HF canon buildtime
    patch.WriteU32((void *)0x007E3E5C, 625); // HF canon buildtime

    patch.WriteU32((void *)0x007E3E60, 1000); // STOLp buildtime
    patch.WriteU32((void *)0x007E3E64, 1000); // STOLp buildtime
    patch.WriteU32((void *)0x007E3E68, 1000); // STOLp buildtime

    patch.WriteU32((void *)0x007E3E84, 1000); // USG buildtime
    patch.WriteU32((void *)0x007E3E88, 1000); // USG buildtime
    patch.WriteU32((void *)0x007E3E8C, 1000); // USG buildtime

    patch.WriteU32((void *)0x007E3F38, 875); // Plasma cannon buildtime
    patch.WriteU32((void *)0x007E3F3C, 875); // Plasma cannon buildtime
    patch.WriteU32((void *)0x007E3F40, 875); // Plasma cannon buildtime

    patch.WriteU32((void *)0x007E3EB4, 625); // Light laser buildtime
    patch.WriteU32((void *)0x007E3EB8, 625); // Light laser buildtime
    patch.WriteU32((void *)0x007E3EBC, 625); // Light laser buildtime

    patch.WriteU32((void *)0x007E3EE4, 875); // Heavy laser buildtime
    patch.WriteU32((void *)0x007E3EE8, 875); // Heavy laser buildtime
    patch.WriteU32((void *)0x007E3EEC, 875); // Heavy laser buildtime

    patch.WriteU32((void *)0x007E3EC0, 1125); // MML buildtime
    patch.WriteU32((void *)0x007E3EC4, 1125); // MML buildtime
    patch.WriteU32((void *)0x007E3EC8, 1125); // MML buildtime

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
    
    patch.WriteU32((void *)0x007C1620, GetPrivateProfileInt(L"Energy_converter", L"Corium_Buy_coeff", 10, ini_file));
    patch.WriteU32((void *)0x007C1624, GetPrivateProfileInt(L"Energy_converter", L"Corium_Sell_coeff", 2, ini_file));
    patch.WriteU32((void *)0x007C1628, GetPrivateProfileInt(L"Energy_converter", L"Silicon_Buy_coeff", 10, ini_file));
    patch.WriteU32((void *)0x007C162C, GetPrivateProfileInt(L"Energy_converter", L"Silicon_Sell_coeff", 50, ini_file));

    patch.WriteByte((void *)0x004D9A66, 20); // Gold mine storage
    patch.WriteJumpSized(GoldMineInterfaceAdjust_Jmp, 8, (unsigned long)GoldMineInterfaceAdjust);

    // Damage
    patch.WriteJumpSized(MediumTorpedoOnlyAoE_Jmp, 7, (unsigned long)MediumTorpedoOnlyAoE);

    patch.WriteU32((void *)0x007A8DA8, GetPrivateProfileInt(L"Bomber", L"Bombs_ammo", 45, ini_file));
    patch.WriteU32((void *)0x007A8DAC, GetPrivateProfileInt(L"Minelayer", L"Mines_ammo", 15, ini_file));
    patch.WriteU32((void *)0x007A8DDC, GetPrivateProfileInt(L"Defender", L"lasmines_ammo", 15, ini_file));
    patch.WriteU32((void *)0x007A8E1C, GetPrivateProfileInt(L"Bio_Assaulter", L"Mines_ammo", 5, ini_file));

    //patch.WriteByte((void *)0x00645E92, 0); // Cassete subshell check upgrade
    //patch.WriteU32((void *)0x007E66C0, 30); // Cassete subshell T1
    //patch.WriteU32((void *)0x007E66C4, 45); // Cassete subshell T2
    //patch.WriteU32((void *)0x007E66C8, 60); // Cassete subshell T3
    //patch.WriteU32((void *)0x007E66CC, 75); // Cassete subshell T4
    //patch.WriteU32((void *)0x007E66D0, 90); // Cassete subshell T5

    // REPAIR
    // WS
    patch.WriteU32((void *)0x007E29FC, 400);  // Repair_Docks repair cost WS
    patch.WriteU32((void *)0x007E0920, 100);  // Repair speed Sentinel dock
    patch.WriteU32((void *)0x007E0924, 225);  // Repair speed Hunter dock
    patch.WriteU32((void *)0x007E0928, 550);  // Repair speed Cruiser dock
    patch.WriteU32((void *)0x007E092C, 400);  // Repair speed DC Bomber dock
    patch.WriteU32((void *)0x007E0930, 325);  // Repair speed Minelayer dock
    patch.WriteU32((void *)0x007E0934, 325);  // Repair speed Marauder dock
    patch.WriteU32((void *)0x007E0938, 125);  // Repair speed Repair Platf dock
    patch.WriteU32((void *)0x007E093C, 200);  // Repair speed Transport dock
    patch.WriteU32((void *)0x007E0944, 500);  // Repair speed Terminator dock
    patch.WriteU32((void *)0x007E0948, 400);  // Repair speed Liberator dock
    patch.WriteU32((void *)0x007E094C, 250);  // Repair speed Builder WS dock
    patch.WriteU32((void *)0x007E08F4, 1500); // Repair speed Flagship WS dock
    
    patch.WriteU32((void *)0x007E0860, GetPrivateProfileInt(L"Sentinel", L"Metal", 400, ini_file) / 2);
    patch.WriteU32((void *)0x007E0864, GetPrivateProfileInt(L"Hunter", L"Metal", 400, ini_file) / 2);
    patch.WriteU32((void *)0x007E0868, GetPrivateProfileInt(L"Cruiser", L"Metal", 400, ini_file) / 2);
    patch.WriteU32((void *)0x007E086C, GetPrivateProfileInt(L"Bomber", L"Metal", 400, ini_file) / 2);
    patch.WriteU32((void *)0x007E0870, GetPrivateProfileInt(L"Minelayer", L"Metal", 400, ini_file) / 2);
    patch.WriteU32((void *)0x007E0874, GetPrivateProfileInt(L"Marauder", L"Metal", 400, ini_file) / 2);
    patch.WriteU32((void *)0x007E0878, GetPrivateProfileInt(L"Repair_Platform_WS", L"Metal", 400, ini_file) / 2);
    patch.WriteU32((void *)0x007E087C, GetPrivateProfileInt(L"Transport_Humans", L"Metal", 400, ini_file) / 2);
    patch.WriteU32((void *)0x007E0884, GetPrivateProfileInt(L"Terminator", L"Metal", 400, ini_file) / 2);
    patch.WriteU32((void *)0x007E0888, GetPrivateProfileInt(L"Liberator", L"Metal", 400, ini_file) / 2);
    patch.WriteU32((void *)0x007E088C, GetPrivateProfileInt(L"Builder_Humans", L"Metal", 400, ini_file) / 2);
    patch.WriteU32((void *)0x007E08F4, GetPrivateProfileInt(L"Flagship_WS", L"Metal", 400, ini_file) / 2);

    // BO
    patch.WriteU32((void *)0x007E2A00, 400);  // Repair_Docks repair cost BO

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

    patch.WriteU32((void *)0x007E08AC, GetPrivateProfileInt(L"Transport_Humans", L"Metal", 400, ini_file) / 2); 
    patch.WriteU32((void *)0x007E08A8, GetPrivateProfileInt(L"Repair_Platform_WS", L"Metal", 400, ini_file) / 2);
    patch.WriteU32((void *)0x007E08A4, GetPrivateProfileInt(L"Raider", L"Metal", 400, ini_file) / 2);
    patch.WriteU32((void *)0x007E08B4, GetPrivateProfileInt(L"Phantom", L"Metal", 400, ini_file) / 2);
    patch.WriteU32((void *)0x007E089C, GetPrivateProfileInt(L"Invader", L"Metal", 400, ini_file) / 2);
    patch.WriteU32((void *)0x007E0898, GetPrivateProfileInt(L"Heavy_Cruiser", L"Metal", 400, ini_file) / 2);
    patch.WriteU32((void *)0x007E0890, GetPrivateProfileInt(L"Fighter", L"Metal", 400, ini_file) / 2);
    patch.WriteU32((void *)0x007E0894, GetPrivateProfileInt(L"Destroyer", L"Metal", 400, ini_file) / 2);
    patch.WriteU32((void *)0x007E08A0, GetPrivateProfileInt(L"Defender", L"Metal", 400, ini_file) / 2);
    patch.WriteU32((void *)0x007E08BC, GetPrivateProfileInt(L"Builder_Humans", L"Metal", 400, ini_file) / 2);
    patch.WriteU32((void *)0x007E08B8, GetPrivateProfileInt(L"Avenger", L"Metal", 400, ini_file) / 2);
    patch.WriteU32((void *)0x007E08F8, GetPrivateProfileInt(L"Flagship_BO", L"Metal", 400, ini_file) / 2);

    
    patch.WriteByte((void *)0x004C8625, 4); // Repair speed shift - ALL BUILDINGS

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

    patch.WriteU32((void *)0x007BF558, GetPrivateProfileInt(L"Economics", L"Starting_gold_1", 500, ini_file)); // Starting gold t1
    patch.WriteU32((void *)0x007BF55C, GetPrivateProfileInt(L"Economics", L"Starting_gold_2", 1000, ini_file)); // Starting gold t2
    patch.WriteU32((void *)0x007BF560, GetPrivateProfileInt(L"Economics", L"Starting_gold_3", 1500, ini_file)); // Starting gold t3
    
    
    patch.WriteU32((void *)0x007BF57C, GetPrivateProfileInt(L"Economics", L"Starting_metal_1", 5000, ini_file)); // Starting metal t1
    patch.WriteU32((void *)0x007BF580, GetPrivateProfileInt(L"Economics", L"Starting_metal_2", 15000, ini_file)); // Starting metal t2
    patch.WriteU32((void *)0x007BF584, GetPrivateProfileInt(L"Economics", L"Starting_metal_3", 20000, ini_file)); // Starting metal t3
    
    patch.WriteU32((void *)0x007BF588, GetPrivateProfileInt(L"Economics", L"Starting_silicon_1", 5000, ini_file)); // Starting silicon t1
    patch.WriteU32((void *)0x007BF58C, GetPrivateProfileInt(L"Economics", L"Starting_silicon_2", 15000, ini_file)); // Starting silicon t2
    patch.WriteU32((void *)0x007BF590, GetPrivateProfileInt(L"Economics", L"Starting_silicon_3", 20000, ini_file)); // Starting silicon t3
    
    patch.WriteU32((void *)0x004E4199, GetPrivateProfileInt(L"Economics", L"Energy_storage_basic", 1000, ini_file)); // Energy storage basic
    
    patch.WriteU32((void *)0x007BF564, GetPrivateProfileInt(L"Economics", L"Starting_energy_1", 1000, ini_file)); // Starting energy t1
    patch.WriteU32((void *)0x007BF568, GetPrivateProfileInt(L"Economics", L"Starting_energy_2", 1500, ini_file)); // Starting energy t2
    patch.WriteU32((void *)0x007BF56C, GetPrivateProfileInt(L"Economics", L"Starting_energy_3", 2000, ini_file)); // Starting energy t3

    patch.WriteU32((void *)0x007BF570, GetPrivateProfileInt(L"Economics", L"Starting_corium_1", 500, ini_file)); // Starting corium t1
    patch.WriteU32((void *)0x007BF574, GetPrivateProfileInt(L"Economics", L"Starting_corium_2", 2000, ini_file)); // Starting corium t2
    patch.WriteU32((void *)0x007BF578, GetPrivateProfileInt(L"Economics", L"Starting_corium_3", 4000, ini_file)); // Starting corium t3

    patch.WriteU32((void *)0x00550CB0, 500); // Starting trade amount
    patch.WriteU32((void *)0x004C08CF, 0x903F4389); // mine interface short type fix

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

    patch.WriteByte((void *)0x00430881, 6); // Light torpedo jump to higher speed (-> 60)
    patch.WriteByte((void *)0x004308A3, 6); // Acid shell jump to higher speed (48 -> 60)
    patch.WriteByte((void *)0x004308A1, 4); // Energy shell jump to higher speed (-> 72)

    patch.WriteJumpSized(LasAbsorb2TimesLess_Jmp, 5, (unsigned long)LasAbsorb2TimesLess);
    patch.WriteJumpSized(LasAbsorbSubmarines_Jmp, 5, (unsigned long)LasAbsorbSubmarines);

    // for laser absorb submarines
    //0x004BB345
 
    patch.WriteByte((void *)0x004E4197, 5); // Replenish pod capacity (shift, result=4000)

    static DWORD ff_charge = GetPrivateProfileInt(L"Force_field", L"Charge", 5000, ini_file);
    static DWORD ff_charge_timer = GetPrivateProfileInt(L"Force_field", L"Charge_timer", 45, ini_file);
    
    patch.WriteU32((void *)0x004DEBA6, ff_charge);
    patch.WriteU32((void *)0x004DED31, ff_charge);
    patch.WriteU32((void *)0x004DED21, ff_charge);
    patch.WriteU32((void *)0x004C0309, pow(2,43)/ff_charge); // Power protector indicator adjust (2^43/10000)

    patch.WriteU32((void *)0x004DECE3, ff_charge_timer);
    patch.WriteU32((void *)0x004DECF1, ff_charge_timer*4); // No oxygen


    //PANEL
    //patch.WriteByte((void *)0x0048798F, 6); // SI patrol instead of move Skat, Escort, Dreadnaught
    //patch.WriteByte((void *)0x00487EE8, 6); // SI patrol instead of move Bioassaulter
    patch.WriteByte((void *)0x004879DA, 6); // SI patrol instead of move Usurper
    patch.WriteByte((void *)0x0044D59F, 6); // SI patrol instead of move Usurper group
    patch.WriteByte((void *)0x0044D68C, 6); // SI patrol instead of move Bioassaulter group
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
    patch.WriteU32((void *)0x007E43DC, 700);  // Silicon extractor HP (+100)
    patch.WriteU32((void *)0x007E417C, 3000); // WS Subcenter HP
    patch.WriteU32((void *)0x007E4180, 3000); // BO Subcenter HP
    patch.WriteU32((void *)0x007E4188, 2250); // WS Repair_Docks HP
    patch.WriteU32((void *)0x007E418C, 2250); // BO Repair_Docks HP
    patch.WriteU32((void *)0x007E4194, 1800); // WS Arsenal HP
    patch.WriteU32((void *)0x007E4198, 1800); // BO Arsenal HP
    patch.WriteU32((void *)0x007E41A0, 1500); // WS Research Center HP
    patch.WriteU32((void *)0x007E41A4, 1500); // BO Research Center HP
    patch.WriteU32((void *)0x007E4310, 2500); // SI Core HP
    patch.WriteU32((void *)0x007E4370, 1500); // SI Arsenal HP
    patch.WriteU32((void *)0x007E437C, 2250); // SI Protoplasm generator HP

    patch.WriteU32((void *)0x007E420C, 1200); // HF canon HP
    patch.WriteU32((void *)0x007E4210, 1200); // HF canon HP
    patch.WriteU32((void *)0x007E4214, 1200); // HF canon HP
    patch.WriteU32((void *)0x007E4218, 1600); // STOLp HP
    patch.WriteU32((void *)0x007E421C, 1600); // STOLp HP
    patch.WriteU32((void *)0x007E4220, 1600); // STOLp HP
    patch.WriteU32((void *)0x007E426C, 1000);  // Light laser HP
    patch.WriteU32((void *)0x007E4270, 1000);  // Light laser HP
    patch.WriteU32((void *)0x007E4274, 1000);  // Light laser HP
    //patch.WriteU32((void *)0x007E429C, 1300); // Heavy laser HP
    //patch.WriteU32((void *)0x007E42A0, 1300); // Heavy laser HP
    //patch.WriteU32((void *)0x007E42A4, 1300); // Heavy laser HP
    patch.WriteU32((void *)0x007E4428, 1000);  // Pulsar HP
    patch.WriteU32((void *)0x007E442C, 1000);  // Pulsar HP
    patch.WriteU32((void *)0x007E4430, 1000);  // Pulsar HP
    //patch.WriteU32((void *)0x007E43EC, 1200); // Gas cannon HP (vanilla 1100)
    //patch.WriteU32((void *)0x007E43F0, 1200); // Gas cannon HP (vanilla 1100)
    //patch.WriteU32((void *)0x007E43F4, 1200); // Gas cannon HP (vanilla 1100)
    patch.WriteU32((void *)0x007E441C, 900);  // Bio mine launcher HP
    patch.WriteU32((void *)0x007E4420, 900);  // Bio mine launcher HP
    patch.WriteU32((void *)0x007E4424, 900);  // Bio mine launcher HP
    //patch.WriteU32((void *)0x007E43E0, 600);  // Soliton oscilator HP
    //patch.WriteU32((void *)0x007E43E4, 600);  // Soliton oscilator HP
    //patch.WriteU32((void *)0x007E43E8, 600);  // Soliton oscilator HP

    // Corium
    // WS
    patch.WriteU32((void *)0x007E1CE0, 80); // HF cannon corium
    patch.WriteU32((void *)0x007E1CE4, 80); // HF cannon corium
    patch.WriteU32((void *)0x007E1CE8, 80); // HF cannon corium

    patch.WriteU32((void *)0x007E1CEC, 120); // STOLp corium
    patch.WriteU32((void *)0x007E1CF0, 120); // STOLp corium

    patch.WriteU32((void *)0x007E1D1C, 1000); // Psychotron corium
    patch.WriteU32((void *)0x007E1D20, 1000); // Psychotron corium
    patch.WriteU32((void *)0x007E1D24, 1000); // Psychotron corium

    patch.WriteU32((void *)0x007E1D28, 2000); // Plasmatron corium
    patch.WriteU32((void *)0x007E1D2C, 2000); // Plasmatron corium
    patch.WriteU32((void *)0x007E1D30, 2000); // Plasmatron corium

    // patch.WriteU32((void *)0x007E1D34, ); // Nuclear launcher corium

    // BO 
    patch.WriteU32((void *)0x007E1D40, 60); // Light laser corium
    patch.WriteU32((void *)0x007E1D44, 60); // Light laser corium
    patch.WriteU32((void *)0x007E1D48, 60); // Light laser corium

    patch.WriteU32((void *)0x007E1D70, 200); // Heavy laser corium
    patch.WriteU32((void *)0x007E1D74, 200); // Heavy laser corium
    patch.WriteU32((void *)0x007E1D78, 200); // Heavy laser corium

    patch.WriteU32((void *)0x007E1D4C, 260); // Magnetic-Mine Launcher corium
    patch.WriteU32((void *)0x007E1D50, 260); // Magnetic-Mine Launcher corium
    patch.WriteU32((void *)0x007E1D54, 260); // Magnetic-Mine Launcher corium

    patch.WriteU32((void *)0x007E1D7C, 240); // EM launcher corium
    patch.WriteU32((void *)0x007E1D80, 240); // EM launcher corium
    patch.WriteU32((void *)0x007E1D84, 240); // EM launcher corium

    patch.WriteU32((void *)0x007E1D88, 800); // Protective shield gen corium
    patch.WriteU32((void *)0x007E1D8C, 800); // Protective shield gen corium
    patch.WriteU32((void *)0x007E1D90, 800); // Protective shield gen corium

    // SI
    //patch.WriteU32((void *)0x007E1EC0, 250); // Gas_Shell_Launcher corium
    //patch.WriteU32((void *)0x007E1EC4, 250); // Gas_Shell_Launcher corium
    //patch.WriteU32((void *)0x007E1EC8, 250); // Gas_Shell_Launcher corium

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
    //patch.WriteU32((void *)0x007E2568, 800);  // Depot
    //patch.WriteU32((void *)0x007E256C, 800);  // Depot
    //patch.WriteU32((void *)0x007E3390, 600);  // Depot
    patch.WriteU32((void *)0x007E33C0, 600); // Silicon_Extractor silicon
    
    patch.WriteU32((void *)0x007E2508, 1200); // Repair_Docks_WS
    patch.WriteU32((void *)0x007E250C, 1200); // Repair_Docks_BO
    // patch.WriteU32((void *)0x007E3414, );    // Pulsar silicon

    patch.WriteU32((void *)0x007E33D8, 1200); // Gas_Shell_Launcher silicon
    patch.WriteU32((void *)0x007E33E4, 900); // DPT silicon
    //patch.WriteU32((void *)0x007E33F0, 600);  // Ion_Reflector silicon
    patch.WriteU32((void *)0x007E3408, 700);  // Bio_Mine_Launcher silicon
    patch.WriteU32((void *)0x007E345C, 1400); // Parcher silicon
    // patch.WriteU32((void *)0x007E3360, 1400); // Protoplasm_Generator silicon

    patch.WriteU32((void *)0x007E2598, 1000); // STOLp metal
    patch.WriteU32((void *)0x007E259C, 1000); // STOLp metal
    patch.WriteU32((void *)0x007E25A0, 1000); // STOLp metal

    patch.WriteU32((void *)0x007E2670, 1200); // Plasma_Cannon metal
    patch.WriteU32((void *)0x007E2674, 1200); // Plasma_Cannon metal
    patch.WriteU32((void *)0x007E2678, 1200); // Plasma_Cannon metal

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

    patch.WriteU32((void *)0x007E25D4, 1000); // Plasmatron metal
    patch.WriteU32((void *)0x007E25D8, 1000); // Plasmatron metal
    patch.WriteU32((void *)0x007E25DC, 1000); // Plasmatron metal

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
    patch.WriteU32((void *)0x007E0A68, 900);  // Psi-zond silicon
    patch.WriteU32((void *)0x007E0A64, 1000);  // Usurper silicon
    patch.WriteU32((void *)0x007E0A54, 250);  // Skat silicon
    // patch.WriteU32((void *)0x007E0A4C, 0);  // Paralisys probe silicon
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
    auto ini_file = InitConfig();   
    // Research make unavailable
    // patch.WriteByte((void *)0x00798FF6, ); // Mining upgrade ws
    // patch.WriteByte((void *)0x00799062, ); // Mining upgrade bo

    patch.WriteByte((void *)0x007BFBBB, 0); // Mining upgrade silicon si
    // patch.WriteByte((void *)0x007BFBBC, ); // Mining upgrade corium si
    
    patch.WriteByte((void *)0x007BFAC8, 0); // WS Capture upg
    patch.WriteByte((void *)0x007BFB60, 0); // BO Capture upg
    patch.WriteByte((void *)0x007BFB4F, 0); // BO Torp upg
    patch.WriteByte((void *)0x007BFBF8, 0); // SI Capture upg

    patch.WriteByte((void *)0x007BFBD6, 0); // SI TRPEVADE unavailable
    //patch.WriteByte((void *)0x007BFBCF, 0); // SI IONARMOR unavailable
    patch.WriteByte((void *)0x0079903F, 1); // SI IONARMOR 1 lvl only
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
    patch.WriteByte((void *)0x007C002F, 61);  // WS CYBER dep
    patch.WriteByte((void *)0x007C0033, 1);  // WS CYBER dep lvl
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
    patch.WriteByte((void *)0x007BFE0E, 7);  // WS PLASMACANN dep2
    patch.WriteByte((void *)0x007BFE3B, 25); // WS NUKE dep
    patch.WriteByte((void *)0x007BFDD7, 4);  // WS LSRSCRN dep
    patch.WriteByte((void *)0x007BFDDB, 3);  // WS LSRSCRN dep lvl
    //patch.WriteByte((void *)0x007BFCAB, 0);  // WS DMG T2 dep
    patch.WriteByte((void *)0x007BFC79, 0);  // WS DPTHMINE dep
    patch.WriteByte((void *)0x007BFD73, 15); // WS SENT DMG dep
    patch.WriteByte((void *)0x007C00AC, 5);  // WS SPEED T3 dep
    // patch.WriteByte((void *)0x007C0048, 11); // WS SPEED T4 dep
    patch.WriteByte((void *)0x007C00F7, 0);  // WS UPGMINE dep
    patch.WriteByte((void *)0x007C00DE, 30);  // WS AMMOPROD dep
    patch.WriteByte((void *)0x007C00E2, 1);  // WS TORPPROD dep lvl
    patch.WriteByte((void *)0x007C0093, 1);  // WS MOBILEPLATF dep
    //patch.WriteByte((void *)0x007BFC2E, 0);  // WS MEDTORP dep
    patch.WriteByte((void *)0x007BFD28, 1);  // WS HFCANNSPEED dep
    patch.WriteByte((void *)0x007BFC79, 0);  // WS MINELAYER dep
    patch.WriteByte((void *)0x007BFE6D, 0);  // WS FINDTELE dep
    patch.WriteByte((void *)0x007BFE86, 9);  // WS FINDMINE dep
    patch.WriteByte((void *)0x007BFEB8, 9);  // WS FINDLASSNARE dep
    
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

    patch.WriteU32((void *)0x007E5498, 3000); // WS RADAR time
    patch.WriteU32((void *)0x007E5548, 3000); // WS HACK time
    patch.WriteU32((void *)0x007E5868, 3000); // WS DEFHACK time
    patch.WriteU32((void *)0x007E5848, 4500); // WS UPGHACK time
    patch.WriteU32((void *)0x007E5598, 6000); // WS LIBERATOR time
    patch.WriteU32((void *)0x007E54CC, 6000); // WS SPD T3 time
    patch.WriteU32((void *)0x007E54D0, 6000); // WS SPD T4 timeg
    patch.WriteU32((void *)0x007E55C8, 7500); // WS PSIFIELD time
    patch.WriteU32((void *)0x007E5608, 6000); // WS NUKE time
    patch.WriteU32((void *)0x007E5618, 7500); // WS CORIUM276 time
    patch.WriteU32((void *)0x007E5528, 9000); // WS UPG HFCANN time
    patch.WriteU32((void *)0x007E5638, 7500); // WS UPG USG time
    patch.WriteU32((void *)0x007E55F8, 9000); // WS TERMINATOR time
    patch.WriteU32((void *)0x007E55D8, 6750);   // WS CYBER time
    
    patch.WriteU32((void *)0x007E5668, 7500); // WS PLASMACANN time
    //patch.WriteU32((void *)0x007E5898, 9000); // WS ANTINUKE time (vanilla 6 min)
    patch.WriteU32((void *)0x007E5578, 3000); // WS TURRETS FLOAT time
    patch.WriteU32((void *)0x007E5598, 4500); // WS LIBERATOR time
    patch.WriteU32((void *)0x007E5588, 3000); // WS DISPSCREEN time

    patch.WriteU32((void *)0x007E54B8, 4500); // WS ARMOR T2 time
    patch.WriteU32((void *)0x007E54BC, 7500); // WS ARMOR T3 time
    patch.WriteU32((void *)0x007E54C0, 9000); // WS ARMOR T4 time

    patch.WriteU32((void *)0x007E54D8, 4500); // WS DMG T1 time
    patch.WriteU32((void *)0x007E54DC, 6000); // WS DMG T2 time
    patch.WriteU32((void *)0x007E54E0, 6750); // WS DMG T3 time
    patch.WriteU32((void *)0x007E54E4, 7500); // WS DMG T4 time
    patch.WriteU32((void *)0x007E5E08, 4500); // WS TORPSPEED time
    patch.WriteU32((void *)0x007E5878, 4500); // WS TELEFIND time
    patch.WriteU32((void *)0x007E5838, 6000); // WS LASMINEFIND time
    patch.WriteU32((void *)0x007E5E18, 4500); // WS LASMINEFIND time
    patch.WriteU32((void *)0x007E5558, 3000); // WS MARAUDER time
    patch.WriteU32((void *)0x007E5628, 7500); // WS LSRSCRN time
    patch.WriteU32((void *)0x007E5658, 7500); // WS MINESPEED time
    patch.WriteU32((void *)0x007E54F8, 4500); // WS CRUISER time
    patch.WriteU32((void *)0x007E5678, 4500); // WS UPGREPAIR time
    //patch.WriteU32((void *)0x007E55A8, 6000); // WS TELEPORT time
    patch.WriteU32((void *)0x007E5688, 4500); // WS UPG TELEPORT time
    patch.WriteU32((void *)0x007E5828, 4500); // WS TELESHIELD time
    patch.WriteU32((void *)0x007E5648, 4500); // WS UPG LOCATOR time
    patch.WriteU32((void *)0x007E5DE8, 6000); // WS SENT DMG time
    patch.WriteU32((void *)0x007E55E8, 3000); // WS AMMOPROD time

     patch.WriteU32((void *)0x007C028B, 42);   // BO AVENGER dep
     patch.WriteU32((void *)0x007C028F, 1);   // BO AVENGER dep lvl
    patch.WriteU32((void *)0x007C0290, 0);   // BO AVENGER dep2
    patch.WriteU32((void *)0x007C0294, 0);   // BO AVENGER dep2 lvl
    patch.WriteByte((void *)0x007C04CA, 39);  // BO PHANTOM dep
    //patch.WriteByte((void *)0x007C02A8, 0);   // BO UPGEM dep lvl
    patch.WriteByte((void *)0x007C02A9, 0);  // BO UPGEM dep2
    patch.WriteByte((void *)0x007C0515, 132); // BO DEFHACK dep
    patch.WriteByte((void *)0x007C04E3, 132); // BO UPGRAIDER dep
    patch.WriteByte((void *)0x007C068C, 128); // BO UPG REPSPD dep
    patch.WriteByte((void *)0x007C01DC, 150);  // BO UPG DESTR dep
    patch.WriteByte((void *)0x007C01E1, 0); // BO UPG DESTR dep2
    patch.WriteByte((void *)0x007C01E5, 0);   // BO UPG DESTR dep2 lvl
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
    patch.WriteByte((void *)0x007C0646, 0); // BO AVENGER dep
    patch.WriteByte((void *)0x007C060F, 51); // BO MOBILEPLATF dep
    patch.WriteByte((void *)0x007C025E, 0);   // BO Magnetic_Mine_Launcher dep2
    patch.WriteByte((void *)0x007C0272, 41);  // BO EMTORP 
    patch.WriteByte((void *)0x007C02A4, 43);  // BO UPGEM dep
    patch.WriteByte((void *)0x007C0560, 137); // BO LASBOMB dep
    patch.WriteByte((void *)0x007C0565, 50);  // BO LASBOMB dep2
    patch.WriteByte((void *)0x007C0673, 0);   // BO UPG MINESPD depg
    patch.WriteByte((void *)0x007C033A, 54);  // BO LIGHTLASSPD dep
    patch.WriteByte((void *)0x007C02EF, 54);  // BO RUBY dep
    patch.WriteByte((void *)0x007C036C, 55);  // BO HEAVYLASRATE dep
    patch.WriteByte((void *)0x007C0353, 46);  // BO LASRATE dep
    //patch.WriteByte((void *)0x007C0357, 1);   // BO LASRATE dep lvl
    //patch.WriteByte((void *)0x007C0358, 57);  // BO LASRATE dep2
    //patch.WriteByte((void *)0x007C035C, 1);   // BO LASRATE dep2 lvl
    patch.WriteByte((void *)0x007C0385, 38);  // BO RECHARGEST dep
    patch.WriteByte((void *)0x007C0579, 56);  // BO SHIELDGEN dep
    patch.WriteByte((void *)0x007C05AB, 48);  // BO FORCEFIELD dep
    // patch.WriteByte((void *)0x007C0498, ); // BO UPGHACK dep
    patch.WriteByte((void *)0x007C052E, 127); // BO LOCSHIELD dep
    patch.WriteByte((void *)0x007C0466, 134); // BO STEALTH dep
    patch.WriteByte((void *)0x007C03B7, 143);  // BO TELEPORT dep
    patch.WriteByte((void *)0x007C041B, 135);  // BO UPGTELE dep
    patch.WriteByte((void *)0x007C0420, 0);   // BO UPGTELE dep2
    patch.WriteByte((void *)0x007C03D0, 0);   // BO FINDTELE dep
    patch.WriteByte((void *)0x007C03D5, 0);   // BO FINDTELE dep2
    patch.WriteByte((void *)0x007C03E9, 37);  // BO FINDMINES dep
    patch.WriteByte((void *)0x007C0402, 37);  // BO FINDLASMINES dep
    patch.WriteByte((void *)0x007C05F6, 0);   // BO REPAIR dep
    patch.WriteByte((void *)0x007C0484, 0);   // BO RAIDER dep2
    patch.WriteByte((void *)0x007C0489, 0);   // BO RAIDER dep2
    patch.WriteU32((void *)0x007C0547, 141);  // BO UPGLOCATOR dep
    //patch.WriteU32((void *)0x007C05C4, 142); // BO ANTISMP dep
    patch.WriteU32((void *)0x007C05C9, 142);  // BO ANTISMP dep2
    patch.WriteU32((void *)0x007C05CD, 1);    // BO ANTISMP dep2 lvl
    patch.WriteU32((void *)0x007C01F5, 0);    // BO DEFENDER dep
    patch.WriteU32((void *)0x007C0240, 34);   // BO CASSETE dep
    patch.WriteU32((void *)0x007C01C3, 34);   // BO TORPSPEED dep
    patch.WriteU32((void *)0x007C01C7, 1);    // BO TORPSPEED dep lvl
    patch.WriteU32((void *)0x007C01AA, 150);  // BO DMG T4 dep
    patch.WriteU32((void *)0x007C01AE, 1);    // BO DMG T4 dep lvl
    patch.WriteU32((void *)0x007C02D6, 51);   // BO LIGHTLASRANGE dep 
    patch.WriteU32((void *)0x007C0308, 35);   // BO HEAVYLASER dep
    patch.WriteU32((void *)0x007C0321, 38);   // BO HEAVYLASRANGE dep
    

    patch.WriteU32((void *)0x007E5D08, 4500); // BO UPGLOCATOR time
    patch.WriteU32((void *)0x007E5C88, 6000); // BO ARMOR T2 time
    patch.WriteU32((void *)0x007E5C8C, 7500); // BO ARMOR T3 time
    patch.WriteU32((void *)0x007E5C90, 9000); // BO ARMOR T4 time
    patch.WriteU32((void *)0x007E56A8, 7500); // BO HEAVYCRUISER time
    patch.WriteU32((void *)0x007E5758, 6000); // BO PARALYZE time
    patch.WriteU32((void *)0x007E5768, 4500); // BO UPG RECHARGEST time
    // patch.WriteU32((void *)0x007E58A8, 9000); // BO ANTISMP time
    patch.WriteU32((void *)0x007E5748, 6000); // BO USGDEF time
    patch.WriteU32((void *)0x007E5D18, 7500); // BO UPGMINE time
    patch.WriteU32((void *)0x007E5C68, 3000); // BO RADAR time
    patch.WriteU32((void *)0x007E5CB8, 3000); // BO HACK time
    patch.WriteU32((void *)0x007E5D48, 4500); // BO UPGHACK time
    patch.WriteU32((void *)0x007E5D58, 3000); // BO DEFHACK time
    patch.WriteU32((void *)0x007E5D98, 6000); // BO PHANTOMUPG time
    patch.WriteU32((void *)0x007E5758, 6000); // BO AVENGER time
    patch.WriteU32((void *)0x007E56D8, 6000); // BO HEAVYLAS time
    patch.WriteU32((void *)0x007E57E8, 4500); // BO HEAVYLASRANGE time
    patch.WriteU32((void *)0x007E5818, 9000); // BO LASRATE time
    patch.WriteU32((void *)0x007E57B8, 3000); // BO RAIDER time
    patch.WriteU32((void *)0x007E5778, 6000); // BO SHIELDGEN time
    patch.WriteU32((void *)0x007E5798, 7500); // BO FORCEFIELD time
    patch.WriteU32((void *)0x007E5888, 6000); // BO MINEFIND time
    patch.WriteU32((void *)0x007E5D28, 4500); // BO UPGREPAIR time
    patch.WriteU32((void *)0x007E5D38, 4500); // BO UPGTELE time
    patch.WriteU32((void *)0x007E5698, 4500); // BO DESTROYER time
    patch.WriteU32((void *)0x007E57C8, 6000); // BO CYBER time
    patch.WriteU32((void *)0x007E5C98, 2500); // BO SPEED T1 time
    patch.WriteU32((void *)0x007E5C98, 2500); // BO SPEED T1 time
    patch.WriteU32((void *)0x007E5C9C, 6000); // BO SPEED T2 time
    patch.WriteU32((void *)0x007E5CA0, 7000); // BO SPEED T3 time
    patch.WriteU32((void *)0x007E56F8, 6000); // BO CASSETTE time
    patch.WriteU32((void *)0x007E5DA8, 6000); // BO UPG EMTORP time
    patch.WriteU32((void *)0x007E5788, 10500); // BO LASBOMB time
    patch.WriteU32((void *)0x007E57D8, 3000); // BO LIGHTLASRANGE time
    patch.WriteU32((void *)0x007E57F8, 6000); // BO LIGHTLASRATE time
    patch.WriteU32((void *)0x007E5CC8, 3000); // BO TURRETS FLOAT time
    patch.WriteU32((void *)0x007E5708, 5250); // BO MML time
    patch.WriteU32((void *)0x007E5728, 4500); // BO EM time
    patch.WriteU32((void *)0x007E5DD8, 4500); // BO TORPSPEED time
    patch.WriteU32((void *)0x007E56C8, 4500); // BO LASMINES time
    patch.WriteU32((void *)0x007E5D88, 3000); // BO LASMINEFIND time
    
    

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
    patch.WriteByte((void *)0x007C0903, 78);  // SI NRG T3 dep
    // patch.WriteByte((void *)0x007C0908, );  // SI NRG T3 dep2
    // patch.WriteByte((void *)0x007C090C, );  // SI NRG T3 dep2 lvl
    patch.WriteByte((void *)0x007C094E, 81); // SI NRG T4 dep
    patch.WriteByte((void *)0x007C0952, 1);  // SI NRG T4 dep lvl
    patch.WriteByte((void *)0x007C09CB, 84); // SI SHELLPROD dep
    //patch.WriteByte((void *)0x007C09CF, 2); // SI SHELLPROD dep lvl
    // patch.WriteByte((void *)0x007C0D9A, 2);    // SI NRGSHLDNEUTR dep
    patch.WriteByte((void *)0x007C0D9E, 1); // SI NRGSHLDNEUTR dep lvl
    patch.WriteByte((void *)0x007C091C, 78);  // SI NRGTRANSF dep
    patch.WriteByte((void *)0x007C0920, 1);   // SI NRGTRANSF dep lvl
    patch.WriteByte((void *)0x007C0A93, 119); // SI ORBITLAS dep
    patch.WriteByte((void *)0x007C0A98, 94);   // SI ORBITLAS dep2
    patch.WriteByte((void *)0x007C0999, 78);  // SI UPGNRGMINE dep
    patch.WriteByte((void *)0x007C099D, 2);   // SI UPGNRGMINE dep lvl
    patch.WriteByte((void *)0x007C0AAC, 71);  // SI ANTISMP dep
    //patch.WriteByte((void *)0x007C0AB1, 119);  // SI ANTISMP dep2
    //patch.WriteByte((void *)0x007C0AB5, 1);   // SI ANTISMP dep2 lvl
    // patch.WriteByte((void *)0x007C0AB0, 2);  // SI ANTISMP dep lvl
    patch.WriteByte((void *)0x007C0B47, 106);    // SI PSISHIELD dep2
    patch.WriteByte((void *)0x007C0B4B, 1);    // SI PSISHIELD dep2 lvl
    patch.WriteByte((void *)0x007C0A48, 101); // SI IONARMOR dep
    patch.WriteByte((void *)0x007C0A4C, 3); // SI IONARMOR dep lvl
    patch.WriteByte((void *)0x007C0B2E, 0); // SI IONARMOR T4 dep2
    patch.WriteByte((void *)0x007C0B32, 0); // SI IONARMOR T4 dep2 lvl
    // patch.WriteByte((void *)0x007C0C0A, 0);   // SI DMG T2 dep
    // patch.WriteByte((void *)0x007C0C0E, 0);   // SI DMG T2 dep lvl
    patch.WriteByte((void *)0x007C0C23, 124); // SI DMG T3 dep
    // patch.WriteByte((void *)0x007C0C27, ); // SI DMG T3 dep lvl 
    patch.WriteByte((void *)0x007C09B2, 79); // SI MOLECULAR dep
    patch.WriteByte((void *)0x007C09B6, 1);  // SI MOLECULAR dep lvl
    patch.WriteByte((void *)0x007C09B7, 0);  // SI MOLECULAR dep2
    patch.WriteByte((void *)0x007C09BB, 0);  // SI MOLECULAR dep2 lvl
    patch.WriteByte((void *)0x007C09FD, 0); // SI UPGCORMINE dep
    // patch.WriteByte((void *)0x007C0AC5, ); // SI VACBOMB dep
    patch.WriteByte((void *)0x007C0ACA, 107);   // SI VACBOMB dep2
    patch.WriteByte((void *)0x007C0ACE, 1);   // SI VACBOMB dep2 lvl
    patch.WriteByte((void *)0x007C0A7A, 102); // SI LASABSORB dep
    patch.WriteByte((void *)0x007C0A7E, 1);  // SI LASABSORB dep lvl
    patch.WriteByte((void *)0x007C0A61, 101); // SI REGEN dep
    patch.WriteByte((void *)0x007C0A65, 1);  // SI REGEN dep lvl
    patch.WriteByte((void *)0x007C0A66, 81);  // SI REGEN dep2
    patch.WriteByte((void *)0x007C0A6A, 1);  // SI REGEN dep2 lvl
    patch.WriteByte((void *)0x007C086D, 69); // SI USURPER dep
    patch.WriteByte((void *)0x007C0872, 0); // SI USURPER dep2
    patch.WriteByte((void *)0x007C07D7, 73); // SI RESIDENT dep
    patch.WriteByte((void *)0x007C07DC, 0);  // SI RESIDENT dep2
    // patch.WriteByte((void *)0x007C07E0, );  // SI RESIDENT dep2 lvl
     patch.WriteByte((void *)0x007C07BE, 68); // SI BIOLOCSCREEN dep
    patch.WriteByte((void *)0x007C07A5, 72);  // SI BIOLOCSCAN dep
    patch.WriteByte((void *)0x007C0809, 72);  // SI INVISFIND dep
    patch.WriteByte((void *)0x007C06DD, 0);  // SI TELEPERSONAL dep
    patch.WriteByte((void *)0x007C06E1, 0);   // SI TELEPERSONAL dep lvl
    patch.WriteByte((void *)0x007C06F6, 95);  // SI TELEPORTAL dep
    patch.WriteByte((void *)0x007C06FA, 1);   // SI TELEPORTAL dep lvl
    patch.WriteByte((void *)0x007C0728, 96);  // SI TELEPORTALSEC dep
    patch.WriteByte((void *)0x007C070F, 77);  // SI QUANTUMPAR dep
    patch.WriteByte((void *)0x007C0714, 0);  // SI QUANTUMPAR dep2
    patch.WriteByte((void *)0x007C0718, 0);   // SI QUANTUMPAR dep2 lvl
    patch.WriteByte((void *)0x007C0935, 108); // SI RECYCLE dep
    patch.WriteByte((void *)0x007C07F0, 0);   // SI TELEFIND dep
    patch.WriteByte((void *)0x007C0822, 116);   // SI MINEFIND dep
    patch.WriteByte((void *)0x007C083B, 116);   // SI LASMINEFIND dep
    patch.WriteByte((void *)0x007C0980, 92); // SI IONFIELD dep
    patch.WriteByte((void *)0x007C0985, 0);   // SI IONFIELD dep2
    // patch.WriteByte((void *)0x007C0989, );   // SI IONFIELD dep2 lvl
    patch.WriteByte((void *)0x007C0D09, 0);   // SI PARALYZE dep
    patch.WriteByte((void *)0x007C0D0D, 0);   // SI PARALYZE dep lvl
    patch.WriteByte((void *)0x007C078C, 69);  // SI DEFHACK dep
    patch.WriteByte((void *)0x007C0773, 114); // SI UPGHACK dep
    patch.WriteByte((void *)0x007C0B42, 106); // SI PSISHIELD dep
    patch.WriteByte((void *)0x007C0B46, 1);   // SI PSISHIELD dep lvl
    patch.WriteByte((void *)0x007C0BF1, 89);  // SI UPGPULSAR dep
    patch.WriteByte((void *)0x007C0B8D, 85);  // SI DPT dep
    patch.WriteByte((void *)0x007C0BA6, 85);  // SI GASLAUNCHER dep
    patch.WriteByte((void *)0x007C0C55, 90);  // SI PARCHER dep
    patch.WriteU32((void *)0x007C0D9E, 1);    // SI NEUTRSHIELD dep lvl
    patch.WriteByte((void *)0x007C0AFB, 3);  // SI USGDEF dep lvl
    
    

    patch.WriteU32((void *)0x007E59D8, 3750);  // SI GASSHLLNCHR time
    patch.WriteU32((void *)0x007E5A48, 6000);  // SI UPG GASSHLLNCHR time
    patch.WriteU32((void *)0x007E5B50, 9000); // SI SPEED T4 time
    patch.WriteU32((void *)0x007E5B4C, 6000);  // SI SPEED T3 time
    patch.WriteU32((void *)0x007E5B48, 3000);  // SI SPEED T2 time
    patch.WriteU32((void *)0x007E58C8, 3000);  // SI HACK time
    patch.WriteU32((void *)0x007E58E8, 3000);  // SI DEFHACK time
    patch.WriteU32((void *)0x007E5AA8, 10500); // SI ANTINUKE time
    patch.WriteU32((void *)0x007E5B28, 6000); // SI IONFIELD time
    patch.WriteU32((void *)0x007E58F8, 3000);  // SI LOCDISPSCREEN time
    patch.WriteU32((void *)0x007E5918, 4500);  // SI INVISFIND time
    patch.WriteU32((void *)0x007E5B98, 3000);  // SI USURPER time
    patch.WriteU32((void *)0x007E5A38, 4500);  // SI IONREFLECTOR time
    patch.WriteU32((void *)0x007E5C28, 3000);  // SI UPGIONREFLECTOR time
    patch.WriteU32((void *)0x007E59E8, 6000);  // SI SOLITON time
    patch.WriteU32((void *)0x007E5C08, 3750);  // SI UPGDPT time
    patch.WriteU32((void *)0x007E5A68, 7500);  // SI TELEPERSONAL time
    patch.WriteU32((void *)0x007E5A78, 4500);  // SI PORTAL time
    patch.WriteU32((void *)0x007E5948, 4500);  // SI FINDTELE time
    patch.WriteU32((void *)0x007E5928, 3000);  // SI FINDMINES time
    patch.WriteU32((void *)0x007E5938, 3000);  // SI FINDLASMINES time
    patch.WriteU32((void *)0x007E5A98, 4500);  // SI PORTALCODE time
    patch.WriteU32((void *)0x007E5AB8, 6000);  // SI QUANTUMPAR time
    //patch.WriteU32((void *)0x007E5BE8, 3000);  // SI RESIDENT time
    patch.WriteU32((void *)0x007E59B8, 7500);  // SI CORMINESPEED time
    patch.WriteU32((void *)0x007E5BB8, 6000);  // SI ACOUSTICMINES time
    patch.WriteU32((void *)0x007E5BA8, 6000);  // SI BIOASSAULTER time
    patch.WriteU32((void *)0x007E5BD8, 4500);  // SI UPGBIO time
    // patch.WriteU32((void *)0x007E5C18, 6000); // SI DMG T2 time
    patch.WriteU32((void *)0x007E5C1C, 9000); // SI DMG T3 time
    patch.WriteU32((void *)0x007E5C18, 6000); // SI RECYCLE time
    patch.WriteU32((void *)0x007E595C, 3750); // SI NRG T3 time
    patch.WriteU32((void *)0x007E5960, 6000); // SI NRG T4 time
    patch.WriteU32((void *)0x007E5AD8, 4500); // SI REGEN time
    patch.WriteU32((void *)0x007E5BF8, 3000); // SI SHELLPROD time
    patch.WriteU32((void *)0x007E5988, 3000); // SI ENERGIZER time
    

    patch.WriteU32((void *)0x007E5B78, 6000); // SI DREADNAUGHT time
    patch.WriteU32((void *)0x007E5978, 5250); // SI UPGACCUM time
    patch.WriteU32((void *)0x007E5AF8, 4500); // SI LASABSORB time
    patch.WriteU32((void *)0x007E5B88, 7500); // SI PARALYZE time
    patch.WriteU32((void *)0x007E5AC8, 4500); // SI ARMOR T2 time
    patch.WriteU32((void *)0x007E5ACC, 6750); // SI ARMOR T3 time
    patch.WriteU32((void *)0x007E5AD0, 7500); // SI ARMOR T4 time
    patch.WriteU32((void *)0x007E5A88, 6750); // SI ORBITLAS time
    patch.WriteU32((void *)0x007E5BC8, 9000); // SI VACBOMB time
    patch.WriteU32((void *)0x007E5A18, 6000); // SI PULSARUPG time
    patch.WriteU32((void *)0x007E5A48, 7500); // SI PARCHER time
    patch.WriteU32((void *)0x007E5C38, 6000); // SI UPG DREDNAUGHT time
    patch.WriteU32((void *)0x007E58D8, 4500); // SI BIOLOCSCAN time
    patch.WriteU32((void *)0x007E5AE8, 6000); // SI IONARMOR time
    patch.WriteU32((void *)0x007E5B08, 6000); // SI PSISHIELD time
    
    

    // SPEED Upgrade
    patch.WriteByte((void *)0x0045F737, GetPrivateProfileInt(L"Speed_upgrade", L"Speed_total_add_1", 2, ini_file));
    patch.WriteByte((void *)0x0045F733, GetPrivateProfileInt(L"Speed_upgrade", L"Speed_total_add_2", 6, ini_file));
    patch.WriteByte((void *)0x0045F72F, GetPrivateProfileInt(L"Speed_upgrade", L"Speed_total_add_3", 8, ini_file));


    // BUILDINGS 
    // HP
    // COMMON HUMANS
    patch.WriteU32Dual((void *)0x007E417C, GetPrivateProfileInt(L"Subcenter", L"HP", 2000, ini_file));
    patch.WriteU32Dual((void *)0x007E4188, GetPrivateProfileInt(L"Repair_Docks", L"HP", 1500, ini_file));
    patch.WriteU32Dual((void *)0x007E4194, GetPrivateProfileInt(L"Arsenal", L"HP", 1200, ini_file));
    patch.WriteU32Dual((void *)0x007E41A0, GetPrivateProfileInt(L"Research_Center", L"HP", 1000, ini_file));
    patch.WriteU32Dual((void *)0x007E41E8, GetPrivateProfileInt(L"Depot", L"HP", 800, ini_file));
    patch.WriteU32Dual((void *)0x007E41DC, GetPrivateProfileInt(L"Gold_Extractor", L"HP", 500, ini_file));
    patch.WriteU32Dual((void *)0x007E41AC, GetPrivateProfileInt(L"Sonar", L"HP", 800, ini_file));
    patch.WriteU32Triple((void *)0x007E41B8, GetPrivateProfileInt(L"Teleport", L"HP", 1500, ini_file));
    patch.WriteU32Triple((void *)0x007E41D0, GetPrivateProfileInt(L"Corium_Mine_Humans", L"HP", 500, ini_file));
    patch.WriteU32Dual((void *)0x007E41F4, GetPrivateProfileInt(L"Infocenter", L"HP", 700, ini_file));
    patch.WriteU32Dual((void *)0x007E4200, GetPrivateProfileInt(L"Disperser", L"HP", 800, ini_file));
    patch.WriteU32Dual((void *)0x007E42D8, GetPrivateProfileInt(L"Metal_Mine_Humans", L"HP", 500, ini_file));
    patch.WriteU32Dual((void *)0x007E42E4, GetPrivateProfileInt(L"Oxygen_Generator_Humans", L"HP", 500, ini_file));
    patch.WriteU32Dual((void *)0x007E42FC, GetPrivateProfileInt(L"Market_humans", L"HP", 1000, ini_file));

    // WS
    patch.WriteU32Dual((void *)0x007E4224, GetPrivateProfileInt(L"Cybercenter_WS", L"HP", 600, ini_file));
    patch.WriteU32Dual((void *)0x007E4230, GetPrivateProfileInt(L"Shark_Control", L"HP", 500, ini_file));
    patch.WriteU32Dual((void *)0x007E4248, GetPrivateProfileInt(L"Psychotron", L"HP", 800, ini_file));
    patch.WriteU32Dual((void *)0x007E4458, GetPrivateProfileInt(L"Teleshield", L"HP", 700, ini_file));
    
    patch.WriteU32Triple((void *)0x007E420C, GetPrivateProfileInt(L"HF_Cannon", L"HP", 1600, ini_file));
    patch.WriteU32Triple((void *)0x007E4218, GetPrivateProfileInt(L"STOLp", L"HP", 1800, ini_file));    
    patch.WriteU32Triple((void *)0x007E423C, GetPrivateProfileInt(L"USG", L"HP", 500, ini_file));
    patch.WriteU32Triple((void *)0x007E42F0, GetPrivateProfileInt(L"Plasma_Cannon", L"HP", 1200, ini_file));

    patch.WriteU32Triple((void *)0x007E4254, GetPrivateProfileInt(L"Plasmatron", L"HP", 700, ini_file));
    patch.WriteU32Triple((void *)0x007E4260, GetPrivateProfileInt(L"Nuclear_Launcher", L"HP", 600, ini_file));

    // BO
    patch.WriteU32Dual((void *)0x007E42B4, GetPrivateProfileInt(L"Protective_field_gen", L"HP", 500, ini_file));
    patch.WriteU32Dual((void *)0x007E42C0, GetPrivateProfileInt(L"Force_field", L"HP", 800, ini_file));
    patch.WriteU32Dual((void *)0x007E4284, GetPrivateProfileInt(L"Power_station", L"HP", 500, ini_file));
    patch.WriteU32Dual((void *)0x007E4290, GetPrivateProfileInt(L"Cyber_laboratory_dolphins", L"HP", 500, ini_file));
    
    patch.WriteU32Triple((void *)0x007E426C, GetPrivateProfileInt(L"Light_Laser", L"HP", 1200, ini_file));
    patch.WriteU32Triple((void *)0x007E429C, GetPrivateProfileInt(L"Heavy_Laser", L"HP", 1400, ini_file));
    patch.WriteU32Triple((void *)0x007E4278, GetPrivateProfileInt(L"Magnetic_Mine_Launcher", L"HP", 1600, ini_file));
    patch.WriteU32Triple((void *)0x007E42A8, GetPrivateProfileInt(L"EM_Launcher", L"HP", 1300, ini_file));

    patch.WriteU32Triple((void *)0x007E42CC, GetPrivateProfileInt(L"Lasbomb_Launcher", L"HP", 500, ini_file));


    // SI
    patch.WriteU32((void *)0x007E43DC, GetPrivateProfileInt(L"Silicon_Extractor", L"HP", 600, ini_file));  // Silicon_Extractor HP 1000
    patch.WriteU32((void *)0x007E4310, GetPrivateProfileInt(L"Core", L"HP", 2000, ini_file)); // SI Core HP 4000
    patch.WriteU32((void *)0x007E4370, GetPrivateProfileInt(L"Arsenal_SI", L"HP", 1200, ini_file)); // SI Arsenal HP 2400
    patch.WriteU32((void *)0x007E437C, GetPrivateProfileInt(L"Protoplasm_Generator", L"HP", 1800, ini_file)); // SI Protoplasm_Generator HP 3600

    patch.WriteU32((void *)0x007E431C, GetPrivateProfileInt(L"Tech_Module", L"HP", 500, ini_file)); // SI Module_SI 10
    patch.WriteU32((void *)0x007E4328, GetPrivateProfileInt(L"Tech_Module", L"HP", 500, ini_file)); // SI Module 10
    patch.WriteU32((void *)0x007E4334, GetPrivateProfileInt(L"Tech_Module", L"HP", 500, ini_file)); // SI Module 10
    patch.WriteU32((void *)0x007E4340, GetPrivateProfileInt(L"Tech_Module", L"HP", 500, ini_file)); // SI Module 10
    patch.WriteU32((void *)0x007E434C, GetPrivateProfileInt(L"Tech_Module", L"HP", 500, ini_file)); // SI Module 10
    patch.WriteU32((void *)0x007E4358, GetPrivateProfileInt(L"Tech_Module", L"HP", 500, ini_file)); // SI Module 10
    patch.WriteU32((void *)0x007E4364, GetPrivateProfileInt(L"Tech_Module", L"HP", 500, ini_file)); // SI Module 10

    patch.WriteU32((void *)0x007E4388, GetPrivateProfileInt(L"Biolocator", L"HP", 700, ini_file)); // SI Biolocator 14
    patch.WriteU32((void *)0x007E438C, GetPrivateProfileInt(L"Corium_Mine_SI", L"HP", 500, ini_file)); // SI Corium extractor 10
    patch.WriteU32((void *)0x007E4390, GetPrivateProfileInt(L"Corium_Mine_SI", L"HP", 500, ini_file)); // SI Corium extractor 10
    patch.WriteU32((void *)0x007E4394, GetPrivateProfileInt(L"Corium_Mine_SI", L"HP", 500, ini_file)); // SI Corium extractor 10 
    patch.WriteU32((void *)0x007E43A0, GetPrivateProfileInt(L"Energy_converter", L"HP", 1400, ini_file)); // SI Energy_converter_SI 24
    patch.WriteU32((void *)0x007E43AC, GetPrivateProfileInt(L"Depot_SI", L"HP", 500, ini_file)); // SI Corium silo 10 Depot_SI
    patch.WriteU32((void *)0x007E43B8, GetPrivateProfileInt(L"Energy_accumulator", L"HP", 800, ini_file)); // SI Energy_accumulator_SI 16
    patch.WriteU32((void *)0x007E43C4, GetPrivateProfileInt(L"Replenish_pod", L"HP", 700, ini_file)); // SI Replenish_pod_SI 14
    patch.WriteU32((void *)0x007E43D0, GetPrivateProfileInt(L"Recyclotron", L"HP", 1100, ini_file)); // SI Recyclotron_SI 22
    patch.WriteU32((void *)0x007E443C, GetPrivateProfileInt(L"Gate", L"HP", 1300, ini_file)); // SI Gate 26
    patch.WriteU32((void *)0x007E4448, GetPrivateProfileInt(L"Ion_field_generator", L"HP", 1000, ini_file)); // SI Ion_field_generator 20
    patch.WriteU32((void *)0x007E4454, GetPrivateProfileInt(L"Molecular_repair_facility", L"HP", 900, ini_file)); // SI Molecular 18
    patch.WriteU32((void *)0x007E446C, GetPrivateProfileInt(L"Orbital_laser", L"HP", 1200, ini_file)); // SI Orbital_laser 24
    patch.WriteU32((void *)0x007E4484, GetPrivateProfileInt(L"Vacuum_Bomb", L"HP", 700, ini_file)); // SI Vacuum_bomb_launcher_SI 14
    patch.WriteU32((void *)0x007E4490, GetPrivateProfileInt(L"Quantum_Paralyzer", L"HP", 800, ini_file)); // SI Quantum_Paralyzer 16



    patch.WriteU32Triple((void *)0x007E4428, GetPrivateProfileInt(L"Pulsar", L"HP", 1000, ini_file));
    patch.WriteU32Triple((void *)0x007E43E0, GetPrivateProfileInt(L"Soliton", L"HP", 700, ini_file));
    patch.WriteU32Triple((void *)0x007E43EC, GetPrivateProfileInt(L"Gas_Shell_Launcher", L"HP", 1100, ini_file));
    patch.WriteU32Triple((void *)0x007E43F8, GetPrivateProfileInt(L"Double_Plasma_Turret", L"HP", 1400, ini_file));
    patch.WriteU32Triple((void *)0x007E441C, GetPrivateProfileInt(L"Bio_Mine_Launcher", L"HP", 1200, ini_file)); 
    patch.WriteU32Triple((void *)0x007E4410, GetPrivateProfileInt(L"Jump_Mine_Launcher", L"HP", 1000, ini_file));
    patch.WriteU32((void *)0x007E440C, GetPrivateProfileInt(L"Ion_Reflector", L"HP", 1300, ini_file));
    patch.WriteU32Triple((void *)0x007E4470, GetPrivateProfileInt(L"Parcher", L"HP", 1400, ini_file));

    // Corium
    // COMMON HUMANS
    patch.WriteU32Dual((void *)0x007E1C50, GetPrivateProfileInt(L"Subcenter", L"Corium", 0, ini_file));
    patch.WriteU32Dual((void *)0x007E1C5C, GetPrivateProfileInt(L"Repair_Docks", L"Corium", 0, ini_file));
    patch.WriteU32Dual((void *)0x007E1C68, GetPrivateProfileInt(L"Arsenal", L"Corium", 400, ini_file));
    patch.WriteU32Dual((void *)0x007E1C74, GetPrivateProfileInt(L"Research_Center", L"Corium", 300, ini_file));
    patch.WriteU32Dual((void *)0x007E1C80, GetPrivateProfileInt(L"Sonar", L"Corium", 0, ini_file));
    patch.WriteU32Dual((void *)0x007E1C8C, GetPrivateProfileInt(L"Teleport", L"Corium", 450, ini_file));
    patch.WriteU32Dual((void *)0x007E1CA4, GetPrivateProfileInt(L"Corium_Mine_Humans", L"Corium", 0, ini_file));
    patch.WriteU32Dual((void *)0x007E1CB0, GetPrivateProfileInt(L"Gold_Extractor", L"Corium", 0, ini_file));
    patch.WriteU32Dual((void *)0x007E1CBC, GetPrivateProfileInt(L"Depot", L"Corium", 0, ini_file));
    patch.WriteU32Dual((void *)0x007E1CC8, GetPrivateProfileInt(L"Infocenter", L"Corium", 0, ini_file));
    patch.WriteU32Dual((void *)0x007E1CD4, GetPrivateProfileInt(L"Disperser", L"Corium", 100, ini_file));
    patch.WriteU32Dual((void *)0x007E1DAC, GetPrivateProfileInt(L"Metal_Mine_Humans", L"Corium", 0, ini_file));
    patch.WriteU32Dual((void *)0x007E1DB8, GetPrivateProfileInt(L"Oxygen_Generator_Humans", L"Corium", 0, ini_file));
    patch.WriteU32Dual((void *)0x007E1DD0, GetPrivateProfileInt(L"Market_humans", L"Corium", 0, ini_file));
    
    // WS
    patch.WriteU32Dual((void *)0x007E1CF8, GetPrivateProfileInt(L"Cybercenter_WS", L"Corium", 0, ini_file));
    patch.WriteU32Dual((void *)0x007E1D04, GetPrivateProfileInt(L"Shark_Control", L"Corium", 0, ini_file));
    patch.WriteU32Dual((void *)0x007E1D1C, GetPrivateProfileInt(L"Psychotron", L"Corium", 300, ini_file));
    patch.WriteU32Dual((void *)0x007E1F2C, GetPrivateProfileInt(L"Teleshield", L"Corium", 200, ini_file));
    
    patch.WriteU32Triple((void *)0x007E1CE0, GetPrivateProfileInt(L"HF_Cannon", L"Corium", 40, ini_file));
    patch.WriteU32Triple((void *)0x007E1CEC, GetPrivateProfileInt(L"STOLp", L"Corium", 80, ini_file));
    patch.WriteU32Triple((void *)0x007E1D10, GetPrivateProfileInt(L"USG", L"Corium", 300, ini_file));
    patch.WriteU32Triple((void *)0x007E1DC4, GetPrivateProfileInt(L"Plasma_Cannon", L"Corium", 500, ini_file));

    patch.WriteU32Triple((void *)0x007E1D28, GetPrivateProfileInt(L"Plasmatron", L"Corium", 1000, ini_file));
    patch.WriteU32Triple((void *)0x007E1D34, GetPrivateProfileInt(L"Nuclear_Launcher", L"Corium", 2000, ini_file)); 

    // BO
    patch.WriteU32Dual((void *)0x007E1D58, GetPrivateProfileInt(L"Power_station", L"Corium", 250, ini_file));
    patch.WriteU32Dual((void *)0x007E1D64, GetPrivateProfileInt(L"Cyber_laboratory_dolphins", L"Corium", 200, ini_file));
    patch.WriteU32Dual((void *)0x007E1D88, GetPrivateProfileInt(L"Protective_field_gen", L"Corium", 400, ini_file));
    patch.WriteU32Dual((void *)0x007E1D94, GetPrivateProfileInt(L"Force_field", L"Corium", 1000, ini_file));

    patch.WriteU32Triple((void *)0x007E1D40, GetPrivateProfileInt(L"Light_Laser", L"Corium", 50, ini_file));
    patch.WriteU32((void *)0x007940D8, GetPrivateProfileInt(L"Light_Laser", L"Ammo", 30, ini_file));
    patch.WriteU32Triple((void *)0x007E1D70, GetPrivateProfileInt(L"Heavy_Laser", L"Corium", 100, ini_file));
    patch.WriteU32Triple((void *)0x007E1D4C, GetPrivateProfileInt(L"Magnetic_Mine_Launcher", L"Corium", 120, ini_file));
    patch.WriteU32Triple((void *)0x007E1D7C, GetPrivateProfileInt(L"EM_Launcher", L"Corium", 80, ini_file));

    patch.WriteU32Triple((void *)0x007E1DA0, GetPrivateProfileInt(L"Lasbomb_Launcher", L"Corium", 3000, ini_file));

    
    // SI
    patch.WriteU32((void *)0x007E1EB0, GetPrivateProfileInt(L"Silicon_Extractor", L"Corium", 0, ini_file));  // Silicon_Extractor Corium 1000
    patch.WriteU32((void *)0x007E1DE4, GetPrivateProfileInt(L"Core", L"Corium", 300, ini_file)); // SI Core Corium 4000
    patch.WriteU32((void *)0x007E1E44, GetPrivateProfileInt(L"Arsenal_SI", L"Corium", 400, ini_file)); // SI Arsenal Corium 2400
    patch.WriteU32((void *)0x007E1E50, GetPrivateProfileInt(L"Protoplasm_Generator", L"Corium", 0, ini_file)); // SI Protoplasm_Generator Corium 3600

    patch.WriteU32((void *)0x007E1DF0, GetPrivateProfileInt(L"Tech_Module", L"Corium", 200, ini_file)); // SI Module_SI 10
    patch.WriteU32((void *)0x007E1DFC, GetPrivateProfileInt(L"Tech_Module", L"Corium", 200, ini_file)); // SI Module 10
    patch.WriteU32((void *)0x007E1E08, GetPrivateProfileInt(L"Tech_Module", L"Corium", 200, ini_file)); // SI Module 10
    patch.WriteU32((void *)0x007E1E14, GetPrivateProfileInt(L"Tech_Module", L"Corium", 200, ini_file)); // SI Module 10
    patch.WriteU32((void *)0x007E1E20, GetPrivateProfileInt(L"Tech_Module", L"Corium", 200, ini_file)); // SI Module 10
    patch.WriteU32((void *)0x007E1E2C, GetPrivateProfileInt(L"Tech_Module", L"Corium", 200, ini_file)); // SI Module 10
    patch.WriteU32((void *)0x007E1E38, GetPrivateProfileInt(L"Tech_Module", L"Corium", 200, ini_file)); // SI Module 10

    patch.WriteU32((void *)0x007E1E5C, GetPrivateProfileInt(L"Biolocator", L"Corium", 50, ini_file)); // SI Biolocator 14
    patch.WriteU32((void *)0x007E1E60, GetPrivateProfileInt(L"Corium_Mine_SI", L"Corium", 0, ini_file)); // SI Corium extractor 10
    patch.WriteU32((void *)0x007E1E64, GetPrivateProfileInt(L"Corium_Mine_SI", L"Corium", 0, ini_file)); // SI Corium extractor 10
    patch.WriteU32((void *)0x007E1E68, GetPrivateProfileInt(L"Corium_Mine_SI", L"Corium", 0, ini_file)); // SI Corium extractor 10 
    patch.WriteU32((void *)0x007E1E74, GetPrivateProfileInt(L"Energy_converter", L"Corium", 200, ini_file)); // SI Energy_converter_SI 24
    patch.WriteU32((void *)0x007E1E80, GetPrivateProfileInt(L"Depot_SI", L"Corium", 0, ini_file)); // SI Corium silo 10 Depot_SI
    patch.WriteU32((void *)0x007E1E8C, GetPrivateProfileInt(L"Energy_accumulator", L"Corium", 0, ini_file)); // SI Energy_accumulator_SI 16
    patch.WriteU32((void *)0x007E1E98, GetPrivateProfileInt(L"Replenish_pod", L"Corium", 50, ini_file)); // SI Replenish_pod_SI 14
    patch.WriteU32((void *)0x007E1EA4, GetPrivateProfileInt(L"Recyclotron", L"Corium", 200, ini_file)); // SI Recyclotron_SI 22
    patch.WriteU32((void *)0x007E1F10, GetPrivateProfileInt(L"Gate", L"Corium", 150, ini_file)); // SI Gate 26
    patch.WriteU32((void *)0x007E1F1C, GetPrivateProfileInt(L"Ion_field_generator", L"Corium", 400, ini_file)); // SI Ion_field_generator 20
    patch.WriteU32((void *)0x007E1F28, GetPrivateProfileInt(L"Molecular_repair_facility", L"Corium", 500, ini_file)); // SI Molecular 18
    patch.WriteU32((void *)0x007E1F40, GetPrivateProfileInt(L"Orbital_laser", L"Corium", 3000, ini_file)); // SI Orbital_laser 24
    patch.WriteU32((void *)0x007E1F58, GetPrivateProfileInt(L"Vacuum_Bomb", L"Corium", 3000, ini_file)); // SI Vacuum_bomb_launcher_SI 14
    patch.WriteU32((void *)0x007E1F64, GetPrivateProfileInt(L"Quantum_Paralyzer", L"Corium", 600, ini_file)); // SI Quantum_Paralyzer 16
    
    patch.WriteU32Triple((void *)0x007E1EFC, GetPrivateProfileInt(L"Pulsar", L"Corium", 50, ini_file));
    patch.WriteU32Triple((void *)0x007E1EB4, GetPrivateProfileInt(L"Soliton", L"Corium", 500, ini_file));
    patch.WriteU32Triple((void *)0x007E1EC0, GetPrivateProfileInt(L"Gas_Shell_Launcher", L"Corium", 300, ini_file));
    patch.WriteU32Triple((void *)0x007E1ECC, GetPrivateProfileInt(L"Double_Plasma_Turret", L"Corium", 200, ini_file));
    patch.WriteU32Triple((void *)0x007E1EF0, GetPrivateProfileInt(L"Bio_Mine_Launcher", L"Corium", 350, ini_file)); 
    patch.WriteU32Triple((void *)0x007E1EE4, GetPrivateProfileInt(L"Jump_Mine_Launcher", L"Corium", 300, ini_file));
    patch.WriteU32((void *)0x007E1EE0, GetPrivateProfileInt(L"Ion_Reflector", L"Corium", 200, ini_file));
    patch.WriteU32Triple((void *)0x007E1F44, GetPrivateProfileInt(L"Parcher", L"Corium", 350, ini_file));
    
    // AMMO
    // WS 
    patch.WriteU32((void *)0x00794098, GetPrivateProfileInt(L"HF_Cannon", L"Ammo", 0, ini_file));
    patch.WriteU32((void *)0x007940A0, GetPrivateProfileInt(L"STOLp", L"Ammo", 40, ini_file));
    patch.WriteU32((void *)0x00794130, GetPrivateProfileInt(L"Plasma_Cannon", L"Ammo", 0, ini_file));
    
    // BO
    patch.WriteU32((void *)0x007940D8, GetPrivateProfileInt(L"Light_Laser", L"Ammo", 30, ini_file));
    patch.WriteU32((void *)0x007940F8, GetPrivateProfileInt(L"Heavy_Laser", L"Ammo", 60, ini_file));
    patch.WriteU32((void *)0x007940E0, GetPrivateProfileInt(L"Magnetic_Mine_Launcher", L"Ammo_main", 40, ini_file));
    patch.WriteU32((void *)0x007940E0, GetPrivateProfileInt(L"Magnetic_Mine_Launcher", L"Ammo_secondary", 10, ini_file));
    patch.WriteU32((void *)0x00794100, GetPrivateProfileInt(L"EM_Launcher", L"Ammo", 20, ini_file));

    // SI
    patch.WriteU32((void *)0x007941D8, GetPrivateProfileInt(L"Gas_Shell_Launcher", L"Ammo", 40, ini_file));
    patch.WriteU32((void *)0x007941E0, GetPrivateProfileInt(L"DPT", L"Ammo", 40, ini_file));
    patch.WriteU32((void *)0x00794200, GetPrivateProfileInt(L"Pulsar", L"Ammo", 0, ini_file)); 
    patch.WriteU32((void *)0x007941F8, GetPrivateProfileInt(L"Bio_Mine_Launcher", L"Ammo", 15, ini_file));
    patch.WriteU32((void *)0x007941F0, GetPrivateProfileInt(L"Jump_Mine_Launcher", L"Ammo", 15, ini_file));
    patch.WriteU32((void *)0x00794230, GetPrivateProfileInt(L"Parcher", L"Ammo", 0, ini_file));


    // RESUPPLY
    // WS
    patch.WriteU32((void *)0x00793E88, GetPrivateProfileInt(L"HF_Cannon", L"Resupply", 0, ini_file));
    patch.WriteU32((void *)0x00793E90, GetPrivateProfileInt(L"STOLp", L"Resupply", 1, ini_file));
    patch.WriteU32((void *)0x00793F20, GetPrivateProfileInt(L"Plasma_Cannon", L"Resupply", 0, ini_file));
    
    // BO
    patch.WriteU32((void *)0x00793EC8, GetPrivateProfileInt(L"Light_Laser", L"Resupply", 2, ini_file));
    patch.WriteU32((void *)0x00793EE8, GetPrivateProfileInt(L"Heavy_Laser", L"Resupply", 2, ini_file));
    patch.WriteU32((void *)0x00793ED0, GetPrivateProfileInt(L"Magnetic_Mine_Launcher", L"Resupply_main", 1, ini_file));
    patch.WriteU32((void *)0x00793ED4, GetPrivateProfileInt(L"Magnetic_Mine_Launcher", L"Resupply_secondary", 1, ini_file));
    patch.WriteU32((void *)0x00793EF0, GetPrivateProfileInt(L"EM_Launcher", L"Resupply", 1, ini_file));

    // SI
    patch.WriteU32((void *)0x00793FC8, GetPrivateProfileInt(L"Gas_Shell_Launcher", L"Resupply", 1, ini_file));
    patch.WriteU32((void *)0x00793FD0, GetPrivateProfileInt(L"DPT", L"Resupply", 0, ini_file));
    patch.WriteU32((void *)0x00793FF0, GetPrivateProfileInt(L"Pulsar", L"Resupply", 0, ini_file)); 
    patch.WriteU32((void *)0x00793FE8, GetPrivateProfileInt(L"Bio_Mine_Launcher", L"Resupply", 1, ini_file));
    patch.WriteU32((void *)0x00793FE0, GetPrivateProfileInt(L"Jump_Mine_Launcher", L"Resupply", 1, ini_file));
    patch.WriteU32((void *)0x00794018, GetPrivateProfileInt(L"Parcher", L"Resupply", 0, ini_file));


    // METAL/SILICON
    // COMMON HUMANS
    patch.WriteU32Dual((void *)0x007E24FC, GetPrivateProfileInt(L"Subcenter", L"Metal", 1800, ini_file));
    patch.WriteU32Dual((void *)0x007E2508, GetPrivateProfileInt(L"Repair_Docks", L"Metal", 700, ini_file));
    patch.WriteU32Dual((void *)0x007E2514, GetPrivateProfileInt(L"Arsenal", L"Metal", 1000, ini_file));
    patch.WriteU32Dual((void *)0x007E2520, GetPrivateProfileInt(L"Research_Center", L"Metal", 1400, ini_file));
    patch.WriteU32Dual((void *)0x007E252C, GetPrivateProfileInt(L"Sonar", L"Metal", 700, ini_file));
    patch.WriteU32Dual((void *)0x007E2538, GetPrivateProfileInt(L"Teleport", L"Metal", 1500, ini_file));
    patch.WriteU32Dual((void *)0x007E2550, GetPrivateProfileInt(L"Corium_Mine_Humans", L"Metal", 300, ini_file));
    patch.WriteU32Dual((void *)0x007E255C, GetPrivateProfileInt(L"Gold_Extractor", L"Metal", 600, ini_file));
    patch.WriteU32Dual((void *)0x007E2568, GetPrivateProfileInt(L"Depot", L"Metal", 300, ini_file));
    patch.WriteU32Dual((void *)0x007E2574, GetPrivateProfileInt(L"Infocenter", L"Metal", 500, ini_file));
    patch.WriteU32Dual((void *)0x007E2580, GetPrivateProfileInt(L"Disperser", L"Metal", 800, ini_file));
    patch.WriteU32Dual((void *)0x007E2658, GetPrivateProfileInt(L"Metal_Mine_Humans", L"Metal", 200, ini_file));
    patch.WriteU32Dual((void *)0x007E2664, GetPrivateProfileInt(L"Oxygen_Generator_Humans", L"Metal", 500, ini_file));
    patch.WriteU32Dual((void *)0x007E267C, GetPrivateProfileInt(L"Market_humans", L"Metal", 700, ini_file));

    // WS
    patch.WriteU32Dual((void *)0x007E25A4, GetPrivateProfileInt(L"Cybercenter_WS", L"Metal", 600, ini_file));
    patch.WriteU32Dual((void *)0x007E25B0, GetPrivateProfileInt(L"Shark_Control", L"Metal", 500, ini_file));
    patch.WriteU32Dual((void *)0x007E25C8, GetPrivateProfileInt(L"Psychotron", L"Metal", 900, ini_file));
    patch.WriteU32Dual((void *)0x007E27D8, GetPrivateProfileInt(L"Teleshield", L"Metal", 600, ini_file));

    patch.WriteU32Triple((void *)0x007E258C, GetPrivateProfileInt(L"HF_Cannon", L"Metal", 500, ini_file));
    patch.WriteU32Triple((void *)0x007E2598, GetPrivateProfileInt(L"STOLp", L"Metal", 800, ini_file));
    patch.WriteU32Triple((void *)0x007E25BC, GetPrivateProfileInt(L"USG", L"Metal", 600, ini_file)); 
    patch.WriteU32Triple((void *)0x007E2670, GetPrivateProfileInt(L"Plasma_Cannon", L"Metal", 900, ini_file)); 
    
    patch.WriteU32Triple((void *)0x007E25D4, GetPrivateProfileInt(L"Plasmatron", L"Metal", 600, ini_file)); // Plasmatron metal 1
    patch.WriteU32Triple((void *)0x007E25E0, GetPrivateProfileInt(L"Nuclear_Launcher", L"Metal", 1000, ini_file)); // Nuclear_Launcher metal 2


    // BO
    patch.WriteU32Dual((void *)0x007E2610, GetPrivateProfileInt(L"Cyber_laboratory_dolphins", L"Metal", 600, ini_file));
    patch.WriteU32Dual((void *)0x007E2604, GetPrivateProfileInt(L"Power_station", L"Metal", 500, ini_file));
    patch.WriteU32Dual((void *)0x007E2634, GetPrivateProfileInt(L"Protective_field_gen", L"Metal", 1000, ini_file));
    patch.WriteU32Dual((void *)0x007E2640, GetPrivateProfileInt(L"Force_field", L"Metal", 1800, ini_file));

    patch.WriteU32Triple((void *)0x007E25EC, GetPrivateProfileInt(L"Light_Laser", L"Metal", 400, ini_file)); // Light_Laser metal 04
    patch.WriteU32Triple((void *)0x007E25F8, GetPrivateProfileInt(L"Magnetic_Mine_Launcher", L"Metal", 600, ini_file)); // Magnetic_Mine_Launcher metal 14
    patch.WriteU32Triple((void *)0x007E261C, GetPrivateProfileInt(L"Heavy_Laser", L"Metal", 800, ini_file)); // Heavy_Laser metal 1
    patch.WriteU32Triple((void *)0x007E2628, GetPrivateProfileInt(L"EM_Launcher", L"Metal", 700, ini_file)); // EM_Launcher metal 12

    patch.WriteU32Triple((void *)0x007E264C, GetPrivateProfileInt(L"Lasbomb_Launcher", L"Metal", 1000, ini_file)); // Lasbomb_Launcher metal 2
    

    // SI
    patch.WriteU32((void *)0x007E33C0, GetPrivateProfileInt(L"Silicon_Extractor", L"Silicon", 700, ini_file)); // Silicon_Extractor silicon 06
    patch.WriteU32((void *)0x007E3438, GetPrivateProfileInt(L"Molecular_repair_facility", L"Silicon", 1000, ini_file)); // Molecular_repair_facility silicon 06
    patch.WriteU32((void *)0x007E3474, GetPrivateProfileInt(L"Quantum_Paralyzer", L"Silicon", 1000, ini_file)); // Quantum_Paralyzer silicon 06
    patch.WriteU32((void *)0x007E342C, GetPrivateProfileInt(L"Ion_field_generator", L"Silicon", 900, ini_file)); // Ion_field_generator silicon 06
    patch.WriteU32((void *)0x007E3420, GetPrivateProfileInt(L"Gate", L"Silicon", 1000, ini_file)); // Gate silicon 06
    patch.WriteU32((void *)0x007E33B4, GetPrivateProfileInt(L"Recyclotron", L"Silicon", 1000, ini_file)); // Recyclotron silicon 06
    patch.WriteU32((void *)0x007E33A8, GetPrivateProfileInt(L"Replenish_pod", L"Silicon", 600, ini_file)); // Replenish_pod silicon 06
    patch.WriteU32((void *)0x007E336C, GetPrivateProfileInt(L"Biolocator", L"Silicon", 600, ini_file)); // Biolocator silicon 06
    patch.WriteU32((void *)0x007E3360, GetPrivateProfileInt(L"Protoplasm_Generator", L"Silicon", 1500, ini_file)); // Protoplasm_Generator silicon 06
    patch.WriteU32((void *)0x007E3354, GetPrivateProfileInt(L"Arsenal_SI", L"Silicon", 900, ini_file)); // Arsenal_SI silicon 06
    patch.WriteU32((void *)0x007E32F4, GetPrivateProfileInt(L"Core", L"Silicon", 1200, ini_file)); // Core silicon 06
    patch.WriteU32((void *)0x007E3300, GetPrivateProfileInt(L"Tech_Module", L"Silicon", 600, ini_file)); // Tech_Module silicon 06
    patch.WriteU32((void *)0x007E330C, GetPrivateProfileInt(L"Tech_Module", L"Silicon", 600, ini_file)); // Tech_Module silicon 06
    patch.WriteU32((void *)0x007E3318, GetPrivateProfileInt(L"Tech_Module", L"Silicon", 600, ini_file)); // Tech_Module silicon 06
    patch.WriteU32((void *)0x007E3324, GetPrivateProfileInt(L"Tech_Module", L"Silicon", 600, ini_file)); // Tech_Module silicon 06
    patch.WriteU32((void *)0x007E3330, GetPrivateProfileInt(L"Tech_Module", L"Silicon", 600, ini_file)); // Tech_Module silicon 06
    patch.WriteU32((void *)0x007E333C, GetPrivateProfileInt(L"Tech_Module", L"Silicon", 600, ini_file)); // Tech_Module silicon 06
    patch.WriteU32((void *)0x007E3348, GetPrivateProfileInt(L"Tech_Module", L"Silicon", 600, ini_file)); // Tech_Module silicon 06
    patch.WriteU32((void *)0x007E3390, GetPrivateProfileInt(L"Depot_SI", L"Silicon", 300, ini_file)); // Depot_SI silicon 06
    patch.WriteU32((void *)0x007E3370, GetPrivateProfileInt(L"Corium_Mine_SI", L"Silicon", 300, ini_file)); // Corium_Mine_SI silicon 06
    patch.WriteU32((void *)0x007E3374, GetPrivateProfileInt(L"Corium_Mine_SI", L"Silicon", 300, ini_file)); // Corium_Mine_SI silicon 06
    patch.WriteU32((void *)0x007E3378, GetPrivateProfileInt(L"Corium_Mine_SI", L"Silicon", 300, ini_file)); // Corium_Mine_SI silicon 06
    patch.WriteU32((void *)0x007E339C, GetPrivateProfileInt(L"Energy_accumulator", L"Silicon", 800, ini_file)); // Energy_accumulator silicon 06
    patch.WriteU32((void *)0x007E3384, GetPrivateProfileInt(L"Energy_converter", L"Silicon", 800, ini_file)); // Energy_converter silicon 06
    
    patch.WriteU32Triple((void *)0x007E340C, GetPrivateProfileInt(L"Pulsar", L"Silicon", 500, ini_file)); // Pulsar silicon 05
    patch.WriteU32Triple((void *)0x007E33C4, GetPrivateProfileInt(L"Soliton", L"Silicon", 800, ini_file)); // Soliton silicon 05
    patch.WriteU32Triple((void *)0x007E33D0, GetPrivateProfileInt(L"Gas_Shell_Launcher", L"Silicon", 900, ini_file)); // Gas_Shell_Launcher silicon 12
    patch.WriteU32Triple((void *)0x007E33DC, GetPrivateProfileInt(L"Double_Plasma_Turret", L"Silicon", 800, ini_file));  // DPT silicon 09
    patch.WriteU32((void *)0x007E33F0, GetPrivateProfileInt(L"Ion_Reflector", L"Silicon", 700, ini_file));  // Ion_Reflector silicon 06
    patch.WriteU32Triple((void *)0x007E3400, GetPrivateProfileInt(L"Bio_Mine_Launcher", L"Silicon", 800, ini_file));  // Bio_Mine_Launcher silicon 07
    patch.WriteU32Triple((void *)0x007E33F4, GetPrivateProfileInt(L"Jump_Mine_Launcher", L"Silicon", 900, ini_file));  // Jump_Mine_Launcher silicon 07
    patch.WriteU32Triple((void *)0x007E3454, GetPrivateProfileInt(L"Parcher", L"Silicon", 900, ini_file)); // Parcher silicon 14
    
    patch.WriteU32((void *)0x007E3450, GetPrivateProfileInt(L"Orbital_laser", L"Silicon", 1100, ini_file)); // Orbital_laser launcher silicon 2
    patch.WriteU32((void *)0x007E3468, GetPrivateProfileInt(L"Vacuum_Bomb", L"Silicon", 800, ini_file)); // Vacuum_Bomb launcher silicon 2

    // BUILDTIME
    // COMMON HUMANS
    patch.WriteU32Dual((void *)0x007E3DC4, GetPrivateProfileInt(L"Subcenter", L"BuildTime", 2250, ini_file));
    patch.WriteU32Dual((void *)0x007E3DD0, GetPrivateProfileInt(L"Repair_Docks", L"BuildTime", 700, ini_file));
    patch.WriteU32Dual((void *)0x007E3DDC, GetPrivateProfileInt(L"Arsenal", L"BuildTime", 1000, ini_file));
    patch.WriteU32Dual((void *)0x007E3DE8, GetPrivateProfileInt(L"Research_Center", L"BuildTime", 1500, ini_file));
    patch.WriteU32Dual((void *)0x007E3DF4, GetPrivateProfileInt(L"Sonar", L"BuildTime", 500, ini_file));
    patch.WriteU32Triple((void *)0x007E3E00, GetPrivateProfileInt(L"Teleport", L"BuildTime", 2250, ini_file));
    patch.WriteU32Triple((void *)0x007E3E18, GetPrivateProfileInt(L"Corium_Mine_Humans", L"BuildTime", 500, ini_file));
    patch.WriteU32Dual((void *)0x007E3E24, GetPrivateProfileInt(L"Gold_Extractor", L"BuildTime", 500, ini_file));
    patch.WriteU32Dual((void *)0x007E3E30, GetPrivateProfileInt(L"Depot", L"BuildTime", 1000, ini_file));
    patch.WriteU32Dual((void *)0x007E3E3C, GetPrivateProfileInt(L"Infocenter", L"BuildTime", 1500, ini_file));
    patch.WriteU32Dual((void *)0x007E3E48, GetPrivateProfileInt(L"Disperser", L"BuildTime", 500, ini_file));
    patch.WriteU32Dual((void *)0x007E3F20, GetPrivateProfileInt(L"Metal_Mine_Humans", L"BuildTime", 500, ini_file));
    patch.WriteU32Dual((void *)0x007E3F2C, GetPrivateProfileInt(L"Oxygen_Generator_Humans", L"BuildTime", 500, ini_file));
    patch.WriteU32Dual((void *)0x007E3F44, GetPrivateProfileInt(L"Market_humans", L"BuildTime", 1500, ini_file));
    
    // WS
    patch.WriteU32Dual((void *)0x007E3E6C, GetPrivateProfileInt(L"Cybercenter_WS", L"BuildTime", 1500, ini_file));
    patch.WriteU32Dual((void *)0x007E3E78, GetPrivateProfileInt(L"Shark_Control", L"BuildTime", 625, ini_file));
    patch.WriteU32Dual((void *)0x007E3E90, GetPrivateProfileInt(L"Psychotron", L"BuildTime", 1125, ini_file));
    patch.WriteU32Dual((void *)0x007E40A0, GetPrivateProfileInt(L"Teleshield", L"BuildTime", 1500, ini_file));

    patch.WriteU32Triple((void *)0x007E3E54, GetPrivateProfileInt(L"HF_Cannon", L"BuildTime", 500, ini_file));
    patch.WriteU32Triple((void *)0x007E3E60, GetPrivateProfileInt(L"STOLp", L"BuildTime", 750, ini_file)); 
    patch.WriteU32Triple((void *)0x007E3E84, GetPrivateProfileInt(L"USG", L"BuildTime", 625, ini_file));
    patch.WriteU32Triple((void *)0x007E3F38, GetPrivateProfileInt(L"Plasma_Cannon", L"BuildTime", 625, ini_file));
    
    patch.WriteU32Triple((void *)0x007E3E9C, GetPrivateProfileInt(L"Plasmatron", L"BuildTime", 1500, ini_file));
    patch.WriteU32Triple((void *)0x007E3EA8, GetPrivateProfileInt(L"Nuclear_Launcher", L"BuildTime", 1500, ini_file));

    // BO
    patch.WriteU32Dual((void *)0x007E3ECC, GetPrivateProfileInt(L"Power_station", L"BuildTime", 750, ini_file));
    patch.WriteU32Dual((void *)0x007E3ED8, GetPrivateProfileInt(L"Cyber_laboratory_dolphins", L"BuildTime", 750, ini_file));
    patch.WriteU32Dual((void *)0x007E3EFC, GetPrivateProfileInt(L"Protective_field_gen", L"BuildTime", 1000, ini_file));
    patch.WriteU32Dual((void *)0x007E3F08, GetPrivateProfileInt(L"Force_field", L"BuildTime", 2250, ini_file));

    patch.WriteU32Triple((void *)0x007E3EB4, GetPrivateProfileInt(L"Light_Laser", L"BuildTime", 500, ini_file));
    patch.WriteU32Triple((void *)0x007E3EE4, GetPrivateProfileInt(L"Heavy_Laser", L"BuildTime", 750, ini_file));
    patch.WriteU32Triple((void *)0x007E3EC0, GetPrivateProfileInt(L"Magnetic_Mine_Launcher", L"BuildTime", 625, ini_file));
    patch.WriteU32Triple((void *)0x007E3EF0, GetPrivateProfileInt(L"EM_Launcher", L"BuildTime", 750, ini_file));

    patch.WriteU32Triple((void *)0x007E3F14, GetPrivateProfileInt(L"Lasbomb_Launcher", L"BuildTime", 1500, ini_file));

    // SI
    patch.WriteU32((void *)0x007E3F58, GetPrivateProfileInt(L"Core", L"BuildTime", 1125, ini_file)); // Core buildtime
    patch.WriteU32((void *)0x007E3F64, GetPrivateProfileInt(L"Tech_Module", L"BuildTime", 1500, ini_file)); // Tech_Module buildtime
    patch.WriteU32((void *)0x007E3F70, GetPrivateProfileInt(L"Tech_Module", L"BuildTime", 1500, ini_file)); // Tech_Module buildtime
    patch.WriteU32((void *)0x007E3F7C, GetPrivateProfileInt(L"Tech_Module", L"BuildTime", 1500, ini_file)); // Tech_Module buildtime
    patch.WriteU32((void *)0x007E3F88, GetPrivateProfileInt(L"Tech_Module", L"BuildTime", 1500, ini_file)); // Tech_Module buildtime
    patch.WriteU32((void *)0x007E3F94, GetPrivateProfileInt(L"Tech_Module", L"BuildTime", 1500, ini_file)); // Tech_Module buildtime
    patch.WriteU32((void *)0x007E3FA0, GetPrivateProfileInt(L"Tech_Module", L"BuildTime", 1500, ini_file)); // Tech_Module buildtime
    patch.WriteU32((void *)0x007E3FAC, GetPrivateProfileInt(L"Tech_Module", L"BuildTime", 1500, ini_file)); // Tech_Module buildtime
    patch.WriteU32((void *)0x007E3FB8, GetPrivateProfileInt(L"Arsenal_SI", L"BuildTime", 1125, ini_file)); // Arsenal_SI buildtime
    patch.WriteU32((void *)0x007E3FC4, GetPrivateProfileInt(L"Protoplasm_Generator", L"BuildTime", 2250, ini_file)); // Protoplasm_Generator buildtime
    patch.WriteU32((void *)0x007E3FD0, GetPrivateProfileInt(L"Biolocator", L"BuildTime", 750, ini_file)); // Biolocator buildtime
    patch.WriteU32((void *)0x007E3FD4, GetPrivateProfileInt(L"Corium_Mine_SI", L"BuildTime", 500, ini_file)); // Corium_Mine_SI buildtime
    patch.WriteU32((void *)0x007E3FD8, GetPrivateProfileInt(L"Corium_Mine_SI", L"BuildTime", 500, ini_file)); // Corium_Mine_SI buildtime
    patch.WriteU32((void *)0x007E3FDC, GetPrivateProfileInt(L"Corium_Mine_SI", L"BuildTime", 500, ini_file)); // Corium_Mine_SI buildtime
    patch.WriteU32((void *)0x007E3FE8, GetPrivateProfileInt(L"Energy_converter", L"BuildTime", 1000, ini_file)); // Energy_converter buildtime
    patch.WriteU32((void *)0x007E3FF4, GetPrivateProfileInt(L"Depot_SI", L"BuildTime", 500, ini_file)); // Depot_SI buildtime
    patch.WriteU32((void *)0x007E4000, GetPrivateProfileInt(L"Energy_accumulator", L"BuildTime", 750, ini_file)); // Energy_accumulator buildtime
    patch.WriteU32((void *)0x007E400C, GetPrivateProfileInt(L"Replenish_pod", L"BuildTime", 750, ini_file)); // Replenish_pod buildtime
    patch.WriteU32((void *)0x007E4018, GetPrivateProfileInt(L"Recyclotron", L"BuildTime", 1125, ini_file)); // Recyclotron buildtime
    patch.WriteU32((void *)0x007E4024, GetPrivateProfileInt(L"Silicon_Extractor", L"BuildTime", 750, ini_file)); // Silicon_Extractor buildtime
    patch.WriteU32((void *)0x007E4084, GetPrivateProfileInt(L"Gate", L"BuildTime", 1500, ini_file)); // Gate buildtime
    patch.WriteU32((void *)0x007E4090, GetPrivateProfileInt(L"Ion_field_generator", L"BuildTime", 1250, ini_file)); // Gate buildtime
    patch.WriteU32((void *)0x007E409C, GetPrivateProfileInt(L"Molecular_repair_facility", L"BuildTime", 2250, ini_file)); // Molecular_repair_facility buildtime
    patch.WriteU32((void *)0x007E40D8, GetPrivateProfileInt(L"Quantum_Paralyzer", L"BuildTime", 1500, ini_file)); // Gate buildtime

    patch.WriteU32Triple((void *)0x007E4028, GetPrivateProfileInt(L"Soliton", L"BuildTime", 750, ini_file));
    patch.WriteU32Triple((void *)0x007E4034, GetPrivateProfileInt(L"Gas_Shell_Launcher", L"BuildTime", 625, ini_file));
    patch.WriteU32Triple((void *)0x007E4040, GetPrivateProfileInt(L"Double_Plasma_Turret", L"BuildTime", 500, ini_file));
    patch.WriteU32((void *)0x007E4054, GetPrivateProfileInt(L"Ion_Reflector", L"BuildTime", 750, ini_file));
    patch.WriteU32Triple((void *)0x007E4058, GetPrivateProfileInt(L"Jump_Mine_Launcher", L"BuildTime", 875, ini_file));
    patch.WriteU32Triple((void *)0x007E4064, GetPrivateProfileInt(L"Bio_Mine_Launcher", L"BuildTime", 875, ini_file));
    patch.WriteU32Triple((void *)0x007E4070, GetPrivateProfileInt(L"Pulsar", L"BuildTime", 500, ini_file));
    patch.WriteU32Triple((void *)0x007E40B8, GetPrivateProfileInt(L"Parcher", L"BuildTime", 875, ini_file));
    
    patch.WriteU32((void *)0x007E40B4, GetPrivateProfileInt(L"Orbital_laser", L"BuildTime", 1250, ini_file));
    patch.WriteU32((void *)0x007E40D8, GetPrivateProfileInt(L"Vacuum_Bomb", L"BuildTime", 1500, ini_file));
    

    // RANGE
    // Unlock Turrets Range 8->10
    patch.WriteByte((void *)0x004C3CC2, 246);
    patch.WriteByte((void *)0x004C3CF0, 246);
    patch.WriteByte((void *)0x004C3CF3, 10);
    patch.WriteByte((void *)0x004C3CC5, 10);
    patch.WriteByte((void *)0x004C426F, 10);
    patch.WriteByte((void *)0x004C4281, 10);
    //

    patch.WriteByte((void *)0x00792208, GetPrivateProfileInt(L"HF_Cannon", L"Range", 8, ini_file)); // HF_Cannon first range 7
    patch.WriteByte((void *)0x00792218, GetPrivateProfileInt(L"STOLp", L"Range", 8, ini_file)); // STOLp first range 8
    patch.WriteByte((void *)0x00792338, GetPrivateProfileInt(L"Plasma_Cannon", L"Range", 8, ini_file)); // Plasma_Cannon first range 9 

    patch.WriteByte((void *)0x00792288, GetPrivateProfileInt(L"Light_Laser", L"Range_1", 7, ini_file)); // Light_Laser first range 7
    patch.WriteByte((void *)0x0079228C, GetPrivateProfileInt(L"Light_Laser", L"Range_2", 9, ini_file)); // Light_Laser second range 8
    patch.WriteByte((void *)0x007922C8, GetPrivateProfileInt(L"Heavy_Laser", L"Range_1", 8, ini_file)); // Heavy_Laser first range 6
    patch.WriteByte((void *)0x007922CC, GetPrivateProfileInt(L"Heavy_Laser", L"Range_2	", 10, ini_file)); // Heavy_Laser second range 8 
    patch.WriteByte((void *)0x00792298, GetPrivateProfileInt(L"Magnetic_Mine_Launcher", L"Range", 8, ini_file)); // Magnetic_Mine_Launcher range 7 
    patch.WriteByte((void *)0x007922A0, GetPrivateProfileInt(L"Magnetic_Mine_Launcher", L"Range_Mines", 8, ini_file));  // Magnetic_Mine_Launcher mines range 8 
    patch.WriteByte((void *)0x007922D8, GetPrivateProfileInt(L"EM_Launcher", L"Range", 8, ini_file)); // EM_Launcher first range 9

    patch.WriteByte((void *)0x00792488, GetPrivateProfileInt(L"Gas_Shell_Launcher", L"Range", 8, ini_file));  // Gas_Shell_Launcher first range 7
    patch.WriteU32((void *)0x00792498, GetPrivateProfileInt(L"Double_Plasma_Turret", L"Range_1", 8, ini_file));  // DPT range 1 8
    patch.WriteU32((void *)0x0079249C, GetPrivateProfileInt(L"Double_Plasma_Turret", L"Range_2", 10, ini_file)); // DPT range 2 10
    patch.WriteByte((void *)0x007924A8, GetPrivateProfileInt(L"Ion_Reflector", L"Range", 8, ini_file)); // Ion_Reflector first range 8
    patch.WriteByte((void *)0x007924D8, GetPrivateProfileInt(L"Pulsar", L"Range", 8, ini_file)); // Pulsar first range 7
    patch.WriteByte((void *)0x00792538, GetPrivateProfileInt(L"Parcher", L"Range", 8, ini_file)); // Parcher first range 9
    //


    // ATTACK COOLDOWN
    patch.WriteU32((void *)0x007DFDF0, GetPrivateProfileInt(L"HF_Cannon", L"Reload_1", 50, ini_file));
    patch.WriteU32((void *)0x007DFDF4, GetPrivateProfileInt(L"HF_Cannon", L"Reload_2", 25, ini_file));
    patch.WriteU32((void *)0x007DFE00, GetPrivateProfileInt(L"STOLp", L"Reload", 75, ini_file));
    //patch.WriteU32((void *)0x007DFF20, GetPrivateProfileInt(L"USG", L"Reload", 100, ini_file)); UNKNOWN ADRESS!
    patch.WriteU32((void *)0x007DFF20, GetPrivateProfileInt(L"Plasma_Cannon", L"Reload", 100, ini_file));

    patch.WriteU32((void *)0x007DFE70, GetPrivateProfileInt(L"Light_Laser", L"Reload_1", 25, ini_file));
    patch.WriteU32((void *)0x007DFE74, GetPrivateProfileInt(L"Light_Laser", L"Reload_2", 13, ini_file));
    patch.WriteU32((void *)0x007DFEB0, GetPrivateProfileInt(L"Heavy_Laser", L"Reload_1", 50, ini_file));
    patch.WriteU32((void *)0x007DFEB4, GetPrivateProfileInt(L"Heavy_Laser", L"Reload_2", 25, ini_file));
    patch.WriteU32((void *)0x007DFE80, GetPrivateProfileInt(L"Magnetic_Mine_Launcher", L"Reload_main", 50, ini_file));
    patch.WriteU32((void *)0x007DFE88, GetPrivateProfileInt(L"Magnetic_Mine_Launcher", L"Reload_secondary", 75, ini_file));
    patch.WriteU32((void *)0x007DFEC0, GetPrivateProfileInt(L"EM_Launcher", L"Reload", 50, ini_file));

    //patch.WriteU32((void *)0x007DFF20, GetPrivateProfileInt(L"Soliton", L"Reload", 100, ini_file)); UNKNOWN ADRESS!
    patch.WriteU32((void *)0x007E0070, GetPrivateProfileInt(L"Gas_Shell_Launcher", L"Reload_1", 50, ini_file));
    patch.WriteU32((void *)0x007E0074, GetPrivateProfileInt(L"Gas_Shell_Launcher", L"Reload_2", 25, ini_file));
    patch.WriteU32((void *)0x007E0080, GetPrivateProfileInt(L"Double_Plasma_Turret", L"Reload", 50, ini_file)); 
    patch.WriteU32((void *)0x007E0090, GetPrivateProfileInt(L"Ion_Reflector", L"Reload", 25, ini_file)); 
    patch.WriteU32((void *)0x007E00A0, GetPrivateProfileInt(L"Jump_Mine_Launcher", L"Reload", 75, ini_file));
    patch.WriteU32((void *)0x007E00B0, GetPrivateProfileInt(L"Bio_Mine_Launcher", L"Reload", 175, ini_file)); 
    patch.WriteU32((void *)0x007E00C0, GetPrivateProfileInt(L"Pulsar", L"Reload_1", 50, ini_file));
    patch.WriteU32((void *)0x007E00C4, GetPrivateProfileInt(L"Pulsar", L"Reload_2", 25, ini_file));
    patch.WriteU32((void *)0x007E0120, GetPrivateProfileInt(L"Parcher", L"Reload", 50, ini_file));
    

    // WEAPON    
    // WS    
    patch.WriteU32Dual((void *)0x00792DC0, GetPrivateProfileInt(L"HF_Cannon", L"Weapon", 160, ini_file));
    patch.WriteU32Dual((void *)0x00792DD8, GetPrivateProfileInt(L"STOLp", L"Weapon", 151, ini_file));
    patch.WriteU32((void *)0x00792E20, GetPrivateProfileInt(L"USG", L"Weapon", 192, ini_file));
    patch.WriteU32((void *)0x00792F88, GetPrivateProfileInt(L"Plasma_Cannon", L"Weapon", 164, ini_file));
    
    // BO
    patch.WriteU32((void *)0x00792E80, GetPrivateProfileInt(L"Light_Laser", L"Weapon", 156, ini_file));
    patch.WriteU32Dual((void *)0x00792EE0, GetPrivateProfileInt(L"Heavy_Laser", L"Weapon", 158, ini_file));
    patch.WriteU32((void *)0x00792E98, GetPrivateProfileInt(L"Magnetic_Mine_Launcher", L"Weapon_main", 153, ini_file));
    patch.WriteU32Dual((void *)0x00792EA4, GetPrivateProfileInt(L"Magnetic_Mine_Launcher", L"Weapon_secondary", 171, ini_file));
    patch.WriteU32((void *)0x00792EF8, GetPrivateProfileInt(L"EM_Launcher", L"Weapon", 154, ini_file));

    // SI
    patch.WriteU32Dual((void *)0x00793180, GetPrivateProfileInt(L"Gas_Shell_Launcher", L"Weapon", 174, ini_file));
    patch.WriteU32Dual((void *)0x00793198, GetPrivateProfileInt(L"Double_Plasma_Turret", L"Weapon", 186, ini_file));
    patch.WriteU32((void *)0x007931B0, GetPrivateProfileInt(L"Ion_Reflector", L"Weapon", 176, ini_file)); 
    patch.WriteU32((void *)0x007931C8, GetPrivateProfileInt(L"Jump_Mine_Launcher", L"Weapon", 179, ini_file));
    patch.WriteU32((void *)0x007931E0, GetPrivateProfileInt(L"Bio_Mine_Launcher", L"Weapon", 188, ini_file)); 
    patch.WriteU32((void *)0x007931F8, GetPrivateProfileInt(L"Pulsar", L"Weapon", 191, ini_file));
    patch.WriteU32((void *)0x00793270, GetPrivateProfileInt(L"Parcher", L"Weapon", 178, ini_file));
    



    // SUBMARINES
    // METAL/SILICON
    // WS
    patch.WriteU32((void *)0x007E07A0, GetPrivateProfileInt(L"Sentinel", L"Metal", 200, ini_file));
    patch.WriteU32((void *)0x007E07A4, GetPrivateProfileInt(L"Hunter", L"Metal", 400, ini_file));
    patch.WriteU32((void *)0x007E07A8, GetPrivateProfileInt(L"Cruiser", L"Metal", 1000, ini_file));
    patch.WriteU32((void *)0x007E07AC, GetPrivateProfileInt(L"Bomber", L"Metal", 1000, ini_file));
    patch.WriteU32((void *)0x007E07B0, GetPrivateProfileInt(L"Minelayer", L"Metal", 700, ini_file));
    patch.WriteU32((void *)0x007E07B4, GetPrivateProfileInt(L"Marauder", L"Metal", 800, ini_file));
    patch.WriteU32((void *)0x007E07B8, GetPrivateProfileInt(L"Repair_Platform_WS", L"Metal", 800, ini_file));
    patch.WriteU32((void *)0x007E07BC, GetPrivateProfileInt(L"Transport_Humans", L"Metal", 600, ini_file));
    patch.WriteU32((void *)0x007E07C0, GetPrivateProfileInt(L"Cyberworm", L"Metal", 200, ini_file));
    patch.WriteU32((void *)0x007E07C4, GetPrivateProfileInt(L"Terminator", L"Metal", 1000, ini_file));
    patch.WriteU32((void *)0x007E07C8, GetPrivateProfileInt(L"Liberator", L"Metal", 700, ini_file));
    patch.WriteU32((void *)0x007E07CC, GetPrivateProfileInt(L"Builder_Humans", L"Metal", 1000, ini_file));
    
    // BO
    patch.WriteU32((void *)0x007E07D0, GetPrivateProfileInt(L"Fighter", L"Metal", 300, ini_file));
    patch.WriteU32((void *)0x007E07D4, GetPrivateProfileInt(L"Destroyer", L"Metal", 500, ini_file)); 
    patch.WriteU32((void *)0x007E07D8, GetPrivateProfileInt(L"Heavy_Cruiser", L"Metal", 1200, ini_file));
    patch.WriteU32((void *)0x007E07DC, GetPrivateProfileInt(L"Invader", L"Metal", 800, ini_file));
    patch.WriteU32((void *)0x007E07E0, GetPrivateProfileInt(L"Defender", L"Metal", 700, ini_file));
    patch.WriteU32((void *)0x007E07E4, GetPrivateProfileInt(L"Raider", L"Metal", 700, ini_file)); 
    patch.WriteU32((void *)0x007E07E8, GetPrivateProfileInt(L"Repair_Platform_BO", L"Metal", 800, ini_file));
    patch.WriteU32((void *)0x007E07EC, GetPrivateProfileInt(L"Transport_Humans", L"Metal", 600, ini_file));
    patch.WriteU32((void *)0x007E07F0, GetPrivateProfileInt(L"Cyberdolphin", L"Metal", 400, ini_file));
    patch.WriteU32((void *)0x007E07F4, GetPrivateProfileInt(L"Phantom", L"Metal", 1000, ini_file));
    patch.WriteU32((void *)0x007E07F8, GetPrivateProfileInt(L"Avenger", L"Metal", 1200, ini_file));
    patch.WriteU32((void *)0x007E07FC, GetPrivateProfileInt(L"Builder_Humans", L"Metal", 1000, ini_file));
    patch.WriteU32((void *)0x007E0830, GetPrivateProfileInt(L"Stealth_Scout", L"Metal", 500, ini_file));
    
    // SI
    patch.WriteU32((void *)0x007E0A40, GetPrivateProfileInt(L"Module_Prototype", L"Silicon", 50, ini_file)); 
    patch.WriteU32((void *)0x007E0A44, GetPrivateProfileInt(L"Transport_SI", L"Silicon", 100, ini_file));
    patch.WriteU32((void *)0x007E0A48, GetPrivateProfileInt(L"Supplier", L"Silicon", 400, ini_file));
    patch.WriteU32((void *)0x007E0A4C, GetPrivateProfileInt(L"Paralizator", L"Silicon", 600, ini_file));
    patch.WriteU32((void *)0x007E0A50, GetPrivateProfileInt(L"Energizer", L"Silicon", 600, ini_file));
    patch.WriteU32((void *)0x007E0A54, GetPrivateProfileInt(L"Skat", L"Silicon", 300, ini_file)); 
    patch.WriteU32((void *)0x007E0A58, GetPrivateProfileInt(L"Dreadnaught", L"Silicon", 1000, ini_file)); 
    patch.WriteU32((void *)0x007E0A5C, GetPrivateProfileInt(L"Escort", L"Silicon", 800, ini_file));  
	patch.WriteU32((void *)0x007E0A60, GetPrivateProfileInt(L"Bio_Assaulter", L"Silicon", 700, ini_file));
    patch.WriteU32((void *)0x007E0A64, GetPrivateProfileInt(L"Usurper", L"Silicon", 500, ini_file)); 
    patch.WriteU32((void *)0x007E0A68, GetPrivateProfileInt(L"Psi_Zond", L"Silicon", 600, ini_file));
    patch.WriteU32((void *)0x007E0A6C, GetPrivateProfileInt(L"Explorer", L"Silicon", 200, ini_file));
	

    // CORIUM  
    // WS  
    patch.WriteU32((void *)0x007E0560, GetPrivateProfileInt(L"Sentinel", L"Corium", 40, ini_file));
    patch.WriteU32((void *)0x007E0564, GetPrivateProfileInt(L"Hunter", L"Corium", 80, ini_file));
    patch.WriteU32((void *)0x007E0568, GetPrivateProfileInt(L"Cruiser", L"Corium", 300, ini_file));
    patch.WriteU32((void *)0x007E056C, GetPrivateProfileInt(L"Bomber", L"Corium", 250, ini_file));
    patch.WriteU32((void *)0x007E0570, GetPrivateProfileInt(L"Minelayer", L"Corium", 90, ini_file));
    patch.WriteU32((void *)0x007E0574, GetPrivateProfileInt(L"Marauder", L"Corium", 100, ini_file));
    patch.WriteU32((void *)0x007E0578, GetPrivateProfileInt(L"Repair_Platform_WS", L"Corium", 0, ini_file));
    patch.WriteU32((void *)0x007E057C, GetPrivateProfileInt(L"Transport_Humans", L"Corium", 0, ini_file));
    patch.WriteU32((void *)0x007E0580, GetPrivateProfileInt(L"Cyberworm", L"Corium", 20, ini_file));
    patch.WriteU32((void *)0x007E0584, GetPrivateProfileInt(L"Terminator", L"Corium", 500, ini_file));
    patch.WriteU32((void *)0x007E0588, GetPrivateProfileInt(L"Liberator", L"Corium", 150, ini_file));
    patch.WriteU32((void *)0x007E058C, GetPrivateProfileInt(L"Builder_Humans", L"Corium", 0, ini_file));

    // BO
    patch.WriteU32((void *)0x007E0590, GetPrivateProfileInt(L"Fighter", L"Corium", 50, ini_file)); 
    patch.WriteU32((void *)0x007E0594, GetPrivateProfileInt(L"Destroyer", L"Corium", 80, ini_file)); 
    patch.WriteU32((void *)0x007E0598, GetPrivateProfileInt(L"Heavy_Cruiser", L"Corium", 300, ini_file)); 
    patch.WriteU32((void *)0x007E059C, GetPrivateProfileInt(L"Invader", L"Corium", 150, ini_file));
    patch.WriteU32((void *)0x007E05A0, GetPrivateProfileInt(L"Defender", L"Corium", 80, ini_file));
    patch.WriteU32((void *)0x007E05A4, GetPrivateProfileInt(L"Raider", L"Corium", 60, ini_file));
    patch.WriteU32((void *)0x007E05A8, GetPrivateProfileInt(L"Repair_Platform_BO", L"Corium", 0, ini_file));
    patch.WriteU32((void *)0x007E05AC, GetPrivateProfileInt(L"Transport_Humans", L"Corium", 0, ini_file));
    patch.WriteU32((void *)0x007E05B0, GetPrivateProfileInt(L"Cyberdolphin", L"Corium", 200, ini_file));
    patch.WriteU32((void *)0x007E05B4, GetPrivateProfileInt(L"Phantom", L"Corium", 250, ini_file));
    patch.WriteU32((void *)0x007E05B8, GetPrivateProfileInt(L"Avenger", L"Corium", 200, ini_file)); 
    patch.WriteU32((void *)0x007E05BC, GetPrivateProfileInt(L"Builder_Humans", L"Corium", 0, ini_file));
    patch.WriteU32((void *)0x007E05F0, GetPrivateProfileInt(L"Stealth_Scout", L"Corium", 40, ini_file));

    // SI 
    patch.WriteU32((void *)0x007E05C0, GetPrivateProfileInt(L"Module_Prototype", L"Corium", 0, ini_file)); 
    patch.WriteU32((void *)0x007E05C4, GetPrivateProfileInt(L"Transport_SI", L"Corium", 0, ini_file));
    patch.WriteU32((void *)0x007E05C8, GetPrivateProfileInt(L"Supplier", L"Corium", 0, ini_file));
    patch.WriteU32((void *)0x007E05CC, GetPrivateProfileInt(L"Paralizator", L"Corium", 400, ini_file));
    patch.WriteU32((void *)0x007E05D0, GetPrivateProfileInt(L"Energizer", L"Corium", 40, ini_file));
    patch.WriteU32((void *)0x007E05D4, GetPrivateProfileInt(L"Skat", L"Corium", 50, ini_file)); 
    patch.WriteU32((void *)0x007E05D8, GetPrivateProfileInt(L"Dreadnaught", L"Corium", 110, ini_file)); 
    patch.WriteU32((void *)0x007E05DC, GetPrivateProfileInt(L"Escort", L"Corium", 180, ini_file));  
	patch.WriteU32((void *)0x007E05E0, GetPrivateProfileInt(L"Bio_Assaulter", L"Corium", 200, ini_file));
    patch.WriteU32((void *)0x007E05E4, GetPrivateProfileInt(L"Usurper", L"Corium", 100, ini_file)); 
    patch.WriteU32((void *)0x007E05E8, GetPrivateProfileInt(L"Psi_Zond", L"Corium", 150, ini_file));
    patch.WriteU32((void *)0x007E05EC, GetPrivateProfileInt(L"Explorer", L"Corium", 40, ini_file));
    

    // BUILDTIME
    // WS
    patch.WriteU32((void *)0x007E04A0, GetPrivateProfileInt(L"Sentinel", L"BuildTime", 500, ini_file));
    patch.WriteU32((void *)0x007E04A4, GetPrivateProfileInt(L"Hunter", L"BuildTime", 750, ini_file));
    patch.WriteU32((void *)0x007E04A8, GetPrivateProfileInt(L"Cruiser", L"BuildTime", 1750, ini_file));
    patch.WriteU32((void *)0x007E04AC, GetPrivateProfileInt(L"Bomber", L"BuildTime", 1250, ini_file));
    patch.WriteU32((void *)0x007E04B0, GetPrivateProfileInt(L"Minelayer", L"BuildTime", 1000, ini_file));
    patch.WriteU32((void *)0x007E04B4, GetPrivateProfileInt(L"Marauder", L"BuildTime", 1000, ini_file));
    patch.WriteU32((void *)0x007E04B8, GetPrivateProfileInt(L"Repair_Platform_WS", L"BuildTime", 750, ini_file));
    patch.WriteU32((void *)0x007E04BC, GetPrivateProfileInt(L"Transport_Humans", L"BuildTime", 500, ini_file));
    patch.WriteU32((void *)0x007E04C0, GetPrivateProfileInt(L"Cyberworm", L"BuildTime", 750, ini_file));
    patch.WriteU32((void *)0x007E04C4, GetPrivateProfileInt(L"Terminator", L"BuildTime", 1500, ini_file));
    patch.WriteU32((void *)0x007E04C8, GetPrivateProfileInt(L"Liberator", L"BuildTime", 1500, ini_file));
    patch.WriteU32((void *)0x007E04CC, GetPrivateProfileInt(L"Builder_Humans", L"BuildTime", 750, ini_file));

    // BO
    patch.WriteU32((void *)0x007E04D0, GetPrivateProfileInt(L"Fighter", L"BuildTime", 500, ini_file)); 
    patch.WriteU32((void *)0x007E04D4, GetPrivateProfileInt(L"Destroyer", L"BuildTime", 1000, ini_file)); 
    patch.WriteU32((void *)0x007E04D8, GetPrivateProfileInt(L"Heavy_Cruiser", L"BuildTime", 1750, ini_file)); 
    patch.WriteU32((void *)0x007E04DC, GetPrivateProfileInt(L"Invader", L"BuildTime", 1250, ini_file));
    patch.WriteU32((void *)0x007E04E0, GetPrivateProfileInt(L"Defender", L"BuildTime", 1000, ini_file));
    patch.WriteU32((void *)0x007E04E4, GetPrivateProfileInt(L"Raider", L"BuildTime", 1000, ini_file));
    patch.WriteU32((void *)0x007E04E8, GetPrivateProfileInt(L"Repair_Platform_BO", L"BuildTime", 750, ini_file));
    patch.WriteU32((void *)0x007E04EC, GetPrivateProfileInt(L"Transport_Humans", L"BuildTime", 500, ini_file));
    patch.WriteU32((void *)0x007E04F0, GetPrivateProfileInt(L"Cyberdolphin", L"BuildTime", 875, ini_file));
    patch.WriteU32((void *)0x007E04F4, GetPrivateProfileInt(L"Phantom", L"BuildTime", 1500, ini_file));
    patch.WriteU32((void *)0x007E04F8, GetPrivateProfileInt(L"Avenger", L"BuildTime", 1500, ini_file)); 
    patch.WriteU32((void *)0x007E04FC, GetPrivateProfileInt(L"Builder_Humans", L"BuildTime", 750, ini_file));
    patch.WriteU32((void *)0x007E0530, GetPrivateProfileInt(L"Stealth_Scout", L"BuildTime", 500, ini_file));

    // SI
    patch.WriteU32((void *)0x007E0500, GetPrivateProfileInt(L"Module_Prototype", L"BuildTime", 175, ini_file)); 
    patch.WriteU32((void *)0x007E0504, GetPrivateProfileInt(L"Transport_SI", L"BuildTime", 375, ini_file));
    patch.WriteU32((void *)0x007E0508, GetPrivateProfileInt(L"Supplier", L"BuildTime", 1000, ini_file));
    patch.WriteU32((void *)0x007E050C, GetPrivateProfileInt(L"Paralizator", L"BuildTime", 1750, ini_file));
    patch.WriteU32((void *)0x007E0510, GetPrivateProfileInt(L"Energizer", L"BuildTime", 1000, ini_file));
    patch.WriteU32((void *)0x007E0514, GetPrivateProfileInt(L"Skat", L"BuildTime", 500, ini_file)); 
    patch.WriteU32((void *)0x007E0518, GetPrivateProfileInt(L"Dreadnaught", L"BuildTime", 1250, ini_file)); 
    patch.WriteU32((void *)0x007E051C, GetPrivateProfileInt(L"Escort", L"BuildTime", 1125, ini_file));  
	patch.WriteU32((void *)0x007E0520, GetPrivateProfileInt(L"Bio_Assaulter", L"BuildTime", 1500, ini_file));
    patch.WriteU32((void *)0x007E0524, GetPrivateProfileInt(L"Usurper", L"BuildTime", 1000, ini_file)); 
    patch.WriteU32((void *)0x007E0528, GetPrivateProfileInt(L"Psi_Zond", L"BuildTime", 1000, ini_file));
    patch.WriteU32((void *)0x007E052C, GetPrivateProfileInt(L"Explorer", L"BuildTime", 500, ini_file));


    // HP
    // WS
    patch.WriteU32((void *)0x007DFBB0, GetPrivateProfileInt(L"Sentinel", L"HP", 300, ini_file));
    patch.WriteU32((void *)0x007DFBB4, GetPrivateProfileInt(L"Hunter", L"HP", 500, ini_file));
    patch.WriteU32((void *)0x007DFBB8, GetPrivateProfileInt(L"Cruiser", L"HP", 1300, ini_file));
    patch.WriteU32((void *)0x007DFBBC, GetPrivateProfileInt(L"Bomber", L"HP", 2000, ini_file));
    patch.WriteU32((void *)0x007DFBC0, GetPrivateProfileInt(L"Minelayer", L"HP", 800, ini_file));
    patch.WriteU32((void *)0x007DFBC4, GetPrivateProfileInt(L"Marauder", L"HP", 1200, ini_file));
    patch.WriteU32((void *)0x007DFBC8, GetPrivateProfileInt(L"Repair_Platform_WS", L"HP", 800, ini_file));
    patch.WriteU32((void *)0x007DFBCC, GetPrivateProfileInt(L"Transport_Humans", L"HP", 400, ini_file));
    patch.WriteU32((void *)0x007DFBD0, GetPrivateProfileInt(L"Cyberworm", L"HP", 1000, ini_file));
    patch.WriteU32((void *)0x007DFBD4, GetPrivateProfileInt(L"Terminator", L"HP", 800, ini_file));
    patch.WriteU32((void *)0x007DFBD8, GetPrivateProfileInt(L"Liberator", L"HP", 700, ini_file));
    patch.WriteU32((void *)0x007DFBDC, GetPrivateProfileInt(L"Builder_Humans", L"HP", 800, ini_file));

    // BO
    patch.WriteU32((void *)0x007DFBE0, GetPrivateProfileInt(L"Fighter", L"HP", 400, ini_file));
    patch.WriteU32((void *)0x007DFBE4, GetPrivateProfileInt(L"Destroyer", L"HP", 600, ini_file));
    patch.WriteU32((void *)0x007DFBE8, GetPrivateProfileInt(L"Heavy_Cruiser", L"HP", 1500, ini_file)); 
    patch.WriteU32((void *)0x007DFBEC, GetPrivateProfileInt(L"Invader", L"HP", 800, ini_file));
    patch.WriteU32((void *)0x007DFBF0, GetPrivateProfileInt(L"Defender", L"HP", 900, ini_file));
    patch.WriteU32((void *)0x007DFBF4, GetPrivateProfileInt(L"Raider", L"HP", 1300, ini_file));
    patch.WriteU32((void *)0x007DFBF8, GetPrivateProfileInt(L"Repair_Platform_BO", L"HP", 800, ini_file));
    patch.WriteU32((void *)0x007DFBFC, GetPrivateProfileInt(L"Transport_Humans", L"HP", 400, ini_file));
    patch.WriteU32((void *)0x007DFC00, GetPrivateProfileInt(L"Cyberdolphin", L"HP", 1000, ini_file));
    patch.WriteU32((void *)0x007DFC04, GetPrivateProfileInt(L"Phantom", L"HP", 700, ini_file));
    patch.WriteU32((void *)0x007DFC08, GetPrivateProfileInt(L"Avenger", L"HP", 900, ini_file));
    patch.WriteU32((void *)0x007DFC0C, GetPrivateProfileInt(L"Builder_Humans", L"HP", 800, ini_file));
    patch.WriteU32((void *)0x007DFC40, GetPrivateProfileInt(L"Stealth_Scout", L"HP", 300, ini_file)); 

    // SI    
    patch.WriteU32((void *)0x007DFC10, GetPrivateProfileInt(L"Module_Prototype", L"HP", 200, ini_file));
    patch.WriteU32((void *)0x007DFC14, GetPrivateProfileInt(L"Transport_SI", L"HP", 500, ini_file)); 
    patch.WriteU32((void *)0x007DFC18, GetPrivateProfileInt(L"Supplier", L"HP", 600, ini_file));
    patch.WriteU32((void *)0x007DFC1C, GetPrivateProfileInt(L"Paralizator", L"HP", 400, ini_file));
    patch.WriteU32((void *)0x007DFC20, GetPrivateProfileInt(L"Energizer", L"HP", 600, ini_file));
    patch.WriteU32((void *)0x007DFC24, GetPrivateProfileInt(L"Skat", L"HP", 300, ini_file));
    patch.WriteU32((void *)0x007DFC28, GetPrivateProfileInt(L"Dreadnaught", L"HP", 1500, ini_file));
    patch.WriteU32((void *)0x007DFC2C, GetPrivateProfileInt(L"Escort", L"HP", 500, ini_file)); 
    patch.WriteU32((void *)0x007DFC30, GetPrivateProfileInt(L"Bio_Assaulter", L"HP", 900, ini_file));
    patch.WriteU32((void *)0x007DFC34, GetPrivateProfileInt(L"Usurper", L"HP", 1200, ini_file));
    patch.WriteU32((void *)0x007DFC38, GetPrivateProfileInt(L"Psi_Zond", L"HP", 700, ini_file));
    patch.WriteU32((void *)0x007DFC3C, GetPrivateProfileInt(L"Explorer", L"HP", 200, ini_file));
    

    // SPEED
    // WS
    patch.WriteU32((void *)0x007DFC70, GetPrivateProfileInt(L"Sentinel", L"Speed", 12, ini_file)); // Setinel
    patch.WriteU32((void *)0x007DFC74, GetPrivateProfileInt(L"Hunter", L"Speed", 9, ini_file)); // Hunter
    patch.WriteU32((void *)0x007DFC78, GetPrivateProfileInt(L"Cruiser", L"Speed", 6, ini_file));  // Cruiser
    patch.WriteU32((void *)0x007DFC7C, GetPrivateProfileInt(L"Bomber", L"Speed", 6, ini_file)); // DC Bomber (standard)
    patch.WriteU32((void *)0x007DFC80, GetPrivateProfileInt(L"Minelayer", L"Speed", 9, ini_file)); // Minelayer
    patch.WriteU32((void *)0x007DFC84, GetPrivateProfileInt(L"Marauder", L"Speed", 9, ini_file)); // Marauder
    patch.WriteU32((void *)0x007DFC88, GetPrivateProfileInt(L"Repair_Platform_WS", L"Speed", 9, ini_file)); // Repair platform
    patch.WriteU32((void *)0x007DFC8C, GetPrivateProfileInt(L"Transport_Humans", L"Speed", 6, ini_file)); // Transport
    patch.WriteU32((void *)0x007DFC90, GetPrivateProfileInt(L"Cyberworm", L"Speed", 6, ini_file)); // Cyberworm
    patch.WriteU32((void *)0x007DFC94, GetPrivateProfileInt(L"Terminator", L"Speed", 6, ini_file)); // Terminator
    patch.WriteU32((void *)0x007DFC98, GetPrivateProfileInt(L"Liberator", L"Speed", 9, ini_file)); // Liberator
    patch.WriteU32((void *)0x007DFC9C, GetPrivateProfileInt(L"Builder_Humans", L"Speed", 6, ini_file)); // Builder
    patch.WriteU32((void *)0x007DFD04, GetPrivateProfileInt(L"Flagship_WS", L"Speed", 9, ini_file)); // Flagship

    // BO
    patch.WriteU32((void *)0x007DFCA0, GetPrivateProfileInt(L"Fighter", L"Speed", 12, ini_file)); // Fighter
    patch.WriteU32((void *)0x007DFCA4, GetPrivateProfileInt(L"Destroyer", L"Speed", 9, ini_file)); // Destroyer
    patch.WriteU32((void *)0x007DFCA8, GetPrivateProfileInt(L"Heavy_Cruiser", L"Speed", 6, ini_file));  // Heavy Cruiser
    patch.WriteU32((void *)0x007DFCAC, GetPrivateProfileInt(L"Invader", L"Speed", 9, ini_file)); // Invader
    patch.WriteU32((void *)0x007DFCB0, GetPrivateProfileInt(L"Defender", L"Speed", 6, ini_file)); // Defender
    patch.WriteU32((void *)0x007DFCB4, GetPrivateProfileInt(L"Raider", L"Speed", 9, ini_file)); // Raider
    patch.WriteU32((void *)0x007DFCB8, GetPrivateProfileInt(L"Repair_Platform_BO", L"Speed", 6, ini_file)); // Repair platform
    patch.WriteU32((void *)0x007DFCBC, GetPrivateProfileInt(L"Transport_Humans", L"Speed", 6, ini_file));   // Transport
    patch.WriteU32((void *)0x007DFCC0, GetPrivateProfileInt(L"Cyberdolphin", L"Speed", 12, ini_file)); // Cyberdolphin
    patch.WriteU32((void *)0x007DFCC4, GetPrivateProfileInt(L"Phantom", L"Speed", 9, ini_file)); // Phantom
    patch.WriteU32((void *)0x007DFCC8, GetPrivateProfileInt(L"Avenger", L"Speed", 9, ini_file)); // Avenger
    patch.WriteU32((void *)0x007DFCCC, GetPrivateProfileInt(L"Builder_Humans", L"Speed", 6, ini_file)); // Builder
    patch.WriteU32((void *)0x007DFD00, GetPrivateProfileInt(L"Stealth_Scout", L"Speed", 12, ini_file)); // Builder
    patch.WriteU32((void *)0x007DFD08, GetPrivateProfileInt(L"Flagship_BO", L"Speed", 9, ini_file)); // Flagship

    // SI
    patch.WriteU32((void *)0x007DFCD0, GetPrivateProfileInt(L"Module_Prototype", L"Speed", 6, ini_file)); // Module-prototype
    patch.WriteU32((void *)0x007DFCD4, GetPrivateProfileInt(L"Transport_SI", L"Speed", 6, ini_file)); // Transport
    patch.WriteU32((void *)0x007DFCD8, GetPrivateProfileInt(L"Supplier", L"Speed", 6, ini_file)); // Supplier
    patch.WriteU32((void *)0x007DFCDC, GetPrivateProfileInt(L"Paralizator", L"Speed", 12, ini_file));   // Paralyzer
    patch.WriteU32((void *)0x007DFCE0, GetPrivateProfileInt(L"Energizer", L"Speed", 6, ini_file)); // Replenisher
    patch.WriteU32((void *)0x007DFCE4, GetPrivateProfileInt(L"Skat", L"Speed", 12, ini_file)); // SHS
    patch.WriteU32((void *)0x007DFCE8, GetPrivateProfileInt(L"Dreadnaught", L"Speed", 6, ini_file));   // Dreadnaught
    patch.WriteU32((void *)0x007DFCEC, GetPrivateProfileInt(L"Escort", L"Speed", 9, ini_file)); // Escort
    patch.WriteU32((void *)0x007DFCF0, GetPrivateProfileInt(L"Bio_Assaulter", L"Speed", 6, ini_file));   // Bio-assaulter
    patch.WriteU32((void *)0x007DFCF4, GetPrivateProfileInt(L"Usurper", L"Speed", 9, ini_file)); // Usurper
    patch.WriteU32((void *)0x007DFCF8, GetPrivateProfileInt(L"Psi_Zond", L"Speed", 9, ini_file)); // Psi-zond (Vermin)
    patch.WriteU32((void *)0x007DFCFC, GetPrivateProfileInt(L"Explorer", L"Speed", 12, ini_file)); // Explorer
    patch.WriteU32((void *)0x007DFD0C, GetPrivateProfileInt(L"Flagship_SI", L"Speed", 9, ini_file)); // Flagship

    // WEAPON
    // WS
    patch.WriteU32((void *)0x007A8B1C, GetPrivateProfileInt(L"Sentinel", L"Weapon", 159, ini_file));
    patch.WriteU32((void *)0x007A8B20, GetPrivateProfileInt(L"Hunter", L"Weapon", 150, ini_file));
    patch.WriteU32((void *)0x007A8B24, GetPrivateProfileInt(L"Cruiser", L"Weapon", 152, ini_file));
    patch.WriteU32((void *)0x007A8B28, GetPrivateProfileInt(L"Bomber", L"Weapon", 150, ini_file));
    patch.WriteU32((void *)0x007A8B2C, GetPrivateProfileInt(L"Minelayer", L"Weapon", 150, ini_file)); 
    patch.WriteU32((void *)0x007A8B30, GetPrivateProfileInt(L"Marauder", L"Weapon", 150, ini_file));
    //patch.WriteU32((void *)0x007A8B34, GetPrivateProfileInt(L"Repair_Platform_WS", L"Weapon", 0, ini_file));
    //patch.WriteU32((void *)0x007A8B38, GetPrivateProfileInt(L"Transport_Humans", L"Weapon", 0, ini_file)); 
    //patch.WriteU32((void *)0x007A8B3C, GetPrivateProfileInt(L"Cyberworm", L"Weapon", 0, ini_file));
    patch.WriteU32((void *)0x007A8B40, GetPrivateProfileInt(L"Terminator", L"Weapon", 164, ini_file));
    patch.WriteU32((void *)0x007A8B44, GetPrivateProfileInt(L"Liberator", L"Weapon", 150, ini_file));
    //patch.WriteU32((void *)0x007A8B48, GetPrivateProfileInt(L"Builder_Humans", L"Weapon", 0, ini_file)); 

    // BO
    patch.WriteU32((void *)0x007A8B4C, GetPrivateProfileInt(L"Fighter", L"Weapon", 150, ini_file));
    patch.WriteU32((void *)0x007A8B50, GetPrivateProfileInt(L"Destroyer", L"Weapon", 172, ini_file));
    patch.WriteU32((void *)0x007A8B54, GetPrivateProfileInt(L"Heavy_Cruiser", L"Weapon", 157, ini_file)); 
    patch.WriteU32((void *)0x007A8B58, GetPrivateProfileInt(L"Invader", L"Weapon", 153, ini_file));
    patch.WriteU32((void *)0x007A8B5C, GetPrivateProfileInt(L"Defender", L"Weapon", 150, ini_file));
    patch.WriteU32((void *)0x007A8B60, GetPrivateProfileInt(L"Raider", L"Weapon", 156, ini_file));
    //patch.WriteU32((void *)0x007A8B64, GetPrivateProfileInt(L"Repair_Platform_BO", L"Weapon", 0, ini_file));
    //patch.WriteU32((void *)0x007A8B68, GetPrivateProfileInt(L"Transport_Humans", L"Weapon", 0, ini_file));
    //patch.WriteU32((void *)0x007A8B6C, GetPrivateProfileInt(L"Cyberdolphin", L"Weapon", 0, ini_file));
    patch.WriteU32((void *)0x007A8B70, GetPrivateProfileInt(L"Phantom", L"Weapon", 157, ini_file));
    patch.WriteU32((void *)0x007A8B74, GetPrivateProfileInt(L"Avenger", L"Weapon", 156, ini_file));
    patch.WriteU32((void *)0x00462727, GetPrivateProfileInt(L"Avenger", L"Weapon_ability", 161, ini_file));
    //patch.WriteU32((void *)0x007A8B78, GetPrivateProfileInt(L"Builder_Humans", L"Weapon", 0, ini_file));
    //patch.WriteU32((void *)0x007A8BA8, GetPrivateProfileInt(L"Stealth_Scout", L"Weapon", 0, ini_file)); 

    // SI
    //patch.WriteU32((void *)0x007A8B7C, GetPrivateProfileInt(L"Module_Prototype", L"Weapon", 0, ini_file));
    //patch.WriteU32((void *)0x007A8B80, GetPrivateProfileInt(L"Transport_SI", L"Weapon", 0, ini_file)); 
    //patch.WriteU32((void *)0x007A8B84, GetPrivateProfileInt(L"Supplier", L"Weapon", 0, ini_file));
    patch.WriteU32((void *)0x007A8B88, GetPrivateProfileInt(L"Paralizator", L"Weapon", 173, ini_file));
    //patch.WriteU32((void *)0x007A8B8C, GetPrivateProfileInt(L"Energizer", L"Weapon", 0, ini_file));
    patch.WriteU32((void *)0x007A8B90, GetPrivateProfileInt(L"Skat", L"Weapon", 182, ini_file));
    patch.WriteU32((void *)0x007A8B94, GetPrivateProfileInt(L"Dreadnaught", L"Weapon", 181, ini_file));
    patch.WriteU32((void *)0x007A8B98, GetPrivateProfileInt(L"Escort", L"Weapon", 183, ini_file)); 
    patch.WriteU32((void *)0x007A8B9C, GetPrivateProfileInt(L"Bio_Assaulter", L"Weapon", 184, ini_file));
    patch.WriteU32((void *)0x007A8BA0, GetPrivateProfileInt(L"Usurper", L"Weapon", 182, ini_file));
    patch.WriteU32((void *)0x007A8BA4, GetPrivateProfileInt(L"Psi_Zond", L"Weapon", 182, ini_file));
    //patch.WriteU32((void *)0x007A8BA8, GetPrivateProfileInt(L"Explorer", L"Weapon", 0, ini_file));
    

    // RELOAD
    // WS
    patch.WriteU32((void *)0x007A8C5C, GetPrivateProfileInt(L"Sentinel", L"Reload", 30, ini_file));
    patch.WriteU32((void *)0x007A8C60, GetPrivateProfileInt(L"Hunter", L"Reload", 50, ini_file));
    patch.WriteU32((void *)0x007A8C64, GetPrivateProfileInt(L"Cruiser", L"Reload", 90, ini_file));
    patch.WriteU32((void *)0x007A8C68, GetPrivateProfileInt(L"Bomber", L"Reload", 80, ini_file));
    patch.WriteU32((void *)0x007A8C6C, GetPrivateProfileInt(L"Minelayer", L"Reload", 80, ini_file)); 
    patch.WriteU32((void *)0x007A8C70, GetPrivateProfileInt(L"Marauder", L"Reload", 70, ini_file));
    //patch.WriteU32((void *)0x007A8C74, GetPrivateProfileInt(L"Repair_Platform_WS", L"Reload", 0, ini_file));
    //patch.WriteU32((void *)0x007A8C78, GetPrivateProfileInt(L"Transport_Humans", L"Reload", 0, ini_file)); 
    //patch.WriteU32((void *)0x007A8C7C, GetPrivateProfileInt(L"Cyberworm", L"Reload", 0, ini_file));
    patch.WriteU32((void *)0x007A8C80, GetPrivateProfileInt(L"Terminator", L"Reload", 100, ini_file));
    patch.WriteU32((void *)0x007A8C84, GetPrivateProfileInt(L"Liberator", L"Reload", 80, ini_file));
    //patch.WriteU32((void *)0x007A8C88, GetPrivateProfileInt(L"Builder_Humans", L"Reload", 0, ini_file)); 

    // BO
    patch.WriteU32((void *)0x007A8C8C, GetPrivateProfileInt(L"Fighter", L"Reload", 40, ini_file));
    patch.WriteU32((void *)0x007A8C90, GetPrivateProfileInt(L"Destroyer", L"Reload", 50, ini_file));
    patch.WriteU32((void *)0x007A8C94, GetPrivateProfileInt(L"Heavy_Cruiser", L"Reload", 50, ini_file)); 
    patch.WriteU32((void *)0x007A8C98, GetPrivateProfileInt(L"Invader", L"Reload", 80, ini_file));
    patch.WriteU32((void *)0x007A8C9C, GetPrivateProfileInt(L"Defender", L"Reload", 70, ini_file));
    patch.WriteU32((void *)0x007A8CA0, GetPrivateProfileInt(L"Raider", L"Reload", 70, ini_file));
    //patch.WriteU32((void *)0x007A8CA4, GetPrivateProfileInt(L"Repair_Platform_BO", L"Reload", 0, ini_file));
    //patch.WriteU32((void *)0x007A8CA8, GetPrivateProfileInt(L"Transport_Humans", L"Reload", 0, ini_file));
    //patch.WriteU32((void *)0x007A8CAC, GetPrivateProfileInt(L"Cyberdolphin", L"Reload", 0, ini_file));
    patch.WriteU32((void *)0x007A8CB0, GetPrivateProfileInt(L"Phantom", L"Reload", 50, ini_file));
    patch.WriteU32((void *)0x007A8CB4, GetPrivateProfileInt(L"Avenger", L"Reload", 50, ini_file));
    //patch.WriteU32((void *)0x007A8CB8, GetPrivateProfileInt(L"Builder_Humans", L"Reload", 0, ini_file));
    //patch.WriteU32((void *)0x007A8CEC, GetPrivateProfileInt(L"Stealth_Scout", L"Reload", 0, ini_file)); 

    // SI
    //patch.WriteU32((void *)0x007A8CBC, GetPrivateProfileInt(L"Module_Prototype", L"Reload", 0, ini_file));
    //patch.WriteU32((void *)0x007A8CC0, GetPrivateProfileInt(L"Transport_SI", L"Reload", 0, ini_file)); 
    //patch.WriteU32((void *)0x007A8CC4, GetPrivateProfileInt(L"Supplier", L"Reload", 0, ini_file));
    patch.WriteU32((void *)0x007A8CC8, GetPrivateProfileInt(L"Paralizator", L"Reload", 100, ini_file));
    //patch.WriteU32((void *)0x007A8CCC, GetPrivateProfileInt(L"Energizer", L"Reload", 0, ini_file));
    patch.WriteU32((void *)0x007A8CD0, GetPrivateProfileInt(L"Skat", L"Reload", 40, ini_file));
    patch.WriteU32((void *)0x007A8CD4, GetPrivateProfileInt(L"Dreadnaught", L"Reload", 150, ini_file));
    patch.WriteU32((void *)0x007A8CD8, GetPrivateProfileInt(L"Escort", L"Reload", 60, ini_file)); 
    patch.WriteU32((void *)0x007A8CDC, GetPrivateProfileInt(L"Bio_Assaulter", L"Reload", 60, ini_file));
    patch.WriteU32((void *)0x007A8CE0, GetPrivateProfileInt(L"Usurper", L"Reload", 50, ini_file));
    patch.WriteU32((void *)0x007A8CE4, GetPrivateProfileInt(L"Psi_Zond", L"Reload", 40, ini_file));
    //patch.WriteU32((void *)0x007A8CE8, GetPrivateProfileInt(L"Explorer", L"Reload", 0, ini_file));
    

    // AMMO
    // WS
    patch.WriteU32((void *)0x007A8BBC, GetPrivateProfileInt(L"Sentinel", L"Ammo", 100, ini_file));
    patch.WriteU32((void *)0x007A8BC0, GetPrivateProfileInt(L"Hunter", L"Ammo", 20, ini_file));
    patch.WriteU32((void *)0x007A8BC4, GetPrivateProfileInt(L"Cruiser", L"Ammo", 30, ini_file));
    patch.WriteU32((void *)0x007A8BC8, GetPrivateProfileInt(L"Bomber", L"Ammo", 20, ini_file));
    patch.WriteU32((void *)0x007A8BCC, GetPrivateProfileInt(L"Minelayer", L"Ammo", 20, ini_file)); 
    patch.WriteU32((void *)0x007A8BD0, GetPrivateProfileInt(L"Marauder", L"Ammo", 20, ini_file));
    //patch.WriteU32((void *)0x007A8C74, GetPrivateProfileInt(L"Repair_Platform_WS", L"Reload", 0, ini_file));
    //patch.WriteU32((void *)0x007A8C78, GetPrivateProfileInt(L"Transport_Humans", L"Reload", 0, ini_file)); 
    //patch.WriteU32((void *)0x007A8C7C, GetPrivateProfileInt(L"Cyberworm", L"Reload", 0, ini_file));
    patch.WriteU32((void *)0x007A8BE0, GetPrivateProfileInt(L"Terminator", L"Ammo", 5, ini_file));
    patch.WriteU32((void *)0x007A8BE4, GetPrivateProfileInt(L"Liberator", L"Ammo", 20, ini_file));
    //patch.WriteU32((void *)0x007A8C88, GetPrivateProfileInt(L"Builder_Humans", L"Reload", 0, ini_file)); 

    // BO
    patch.WriteU32((void *)0x007A8BEC, GetPrivateProfileInt(L"Fighter", L"Ammo", 20, ini_file));
    patch.WriteU32((void *)0x007A8BF0, GetPrivateProfileInt(L"Destroyer", L"Ammo", 40, ini_file));
    patch.WriteU32((void *)0x007A8BF4, GetPrivateProfileInt(L"Heavy_Cruiser", L"Ammo", 30, ini_file)); 
    patch.WriteU32((void *)0x007A8BF8, GetPrivateProfileInt(L"Invader", L"Ammo", 30, ini_file));
    patch.WriteU32((void *)0x007A8BFC, GetPrivateProfileInt(L"Defender", L"Ammo", 20, ini_file));
    patch.WriteU32((void *)0x007A8C00, GetPrivateProfileInt(L"Raider", L"Ammo", 20, ini_file));
    //patch.WriteU32((void *)0x007A8CA4, GetPrivateProfileInt(L"Repair_Platform_BO", L"Reload", 0, ini_file));
    //patch.WriteU32((void *)0x007A8CA8, GetPrivateProfileInt(L"Transport_Humans", L"Reload", 0, ini_file));
    //patch.WriteU32((void *)0x007A8CAC, GetPrivateProfileInt(L"Cyberdolphin", L"Reload", 0, ini_file));
    patch.WriteU32((void *)0x007A8C10, GetPrivateProfileInt(L"Phantom", L"Ammo", 20, ini_file));
    patch.WriteU32((void *)0x007A8C14, GetPrivateProfileInt(L"Avenger", L"Ammo", 30, ini_file));
    //patch.WriteU32((void *)0x007A8CB8, GetPrivateProfileInt(L"Builder_Humans", L"Reload", 0, ini_file));
    //patch.WriteU32((void *)0x007A8CEC, GetPrivateProfileInt(L"Stealth_Scout", L"Reload", 0, ini_file)); 

    // SI
    //patch.WriteU32((void *)0x007A8CBC, GetPrivateProfileInt(L"Module_Prototype", L"Reload", 0, ini_file));
    //patch.WriteU32((void *)0x007A8CC0, GetPrivateProfileInt(L"Transport_SI", L"Reload", 0, ini_file)); 
    //patch.WriteU32((void *)0x007A8CC4, GetPrivateProfileInt(L"Supplier", L"Reload", 0, ini_file));
    patch.WriteU32((void *)0x007A8C28, GetPrivateProfileInt(L"Paralizator", L"Ammo", 20, ini_file));
    //patch.WriteU32((void *)0x007A8CCC, GetPrivateProfileInt(L"Energizer", L"Reload", 0, ini_file));
    patch.WriteU32((void *)0x007A8C30, GetPrivateProfileInt(L"Skat", L"Ammo", 30, ini_file));
    patch.WriteU32((void *)0x007A8C34, GetPrivateProfileInt(L"Dreadnaught", L"Ammo", 20, ini_file));
    patch.WriteU32((void *)0x007A8C38, GetPrivateProfileInt(L"Escort", L"Ammo", 20, ini_file)); 
    patch.WriteU32((void *)0x007A8C3C, GetPrivateProfileInt(L"Bio_Assaulter", L"Ammo", 25, ini_file));
    patch.WriteU32((void *)0x007A8C40, GetPrivateProfileInt(L"Usurper", L"Ammo", 20, ini_file));
    patch.WriteU32((void *)0x007A8C44, GetPrivateProfileInt(L"Psi_Zond", L"Ammo", 30, ini_file));
    //patch.WriteU32((void *)0x007A8CE8, GetPrivateProfileInt(L"Explorer", L"Reload", 0, ini_file));



    // RESUPPLY
    // WS
    patch.WriteByte((void *)0x0045B1E0, GetPrivateProfileInt(L"Sentinel", L"Resupply", 0, ini_file));
    patch.WriteByte((void *)0x0045B1E1, GetPrivateProfileInt(L"Hunter", L"Resupply", 2, ini_file));
    patch.WriteByte((void *)0x0045B1E2, GetPrivateProfileInt(L"Cruiser", L"Resupply", 2, ini_file));
    patch.WriteByte((void *)0x0045B1E3, GetPrivateProfileInt(L"Bomber", L"Resupply", 2, ini_file));
    patch.WriteByte((void *)0x0045B1E4, GetPrivateProfileInt(L"Minelayer", L"Resupply", 2, ini_file)); 
    patch.WriteByte((void *)0x0045B1E5, GetPrivateProfileInt(L"Marauder", L"Resupply", 2, ini_file));
    //patch.WriteByte((void *)0x007A8C74, GetPrivateProfileInt(L"Repair_Platform_WS", L"Reload", 0, ini_file));
    //patch.WriteByte((void *)0x007A8C78, GetPrivateProfileInt(L"Transport_Humans", L"Reload", 0, ini_file)); 
    //patch.WriteByte((void *)0x007A8C7C, GetPrivateProfileInt(L"Cyberworm", L"Reload", 0, ini_file));
    patch.WriteByte((void *)0x0045B1E9, GetPrivateProfileInt(L"Terminator", L"Resupply", 0, ini_file));
    patch.WriteByte((void *)0x0045B1EA, GetPrivateProfileInt(L"Liberator", L"Resupply", 2, ini_file));
    //patch.WriteByte((void *)0x007A8C88, GetPrivateProfileInt(L"Builder_Humans", L"Reload", 0, ini_file)); 

    // BO
    patch.WriteByte((void *)0x0045B1EC, GetPrivateProfileInt(L"Fighter", L"Resupply", 2, ini_file));
    patch.WriteByte((void *)0x0045B1ED, GetPrivateProfileInt(L"Destroyer", L"Resupply", 2, ini_file));
    patch.WriteByte((void *)0x0045B1EE, GetPrivateProfileInt(L"Heavy_Cruiser", L"Resupply", 1, ini_file)); 
    patch.WriteByte((void *)0x0045B1EF, GetPrivateProfileInt(L"Invader", L"Resupply", 2, ini_file));
    patch.WriteByte((void *)0x0045B1F0, GetPrivateProfileInt(L"Defender", L"Resupply", 2, ini_file));
    patch.WriteByte((void *)0x0045B1F1, GetPrivateProfileInt(L"Raider", L"Resupply", 1, ini_file));
    //patch.WriteByte((void *)0x007A8CA4, GetPrivateProfileInt(L"Repair_Platform_BO", L"Reload", 0, ini_file));
    //patch.WriteByte((void *)0x007A8CA8, GetPrivateProfileInt(L"Transport_Humans", L"Reload", 0, ini_file));
    //patch.WriteByte((void *)0x007A8CAC, GetPrivateProfileInt(L"Cyberdolphin", L"Reload", 0, ini_file));
    patch.WriteByte((void *)0x0045B1F5, GetPrivateProfileInt(L"Phantom", L"Resupply", 1, ini_file));
    patch.WriteByte((void *)0x0045B1F6, GetPrivateProfileInt(L"Avenger", L"Resupply", 1, ini_file));
    //patch.WriteByte((void *)0x007A8CB8, GetPrivateProfileInt(L"Builder_Humans", L"Reload", 0, ini_file));
    //patch.WriteByte((void *)0x007A8CEC, GetPrivateProfileInt(L"Stealth_Scout", L"Reload", 0, ini_file)); 

    // SI
    //patch.WriteByte((void *)0x007A8CBC, GetPrivateProfileInt(L"Module_Prototype", L"Reload", 0, ini_file));
    //patch.WriteByte((void *)0x007A8CC0, GetPrivateProfileInt(L"Transport_SI", L"Reload", 0, ini_file)); 
    //patch.WriteByte((void *)0x007A8CC4, GetPrivateProfileInt(L"Supplier", L"Reload", 0, ini_file));
    patch.WriteByte((void *)0x0045B1FB, GetPrivateProfileInt(L"Paralizator", L"Resupply", 2, ini_file));
    //patch.WriteByte((void *)0x007A8CCC, GetPrivateProfileInt(L"Energizer", L"Reload", 0, ini_file));
    patch.WriteByte((void *)0x0045B1FD, GetPrivateProfileInt(L"Skat", L"Resupply", 0, ini_file));
    patch.WriteByte((void *)0x0045B1FE, GetPrivateProfileInt(L"Dreadnaught", L"Resupply", 2, ini_file));
    patch.WriteByte((void *)0x0045B1FF, GetPrivateProfileInt(L"Escort", L"Resupply", 0, ini_file)); 
    patch.WriteByte((void *)0x0045B200, GetPrivateProfileInt(L"Bio_Assaulter", L"Resupply", 2, ini_file));
    patch.WriteByte((void *)0x0045B201, GetPrivateProfileInt(L"Usurper", L"Resupply", 0, ini_file));
    patch.WriteByte((void *)0x0045B202, GetPrivateProfileInt(L"Psi_Zond", L"Resupply", 0, ini_file));
    //patch.WriteByte((void *)0x007A8CE8, GetPrivateProfileInt(L"Explorer", L"Reload", 0, ini_file));


    // DAMAGE     
    patch.WriteU32((void *)0x007E6468, GetPrivateProfileInt(L"Light_Torpedo", L"Damage_1", 50, ini_file));
    patch.WriteU32((void *)0x007E646C, GetPrivateProfileInt(L"Light_Torpedo", L"Damage_2", 70, ini_file));
    patch.WriteU32((void *)0x007E6470, GetPrivateProfileInt(L"Light_Torpedo", L"Damage_3", 90, ini_file));
    patch.WriteU32((void *)0x007E6474, GetPrivateProfileInt(L"Light_Torpedo", L"Damage_4", 110, ini_file));
    patch.WriteU32((void *)0x007E6478, GetPrivateProfileInt(L"Light_Torpedo", L"Damage_5", 120, ini_file));
    
    patch.WriteU32((void *)0x007E647C, GetPrivateProfileInt(L"Medium_Torpedo", L"Damage_1", 80, ini_file));
    patch.WriteU32((void *)0x007E6480, GetPrivateProfileInt(L"Medium_Torpedo", L"Damage_2", 100, ini_file));
    patch.WriteU32((void *)0x007E6484, GetPrivateProfileInt(L"Medium_Torpedo", L"Damage_3", 130, ini_file));
    patch.WriteU32((void *)0x007E6488, GetPrivateProfileInt(L"Medium_Torpedo", L"Damage_4", 150, ini_file));
    patch.WriteU32((void *)0x007E648C, GetPrivateProfileInt(L"Medium_Torpedo", L"Damage_5", 180, ini_file)); 

    patch.WriteU32((void *)0x007E6490, GetPrivateProfileInt(L"Heavy_Torpedo", L"Damage_1", 90, ini_file));
    patch.WriteU32((void *)0x007E6494, GetPrivateProfileInt(L"Heavy_Torpedo", L"Damage_2", 120, ini_file));
    patch.WriteU32((void *)0x007E6498, GetPrivateProfileInt(L"Heavy_Torpedo", L"Damage_3", 150, ini_file));
    patch.WriteU32((void *)0x007E649C, GetPrivateProfileInt(L"Heavy_Torpedo", L"Damage_4", 170, ini_file));
    patch.WriteU32((void *)0x007E64A0, GetPrivateProfileInt(L"Heavy_Torpedo", L"Damage_5", 200, ini_file));
    
    patch.WriteU32((void *)0x007E651C, GetPrivateProfileInt(L"LHF", L"Damage_1", 30, ini_file));
    patch.WriteU32((void *)0x007E6520, GetPrivateProfileInt(L"LHF", L"Damage_2", 80, ini_file));
    
    patch.WriteU32((void *)0x007E6530, GetPrivateProfileInt(L"HHF", L"Damage_1", 70, ini_file));
    patch.WriteU32((void *)0x007E6534, GetPrivateProfileInt(L"HHF", L"Damage_2", 120, ini_file));
    
    patch.WriteU32((void *)0x007E65E4, GetPrivateProfileInt(L"DCBomb", L"Damage", 500, ini_file)); // DC Bomb damage
    
    patch.WriteU32((void *)0x007E65A8, GetPrivateProfileInt(L"Depth_Mine", L"Damage", 1000, ini_file)); 
    patch.WriteU32((void *)0x007E64CC, GetPrivateProfileInt(L"Laser_Snare", L"Damage", 800, ini_file)); 
    patch.WriteU32((void *)0x007E6774, GetPrivateProfileInt(L"Acoustic_Mine", L"Damage", 950, ini_file)); 

    patch.WriteU32((void *)0x007E6580, GetPrivateProfileInt(L"Plasma", L"Damage", 600, ini_file)); // Plasma damage  

    // BO
    patch.WriteU32((void *)0x007E6620, GetPrivateProfileInt(L"Splinter_Torpedo", L"Damage_1", 60, ini_file)); // Destroyer T1 damage (vanilla 60)
    patch.WriteU32((void *)0x007E6624, GetPrivateProfileInt(L"Splinter_Torpedo", L"Damage_2", 150, ini_file)); // Destroyer T2 damage (vanilla 150)
    
    patch.WriteU32((void *)0x007E64E0, GetPrivateProfileInt(L"Light_Laser", L"Damage", 60, ini_file));
    patch.WriteU32((void *)0x007E64F4, GetPrivateProfileInt(L"Ruby_Laser", L"Damage", 120, ini_file));
    patch.WriteU32((void *)0x007E6508, GetPrivateProfileInt(L"Heavy_Laser", L"Damage", 200, ini_file));

    patch.WriteU32((void *)0x007E64B8, GetPrivateProfileInt(L"EM_Torpedo", L"Damage_1", 400, ini_file));
    patch.WriteU32((void *)0x007E64BC, GetPrivateProfileInt(L"EM_Torpedo", L"Damage_2", 500, ini_file));

    patch.WriteU32((void *)0x00464814, GetPrivateProfileInt(L"Cyberdolphin", L"Damage", 600, ini_file)); 
    
    patch.WriteU32((void *)0x007E64A4, GetPrivateProfileInt(L"Cassete_Shell", L"Damage", 120, ini_file));

    patch.WriteU32((void *)0x007E66C0, GetPrivateProfileInt(L"Cassete_Subshell", L"Damage_1", 30, ini_file));
    patch.WriteU32((void *)0x007E66C4, GetPrivateProfileInt(L"Cassete_Subshell", L"Damage_2", 45, ini_file));
    patch.WriteU32((void *)0x007E66C8, GetPrivateProfileInt(L"Cassete_Subshell", L"Damage_3", 60, ini_file));
    patch.WriteU32((void *)0x007E66CC, GetPrivateProfileInt(L"Cassete_Subshell", L"Damage_4", 75, ini_file));
    patch.WriteU32((void *)0x007E66D0, GetPrivateProfileInt(L"Cassete_Subshell", L"Damage_5", 90, ini_file));

    patch.WriteU32((void *)0x007E660C, GetPrivateProfileInt(L"Magnetic_Mine", L"Damage", 350, ini_file));
    
    // SI
    patch.WriteU32((void *)0x007E679C, GetPrivateProfileInt(L"Weap_Pulsar", L"Damage_1", 80, ini_file)); // Pulsar T1 damage
    patch.WriteU32((void *)0x007E67A0, GetPrivateProfileInt(L"Weap_Pulsar", L"Damage_2", 120, ini_file)); // Pulsar T2 damage
    patch.WriteU32((void *)0x007E67A4, GetPrivateProfileInt(L"Weap_Pulsar", L"Damage_3", 150, ini_file)); // Pulsar T3 damage
    
    patch.WriteU32((void *)0x007E66FC, GetPrivateProfileInt(L"Ion_Cassete", L"Damage_1", 120, ini_file)); // Ion cassete t1 
    patch.WriteU32((void *)0x007E6700, GetPrivateProfileInt(L"Ion_Cassete", L"Damage_2", 140, ini_file)); // Ion cassete t2
    patch.WriteU32((void *)0x007E6704, GetPrivateProfileInt(L"Ion_Cassete", L"Damage_3", 160, ini_file)); // Ion cassete t3

    patch.WriteU32((void *)0x007E6724, GetPrivateProfileInt(L"Ion_Cassete_Subshell", L"Damage_1", 20, ini_file)); // Ion cassete subshell t1
    patch.WriteU32((void *)0x007E6728, GetPrivateProfileInt(L"Ion_Cassete_Subshell", L"Damage_2", 30, ini_file)); // Ion cassete subshell t2
    patch.WriteU32((void *)0x007E672C, GetPrivateProfileInt(L"Ion_Cassete_Subshell", L"Damage_3", 40, ini_file)); // Ion cassete subshell t3

	patch.WriteU32((void *)0x007E66E8, GetPrivateProfileInt(L"Energy_Shell", L"Damage_1", 40, ini_file)); // Energy shell dmg t1 
	patch.WriteU32((void *)0x007E66EC, GetPrivateProfileInt(L"Energy_Shell", L"Damage_2", 60, ini_file)); // Energy shell dmg t2 
    patch.WriteU32((void *)0x007E66F0, GetPrivateProfileInt(L"Energy_Shell", L"Damage_3", 100, ini_file)); // Energy shell dmg t3 

    patch.WriteU32((void *)0x007E67C4, GetPrivateProfileInt(L"Weap_Soliton", L"Damage", 30, ini_file)); // Soliton dmg 
    
    patch.WriteU32((void *)0x007E66D4, GetPrivateProfileInt(L"BHE_Shell", L"Damage", 300, ini_file));

    patch.WriteU32((void *)0x007E6648, GetPrivateProfileInt(L"Gas_Shell", L"Damage", 150, ini_file));
    
    patch.WriteU32((void *)0x007E67B0, GetPrivateProfileInt(L"Weap_USG", L"Damage", 25, ini_file));
    
    patch.WriteU32((void *)0x007E66AC, GetPrivateProfileInt(L"Jump_mine", L"Damage", 200, ini_file));
    patch.WriteU32((void *)0x007E6760, GetPrivateProfileInt(L"Bio_mine", L"Damage", 150, ini_file));
    patch.WriteU32((void *)0x007E6594, GetPrivateProfileInt(L"Satellite_Gas_Laser", L"Damage", 1500, ini_file));
    
    patch.WriteU32((void *)0x007E6710, GetPrivateProfileInt(L"Bioacid_Shell", L"Damage_1", 400, ini_file));
    patch.WriteU32((void *)0x007E6714, GetPrivateProfileInt(L"Bioacid_Shell", L"Damage_2", 600, ini_file));
     
    patch.WriteU32((void *)0x007E6544, GetPrivateProfileInt(L"Paralyze_Ray", L"Damage", 20, ini_file));  
    patch.WriteU32((void *)0x007E6634, GetPrivateProfileInt(L"Neuro_Paralysis_Shell", L"Damage_1", 10, ini_file)); 
    patch.WriteU32((void *)0x007E6638, GetPrivateProfileInt(L"Neuro_Paralysis_Shell", L"Damage_2", 20, ini_file)); 
    patch.WriteU32((void *)0x007E663C, GetPrivateProfileInt(L"Neuro_Paralysis_Shell", L"Damage_3", 30, ini_file)); 
    patch.WriteU32((void *)0x007E6640, GetPrivateProfileInt(L"Neuro_Paralysis_Shell", L"Damage_4", 30, ini_file)); 
    
    patch.WriteU32((void *)0x007E6670, GetPrivateProfileInt(L"Weap_Parcher", L"Damage_1", 400, ini_file)); 
    patch.WriteU32((void *)0x007E6674, GetPrivateProfileInt(L"Weap_Parcher", L"Damage_2", 500, ini_file)); 
    patch.WriteU32((void *)0x007E6678, GetPrivateProfileInt(L"Weap_Parcher", L"Damage_3", 600, ini_file)); 

    // Other
    patch.WriteByte((void *)0x00476AE4, GetPrivateProfileInt(L"Bomber", L"Bombs_drop", 15, ini_file));
    patch.WriteByte((void *)0x00476AD3, GetPrivateProfileInt(L"Bomber", L"Bombs_drop", 15, ini_file));
    int bd = GetPrivateProfileInt(L"Bomber", L"Bombs_drop", 15, ini_file);
    patch.WriteByte((void *)0x00476B1B, -bd);

    patch.WriteByte((void *)0x00463683, GetPrivateProfileInt(L"Cyberworm", L"Gold_steal", 200, ini_file));
    patch.WriteByte((void *)0x0046368A, GetPrivateProfileInt(L"Cyberworm", L"Gold_steal", 200, ini_file));
    patch.WriteByte((void *)0x00463703, GetPrivateProfileInt(L"Cyberworm", L"Metal_steal", 1500, ini_file));
    patch.WriteByte((void *)0x004636FC, GetPrivateProfileInt(L"Cyberworm", L"Metal_steal", 1500, ini_file));
    patch.WriteJumpSized(CyberWormCoriumSteal_Jmp, 5, (unsigned long)CyberWormCoriumSteal);
    patch.WriteByte((void *)0x004636C5, GetPrivateProfileInt(L"Cyberworm", L"Corium_steal", 100, ini_file));

    patch.WriteByte((void *)0x0045094E, GetPrivateProfileInt(L"Phantom", L"Discharge", 30, ini_file));

    patch.WriteByte((void *)0x007D2220, GetPrivateProfileInt(L"Paralyze_Ray", L"Time", 375, ini_file)); 
    patch.WriteByte((void *)0x007D2210, GetPrivateProfileInt(L"Neuro_Paralysis_Shell", L"Time_1", 125, ini_file));
    patch.WriteByte((void *)0x007D2210, GetPrivateProfileInt(L"Neuro_Paralysis_Shell", L"Time_2", 250, ini_file));

    //--------------------------------------------------------------------------------------------------------------------

    //Submarines armor
    bool half_armor = GetPrivateProfileInt(L"Armor", L"HalfStrength", TRUE, ini_file);
    if (half_armor)
    {
        patch.WriteByte((void *)0x00459E86, 0x11); // Half armor T2 jump
        patch.WriteByte((void *)0x00459E9C, 0xC9); // Half armor T2 value (90%)
        patch.WriteNops((void *)0x00459E9D, 2);    // Half armor T2 nops

        patch.WriteByte((void *)0x00459E89, 0x17); // Half armor T3 jump

        patch.WriteByte((void *)0x00459E91, 0x89);  // Half armor T4
        patch.WriteU16((void *)0x00459E92, 0xCA01); // Half armor T4
        patch.WriteU16((void *)0x00459E94, 0xCA01); // Half armor T4

        // Buildings armor
        patch.WriteByte((void *)0x004BB5A1, 0x12); // Half armor T2 jump
        patch.WriteByte((void *)0x004BB5B9, 0xC9); // Half armor T2 value (90%)
        patch.WriteNops((void *)0x004BB5BA, 2);    // Half armor T2 nops

        patch.WriteByte((void *)0x004BB5A4, 0x19); // Half armor T3 jump

        patch.WriteByte((void *)0x004BB5AD, 0x89);  // Half armor T4
        patch.WriteU16((void *)0x004BB5AE, 0xCA01); // Half armor T4
        patch.WriteU16((void *)0x004BB5B0, 0xCA01); // Half armor T4
    }

    //patch.WriteByte((void *)0x00642ABA, 3);   // Laser reflection % (25 -> 12.5)
    // Max blocked damage
    // Buildings
    int max_block_bld = GetPrivateProfileInt(L"Armor", L"MaxBlockedDamageBuildings", 200, ini_file);
    int max_block_sub = GetPrivateProfileInt(L"Armor", L"MaxBlockedDamageSubmarines", 200, ini_file);
    patch.WriteU32((void *)0x004BB5DF, max_block_bld); // max blocked damage check
    patch.WriteU32((void *)0x004BB5E6, max_block_bld); // max blocked damage replace

    // Subs
    patch.WriteU32((void *)0x00459F64, max_block_sub); // max blocked damage check
    patch.WriteU32((void *)0x00459F6B, -max_block_sub); // max blocked damage replace

    //ECONOMICS
    DWORD metal_capacity = GetPrivateProfileInt(L"Economics", L"MetalCapacityTransport", 20, ini_file);
    patch.WriteU32((void *)0x0043092D, metal_capacity); // Metal in 1/40 of Transport capacity load
    patch.WriteNops((void *)0x00469345, 1); // Metal in 1/40 of Transport capacity unload
    patch.WriteByte((void *)0x00469346, 0xB9); // Metal in 1/40 of Transport capacity unload
    patch.WriteU32((void *)0x00469347, metal_capacity); // Metal in 1/40 of Transport capacity unload

    DWORD energy_mine_cd = GetPrivateProfileInt(L"Economics", L"EnergyMineTimer", 6, ini_file);
    patch.WriteU32((void *)0x004E0156, energy_mine_cd); // energy mine tick timer
    
    // OTHER
    //patch.WriteU32((void *)0x0044F745, 7); // Submarines standard view range BO
    //patch.WriteU32((void *)0x0044F427, 7); // Submarines standard view range WS
    //patch.WriteJumpSized(ChangeSubsRangeStd_Jmp, 7, (unsigned long)ChangeSubsRangeStd);
    patch.WriteJumpSized(ChangeSubsRange_Jmp, 7, (unsigned long)ChangeSubsRange);
    
    // AI Compatible
    bool ai_compatible = GetPrivateProfileInt(L"Plugins", L"AICompatible", FALSE, ini_file);
    if (ai_compatible)
    {
        patch.WriteByte((void *)0x007BFBBB, 1); // Mining upgrade silicon si
        patch.WriteByte((void *)0x007BFAC8, 1); // WS Capture upg
        patch.WriteByte((void *)0x007BFB60, 1); // BO Capture upg
        patch.WriteByte((void *)0x007BFBF8, 1); // SI Capture upg

        patch.WriteByte((void *)0x007BFBD6, 1); // SI TRPEVADE unavailable
        patch.WriteByte((void *)0x0079903F, 3); // SI IONARMOR 1 lvl only
        patch.WriteByte((void *)0x007BFBB8, 1); // SI UPG NRG MINE unavailable
        patch.WriteByte((void *)0x007BFBE1, 1); // SI DPTRANGE unavailable
    }

    return true;
}

static bool Flagships(Patcher::SPatch &patch)
{
    auto ini_file = InitConfig();   
    // Flagships in wargroups and not in special groups
    patch.WriteU32((void *)0x0080148C, 899);        // Flagships add to wargroups 899
    patch.WriteU32((void *)0x004E87F7, 2425393296); // nops to not overwrite
    patch.WriteByte((void *)0x004E87FB, 144);
    patch.WriteByte((void *)0x004E87D7, 137);
    patch.WriteByte((void *)0x004E87D8, 242);

    patch.WriteJumpSized(NoPlatformLoadFlagships_Jmp, 5, (unsigned long)NoPlatformLoadFlagships);
    patch.WriteJumpSized(FlagshipsSelection_Jmp, 5, (unsigned long)FlagshipsSelection);


    //WS
    patch.WriteByte((void *)0x007C0E44, 7);   // Research ID
    patch.WriteByte((void *)0x004E8341, 128); // Belongs race
    patch.WriteU32((void *)0x007E0534, GetPrivateProfileInt(L"Flagship_WS", L"BuildTime", 1750, ini_file)); // Time
    patch.WriteU32((void *)0x007E0834, GetPrivateProfileInt(L"Flagship_WS", L"Metal", 1000, ini_file)); // Metal
    patch.WriteU32((void *)0x007E05F4, GetPrivateProfileInt(L"Flagship_WS", L"Corium", 300, ini_file)); // Corium
    patch.WriteU32((void *)0x007A8BB0, GetPrivateProfileInt(L"Flagship_WS", L"Weapon", 152, ini_file));  // Weapon type
    patch.WriteByte((void *)0x0045B205, GetPrivateProfileInt(L"Flagship_WS", L"Resupply", 2, ini_file));
    patch.WriteU32((void *)0x007A8CF0, GetPrivateProfileInt(L"Flagship_WS", L"Reload", 90, ini_file));   // Reload
    patch.WriteU32((void *)0x007A8C50, GetPrivateProfileInt(L"Flagship_WS", L"Ammo", 30, ini_file));   // Ammo
    patch.WriteU16((void *)0x0048C31c, 40);   // Side shift
    patch.WriteI16((void *)0x0048C333, -40);  // Side shift 2
    patch.WriteU32((void *)0x007DFC44, GetPrivateProfileInt(L"Flagship_WS", L"HP", 1000, ini_file)); // HP


    // BO
    patch.WriteByte((void *)0x007C0E47, 35); // Research ID
    // Belongs race
    patch.WriteByte((void *)0x004E8364, 12);  // al or
    patch.WriteByte((void *)0x004E8365, 36);  // 36 (0x24 + 0x140) = 356
    patch.WriteByte((void *)0x004E8366, 144); // nop

    patch.WriteU32((void *)0x007E0538, GetPrivateProfileInt(L"Flagship_BO", L"BuildTime", 1750, ini_file)); // Time
    patch.WriteU32((void *)0x007E0838, GetPrivateProfileInt(L"Flagship_BO", L"Metal", 1000, ini_file)); // Metal
    patch.WriteU32((void *)0x007E05F8, GetPrivateProfileInt(L"Flagship_BO", L"Corium", 300, ini_file)); // Corium
    patch.WriteU32((void *)0x007A8BB4, GetPrivateProfileInt(L"Flagship_BO", L"Weapon", 156, ini_file));  // Weapon type
    patch.WriteByte((void *)0x0045B206, GetPrivateProfileInt(L"Flagship_BO", L"Resupply", 1, ini_file));
    patch.WriteU32((void *)0x007A8CF4, GetPrivateProfileInt(L"Flagship_BO", L"Reload", 80, ini_file));   // Reload
    patch.WriteU32((void *)0x007A8C54, GetPrivateProfileInt(L"Flagship_BO", L"Ammo", 1750, ini_file));  // Ammo
    patch.WriteU32((void *)0x007DFC48, GetPrivateProfileInt(L"Flagship_BO", L"HP", 3000, ini_file)); // HP

    //patch.WriteJumpSized(BOFlagshipRange6_Jmp, 5, (unsigned long)BOFlagshipRange6);

    //SI
    patch.WriteByte((void *)0x007C0E4A, 0); // Research ID
    patch.WriteU16((void *)0x004E83A2, 204);  // Belongs race
    patch.WriteU32((void *)0x007E053C, GetPrivateProfileInt(L"Flagship_SI", L"BuildTime", 1750, ini_file)); // Time
    patch.WriteU32((void *)0x007E0A7C, GetPrivateProfileInt(L"Flagship_SI", L"Silicon", 1000, ini_file)); // Silicon
    patch.WriteU32((void *)0x007E05FC, GetPrivateProfileInt(L"Flagship_SI", L"Corium", 300, ini_file));  // Corium
    patch.WriteU32((void *)0x007A8CF8, GetPrivateProfileInt(L"Flagship_SI", L"Reload", 40, ini_file));    // Reload
    patch.WriteU32((void *)0x007DFC4C, GetPrivateProfileInt(L"Flagship_SI", L"HP", 3000, ini_file)); // HP
    patch.WriteU32((void *)0x007E077C, 50);   // regen speed
    patch.WriteU32((void *)0x007E0D10, 22500); // regen amount T1 (/1500)
    patch.WriteU32((void *)0x007E0D14, 33000); // regen amount T1 (/1500)
    patch.WriteU32((void *)0x007E0D18, 45000); // regen amount T1 (/1500)
    patch.WriteU32((void *)0x007E0D1C, 60000); // regen amount T1 (/1500)
    patch.WriteU32((void *)0x007A8BB8, GetPrivateProfileInt(L"Flagship_SI", L"Weapon", 182, ini_file)); // weapon
    patch.WriteByte((void *)0x0045B207, GetPrivateProfileInt(L"Flagship_SI", L"Resupply", 0, ini_file));
    patch.WriteU32((void *)0x007A8C58, GetPrivateProfileInt(L"Flagship_SI", L"Ammo", 20, ini_file)); // weapon
    //patch.WriteJumpSized(SIFlagshipRange7_Jmp, 5, (unsigned long)SIFlagshipRange7);
    patch.WriteNops((void *)0x004622FF, 9); // No overwrite 5 range
    patch.WriteNops((void *)0x004653D8, 9); // No overwrite 5 range again
    patch.WriteNops((void *)0x00459324, 9); // No overwrite 5 range and again
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
    patch.WriteJumpSized(AimPredictionSubmarinesDef0_Jmp, 15, (unsigned long)AimPredictionSubmarinesDef0);
    patch.WriteJumpSized(AimPredictionSubmarinesDef1_Jmp, 15, (unsigned long)AimPredictionSubmarinesDef1);
    patch.WriteJumpSized(AimPredictionSubmarinesDef2_Jmp, 15, (unsigned long)AimPredictionSubmarinesDef2);
    patch.WriteJumpSized(AimPredictionSubmarinesDef3_Jmp, 15, (unsigned long)AimPredictionSubmarinesDef3);
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

static bool OneDepotFor2Mines2(Patcher::SPatch &patch)
{
    patch.WriteByte((void *)0x004693A6, 2); // Transport waiting distance set after depot
    patch.WriteByte((void *)0x00467488, 2); // Transport waiting distance set after mine
    patch.WriteByte((void *)0x004696F9, 2); // Transport waiting distance 3
    patch.WriteByte((void *)0x004699A1, 2); // Transport waiting distance set after mine order
    patch.WriteJumpSized(TransportDepotDecision_Jmp, 5, (unsigned long)TransportDepotDecision);
    patch.WriteJumpSized(TransportDepotDecision2_Jmp, 5, (unsigned long)TransportDepotDecision2);

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
    //patch.WriteJumpSized(CapturedTechBuildings_Jmp, 6, (unsigned long)CapturedTechBuildings);
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
    patch.WriteU32((void *)0x0079A5E4, 103);
    patch.WriteU32((void *)0x0079A5E8, 121);
    patch.WriteU32((void *)0x0079A5EC, 0);

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
    patch.WriteU32((void *)0x0079A6A0, 83);
    patch.WriteU32((void *)0x0079A6A4, 80);
    patch.WriteU32((void *)0x0079A6A8, 144);

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

static bool AI2021Compatible(Patcher::SPatch &patch)
{
    patch.WriteByte((void *)0x007BFBBB, 1); // Mining upgrade silicon si
    patch.WriteByte((void *)0x007BFAC7, 1); // WS Capture upg
    patch.WriteByte((void *)0x007BFB60, 1); // BO Capture upg
    patch.WriteByte((void *)0x007BFBF8, 1); // SI Capture upg
    
    patch.WriteByte((void *)0x007BFBD6, 1); // SI TRPEVADE unavailable
    patch.WriteByte((void *)0x0079903F, 3); // SI IONARMOR 1 lvl only
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

typedef bool (*PatchFunction)(Patcher::SPatch &patch);
static const PatchFunction Patches[] = {
    //Yaml,
    //Put your patch functions here:     
    FixesQoL, 
    OneDepotFor2Mines2,
    AimPrediction,
    BalancingTacticsTree,
    ResearchBuildingsLimit,
    Flagships,

    LobbyAnnouncements,

    SiResearchModulesReduce2,

    ShiftQueue
    
    // EnableFog
    
    // EconomicsAndOther,
    
    // BalancingNormalTree,
   
    // AI2021Compatible
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
