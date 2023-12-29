#pragma once

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include "windows.h"
#include "winhttp.h"
#include <string>
#include <fstream>

#if !defined(_M_IX86) && !defined(__i386__)
#error "Patcher supports only x86 systems"
#endif


namespace Patcher {

static auto  game_mode_ptr = (DWORD *)0x00808783;
static char *player_name_ptr = (char *)0x00807DDD;

static auto host_flag = (DWORD *)0x007F586A;


void inline AnnounceGameHost()
{
    std::string player_name(player_name_ptr);

    HINTERNET hsession = WinHttpOpen(NULL, WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME,
                                     WINHTTP_NO_PROXY_BYPASS, 0);
    if (*game_mode_ptr == 3)
    {
        if (hsession)
        {
            HINTERNET hconnect = WinHttpConnect(hsession, L"discord.com",
                                                INTERNET_DEFAULT_HTTPS_PORT, 0);
            if (hconnect)
            {
                HINTERNET hRequest = WinHttpOpenRequest(
                    hconnect, L"POST", L"/api/v10/channels/1140961298692190238/messages", NULL,
                    WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
                if (hRequest)
                {
                    std::string body;
                    if (*host_flag == 1)
                    {
                        body = "content=Game hosted by " + player_name;
                    }
                    else
                    {
                        body = "content=Player " + player_name + " joined";
                    }
                    LPCWSTR additionalHeaders =
                        L"Authorization: Bot "
                        L"MTEzOTU5ODAwNTk2NDY1MjU4NQ.GDRJJ4."
                        L"9ET1k7Pge4v8CT6WCrYdGWY3F19DDC2b0tvBvg\r\n"
                        L"Content-Type: application/x-www-form-urlencoded\r\n";
                    WinHttpSendRequest(hRequest, additionalHeaders, -1L, (void *)body.c_str(),
                                       body.size(), body.size(), 0);
                    WinHttpReceiveResponse(hRequest, 0);
                    WinHttpReadData(hRequest, (void *)0x0080F33A, 0xFF, NULL);
                    WinHttpCloseHandle(hRequest);
                }
            }
        }
    }
}

void inline AnnounceGameStart()
{
    if (*game_mode_ptr == 3 && *host_flag)
    {
        std::string player_name(player_name_ptr);

        HINTERNET hsession = WinHttpOpen(NULL, WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                         WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

        if (hsession)
        {
            HINTERNET hconnect = WinHttpConnect(hsession, L"discord.com",
                                                INTERNET_DEFAULT_HTTPS_PORT, 0);
            if (hconnect)
            {
                HINTERNET hRequest = WinHttpOpenRequest(
                    hconnect, L"POST", L"/api/v10/channels/1140961298692190238/messages", NULL,
                    WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
                if (hRequest)
                {
                    std::string body = "content=Game started by " + player_name;
                    LPCWSTR additionalHeaders =
                        L"Authorization: Bot "
                        L"MTEzOTU5ODAwNTk2NDY1MjU4NQ.GDRJJ4."
                        L"9ET1k7Pge4v8CT6WCrYdGWY3F19DDC2b0tvBvg\r\n"
                        L"Content-Type: application/x-www-form-urlencoded\r\n";
                    WinHttpSendRequest(hRequest, additionalHeaders, -1L, (void *)body.c_str(),
                                       body.size(), body.size(), 0);
                    WinHttpReceiveResponse(hRequest, 0);
                    WinHttpReadData(hRequest, (void *)0x0080F33A, 0xFF, NULL);
                    WinHttpCloseHandle(hRequest);
                }
            }
        }
    }
}

void inline AnnounceGameCancel()
{
    if (*game_mode_ptr == 3 && *host_flag)
    {
        std::string player_name(player_name_ptr);

        HINTERNET hsession = WinHttpOpen(NULL, WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                         WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

        if (hsession)
        {
            HINTERNET hconnect = WinHttpConnect(hsession, L"discord.com",
                                                INTERNET_DEFAULT_HTTPS_PORT, 0);
            if (hconnect)
            {
                HINTERNET hRequest = WinHttpOpenRequest(
                    hconnect, L"POST", L"/api/v10/channels/1140961298692190238/messages", NULL,
                    WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
                if (hRequest)
                {
                    std::string body = "content=Game cancelled - " + player_name + " or changing map";
                    LPCWSTR additionalHeaders =
                        L"Authorization: Bot "
                        L"MTEzOTU5ODAwNTk2NDY1MjU4NQ.GDRJJ4."
                        L"9ET1k7Pge4v8CT6WCrYdGWY3F19DDC2b0tvBvg\r\n"
                        L"Content-Type: application/x-www-form-urlencoded\r\n";
                    WinHttpSendRequest(hRequest, additionalHeaders, -1L, (void *)body.c_str(),
                                       body.size(), body.size(), 0);
                    WinHttpReceiveResponse(hRequest, 0);
                    WinHttpReadData(hRequest, (void *)0x0080F33A, 0xFF, NULL);
                    WinHttpCloseHandle(hRequest);
                }
            }
        }
    }
}

void inline AnnounceGamePlayerLeft()
{
    if (*game_mode_ptr == 3)
    {
        std::string player_name(player_name_ptr);

        HINTERNET hsession = WinHttpOpen(NULL, WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                         WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

        if (hsession)
        {
            HINTERNET hconnect = WinHttpConnect(hsession, L"discord.com",
                                                INTERNET_DEFAULT_HTTPS_PORT, 0);
            if (hconnect)
            {
                HINTERNET hRequest = WinHttpOpenRequest(
                    hconnect, L"POST", L"/api/v10/channels/1140961298692190238/messages", NULL,
                    WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
                if (hRequest)
                {
                    std::string body = "content=Player " + player_name + " disconnected";
                    LPCWSTR additionalHeaders =
                        L"Authorization: Bot "
                        L"MTEzOTU5ODAwNTk2NDY1MjU4NQ.GDRJJ4."
                        L"9ET1k7Pge4v8CT6WCrYdGWY3F19DDC2b0tvBvg\r\n"
                        L"Content-Type: application/x-www-form-urlencoded\r\n";
                    WinHttpSendRequest(hRequest, additionalHeaders, -1L, (void *)body.c_str(),
                                       body.size(), body.size(), 0);
                    WinHttpReceiveResponse(hRequest, 0);
                    WinHttpReadData(hRequest, (void *)0x0080F33A, 0xFF, NULL);
                    WinHttpCloseHandle(hRequest);
                }
            }
        }
    }
}

bool inline AutosaveCheck()
{
    return (*game_mode_ptr == 3 && *host_flag);
}

bool inline ReadDbFile()
{
    std::ifstream patchListFile("patchlist.db");
    std::string patchList;
    if (patchListFile.is_open())
    {
        while (patchListFile)
        {
            std::getline(patchListFile, patchList);
        }
    }
    return 0;
}

static unsigned long AnnounceGameStart_Jmp = 0x005D48A9;
static unsigned long AnnounceGameStart_JmpBack = AnnounceGameStart_Jmp + 5;
static unsigned long AnnounceGameCancel_Jmp = 0x005C9D70;
static unsigned long AnnounceGameCancel_JmpBack = AnnounceGameCancel_Jmp + 5;
static unsigned long SetHostFlag_Jmp = 0x005C29F4;
static unsigned long SetHostFlag_JmpBack = SetHostFlag_Jmp + 5;
static unsigned long AnnounceGamePlayerLeft_Jmp = 0x005C9E69;
static unsigned long AnnounceGamePlayerLeft_JmpBack = AnnounceGamePlayerLeft_Jmp + 5;

__declspec(naked) void inline AnnounceGameStart_Detour()
{
    __asm pushad;
    __asm pushfd;

    __asm call[AnnounceGameStart];

    __asm popfd;
    __asm popad;

    __asm mov ebx, 01;

    __asm jmp[AnnounceGameStart_JmpBack];
}

__declspec(naked) void inline AnnounceGameCancel_Detour()
{
    __asm pushad;
    __asm pushfd;

    __asm call[AnnounceGameCancel];

    __asm popfd;
    __asm popad;

    __asm mov eax, [ebx + 0x1A5B];

    __asm jmp[AnnounceGameCancel_JmpBack];
}

__declspec(naked) void inline AnnounceGamePlayerLeft_Detour()
{
    __asm pushad;
    __asm pushfd;

    __asm call[AnnounceGamePlayerLeft];

    __asm popfd;
    __asm popad;

    __asm mov eax, [ebx + 0x1A5B];

    __asm jmp[AnnounceGamePlayerLeft_JmpBack];
}

__declspec(naked) void inline SetHostFlag_AnnounceGameHost_Detour()
{
    __asm pushad;
    __asm pushfd;

    __asm cmp al, 4;
    __asm je host;
    __asm cmp al, 5;
    __asm je host;
    __asm cmp al, 12;
    __asm je host;
    __asm mov dword ptr ss : [0x007F586A], 0;
    __asm jmp skip;

    __asm host:;
    __asm mov dword ptr ss : [0x007F586A], 1;

    __asm skip:;
    __asm call[AnnounceGameHost];
    __asm popfd;
    __asm popad;

    __asm cmp al, 6;
    __asm mov[ebx + 0x1E26], al;

    __asm jmp[SetHostFlag_JmpBack];
}

static unsigned long DontResetHostFlag_Jmp = 0x0042A955;
static unsigned long DontResetHostFlag_JmpBack = DontResetHostFlag_Jmp + 8;
__declspec(naked) void inline DontResetHostFlag()
{
    __asm {
        push ebx
        mov ebx, 0x007F586A
        mov ebx,[ebx]
        
        mov dword ptr ss:[esi], 0x0079059C
        rep stosd;
    
        mov dword ptr ss:[0x007F586A], ebx
        pop ebx
        jmp[DontResetHostFlag_JmpBack]
    }
}

static unsigned long MinesDetectionWS_Jmp = 0x0044F826;
static unsigned long MinesDetectionWS_JmpBack = MinesDetectionWS_Jmp + 5;
__declspec(naked) void inline MinesDetectionWS()
{
    __asm mov ecx, ebx;
    __asm mov eax, 0x004025EA;
    __asm call eax;

    __asm mov eax, 0xE0;

    __asm jmp[MinesDetectionWS_JmpBack];
}

static unsigned long MinesDetectionBO_Jmp = 0x0044F89E;
static unsigned long MinesDetectionBO_JmpBack = MinesDetectionBO_Jmp + 5;
__declspec(naked) void inline MinesDetectionBO()
{
    __asm mov ecx, ebx;
    __asm mov eax, 0x004025EA;
    __asm call eax;

    __asm mov eax, 0x144;

    __asm jmp[MinesDetectionBO_JmpBack];
}

static unsigned long MinesDetectionSI_Jmp = 0x0044F920;
static unsigned long MinesDetectionSI_JmpBack = MinesDetectionSI_Jmp + 5;
__declspec(naked) void inline MinesDetectionSI()
{
    __asm mov ecx, ebx;
    __asm mov eax, 0x004025EA;
    __asm call eax;

    __asm mov eax, 0x1C5;

    __asm jmp[MinesDetectionSI_JmpBack];
}

static unsigned long UPGNRGACCUM_decrease_deposit_Jmp = 0x004E0FA4;
static unsigned long UPGNRGACCUM_decrease_deposit_JmpBack = UPGNRGACCUM_decrease_deposit_Jmp + 9;
__declspec(naked) void inline UPGNRGACCUM_decrease_deposit()
{
    __asm {
    push 80
    push[esi + 0x24]
    mov eax, 0x0040186B
    call eax

    test ax, ax
    jle stock
    xor eax, eax
    add eax, -6
    jmp originalcode

    stock:
    xor eax, eax
    add eax, -5

    originalcode:
    add[esi + 0x000004E0], eax

    jmp[UPGNRGACCUM_decrease_deposit_JmpBack]
    }
}

static unsigned long UPGNRGACCUM_increase_accum_Jmp = 0x004E0FBF;
static unsigned long UPGNRGACCUM_increase_accum_JmpBack = UPGNRGACCUM_increase_accum_Jmp + 9;
__declspec(naked) void inline UPGNRGACCUM_increase_accum()
{
    __asm push 80;
    __asm push[esi + 0x24];
    __asm mov eax, 0x0040186B;
    __asm call eax;

    __asm test ax, ax;
    __asm jle stock;
    __asm xor edi, edi;
    __asm add edi, 6;
    __asm jmp originalcode;

    __asm stock:;
    __asm xor edi, edi;
    __asm add edi, 5;

    __asm originalcode:;
    __asm add[esi + 0x00000518], edi;

    __asm jmp[UPGNRGACCUM_increase_accum_JmpBack];
}

static unsigned long Transport_waiting_depot_distance_Jmp = 0x004676F6;
static unsigned long Transport_waiting_depot_distance_JmpBack = Transport_waiting_depot_distance_Jmp + 6;
__declspec(naked) void inline Transport_waiting_depot_distance()
{
    __asm mov edi, 1;
    __asm mov[esi + 0x000000B7], edi;

    __asm jmp[Transport_waiting_depot_distance_JmpBack];
}

static unsigned long Transport_waiting_mine_distance_Jmp = 0x0046971C;
static unsigned long Transport_waiting_mine_distance_JmpBack = Transport_waiting_mine_distance_Jmp + 6;
__declspec(naked) void inline Transport_waiting_mine_distance()
{
    __asm mov edi, 1;
    __asm mov[esi + 0x000000B7], edi;

    __asm jmp[Transport_waiting_mine_distance_JmpBack];
}

static unsigned long Transport_waiting_mine_distance2_Jmp = 0x00469863;
static unsigned long Transport_waiting_mine_distance2_JmpBack = Transport_waiting_mine_distance2_Jmp + 6;
__declspec(naked) void inline Transport_waiting_mine_distance2()
{
    __asm mov edi, 1;
    __asm mov[esi + 0x000000B7], edi;

    __asm jmp[Transport_waiting_mine_distance2_JmpBack];
}

static unsigned long OpenMap_Jmp = 0x00553B98;
static unsigned long OpenMap_Jmp_2 = 0x00553B9A;
static unsigned long OpenMap_JmpBack = OpenMap_Jmp + 6;
__declspec(naked) void inline OpenMap()
{
    __asm mov edx, [ebp + 0x18];
    __asm mov edi, -1;

    __asm start:;
    __asm xor eax, eax;
    __asm inc edi;
    __asm cmp edi, edx;
    __asm ja exitt;

    __asm row:;
    __asm inc eax;
    __asm cmp eax, edx;
    __asm ja start;

    __asm mov edx, [ebp + 0x18]; // view_size
    __asm mov ecx, [ebp + 0x10]; // map_ptr
    __asm push eax;
    __asm push 0xF;
    __asm push edx;
    __asm push edx;
    __asm push ecx;
    __asm push edi;
    __asm push eax;
    __asm mov eax, 0x00401D07;
    __asm call eax;  
    __asm pop eax;
    __asm add esp, 0x18;
    __asm mov edx, [ebp + 0x18];
    __asm mov ecx, [ebp + 0x10];
    __asm jmp row;

    __asm exitt:;
    __asm jmp[OpenMap_JmpBack];
}

static unsigned long UpgBHEExpansionRate_Jmp = 0x005F4CA7;
static unsigned long UpgBHEExpansionRate_JmpBack = UpgBHEExpansionRate_Jmp + 10;
__declspec(naked) void inline UpgBHEExpansionRate()
{
    __asm push 124;
    __asm push[esi + 0x0000051];
    __asm mov eax, 0x0040186B;
    __asm call eax;
    __asm test ax, ax;
    __asm jle originalcode;
    __asm mov[esi + 0x125], 0xA;
    __asm test ecx, ecx;
    __asm jmp exitt;

    __asm originalcode:;
    __asm mov[esi + 0x125], 7;
    __asm test ecx, ecx;

    __asm exitt:;
    __asm jmp[UpgBHEExpansionRate_JmpBack];
}

static unsigned long UpgBHESpeed_Jmp = 0x005F4C93;
static unsigned long UpgBHESpeed_JmpBack = UpgBHESpeed_Jmp + 10;
__declspec(naked) void inline UpgBHESpeed()
{
    __asm push 124;
    __asm push[esi + 0x0000051];
    __asm mov eax, 0x0040186B;
    __asm call eax;
    __asm test ax, ax;
    __asm jz originalcode;
    __asm mov dword ptr [esi + 0x121], 0xFFFFFFE7;
    __asm test ecx, ecx;
    __asm jmp exitt;

    __asm originalcode:;
    __asm mov dword ptr [esi + 0x121], 0xFFFFFFE2; // same

    __asm exitt:;
    __asm jmp[UpgBHESpeed_JmpBack];
}

static unsigned long UpgBHEDotsAmount_Jmp = 0x005F4C56;
static unsigned long UpgBHEDotsAmount_JmpBack = UpgBHEDotsAmount_Jmp + 6;
__declspec(naked) void inline UpgBHEDotsAmount()
{
    __asm push 124;
    __asm push[esi + 0x0000051];
    __asm mov eax, 0x0040186B;
    __asm call eax;
    __asm test ax, ax;
    __asm jz originalcode;
    __asm mov[ebp + 0x18], 0x32;

    __asm originalcode:;
    __asm fild dword ptr[ebp + 0x18];
    __asm mov eax, [ebp + 0x18];
    __asm mov edx, [ebp - 0x4];
    __asm mov ecx, esi;

    __asm jmp[UpgBHEDotsAmount_JmpBack];
}

static unsigned long UpgRepairSpeed_Jmp = 0x004E238E;
static unsigned long UpgRepairSpeed_JmpBack = UpgRepairSpeed_Jmp + 5;
__declspec(naked) void inline UpgRepairSpeed()
{
    __asm push ecx;
    __asm push 32;
    __asm push[ebx + 0x24];
    __asm mov eax, 0x0040186B;
    __asm call eax;
    __asm test ax, ax;
    __asm pop ecx;
    __asm ja originalcode;

    __asm push ecx;
    __asm push 139;
    __asm push[ebx + 0x24];
    __asm mov eax, 0x0040186B;
    __asm call eax;
    __asm test ax, ax;
    __asm pop ecx;
    __asm ja originalcode;
    __asm add ecx, ecx;

    __asm originalcode:;
    __asm mov eax, 0x51EB851F;

    __asm jmp[UpgRepairSpeed_JmpBack];
}

static unsigned long UpgRepairSpeed2_Jmp = 0x004E2418;
static unsigned long UpgRepairSpeed2_JmpBack = UpgRepairSpeed2_Jmp + 7;
__declspec(naked) void inline UpgRepairSpeed2()
{
    __asm mov edi, [ecx * 4 + 0x007E091C];
    __asm push eax;
    __asm push 32;
    __asm push[ebx + 0x24];
    __asm mov eax, 0x0040186B;
    __asm call eax;
    __asm test ax, ax;
    __asm pop eax;
    __asm ja originalcode;

    __asm push eax;
    __asm push 139;
    __asm push[ebx + 0x24];
    __asm mov eax, 0x0040186B;
    __asm call eax;
    __asm test ax, ax;
    __asm pop eax;
    __asm ja originalcode;
    __asm add edi, edi;

    __asm originalcode:;
    __asm xor edx, edx;
    __asm div edi;
    
    __asm jmp[UpgRepairSpeed2_JmpBack];
}

static unsigned long UpgRepairSpeedPlatf_Jmp = 0x00475109;
static unsigned long UpgRepairSpeedPlatf_JmpBack = UpgRepairSpeedPlatf_Jmp + 5;
__declspec(naked) void inline UpgRepairSpeedPlatf()
{
    __asm push ecx;
    __asm push 32;
    __asm push[esi + 0x24];
    __asm mov eax, 0x0040186B;
    __asm call eax;
    __asm test ax, ax;
    __asm pop ecx;
    __asm ja originalcode;

    __asm push ecx;
    __asm push 139;
    __asm push[esi + 0x24];
    __asm mov eax, 0x0040186B;
    __asm call eax;
    __asm test ax, ax;
    __asm pop ecx;
    __asm ja originalcode;
    __asm mov edi, 8;
    __asm jmp exitt

        __asm originalcode:;
    __asm mov edi, 5;

    __asm exitt:;
    __asm xor edx, edx;
    __asm jmp[UpgRepairSpeedPlatf_JmpBack];
}

static unsigned long TargetingNoHpPriority_Jmp = 0x00489BE1;
static unsigned long TargetingNoHpPriority_JmpBack = TargetingNoHpPriority_Jmp + 9;
__declspec(naked) void inline TargetingNoHpPriority()
{
    __asm {
        xor eax, eax
        mov ecx, [ebp - 4] 
        mov edx, [esi + 0x48B]
        jmp[TargetingNoHpPriority_JmpBack]
    }
}

static unsigned long GoldForHumansOnly_Jmp = 0x004D86FD;
static unsigned long GoldForHumansOnly_JmpBack = GoldForHumansOnly_Jmp + 7;
__declspec(naked) void inline GoldForHumansOnly()
{
    __asm {
        mov edi,[esi*4+0x007BF558]
        mov dword ptr [eax+0x007F4E3F],edi
        mov esi,[esi*4+0x007BF57C]
        jmp[GoldForHumansOnly_JmpBack]
    }
}

static unsigned long OrbitalLaserFasterBuild_Jmp = 0x004D8F9E;
static unsigned long OrbitalLaserFasterBuild_JmpBack = OrbitalLaserFasterBuild_Jmp + 5;
__declspec(naked) void inline OrbitalLaserFasterBuild()
{
    __asm {
        push eax
        mov eax,[ecx+0x4F0]
        test eax,eax
        jz buildsat
        jmp originalcode

        buildsat:
        add esi,25
        cmp edx,esi
        jmp exitt

        originalcode:
        add esi,0x32
        cmp edx,esi

        exitt:
        pop eax
        jmp[OrbitalLaserFasterBuild_JmpBack]
    }
}

static unsigned long FOWConstruction_Jmp = 0x004C6598;
static unsigned long FOWConstruction_JmpBack = FOWConstruction_Jmp + 5;
__declspec(naked) void inline FOWConstruction()
{
    __asm mov ebx, [ebp - 0x1C];
    __asm jmp[FOWConstruction_JmpBack];
}

static unsigned long RecycleSiliconHalfCoeff_Jmp = 0x004B7E92;
static unsigned long RecycleSiliconHalfCoeff_JmpBack = RecycleSiliconHalfCoeff_Jmp + 7;
__declspec(naked) void inline RecycleSiliconHalfCoeff()
{
    __asm mov esi, [eax * 4 + 0x007E09DC];
    __asm sar esi, 1;
    __asm jmp[RecycleSiliconHalfCoeff_JmpBack]
}

static unsigned long RecycleMetalContainerQuarterCoeff_Jmp = 0x004B7E5B;
static unsigned long RecycleMetalContainerQuarterCoeff_JmpBack =
    RecycleMetalContainerQuarterCoeff_Jmp + 5;
__declspec(naked) void inline RecycleMetalContainerQuarterCoeff()
{
    __asm mov edi, [ebp + 10];
    __asm shr edi, 2;
    __asm mov eax, 0x004B7E99;
    __asm jmp eax;
    __asm jmp[RecycleMetalContainerQuarterCoeff_JmpBack]
}

static unsigned long RecycleContainerCallUpdate_Jmp = 0x004B7EB2;
static unsigned long RecycleContainerCallUpdate_JmpBack = RecycleContainerCallUpdate_Jmp + 5;
__declspec(naked) void inline RecycleContainerCallUpdate()
{
    __asm {
        mov ecx, 0x00404B8D
        call ecx
        mov ecx, 0x007FA174
        //mov ecx, [ecx]
        pop edi
        xor eax,eax
        pop esi
        pop ebp
        jmp[RecycleContainerCallUpdate_JmpBack]
    }
}

static unsigned long RecycleContainerPushPlayer_Jmp = 0x004B7E99;
static unsigned long RecycleContainerPushPlayer_JmpBack = RecycleContainerPushPlayer_Jmp + 6;
__declspec(naked) void inline RecycleContainerPushPlayer()
{
    __asm {
        mov ecx,[ecx+0x24]
        push ecx
        lea eax,[edx+esi]
        jmp[RecycleContainerPushPlayer_JmpBack]
    }
}

static unsigned long BioassaulterAddMinesResearched_Jmp = 0x00494AEB;
static unsigned long BioassaulterAddMinesResearched_JmpBack = BioassaulterAddMinesResearched_Jmp + 5;
__declspec(naked) void inline BioassaulterAddMinesResearched()
{
    __asm {
        push eax
        push 116
        push[esi + 0x24]
        mov eax, 0x0040186B
        call eax
        test ax, ax
        pop eax
        jbe originalcode
        cmp eax,33
        jne originalcode
        push ecx
        mov ecx,[eax*4+0x007A8D98]
        mov dword ptr [esi+0x7BE], ecx
        pop ecx
    
        originalcode:
        cmp eax,5
        jne exitt
        mov ecx,0x00494AFE
        jmp ecx

        exitt:
        jmp[BioassaulterAddMinesResearched_JmpBack]
    }
}

static unsigned long AcousticMinesCheck_Jmp = 0x004E653F;
static unsigned long AcousticMinesCheck_JmpBack = AcousticMinesCheck_Jmp + 5;
__declspec(naked) void inline AcousticMinesCheck()
{
    __asm {
        cmp ebx,65 //0x41
        jne outt
        cmp ebx,74
        jne outt
        jmp exitt

        outt:
        mov ecx, 0x004E65A4
        jmp ecx

        exitt:
        jmp[AcousticMinesCheck_JmpBack]
    }
}

static unsigned long CasseteShellExpl3CellsB4Target_Jmp = 0x00641930;
static unsigned long CasseteShellExpl3CellsB4Target_JmpBack = CasseteShellExpl3CellsB4Target_Jmp +
                                                              6;
__declspec(naked) void inline CasseteShellExpl3CellsB4Target()
{
    __asm {
        push eax
        push ecx
        push edx
        movsx eax,word ptr [ebx+0x3E]
        push eax
        movsx ecx,word ptr [ebx+0x3C]
        push ecx
        movsx edx,word ptr [ebx+0x3A]
        push edx
        movsx eax,word ptr [ebx+0x38]
        push eax
        movsx ecx,word ptr [ebx+0x36]
        push ecx
        movsx edx,word ptr [ebx+0x34]
        push edx
        mov eax, 0x006ACF0D
        call eax
        pop edx
        pop edx
        pop edx
        pop edx
        pop edx
        pop edx

        pop edx
        sub eax,edx
        mov edx,601
        cmp edx,eax
        pop ecx
        pop eax
        jmp[CasseteShellExpl3CellsB4Target_JmpBack]
    }
}

static unsigned long CasseteShellExplMidWay_Jmp = 0x00641930;
static unsigned long CasseteShellExplMidWay_JmpBack = CasseteShellExplMidWay_Jmp + 6;
__declspec(naked) void inline CasseteShellExplMidWay()
{
    __asm {
        push eax
        push ecx
        push edx
        movsx eax,word ptr [ebx+0x3E]
        push eax
        movsx ecx,word ptr [ebx+0x3C]
        push ecx
        movsx edx,word ptr [ebx+0x3A]
        push edx
        movsx eax,word ptr [ebx+0x38]
        push eax
        movsx ecx,word ptr [ebx+0x36]
        push ecx
        movsx edx,word ptr [ebx+0x34]
        push edx
        mov eax, 0x006ACF0D
        call eax
        pop edx
        pop edx
        pop edx
        pop edx
        pop edx
        pop edx

        xor edx, edx
        mov ecx, 2
        div ecx
        pop edx
        cmp edx,eax
        pop ecx
        pop eax
        jmp[CasseteShellExplMidWay_JmpBack]
    }
}

static unsigned long CyberNoArmor_Jmp = 0x00459E77;
static unsigned long CyberNoArmor_JmpBack = CyberNoArmor_Jmp + 5;
__declspec(naked) void inline CyberNoArmor()
{
    __asm {
        mov eax, 0x0040186B
        call eax
        push ecx
        mov ecx,[ebx+0x6F7]
        cmp ecx,9
        je cyber
        cmp ecx,15
        je cyber
        jmp exitt

        cyber:
        xor eax, eax

        exitt:
        pop ecx
        jmp[CyberNoArmor_JmpBack]
    }
}

static unsigned long PSGDamageReductionFix_Jmp = 0x004BB42A;
__declspec(naked) void inline PSGDamageReductionFix()
{
    __asm {
        mov eax,[ebp-0x58]
        sub eax,ecx
        mov ecx,eax

        mov dword ptr [ebp-0x58],ecx
        mov eax, 0x004BB432
        jmp eax
    }
}

static unsigned long SplinterTorpedoRangex201_Jmp = 0x00641A92;
static unsigned long SplinterTorpedoRangex201_JmpBack = SplinterTorpedoRangex201_Jmp + 8;
__declspec(naked) void inline SplinterTorpedoRangex201()
{
    __asm {
        push 201
        push ebx
        mov eax, 0x00403116
        call eax
        jmp[SplinterTorpedoRangex201_JmpBack]
    }
}

static unsigned long SplinterTorpedoFixCalc_Jmp = 0x0057BA86;
static unsigned long SplinterTorpedoFixCalc_JmpBack = SplinterTorpedoFixCalc_Jmp + 6;
__declspec(naked) void inline SplinterTorpedoFixCalc()
{
    __asm {
        push edx
        push ebx
        mov eax, 0x028C1979
        imul ecx
        sar edx,1
        mov ecx,edx
        shr ecx,0x1F
        lea ecx,[edx+ecx]

        pop ebx
        mov eax,0x028C1979
        imul ebx
        sar edx,1
        mov eax,edx
        shr eax,0x1F
        lea ebx,[edx+eax]

        pop edx
        mov eax,0x028C1979
        imul edx
        sar edx,1
        mov eax,edx
        shr eax,0x1F
        lea edx,[edx+eax]

        mov eax,ecx
        lea ecx,[ecx+edi+1]
        jmp[SplinterTorpedoFixCalc_JmpBack]
    }
}

static unsigned long SplinterTorpedoAoEDamageCheckLvl_Jmp = 0x0057BB98;
static unsigned long SplinterTorpedoAoEDamageCheckLvl_JmpBack = SplinterTorpedoAoEDamageCheckLvl_Jmp + 5;
__declspec(naked) void inline SplinterTorpedoAoEDamageCheckLvl()
{
    __asm {
        push edx
        push ecx
        push 149
        push [esi+0x24]
        mov eax, 0x0040186B
        call eax
        test ax, ax
        mov eax,[eax*4+0x007E6620]
        shr eax,1
        pop ecx
        pop edx
        jmp[SplinterTorpedoAoEDamageCheckLvl_JmpBack]
    }
}

static unsigned long ChangeSubsRange_Jmp = 0x0044F7F7;
static unsigned long ChangeSubsRange_JmpBack = ChangeSubsRange_Jmp + 7;
__declspec(naked) void inline ChangeSubsRange()
{
    __asm {
        push eax
        mov eax,[ebx+1783]
        cmp eax,2 //6
        je range_6
        cmp eax,4
        je range_6
        cmp eax,5
        je range_6
        cmp eax,6
        je range_6
        cmp eax,11
        je range_6
        cmp eax,38
        je range_6
        cmp eax,13
        je range_6
        cmp eax,17
        je range_6
        cmp eax,18
        je range_6
        cmp eax,23
        je range_6
        cmp eax,39
        je range_6
        cmp eax,32
        je range_6
        cmp eax,33
        je range_6
        cmp eax,28
        je range_6

        cmp eax,3 // 5
        je outt
        cmp eax,10
        je outt
        cmp eax,15
        je outt
        cmp eax,16
        je outt
        cmp eax,22
        je outt
        cmp eax,31
        je outt
        
        //range_7:
        mov WORD PTR [ebx+0x814], 0x57F
        mov WORD PTR [ebx+0x816], 7
        jmp outt

        range_6:
        mov WORD PTR [ebx+0x814], 0x4B6
        mov WORD PTR [ebx+0x816], 6

        outt:
        //mov byte ptr [ebx+1129],0 //dodge distance
        pop eax
        jmp dword ptr [eax*4+0x0045B044]
    }
}

//static unsigned long ChangeSubsRange_Jmp = 0x0044F7F7;
//static unsigned long ChangeSubsRange_JmpBack = ChangeSubsRange_Jmp + 7;
//__declspec(naked) void inline ChangeSubsRange()
//{
//    __asm {
//        push eax
//        mov eax,[ebx+1783]
//        cmp eax,1 //6
//        je range_6
//        cmp eax,3
//        je range_6
//        cmp eax,13
//        je range_6
//        cmp eax,38
//        je range_6
//        cmp eax,14
//        je range_6
//        cmp eax,18
//        je range_6
//        cmp eax,23
//        je range_6
//        cmp eax,30
//        je range_6
//        cmp eax,32
//        je range_6
//        cmp eax,28
//        je range_6
//        cmp eax,33
//        je range_6
//        cmp eax,39
//        je range_6
//
//        cmp eax,31 // 5
//        je outt
//        cmp eax,22
//        je outt
//        cmp eax,15
//        je outt
//        cmp eax,16
//        je outt
//        cmp eax,10
//        je outt
//        
//        //range_7:
//        mov WORD PTR [ebx+0x814], 0x57F
//        mov WORD PTR [ebx+0x816], 7
//        jmp outt
//
//        range_6:
//        mov WORD PTR [ebx+0x814], 0x4B6
//        mov WORD PTR [ebx+0x816], 6
//
//        outt:
//        pop eax
//        jmp dword ptr [eax*4+0x0045B044]
//    }
//}

static unsigned long BOFlagshipRange6_Jmp = 0x0044F94A;
static unsigned long BOFlagshipRange6_JmpBack = BOFlagshipRange6_Jmp + 5;
__declspec(naked) void inline BOFlagshipRange6()
{
    __asm {
        mov eax,0x180
        mov WORD PTR [ebx+0x814], 0x4B6
        mov WORD PTR [ebx+0x816], 6
        jmp[BOFlagshipRange6_JmpBack]
    }
}

static unsigned long SIFlagshipRange7_Jmp = 0x0044F951;
static unsigned long SIFlagshipRange7_JmpBack = SIFlagshipRange7_Jmp + 5;
__declspec(naked) void inline SIFlagshipRange7()
{
    __asm {
        mov eax,0x1DF
        mov WORD PTR [ebx+0x814], 0x57F
        mov WORD PTR [ebx+0x816], 7
        jmp[SIFlagshipRange7_JmpBack]
    }
}

static unsigned long MediumTorpedoOnlyAoE_Jmp = 0x006412F0;
static unsigned long MediumTorpedoOnlyAoE_JmpBack = MediumTorpedoOnlyAoE_Jmp + 7;
__declspec(naked) void inline MediumTorpedoOnlyAoE()
{
    __asm {
        push edx
        mov byte ptr [ebx+0x00000288], 2
        mov dword ptr [ebx+0x00000270], 0
        movsx edx, word ptr [ebx+0x00000045]
        push edx
        movsx eax,word ptr [ebx+0x43]
        movsx ecx,word ptr [ebx+0x41]
        mov edx,[ebx+0x000001ED]
        push eax
        push ecx
        push 5
        push edx
        mov eax, 0x004033B4
        call eax
        add esp,0x14
        pop edx
        jmp[MediumTorpedoOnlyAoE_JmpBack]
    }
}

static unsigned long NoPlatformLoadFlagships_Jmp = 0x0049194A;
static unsigned long NoPlatformLoadFlagships_JmpBack = NoPlatformLoadFlagships_Jmp + 5;
__declspec(naked) void inline NoPlatformLoadFlagships()
{
    __asm {
        cmp eax,38
        je outt
        cmp eax,39
        je outt
        cmp eax,40
        je outt
        jmp originalcode

        outt:
        mov ecx, 0x00491967
        jmp ecx

        originalcode:
        cmp eax,15
        je outt
        jmp[NoPlatformLoadFlagships_JmpBack]
    }
}

static unsigned long AltRMBForLineFormation_Jmp = 0x00547239;
static unsigned long AltRMBForLineFormation_JmpBack = AltRMBForLineFormation_Jmp + 5;
__declspec(naked) void inline AltRMBForLineFormation()
{
    __asm {
        push ecx
        push edx
        push 0x12
        mov eax, 0x0085BDF0
        call dword ptr [eax]
        and eax,0x8000
        test eax,eax
        pop edx
        pop ecx
        jnz alt_pressed

        originalcode:
        mov eax, [0x00808784]
        mov eax, [eax]
        jmp exitt

        alt_pressed:
        push 1
        mov ecx,[0x00802A30]
        mov ecx,[ecx]
        push 0x4E
        mov eax, 0x004035AD
        call eax
        jmp originalcode

        exitt:
        jmp[AltRMBForLineFormation_JmpBack]
    }
}

static unsigned long AltRMBNoDoubleOrder_Jmp = 0x0071BE6B;
static unsigned long AltRMBNoDoubleOrder_JmpBack = AltRMBNoDoubleOrder_Jmp + 7;
__declspec(naked) void inline AltRMBNoDoubleOrder()
{
    __asm {
        push eax
        push ecx
        push edx
        push 0x12
        mov eax, 0x0085BDF0
        call dword ptr [eax]
        and eax,0x8000
        test eax,eax
        pop edx
        pop ecx
        jnz alt_pressed

        mov dword ptr [ebp-0x20],99
        jmp exitt

        alt_pressed:
        mov dword ptr [ebp-0x20],0x0000A50D

        exitt:
        pop eax
        jmp[AltRMBNoDoubleOrder_JmpBack]
    }
}

static unsigned long BoxCursorLoadCheck1_Jmp = 0x004855DC;
static unsigned long BoxCursorLoadCheck1_JmpBack = BoxCursorLoadCheck1_Jmp + 5;
__declspec(naked) void inline BoxCursorLoadCheck1()
{
    __asm {
        cmp eax,0x000001A4
        je outt
        jmp originalcode

        outt:
        mov eax, 0x004855F0
        jmp eax

        originalcode:
        cmp eax,0x000001AE
        jmp[BoxCursorLoadCheck1_JmpBack]
    }
}

static unsigned long BoxCursorLoadCheck2_Jmp = 0x0048603F;
static unsigned long BoxCursorLoadCheck2_JmpBack = BoxCursorLoadCheck2_Jmp + 10;
__declspec(naked) void inline BoxCursorLoadCheck2()
{
    __asm {
        cmp dword ptr [edi+0x20],0x1A4
        je exitt

        cmp dword ptr [edi+0x20],0x14
        je exitt
        mov eax, 0x00485CAA
        jmp eax

        exitt:
        jmp[BoxCursorLoadCheck2_JmpBack]
    }
}

static unsigned long AlwaysShowHP_Jmp = 0x0041F3BA;
static unsigned long AlwaysShowHP_JmpBack = AlwaysShowHP_Jmp + 9;
__declspec(naked) void inline AlwaysShowHP()
{
    __asm {
        cmp eax,-1
        jne exitt
        mov eax,2
        mov dword ptr [esi+0x221],2

        exitt:
        jmp[AlwaysShowHP_JmpBack]
    }
}

static unsigned long DecreaseShowHPState_Jmp = 0x0041F521;
static unsigned long DecreaseShowHPState_JmpBack = DecreaseShowHPState_Jmp + 8;
__declspec(naked) void inline DecreaseShowHPState()
{
    __asm {
        pop edi
        mov dword ptr [esi+0x221],eax
        jmp[DecreaseShowHPState_JmpBack]
    }
}

//Shift
static unsigned long SkipStopResetOrderMove_Move_Jmp = 0x004523B4;
static unsigned long SkipStopResetOrderMove_Move_JmpBack =
    SkipStopResetOrderMove_Move_Jmp + 5;
__declspec(naked) void inline SkipStopResetOrderMove_Move()
{
    __asm {
        push eax
        push ecx
        push edx
        push 0x10
        mov eax, 0x0085BDF0
        call dword ptr [eax]
        and eax,0x8000
        test eax,eax
        pop edx
        pop ecx
        pop eax
        jnz shift_pressed
        jmp originalcode

        shift_pressed:
        pop esi
        mov eax,0
        jmp exitt

        originalcode:
        mov eax, 0x00403DF0
        call eax

        exitt:
        jmp[SkipStopResetOrderMove_Move_JmpBack]
    }
}

static unsigned long SkipStopResetOrderIdle_Build_Jmp = 0x00452EF7;
static unsigned long SkipStopResetOrderIdle_Build_JmpBack = SkipStopResetOrderIdle_Build_Jmp + 5;
__declspec(naked) void inline SkipStopResetOrderIdle_Build()
{
    __asm {
        push eax
        push ecx
        push edx
        push 0x10
        mov eax, 0x0085BDF0
        call dword ptr [eax]
        and eax,0x8000
        test eax,eax
        pop edx
        pop ecx
        pop eax
        jnz shift_pressed
        jmp originalcode

        shift_pressed:
        pop esi
        mov eax,0
        jmp exitt

        originalcode:
        mov eax, 0x0040493A
        call eax

        exitt:
        jmp[SkipStopResetOrderIdle_Build_JmpBack]
    }
}

static unsigned long SkipStopResetOrderBuild_Build_Jmp = 0x00452FCF;
static unsigned long SkipStopResetOrderBuild_Build_JmpBack = SkipStopResetOrderBuild_Build_Jmp + 5;
__declspec(naked) void inline SkipStopResetOrderBuild_Build()
{
    __asm {
        push eax
        push ecx
        push edx
        push 0x10
        mov eax, 0x0085BDF0
        call dword ptr [eax]
        and eax,0x8000
        test eax,eax
        pop edx
        pop ecx
        pop eax
        jnz shift_pressed
        jmp originalcode

        shift_pressed:
        cmp [ebx+0x508],2
        je originalcode
        cmp [ebx+0x508],5
        je originalcode
        pop esi
        mov eax,0
        jmp exitt

            // out:
            // pop eax
        originalcode:
        mov eax, 0x00401113
        call eax

        exitt:
        jmp[SkipStopResetOrderBuild_Build_JmpBack]
    }
}

static unsigned long EnableShiftAltInput_Jmp = 0x00731B878;
static unsigned long EnableShiftAltInput_JmpBack = EnableShiftAltInput_Jmp + 5;
__declspec(naked) void inline EnableShiftAltInput()
{
    __asm {
        mov cl,0
        mov edx,esi
        jmp[EnableShiftAltInput_JmpBack]
    }
}

static unsigned long DontEraseOldOrder_jmp = 0x0040AE67;
static unsigned long DontEraseOldOrder_jmpBack = DontEraseOldOrder_jmp + 6;
__declspec(naked) void inline DontEraseOldOrder()
{
    __asm {
        push ecx
        push edx
        push 0x10
        mov eax, 0x0085BDF0
        call dword ptr [eax]
        and eax,0x8000
        test eax,eax
        pop edx
        pop ecx
        jnz shift_pressed

        lea ecx,[esi+0x0000009F]
        jmp exitt

        shift_pressed:
        mov eax, 0x0040AE85
        jmp eax

        exitt:
        jmp[DontEraseOldOrder_jmpBack]
    }
}

static unsigned long AppendOrderInsteadOfReplace_Jmp = 0x0040B7A6;
static unsigned long AppendOrderInsteadOfReplace_JmpBack = AppendOrderInsteadOfReplace_Jmp + 8;
__declspec(naked) void inline AppendOrderInsteadOfReplace()
{
    __asm {
        push eax
        push ecx
        push edx
        push 0x10
        mov eax, 0x0085BDF0
        call dword ptr [eax]
        and eax,0x8000
        test eax,eax
        pop edx
        pop ecx
        pop eax
        jnz shift_pressed
        jmp originalcode

        shift_pressed:
        mov dword ptr [ebx+0xE3],1 /////добавка 27.03.2023 для начала движения в stop_move
        push edx
        mov edx,[ebx+0x0000009F] //взять текущий приказ
        test edx,edx
        jz zero
        push ebx

        go_deeper:
        mov ebx,edx
        mov dword ptr [edx+0xC],0 //флаг отличия момента задания флага нового приказа
        mov edx,[edx+8]
        cmp edx,0xFFFFFFFF
        jne go_deeper
        mov edx,ebx
        pop ebx
        mov dword ptr [edx+8], eax //вложить приказ
        pop edx
        test eax,eax
        jmp exitt

        zero:
        pop edx
        mov dword ptr [ebx+0x0000009F],eax
        test eax,eax
        jmp exit

        originalcode:
        test eax,eax
        jz skip_set_flag
        mov dword ptr [eax+0xC],0 //флаг отличия момента задания флага нового приказа
        skip_set_flag:
        mov dword ptr [ebx+0x0000009F],eax

        exitt:
        jmp[AppendOrderInsteadOfReplace_JmpBack]
    }
}

static unsigned long OrderEndProcedure_Jmp = 0x0045FC06;
static unsigned long OrderEndProcedure_JmpBack = OrderEndProcedure_Jmp + 7;
__declspec(naked) void inline OrderEndProcedure()
{
    __asm {
        xor eax,eax
        mov eax,[esi+0x9F]
        push eax //сохранение старого приказа
        test eax, eax
        jz vanilla
        mov eax,[eax+8] //достать вложенный приказ
        cmp eax,0xFFFFFFFF
        jz vanilla
        cmp [esi+0x508],7
        jne area4
        mov dword ptr [eax+0xC],1
        mov dword ptr [esi+0xA7],0 // travelled
        mov dword ptr [esi+0x9F],eax //замена на вложенный приказ
        mov dword ptr [esi+0x2C4],1 //флаг вложенный приказа
        mov dword ptr [esi+0x30C],1 //флаг приказа строительства
        pop eax //возврат старого приказа
        mov edi,[eax+0x34] //Прочитать дистанцию до приказа из старого приказа
        mov dword ptr [esi+0xA3],edi //Положить её в подлодку
        push esi
        push ecx
        push edi
        lea edi,[esi+0x36F] //задание приёмника
        lea esi,[eax+0x10] //задание источником старого приказа
        mov ecx,0x00000008
        repe movsd
        movsw
        movsb
        pop edi
        pop ecx
        pop esi
        jmp area3

        area4:
        pop eax
        area3:
        cmp dword ptr [esi+0x0000008F],-1
        jne some_area2
        mov dword ptr [esi+0x0000008F],ebx

        some_area2:
        xor eax,eax
        mov ecx,edi
        mov ax,[esi+0x32]
        jmp exitt


        vanilla:
        pop eax
        cmp dword ptr [esi+0x0000008F],-1
        jne some_area
        mov dword ptr [esi+0x0000008F],ebx

        some_area:
        xor eax,eax
        mov ecx,edi
        mov ax,[esi+0x32]
        mov dword ptr [esi+0x000000FD],0x00000001
        push eax
        mov eax, 0x00404FF2
        call eax

        exitt:
        jmp[OrderEndProcedure_JmpBack]
    }
}

static unsigned long NewBuildOrderWithShift_Jmp = 0x0045EFE5;
static unsigned long NewBuildOrderWithShift_JmpBack = NewBuildOrderWithShift_Jmp + 6;
__declspec(naked) void inline NewBuildOrderWithShift()
{
    __asm {
        push eax
        push ecx
        push edx
        push 0x10
        mov eax, 0x0085BDF0
        call dword ptr [eax]
        and eax,0x8000
        test eax,eax
        pop edx
        pop ecx
        pop eax
        jnz shift_pressed
        jmp originalcode

        shift_pressed:
        push eax
        push ebx
        mov eax,[edi+0x9F]
        test eax,eax
        jz vanilla //нет текущего приказа
        go_deeper:
        mov ebx,eax //сохранить ненулевой приказ
        mov eax,[eax+8] //прочитать вложенный приказ
        cmp eax,0xFFFFFFFF
        jne go_deeper
        mov eax,ebx
        mov dword ptr [edi+0x0000030C],esi //флаг нового приказа строительства
        mov esi,[ebp+0x0C]
        mov ecx,0x00000008
        lea edi,[eax+0x10]
        repe movsd
        movsw
        movsb
        pop ebx
        pop eax
        jmp exitt

        vanilla:
        pop ebx
        pop eax

        originalcode:
        mov dword ptr [edi+0x0000030C],esi
        mov esi,[ebp+0x0C]
        mov ecx,0x00000008
        add edi,0x0000036F
        repe movsd
        movsw
        movsb

        exitt:
        jmp[NewBuildOrderWithShift_JmpBack]
    }
}

static unsigned long PtrDistanceToTargetWithShift_Jmp = 0x0040B747;
static unsigned long PtrDistanceToTargetWithShift_JmpBack = PtrDistanceToTargetWithShift_Jmp + 6;
__declspec(naked) void inline PtrDistanceToTargetWithShift()
{
    __asm {
        push eax
        push ecx
        push edx
        push 0x10
        mov eax, 0x0085BDF0
        call dword ptr [eax]
        and eax,0x8000
        test eax,eax
        pop edx
        pop ecx
        pop eax
        jnz shift_pressed
        jmp originalcode

        shift_pressed:
        push eax
        mov eax,[ebx+0x9F]
        test eax,eax
        jz vanilla
        push ecx

        go_deeper:
        mov ecx,eax
        mov eax,[eax+8]
        cmp eax,0xFFFFFFFF
        jne go_deeper
        mov eax,ecx
        pop ecx
        lea ecx,[eax+0x34]
        pop eax
        jmp exitt

        vanilla:
        pop eax
        originalcode:
        lea ecx,[ebx+0x000000A3]

        exitt:
        jmp[PtrDistanceToTargetWithShift_JmpBack]
    }
}

static unsigned long DontResetOrderWhenChanged_Jmp = 0x0046BF9B;
static unsigned long DontResetOrderWhenChanged_JmpBack = DontResetOrderWhenChanged_Jmp + 8;
__declspec(naked) void inline DontResetOrderWhenChanged()
{
    __asm {
        push eax
        mov eax,[esi+0x9F]
        test eax,eax
        jz originalcode
        mov ebx,1

        originalcode:
        pop eax
        push ebx
        mov ecx,esi
        mov eax, 0x00403B34
        call dword ptr [eax]
        jmp[DontResetOrderWhenChanged_JmpBack]
    }
}

static unsigned long DontResetOrderWhenChanged2x2_Jmp = 0x0046BF9B;
static unsigned long DontResetOrderWhenChanged2x2_JmpBack = DontResetOrderWhenChanged2x2_Jmp + 9;
__declspec(naked) void inline DontResetOrderWhenChanged2x2()
{
    __asm {
        push eax
        mov eax,[esi+0x9F]
        test eax,eax
        jz originalcode
        mov ebx,1

        originalcode:
        pop eax
        push ebx
        mov ecx,esi
        mov eax, 0x00403B34
        call dword ptr [eax]
        jmp[DontResetOrderWhenChanged2x2_JmpBack]
    }
}

static unsigned long ReplaceSubGpsToOrderWithShift_Jmp = 0x0040B777;
static unsigned long ReplaceSubGpsToOrderWithShift_JmpBack = ReplaceSubGpsToOrderWithShift_Jmp + 8;
__declspec(naked) void inline ReplaceSubGpsToOrderWithShift()
{
    __asm {
        push eax
        push ecx
        push edx
        push 0x10
        mov eax, 0x0085BDF0
        call dword ptr [eax]
        and eax,0x8000
        test eax,eax
        pop edx
        pop ecx
        pop eax
        jnz shift_pressed
        jmp originalcode

        shift_pressed:
        push edi
        mov edi,[ebx+0x9F]
        test edi,edi
        jz outt
        push esi
        push edx
        xor edx,edx //установить счётчик глубины на 0
        go_deeper:
        inc edx
        mov esi,edi
        mov edi,[edi+8]
        cmp edi,0xFFFFFFFF
        jne go_deeper
        mov edi,esi //вернуть последний вложенный существующий приказ
        cmp edx, 1
        ja deep
        pop edx
                    //ТОЛЬКО 1 ВЛОЖЕННЫЙ ПРИКАЗ
        movsx ecx,word ptr [ebx+0xC3]
                // inc ecx
        movsx edx,word ptr [ebx+0xBF]
        movsx eax,word ptr [ebx+0xBB]
                // movsx ecx,word ptr [edi+18]
                // inc ecx
                // movsx edx,word ptr [edi+16]
                // movsx eax,word ptr [edi+14]
        pop esi
        pop edi
        jmp exitt

        deep:
                    //ДОСТАТЬ КООРДИНАТЫ ЛОДКИ В БУДУЩЕМ ИЗ ПРИКАЗА
        mov esi,[ebx+0x9F] //Взять первый приказ
        dec edx
        cmp edx,1
        je get_gps
        unwrap:
        mov esi,[esi+8]
        dec edx
        cmp edx,1
        ja unwrap

        get_gps:
        movsx ecx,word ptr [esi+0x18]
        inc ecx
        pop edx
        xor edx,edx
        movsx edx,word ptr [esi+0x16]
        movsx eax,word ptr [esi+0x14]
        pop esi
        jmp out2

        outt:
        pop edi
        originalcode:
        movsx edx,word ptr [ebx+0x49]
        movsx eax,word ptr [ebx+0x47]
        jmp exitt

        out2:
        pop edi

        exitt:
        jmp[ReplaceSubGpsToOrderWithShift_JmpBack]
    }
}

static unsigned long ReplaceOrderGpsToOrderWithShift_Jmp = 0x0040B771;
static unsigned long ReplaceOrderGpsToOrderWithShift_JmpBack = ReplaceOrderGpsToOrderWithShift_Jmp + 5;
__declspec(naked) void inline ReplaceOrderGpsToOrderWithShift()
{
    __asm {
        pop ecx
        push eax
        push ecx
        push edx
        push 0x10
        mov eax, 0x0085BDF0
        call dword ptr [eax]
        and eax,0x8000
        test eax,eax
        pop edx
        pop ecx
        pop eax
        jnz shift_pressed
        jmp originalcode

        shift_pressed:
        push edi
        mov edi,[ebx+0x9F]
        test edi,edi
        jz no_order

        push edx
        go_deeper:
        mov edx,edi
        mov edi,[edi+8]
        cmp edi,0xFFFFFFFF
        jne go_deeper
        mov edi,edx //вернуть последний вложенный существующий приказ
        pop edx

        movsx ecx,word ptr [edi+0x18]
        inc ecx
                    //проверка 6 высоты
        cmp ecx,5
        jbe next
        dec ecx
        next:
                    //
        movsx edx,word ptr [edi+0x16]
        movsx eax,word ptr [edi+0x14]
        pop edi
        jmp originalcode

        no_order:
        pop edi

        originalcode:
        push ecx
        movsx ecx,word ptr [ebx+0x4B]
        push edx

        jmp[ReplaceOrderGpsToOrderWithShift_JmpBack]
    }
}

static unsigned long AlwaysJumpToRightOrderCreation_Jmp = 0x0040AFA0;
__declspec(naked) void inline AlwaysJumpToRightOrderCreation()
{
    __asm {
        mov ecx, 0x0040B56A
        jmp ecx
    }
}

static unsigned long DontDestroyOrderObjects_Jmp = 0x0045FE54;
static unsigned long DontDestroyOrderObjects_JmpBack = DontDestroyOrderObjects_Jmp + 5;
__declspec(naked) void inline DontDestroyOrderObjects()
{
    __asm {
        push eax
        push ecx
        push edx
        push 0x10
        mov eax, 0x0085BDF0
        call dword ptr [eax]
        and eax,0x8000
        test eax,eax
        pop edx
        pop ecx
        pop eax
        jnz shift_pressed
        jmp originalcode

        shift_pressed:
        push edi
        mov edi,[ebx+0x9F]
        test edi,edi
        jz no_order
        pop edi
        jmp exitt


        no_order:
        pop edi
        originalcode:
        mov eax, 0x00405952
        call eax
        xor ecx,ecx
        mov dword ptr [esi+0x000000FD],00000001
        mov cx,[esi+0x32]
        push ecx
        mov ecx,ebx
        mov eax, 0x00404FF2
        call eax

        exitt:
        jmp[DontDestroyOrderObjects_JmpBack]
    }
}

static unsigned long AfterCheckOrderStateReturns2_Jmp = 0x0045FFCB;
static unsigned long AfterCheckOrderStateReturns2_JmpBack = AfterCheckOrderStateReturns2_Jmp + 7;
__declspec(naked) void inline AfterCheckOrderStateReturns2()
{
    __asm {
        // inc word ptr [esi+000000FA]
        mov word ptr [esi+0x000000FA],0
        jmp[AfterCheckOrderStateReturns2_JmpBack]
    }
}

static unsigned long AutosaveCheckTick_Jmp = 0x00533DB6;
static unsigned long AutosaveCheckTick_JmpBack = AutosaveCheckTick_Jmp + 5;
__declspec(naked) void inline AutosaveCheckTick()
{
    __asm {
        // взять тик
        push eax
        push ebx
        push edx
        
        call[AutosaveCheck]
        test eax, eax
        jz go_out

        xor edx,edx
        mov eax,0x802A38
        mov eax,[eax]
        mov eax,[eax+0xE4]
        test eax, eax
        jz go_out
        mov ebx,1500
        div ebx // В eax - результат деления
        cmp dx,0
        jnz go_out
                     // Тик сохранения
        pop edx
        pop ebx

                // Проверка одинаковости тика
        push ecx
        mov ecx,[ebx+0x201]       // 501+12 (tick name part)
        sub ecx,0x30

        push ebx
        push edx
        xor edx,edx
        mov ebx,2
        div ebx
        cmp ecx,edx
        pop edx
        pop ebx
        pop ecx
        pop eax
        je originalcode
                            // Новое сохранение
        mov eax,0xC0A1
        jmp originalcode

        go_out:
        pop edx
        pop ebx
        pop eax

        originalcode:
        cmp eax,0x0000C006

        jmp[AutosaveCheckTick_JmpBack]
    }
}

static unsigned long AutosaveCheckMarker_Jmp = 0x005353B4;
static unsigned long AutosaveCheckMarker_JmpBack = AutosaveCheckMarker_Jmp + 8;
__declspec(naked) void inline AutosaveCheckMarker()
{
    __asm {
                // взять тик
        push eax
        push ebx
        push edx
        
        call[AutosaveCheck]
        test eax, eax
        jz go_out

        xor edx,edx
        mov eax,0x802A38
        mov eax,[eax]
        mov eax,[eax+0xE4]
        test eax, eax
        jz go_out
        mov ebx,1500
        div ebx // В eax - результат деления
        cmp dx,0
        pop edx
        pop ebx
        pop eax
        jnz originalcode
        mov eax,3
        jmp originalcode
        
        go_out:
        pop edx
        pop ebx
        pop eax

        originalcode:
        mov edx,eax
        and edx,0x000000FF

        jmp[AutosaveCheckMarker_JmpBack]
    }
}

static unsigned long AutosaveMakeFileName_Jmp = 0x00535513;
static unsigned long AutosaveMakeFileName_JmpBack = AutosaveMakeFileName_Jmp + 5;
__declspec(naked) void inline AutosaveMakeFileName()
{
    __asm {
            // взять тик
        mov eax,[eax+0x14]
        mov edi,[eax]
        
        call[AutosaveCheck]
        test eax, eax
        jz exitt

        push ebx
        push edx
        xor edx,edx
        mov eax,0x802A38
        mov eax,[eax]
        mov eax,[eax+0xE4]
        mov ebx,1500
        div ebx //В eax - результат деления
        cmp dx,0
        jnz originalcode
            //название файла MP_Q UICK SAVE NNNN
        mov dword ptr [edi],0x515F504D
        mov dword ptr [edi+4],0x4B434955
        mov dword ptr [edi+8],0x45564153

        mov ebx,2
        div ebx
        add edx,0x30
        mov word ptr [edi+0xC],dx  // Записать чётный/нечётный результат деления
            //символ конца строки
            // mov byte ptr [edi+D],0

        originalcode:
        pop edx
        pop ebx
            // mov eax,[eax+14]
            // mov edi,[eax]

        exitt:
        jmp[AutosaveMakeFileName_JmpBack]
    }
}

static unsigned long AutosaveFillNameBuffer_Jmp = 0x0053552D;
static unsigned long AutosaveFillNameBuffer_JmpBack = AutosaveFillNameBuffer_Jmp + 6;
__declspec(naked) void inline AutosaveFillNameBuffer()
{
    __asm {
        call[AutosaveCheck]
        test eax, eax
        jz originalcode

        push ebx
        push edx
        xor edx,edx
        mov eax,0x802A38
        mov eax,[eax]
        mov eax,[eax+0xE4]
        mov ebx,1500
        div ebx //В eax - результат деления
        cmp dx,0
        jnz go_out

        pop edx
        push eax
        mov eax,[edx]
        test eax, eax
        pop eax
        jnz go_out2
                     // pop edx
            //название файла MP_Q UICK SAVE NNNN
        mov dword ptr [edi],0x515F504D
        mov dword ptr [edi+4],0x4B434955
        mov dword ptr [edi+8],0x45564153

        push edx
        xor edx,edx
        mov ebx,2
        div ebx
        add edx,0x30
        mov ax,dx
        pop edx
        mov word ptr [edx+0xC],ax // Записать чётный/нечётный результат деления
        pop ebx
        jmp originalcode

        go_out:
        pop edx
        go_out2:
        pop ebx

        originalcode:
        mov eax,ecx
        mov esi,edi
        mov edi,edx

        jmp[AutosaveFillNameBuffer_JmpBack]
    }
}

static unsigned long AutosaveDontCheckIfFileExists_Jmp = 0x005355BD;
static unsigned long AutosaveDontCheckIfFileExists_JmpBack = AutosaveDontCheckIfFileExists_Jmp + 5;
__declspec(naked) void inline AutosaveDontCheckIfFileExists()
{
    __asm {
        push eax
        push ebx
        push edx
        
        call[AutosaveCheck]
        test eax, eax
        jz go_out

        xor edx,edx
        mov eax,0x802A38
        mov eax,[eax]
        mov eax,[eax+0xE4]
        test eax, eax
        jz go_out
        mov ebx,1500
        div ebx //В eax - результат деления
        cmp dx,0
        jnz go_out

            //Пропуск проверки
        pop edx
        pop ebx
        pop eax
        pop edx

        mov eax, 0
        jmp exitt

        go_out:
        pop edx
        pop ebx
        pop eax

        mov eax, 0x00402874
        call eax

        exitt:
        jmp[AutosaveDontCheckIfFileExists_JmpBack]
    }
}

//static unsigned long AutosaveDontCheckIfFileExists_Jmp = 0x005355BD;
//static unsigned long AutosaveDontCheckIfFileExists_JmpBack = AutosaveDontCheckIfFileExists_Jmp + 5;
//__declspec(naked) void inline AutosaveDontCheckIfFileExists()
//{
//    __asm {
//        push eax
//        push ebx
//        push edx
//        
//        call[AutosaveCheck]
//        test eax, eax
//        jz go_out
//
//        xor edx,edx
//        mov eax,0x802A38
//        mov eax,[eax]
//        mov eax,[eax+0xE4]
//        test eax, eax
//        jz go_out
//        mov ebx,1500
//        div ebx //В eax - результат деления
//        cmp dx,0
//        jnz go_out
//
//            //Пропуск проверки
//        pop edx
//        pop ebx
//        pop eax
//                // pop edx
//
//        push edx
//        push ebx
//        push eax
//
//        mov al,[ebx+0x000001A4]
//        push 00
//        push 00
//        push 00
//        push 00
//        push 00
//        push 00
//        push 0x0000C0B1
//        push 0x0000C0A1
//        cmp al,0xE
//        push 00
//        push 0x007C3894
//        je exitt
//        mov eax, 0x0040577C
//        call eax
//        add esp,8
//        mov ecx,ebx
//        push eax
//        push 1
//        push 0x7C
//        push 0x5D
//        push 0x01
//        push 00
//        mov eax, 0x0040398B
//        call eax
//        push 00
//        push 00
//        push 00
//        push 00
//        push 00
//        push 00
//        push 0x0000C0B2
//        push 0x0000C0A2
//        push 00
//        push 0x007C3894
//        mov [ebx+0x000001BD],eax
//        mov eax, 0x0040577C
//        call eax
//        add esp,8
//        mov ecx,ebx
//        push eax
//        push 1
//        push 0x7C
//        push 0x00000094
//        push 1
//        push 0
//        mov eax, 0x0040398B
//        call eax
//        mov [ebx+0x000001C1],eax
//        mov eax,[ebx+0x000001E1]
//        push eax
//        mov ecx,ebx
//
//        mov eax, 0x00403FBC
//        call eax
//
//        pop eax
//        pop ebx
//        pop edx
//        mov eax, 0x00402874
//        call eax
//
//            // mov eax,0
//        jmp exitt
//
//        go_out:
//        pop edx
//        pop ebx
//        pop eax
//
//        mov eax, 0x00402874
//        call eax
//
//        exitt:
//        jmp[AutosaveDontCheckIfFileExists_JmpBack]
//    }
//}

static unsigned long AutosaveSkipToggleMenu_Jmp = 0x005336BD;
static unsigned long AutosaveSkipToggleMenu_JmpBack = AutosaveSkipToggleMenu_Jmp + 7;
__declspec(naked) void inline AutosaveSkipToggleMenu()
{
    __asm {

        push eax
        push ebx
        push edx
        
        call[AutosaveCheck]
        test eax, eax
        jz go_out

        xor edx,edx
        mov eax,0x802A38
        mov eax,[eax]
        mov eax,[eax+0xE4]
        mov ebx,1500
        div ebx //В eax - результат деления
        cmp dx,0
        pop edx
        pop ebx
        pop eax
        jnz originalcode
        mov dword ptr [edx+0x28],0
        jmp exitt

        go_out:        
        pop edx
        pop ebx
        pop eax

        originalcode:
        mov dword ptr [edx+0x28],0x0000C001

        exitt:
        jmp[AutosaveSkipToggleMenu_JmpBack]
    }
}

static unsigned long SiliconDumpWhenDepleted_Jmp = 0x004E47F9;
static unsigned long SiliconDumpWhenDepleted_JmpBack = SiliconDumpWhenDepleted_Jmp + 6;
__declspec(naked) void inline SiliconDumpWhenDepleted()
{
    __asm {
        mov ecx,ebx
        mov eax, 0x00402C07
        call eax

        mov ecx,[esi+0x10]
        mov eax,[esi+0x24]
        jmp[SiliconDumpWhenDepleted_JmpBack]
    }
}

static unsigned long NoEnergyOverflow_Jmp = 0x004E425B;
static unsigned long NoEnergyOverflow_JmpBack = NoEnergyOverflow_Jmp + 5;
__declspec(naked) void inline NoEnergyOverflow()
{
    __asm {
        push eax
        mov eax,[ebp+0x08]
        push eax
        mov eax, 0x00404390
        call eax

        pop eax
        pop ebp
        ret 8
        nop 
        jmp[NoEnergyOverflow_JmpBack]
    }
}

static unsigned long AvengerNoAttackSpeedUpgrade_Jmp = 0x004507CB;
static unsigned long AvengerNoAttackSpeedUpgrade_JmpBack = AvengerNoAttackSpeedUpgrade_Jmp + 6;
__declspec(naked) void inline AvengerNoAttackSpeedUpgrade()
{
    __asm {
        mov eax, [ebx+0x6F7]
        cmp eax, 0x17
        je exitt

        inc [ebx+0x000007AA]

        exitt:
        jmp[AvengerNoAttackSpeedUpgrade_JmpBack]
    }
}

static unsigned long UpgParcherDmg_Jmp = 0x0061481F;
static unsigned long UpgParcherDmg_JmpBack = UpgParcherDmg_Jmp + 5;
__declspec(naked) void inline UpgParcherDmg()
{
    __asm {
        push 122
        push [eax+4]
        mov eax, 0x0040186B;
        call eax;
        test ax, ax
        jbe originalcode
        sub ax, 1
        test ax, ax
        jbe upgrade1
        mov eax,0x007E6678
        mov eax,[eax]
        jmp exitt

        upgrade1:
        mov eax,0x007E6674
        mov eax,[eax]
        jmp exitt

        originalcode:
        mov eax,0x007E6670
        mov eax,[eax]

        exitt:
        jmp[UpgParcherDmg_JmpBack]
    }
}

static unsigned long IonArmorBlockedDamageHalf_Jmp = 0x00459E32;
static unsigned long IonArmorBlockedDamageHalf_JmpBack = IonArmorBlockedDamageHalf_Jmp + 5;
__declspec(naked) void inline IonArmorBlockedDamageHalf()
{
    __asm {
        shr eax,0x1F
        add edx,eax

        sub ecx,edx
        shr ecx,1

        jmp[IonArmorBlockedDamageHalf_JmpBack]
    }
}

static unsigned long MessageResearchComplete_Jmp = 0x004E6368;
static unsigned long MessageResearchComplete_JmpBack = MessageResearchComplete_Jmp + 6;
__declspec(naked) void inline MessageResearchComplete()
{
    __asm {
        push ebx
        push ecx
        push edi
        push esi
        push eax
        mov al,[ebp+0x08] // player input
        mov edi,0x0080874D
        cmp al,[edi]
        jne no_show

        mov eax,0x0080F33A // global string buffer
        mov dword ptr [eax],0xEBF1F1C8 //Иссл
        mov dword ptr [eax+4],0xE2EEE4E5 //едов
        mov dword ptr [eax+8],0x20EEEDE0 //ано
        mov dword ptr [eax+0xC],0

                // scan start
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi

        cmp ebx,1 //Гидропушка
        jne next2
        mov edi,13000 //Гидропушка
        push edi
        mov edi, 0x006B0140
        call edi                  // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13502 //Новый тип сооружений
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next2:
        cmp ebx,2 //Расширение обзора локатора
        jne next3
        mov edi,13001 //Расширение обзора локатора
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13502 //Новый тип сооружений
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next3:
        cmp ebx,3 //Трансп. ремонтник
        jne next4
        mov edi,13002 //Трансп. ремонтник
        push edi
        mov edi,0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13501 //Новый класс подлодок
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next4:
        cmp ebx,129 //Усиление брони
        je armor
        cmp ebx,4 //Усиление брони
        je armor
        jmp next5
        armor:
        cmp edx,2
        jb lvl1_4
        ja lvl3_4
        mov edi,13004 //Усиление брони ур2
        jmp defined_4
        lvl1_4:
        mov edi,13003 //Усиление брони ур3
        jmp defined_4
        lvl3_4:
        mov edi,13005 //Усиление брони ур4
        defined_4:
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13500 //Усовершенствование подлодок
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next5:
        cmp ebx,130 //Увеличение скорости
        je speed
        cmp ebx,5 //Увеличение скорости
        je speed
        jmp next6
        speed:
        cmp edx,2
        jb lvl1_5
        ja lvl3_5
        mov edi,13007 //Увеличение скорости ур3
        jmp defined_5
        lvl1_5:
        mov edi,13006 //Увеличение скорости ур2
        jmp defined_5
        lvl3_5:
        mov edi,13008 //Увеличение скорости ур4
        defined_5:
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13500 //Усовершенствование подлодок
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next6:
        cmp ebx,131 //Усиление торпед
        je torp_dmg
        cmp ebx,6 //Усиление торпед
        je torp_dmg
        jmp next7_30
        torp_dmg:
        cmp edx,2
        jb lvl1_6
        ja lvl34_6
        mov edi,13010 //ур3
        jmp defined_6
        lvl1_6:
        mov edi,13009 //ур2
        jmp defined_6
        lvl34_6:
        cmp edx,3
        jne lvl4_6
        mov edi,13011 //ур4
        jmp defined_6
        lvl4_6:
        mov edi,13012 //ур5
        defined_6:
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13504 //Усовершенствование оружия
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next7_30:
        cmp ebx,30                                          // N7_30
        ja next31
        cmp ebx,14 //Выше 14: +1
        push ebx
        jbe no_corr_7_30
        inc ebx
        cmp ebx,28
        jb no_corr_7_30
        inc ebx
        no_corr_7_30:
        mov edi,13006
        add edi,ebx
        pop ebx
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        cmp ebx,7
        je nts_7_30
        cmp ebx,12
        je nts_7_30
        cmp ebx,13
        je nts_7_30
        cmp ebx,15
        je nts_7_30
        cmp ebx,17
        je nts_7_30
        cmp ebx,19
        je nts_7_30
        cmp ebx,21
        je nts_7_30
        cmp ebx,22
        je nkp_7_30
        cmp ebx,25
        je nts_7_30
        cmp ebx,26
        je nts_7_30
        cmp ebx,8
        je nkp_7_30
        cmp ebx,9
        je nkp_7_30
        cmp ebx,14
        je nkp_7_30
        cmp ebx,18
        je nkp_7_30
        cmp ebx,20
        je nkp_7_30
        cmp ebx,24
        je nkp_7_30
        cmp ebx,10
        je up_7_30
        cmp ebx,27
        je up_7_30
        cmp ebx,11
        je us_7_30
        cmp ebx,16
        je us_7_30
        cmp ebx,23
        je us_7_30
        cmp ebx,30
        je us_7_30


        nts_7_30:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13502 //Новый тип сооружений
        jmp get_7_30

        nkp_7_30:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13501 //Новый класс подлодок
        jmp get_7_30

        up_7_30:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13500 //Усовершенствование подлодок
        jmp get_7_30

        us_7_30:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13505 //Усовершенствование сооружений

        get_7_30:
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next31:
        cmp ebx,31 //Плазмопушка
        ja next32
        mov edi,13042
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13502 //Новый тип сооружений
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next32:
        cmp ebx,32 //Ускорение ремонта
        ja next33
        mov edi,13040
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13505 //Усовершенствование сооружений
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next33:
        cmp ebx,33 //Ускорение ремонта
        ja next34_49
        mov edi,13041
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13505 //Усовершенствование сооружений
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next34_49:
        cmp ebx,49
        ja next50
        mov edi,13009
        add edi,ebx
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        cmp ebx,34
        jbe nkp_34_49
        cmp ebx,35
        jbe nkp_34_49
        cmp ebx,36
        je up_34_49
        cmp ebx,37
        je nkp_34_49
        cmp ebx,38
        je nts_34_49
        cmp ebx,40
        jbe nkp_34_49
        cmp ebx,43
        jbe nts_34_49
        cmp ebx,44
        je nkp_34_49
        cmp ebx,45
        je up_34_49
        cmp ebx,46
        je nkp_34_49
        cmp ebx,47
        je us_34_49
        jmp nts_34_49

        nts_34_49:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13502 //Новый тип сооружений
        jmp get_34_49

        nkp_34_49:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13501 //Новый класс подлодок
        jmp get_34_49

        up_34_49:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13500 //Усовершенствование подлодок
        jmp get_34_49

        us_34_49:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13505 //Усовершенствование сооружений

        get_34_49:
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next50:
        cmp ebx,50 //Энергетический щит
        ja next51
        mov edi,13034
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13505 //Усовершенствование сооружений
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next51:
        cmp ebx,51 //Лёгкий лазер
        ja next52
        mov edi,13059
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13502 //Новый тип сооружений
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next52:
        cmp ebx,52 //Оборудование рейдера
        ja next53
        mov edi,13164
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13501 //Новый класс подлодок
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next53:
        cmp ebx,53 //Кибер-технология
        ja next54_65
        mov edi,13029
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13501 //Новый класс подлодок
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next54_65:
        cmp ebx,65 //Повыш. дальности лёгкого лазера
        ja next66_67
        cmp ebx,62
        push ebx
        jbe no_corr_54_55
        inc ebx
        no_corr_54_55:
        mov edi,13007
        add edi,ebx
        pop ebx
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        cmp ebx,57
        jbe us_54_65
        cmp ebx,58
        je up_54_65
        cmp ebx,59
        je nts_54_65
        cmp ebx,60
        je up_54_65
        cmp ebx,64
        jbe us_54_65
        jmp up_54_65

        us_54_65:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13505 //Усовершенствование сооружений
        jmp get_54_65

        up_54_65:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13500 //Усовершенствование подлодок
        jmp get_54_65

        nts_54_65:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13502 //Новый тип сооружений

        get_54_65:
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer


        next66_67:
        cmp ebx,67 //Система защиты от СМП
        ja next68_78
        mov edi,13150
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13505 //Усовершенствование сооружений
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer


        next68_78:
        cmp ebx,78 //Повыш. дальности лёгкого лазера
        ja next79
        cmp ebx,78
        jb not_energy_or_lvl2
        cmp edx,2
        jb not_energy_or_lvl2 //ур2
        ja lvl4_78 //ур4
        mov edi,13139 //ур3
        jmp defined_78
        lvl4_78:
        mov edi,13140
        jmp defined_78
        not_energy_or_lvl2:
        mov edi,13006
        add edi,ebx
        defined_78:
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        cmp ebx,68
        je nts_68_78
        cmp ebx,74
        jbe us_68_78
        cmp ebx,76
        jbe up_68_78
        cmp ebx,77
        je us_68_78
        jmp fou_68_78

        us_68_78:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13505 //Усовершенствование сооружений
        jmp get_68_78

        fou_68_78:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13503 //Общее усовершенствование
        jmp get_68_78

        up_68_78:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13500 //Усовершенствование подлодок
        jmp get_68_78

        nts_68_78:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13502 //Новый тип сооружений

        get_68_78:
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next79:
        cmp ebx,79 //Преобр. кориума в энергию
        ja next80_99
        mov edi,13085
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13505 //Усовершенствование сооружений
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer


        next80_99:
        cmp ebx,99 //Повыш. дальности лёгкого лазера
        ja next100
        push ebx
        cmp ebx,97
        jb no_corr_80_99
        inc ebx
        no_corr_80_99:
        mov edi,13006
        add edi,ebx
        pop ebx
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        cmp ebx,80
        je us_80_99
        cmp ebx,81
        je nkp_80_99
        cmp ebx,82
        je nts_80_99
        cmp ebx,84
        jbe us_80_99
        cmp ebx,89
        jbe nts_80_99
        cmp ebx,90
        je us_80_99
        cmp ebx,92
        jbe nts_80_99
        cmp ebx,93
        je us_80_99
        cmp ebx,94
        je nts_80_99
        cmp ebx,95
        je up_80_99
        cmp ebx,97
        jbe nts_80_99
        jmp us_80_99

        us_80_99:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13505 //Усовершенствование сооружений
        jmp get_80_99

        //ou_68_78:
        //mov edi,0x00807618 // lpModulename
        //mov edi,[edi] // lpModulename
        //push edi
        //mov edi,13503 //Общее усовершенствование
        //jmp get_80_99

        up_80_99:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13500 //Усовершенствование подлодок
        jmp get_80_99

        nts_80_99:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13502 //Новый тип сооружений
        jmp get_80_99

        nkp_80_99:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13501 //Новый класс подлодок

        get_80_99:
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer


        next100:
        cmp ebx,100 //Квантовый парализатор
        ja next101
        mov edi,13176
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13501 //Новый класс подлодок
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next101:
        cmp ebx,101 //Усиление брони
        ja next102_126
        cmp edx,2
        ja lvl3_101
        jb lvl1_101
        mov edi,13141
        jmp defined_101
        lvl3_101:
        mov edi,13142
        jmp defined_101
        lvl1_101:
        mov edi,13110
        defined_101:
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13501 //Новый класс подлодок
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next102_126:
        cmp ebx,126
        ja next127
        cmp ebx,103 //Ионная защитная обшивка
        ja not_ion_armor_or_lvl1
        cmp edx,2
        ja lvl3_103
        jb not_leveled_research
        mov edi,13143
        jmp defined
        lvl3_103:
        mov edi,13144
        jmp defined
        not_ion_armor_or_lvl1:
        cmp ebx,109 //Увеличение скорости
        jne not_speed_si_or_lvl1
        cmp edx,2
        ja lvl3_109
        jb not_leveled_research
        mov edi,13145
        jmp defined
        lvl3_109:
        mov edi,13146
        jmp defined

        not_speed_si_or_lvl1:
        cmp ebx,122 //Энергоснаряд урон
        jne not_energy_dmg_or_lvl1
        cmp edx,2
        jb not_leveled_research
        mov edi,13147
        jmp defined

        not_energy_dmg_or_lvl1:
        cmp ebx,125 //Парализация
        je not_leveled_research
        cmp edx,2
        jb not_leveled_research
        mov edi,13148
        jmp defined

        not_leveled_research:
        push ebx
        cmp ebx,105
        jb no_corr_102_126
        inc ebx
        no_corr_102_126:
        mov edi,13009
        add edi,ebx
        pop ebx
        defined:
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        cmp ebx,103
        jbe up_102_126
        cmp ebx,104
        je us_102_126
        cmp ebx,105
        je nkp_102_126
        cmp ebx,106
        je up_102_126
        cmp ebx,108
        jbe nts_102_126
        cmp ebx,110
        jbe up_102_126
        cmp ebx,115
        jbe nkp_102_126
        cmp ebx,116
        je up_102_126
        cmp ebx,117
        je nts_102_126
        cmp ebx,118
        je uo_102_126
        cmp ebx,119
        je nkp_102_126
        cmp ebx,121
        jbe us_102_126
        cmp ebx,122
        je uo_102_126
        cmp ebx,123
        je us_102_126
        cmp ebx,125
        jbe uo_102_126
        jmp up_102_126

        us_102_126:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13505 //Усовершенствование сооружений
        jmp get_102_126

        up_102_126:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13500 //Усовершенствование подлодок
        jmp get_102_126

        nts_102_126:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13502 //Новый тип сооружений
        jmp get_102_126

        nkp_102_126:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13501 //Новый класс подлодок
        jmp get_102_126

        uo_102_126:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13504 //Усовершенствование оружия

        get_102_126:
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next127:
        cmp ebx,127 //Увеличение дистанции обзора осм
        ja next128
        mov edi,13037
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13505 //Усовершенствование сооружений
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer


        next128:
        cmp ebx,128 //Мобильная рем платформа
        ja next132
        mov edi,13163
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13501 //Новый класс подлодок
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next132:
        cmp ebx,132 //Ключ к шифру
        ja next133
        mov edi,13019
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13505 //Усовершенствование сооружений
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next133:
        cmp ebx,133 //Плавучие платформы
        ja next134
        mov edi,13023
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13505 //Усовершенствование сооружений
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next134:
        cmp ebx,134 //Рассеивающий экран
        ja next135
        mov edi,13024
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13502 //Новый тип сооружений
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next135:
        cmp ebx,135 //Телепортация
        ja next136
        mov edi,13026
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13502 //Новый тип сооружений
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next136:
        cmp ebx,136 //Ускорение создания вооруж
        ja next137
        mov edi,13162
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13505 //Усовершенствование сооружений
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next137:
        cmp ebx,137 //Усиление мощности локатора
        ja next138
        mov edi,13165
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13505 //Усовершенствование сооружений
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next138:
        cmp ebx,138 //Увеличение добычи шахт
        ja next139
        mov edi,13038
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13505 //Усовершенствование сооружений
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next139:
        cmp ebx,139 //Ускорение ремнота
        ja next140
        mov edi,13040
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13505 //Усовершенствование сооружений
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next140:
        cmp ebx,140 //Ускорение перезарядки телепорта
        ja next141
        mov edi,13041
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13505 //Усовершенствование сооружений
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next141:
        cmp ebx,141 //Улучшенная методика взлома
        ja next142
        mov edi,13068
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13505 //Усовершенствование сооружений
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next142:
        cmp ebx,142 //Повышение сетевой безопасности
        ja next143
        mov edi,13071
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13505 //Усовершенствование сооружений
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next143:
        cmp ebx,143 //Обнаружение телепортации
        ja next144
        mov edi,13083
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13505 //Усовершенствование сооружений
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next144:
        cmp ebx,144 //Ускоренный захват сооружений
        ja next145
        mov edi,13151
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13500 //Усовершенствование подлодок
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer

        next145:
        cmp ebx,145 //Обнаружение лазерных ловушек
        ja next146_154
        mov edi,13082
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13500 //Усовершенствование подлодок
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer


        next146_154:
        mov edi,13007
        add edi,ebx
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        cmp ebx,146
        je up_146_154
        cmp ebx,147
        je uo_146_154
        cmp ebx,148
        je up_146_154
        cmp ebx,151
        jbe uo_146_154
        cmp ebx,152
        je up_146_154
        cmp ebx,143
        je uo_146_154
        jmp up_146_154

        //us_146_154:
        //mov edi,0x00807618 // lpModulename
        //mov edi,[edi] // lpModulename
        //push edi
        //mov edi,13505 //Усовершенствование сооружений
        //jmp get_146_154

        //ou_146_154:
        //mov edi,0x00807618 // lpModulename
        //mov edi,[edi] // lpModulename
        //push edi
        //mov edi,13503 //Общее усовершенствование
        //jmp get_146_154

        up_146_154:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13500 //Усовершенствование подлодок
        jmp get_146_154

        //nts_146_154:
        //mov edi,0x00807618 // lpModulename
        //mov edi,[edi] // lpModulename
        //push edi
        //mov edi,13502 //Новый тип сооружений
        //jmp get_146_154

        //nkp_146_154:
        //mov edi,0x00807618 // lpModulename
        //mov edi,[edi] // lpModulename
        //push edi
        //mov edi,13501 //Новый класс подлодок

        uo_146_154:
        mov edi,0x00807618 // lpModulename
        mov edi,[edi] // lpModulename
        push edi
        mov edi,13504 //Усовершенствование оружия

        get_146_154:
        push edi
        mov edi, 0x006B0140
        call edi // func_get_string
        push eax
        jmp prepare_buffer



        prepare_buffer:
                    // push 007C411C //aSS (%s %s)
        push 0x007C7FE4        // aSS_3 (%s - %s)
        push 0x80F346 // global string buffer + 12
        mov eax, 0x0085BDE8
        call [eax] // WsprintfA
        pop eax                  // compensate, esp doesn't return after function call
        pop eax
        pop eax
        pop eax

        //show_message
        mov ecx,[0x008016D8]        // dw_for_message_send
        mov ecx,[ecx]        // dw_for_message_send
                // xor eax,eax
                // mov al,[ebp+08] //player input
                // push eax //player input
        push 8
        push 0x0080F33A // global string buffer
        mov eax, 0x004014D8     // func_show_player_message
        call eax     // func_show_player_message

        no_show:
        pop eax
        pop esi
        pop edi
        pop ecx
        pop ebx
        mov dword ptr [ebp-0x0C],eax
        mov ecx,[ebp-0x0C]

        jmp[MessageResearchComplete_JmpBack]
    }
}

static unsigned long GoldMineInterfaceAdjust_Jmp = 0x004C07AD;
static unsigned long GoldMineInterfaceAdjust_JmpBack = GoldMineInterfaceAdjust_Jmp + 8;
__declspec(naked) void inline GoldMineInterfaceAdjust()
{
    __asm {
        lea eax,[eax+eax*4]

        lea ecx,[eax+eax*4]
        mov eax, 0x51EB851F
        jmp[GoldMineInterfaceAdjust_JmpBack]
    }
}

static unsigned long PSGCreateStruct_Jmp = 0x004D14D4;
static unsigned long PSGCreateStruct_JmpBack = PSGCreateStruct_Jmp + 5;
__declspec(naked) void inline PSGCreateStruct()
{
    __asm {
        cmp eax,0x4C
        jne originalcode
        mov eax,[ebx+0x24]
        lea edx,[eax+eax*4]
        lea ecx,[eax+edx*8]
        lea edx,[eax+ecx*2]
        shl edx,4
        add edx,eax
        cmp [edx*2+0x007F5862],edi
        jne region1
        push 0xA
        push 4
        push 0xA
        push edi
        mov eax, 0x006AE290
        call eax
        mov ecx,[ebx+0x24]
        lea edx,[ecx+ecx*4]
        lea edx,[ecx+edx*8]
        lea edx,[ecx+edx*2]
        shl edx,4
        add edx,ecx
        mov dword ptr [edx*2+0x007F5862],eax

        region1:
        lea eax,[ebp-4]
        mov dword ptr [ebp-4],ebx
        push eax
        mov eax,[ebx+0x24]
        lea ecx,[eax+eax*4]
        lea edx,[eax+ecx*8]
        lea ecx,[eax+edx*2]
        shl ecx,4
        add ecx,eax
        mov edx,[ecx*2+0x007F5862]
        mov ecx,0x004D1762
        jmp ecx

        jumpregion:
        mov ecx,0x004D153B
        jmp ecx

        originalcode:
        cmp eax,0x64
        jne jumpregion
        jmp[PSGCreateStruct_JmpBack]
    }
}

static unsigned long PSGPlacingCheck_Jmp = 0x004AE8DA;
static unsigned long PSGPlacingCheck_JmpBack = PSGPlacingCheck_Jmp + 9;
__declspec(naked) void inline PSGPlacingCheck()
{
    __asm {
        cmp eax,0x4C
        jne originalcode
        lea eax,[esi+esi*4]
        lea ecx,[esi+eax*8]
        lea edx,[esi+ecx*2]
        shl edx,4
        add edx,esi
        mov ecx,[edx*2+0x007F5862]
        lea edi,[edx*2+0x007F5862]
        test ecx,ecx
        je jumpregion3
        mov eax,[ecx+0xC]
        xor esi,esi
        test eax,eax
        jng jumpregion3

        region:
        lea eax,[ebp-0xC]
        mov edx,esi
        push eax
        mov eax, 0x006ACC70
        call eax
        lea ecx,[ebp-4]
        lea edx,[ebp-2]
        push ecx
        mov ecx,[ebp-0xC]
        lea eax,[ebp+0x2A]
        push edx
        push eax
        mov eax, 0x004018C5
        call eax
        movsx eax,word ptr [ebp+0x2A]
        mov ecx,[ebp+8]
        cmp eax,ecx
        mov cx,[ebp-2]
        jne region1
        mov ebx,[ebp+0x0C]
        movsx edx,cx
        cmp edx,ebx
        jne region1
        movsx edx,word ptr [ebp-4]
        cmp edx,[ebp+0x10]
        je region2

        region1:
        sub eax,[ebp+8]
        cdq
        xor eax,edx
        sub eax,edx
        cmp eax,6
        jg region2
        mov edx,[ebp+0x0C]
        movsx eax,cx
        sub eax,edx
        cdq
        xor eax,edx
        sub eax,edx
        cmp eax,6

        region2:
        jng jumpregion2
        mov ecx,[edi]
        inc esi
        cmp esi,[ecx+0x0C]
        jl region

        jumpregion3:
        mov ecx,0x004AEC9D
        jmp ecx
            
        jumpregion:
        mov ecx,0x004AE985
        jmp ecx

        jumpregion2:
        mov ecx,0x004AEC96
        jmp ecx
            
        originalcode:
        cmp eax,0x64
        jne jumpregion
        jmp[PSGPlacingCheck_JmpBack]
    }
}

static unsigned long PSGClearStruct_Jmp = 0x004D28CB;
static unsigned long PSGClearStruct_JmpBack = PSGClearStruct_Jmp + 9;
__declspec(naked) void inline PSGClearStruct()
{
    __asm {
        cmp eax,0x4C
        jne originalcode
        mov eax,[esi+0x24]
        lea ecx,[eax+eax*4]
        lea edx,[eax+ecx*8]
        lea ecx,[eax+edx*2]
        shl ecx,4
        add ecx,eax
        mov ecx,[ecx*2+0x007F5862]
        cmp ecx,edi
        je jumpregion3
        mov eax,[ecx+0xC]
        xor ebx,ebx
        cmp eax,edi
        jle region1

        region2:
        lea edx,[ebp-04]
        push edx
        mov edx,ebx
        mov eax, 0x006ACC70
        call eax
        cmp [ebp-4],esi
        je region3
        mov eax,[esi+0x24]
        inc ebx
        lea ecx,[eax+eax*4]
        lea edx,[eax+ecx*8]
        lea ecx,[eax+edx*2]
        shl ecx,4
        add ecx,eax
        mov ecx,[ecx*2+0x007F5862]
        cmp ebx,[ecx+0xC]
        jl region2
        jmp region1

        region3:
        mov eax,[esi+0x24]
        push ebx
        lea edx,[eax+eax*4]
        lea ecx,[eax+edx*8]
        lea edx,[eax+ecx*2]
        shl edx,4
        add edx,eax
        mov eax,[edx*2+0x007F5862]
        push eax
        mov eax, 0x006B0C70
        call eax

        region1:
        mov eax,[esi+0x24]
        lea ecx,[eax+eax*4]
        lea edx,[eax+ecx*8]
        lea ecx,[eax+edx*2]
        shl ecx,04
        add ecx,eax
        mov eax,[ecx*2+0x007F5862]
        cmp [eax+0xC],edi
        jne jumpregion3
        push eax
        mov eax,0x006AE110
        call eax
        mov eax,[esi+0x24]
        lea edx,[eax+eax*4]
        lea ecx,[eax+edx*8]
        lea edx,[eax+ecx*2]
        shl edx,4
        add edx,eax
        mov dword ptr [edx*2+0x007F5862],edi

        jumpregion3:
        mov ecx,0x004D2DC7
        jmp ecx
            
        jumpregion:
        mov ecx,0x004D2990
        jmp ecx
                        
        originalcode:
        cmp eax,0x64
        jne jumpregion
        jmp[PSGClearStruct_JmpBack]
    }
}

static unsigned long PSGClearStruct2_Jmp = 0x004B9AE9;
static unsigned long PSGClearStruct2_JmpBack = PSGClearStruct2_Jmp + 5;
__declspec(naked) void inline PSGClearStruct2()
{
    __asm {
        
        cmp eax,0x4C
        jne originalcode
        mov ecx,esi
        mov eax, 0x0040385F
        call eax
        xor eax,eax
        pop esi
        ret

        originalcode:
        cmp eax,0x4D
        jne jumpregion
        jmp exitt

        jumpregion:
        mov ecx,0x004B9AF9
        jmp ecx

        exitt:
        jmp[PSGClearStruct2_JmpBack]
    }
}

static unsigned long PSGFuncClearForcefieldUse_Jmp = 0x004DF008;
static unsigned long PSGFuncClearForcefieldUse_JmpBack = PSGFuncClearForcefieldUse_Jmp + 7;
__declspec(naked) void inline PSGFuncClearForcefieldUse()
{
    __asm {
        cmp [esi+0x5AC],0x4C
        jne originalcode
        mov ecx,[ecx*2+0x007F5862]
        jmp exitt

        originalcode:
        mov ecx,[ecx*2+0x007F5802]

        exitt:
        jmp[PSGFuncClearForcefieldUse_JmpBack]
    }
}

static unsigned long PSGFuncClearForcefieldUse2_Jmp = 0x004DF043;
static unsigned long PSGFuncClearForcefieldUse2_JmpBack = PSGFuncClearForcefieldUse2_Jmp + 7;
__declspec(naked) void inline PSGFuncClearForcefieldUse2()
{
    __asm {
        cmp [esi+0x5AC],0x4C
        jne originalcode
        mov ecx,[ecx*2+0x007F5862]
        jmp exitt

        originalcode:
        mov ecx,[ecx*2+0x007F5802]

        exitt:
        jmp[PSGFuncClearForcefieldUse2_JmpBack]
    }
}

static unsigned long PSGFuncClearForcefieldUse3_Jmp = 0x004DF063;
static unsigned long PSGFuncClearForcefieldUse3_JmpBack = PSGFuncClearForcefieldUse3_Jmp + 7;
__declspec(naked) void inline PSGFuncClearForcefieldUse3()
{
    __asm {
        cmp [esi+0x5AC],0x4C
        jne originalcode
        mov eax,[edx*2+0x007F5862]
        jmp exitt

        originalcode:
        mov eax,[edx*2+0x007F5802]

        exitt:
        jmp[PSGFuncClearForcefieldUse3_JmpBack]
    }
}

static unsigned long PSGFuncClearForcefieldUse4_Jmp = 0x004DF082;
static unsigned long PSGFuncClearForcefieldUse4_JmpBack = PSGFuncClearForcefieldUse4_Jmp + 7;
__declspec(naked) void inline PSGFuncClearForcefieldUse4()
{
    __asm {
        cmp [esi+0x5AC],0x4C
        jne originalcode
        mov eax,[eax*2+0x007F5862]
        jmp exitt

        originalcode:
        mov eax,[eax*2+0x007F5802]

        exitt:
        jmp[PSGFuncClearForcefieldUse4_JmpBack]
    }
}

static unsigned long PSGFuncClearForcefieldUse5_Jmp = 0x004DF0A7;
static unsigned long PSGFuncClearForcefieldUse5_JmpBack = PSGFuncClearForcefieldUse5_Jmp + 11;
__declspec(naked) void inline PSGFuncClearForcefieldUse5()
{
    __asm {
        cmp [ebx+0x5AC],0x4C
        jne originalcode
        mov dword ptr [ecx*2+0x007F5862],0
        jmp exitt

        originalcode:
        mov dword ptr [ecx*2+0x007F5802],0

        exitt:
        jmp[PSGFuncClearForcefieldUse5_JmpBack]
    }
}

static unsigned long PSGAddNumberBeforeComplete_Jmp = 0x004B9974;
static unsigned long PSGAddNumberBeforeComplete_JmpBack = PSGAddNumberBeforeComplete_Jmp + 5;
__declspec(naked) void inline PSGAddNumberBeforeComplete()
{
    __asm {
        cmp eax,0x4C
        jne originalcode
        mov ecx,esi
        mov eax, 0x004045A2 //func_make_power_protector_description
        call eax
        mov eax, 0x004B99D4
        jmp eax

        jumpregion:
        mov ecx, 0x004B9982
        jmp ecx

        originalcode:
        cmp eax,0x4D
        jne jumpregion

        jmp[PSGAddNumberBeforeComplete_JmpBack]
    }
}

static unsigned long PSGFuncMakePowerProtectorUse_Jmp = 0x004DEF68;
static unsigned long PSGFuncMakePowerProtectorUse_JmpBack = PSGFuncMakePowerProtectorUse_Jmp + 7;
__declspec(naked) void inline PSGFuncMakePowerProtectorUse()
{
    __asm {
        cmp [esi+0x5AC],0x4C
        jne originalcode
        mov eax,[ecx*2+0x007F5862]
        jmp exitt

        originalcode:
        mov eax,[ecx*2+0x007F5802]
        exitt:
        jmp[PSGFuncMakePowerProtectorUse_JmpBack]
    }
}

static unsigned long PSGFuncMakePowerProtectorUse2_Jmp = 0x004DEF91;
static unsigned long PSGFuncMakePowerProtectorUse2_JmpBack = PSGFuncMakePowerProtectorUse2_Jmp + 7;
__declspec(naked) void inline PSGFuncMakePowerProtectorUse2()
{
    __asm {
        cmp [esi+0x5AC],0x4C
        jne originalcode
        mov dword ptr [edx*2+0x007F5862],eax
        jmp exitt

        originalcode:
        mov dword ptr [edx*2+0x007F5802],eax
        exitt:
        jmp[PSGFuncMakePowerProtectorUse2_JmpBack]
    }
}

static unsigned long PSGFuncMakePowerProtectorUse3_Jmp = 0x004DEFB0;
static unsigned long PSGFuncMakePowerProtectorUse3_JmpBack = PSGFuncMakePowerProtectorUse3_Jmp + 7;
__declspec(naked) void inline PSGFuncMakePowerProtectorUse3()
{
    __asm {
        cmp [ebx+0x5AC],0x4C
        jne originalcode
        mov ecx,[eax*2+0x007F5862]
        jmp exitt

        originalcode:
        mov ecx,[eax*2+0x007F5802]
        exitt:
        jmp[PSGFuncMakePowerProtectorUse3_JmpBack]
    }
}

static unsigned long PrivateOrderSounds_Jmp = 0x0041C3BA;
static unsigned long PrivateOrderSounds_JmpBack = PrivateOrderSounds_Jmp + 5;
__declspec(naked) void inline PrivateOrderSounds()
{
    __asm {
        cmp esi,0x10000
        jb originalcode

        pop ecx
        cmp ecx,4
        jne not_order

        mov al,[esi+0x24] // player owner
        push ebx
        xor ebx, ebx
        mov ebx, 0x0080874D
        mov ebx, [ebx]
        cmp al,bl
        pop ebx
        je not_order
                     // no sound
        pop eax
        pop eax
        pop eax
        pop eax
        pop eax
        jmp exitt

        not_order:
        push ecx
        mov ecx,0x00807658

        originalcode:
        mov eax,0x00404BD8
        call eax
        exitt:
        jmp[PrivateOrderSounds_JmpBack]
    }
}

static unsigned long CoriumMiningUpgrades_Jmp = 0x00467247;
static unsigned long CoriumMiningUpgrades_JmpBack = CoriumMiningUpgrades_Jmp + 5;
__declspec(naked) void inline CoriumMiningUpgrades()
{
    __asm {
        push eax
        mov edx,[esi+0x7D6]
        test edx,edx
        jz originalcode

        push [esi+0x24]
        mov eax, 0x004049B7 // func_return_player_race
        call eax

        cmp eax,2
        ja silicoids
        jb sharks
        push 138 // octopi
        jmp check_upgrade

        sharks:
        push 30 // sharks
        jmp check_upgrade

        silicoids:
        push 84 // silicoids

        check_upgrade:
        push [esi+0x24]
        mov eax, 0x0040186B
        call eax
        test ax, ax
        jz originalcode
        pop eax
        mov ecx,8
        jmp exitt

        originalcode:
        pop eax
        mov ecx,0xA
        exitt:
        jmp[CoriumMiningUpgrades_JmpBack]
    }
}

static unsigned long RangeAllSubs6_Jmp = 0x0044F7E7;
static unsigned long RangeAllSubs6_JmpBack = RangeAllSubs6_Jmp + 6;
__declspec(naked) void inline RangeAllSubs6()
{
    __asm {
        mov eax,[ebx+0x000006F7]
        cmp eax,3 // Cruiser
        je exitt
        cmp eax,38 // WS Flagship
        je exitt
        cmp eax,15 // Heavy cruiser
        je exitt
        cmp eax,16 // Invader
        je exitt
        cmp eax,31  // Dreadnaught
        je exitt
            // cmp eax,#32 // Escort
            // je exit
        mov WORD PTR [ebx+0x814], 0x4B6
        mov WORD PTR [ebx+0x816], 6

        exitt:
        jmp[RangeAllSubs6_JmpBack]
    }
}

static unsigned long ResearchBuildingsLimitCreateCommon_Jmp = 0x004D1482;
static unsigned long ResearchBuildingsLimitCreateCommon_JmpBack =
    ResearchBuildingsLimitCreateCommon_Jmp + 7;
__declspec(naked) void inline ResearchBuildingsLimitCreateCommon()
{
    __asm {
        cmp dword ptr [ebx+0x00000259],92
        je exitt
        cmp dword ptr [ebx+0x00000259],53
        je start
        cmp dword ptr [ebx+0x00000259],84
        jb exitt
        cmp dword ptr [ebx+0x00000259],90
        ja exitt

        start:
        mov eax, [ebx+0x24]
        lea edx, [eax+eax*4]
        lea ecx, [eax+edx*8]
        lea edx, [eax+ecx*2]
        shl edx, 4
        add edx, eax
        cmp dword ptr [ebx+0x00000259],53
        jne modules
        add [edx*2+0x007F5866],1
        jmp exitt

        modules:
        add [edx*2+0x007F5866],1

        exitt:
        jmp[ResearchBuildingsLimitCreateCommon_JmpBack]
    }
}

static unsigned long CheckHumanResearchCenters_Jmp = 0x0048898D;
static unsigned long CheckHumanResearchCenters_JmpBack = CheckHumanResearchCenters_Jmp + 5;
__declspec(naked) void inline CheckHumanResearchCenters()
{
    __asm {
        mov eax, 0x0040571D
        call eax

        cmp edi,53
        jne exitt

        push eax
        push ecx
        push edx

        mov eax,[esi+0x24]
        lea ecx,[eax+eax*4]
        lea edx,[eax+ecx*8]
        lea ecx,[eax+edx*2]
        shl ecx,4
        add ecx,eax
        mov eax,[ecx*2+0x007F5866]
        cmp eax,5 //max centers

        pop edx
        pop ecx
        pop eax
        jb exitt
        mov eax,0

        exitt:
        jmp[CheckHumanResearchCenters_JmpBack]
    }
}

static unsigned long CheckSIModules_Jmp = 0x004CE147;
static unsigned long CheckSIModules_JmpBack = CheckSIModules_Jmp + 5;
__declspec(naked) void inline CheckSIModules()
{
    __asm {
        mov eax, 0x0040571D
        call eax

        mov edi,[ebp-4]
        cmp edi,84
        jb exitt
        cmp edi,90
        ja exitt

        push ebx
        push ecx
        push edx

        mov edi,0x007F5866

        mov ebx,[ebx+0x24]
        lea ecx,[ebx+ebx*4]
        lea edx,[ebx+ecx*8]
        lea ecx,[ebx+edx*2]
        shl ecx,4
        add ecx,ebx
        lea ebx,[ecx*2+edi]
        mov ecx,[ebx]
        cmp ecx, 7 //max modules

        pop edx
        pop ecx
        pop ebx
        jb exitt
        mov eax,0

        exitt:
        jmp[CheckSIModules_JmpBack]
    }
}

static unsigned long DestroyedModulesAndHumanCentersFinished_Jmp = 0x004B9C49;
static unsigned long DestroyedModulesAndHumanCentersFinished_JmpBack =
    DestroyedModulesAndHumanCentersFinished_Jmp + 5;
__declspec(naked) void inline DestroyedModulesAndHumanCentersFinished()
{
    __asm {
        mov eax,[esi+0x5AC] // ID
        cmp eax,53
        je humans
        cmp eax,84
        jb originalcode
        cmp eax,90
        ja originalcode

        push ebx
        push ecx
        push edx
        push edi

        mov edi,0x007F5866 // lea edi,[0x007F5866]

        mov eax,[esi+0x24]
        lea ecx,[eax+eax*4]
        lea edx,[eax+ecx*8]
        lea ecx,[eax+edx*2]
        shl ecx,4
        add ecx,eax
        lea ebx,[ecx*2+edi]
        sub [ebx],1
        pop edi
        pop edx
        pop ecx
        pop ebx
        jmp originalcode

        humans:
        push ebx
        push ecx
        push edx

        mov eax,[esi+0x24]
        lea ecx,[eax+eax*4]
        lea edx,[eax+ecx*8]
        lea ecx,[eax+edx*2]
        shl ecx,4
        add ecx,eax
        lea ebx,[ecx*2+0x007F5866]
        mov eax,[ebx]
        sub [ebx],1
        pop edx
        pop ecx
        pop ebx

        originalcode:
        mov eax, 0x004010AA
        call eax

        jmp[DestroyedModulesAndHumanCentersFinished_JmpBack]
    }
}

static unsigned long DestroyedModulesAndHumanCentersBuilding_Jmp = 0x004D5B9B;
static unsigned long DestroyedModulesAndHumanCentersBuilding_JmpBack =
    DestroyedModulesAndHumanCentersBuilding_Jmp + 5;
__declspec(naked) void inline DestroyedModulesAndHumanCentersBuilding()
{
    __asm {
        mov eax,[esi+0x259]
        cmp eax,53
        je humans
        cmp eax,84
        jb originalcode
        cmp eax,90
        ja originalcode

        push ebx
        push ecx
        push edx
        push edi

        mov edi,0x007F5866

        mov eax,[esi+0x24]
        lea ecx,[eax+eax*4]
        lea edx,[eax+ecx*8]
        lea ecx,[eax+edx*2]
        shl ecx,4
        add ecx,eax
        lea ebx,[ecx*2+edi]
        sub [ebx],1
        pop edi
        pop edx
        pop ecx
        pop ebx
        jmp originalcode

        humans:
        push ebx
        push ecx
        push edx

        mov eax,[esi+0x24]
        lea ecx,[eax+eax*4]
        lea edx,[eax+ecx*8]
        lea ecx,[eax+edx*2]
        shl ecx,4
        add ecx,eax
        lea ebx,[ecx*2+0x007F5866]
        mov eax,[ebx]

        sub [ebx],1
        pop edx
        pop ecx
        pop ebx

        originalcode:
        mov eax, 0x00404264
        call eax

        jmp[DestroyedModulesAndHumanCentersBuilding_JmpBack]
    }
}

static unsigned long DismantledModulesAndHumanCenters_Jmp = 0x004B8DDA;
static unsigned long DismantledModulesAndHumanCenters_JmpBack =
    DismantledModulesAndHumanCenters_Jmp + 6;
__declspec(naked) void inline DismantledModulesAndHumanCenters()
{
    __asm {
        mov ecx,[esi+0x00000239]

        push eax

        mov eax,[esi+0x5AC] // ID
        cmp eax,53
        je humans
        cmp eax,84
        jb exitt
        cmp eax,90
        ja exitt

        push ebx
        push ecx
        push edx
        push edi

        mov edi,0x007F5866

        mov eax,[esi+0x24]
        lea ecx,[eax+eax*4]
        lea edx,[eax+ecx*8]
        lea ecx,[eax+edx*2]
        shl ecx,4
        add ecx,eax
        lea ebx,[ecx*2+edi]
        sub [ebx],1
        pop edi
        pop edx
        pop ecx
        pop ebx
        jmp exitt

        humans:
        push ebx
        push ecx
        push edx

        mov eax,[esi+0x24]
        lea ecx,[eax+eax*4]
        lea edx,[eax+ecx*8]
        lea ecx,[eax+edx*2]
        shl ecx,4
        add ecx,eax
        lea ebx,[ecx*2+0x007F5866]
        mov eax,[ebx]
        sub [ebx],1
        pop edx
        pop ecx
        pop ebx

        exitt:
        pop eax
        jmp[DismantledModulesAndHumanCenters_JmpBack]
    }
}

static unsigned long CancelledModulesAndHumanCenters_Jmp = 0x004D3765;
static unsigned long CancelledModulesAndHumanCenters_JmpBack = CancelledModulesAndHumanCenters_Jmp + 6;
__declspec(naked) void inline CancelledModulesAndHumanCenters()
{
    __asm {
        mov eax,[esi+0x259]
        cmp eax,53
        je humans
        cmp eax,84
        jb originalcode
        cmp eax,90
        ja originalcode

        push ebx
        push edx

        mov edi,0x007F5866

        mov eax,[esi+0x24]
        lea ecx,[eax+eax*4]
        lea edx,[eax+ecx*8]
        lea ecx,[eax+edx*2]
        shl ecx,04
        add ecx,eax
        lea ebx,[ecx*2+edi]
        sub [ebx],1
        pop edx
        pop ebx
        jmp originalcode

        humans:
        push ebx
        push edx

        mov eax,[esi+0x24]
        lea ecx,[eax+eax*4]
        lea edx,[eax+ecx*8]
        lea ecx,[eax+edx*2]
        shl ecx,4
        add ecx,eax
        lea ebx,[ecx*2+0x007F5866]
        mov eax,[ebx]

        sub [ebx],1
        pop edx
        pop ebx

        originalcode:
        lea edi,[esi+0x000001D5]

        jmp[CancelledModulesAndHumanCenters_JmpBack]
    }
}

static unsigned long ModifyAimGpsV2_Jmp = 0x004C3902;
static unsigned long ModifyAimGpsV2_JmpBack = ModifyAimGpsV2_Jmp + 7;
__declspec(naked) void inline ModifyAimGpsV2()
{
    __asm {
        push ebx
        push edi

        //order
        mov edx,[esi+0x0C]
        mov eax,[edx+0x9F]
        test eax,eax
        jne main

        idle:
        mov edi,0
        mov ebx,0
        jmp calc

        main:
        mov eax,[edx+0xE3] // move flag
        test eax,eax
        jz idle

        // Check if too close        
        push eax
        push ecx
        push edx
        movsx eax,word ptr [edx+0x4B]
        push eax
        movsx ecx,word ptr [edx+0x49]
        push ecx
        movsx edx,word ptr [edx+0x47]
        push edx
        movsx eax,word ptr [edi+0x4B]
        push eax
        movsx ecx,word ptr [edi+0x49]
        push ecx
        movsx edx,word ptr [edi+0x47]
        push edx
        mov eax, 0x006AADD0
        call eax
        cmp eax, 2
        pop edx
        pop ecx
        pop eax
        jbe idle
        //---

        mov eax,[edx+0xAF]
        test eax,eax
        jne non_zero
        mov edi,1
        mov ebx,0
        jmp calc // 0

        non_zero:
        cmp eax,180
        je degree_180
        jb under_180
        mov ebx,1
        cmp eax,270
        je degree_270
        jb degree_225
        cmp eax,360
        ja idle
        mov edi,1          // 315
        jmp calc

        degree_180:
        mov edi,-1
        mov ebx,0          // 180
        jmp calc

        under_180:
        mov ebx,-1

        cmp eax,90
        jne not_90
        mov edi,0          // 90
        jmp calc

        not_90:
        cmp eax,45
        je degree_45
        mov edi,-1         // 135
        jmp calc

        degree_45:
        mov edi,1          // 45
        jmp calc

        degree_270:
        mov edi,0          // 270
        jmp calc

        degree_225:
        mov edi,-1         // 225

        calc:
        mov edx,[esi+0x0C]
        movsx eax,word ptr [edx+0x41]
        imul edi,201
                    // speed
        xor ecx,ecx
        mov cl,[edx+0x61]
        sub ecx,17
        imul ecx,0x10
        test edi,edi
        je set_change_x
        jns increasing_x
        sub edi,ecx
        jmp set_change_x
        increasing_x:
        add edi,ecx

        set_change_x:
                    // ecx, edx, push eax
                    // get distance
                    // mov ecx,[esi+0C]
                    // mov
        add eax,edi
        mov dword ptr [esi+0x20],eax

        mov ecx,[esi+0x0C]
        movsx edx,word ptr [ecx+0x43]
        imul ebx,201

                    // speed
        xor eax,eax
        mov al,[ecx+0x61]
        sub eax,17
        imul eax,0x10
        test ebx,ebx
        je set_change_y
        jns increasing_y
        sub ebx,eax
        jmp set_change_y
        increasing_y:
        add ebx,eax

        set_change_y:
        add edx,ebx
        mov dword ptr [esi+0x24],edx

        mov eax,[esi+0x0C]
        movsx ecx,word ptr [eax+0x45]
        mov dword ptr [esi+0x28],ecx

        pop edi
        pop ebx

        jmp[ModifyAimGpsV2_JmpBack]
    }
}

static unsigned long ModifyTurretTurnV2_Jmp = 0x004C36D9;
static unsigned long ModifyTurretTurnV2_JmpBack = ModifyTurretTurnV2_Jmp + 5;
__declspec(naked) void inline ModifyTurretTurnV2()
{
    __asm {
        push edx
            // order:
        mov edx,[eax+0x9F]
        test edx,edx
        jne main

        idle:
        mov ecx,0
        mov ebx,0
        jmp calc

        main:
        push eax
        mov eax,[eax+0xE3] // move flag
        test eax,eax
        pop eax
        jz idle

        
        // Check if too close        
        push eax   
        push ebx
        push ecx
        push edx
        movsx ebx,word ptr [eax+0x4B]
        push ebx
        movsx ecx,word ptr [eax+0x49]
        push ecx
        movsx edx,word ptr [eax+0x47]
        push edx
        movsx ebx,word ptr [edi+0x4B]
        push ebx
        movsx ecx,word ptr [edi+0x49]
        push ecx
        movsx edx,word ptr [edi+0x47]
        push edx
        mov eax, 0x006AADD0
        call eax
        cmp eax, 2
        pop edx
        pop ecx
        pop ebx
        pop eax
        jbe idle
        //---

        mov edx,[eax+0xAF]
        test edx,edx
        jne non_zero
        mov ecx,1
        mov ebx,0
        jmp calc // 0

        non_zero:
        cmp edx,180
        je degree_180
        jb under_180
        mov ebx,1
        cmp edx,270
        je degree_270
        jb degree_225
        cmp edx,360
        ja idle
        mov ecx,1 // 315
        jmp calc

        degree_180:
        mov ecx,-1
        mov ebx,0 // 180
        jmp calc

        under_180:
        mov ebx,-1

        cmp edx,90
        jne not_90
        mov ecx,0 // 90
        jmp calc

        not_90:
        cmp edx,45
        je degree_45
        mov ecx,-1 // 135
        jmp calc

        degree_45:
        mov ecx,1 // 45
        jmp calc

        degree_270:
        mov ecx,0 // 270
        jmp calc

        degree_225:
        mov ecx,-1  // 225

        calc:
        mov dx,[eax+0x43]
        imul ebx,201
            // speed
        push ecx
        xor ecx,ecx
        mov cl,[eax+0x61]
        sub ecx,17
        imul ecx,0x10
        test ebx,ebx
        je set_change_x
        jns increasing_x
        sub ebx,ecx
        jmp set_change_x
        increasing_x:
        add ebx,ecx

        set_change_x:
        add edx,ebx
        pop ecx
        push edx
        xor edx,edx

            // Y
        mov dx,[eax+0x41]
        imul ecx,201
            // speed
        xor ebx,ebx
        mov bl,[eax+0x61]
        sub ebx,17
        imul ebx,0x10
        test ecx,ecx
        je set_change_y
        jns increasing_y
        sub ecx,ebx
        jmp set_change_y
        increasing_y:
        add ecx,ebx

        set_change_y:
        add edx,ecx
        mov eax,edx

        jmp[ModifyTurretTurnV2_JmpBack]
    }
}

static unsigned long ModifyTurretTurnCheckV2_Jmp = 0x004C3EE1;
static unsigned long ModifyTurretTurnCheckV2_JmpBack = ModifyTurretTurnCheckV2_Jmp + 5;
__declspec(naked) void inline ModifyTurretTurnCheckV2()
{
    __asm {
        push edx
            // order:
        mov edx,[eax+0x9F]
        test edx,edx
        jne main

        idle:
        mov ecx,0
        mov ebx,0
        jmp calc

        main:
        push eax
        mov eax,[eax+0xE3] // move flag
        test eax,eax
        pop eax
        jz idle

        
        // Check if too close        
        push ebx
        push ecx
        push edx
        push eax
        movsx ebx,word ptr [eax+0x4B]
        push ebx
        movsx ecx,word ptr [eax+0x49]
        push ecx
        movsx edx,word ptr [eax+0x47]
        push edx
        movsx ebx,word ptr [esi+0x4B]
        push ebx
        movsx ecx,word ptr [esi+0x49]
        push ecx
        movsx edx,word ptr [esi+0x47]
        push edx
        mov eax, 0x006AADD0
        call eax
        cmp eax, 2
        pop eax
        pop edx
        pop ecx
        pop ebx
        jbe idle
        //---

        mov edx,[eax+0xAF]
        test edx,edx
        jne non_zero
        mov ecx,1
        mov ebx,0
        jmp calc // 0

        non_zero:
        cmp edx,180
        je degree_180
        jb under_180
        mov ebx,1
        cmp edx,270
        je degree_270
        jb degree_225
        cmp edx,360
        ja idle
        mov ecx,1 // 315
        jmp calc

        degree_180:
        mov ecx,-1
        mov ebx,0 // 180
        jmp calc

        under_180:
        mov ebx,-1

        cmp edx,90
        jne not_90
        mov ecx,0 // 90
        jmp calc

        not_90:
        cmp edx,45
        je degree_45
        mov ecx,-1 // 135
        jmp calc

        degree_45:
        mov ecx,1 // 45
        jmp calc

        degree_270:
        mov ecx,0 // 270
        jmp calc

        degree_225:
        mov ecx,-1  // 225

        calc:
        mov dx,[eax+0x43]
        imul ebx,201
            // speed
        push ecx
        xor ecx,ecx
        mov cl,[eax+0x61]
        sub ecx,17
        imul ecx,0x10
        test ebx,ebx
        je set_change_x
        jns increasing_x
        sub ebx,ecx
        jmp set_change_x
        increasing_x:
        add ebx,ecx

        set_change_x:
        add edx,ebx
        pop ecx
        push edx
        xor edx,edx

            // Y
        mov dx,[eax+0x41]
        imul ecx,201
            // speed
        xor ebx,ebx
        mov bl,[eax+0x61]
        sub ebx,17
        imul ebx,0x10
        test ecx,ecx
        je set_change_y
        jns increasing_y
        sub ecx,ebx
        jmp set_change_y
        increasing_y:
        add ecx,ebx

        set_change_y:
        add edx,ecx
        mov eax,edx

        jmp[ModifyTurretTurnCheckV2_JmpBack]
    }
}

static unsigned long ModifyTurretFix_Jmp = 0x004C36DF;
static unsigned long ModifyTurretFix_JmpBack = ModifyTurretFix_Jmp + 5;
__declspec(naked) void inline ModifyTurretFix()
{
    __asm {
        pop eax
        pop edx
        mov ebx,edx
        pop edx
        push ebx
        push eax
        mov ecx,edi
        call dword ptr [edx+0x10]

        jmp[ModifyTurretFix_JmpBack]
    }
}

static unsigned long ModifyTurretFix2_Jmp = 0x004C3EE7;
static unsigned long ModifyTurretFix2_JmpBack = ModifyTurretFix2_Jmp + 5;
__declspec(naked) void inline ModifyTurretFix2()
{
    __asm {
        pop eax
        pop edx
        mov ebx,edx
        pop edx
        push ebx
        push eax
            // mov ecx,edi
            // call dword ptr [edx+10]
        mov ecx,esi
        call dword ptr [edx+0x10]

        jmp[ModifyTurretFix2_JmpBack]
    }
}

static unsigned long AimPredictionSubmarines_Jmp = 0x004626F2;
static unsigned long AimPredictionSubmarines_JmpBack = AimPredictionSubmarines_Jmp + 7;
__declspec(naked) void inline AimPredictionSubmarines()
{
    __asm {
        mov dx,[edi+0x45] // Z target final
        mov ecx,[esi+0x24]

        push ebx   // ecx free, edi = target ptr
        push eax
        push ecx

                        // move check
        mov eax,[edi+0xE3] // move flag (1, 2)
        test eax,eax
        jz exitt

                    // target has order check
        mov eax,[edi+0x9F]
        test eax,eax
        jz exitt

                    // moving
        mov eax,[edi+0x9F] // order
        mov ecx,[edi+0xA3]         // path length
        lea ecx,[ecx+ecx*8]
                // movsx eax, word ptr [eax+48] //X target in order
        movsx ebx, word ptr [edi+0x47] // X current
        cmp bx, [eax+ecx*8-0x48] // X target in order
        jne horizontal
                    // mov eax,[edi+9F] //order
                    // movsx eax, word ptr [eax+4A] //Y target in order
        movsx ebx, word ptr [edi+0x49] // Y current
        cmp bx, [eax+ecx*8-0x46] // Y target in order
        jne horizontal

                    // vertical
        mov eax,[edi+0x9F]     // order
                // movsx eax, word ptr [eax+4C] //Z target in order
        movsx ebx, word ptr [edi+0x4B] // Z current
        sub ebx, [eax+ecx*8-0x44] // Z target in order
        je exitt         // must never be triggered


        xor ecx,ecx
        mov cl,[edi+0x61]     //реальная скорость
                                     // sub ecx,#17
        imul ecx,5
        test ebx,ebx
        js going_up
        sub edx,ecx
        jmp exitt

        going_up:
        add edx,ecx
        jmp exitt

        horizontal: // define direction
        mov eax,[edi+0xAF]
        test eax,eax
        jnz non_zero
        mov eax,1 // X
        mov ebx,0 // Y
        jmp calc             // 0

        non_zero:
        cmp eax,180
        je degree_180
        jb under_180
        mov ebx,1
        cmp eax,270
        je degree_270
        jb degree_225
        cmp eax,360
        ja exitt
        mov eax,1                    // 315
        jmp calc

        degree_180:
        mov eax,-1
        mov ebx,0                    // 180
        jmp calc

        under_180:
        mov ebx,-1

        //dimension_2:
        cmp eax,90
        jne not_90
        mov eax,0                    // 90
        jmp calc

        not_90:
        cmp eax,45
        je degree_45
        mov eax,-1                   // 135
        jmp calc

        degree_45:
        mov eax,1                    // 45
        jmp calc

        degree_270:
        mov eax,0                    // 270
        jmp calc

        degree_225:
        mov eax,-1                   // 225


        calc:
        test eax,eax
        jz calc_Y
        mov ax,[ebp-0x84] // X target final
        jns inceasing_X
                    // decreasing_X:
        xor ecx,ecx
        mov cl,[edi+0x61]     //реальная скорость
                                 // sub ecx,#17
        imul ecx,7
        sub eax,ecx // add to X axis

        set_X:
        mov [ebp-0x84],ax
        jmp exitt

        inceasing_X:
        xor ecx,ecx
        mov cl,[edi+0x61]     //реальная скорость, от 6 до 21
                                 // sub ecx,#17
        imul ecx,7
        add eax,ecx // add to X axis
        jmp set_X


        calc_Y:
        test ebx,ebx
        mov ax,[ebp-0x82] // Y target final
        jns inceasing_Y
                    // decreasing_Y:
        xor ecx,ecx
        mov cl,[edi+0x61] //реальная скорость
                           // sub ecx,#17
        imul ecx,7
        sub eax,ecx // add to Y axis

        set_Y:
        mov [ebp-0x82],ax
        jmp exitt

        inceasing_Y:
        xor ecx,ecx
        mov cl,[edi+0x61] //реальная скорость
                           // sub ecx,#17
        imul ecx,7
        add eax,ecx        // add to X axis
        jmp set_Y


        exitt:
        pop ecx
        pop eax
        pop ebx

        jmp[AimPredictionSubmarines_JmpBack]
    }
}

static unsigned long DodgeFlagSet2_Jmp = 0x00460B68;
static unsigned long DodgeFlagSet2_JmpBack = DodgeFlagSet2_Jmp + 6;
__declspec(naked) void inline DodgeFlagSet2()
{
    __asm {
        mov dword ptr [esi+0x82E],0
        jmp[DodgeFlagSet2_JmpBack]
    }
}

static unsigned long DodgeFlagSet3_Jmp = 0x00460CBF;
static unsigned long DodgeFlagSet3_JmpBack = DodgeFlagSet3_Jmp + 6;
__declspec(naked) void inline DodgeFlagSet3()
{
    __asm {
        mov dword ptr [esi+0x82E],0
        jmp[DodgeFlagSet3_JmpBack]
    }
}

static unsigned long DodgeFlagSet4_Jmp = 0x00460D4E;
static unsigned long DodgeFlagSet4_JmpBack = DodgeFlagSet4_Jmp + 6;
__declspec(naked) void inline DodgeFlagSet4()
{
    __asm {
        mov dword ptr [esi+0x82E],0
        jmp[DodgeFlagSet4_JmpBack]
    }
}

static unsigned long DodgeFlagSet5_Jmp = 0x00472710;
static unsigned long DodgeFlagSet5_JmpBack = DodgeFlagSet5_Jmp + 10;
__declspec(naked) void inline DodgeFlagSet5()
{
    __asm {
        mov dword ptr [esi+0x82E],0
        jmp[DodgeFlagSet5_JmpBack]
    }
}

static unsigned long DodgeFlagSet6_Jmp = 0x00471E6B;
static unsigned long DodgeFlagSet6_JmpBack = DodgeFlagSet6_Jmp + 6;
__declspec(naked) void inline DodgeFlagSet6()
{
    __asm {
        mov dword ptr [esi+0x82E],0
        jmp[DodgeFlagSet6_JmpBack]
    }
}

 
static unsigned long TradeStep10_Jmp = 0x0072434D;
static unsigned long TradeStep10_JmpBack = TradeStep10_Jmp + 5;
__declspec(naked) void inline TradeStep10()
{
    __asm {
        imul eax, [ecx+0x60]
        inc eax
        imul eax, 0xA
        jmp[TradeStep10_JmpBack]
    }
}


//static unsigned long TeleportPersonalDistanceCharge_Jmp = 0x0047A9D2;
//static unsigned long TeleportPersonalDistanceCharge_JmpBack = TeleportPersonalDistanceCharge_Jmp + 6;
//__declspec(naked) void inline TeleportPersonalDistanceCharge()
//{
//    __asm {
//        //add eax, 20
//        push ebx
//        mov ebx, eax
//
//        movsx eax, word ptr [esi+1627] 
//        push eax
//        movsx eax, word ptr [esi+1625] 
//        push eax
//        movsx eax, word ptr [esi+1623] 
//        push eax
//        
//        movsx eax, word ptr [esi+75] 
//        push eax
//        movsx eax, word ptr [esi+73] 
//        push eax
//        movsx eax, word ptr [esi+71] 
//        push eax
//
//        mov dword ptr [eax], 0x006AADD0
//        call eax
//
//        sub ebx,eax
//        test ebx, ebx
//        jnb bigger
//
//        cmp eax,20
//        ja bigger
//
//        sub eax, 20
//        neg eax
//        mov [esi+1822], eax
//
//
//        bigger:
//
//        jmp[TeleportPersonalDistanceCharge_JmpBack]
//    }
//}

 
//static unsigned long HalfArmorT4_Jmp = 0x00459E8F;
//static unsigned long HalfArmorT4_JmpBack = HalfArmorT4_Jmp + 7;
//__declspec(naked) void inline HalfArmorT4()
//{
//    __asm {
//        lea     edx, ds:0[ecx*4+ecx]
//add edx, ecx
//
//        jmp[HalfArmorT4_JmpBack]
//    }
//}

static unsigned long SetMineInSubLocation_Jmp = 0x004767E0;
static unsigned long SetMineInSubLocation_JmpBack = SetMineInSubLocation_Jmp + 21;
__declspec(naked) void inline SetMineInSubLocation()
{
    __asm {
        movsx eax, word ptr [esi+75]
        movsx ecx, word ptr [esi+73]
        movsx edx, word ptr [esi+71]

        jmp[SetMineInSubLocation_JmpBack]
    }
}

static unsigned long ReturnResourcesCanceledBuilding_Jmp = 0x004D284F;
static unsigned long ReturnResourcesCanceledBuilding_JmpBack = ReturnResourcesCanceledBuilding_Jmp + 7;
__declspec(naked) void inline ReturnResourcesCanceledBuilding()
{
    __asm {
        cmp dword ptr [esi+680], 0
        je exitt
        cmp dword ptr [esi+680], 100
        je exitt
        
        push eax
        push ecx
        push edx

        mov eax,[esi+0x368]
        mov ecx,[esi+0x36C]
        xor edi,edi
        lea edx,[eax+eax*2]
        add edx,ecx
        mov ecx,[edx*4+0x007E1C50]
        cmp ecx,edi
        jz metal
        mov eax,[esi+680]
        imul eax,ecx
        lea eax,[eax+eax*2]
        lea ecx,[eax+eax*4]
        mov eax,0x68DB8BAD
        shl ecx,02
        imul ecx
        mov cl,[esi+0x24]
        sar edx,0xC
        mov eax,edx
        shr eax,0x1F
        add edx,eax
        push edx //result corium to replenish
        push ecx //player
        mov ecx,[0x007FA174]
        mov eax, 0x00404412
        call eax
        
        metal:
        mov eax,[esi+0x368]
        mov ecx,[esi+0x36C]
        xor edi,edi
        lea edx,[eax+eax*2]
        add edx,ecx
        mov ecx,[edx*4+0x007E24FC]
        cmp ecx,edi
        jz silicon
        mov eax,[esi+680]
        imul eax,ecx
        lea eax,[eax+eax*2]
        lea ecx,[eax+eax*4]
        mov eax,0x68DB8BAD
        shl ecx,02
        imul ecx
        mov cl,[esi+0x24]
        sar edx,0xC
        mov eax,edx
        shr eax,0x1F
        add edx,eax
        push edx // result metal to replenish
        push ecx // player
        mov ecx,[0x007FA174]
        mov eax, 0x004055E7
        call eax
            
        silicon:
        mov eax,[esi+0x368]
        mov ecx,[esi+0x36C]
        xor edi,edi
        lea edx,[eax+eax*2]
        add edx,ecx
        mov ecx,[edx*4+0x007E3160]
        cmp ecx,edi
        jz gold
        mov eax,[esi+680]
        imul eax,ecx
        lea eax,[eax+eax*2]
        lea ecx,[eax+eax*4]
        mov eax,0x68DB8BAD
        shl ecx,02
        imul ecx
        mov ecx,[esi+0x24]
        sar edx,0xC
        mov eax,edx
        shr eax,0x1F
        add edx,eax
        push edx // result silicon to replenish
        push ecx // player
        mov ecx,[0x007FA174]
        mov eax, 0x00405E6B
        call eax
            
        gold:
        mov eax,[esi+0x368]
        mov ecx,[esi+0x36C]
        xor edi,edi
        lea edx,[eax+eax*2]
        add edx,ecx
        mov ecx,[edx*4+0x008545AC]
        cmp ecx,edi
        jz updateres
        mov eax,[esi+680]
        imul eax,ecx
        lea eax,[eax+eax*2]
        lea ecx,[eax+eax*4]
        mov eax,0x68DB8BAD
        shl ecx,02
        imul ecx
        mov cl,[esi+0x24]
        sar edx,0xC
        mov eax,edx
        shr eax,0x1F
        add edx,eax
        push edx // result gold to replenish
        push ecx // player
        mov ecx,[0x007FA174]
        mov eax, 0x00404336
        call eax

        updateres:
        mov dl,[esi+0x24]
        mov ecx,[0x007FA174]
        push edx
        mov eax, 0x004028F6
        call eax
        mov eax,0x0080874D
        xor ecx, ecx
        mov cl,[eax]
        mov eax,[esi+0x24]
        cmp eax,ecx
        jne outt
        mov ecx,[0x007FA174]
        mov dl,al
        push edx
        mov eax, 0x00404B8D //update resource panel
        call eax


        outt:
        pop edx
        pop ecx
        pop eax

        exitt:
        xor edi, edi
        cmp dword ptr [esi+680], 100
        jmp[ReturnResourcesCanceledBuilding_JmpBack]
    }
}


static unsigned long FixIonFieldResist_Jmp = 0x004BB43C;
static unsigned long FixIonFieldResist_JmpBack = FixIonFieldResist_Jmp + 6;
__declspec(naked) void inline FixIonFieldResist()
{
    __asm {
        lea ecx, [ecx+ecx*4]
        lea ecx, [ecx+ecx*4]
        shl ecx, 1
        mov edx, eax
        mov eax, ecx
        mov ecx, edx
        xor edx, edx
        div ecx
        mov ecx, eax
        jmp[FixIonFieldResist_JmpBack]
    }
}

//static unsigned long ScoutDetectInvis_Jmp = 0x0041C4AA;
//static unsigned long ScoutDetectInvis_JmpBack = ScoutDetectInvis_Jmp + 6;
//__declspec(naked) void inline ScoutDetectInvis()
//{
//    __asm {
//        add     eax, 0x0FFFFFFFB
//        cmp     eax, 32
//
//        jmp[ScoutDetectInvis_JmpBack]
//    }
//}

static unsigned long ChangeGameVersion_Jmp = 0x005B324F;
static unsigned long ChangeGameVersion_JmpBack = ChangeGameVersion_Jmp + 5;
__declspec(naked) void inline ChangeGameVersion()
{
    __asm {
        mov eax, 0x00807DD5
        mov dword ptr [eax], 0x01030000 // 0x0101002A standart current
        mov eax, [eax]
        jmp[ChangeGameVersion_JmpBack]
    }
}


const size_t CallJmpSize = 5;

enum ERegisterName : uint8_t
{
    RN_EAX = 0x00,
    RN_ECX = 0x01,
    RN_EDX = 0x02,
    RN_EBX = 0x03,
    RN_ESP = 0x04,
    RN_EBP = 0x05,
    RN_ESI = 0x06,
    RN_EDI = 0x07,
};

static inline size_t WritePatch(void *addr, const void *data, size_t size)
{
    const volatile char *volatile src = (const char *)data;
    volatile char *volatile dst = (char *)addr;
    for (size_t i = 0; i < size; i++)
        dst[i] = src[i];
    return size;
}

static inline size_t WriteFill(void *addr, uint8_t value, size_t size)
{
    volatile char *volatile dst = (char *)addr;
    volatile uint8_t val = value;
    for (size_t i = 0; i < size; i++)
        dst[i] = val;
    return size;
}

template <size_t Size>
static inline size_t WritePatch(void *addr, const uint8_t (&data)[Size])
{
    return WritePatch(addr, data, Size);
}

// clang-format off
static inline char     *volatile &GetVarStr    (void *addr) { return *((char    *volatile *)addr); }
static inline void     *volatile &GetVarPtr    (void *addr) { return *((void    *volatile *)addr); }
static inline float     volatile &GetVarFloat  (void *addr) { return *((float    volatile *)addr); }
static inline double    volatile &GetVarDouble (void *addr) { return *((double   volatile *)addr); }
static inline int32_t   volatile &GetVarI32    (void *addr) { return *((int32_t  volatile *)addr); }
static inline uint32_t  volatile &GetVarU32    (void *addr) { return *((uint32_t volatile *)addr); }
static inline int16_t   volatile &GetVarI16    (void *addr) { return *((int16_t  volatile *)addr); }
static inline uint16_t  volatile &GetVarU16    (void *addr) { return *((uint16_t volatile *)addr); }
static inline int8_t    volatile &GetVarI8     (void *addr) { return *((int8_t   volatile *)addr); }
static inline uint8_t   volatile &GetVarU8     (void *addr) { return *((uint8_t  volatile *)addr); }
static inline int8_t    volatile &GetVarSByte  (void *addr) { return *((int8_t   volatile *)addr); }
static inline uint8_t   volatile &GetVarByte   (void *addr) { return *((uint8_t  volatile *)addr); }

static inline char      *ReadStr      (const void *addr) { return GetVarStr    ((void*)addr); }
static inline void      *ReadPtr      (const void *addr) { return GetVarPtr    ((void*)addr); }
static inline float      ReadFloat    (const void *addr) { return GetVarFloat  ((void*)addr); }
static inline double     ReadDouble   (const void *addr) { return GetVarDouble ((void*)addr); }
static inline int32_t    ReadI32      (const void *addr) { return GetVarI32    ((void*)addr); }
static inline uint32_t   ReadU32      (const void *addr) { return GetVarU32    ((void*)addr); }
static inline int16_t    ReadI16      (const void *addr) { return GetVarI16    ((void*)addr); }
static inline uint16_t   ReadU16      (const void *addr) { return GetVarU16    ((void*)addr); }
static inline int8_t     ReadI8       (const void *addr) { return GetVarI8     ((void*)addr); }
static inline uint8_t    ReadU8       (const void *addr) { return GetVarU8     ((void*)addr); }
static inline int8_t     ReadSByte    (const void *addr) { return GetVarI8     ((void*)addr); }
static inline uint8_t    ReadByte     (const void *addr) { return GetVarU8     ((void*)addr); }

static inline size_t     WriteCharPtr (void *addr, const char  *value) { return WritePatch(addr, &value, sizeof(value)); }
static inline size_t     WritePtr     (void *addr, const void  *value) { return WritePatch(addr, &value, sizeof(value)); }
static inline size_t     WriteFloat   (void *addr, float        value) { return WritePatch(addr, &value, sizeof(value)); }
static inline size_t     WriteDouble  (void *addr, double       value) { return WritePatch(addr, &value, sizeof(value)); }
static inline size_t     WriteI32     (void *addr, int32_t      value) { return WritePatch(addr, &value, sizeof(value)); }
static inline size_t     WriteU32     (void *addr, uint32_t     value) { return WritePatch(addr, &value, sizeof(value)); }
static inline size_t     WriteI16     (void *addr, int16_t      value) { return WritePatch(addr, &value, sizeof(value)); }
static inline size_t     WriteU16     (void *addr, uint16_t     value) { return WritePatch(addr, &value, sizeof(value)); }
static inline size_t     WriteI8      (void *addr, int8_t       value) { return WritePatch(addr, &value, sizeof(value)); }
static inline size_t     WriteU8      (void *addr, uint8_t      value) { return WritePatch(addr, &value, sizeof(value)); }
static inline size_t     WriteSByte   (void *addr, int8_t       value) { return WritePatch(addr, &value, sizeof(value)); }
static inline size_t     WriteByte    (void *addr, uint8_t      value) { return WritePatch(addr, &value, sizeof(value)); }

static inline size_t WriteBytes(
    void *addr,
    int b0 = -1, int b1 = -1, int b2 = -1, int b3 = -1, int b4 = -1,
    int b5 = -1, int b6 = -1, int b7 = -1, int b8 = -1, int b9 = -1)
{
    int data[] = { b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, -1 };
    size_t count;
    for (count = 0; data[count] >= 0 && data[count] <= 255; count++)
        WriteByte((uint8_t *)addr + count, (uint8_t)(data[count]));
    return count;
}
// clang-format on

// For call/jmp instructions
static inline int32_t AddrDelta(const void *from, const void *to, int instrSize)
{
    auto offset = (intptr_t)((const char *)to - (const char *)from - instrSize);
    assert(offset >= INT32_MIN && offset <= INT32_MAX);
    return (int32_t)offset;
}

constexpr unsigned long Five_DetourSize = 5;

bool inline ApplyDetour(unsigned long origin, unsigned long length, unsigned long destination)
{
    HANDLE currentProcess = GetCurrentProcess();
    unsigned long *originPointer = (unsigned long *)origin;

    unsigned long previousProtection = 0;
    if (VirtualProtectEx(currentProcess, originPointer, length, PAGE_EXECUTE_READWRITE,
                         &previousProtection) == FALSE)
        return false;

    // Hard length limit of 10...
    unsigned char bytesToCopy[] = { 0xE9, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
    if (sizeof(bytesToCopy) < length)
        return false;

    unsigned long jumpDistance = destination - origin - 5;

    for (int i = 0; i < 4; ++i)
    {
        unsigned char *destByte = (unsigned char *)&jumpDistance;
        bytesToCopy[i + 1] = *(destByte + i);
    }

    SIZE_T writtenBytes = 0;
    if (WriteProcessMemory(currentProcess, originPointer, bytesToCopy, length, &writtenBytes) ==
        FALSE)
        return false;

    FlushInstructionCache(currentProcess, originPointer, length);

    if (VirtualProtectEx(currentProcess, originPointer, length, previousProtection,
                         &previousProtection) == FALSE)
        return false;

    return true;
}

static inline size_t WriteNops(void *addr, size_t count)
{
    return WriteFill(addr, 0x90, count);
}

static inline size_t WriteCall(void *addr, const void *from, const void *to)
{
    return WriteU8(addr, 0xE8) + WriteI32((char *)addr + 1, AddrDelta(from, to, CallJmpSize));
}

static inline size_t WriteJump(void *addr, const void *from, const void *to)
{
    return WriteU8(addr, 0xE9) + WriteI32((char *)addr + 1, AddrDelta(from, to, CallJmpSize));
}

static inline size_t WriteCall(void *addr, const void *to)
{
    return WriteCall(addr, addr, to);
}

static inline size_t WriteJump(void *addr, const void *to)
{
    return WriteJump(addr, addr, to);
}

static inline size_t WriteJumpSized(unsigned long addr, unsigned long length, unsigned long to)
{
    return ApplyDetour(addr, length, to);
}

static inline size_t WritePush(void *addr, uint32_t value)
{
    return WriteU8(addr, 0x68) + WriteU32((char *)addr + 1, value);
}

static inline size_t WriteCall(void *addr, ERegisterName reg)
{
    return WriteBytes(addr, 0xFF, 0xD0 + reg);
}

static inline size_t WriteJump(void *addr, ERegisterName reg)
{
    return WriteBytes(addr, 0xFF, 0xE0 + reg);
}

static inline size_t WritePush(void *addr, ERegisterName reg)
{
    return WriteByte(addr, 0x50 + reg);
}

static inline size_t WritePop(void *addr, ERegisterName reg)
{
    return WriteByte(addr, 0x58 + reg);
}

static inline size_t WriteMov(void *addr, ERegisterName reg, uint32_t value)
{
    return WriteU8(addr, 0xB8 + reg) + WriteU32((char *)addr + 1, value);
}

struct SPatchChunk
{
    uint8_t *Addr;
    std::vector<uint8_t> Data;

    SPatchChunk(void *addr, const void *data, size_t size)
        : Addr((uint8_t *)addr)
        , Data((uint8_t *)data, (uint8_t *)data + size)
    {
    }

    template <size_t Size>
    SPatchChunk(void *addr, const uint8_t (&data)[Size])
        : Addr((uint8_t *)addr)
        , Data(data, data + Size)
    {
    }

    SPatchChunk(void *addr, const std::vector<uint8_t> &data)
        : Addr((uint8_t *)addr)
        , Data(data)
    {
    }
};

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4512) // assignment operator could not be generated
#endif

struct SPatch
{
    const char *const Name;
    std::vector<SPatchChunk> Chunks;

    SPatch(const char *name = "")
        : Name(name)
        , _finished(false)
    {
    }

    SPatch(void *addr)
        : Name("")
        , _finished(false)
    {
        SetAddr(addr);
    }

    SPatch(const char *name, void *addr)
        : Name(name)
        , _finished(false)
    {
        SetAddr(addr);
    }

    void Finish()
    {
        if (!_finished)
        {
            TryMergeLastChunk();
            for (auto it = Chunks.begin(); it != Chunks.end(); ++it)
                it->Data.shrink_to_fit();
            _finished = true;
        }
    }

    uint8_t *GetAddr()
    {
        assert(!Chunks.empty());
        auto &chunk = Chunks.back();
        return chunk.Addr + chunk.Data.size();
    }

    void SetAddr(void *addr)
    {
        assert(!_finished);
        if (Chunks.empty() || addr != GetAddr())
        {
            TryMergeLastChunk();
            char nothing = 0;
            Chunks.push_back(SPatchChunk(addr, &nothing, 0));
        }
    }

    size_t Skip(size_t size)
    {
        SetAddr(GetAddr() + size);
        return size;
    }

    size_t Write(uint8_t *addr, const void *data, size_t size)
    {
        assert(!_finished);
        if (!Chunks.empty() && addr == GetAddr())
        {
            auto &chunk = Chunks.back();
            size_t prevSize = chunk.Data.size();
            chunk.Data.resize(prevSize + size);
            memcpy(&chunk.Data[prevSize], data, size);
        }
        else
        {
            TryMergeLastChunk();
            Chunks.push_back(SPatchChunk(addr, data, size));
        }
        return size;
    }

    size_t Write(void *addr, const void *data, size_t size)
    {
        return Write((uint8_t *)addr, data, size);
    }

    size_t Write(const void *data, size_t size) { return Write(GetAddr(), data, size); }

    template <size_t Size>
    size_t Write(void *addr, const uint8_t (&data)[Size])
    {
        return Write(addr, data, Size);
    }

    template <size_t Size>
    size_t Write(const uint8_t (&data)[Size])
    {
        return Write(data, Size);
    }

    size_t Write(void *addr, const std::vector<uint8_t> &data)
    {
        return Write(addr, &data[0], data.size());
    }

    size_t Write(const std::vector<uint8_t> &data) { return Write(&data[0], data.size()); }

    /* LPVOID InjectASM(void *addr, size_t size)
    {
        void* alloc_addr = VirtualAlloc(NULL, size, MEM_RESERVE, PAGE_NOACCESS);
        memset(addr, code, size)
    } */



    size_t WriteBytes(void *addr, int b0 = -1, int b1 = -1, int b2 = -1, int b3 = -1, int b4 = -1,
                      int b5 = -1, int b6 = -1, int b7 = -1, int b8 = -1, int b9 = -1)
    {
        int data[] = { b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, -1 };
        size_t count;
        for (count = 0; data[count] >= 0 && data[count] <= 255; count++)
            WriteByte((uint8_t *)addr + count, (uint8_t)(data[count]));
        return count;
    }

    size_t WriteBytes(int b0 = -1, int b1 = -1, int b2 = -1, int b3 = -1, int b4 = -1, int b5 = -1,
                      int b6 = -1, int b7 = -1, int b8 = -1, int b9 = -1)
    {
        return WriteBytes(GetAddr(), b0, b1, b2, b3, b4, b5, b6, b7, b8, b9);
    }

    // clang-format off
    size_t WriteCharPtr (void *addr, const char  *value) { return Write(addr, &value, sizeof(value)); }
    size_t WritePtr     (void *addr, const void  *value) { return Write(addr, &value, sizeof(value)); }
    size_t WriteFloat   (void *addr, float        value) { return Write(addr, &value, sizeof(value)); }
    size_t WriteDouble  (void *addr, double       value) { return Write(addr, &value, sizeof(value)); }
    size_t WriteI32     (void *addr, int32_t      value) { return Write(addr, &value, sizeof(value)); }
    size_t WriteU32     (void *addr, uint32_t     value) { return Write(addr, &value, sizeof(value)); }
    size_t WriteI16     (void *addr, int16_t      value) { return Write(addr, &value, sizeof(value)); }
    size_t WriteU16     (void *addr, uint16_t     value) { return Write(addr, &value, sizeof(value)); }
    size_t WriteI8      (void *addr, int8_t       value) { return Write(addr, &value, sizeof(value)); }
    size_t WriteU8      (void *addr, uint8_t      value) { return Write(addr, &value, sizeof(value)); }
    size_t WriteSByte   (void *addr, int8_t       value) { return Write(addr, &value, sizeof(value)); }
    size_t WriteByte    (void *addr, uint8_t      value) { return Write(addr, &value, sizeof(value)); }

    size_t WriteCharPtr (const char  *value) { return Write(&value, sizeof(value)); }
    size_t WritePtr     (const void  *value) { return Write(&value, sizeof(value)); }
    size_t WriteFloat   (float        value) { return Write(&value, sizeof(value)); }
    size_t WriteDouble  (double       value) { return Write(&value, sizeof(value)); }
    size_t WriteI32     (int32_t      value) { return Write(&value, sizeof(value)); }
    size_t WriteU32     (uint32_t     value) { return Write(&value, sizeof(value)); }
    size_t WriteI16     (int16_t      value) { return Write(&value, sizeof(value)); }
    size_t WriteU16     (uint16_t     value) { return Write(&value, sizeof(value)); }
    size_t WriteI8      (int8_t       value) { return Write(&value, sizeof(value)); }
    size_t WriteU8      (uint8_t      value) { return Write(&value, sizeof(value)); }
    size_t WriteSByte   (int8_t       value) { return Write(&value, sizeof(value)); }
    size_t WriteByte    (uint8_t      value) { return Write(&value, sizeof(value)); }
    // clang-format on

    size_t WriteFill(void *addr, uint8_t value, size_t size)
    {
        for (size_t i = 0; i < size; i++)
            WriteByte((char *)addr + i, value);
        return size;
    }

    size_t WriteNops(void *addr, size_t count) { return WriteFill(addr, 0x90, count); }

    size_t WriteZeros(void *addr, size_t count) { return WriteFill(addr, 0x00, count); }

    size_t WriteNopsToAddr(void *addr, const void *to)
    {
        assert(addr < to);
        return WriteNops(addr, (char *)to - (char *)addr);
    }

    size_t WriteCall(void *from, const void *to)
    {
        return WriteU8(from, 0xE8) + WriteI32((char *)from + 1, AddrDelta(from, to, CallJmpSize));
    }

    size_t WriteJump(void *from, const void *to)
    {
        return WriteU8(from, 0xE9) + WriteI32((char *)from + 1, AddrDelta(from, to, CallJmpSize));
    }

    static inline size_t WriteJumpSized(unsigned long addr, unsigned long length, unsigned long to)
    {
        return ApplyDetour(addr, length, to);
    }

    size_t WritePush(void *addr, uint32_t value)
    {
        return WriteU8(addr, 0x68) + WriteU32((char *)addr + 1, value);
    }

    size_t WriteCall(void *addr, ERegisterName reg) { return WriteBytes(addr, 0xFF, 0xD0 + reg); }

    size_t WriteJump(void *addr, ERegisterName reg) { return WriteBytes(addr, 0xFF, 0xE0 + reg); }

    size_t WritePush(void *addr, ERegisterName reg) { return WriteU8(addr, 0x50 + reg); }

    size_t WritePop(void *addr, ERegisterName reg) { return WriteU8(addr, 0x58 + reg); }

    size_t WriteMov(void *addr, ERegisterName reg, uint32_t value)
    {
        return WriteU8(addr, 0xB8 + reg) + WriteU32((char *)addr + 1, value);
    }

    // clang-format off
    size_t WriteFill(uint8_t value, size_t size)       { return WriteFill(GetAddr(), value, size); }
    size_t WriteNops(size_t count)                     { return WriteNops(GetAddr(), count); }
    size_t WriteNopsToAddr(const void *to)             { return WriteNopsToAddr(GetAddr(), to); }
    size_t WriteCall(const void *to)                   { return WriteCall(GetAddr(), to); }
    size_t WriteJump(const void *to)                   { return WriteJump(GetAddr(), to); }
    size_t WritePush(uint32_t value)                   { return WritePush(GetAddr(), value); }
    size_t WriteCall(ERegisterName reg)                { return WriteCall(GetAddr(), reg); }
    size_t WriteJump(ERegisterName reg)                { return WriteJump(GetAddr(), reg); }
    size_t WritePush(ERegisterName reg)                { return WritePush(GetAddr(), reg); }
    size_t WritePop(ERegisterName reg)                 { return WritePop(GetAddr(), reg); }
    size_t WriteMov(ERegisterName reg, uint32_t value) { return WriteMov(GetAddr(), reg, value); }
    // clang-format on

private:
    bool _finished;

    void TryMergeLastChunk()
    {
        if (Chunks.size() < 2)
            return;

        auto &lastChunk = Chunks.back();
        if (lastChunk.Data.empty())
        {
            Chunks.pop_back();
            return;
        }

        for (auto it = Chunks.begin(); &(*it) != &lastChunk; ++it)
        {
            if (it->Addr <= lastChunk.Addr + lastChunk.Data.size() &&
                it->Addr + it->Data.size() >= lastChunk.Addr)
            {
                if (it->Addr > lastChunk.Addr)
                    std::swap(*it, lastChunk);

                auto extraSize = (lastChunk.Addr + lastChunk.Data.size()) -
                                 (it->Addr + it->Data.size());
                if (extraSize > 0)
                    it->Data.resize(it->Data.size() + extraSize);
                memcpy(&it->Data[lastChunk.Addr - it->Addr], &lastChunk.Data[0],
                       lastChunk.Data.size());
                Chunks.pop_back();
                return;
            }
        }
    }
};

#ifdef _MSC_VER
#pragma warning(pop)
#endif

} // namespace Patcher
