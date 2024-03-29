#include "patches.h"
#include "config.h"
#include "Shared/Common.h"
#include "Shared/Patcher.h"
#include <windows.h>
#include "winhttp.h"
//#include <string>

using namespace Common;
using namespace Patcher;

#pragma comment(lib, "winhttp.lib")
// Implement your patches here

static bool FixesQoL(Patcher::SPatch &patch) {
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

    patch.WriteJumpSized(BoxCursorLoadCheck1_Jmp, 5, (unsigned long)BoxCursorLoadCheck1);
    patch.WriteJumpSized(BoxCursorLoadCheck2_Jmp, 10, (unsigned long)BoxCursorLoadCheck2);

    patch.WriteJumpSized(AlwaysShowHP_Jmp, 9, (unsigned long)AlwaysShowHP);
    patch.WriteJumpSized(DecreaseShowHPState_Jmp, 8, (unsigned long)DecreaseShowHPState);

    patch.WriteNops((void *)0x00489C36, 6); // No extra 200 priority to building targets in range
    
    //Shift for order queue (desync issue)
    //Wait for movement complete
    //patch.WriteNops((void *)0x0040B570, 8); // 8 Null bytes 
    //patch.WriteJumpSized(SkipStopResetOrderMove_Move_Jmp, 5, (unsigned long)SkipStopResetOrderMove_Move);
    //patch.WriteJumpSized(SkipStopResetOrderIdle_Build_Jmp, 5, (unsigned long)SkipStopResetOrderIdle_Build);
    //patch.WriteJumpSized(SkipStopResetOrderBuild_Build_Jmp, 5, (unsigned long)SkipStopResetOrderBuild_Build);
    //patch.WriteJumpSized(EnableShiftAltInput_Jmp, 5, (unsigned long)EnableShiftAltInput);
    //patch.WriteJumpSized(DontEraseOldOrder_jmp, 6, (unsigned long)DontEraseOldOrder);
    //patch.WriteJumpSized(AppendOrderInsteadOfReplace_Jmp, 8, (unsigned long)AppendOrderInsteadOfReplace);
    //patch.WriteJumpSized(OrderEndProcedure_Jmp, 7, (unsigned long)OrderEndProcedure);
    //patch.WriteNops((void *)0x0045FC0D, 32); // Nop for prev script
    //patch.WriteNops((void *)0x0045EFEB, 19); // Nop for new build order with shift
    //patch.WriteJumpSized(NewBuildOrderWithShift_Jmp, 6, (unsigned long)NewBuildOrderWithShift);
    //patch.WriteJumpSized(PtrDistanceToTargetWithShift_Jmp, 6, (unsigned long)PtrDistanceToTargetWithShift);
    //patch.WriteJumpSized(DontResetOrderWhenChanged_Jmp, 8, (unsigned long)DontResetOrderWhenChanged);
    //patch.WriteJumpSized(DontResetOrderWhenChanged2x2_Jmp, 9, (unsigned long)DontResetOrderWhenChanged2x2);
    //patch.WriteJumpSized(CheckMyFlagToNotMakeNewOrder_Jmp, 5, (unsigned long)CheckMyFlagToNotMakeNewOrder);
    //patch.WriteJumpSized(ReplaceSubGpsToOrderWithShift_Jmp, 8, (unsigned long)ReplaceSubGpsToOrderWithShift);
    //patch.WriteJumpSized(ReplaceOrderGpsToOrderWithShift_Jmp, 5, (unsigned long)ReplaceOrderGpsToOrderWithShift);
    //patch.WriteJumpSized(AlwaysJumpToRightOrderCreation_Jmp, 6, (unsigned long)AlwaysJumpToRightOrderCreation);
    //patch.WriteJumpSized(DontDestroyOrderObjects_Jmp, 5, (unsigned long)DontDestroyOrderObjects);
    //patch.WriteNops((void *)0x0045FE59, 24); // Nop for don't erase
    //patch.WriteJumpSized(AfterCheckOrderStateReturns2_Jmp, 7, (unsigned long)AfterCheckOrderStateReturns2);
    //----------
    

    //Autosave
    patch.WriteJumpSized(AutosaveCheckTick_Jmp, 5, (unsigned long)AutosaveCheckTick);
    patch.WriteJumpSized(AutosaveCheckMarker_Jmp, 8, (unsigned long)AutosaveCheckMarker);
    patch.WriteJumpSized(AutosaveMakeFileName_Jmp, 5, (unsigned long)AutosaveMakeFileName);
    patch.WriteJumpSized(AutosaveDontCheckIfFileExists_Jmp, 5, (unsigned long)AutosaveDontCheckIfFileExists);
    patch.WriteJumpSized(AutosaveSkipToggleMenu_Jmp, 7, (unsigned long)AutosaveSkipToggleMenu);
    //-------
    
  
    patch.WriteU32((void *)0x005C8253, 0x0079C050); // Random map directory - custom
    patch.WriteU32((void *)0x005C851C, 0x0079C050); // Random map directory - custom 2
    patch.WriteU32((void *)0x005C7AE8, 0x0079C050); // Random map directory - custom 3

    patch.WriteU32((void *)0x0047A44E, 0); // Give ghost state teleport
    patch.WriteByte((void *)0x004ECC7D, 12); // Increase teleshield range
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

    
    patch.WriteU32((void *)0x007D2220, 1500); // Paralyze ray time (vanilla 375 = 15 sec)
    patch.WriteU32((void *)0x007D2210, 200); // NeuroParalyze shell time (vanilla 250 = 10 sec)
    patch.WriteU32((void *)0x007C0D9E, 1);  // SI NEUTRSHIELD dep lvl
    
    
    

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
    patch.WriteU32((void *)0x00792498, 6);   // DPT range 1
    patch.WriteU32((void *)0x0079249C, 10);  // DPT range 2
    patch.WriteU32((void *)0x00792710, 121); // DPT range research id

    patch.WriteByte((void *)0x00792288, 8); // Light laser first range
    patch.WriteByte((void *)0x007922C8, 8); // Heavy laser first range
    //


    patch.WriteU32((void *)0x007E6738, 150); // DPT turret damage T1
    patch.WriteU32((void *)0x007E673C, 180); // DPT turret damage T2
    patch.WriteU32((void *)0x007E6740, 240); // DPT turret damage T3
    patch.WriteU32((void *)0x007E66F0, 90);  // Energy shell dmg t3


    patch.WriteU32((void *)0x007A8C90, 80); // Destroyer reload (vanilla 50)
    patch.WriteU32((void *)0x007E6620, 40);  // Destroyer T1 (vanilla 60)
    patch.WriteU32((void *)0x007E6624, 120); // Destroyer T2 (vanilla 150)

    patch.WriteU32((void *)0x007E0570, 280); // Mine-Layer corium
    patch.WriteU32((void *)0x007E05E0, 250); // Bio-acid assaulter corium (vanilla 200)
    patch.WriteU32((void *)0x007E05A0, 280); // Defender corium
    // patch.WriteU32((void *)0x007E0A60, 900); // Bio-acid assaulter silicon (vanilla 700)

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
    patch.WriteU32((void *)0x007A8E1C, 1);  // Bio-assaulter mine stock

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

    //------
    patch.WriteByte((void *)0x0047A9D1, 0xEC); // Teleport charge use personal (-20)
    patch.WriteByte((void *)0x00487ED3, 0x14); // Teleport check charge to unlock button

    // patch.WriteJumpSized(CasseteShellExpl3CellsB4Target_Jmp, 6, (unsigned
    // long)CasseteShellExpl3CellsB4Target);
    patch.WriteJumpSized(CasseteShellExplMidWay_Jmp, 6, (unsigned long)CasseteShellExplMidWay);

    patch.WriteJumpSized(IonArmorBlockedDamageHalf_Jmp, 5,
                         (unsigned long)IonArmorBlockedDamageHalf);
    patch.WriteNops((void *)0x00459E37, 2); // Ion armor nops

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
    // patch.WriteU32((void *)0x007DFCF0, ); // Bio-assaulter
    // patch.WriteU32((void *)0x007DFCF8, ); // Psi-zond (Vermin)
    // patch.WriteU32((void *)0x007DFCDC, ); // Paralyzer


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
    patch.WriteU32((void *)0x007E417C, 3000); // WS Dockyard HP
    patch.WriteU32((void *)0x007E4180, 3000); // BO Dockyard HP
    patch.WriteU32((void *)0x007E4188, 2250); // WS Docks HP
    patch.WriteU32((void *)0x007E418C, 2250); // BO Docks HP
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

    patch.WriteU32((void *)0x007E1D28, 2000); // Plasmotron corium
    patch.WriteU32((void *)0x007E1D2C, 2000); // Plasmotron corium
    patch.WriteU32((void *)0x007E1D30, 2000); // Plasmotron corium

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
    //patch.WriteU32((void *)0x007E1EC0, 250); // Gas Shell launcher corium
    //patch.WriteU32((void *)0x007E1EC4, 250); // Gas Shell launcher corium
    //patch.WriteU32((void *)0x007E1EC8, 250); // Gas Shell launcher corium

    patch.WriteU32((void *)0x007E1ECC, 150); // DPT corium
    patch.WriteU32((void *)0x007E1ED0, 150); // DPT corium
    patch.WriteU32((void *)0x007E1ED4, 150); // DPT corium

    patch.WriteU32((void *)0x007E1EFC, 70); // Pulsar corium
    patch.WriteU32((void *)0x007E1F00, 70); // Pulsar corium
    patch.WriteU32((void *)0x007E1F04, 70); // Pulsar corium

    patch.WriteU32((void *)0x007E1EF0, 200); // Bio mine launcher corium
    patch.WriteU32((void *)0x007E1EF4, 200); // Bio mine launcher corium
    patch.WriteU32((void *)0x007E1EF8, 200); // Bio mine launcher corium

    patch.WriteU32((void *)0x007E1EE4, 230); // Jump mine launcher corium
    patch.WriteU32((void *)0x007E1EE8, 230); // Jump mine launcher corium
    patch.WriteU32((void *)0x007E1EEC, 230); // Jump mine launcher corium

    patch.WriteU32((void *)0x007E1EE0, 200); // Ion reflector corium

    //patch.WriteU32((void *)0x007E1DE4, 0);   // Core corium

    // METAL/SILICON
    //patch.WriteU32((void *)0x007E2568, 800);  // Depot cost WS
    //patch.WriteU32((void *)0x007E256C, 800);  // Depot cost BO
    //patch.WriteU32((void *)0x007E3390, 600);  // Depot cost SI
    patch.WriteU32((void *)0x007E33C0, 600); // Silicon extractor silicon
    
    patch.WriteU32((void *)0x007E2508, 1200); // Docks cost WS
    patch.WriteU32((void *)0x007E250C, 1200); // Docks cost BO
    // patch.WriteU32((void *)0x007E3414, );    // Pulsar silicon

    patch.WriteU32((void *)0x007E33D8, 1200); // Gas canon silicon
    patch.WriteU32((void *)0x007E33E4, 900); // DPT silicon
    //patch.WriteU32((void *)0x007E33F0, 600);  // Ion reflector silicon
    patch.WriteU32((void *)0x007E3408, 700);  // Bio-mine launcher silicon
    patch.WriteU32((void *)0x007E345C, 1400); // Parcher silicon
    // patch.WriteU32((void *)0x007E3360, 1400); // Protoplasm generator silicon

    patch.WriteU32((void *)0x007E2598, 1000); // STOLp metal
    patch.WriteU32((void *)0x007E259C, 1000); // STOLp metal
    patch.WriteU32((void *)0x007E25A0, 1000); // STOLp metal

    patch.WriteU32((void *)0x007E2670, 1200); // Plasma canon metal
    patch.WriteU32((void *)0x007E2674, 1200); // Plasma canon metal
    patch.WriteU32((void *)0x007E2678, 1200); // Plasma canon metal

    patch.WriteU32((void *)0x007E25BC, 900); // USG metal
    patch.WriteU32((void *)0x007E25C0, 900); // USG metal
    patch.WriteU32((void *)0x007E25C4, 900); // USG metal

    patch.WriteU32((void *)0x007E25EC, 400); // Light laser metal
    patch.WriteU32((void *)0x007E25F0, 400); // Light laser metal
    patch.WriteU32((void *)0x007E25F4, 400); // Light laser metal

    patch.WriteU32((void *)0x007E25F8, 1400); // Magnetic-Mine Launcher metal
    patch.WriteU32((void *)0x007E25FC, 1400); // Magnetic-Mine Launcher metal
    patch.WriteU32((void *)0x007E2600, 1400); // Magnetic-Mine Launcher metal

    patch.WriteU32((void *)0x007E261C, 1000); // Heavy laser metal
    patch.WriteU32((void *)0x007E2620, 1000); // Heavy laser metal
    patch.WriteU32((void *)0x007E2624, 1000); // Heavy laser metal

    patch.WriteU32((void *)0x007E2628, 1200); // E/M launcher metal
    patch.WriteU32((void *)0x007E262C, 1200); // E/M launcher metal
    patch.WriteU32((void *)0x007E2630, 1200); // E/M launcher metal

    patch.WriteU32((void *)0x007E25D4, 1000); // Plasmotron metal
    patch.WriteU32((void *)0x007E25D8, 1000); // Plasmotron metal
    patch.WriteU32((void *)0x007E25DC, 1000); // Plasmotron metal

    patch.WriteU32((void *)0x007E25E0, 2000); // Nuclear launcher metal
    patch.WriteU32((void *)0x007E25E4, 2000); // Nuclear launcher metal
    patch.WriteU32((void *)0x007E25E8, 2000); // Nuclear launcher metal

    patch.WriteU32((void *)0x007E264C, 2000); // Laser Bomb Launcher metal
    patch.WriteU32((void *)0x007E2650, 2000); // Laser Bomb Launcher metal
    patch.WriteU32((void *)0x007E2654, 2000); // Laser Bomb Launcher metal

    patch.WriteU32((void *)0x007E3468, 2000); // Vacuum bomb launcher silicon


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
    // patch.WriteU32((void *)0x007E0A64, 1000);  // Usurper silicon
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
    patch.WriteU32((void *)0x007E05E8, 400); // Psi-zond corium
    patch.WriteU32((void *)0x007E059C, 180); // Invader corium
    patch.WriteU32((void *)0x007E05D0, 200); // Energizer corium
    //patch.WriteU32((void *)0x007E05B8, 220); // Avenger corium
    patch.WriteU32((void *)0x007E0594, 90);  // Destroyer corium
    patch.WriteU32((void *)0x007E0598, 360); // Heavy Cruiser corium
    patch.WriteU32((void *)0x007E05B4, 280); // Phantom corium
    patch.WriteU32((void *)0x007E05A4, 120); // Raider corium

    patch.WriteU32((void *)0x007E05E0, 330); // Bio-acid assaulter corium (vanilla 200)
    patch.WriteU32((void *)0x007E05C8, 100); // Supplier corium (vanilla 0)
    patch.WriteU32((void *)0x007E0A60, 900); // Bio-acid assaulter silicon (vanilla 700)

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
    patch.WriteU32((void *)0x007DFC38, 600);  // Psi-zond hp
    patch.WriteU32((void *)0x007DFC28, 1400); // Dreadnaught hp
    patch.WriteU32((void *)0x007DFC30, 760); // Bio-assaulter hp
    
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
    patch.WriteU32((void *)0x007E5638, 6000); // WS UPG USG time
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
    patch.WriteByte((void *)0x007C025E, 0);   // BO MMLAUNCHER dep2
    patch.WriteByte((void *)0x007C0272, 40);  // BO EMTORP dep
    patch.WriteByte((void *)0x007C0560, 137); // BO LASBOMB dep
    patch.WriteByte((void *)0x007C0565, 50);   // BO LASBOMB dep2
    patch.WriteByte((void *)0x007C0673, 0);   // BO UPG MINESPD dep
    patch.WriteByte((void *)0x007C033A, 51);  // BO LIGHTLASSPD dep
    patch.WriteByte((void *)0x007C02EF, 51);  // BO RUBY dep
    patch.WriteByte((void *)0x007C036C, 38);  // BO HEAVYLASRATE dep
    patch.WriteByte((void *)0x007C0353, 55);  // BO LASRATE dep
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
    patch.WriteU32((void *)0x007E56A8, 7500); // BO HEAVYCRUISER time
    // patch.WriteU32((void *)0x007E58A8, 9000); // BO ANTISMP time
    patch.WriteU32((void *)0x007E5748, 6000); // BO USGDEF time
    patch.WriteU32((void *)0x007E5D18, 7500); // BO UPGMINE time
    patch.WriteU32((void *)0x007E5C68, 4500); // BO RADAR time
    patch.WriteU32((void *)0x007E5CB8, 4500); // BO HACK time
    patch.WriteU32((void *)0x007E5D48, 3000); // BO UPGHACK time
    patch.WriteU32((void *)0x007E5D58, 6000); // BO DEFHACK time
    patch.WriteU32((void *)0x007E5D98, 7500); // BO PHANTOMUPG time
    patch.WriteU32((void *)0x007E56D8, 6000); // BO HEAVYLAS time
    patch.WriteU32((void *)0x007E57E8, 6000); // BO HEAVYLASRANGE time
    patch.WriteU32((void *)0x007E5818, 7500); // BO LASRATE time
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
    patch.WriteU32((void *)0x007E57D8, 3000); // BO LIGHTLASRANGE time
    patch.WriteU32((void *)0x007E5CC8, 3000); // BO TURRETS FLOAT time
    

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
    patch.WriteByte((void *)0x007C0A48, 0); // SI IONARMR dep
    patch.WriteByte((void *)0x007C0A4C, 0); // SI IONARMR dep lvl
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
    patch.WriteByte((void *)0x007C0809, 72);  // SI INVISFIND dep
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
    patch.WriteU32((void *)0x007E5A98, 6000);  // SI PORTALCODE time
    //patch.WriteU32((void *)0x007E5BE8, 3000);  // SI RESIDENT time
    patch.WriteU32((void *)0x007E59B8, 7500);  // SI CORMINESPEED time
    patch.WriteU32((void *)0x007E5BB8, 4500);  // SI ACOUSTICMINES time
    patch.WriteU32((void *)0x007E5BA8, 6000);  // SI BIOASSAULTER time
    // patch.WriteU32((void *)0x007E5BD8, );  // SI UPGBIO time
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
    


    // SUBMARINES
    // SPEED Upgrade
    // patch.WriteByte((void *)0x0045F737, 4); // Plus total at T2
    patch.WriteByte((void *)0x0045F733, 4); // Plus total at T3
    patch.WriteByte((void *)0x0045F72F, 6); // Plus total at T4

    // BUILDINGS

    // HP
    patch.WriteU32((void *)0x007E43DC, 700);  // Silicon extractor HP (+100)
    patch.WriteU32((void *)0x007E417C, 3000); // WS Dockyard HP
    patch.WriteU32((void *)0x007E4180, 3000); // BO Dockyard HP
    patch.WriteU32((void *)0x007E4188, 2250); // WS Docks HP
    patch.WriteU32((void *)0x007E418C, 2250); // BO Docks HP
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
    patch.WriteU32((void *)0x007E42F0, 1500); // Plasma canon HP
    patch.WriteU32((void *)0x007E42F4, 1500); // Plasma canon HP

    patch.WriteU32((void *)0x007E426C, 1000); // Light laser HP
    patch.WriteU32((void *)0x007E4270, 1000); // Light laser HP
    patch.WriteU32((void *)0x007E4274, 1000); // Light laser HP
    // patch.WriteU32((void *)0x007E429C, 1300); // Heavy laser HP
    // patch.WriteU32((void *)0x007E42A0, 1300); // Heavy laser HP
    // patch.WriteU32((void *)0x007E42A4, 1300); // Heavy laser HP

    //patch.WriteU32((void *)0x007E4428, 1100); // Pulsar HP
    //patch.WriteU32((void *)0x007E442C, 1100); // Pulsar HP
    //patch.WriteU32((void *)0x007E4430, 1100); // Pulsar HP
    patch.WriteU32((void *)0x007E43EC, 1200); // Gas cannon HP (vanilla 1100)
    patch.WriteU32((void *)0x007E43F0, 1200); // Gas cannon HP (vanilla 1100)
    patch.WriteU32((void *)0x007E43F4, 1200); // Gas cannon HP (vanilla 1100)
    patch.WriteU32((void *)0x007E441C, 900); // Bio mine launcher HP
    patch.WriteU32((void *)0x007E4420, 900); // Bio mine launcher HP
    patch.WriteU32((void *)0x007E4424, 900); // Bio mine launcher HP
    // patch.WriteU32((void *)0x007E43E0, 600);  // Soliton oscilator HP
    // patch.WriteU32((void *)0x007E43E4, 600);  // Soliton oscilator HP
    // patch.WriteU32((void *)0x007E43E8, 600);  // Soliton oscilator HP

    // Corium
    // WS
    patch.WriteU32((void *)0x007E1CE0, 80); // HF cannon corium
    patch.WriteU32((void *)0x007E1CE4, 80); // HF cannon corium
    patch.WriteU32((void *)0x007E1CE8, 80); // HF cannon corium

    patch.WriteU32((void *)0x007E1CEC, 120); // STOLp corium
    patch.WriteU32((void *)0x007E1CF0, 120); // STOLp corium

    patch.WriteU32((void *)0x007E1DC4, 280); // Plasma cannon corium
    patch.WriteU32((void *)0x007E1DC8, 280); // Plasma cannon corium
    patch.WriteU32((void *)0x007E1DCC, 280); // Plasma cannon corium

    patch.WriteU32((void *)0x007E1D1C, 1000); // Psychotron corium
    patch.WriteU32((void *)0x007E1D20, 1000); // Psychotron corium
    patch.WriteU32((void *)0x007E1D24, 1000); // Psychotron corium

    patch.WriteU32((void *)0x007E1D28, 4000); // Plasmotron corium
    patch.WriteU32((void *)0x007E1D2C, 4000); // Plasmotron corium
    patch.WriteU32((void *)0x007E1D30, 4000); // Plasmotron corium

    // patch.WriteU32((void *)0x007E1D34, ); // Nuclear launcher corium

    // BO
    patch.WriteU32((void *)0x007E1D40, 60); // Light laser corium
    patch.WriteU32((void *)0x007E1D44, 60); // Light laser corium
    patch.WriteU32((void *)0x007E1D48, 60); // Light laser corium
    patch.WriteU32((void *)0x007940D8, 50); // Light laser ammo

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

    patch.WriteU32((void *)0x007E1DA0, 5000); // Laser bomb launcher corium
    patch.WriteU32((void *)0x007E1DA0, 5000); // Laser bomb launcher corium
    patch.WriteU32((void *)0x007E1DA0, 5000); // Laser bomb launcher corium

    // SI
    //patch.WriteU32((void *)0x007E1EC0, 320); // Gas Shell launcher corium
    //patch.WriteU32((void *)0x007E1EC4, 320); // Gas Shell launcher corium
    //patch.WriteU32((void *)0x007E1EC8, 320); // Gas Shell launcher corium

    patch.WriteU32((void *)0x007E1ECC, 150); // DPT corium
    patch.WriteU32((void *)0x007E1ED0, 150); // DPT corium
    patch.WriteU32((void *)0x007E1ED4, 150); // DPT corium

    patch.WriteU32((void *)0x007E1EFC, 70); // Pulsar corium
    patch.WriteU32((void *)0x007E1F00, 70); // Pulsar corium
    patch.WriteU32((void *)0x007E1F04, 70); // Pulsar corium

    patch.WriteU32((void *)0x007E1EF0, 200); // Bio mine launcher corium
    patch.WriteU32((void *)0x007E1EF4, 200); // Bio mine launcher corium
    patch.WriteU32((void *)0x007E1EF8, 200); // Bio mine launcher corium

    patch.WriteU32((void *)0x007E1EE4, 230); // Jump mine launcher corium
    patch.WriteU32((void *)0x007E1EE8, 230); // Jump mine launcher corium
    patch.WriteU32((void *)0x007E1EEC, 230); // Jump mine launcher corium

    patch.WriteU32((void *)0x007E1EE0, 200); // Ion reflector corium

    patch.WriteU32((void *)0x007E1EBC, 700); // Soliton corium

    //patch.WriteU32((void *)0x007E1F4C, 320); // Parcher corium
    
    patch.WriteU32((void *)0x007E1F58, 5000); // Vacuum bomb launcher corium

    // patch.WriteU32((void *)0x007E1DE4, 0);   // Core corium



    // METAL/SILICON
    // patch.WriteU32((void *)0x007E2568, 800);  // Depot cost WS
    // patch.WriteU32((void *)0x007E256C, 800);  // Depot cost BO
    // patch.WriteU32((void *)0x007E3390, 600);  // Depot cost SI
    patch.WriteU32((void *)0x007E33C0, 600); // Silicon extractor silicon

    patch.WriteU32((void *)0x007E2508, 1200); // Docks cost WS
    patch.WriteU32((void *)0x007E250C, 1200); // Docks cost BO
    // patch.WriteU32((void *)0x007E3414, );    // Pulsar silicon

    patch.WriteU32((void *)0x007E33D8, 1200); // Gas canon silicon
    patch.WriteU32((void *)0x007E33E4, 900);  // DPT silicon
    // patch.WriteU32((void *)0x007E33F0, 600);  // Ion reflector silicon
    patch.WriteU32((void *)0x007E3408, 700);  // Bio-mine launcher silicon
    patch.WriteU32((void *)0x007E345C, 1400); // Parcher silicon
    // patch.WriteU32((void *)0x007E3360, 1400); // Protoplasm generator silicon

    patch.WriteU32((void *)0x007E2598, 1000); // STOLp metal
    patch.WriteU32((void *)0x007E259C, 1000); // STOLp metal
    patch.WriteU32((void *)0x007E25A0, 1000); // STOLp metal

    patch.WriteU32((void *)0x007E2670, 1200); // Plasma canon metal
    patch.WriteU32((void *)0x007E2674, 1200); // Plasma canon metal
    patch.WriteU32((void *)0x007E2678, 1200); // Plasma canon metal

    patch.WriteU32((void *)0x007E25BC, 900); // USG metal
    patch.WriteU32((void *)0x007E25C0, 900); // USG metal
    patch.WriteU32((void *)0x007E25C4, 900); // USG metal

    patch.WriteU32((void *)0x007E25EC, 400); // Light laser metal
    patch.WriteU32((void *)0x007E25F0, 400); // Light laser metal
    patch.WriteU32((void *)0x007E25F4, 400); // Light laser metal

    patch.WriteU32((void *)0x007E25F8, 1400); // Magnetic-Mine Launcher metal
    patch.WriteU32((void *)0x007E25FC, 1400); // Magnetic-Mine Launcher metal
    patch.WriteU32((void *)0x007E2600, 1400); // Magnetic-Mine Launcher metal

    patch.WriteU32((void *)0x007E261C, 1000); // Heavy laser metal
    patch.WriteU32((void *)0x007E2620, 1000); // Heavy laser metal
    patch.WriteU32((void *)0x007E2624, 1000); // Heavy laser metal

    patch.WriteU32((void *)0x007E2628, 1200); // E/M launcher metal
    patch.WriteU32((void *)0x007E262C, 1200); // E/M launcher metal
    patch.WriteU32((void *)0x007E2630, 1200); // E/M launcher metal

    patch.WriteU32((void *)0x007E25D4, 1000); // Plasmotron metal
    patch.WriteU32((void *)0x007E25D8, 1000); // Plasmotron metal
    patch.WriteU32((void *)0x007E25DC, 1000); // Plasmotron metal

    patch.WriteU32((void *)0x007E25E0, 2000); // Nuclear launcher metal
    patch.WriteU32((void *)0x007E25E4, 2000); // Nuclear launcher metal
    patch.WriteU32((void *)0x007E25E8, 2000); // Nuclear launcher metal

    patch.WriteU32((void *)0x007E264C, 2000); // Laser Bomb Launcher metal
    patch.WriteU32((void *)0x007E2650, 2000); // Laser Bomb Launcher metal
    patch.WriteU32((void *)0x007E2654, 2000); // Laser Bomb Launcher metal

    patch.WriteU32((void *)0x007E3468, 2000); // Vacuum bomb launcher silicon

    
    // TURRETS RANGE
    patch.WriteByte((void *)0x00792208, 7); // HF Canon first range
    patch.WriteByte((void *)0x00792218, 8); // STOLp first range
    patch.WriteByte((void *)0x00792338, 9); // Plasma canon first range

    patch.WriteByte((void *)0x00792288, 7); // Light laser first range
    patch.WriteByte((void *)0x0079228C, 8); // Light laser second range
    patch.WriteByte((void *)0x007922C8, 6); // Heavy laser first range
    patch.WriteByte((void *)0x007922CC, 8); // Heavy laser second range
    patch.WriteByte((void *)0x00792298, 7); // MML first range
    patch.WriteByte((void *)0x007922A0, 8);  // MML mines first range
    patch.WriteByte((void *)0x007922D8, 9); // E/M launcher first range

    patch.WriteByte((void *)0x007924D8, 7); // Pulsar first range
    patch.WriteByte((void *)0x00792488, 7);  // Gas canon first range
    patch.WriteU32((void *)0x00792498, 8);  // DPT range 1
    //patch.WriteU32((void *)0x0079249C, 10); // DPT range 2
    // patch.WriteByte((void *)0x007924A8, 8); // Ion reflector first range
    patch.WriteByte((void *)0x00792538, 9); // Parcher first range
    //

    // Unlock Turrets Range 8->10
    patch.WriteByte((void *)0x004C3CC2, 246);
    patch.WriteByte((void *)0x004C3CF0, 246);
    patch.WriteByte((void *)0x004C3CF3, 10);
    patch.WriteByte((void *)0x004C3CC5, 10);
    patch.WriteByte((void *)0x004C426F, 10);
    patch.WriteByte((void *)0x004C4281, 10);
    //

    // SUBMARINES
    // METAL/SILICON
    patch.WriteU32((void *)0x007E07D0, 300); // Fighter metal
    patch.WriteU32((void *)0x007E07D4, 600); // Destroyer metal

    patch.WriteU32((void *)0x007E07A4, 450);  // Hunter metal
    patch.WriteU32((void *)0x007E07A8, 1100); // Cruiser metal
    patch.WriteU32((void *)0x007E07C8, 900); // Liberator metal
    patch.WriteU32((void *)0x007E07BC, 300);  // Transport WS metal
    patch.WriteU32((void *)0x007E07EC, 300);  // Transport BO metal
    // patch.WriteU32((void *)0x007E07E4, 300); // Raider metal

    // patch.WriteU32((void *)0x007E0A44, 200);  // Trailer silicon
    //patch.WriteU32((void *)0x007E0A50, 600); // Energizer silicon
    patch.WriteU32((void *)0x007E0A68, 900);  // Psi-zond silicon
    // patch.WriteU32((void *)0x007E0A64, 1000);  // Usurper silicon
    patch.WriteU32((void *)0x007E0A54, 250);  // Skat silicon
    // patch.WriteU32((void *)0x007E0A4C, 0);  // Paralisys probe silicon
    // patch.WriteU32((void *)0x007E0A5C, 0);  // Escort silicon
    patch.WriteU32((void *)0x007E0A58, 1200); // Dreadnaught silicon
    // patch.WriteU32((void *)0x007E0A40, 0); // Module-prototype silicon

    // CORIUM
    patch.WriteU32((void *)0x007E05DC, 150); // Escort corium
    patch.WriteU32((void *)0x007E05D4, 40);  // Skat corium
    // patch.WriteU32((void *)0x007E0590, 40);  // Fighter corium
    patch.WriteU32((void *)0x007E0564, 70);  // Hunter corium
    patch.WriteU32((void *)0x007E05E8, 400); // Psi-zond corium
    patch.WriteU32((void *)0x007E059C, 180); // Invader corium
    patch.WriteU32((void *)0x007E05D0, 200); // Energizer corium
    //patch.WriteU32((void *)0x007E05B8, 220); // Avenger corium
    patch.WriteU32((void *)0x007E0594, 90);  // Destroyer corium
    patch.WriteU32((void *)0x007E0598, 360); // Heavy Cruiser corium
    patch.WriteU32((void *)0x007E05B4, 280); // Phantom corium
    patch.WriteU32((void *)0x007E05A4, 120); // Raider corium

    patch.WriteU32((void *)0x007E05E0, 330); // Bio-acid assaulter corium (vanilla 200)
    patch.WriteU32((void *)0x007E05C8, 100); // Supplier corium (vanilla 0)
    patch.WriteU32((void *)0x007E0A60, 900); // Bio-acid assaulter silicon (vanilla 700)

    // BUILDTIME
    patch.WriteU32((void *)0x007E04C8, 600); // Fighter buildtime

    patch.WriteU32((void *)0x007E04D0, 600);  // Fighter buildtime
    patch.WriteU32((void *)0x007E0514, 500);  // Skat buildtime
    patch.WriteU32((void *)0x007E04B4, 1500); // Marauder buildtime
    patch.WriteU32((void *)0x007E04E4, 1500); // Raider buildtime
    patch.WriteU32((void *)0x007E0528, 1250); // Usurper buildtime
    // patch.WriteU32((void *)0x007E04D4, ); // Destroyer buildtime

    // HP
    patch.WriteU32((void *)0x007DFBB0, 200);  // Sentinel hp
    // patch.WriteU32((void *)0x007DFBC4, 1400); // Marauder hp
    // patch.WriteU32((void *)0x007DFBC0, 1000); // Minelayer hp
    patch.WriteU32((void *)0x007DFBB4, 520);  // Hunter hp
    patch.WriteU32((void *)0x007DFBBC, 1600); // DC Bomber hp
    patch.WriteU32((void *)0x007DFBD8, 1200); // Liberator hp
    patch.WriteU32((void *)0x007DFBD0, 600);  // Cyberworm hp

    patch.WriteU32((void *)0x007DFBE0, 300);  // Fighter hp
    //patch.WriteU32((void *)0x007DFBE4, 580);  // Destroyer hp
    patch.WriteU32((void *)0x007DFBEC, 700);  // Invader hp
    // patch.WriteU32((void *)0x007DFBBF0, ); // Defender hp
    patch.WriteU32((void *)0x007DFBF4, 1100); // Raider hp
    patch.WriteU32((void *)0x007DFC00, 600);  // Cyberdolphin hp

    patch.WriteU32((void *)0x007DFC24, 190);  // Skat hp
    // patch.WriteU32((void *)0x007DFC2C, ); // Escort hp
    patch.WriteU32((void *)0x007DFC38, 600);  // Psi-zond hp
    patch.WriteU32((void *)0x007DFC28, 1400); // Dreadnaught hp
    patch.WriteU32((void *)0x007DFC30, 760);  // Bio-assaulter hp
    patch.WriteU32((void *)0x007DFC34, 1000); // Usurper hp

    patch.WriteU32((void *)0x007DFC14, 400); // Transport SI hp

    // ATTACK COOLDOWN
    patch.WriteU32((void *)0x007A8CB4, 40); // Aveger cd
    
    // WEAPONS

    // DAMAGE
    patch.WriteU32((void *)0x007E6490, 120); // Cruiser T1 damage
    patch.WriteU32((void *)0x007E6494, 160); // Cruiser T2 damage
    patch.WriteU32((void *)0x007E6498, 200); // Cruiser T3 damage
    patch.WriteU32((void *)0x007E649C, 230); // Cruiser T4 damage
    patch.WriteU32((void *)0x007E64A0, 260); // Cruiser T5 damage
    //patch.WriteU32((void *)0x007A8C5C, 35); // Sentinel reload
    patch.WriteU32((void *)0x007A8C80, 90); // Terminator reload

    patch.WriteU32((void *)0x007E6534, 100); // HF heavy T2 damage
    patch.WriteU32((void *)0x007E679C, 100); // Pulsar T1 damage
    
    
    patch.WriteU32((void *)0x007E6520, 70); // Sentinel dmg T2
    patch.WriteU32((void *)0x007E65E4, 600); // DC Bomb damage

    patch.WriteU32((void *)0x007DFF20, 60); // Plasma canon cooldown (vanilla 100 (4 sec))
    
    //patch.WriteU32((void *)0x007A8C90, 80);  // Destroyer reload (vanilla 50)
    //patch.WriteU32((void *)0x007E6620, 40);  // Destroyer T1 (vanilla 60)
    patch.WriteU32((void *)0x007E6624, 100); // Destroyer T2 (vanilla 150)

    patch.WriteU32((void *)0x007E6508, 160); // Heavy laser (vanilla 200)

    patch.WriteU32((void *)0x007E64A4, 10); // Cassete shell
    patch.WriteU32((void *)0x007E66FC, 10); // Ion cassete t1
    patch.WriteU32((void *)0x007E6700, 10); // Ion cassete t2
    patch.WriteU32((void *)0x007E6704, 10); // Ion cassete t3
    // patch.WriteU32((void *)0x007E6724, 20); // Ion cassete subshell t1
    // patch.WriteU32((void *)0x007E6728, 30); // Ion cassete subshell t2
    // patch.WriteU32((void *)0x007E672C, 40); // Ion cassete subshell t3
    patch.WriteU32((void *)0x007E66F0, 90); // Energy shell dmg t3
    patch.WriteU32((void *)0x007E67C4, 25); // Soliton dmg
    

    // patch.WriteU32((void *)0x007E6648, );  // Gas Shell Launcher damage

    patch.WriteU32((void *)0x007E6580, 800); // Plasma damage
    patch.WriteByte((void *)0x00642ABA, 3);   // Laser reflection % (25 -> 12.5)
        
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

    
    patch.WriteU32((void *)0x004BB5DF, 0x3E8); // max blocked damage check
    patch.WriteU32((void *)0x004BB5E6, 0x3E8); // max blocked damage replace

    //ECONOMICS
    //patch.WriteU32((void *)0x0043092D, 12); // Metal in 1/40 of Transport capacity load
    patch.WriteU32((void *)0x0043092D, 15); // Metal in 1/40 of Transport capacity load
    //patch.WriteByte((void *)0x00469347, 0x7F); // Metal in 1/40 of Transport capacity unload
    patch.WriteU32((void *)0x00469348, 0x51490C8D);  // Metal in 1/40 of Transport capacity unload
    //patch.WriteNops((void *)0x00469348, 3);    // No additional shl 2
    
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

    //BO
    patch.WriteByte((void *)0x007C0E47, 38); // Research ID
    // Belongs race
    patch.WriteByte((void *)0x004E8364, 12);  // al or
    patch.WriteByte((void *)0x004E8365, 36);  // 36 (0x24 + 0x140) = 356
    patch.WriteByte((void *)0x004E8366, 144); // nop

    patch.WriteU32((void *)0x007E0538, 4500); // Time
    patch.WriteU32((void *)0x007E0838, 4600); // Metal
    patch.WriteU32((void *)0x007E05F8, 1300); // Corium
    patch.WriteU32((void *)0x007A8BB4, 158);  // Weapon type
    patch.WriteU32((void *)0x007A8CF4, 25);   // Reload
    patch.WriteU32((void *)0x007A8C54, 20);   // Ammo
    patch.WriteU32((void *)0x007DFC48, 2400); // HP
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

    patch.WriteByte((void *)0x004E4197, 5); // Replenish pod capacity (shift, result=4000)

    

    patch.WriteJumpSized(RangeAllSubs6_Jmp, 6, (unsigned long)RangeAllSubs6);


    

    patch.WriteU16((void *)0x0044F773, 0xD233); // Radio stutter make zero before period
    patch.WriteByte((void *)0x0044F77B, 75);    // Radio stutter new period

    // patch.WriteNops((void *)0x0057A320, 6);     // cassete check num??
    // patch.WriteU32((void *)0x0057B6D6, );      // Cassete conus 1/radius

    // UNITS
    patch.WriteByte((void *)0x0045094E, 25); // Phantom discharge

    // BUILDINGS
    patch.WriteU16((void *)0x004DEBA6, 6000);       // Power protector charge 1
    patch.WriteU16((void *)0x004DED31, 6000);       // Power protector charge 2
    patch.WriteU16((void *)0x004DED21, 6000);       // Power protector charge 3
    patch.WriteU32((void *)0x004C0309, 0x57619F10); // Power protector indicator adjust (2^43/6000)
        
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
    patch.WriteJumpSized(AntiAbuseHumanCenters_Jmp, 13, (unsigned long)AntiAbuseHumanCenters);
    //patch.WriteNops((void *)AntiAbuseHumanCenters_Jmp, 10); // Disable use of techcenters limit area

    // MODULES RESEARCH LISTS
    patch.WriteU32((void *)0x0079A3FC, 109); // SI speed module
    patch.WriteU32((void *)0x0079A400, 110);
    patch.WriteU32((void *)0x0079A404, 101);
    patch.WriteU32((void *)0x0079A408, 106);
    patch.WriteU32((void *)0x0079A40C, 105);
    patch.WriteU32((void *)0x0079A410, 102);
    patch.WriteU32((void *)0x0079A414, 104);
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


static bool AI2021—ompatible(Patcher::SPatch &patch)
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
    patch.WriteByte((void *)0x00792208, 10); // HF Canon first range
    patch.WriteByte((void *)0x00792218, 10); // STOLp first range
    patch.WriteByte((void *)0x00792338, 10); // Plasma canon first range

    patch.WriteByte((void *)0x00792288, 10); // Light laser first range
    patch.WriteByte((void *)0x007922C8, 10); // Heavy laser first range
    patch.WriteByte((void *)0x00792298, 10); // MML first range
    patch.WriteByte((void *)0x007922A0, 7); // MML mines first range

    patch.WriteByte((void *)0x007922D8, 10); // E/M launcher first range
    patch.WriteByte((void *)0x007924D8, 10); // Pulsar first range
    patch.WriteU32((void *)0x00792498, 10);  // DPT range 1
    patch.WriteByte((void *)0x00792488, 8); // Gas canon first range
    //patch.WriteByte((void *)0x007924A8, 8); // Ion reflector first range
    patch.WriteByte((void *)0x00792538, 10); // Parcher first range

    // TURRETS HP
    patch.WriteU32((void *)0x007E420C, 1300); // HF canon HP
    patch.WriteU32((void *)0x007E4210, 1300); // HF canon HP
    patch.WriteU32((void *)0x007E4218, 1700); // STOLp HP
    patch.WriteU32((void *)0x007E421C, 1700); // STOLp HP

    patch.WriteU32((void *)0x007E426C, 1200); // Light laser HP
    patch.WriteU32((void *)0x007E4270, 1200); // Light laser HP
    patch.WriteU32((void *)0x007E429C, 1600); // Heavy laser HP
    patch.WriteU32((void *)0x007E42A0, 1600); // Heavy laser HP
    patch.WriteU32((void *)0x007E4278, 1800); // MML HP
    patch.WriteU32((void *)0x007E427C, 1800); // MML HP
    patch.WriteU32((void *)0x007E25F8, 1500); // Magnetic-Mine Launcher metal
    patch.WriteU32((void *)0x007E25FC, 1500); // Magnetic-Mine Launcher metal
    patch.WriteU32((void *)0x007E2600, 1500); // Magnetic-Mine Launcher metal

    patch.WriteU32((void *)0x007E42A8, 1400); // E/M HP
    patch.WriteU32((void *)0x007E42AC, 1400); // E/M HP

    patch.WriteU32((void *)0x007E4428, 1100); // Pulsar HP
    patch.WriteU32((void *)0x007E442C, 1100); // Pulsar HP
    patch.WriteU32((void *)0x007E4430, 1100); // Pulsar HP
    patch.WriteU32((void *)0x007E43EC, 1300); // Gas cannon HP (vanilla 1100)
    patch.WriteU32((void *)0x007E43F0, 1300); // Gas cannon HP (vanilla 1100)
    patch.WriteU32((void *)0x007E43F4, 1300); // Gas cannon HP (vanilla 1100)
    patch.WriteU32((void *)0x007E429C, 1500); // DPT HP
    patch.WriteU32((void *)0x007E42A0, 1500); // DPT HP
    patch.WriteU32((void *)0x007E42A4, 1500); // DPT HP
    // patch.WriteU32((void *)0x007E43E0, 600);  // Soliton oscilator HP
    // patch.WriteU32((void *)0x007E43E4, 600);  // Soliton oscilator HP
    // patch.WriteU32((void *)0x007E43E8, 600);  // Soliton oscilator HP
   
    // Flagship
    // BO
    patch.WriteByte((void *)0x007C0E47, 35); // Research ID

    patch.WriteU32((void *)0x007E0538, 3750); // Time
    patch.WriteU32((void *)0x007E0838, 3800); // Metal
    patch.WriteU32((void *)0x007E05F8, 1100); // Corium
    patch.WriteU32((void *)0x007A8BB4, 157);  // Weapon type
    patch.WriteU32((void *)0x007A8CF4, 20);   // Reload
    patch.WriteU32((void *)0x007A8C54, 20);   // Ammo
    patch.WriteU32((void *)0x007DFC48, 1900); // HP

    patch.WriteJumpSized(ChangeSubsRange_Jmp, 7, (unsigned long)ChangeSubsRange);

    return true;
}

typedef bool (*PatchFunction)(Patcher::SPatch &patch);
static const PatchFunction Patches[] = {
    //Put your patch functions here:
    FixesQoL, 
    OneDepotFor2Mines,
    LobbyAnnouncements,
    AimPrediction,

    BalancingTacticsTree,
    ResearchBuildingsLimit,
    Flagships,
    //Experimental2

    // EnableFog
    // EconomicsAndOther,
    // BalancingNormalTree,
    // AI2021—ompatible
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
