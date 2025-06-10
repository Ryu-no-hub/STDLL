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

//WCHAR Buffer[MAX_PATH];
//auto result = GetCurrentDirectoryW(MAX_PATH, Buffer);
//
//std::wstring FileDirectory(Buffer);
//std::wstring full_path = FileDirectory + L"\\plugins\\config.ini";
//static LPCWSTR ini_file = full_path.c_str();

    
static auto game_mode_ptr = (BYTE *)0x00808783; // 2 - singleplayer, 3 - standard muliplayer
static auto game_submode_ptr = (DWORD *)0x00808784;
static char *player_name_ptr = (char *)0x00807DDD;

static auto host_flag = (DWORD *)0x007F5866;

static wchar_t *convertCharArrayToLPCWSTR(const char *charArray)
{
    wchar_t *wString = new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
    return wString;
}

static LPCWSTR InitConfig()
{
    CHAR Buffer[MAX_PATH];
    CHAR FullPath[MAX_PATH];
    struct _WIN32_FIND_DATAA FindFileData;

    auto result = GetCurrentDirectoryA(MAX_PATH, Buffer);
    if (result)
    {
        lstrcatA(Buffer, "\\plugins\\*.ini");
        auto hFind = FindFirstFileA(Buffer, &FindFileData);
        if (hFind == INVALID_HANDLE_VALUE)
        {
            FullPath[0] = ' ';
            FullPath[1] = '\0';
        }
        else
        {
            GetCurrentDirectoryA(MAX_PATH, FullPath);
            lstrcatA(FullPath, "\\plugins\\");
            lstrcatA(FullPath, FindFileData.cFileName);
            FindClose(hFind);
        }
    }
 
    return convertCharArrayToLPCWSTR(FullPath);
}
static auto ini_file = InitConfig();

void inline AnnounceGameHost()
{
    std::string player_name(player_name_ptr);

    HINTERNET hsession = WinHttpOpen(NULL, WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME,
                                     WINHTTP_NO_PROXY_BYPASS, 0);
    if (*game_mode_ptr == 3 || ((*game_mode_ptr == 1) & (*game_submode_ptr == 3)))
    {
        if (hsession)
        {
            HINTERNET hconnect = WinHttpConnect(hsession, L"discord.com",
                                                INTERNET_DEFAULT_HTTPS_PORT, 0);
            if (hconnect)
            {
                HINTERNET hRequest = WinHttpOpenRequest(
                    //hconnect, L"POST", L"/api/v10/channels/919149425182523426/messages", NULL,
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
    if ((*game_mode_ptr == 3 || ((*game_mode_ptr == 1) & (*game_submode_ptr == 3))) && *host_flag)
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
    if ((*game_mode_ptr == 3 || ((*game_mode_ptr == 1) & (*game_submode_ptr == 3))) && *host_flag)
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
    if (*game_mode_ptr == 3 || ((*game_mode_ptr == 1) & (*game_submode_ptr == 3)))
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

static BYTE autosave_mode = GetPrivateProfileInt(L"Plugins", L"Autosave", FALSE, ini_file);
bool inline AutosaveCheck()
{
    if (autosave_mode == 1)
        return (*game_mode_ptr == 3 && *host_flag);
    else // == 2
        return (*host_flag);
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
    __asm cmp al, 7;
    __asm je host;
    __asm cmp al, 12;
    __asm je host;
    __asm mov eax, [host_flag]
    __asm mov dword ptr ss : [eax], 0;
    __asm jmp skip;

    __asm host:;
    __asm mov eax, [host_flag]
    __asm mov dword ptr ss : [eax], 1;

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
        mov ebx, 0x007F5866
        mov ebx,[ebx]
        
        //mov dword ptr ss:[esi], 0x0079059C
        mov dword ptr [esi], 0x0079059C
        rep stosd
    
        mov dword ptr ss:[0x007F5866], ebx
        //mov dword ptr [0x007F5866], ebx
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

static int energy_mine_amount_1 = GetPrivateProfileInt(L"Economics", L"EnergyMineAmount_1", 5, ini_file);
static int energy_mine_amount_2 = GetPrivateProfileInt(L"Economics", L"EnergyMineAmount_2", 5, ini_file);
static int energy_mine_amount_1_neg = -energy_mine_amount_1;
static int energy_mine_amount_2_neg = -energy_mine_amount_2;
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
    jz stock
    xor eax, eax
    add eax, energy_mine_amount_2_neg
    jmp originalcode

    stock:
    xor eax, eax
    add eax, energy_mine_amount_1_neg

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
    __asm add edi, energy_mine_amount_2;
    __asm jmp originalcode;

    __asm stock:;
    __asm xor edi, edi;
    __asm add edi, energy_mine_amount_1;

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
    __asm mov edi, 2;
    __asm mov[esi + 0x000000B7], edi;

    __asm jmp[Transport_waiting_mine_distance_JmpBack];
}

static unsigned long Transport_waiting_mine_distance2_Jmp = 0x00469863;
static unsigned long Transport_waiting_mine_distance2_JmpBack = Transport_waiting_mine_distance2_Jmp + 6;
__declspec(naked) void inline Transport_waiting_mine_distance2()
{
    __asm {

        push eax
        push ecx

        mov edi, [esi+36]
        mov eax, 0x00808AF4
        sub eax, 156
        xor ecx, ecx

        loopy:
        add eax, 156
        mov cl, [eax]
        cmp edi, ecx
        jne loopy

        mov al, byte ptr [eax+2]
        and eax, 0xFF
        test eax, eax   
        
        jz ai_player
        mov edi, 1
        jmp exitt

        ai_player:
        mov edi, 3

        exitt:
        pop ecx
        pop eax
        mov[esi + 0x000000B7], edi;
        jmp[Transport_waiting_mine_distance2_JmpBack];
    }
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

static unsigned long TransportDepotDecision_Jmp = 0x004438BB;
static unsigned long TransportDepotDecision_JmpBack = TransportDepotDecision_Jmp + 5;
__declspec(naked) void inline TransportDepotDecision()
{
    __asm {
        add eax, edx

        push eax
        push ecx
        push edx

        mov eax, [ebp-4]
        mov edx, [ebp+8]
        mov ecx, [ebp-0x88]
        push 1
        push eax
        push edx
        mov eax, 0x004028BA // STAllPlayersC::GetObjPtr(int,ushort,int)
        call eax

        mov eax, [eax+36]
        mov edx, 0x00808AF4
        sub edx, 156
        xor ecx, ecx

        loopy:
        //cmp edx, 0x00808FD4
        //ja outt
        add edx, 156
        mov cl, [edx]
        cmp eax, ecx
        jne loopy

        mov dl, byte ptr [edx+2]
        and edx, 0xFF
        test edx, edx
        //outt:        

        pop edx
        pop ecx
        pop eax
        
        jz ai_player
        cmp ecx, 100
        jmp exitt

        ai_player:
        cmp eax, 100

        exitt:
        jmp[TransportDepotDecision_JmpBack]
    }
}

static unsigned long TransportDepotDecision2_Jmp = 0x004438E5;
static unsigned long TransportDepotDecision2_JmpBack = TransportDepotDecision2_Jmp + 5;
__declspec(naked) void inline TransportDepotDecision2()
{
    __asm {
        add eax, edx

        push eax
        push ecx
        push edx

        mov eax, [ebp-4]
        mov edx, [ebp+8]
        mov ecx, [ebp-0x88]
        push 1
        push eax
        push edx
        mov eax, 0x004028BA // STAllPlayersC::GetObjPtr(int,ushort,int)
        call eax

        mov eax, [eax+36]
        mov edx, 0x00808AF4
        sub edx, 156
        xor ecx, ecx

        loopy:
        //cmp edx, 0x00808FD4
        //ja outt
        add edx, 156
        mov cl, [edx]
        cmp eax, ecx
        jne loopy

        mov dl, byte ptr [edx+2]
        and edx, 0xFF
        test edx, edx
        //outt:       

        pop edx
        pop ecx
        pop eax
        
        jz ai_player
        cmp ecx, 100
        jmp exitt

        ai_player:
        cmp eax, 100

        exitt:
        jmp[TransportDepotDecision2_JmpBack]
    }
}


static unsigned long DontChangeInterfaceName_Jmp = 0x0065588C;
static unsigned long DontChangeInterfaceName_JmpBack = DontChangeInterfaceName_Jmp + 5;
__declspec(naked) void inline DontChangeInterfaceName()
{
    __asm {
        mov ecx, ebx
        pop edx

        exitt:
        jmp[DontChangeInterfaceName_JmpBack]
    }
}

static int bhe_expansion_rate_1 = GetPrivateProfileInt(L"BHE_Shell", L"ExpansionRate_1", 7, ini_file);
static int bhe_expansion_rate_2 = GetPrivateProfileInt(L"BHE_Shell", L"ExpansionRate_2", 7, ini_file);
static unsigned long UpgBHEExpansionRate_Jmp = 0x005F4CA7;
static unsigned long UpgBHEExpansionRate_JmpBack = UpgBHEExpansionRate_Jmp + 10;
__declspec(naked) void inline UpgBHEExpansionRate()
{
    __asm {
        push 124
        push[esi + 0x0000051]
        mov eax, 0x0040186B
        call eax
        test ax, ax
        jle originalcode
        mov eax, bhe_expansion_rate_2
        mov dword ptr [esi + 0x125], eax
        //test ecx, ecx
        test ebx, ebx
        jmp exitt

        originalcode:
        mov eax, bhe_expansion_rate_1
        mov dword ptr [esi + 0x125], eax
        //test ecx, ecx
        test ebx, ebx

        exitt:
        jmp[UpgBHEExpansionRate_JmpBack]
    }
}

static int fall_Speed_1 = GetPrivateProfileInt(L"BHE_Shell", L"FallSpeed_1", 25, ini_file);
static int fall_Speed_2 = GetPrivateProfileInt(L"BHE_Shell", L"FallSpeed_2", 25, ini_file);
static int fall_Speed_1_neg = -fall_Speed_1;
static int fall_Speed_2_neg = -fall_Speed_2;
static unsigned long UpgBHESpeed_Jmp = 0x005F4C93;
static unsigned long UpgBHESpeed_JmpBack = UpgBHESpeed_Jmp + 10;
__declspec(naked) void inline UpgBHESpeed()
{
    __asm {
        push 124
        push[esi + 0x0000051]
        mov eax, 0x0040186B
        call eax
        test ax, ax
        jz originalcode
        mov eax, fall_Speed_2_neg
        mov dword ptr [esi + 0x121], eax
        //test ecx, ecx
        jmp exitt

        originalcode:
        mov eax, fall_Speed_1_neg
        mov dword ptr [esi + 0x121], eax // same

        exitt:
        jmp[UpgBHESpeed_JmpBack]
    }
}

static int particles_amount_1 = GetPrivateProfileInt(L"BHE_Shell", L"ParticlesAmount_1", 30, ini_file);
static int particles_amount_2 = GetPrivateProfileInt(L"BHE_Shell", L"ParticlesAmount_2", 30, ini_file);
static unsigned long UpgBHEDotsAmount_Jmp = 0x005F4C56;
static unsigned long UpgBHEDotsAmount_JmpBack = UpgBHEDotsAmount_Jmp + 6;
__declspec(naked) void inline UpgBHEDotsAmount()
{
    __asm {
        push 124
        push[esi + 0x0000051]
        mov eax, 0x0040186B
        call eax
        test ax, ax
        jz originalcode
        mov eax, particles_amount_2
        jmp outt

        originalcode:
        mov eax, particles_amount_1

        outt:
        mov dword ptr [ebp + 0x18], eax
        fild dword ptr[ebp + 0x18]
        mov eax, [ebp + 0x18]
        //mov edx, [ebp - 0x4]
        mov ecx, esi

        jmp[UpgBHEDotsAmount_JmpBack]
    }
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

static unsigned long TargetingNoHpPriority_Jmp = 0x00489BEA;
static unsigned long TargetingNoHpPriority_JmpBack = TargetingNoHpPriority_Jmp + 5;
__declspec(naked) void inline TargetingNoHpPriority()
{
    __asm {
        xor eax,eax
        //sar eax,1
        //neg eax
        lea ebx,[edi+eax]
        jmp[TargetingNoHpPriority_JmpBack]
    }
}

//static unsigned long TargetingNoHpPriority_Jmp = 0x00489BEA;
//static unsigned long TargetingNoHpPriority_JmpBack = TargetingNoHpPriority_Jmp + 5;
//__declspec(naked) void inline TargetingNoHpPriority()
//{
//    __asm {
//        shl eax,2
//        neg eax
//        add eax, 1
//        lea ebx, [edi+eax]
//        xor eax, eax
//        jmp[TargetingNoHpPriority_JmpBack]
//    }
//}

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
    __asm {
        mov esi, [eax * 4 + 0x007E09DC];
        sar esi, 1;
        jmp[RecycleSiliconHalfCoeff_JmpBack]
    }
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
static unsigned long RecycleContainerPushPlayer_JmpBack = RecycleContainerPushPlayer_Jmp + 12;
__declspec(naked) void inline RecycleContainerPushPlayer()
{
    __asm {
        mov ecx, [ecx+0x24]
        push ecx
        lea eax, [edx+esi]
        lea edx, [eax+edx*2]
        lea eax, [edx+edi]
        mov edx, eax
        push eax

        mov eax, 0x66666667
        imul edx
        sar edx, 1
        pop eax
        sub eax, edx
        sub eax, edx

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
__declspec(naked) void inline AcousticMinesCheck() // BROKEN, 74 - Обнаружитель невидимок
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
        cmp [ebx+0x6F7], 9
        je cyber
        cmp [ebx+0x6F7], 21
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
        push edx
        push ecx
        push 149
        push [ebx+0x24]
        mov eax, 0x0040186B
        call eax
        test ax, ax        
        pop ecx
        pop edx
        jz stock

        push 402
        jmp originalcode

        stock:
        push 201

        originalcode:
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


//static unsigned long ChangeSubsRangeStd_Jmp = 0x0044F7F7;
//static unsigned long ChangeSubsRangeStd_JmpBack = ChangeSubsRangeStd_Jmp + 7;
//__declspec(naked) void inline ChangeSubsRangeStd()
//{
//    __asm {
//        push eax
//        mov eax,[ebx+1783]
//        cmp eax,2 //6
//        je range_6
//        cmp eax,13
//        je range_6
//        cmp eax,30
//        je range_6
//        jmp outt
//
//        range_6:
//        mov WORD PTR [ebx+0x814], 0x4B6
//        mov WORD PTR [ebx+0x816], 6
//        mov WORD PTR [ebx+1802], 6
//
//        outt:
//        //mov byte ptr [ebx+1129],0 //dodge distance
//        pop eax
//        jmp dword ptr [eax*4+0x0045B044]
//    }
//}

static WORD Sentinel_1_range = GetPrivateProfileInt(L"Sentinel", L"Range", 5, ini_file);
static WORD Hunter_2_range = GetPrivateProfileInt(L"Hunter", L"Range", 5, ini_file);
static WORD Cruiser_3_range = GetPrivateProfileInt(L"Cruiser", L"Range", 5, ini_file);
static WORD Bomber_4_range = GetPrivateProfileInt(L"Bomber", L"Range", 5, ini_file);
static WORD Minelayer_5_range = GetPrivateProfileInt(L"Minelayer", L"Range", 5, ini_file);
static WORD Marauder_6_range = GetPrivateProfileInt(L"Marauder", L"Range", 5, ini_file);
static WORD Terminator_10_range = GetPrivateProfileInt(L"Terminator", L"Range", 5, ini_file);
static WORD Liberator_11_range = GetPrivateProfileInt(L"Liberator", L"Range", 5, ini_file);
static WORD Flagship_WS_38_range = GetPrivateProfileInt(L"Flagship_WS", L"Range", 5, ini_file);

static WORD Fighter_13_range = GetPrivateProfileInt(L"Fighter", L"Range", 5, ini_file);
static WORD Destroyer_14_range = GetPrivateProfileInt(L"Destroyer", L"Range", 5, ini_file);
static WORD Heavy_Cruiser_15_range = GetPrivateProfileInt(L"Heavy_Cruiser", L"Range", 5, ini_file);
static WORD Invader_16_range = GetPrivateProfileInt(L"Invader", L"Range", 5, ini_file);
static WORD Defender_17_range = GetPrivateProfileInt(L"Defender", L"Range", 5, ini_file);
static WORD Raider_18_range = GetPrivateProfileInt(L"Raider", L"Range", 5, ini_file);
static WORD Phantom_22_range = GetPrivateProfileInt(L"Phantom", L"Range", 5, ini_file);
static WORD Avenger_23_range = GetPrivateProfileInt(L"Avenger", L"Range", 5, ini_file);
static WORD Flagship_BO_39_range = GetPrivateProfileInt(L"Flagship_BO", L"Range", 5, ini_file);

static WORD Paralizator_28_range = GetPrivateProfileInt(L"Paralizator", L"Range", 5, ini_file);
static WORD Skat_30_range = GetPrivateProfileInt(L"Skat", L"Range", 5, ini_file);
static WORD Dreadnaught_31_range = GetPrivateProfileInt(L"Dreadnaught", L"Range", 5, ini_file);
static WORD Escort_32_range = GetPrivateProfileInt(L"Escort", L"Range", 5, ini_file);
static WORD Bio_Assaulter_33_range = GetPrivateProfileInt(L"Bio_Assaulter", L"Range", 5, ini_file);
static WORD Usurper_34_range = GetPrivateProfileInt(L"Usurper", L"Range", 5, ini_file);
static WORD Psi_Zond_35_range = GetPrivateProfileInt(L"Psi_Zond", L"Range", 5, ini_file);
static WORD Flagship_SI_40_range = GetPrivateProfileInt(L"Flagship_SI", L"Range", 5, ini_file);

static unsigned long ChangeSubsRange_Jmp = 0x0044F7F7;
__declspec(naked) void inline ChangeSubsRange()
{
    __asm {
        push eax
        push ecx
        push esi
        xor esi,esi
        mov cx, 201
        mov eax,[ebx+1783]
        cmp eax,1 
        je Sentinel
        cmp eax,2
        je Hunter
        cmp eax,3
        je Cruiser
        cmp eax,4
        je Bomber
        cmp eax,5
        je Minelayer
        cmp eax,6
        je Marauder
        cmp eax,10
        je Terminator
        cmp eax,11
        je Liberator
        cmp eax,38
        je Flagship_WS

        cmp eax,13
        je Fighter
        cmp eax,14
        je Destroyer
        cmp eax,15
        je Heavy_Cruiser
        cmp eax,16
        je Invader
        cmp eax,17
        je Defender
        cmp eax,18
        je Raider
        cmp eax,22
        je Phantom
        cmp eax,23
        je Avenger
        cmp eax,39
        je Flagship_BO

        cmp eax,28
        je Paralizator
        cmp eax,30
        je Skat
        cmp eax,31
        je Dreadnaught
        cmp eax,32
        je Escort
        cmp eax,33
        je Bio_Assaulter
        cmp eax,34
        je Usurper
        cmp eax,35
        je Psi_Zond
        cmp eax,40
        je Flagship_SI
        jmp no_change
        
        Sentinel:
        xor eax, eax
        mov ax, Sentinel_1_range
        jmp outt
        
        Hunter:
        xor eax, eax
        mov ax, Hunter_2_range
        jmp outt
        
        Cruiser:
        xor eax, eax
        mov ax, Cruiser_3_range
        jmp outt
        
        Bomber:
        xor eax, eax
        mov ax, Bomber_4_range
        jmp outt
        
        Minelayer:
        xor eax, eax
        mov ax, Minelayer_5_range
        jmp outt
        
        Marauder:
        xor eax, eax
        mov ax, Marauder_6_range
        jmp outt
        
        Terminator:
        xor eax, eax
        mov ax, Terminator_10_range
        jmp outt
        
        Liberator:
        xor eax, eax
        mov ax, Liberator_11_range
        jmp outt
        
        Flagship_WS:
        xor eax, eax
        mov ax, Flagship_WS_38_range
        jmp outt

        
        Fighter:
        xor eax, eax
        mov ax, Fighter_13_range
        jmp outt
        
        Destroyer:
        xor eax, eax
        mov ax, Destroyer_14_range
        jmp outt
        
        Heavy_Cruiser:
        xor eax, eax
        mov ax, Heavy_Cruiser_15_range
        jmp outt
        
        Invader:
        xor eax, eax
        mov ax, Invader_16_range
        jmp outt
        
        Defender:
        xor eax, eax
        mov ax, Defender_17_range
        jmp outt
        
        Raider:
        xor eax, eax
        mov ax, Raider_18_range
        jmp outt
        
        Phantom:
        xor eax, eax
        mov ax, Phantom_22_range
        jmp outt
        
        Avenger:
        xor eax, eax
        mov ax, Avenger_23_range
        jmp outt
        
        Flagship_BO:
        xor eax, eax
        mov ax, Flagship_BO_39_range
        jmp outt
            
        
        Paralizator:
        xor eax, eax
        mov ax, Paralizator_28_range
        jmp outt
        
        Skat:
        xor eax, eax
        mov ax, Skat_30_range
        jmp outt
        
        Dreadnaught:
        xor eax, eax
        mov ax, Dreadnaught_31_range
        jmp outt
        
        Escort:
        xor eax, eax
        mov ax, Escort_32_range
        jmp outt
        
        Bio_Assaulter:
        xor eax, eax
        mov ax, Bio_Assaulter_33_range
        jmp outt
        
        Usurper:
        xor eax, eax
        mov ax, Usurper_34_range
        jmp outt
        
        Psi_Zond:
        xor eax, eax
        mov ax, Psi_Zond_35_range
        jmp outt
        
        Flagship_SI:
        xor eax, eax
        mov ax, Flagship_SI_40_range

        outt:
        mov si, ax
        mul cx
        mov WORD PTR [ebx+0x814], ax
        mov WORD PTR [ebx+0x816], si

        no_change:
        pop esi
        pop ecx
        pop eax
        jmp dword ptr [eax*4+0x0045B044]
    }
}

static unsigned long FirstBuilderOxygen_Jmp = 0x0044EEEE; 
static unsigned long FirstBuilderOxygen_JmpBack = FirstBuilderOxygen_Jmp + 6;
__declspec(naked) void inline FirstBuilderOxygen()
{
    __asm {
        mov [ebx+1783], ecx
        cmp ecx, 12
        je contructor
        cmp ecx, 24
        je contructor
        jmp originalcode

        contructor:
        push eax
        push ecx
        push edx
        mov ecx, ebx
        push esi
        mov esi, ecx
        mov ecx, 0x007FA174
        mov ecx, [ecx]
        push 4 
        xor eax, eax
        mov al, [esi+36]
        push eax
        mov eax, 0x00404106
        call eax
        mov ecx, [esi+16]
        mov eax, [esi+36]
        xor edx,edx
        mov dl, [ecx+4397]
        cmp eax, edx
        jne outt
        mov ecx, 0x007FA174
        mov ecx, [ecx]
        push eax
        mov eax, 0x00404B8D // func_give_and_update_oxygen
        call eax

        outt:
        xor eax, eax
        pop esi
        pop edx
        pop ecx
        pop eax        

        originalcode:
        jmp[FirstBuilderOxygen_JmpBack]
    }
}

//static unsigned long SIFlagshipRange7_Jmp = 0x0044F951;
//static unsigned long SIFlagshipRange7_JmpBack = SIFlagshipRange7_Jmp + 5;
//__declspec(naked) void inline SIFlagshipRange7()
//{
//    __asm {
//        mov eax,0x1DF
//        mov WORD PTR [ebx+0x814], 0x57F
//        mov WORD PTR [ebx+0x816], 7
//        mov WORD PTR [ebx+1802], 7
//        jmp[SIFlagshipRange7_JmpBack]
//    }
//}

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
        //cmp eax,38
        //je outt
        //cmp eax,39
        //je outt
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
static unsigned long BoxCursorLoadCheck1_JmpBack = BoxCursorLoadCheck1_Jmp + 7;
__declspec(naked) void inline BoxCursorLoadCheck1()
{
    __asm {
        cmp eax,0x000001AE
        je outt
        cmp eax,0x000001A4
        je outt
        cmp eax,0x00000172
        je artifact
        jmp[BoxCursorLoadCheck1_JmpBack]
        
        artifact:
        mov ebx, [esi+1783]
        mov edx, 0x00486036
        jmp edx

        outt:
        mov eax, 0x004855F0
        jmp eax
    }
}

static unsigned long BoxCursorLoadCheck2_Jmp = 0x0048603F;
static unsigned long BoxCursorLoadCheck2_JmpBack = BoxCursorLoadCheck2_Jmp + 10;
__declspec(naked) void inline BoxCursorLoadCheck2()
{
    __asm {
        cmp dword ptr [edi+0x20],0x14
        je check_si_platf
        cmp dword ptr [edi+0x20],0x1A4
        je stay
        cmp dword ptr [edi+0x20],0x172
        je stay

        mov eax, 0x00485CAA
        jmp eax

        check_si_platf:
        mov edx, [edi]
        cmp ebx, 27
        mov ecx, edi
        je stay
        mov eax, 0x0048608A
        jmp eax
        
        stay:
        jmp[BoxCursorLoadCheck2_JmpBack]
    }
}

static unsigned long BoxCursorLoadCheck3_Jmp = 0x0048604B;
static unsigned long BoxCursorLoadCheck3_JmpBack = BoxCursorLoadCheck3_Jmp + 5;
__declspec(naked) void inline BoxCursorLoadCheck3()
{
    __asm {
        cmp ebx, 27
        mov ecx, edi
        je change_cursor
        cmp ebx, 7
        je change_cursor
        cmp ebx, 19
        je change_cursor


        mov eax, 0x0048608A
        jmp eax
        
        change_cursor:
        jmp[BoxCursorLoadCheck3_JmpBack]
    }
}

static unsigned long AlwaysShowHP_Jmp = 0x0041F3B4;
static unsigned long AlwaysShowHP_JmpBack = AlwaysShowHP_Jmp + 6;
__declspec(naked) void inline AlwaysShowHP()
{
    __asm {
        cmp dword ptr [esi], 0x7905A0
        je submarine
        
        cmp dword ptr [esi], 0x790AA0
        jne show
        cmp dword ptr [esi+1495], 100
        je originalcode
        jmp show

        submarine:
        mov eax, [esi+1810]
        cmp dword ptr [esi+1814], eax
        je originalcode

        show:
        mov dword ptr [esi+545],2

        originalcode:
        mov eax, [esi+545]
        jmp[AlwaysShowHP_JmpBack]
    }
}

static unsigned long DecreaseShowHPState_Jmp = 0x0041F521;
static unsigned long DecreaseShowHPState_JmpBack = DecreaseShowHPState_Jmp + 8;
__declspec(naked) void inline DecreaseShowHPState()
{
    __asm {
        cmp dword ptr [esi], 0x7905A0
        je submarine
        
        cmp dword ptr [esi], 0x790AA0
        jne show
        cmp dword ptr [esi+1495], 100
        je originalcode
        jmp show

        submarine:
        push eax
        mov eax, [esi+1810]
        cmp [esi+1814], eax
        pop eax
        jne show

        originalcode:
        dec eax

        show:
        pop edi
        mov dword ptr [esi+545], eax
        jmp[DecreaseShowHPState_JmpBack]
    }
}


//Shift
//static unsigned long SkipStopResetOrderMove_Move_Jmp = 0x004523B4;
static unsigned long SkipStopResetOrderMove_Move_Jmp = 0x00452EBB;
static unsigned long SkipStopResetOrderMove_Move_JmpBack = SkipStopResetOrderMove_Move_Jmp + 5;
__declspec(naked) void inline SkipStopResetOrderMove_Move()
{
    __asm {
        push eax        
        mov eax,[ebx+0x9F]
        test eax,eax
        jz outt
        cmp [eax+34],1
        pop eax
        je shift_pressed
        jmp originalcode

        shift_pressed:
        //cmp [ebx+0x508],2  // статус строительства
        //je originalcode
        //cmp [ebx+0x508],5
        //je originalcode
        pop esi
        mov eax,0x00403A44
        call eax

        // +func_with_radio_clutter
        mov edx,[ebx]
        mov ecx,ebx
        mov eax,[edx+216]
        call eax
        //

        mov eax,0
        jmp exitt

        outt:
        pop eax
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
        mov eax,[ebx+0x9F]
        test eax,eax
        jz outt
        cmp [eax+34],1
        pop eax
        je shift_pressed
        jmp originalcode



        shift_pressed:
        pop esi
        mov eax,0
        jmp exitt

        outt:
        pop eax

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
        mov eax,[ebx+0x9F]
        test eax,eax
        jz outt
        cmp [eax+34],1
        pop eax
        je shift_pressed
        jmp originalcode

        shift_pressed:
        //cmp [ebx+0x508],2  // статус строительства
        //je originalcode
        //cmp [ebx+0x508],5
        //je originalcode
        pop esi
        mov eax,0x00403A44
        call eax

        // +func_with_radio_clutter
        mov edx,[ebx]
        mov ecx,ebx
        mov eax,[edx+216]
        call eax
        //

        mov eax,0
        jmp exitt

        outt:
        pop eax
        originalcode:
        mov eax, 0x00401113
        call eax

        exitt:
        jmp[SkipStopResetOrderBuild_Build_JmpBack]
    }
}

static unsigned long EnableShiftAltInput_Jmp = 0x0071B878;
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
        //push edx
        //push 0x10
        //mov eax, 0x0085BDF0
        //call dword ptr [eax]
        //and eax,0x8000
        //test eax,eax
        //pop edx
        mov ecx,[esi+0x9F]
        test ecx,ecx
        jz outt
        cmp [ecx+34],1
        pop ecx
        //jnz shift_pressed
        je shift_pressed
        jmp originalcode

        outt:
        pop ecx

        originalcode:
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

        test eax,eax
        jz reset_order
        push edx
        mov edx,[ebx+0x0000009F] //взять текущий приказ
        test edx,edx
        jz zero
        //push eax
        //push ecx
        //push edx
        //push 0x10
        //mov eax, 0x0085BDF0
        //call dword ptr [eax]
        //and eax,0x8000
        //test eax,eax
        //pop edx
        //pop ecx
        //pop eax
        //jnz shift_pressed
        //jmp originalcode

        push eax
        mov eax,[ebx+0x9F]
        cmp [eax+34],1
        pop eax
        je shift_pressed
        //jmp originalcode
        jmp zero

        shift_pressed:
        //mov dword ptr [ebx+0xE3],1 /////добавка 27.03.2023 для начала движения в stop_move
        mov [ebx+0xE3],1 /////добавка 27.03.2023 для начала движения в stop_move
        push ebx

        go_deeper:
        mov ebx,edx
        //mov dword ptr [edx+0xC],0 //флаг отличия момента задания флага нового приказа
        mov edx,[edx+8]
        cmp edx,0xFFFFFFFF
        jne go_deeper
        mov edx,ebx
        pop ebx
        mov dword ptr [edx+8], eax //вложить приказ
        //mov dword ptr [edx+0xC],0 //флаг распаковки
        mov dword ptr [eax+0xC],0 //флаг распаковки
        pop edx
        test eax,eax
        jmp exitt

        zero:
        pop edx
        test eax,eax
        jz reset_order
        //mov dword ptr [eax+0xC],0 //флаг отличия момента задания флага нового приказа
        reset_order:
        //!!!!!
        mov dword ptr [ebx+0x0000009F],eax
        jmp exitt

        //originalcode:
        //test eax,eax
        //jz reset_order
        //mov dword ptr [eax+0xC],0 //флаг отличия момента задания флага нового приказа
        //reset_order:
        //mov dword ptr [ebx+0x0000009F],eax

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
        //mov eax,[eax+8] //достать вложенный приказ
        //cmp eax,0xFFFFFFFF     
        //jz vanilla   
        cmp [eax+34],1
        jne vanilla
        //

        cmp [esi+0x508],7
        jne area4
        mov eax,[eax+8]
        cmp eax,0xFFFFFFFF
        je vanilla   
        //mov dword ptr [eax+0xC],1
        mov dword ptr [esi+0xA7],0 // travelled
        mov dword ptr [esi+0x9F],eax //замена на вложенный приказ
        mov dword ptr [esi+0x2C4],1 //флаг нового приказа
        mov dword ptr [esi+0x30C],1 //флаг приказа строительства
        mov dword ptr [eax+34],1 //флаг распознавания шифт-приказа
        mov dword ptr [eax+0xC],1 // мой флаг распаковки
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
        cmp [esi+0x508],7 //
        jne area4 //
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
        mov eax,[ebp+12]
        cmp [eax+18],1
        je shift_pressed 
        jmp vanilla 

        //push eax
        //push ecx
        //push edx
        //push 0x10
        //mov eax, 0x0085BDF0
        //call dword ptr [eax]
        //and eax,0x8000
        //test eax,eax
        //pop edx
        //pop ecx
        //pop eax
        //jnz shift_pressed
        //jmp originalcode
        
        shift_pressed:
        //push eax
        mov eax,[edi+0x9F]
        test eax,eax
        //pop eax
        jnz has_order 


        jmp vanilla //нет текущего приказа

        has_order:
        push ebx
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
        mov eax,[edi+0x9F]
        test eax,eax
        jz outt
        mov dword ptr [eax+34],0

        outt:
        pop eax

        //originalcode:
        mov dword ptr [edi+780],esi
        mov esi,[ebp+12]
        mov ecx,8
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
        mov eax,[ebx+0x9F]
        test eax,eax
        jz vanilla
        //push eax
        //push ecx
        //push edx
        //push 0x10
        //mov eax, 0x0085BDF0
        //call dword ptr [eax]
        //and eax,0x8000
        //test eax,eax
        //pop edx
        //pop ecx
        //pop eax
        //jnz shift_pressed
        //jmp originalcode
        
        cmp [eax+34],1
        je shift_pressed
        jmp vanilla

        shift_pressed:
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
        //originalcode:
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
        call eax
        jmp[DontResetOrderWhenChanged_JmpBack]
    }
}

//static unsigned long DontResetOrderWhenChanged2x2_Jmp = 0x0046BF9B;
static unsigned long DontResetOrderWhenChanged2x2_Jmp = 0x0046C30C;
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
        call eax
        jmp[DontResetOrderWhenChanged2x2_JmpBack]
    }
}


static unsigned long CheckMyFlagToNotMakeNewOrder_Jmp = 0x0045FF8B;
static unsigned long CheckMyFlagToNotMakeNewOrder_JmpBack = CheckMyFlagToNotMakeNewOrder_Jmp + 5;
__declspec(naked) void inline CheckMyFlagToNotMakeNewOrder()
{
    __asm {
        //push eax
        //mov eax,[esi+0x9F]
        //test eax,eax
        //jz originalcode
        //cmp [eax+0xC],1
        //jne originalcode
        //mov [eax+0xC],0
        //pop eax
        //jmp dont_create

        
        push eax
        mov eax,[esi+0x9F]
        test eax,eax
        jz originalcode
        cmp byte ptr [eax+34],1
        //cmp dword ptr [eax+8], 0xFFFFFFFF
        
        jne originalcode

        cmp [eax+0xC],1
        je outt
        //mov [eax+0xC],1        

        //push ebx
        //go_deeper:
        //mov ebx,eax //сохранить ненулевой приказ
        //cmp [eax+8],0xFFFFFFFF //прочитать вложенный приказ
        //jne go_deeper
        //pop ebx

        // if 
        ////mov [eax+0xC],1
        //pop eax
        //jmp dont_create


        originalcode:
        pop eax
        mov eax,0x00402B26
        call eax
        jmp exitt

        outt:
        mov [eax+0xC],0
        pop eax

        //dont_create:
        pop edx
        pop edx

        exitt:
        jmp[CheckMyFlagToNotMakeNewOrder_JmpBack]
    }
}


static unsigned long CheckNestedOrderToNotCheckDistance_Jmp = 0x0045FF96;
static unsigned long CheckNestedOrderToNotCheckDistance_JmpBack = CheckNestedOrderToNotCheckDistance_Jmp + 7;
__declspec(naked) void inline CheckNestedOrderToNotCheckDistance()
{
    __asm {        
        push eax
        mov eax,[esi+0x9F]
        test eax,eax
        jz no_order
        //cmp dword ptr [eax+8], 0xFFFFFFFF
        
        //cmp byte ptr [eax+34],0xFF
        //je fix_patrol_reset
        cmp byte ptr [eax+34],1
        pop eax
        jne originalcode
        cmp [esi+1288],6
        je originalcode
        cmp [esi+1288],2
        je originalcode
        mov eax,1
        jmp exitt

        //fix_patrol_reset:
        //pop eax
        //jmp originalcode

        no_order:
        pop eax

        originalcode:
        push eax
        push edi
        mov eax,0x0040230B
        call eax
        
        exitt:
        jmp[CheckNestedOrderToNotCheckDistance_JmpBack]
    }
}


static unsigned long CheckOrderStateSpecialCases_Jmp = 0x0040D566;
static unsigned long CheckOrderStateSpecialCases_JmpBack = CheckOrderStateSpecialCases_Jmp + 6;
__declspec(naked) void inline CheckOrderStateSpecialCases()
{
    __asm {        
        push eax
        mov eax,[esi+0x9F]
        test eax,eax
        jz no_order
        //cmp dword ptr [eax+8], 0xFFFFFFFF
        cmp byte ptr [eax+34],1
        pop eax
        jne originalcode
        cmp [esi+1288],6
        je special_case
        cmp [esi+1288],2
        je special_case
        jmp originalcode

        special_case:
        push eax
        mov eax,[esi+0x9F]
        mov eax,[eax+8]
        cmp eax,-1
        je no_order
        mov ecx, dword ptr [eax+0x14] // X next order

        jmp exitt

        no_order:
        pop eax

        originalcode:
        mov ecx,[esi+187]
        
        exitt:
        jmp[CheckOrderStateSpecialCases_JmpBack]
    }
}


static unsigned long CheckNestedOrderToNotDestroyNextStep_Jmp = 0x0045FB4D;
static unsigned long CheckNestedOrderToNotDestroyNextStep_JmpBack = CheckNestedOrderToNotDestroyNextStep_Jmp+ 5;
__declspec(naked) void inline CheckNestedOrderToNotDestroyNextStep()
{
    __asm {        
        push eax
        mov eax,[esi+0x9F]
        test eax,eax
        jz no_order
        cmp dword ptr [eax+8], 0xFFFFFFFF
        pop eax
        
        je originalcode
        //cmp [esi+64],0
        //je originalcode
        jmp exitt

        no_order:
        pop eax

        originalcode:
        mov eax,0x00405952
        call eax
        
        exitt:
        jmp[CheckNestedOrderToNotDestroyNextStep_JmpBack]
    }
}


static unsigned long DontCalculateNextStep_Jmp = 0x0045FFBB;
static unsigned long DontCalculateNextStep_JmpBack = DontCalculateNextStep_Jmp + 5;
__declspec(naked) void inline DontCalculateNextStep()
{
    __asm {        
        //// X
        //xor eax,eax
        //mov ax, word ptr [esi+65]
        //sub eax,100

        //push edx
        //xor edx,edx
        //mov edi,201
        //div edi
        //test edx,edx

        //jnz dont_calculate

        //// Y
        //mov ax, word ptr [esi+67]
        //sub eax,100

        //xor edx,edx
        //mov edi,201
        //div edi
        //test edx,edx
        //jnz dont_calculate

        //// Z
        //mov ax, word ptr [esi+69]
        //sub eax,100

        //xor edx,edx
        //mov edi,200
        //div edi
        //test edx,edx
        //jnz dont_calculate
        //pop edx
        //jmp originalcode

        push eax
        mov eax,[esi+0x9F]
        cmp [eax+0xC],1
        pop eax
        jne originalcode

        cmp[esi+64],0
        //jne dont_calculate
        jne exitt

        originalcode:
        mov eax,0x00403927
        call eax
        jmp exitt
        
        //dont_calculate:
        //pop edx

        exitt:
        jmp[DontCalculateNextStep_JmpBack]
    }
}


static unsigned long FakeNoShiftForQueue_Jmp = 0x0071C057;
static unsigned long FakeNoShiftForQueue_JmpBack = FakeNoShiftForQueue_Jmp + 6;
__declspec(naked) void inline FakeNoShiftForQueue()
{
    __asm {

        //originalcode:
        lea edx,[ebp-0x1B8]

        push eax
        mov eax,0x00802A30
        mov eax,[eax]
        cmp [eax+1186],14 // ghost building cursor state
        pop eax
        jne exitt
        mov [edx+42],0

        exitt:
        jmp[FakeNoShiftForQueue_JmpBack]
    }
}


static unsigned long DontOverwriteBuildState_Jmp = 0x0046B244;
static unsigned long DontOverwriteBuildState_JmpBack = DontOverwriteBuildState_Jmp + 6;
__declspec(naked) void inline DontOverwriteBuildState()
{
    __asm {        
        //eax free
        mov eax,[esi+0x9F]
        test eax,eax
        jz originalcode
        cmp byte ptr [eax+34],1
        jne originalcode
        cmp byte ptr [eax+0xC],1
        je originalcode
        jmp exitt


        originalcode:
        mov [esi+1288],ebx
        mov [esi+1292],ebx

        exitt:
        jmp[DontOverwriteBuildState_JmpBack]
    }
}


static unsigned long DontCheckCellOccupation_Jmp = 0x0046B19B;
static unsigned long DontCheckCellOccupation_JmpBack = DontCheckCellOccupation_Jmp + 6;
__declspec(naked) void inline DontCheckCellOccupation()
{
    __asm {        
        push eax
        mov eax,[esi+0x9F]
        test eax,eax
        jz originalcode
        cmp byte ptr [eax+34],1
        jne originalcode
        cmp byte ptr [eax+0xC],1
        je originalcode
        test ebx,ebx //
        pop eax
        jmp exitt


        originalcode:
        pop eax
        movsx ecx, word ptr [ecx+edi*2]
        cmp ecx,ebx

        exitt:
        jmp[DontCheckCellOccupation_JmpBack]
    }
}


static unsigned long error_jmp = 0x0046C46B;
static unsigned long ExitAfterWriteOrder_Jmp = 0x0046B260;
static unsigned long ExitAfterWriteOrder_JmpBack = ExitAfterWriteOrder_Jmp + 6;
__declspec(naked) void inline ExitAfterWriteOrder()
{
    __asm {       
        push eax
        mov eax,[esi+0x9F]
        test eax,eax
        jz originalcode
        cmp byte ptr [eax+34],1
        jne originalcode
        cmp byte ptr [eax+0xC],1
        je originalcode
        pop eax
        mov eax,2

        pop edi
        pop esi
        pop ebx
        mov esp,ebp
        pop ebp
        retn 4
        //jmp exitt


        originalcode:
        pop eax
        cmp eax,-1
        jz error_
        jmp exitt

        error_:
        jmp[error_jmp]

        exitt:
        jmp[ExitAfterWriteOrder_JmpBack]
    }
}


static unsigned long DontCheckCellCenterFlag_Jmp = 0x0041640B;
static unsigned long DontCheckCellCenterFlag_JmpBack = DontCheckCellCenterFlag_Jmp + 6;
__declspec(naked) void inline DontCheckCellCenterFlag()
{
    __asm {       
        push eax
        mov eax,[esi+0x9F]
        test eax,eax
        jz originalcode
        cmp byte ptr [eax+34],1
        jne originalcode
        cmp [esi+1288],6
        je special_case
        cmp [esi+1288],2
        je special_case
        jmp originalcode

        special_case:
        pop eax
        mov al,1
        jmp exitt


        originalcode:
        pop eax
        mov al, [esi+227]

        exitt:
        jmp[DontCheckCellCenterFlag_JmpBack]
    }
}


static unsigned long DontOverwriteTargetGPS_Jmp = 0x0046B225;
static unsigned long DontOverwriteTargetGPS_JmpBack = DontOverwriteTargetGPS_Jmp + 5;
__declspec(naked) void inline DontOverwriteTargetGPS()
{
    __asm {        
        mov eax,[esi+0x9F]
        test eax,eax
        jz originalcode
        cmp byte ptr [eax+34],1
        jne originalcode
        cmp byte ptr [eax+0xC],1
        je originalcode
        jmp exitt


        originalcode:
        mov eax, 0x00403EB3
        call eax

        exitt:
        jmp[DontOverwriteTargetGPS_JmpBack]
    }
}

static unsigned long DontOverwriteTargetCell_Jmp = 0x0048DDED;
static unsigned long DontOverwriteTargetCell_JmpBack = DontOverwriteTargetCell_Jmp + 5;
__declspec(naked) void inline DontOverwriteTargetCell()
{
    __asm {        
        push eax

        mov eax,[esi+0x9F]
        test eax,eax
        jz outt
        cmp byte ptr [eax+34],1
        jne outt
        pop eax
        ////cmp byte ptr [eax+0xC],0
        //pop eax
        //cmp eax,1
        //jbe back
        //jmp originalcode

        back:
        mov eax, 0x0048DE27
        jmp eax

        outt:
        pop eax

        //originalcode:
        cmp eax,[ebp-8]
        jge back

        //exitt:
        jmp[DontOverwriteTargetCell_JmpBack]
    }
}



static unsigned long DefineInitiateBuildingMoment_Jmp = 0x00452E3E;
static unsigned long DefineInitiateBuildingMoment_JmpBack = DefineInitiateBuildingMoment_Jmp + 5;
__declspec(naked) void inline DefineInitiateBuildingMoment()
{
    __asm {
        //if (1 and build_state = 7 || 0): func_build_movement else out
        push eax
        //mov eax,[ebx+897]
        mov eax,[ebx+0x9F]
        test eax,eax
        jz normal_order
        cmp [eax+34],1
        jne normal_order
        mov eax,[ebx+1288]
        cmp eax, 7
        pop eax
        
        je originalcode
        jmp dont_initiate

        normal_order:
        pop eax

        originalcode:
        mov eax,0x00404543
        call eax
        jmp exitt

        dont_initiate:
        pop esi
        mov eax,2
        mov [ebx+780],0
        //mov dword ptr [ebx+1117], 0
        
        exitt:
        jmp[DefineInitiateBuildingMoment_JmpBack]
    }
}

static unsigned long ReplaceSubGpsToOrderWithShift_Jmp = 0x0040B777;
static unsigned long ReplaceSubGpsToOrderWithShift_JmpBack = ReplaceSubGpsToOrderWithShift_Jmp + 8;
__declspec(naked) void inline ReplaceSubGpsToOrderWithShift()
{
    __asm {
        push edi
        mov edi,[ebx+0x9F]
        test edi,edi
        jz outt

        cmp [edi+34],1
        je shift_pressed
        jmp outt
        
                
        shift_pressed:
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
        //originalcode:
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
        push edi
        mov edi,[ebx+0x9F]
        test edi,edi
        jz no_order

        cmp [edi+34],1
        je shift_pressed
        jmp no_order

        
        shift_pressed:
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


static unsigned long ReplaceOrderGpsToOrderWithShiftRmk_Jmp = 0x0040B901;
static unsigned long ReplaceOrderGpsToOrderWithShiftRmk_JmpBack = ReplaceOrderGpsToOrderWithShiftRmk_Jmp + 8;
__declspec(naked) void inline ReplaceOrderGpsToOrderWithShiftRmk()
{
    __asm {
        pop edx // Y order revert push to replace
        pop ecx // Z order


        push edi
        mov edi,[ebx+0x9F]
        test edi,edi
        jz no_order

        cmp [edi+34],1
        je shift_pressed
        jmp no_order

        shift_pressed:
        // Взять самый глубокий приказ
        push esi
        go_deeper1:
        mov esi,edi
        mov edi,[edi+8]
        cmp edi,0xFFFFFFFF
        jne go_deeper1
        mov edi,esi //вернуть глубочайший приказ
        pop esi

        // Переписать координаты приказа
        movsx ecx,word ptr [edi+0x18] // Z order
        inc ecx
           //проверка 6 высоты
        cmp ecx,5
        jbe next
        dec ecx
        next:
           //        
        movsx edx,word ptr [edi+0x16] // Y order
        //!!!!!
        //pop esi
        pop edi
        push ecx // Z order push again changed
        push edx // Y order push again changed

        movsx eax,word ptr [edi+0x14] // X order
        push eax // X order


            // Проход с счётчиком
        push edi
        mov edi,[ebx+0x9F]

        push esi
        push edx
        xor edx,edx
        go_deeper2:
        inc edx
        mov esi,edi
        mov edi,[edi+8]
        cmp edi,0xFFFFFFFF
        jne go_deeper2
        mov edi,esi          //вернуть глубочайший приказ
        cmp edx, 1
        ja deep
        pop edx

            // НЕТ ВЛОЖЕННОГО ПРИКАЗА
        // Переписать координаты начала пути с подлодки на текущую точку назначения
        pop esi
        pop edi
        movsx ecx,word ptr [ebx+195]
        movsx edx,word ptr [ebx+191]
        movsx eax,word ptr [ebx+187]
        push ecx
        jmp exitt

            // ЕСТЬ ВЛОЖЕННЫЙ ПРИКАЗ
        deep:

            //ДОСТАТЬ ПРЕДПОСЛЕДНИЙ ВЛОЖЕННЫЙ ПРИКАЗ
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
        inc ecx // высота +1
        pop edx
        xor edx,edx
        movsx edx,word ptr [esi+0x16]
        movsx eax,word ptr [esi+0x14]
        pop esi
        pop edi
        push ecx
        jmp exitt

        no_order:
        pop edi
        push ecx
        push edx

        //originalcode:
        movsx ecx, word ptr [ebx+75] // Z current
        movsx edx, word ptr [ebx+73] // Y current
        push eax
        push ecx
        movsx eax, word ptr [ebx+71] // X current

        exitt:
        jmp[ReplaceOrderGpsToOrderWithShiftRmk_JmpBack]
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


static unsigned long PrepareMailNewCommandType_Jmp = 0x00549655;
static unsigned long PrepareMailNewCommandType_JmpBack = PrepareMailNewCommandType_Jmp + 5;
__declspec(naked) void inline PrepareMailNewCommandType()
{
    __asm {
        push eax

        // shift check
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
        jnz newtype

        //originalcode:
        push 35
        jmp outt

        newtype:
        push 36

        outt:
        mov ecx,esi        
        jmp[PrepareMailNewCommandType_JmpBack]
    }
}

static unsigned long AddInfoMailNewCommandType_Jmp = 0x00438216;
static unsigned long AddInfoMailNewCommandType_JmpBack = AddInfoMailNewCommandType_Jmp + 7;
__declspec(naked) void inline AddInfoMailNewCommandType()
{
    __asm {
        // edx free
        cmp [esi+14],36
        jne originalcode
        mov byte ptr [ebp-0x162],1
        jmp exitt

        originalcode:
        mov byte ptr [ebp-0x162],0

        exitt:
        jmp[AddInfoMailNewCommandType_JmpBack]
    }
}


static unsigned long SendMailNewCommandType_Jmp = 0x00438234;
static unsigned long SendMailNewCommandType_JmpBack = SendMailNewCommandType_Jmp + 5;
__declspec(naked) void inline SendMailNewCommandType()
{
    __asm {
        push eax
        
        cmp [esi+14],36
        jne originalcode
        jmp newtype

        originalcode:
        push 9
        jmp outt

        newtype:
        push 25

        outt:
        mov ecx,ebx        
        jmp[SendMailNewCommandType_JmpBack]
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

static DWORD Autosave_timer = GetPrivateProfileInt(L"Plugins", L"Autosave_timer", 1500, ini_file);
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
        test al, al
        jz go_out

        xor edx,edx
        mov eax,0x802A38
        mov eax,[eax]
        mov eax,[eax+0xE4]
        test eax, eax
        jz go_out
        mov ebx, Autosave_timer
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
        test al, al
        jz go_out

        xor edx,edx
        mov eax,0x802A38
        mov eax,[eax]
        mov eax,[eax+0xE4]
        test eax, eax
        jz go_out
        mov ebx, Autosave_timer
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
        test al, al
        jz exitt

        push ebx
        push edx
        xor edx,edx
        mov eax,0x802A38
        mov eax,[eax]
        mov eax,[eax+0xE4]
        mov ebx, Autosave_timer
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
        test al, al
        jz originalcode

        push ebx
        push edx
        xor edx,edx
        mov eax,0x802A38
        mov eax,[eax]
        mov eax,[eax+0xE4]
        mov ebx, Autosave_timer
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

static unsigned long AutosaveDontCheckIfFileExists_Jmp = 0x005355BD; // + 
static unsigned long AutosaveDontCheckIfFileExists_JmpBack = AutosaveDontCheckIfFileExists_Jmp + 5;
__declspec(naked) void inline AutosaveDontCheckIfFileExists()
{
    __asm {
        push eax
        push ebx
        push edx
        
        call[AutosaveCheck]
        test al, al
        jz go_out

        xor edx,edx
        mov eax,0x802A38
        mov eax,[eax]
        mov eax,[eax+0xE4]
        test eax, eax
        jz go_out
        mov ebx, Autosave_timer
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

static unsigned long AutosaveCheckGameMode_Jmp = 0x00533613;
static unsigned long AutosaveCheckGameMode_JmpBack = AutosaveCheckGameMode_Jmp + 7;
__declspec(naked) void inline AutosaveCheckGameMode()
{
    __asm {
        push eax
        mov eax, 0x00808784 // game_submode
        mov eax, [eax]
        cmp eax, 3
        je check_1_3
        test eax, eax
        jz check_3_0
        pop eax
        jmp[AutosaveCheckGameMode_JmpBack]
        
        check_1_3:
        xor eax, eax
        mov eax, 0x00808783
        cmp byte ptr [eax], 1 // game_mode
        pop eax
        jmp[AutosaveCheckGameMode_JmpBack]
                
        check_3_0:
        xor eax, eax
        mov eax, 0x00808783
        cmp byte ptr [eax], 3 // game_mode
        pop eax
        jmp[AutosaveCheckGameMode_JmpBack]
    }
}


static unsigned long AutosaveSkipToggleMenu_Jmp = 0x005336BD;
static unsigned long AutosaveSkipToggleMenu_JmpBack = AutosaveSkipToggleMenu_Jmp + 7;
__declspec(naked) void inline AutosaveSkipToggleMenu()
{
    __asm {

        push eax
        push ebx
        push edx
        
        call[AutosaveCheck]
        test al, al
        jz go_out

        xor edx,edx
        mov eax,0x802A38
        mov eax,[eax]
        mov eax,[eax+0xE4]
        mov ebx, Autosave_timer
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
        cmp ecx,3
        jb not_order
        cmp ecx,4
        ja not_order

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
        cmp dword ptr [ebx+0x00000259],92 // TOBJ_PROTOPLASM_GENERATOR           
        je exitt
        cmp dword ptr [ebx+0x00000259],53 // TOBJ_RESEARCH_LABORATORY            
        je start
        cmp dword ptr [ebx+0x00000259],84 // TOBJ_MOBILITY_HUB_MODULE            
        jb exitt
        cmp dword ptr [ebx+0x00000259],90 // TOBJ_SUPER_TECH_HUB_MODULE          
        ja exitt

        start:
        mov eax, [ebx+0x24]
        add [eax+0x007F586E],1

        exitt:
        jmp[ResearchBuildingsLimitCreateCommon_JmpBack]
    }
}

static BYTE human_limit = GetPrivateProfileInt(L"Tech_centers", L"human_limit", 3, ini_file);
static BYTE si_limit = GetPrivateProfileInt(L"Tech_centers", L"si_limit", 2, ini_file);
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

        mov eax,[esi+0x24]
        mov al,[eax+0x007F586E]
        cmp al, 100
        ja outt

        cmp al, human_limit // max centers
        jb outt

        pop eax
        mov eax,0
        jmp exitt

        outt:
        pop eax

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
        cmp edi,85     // Exclude TOBJ_SUBMARINE_HUB_MODULE from available
        je unavailable 
        cmp edi,86     // Exclude TOBJ_ENERGY_HUB_MODULE from available
        je unavailable 
        cmp edi,87     // Exclude TOBJ_REGENERATION_HUB_MODULE from available
        je unavailable 
        cmp edi,89     // Exclude TOBJ_INTELLIGENCE_HUB_MODULE from available
        je unavailable 
        cmp edi,88     // Exclude structure from available
        je unavailable 
        cmp edi,90     // Exclude super-tech from available
        je unavailable 
        cmp edi,84
        jb exitt
        cmp edi,90
        ja exitt

        push eax

        mov eax,[ebx+0x24]
        mov al,[eax+0x007F586E]
        cmp al, 100
        ja outt
        cmp al, si_limit // max modules
        jb outt
        

        pop eax
        unavailable:
        mov eax,0
        jmp exitt
            
        outt:
        pop eax

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
        je start
        cmp eax,84
        jb originalcode
        cmp eax,90
        ja originalcode

        start:
        push eax

        mov eax,[esi+0x24]
        lea eax,[eax+0x007F586E]
        sub [eax],1

        pop eax

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
        je start
        cmp eax,84
        jb originalcode
        cmp eax,90
        ja originalcode

        start:
        mov eax,[esi+0x24]
        lea eax,[eax+0x007F586E]
        sub [eax],1

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
        je start
        cmp eax,84
        jb exitt
        cmp eax,90
        ja exitt

        start:
        mov eax,[esi+0x24]
        lea eax,[eax+0x007F586E]
        sub [eax],1

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
        je start
        cmp eax,84
        jb originalcode
        cmp eax,90
        ja originalcode

        start:
        push eax

        mov eax,[esi+0x24]
        lea eax,[eax+0x007F586E]
        sub [eax],1

        pop eax

        originalcode:
        lea edi,[esi+0x000001D5]

        jmp[CancelledModulesAndHumanCenters_JmpBack]
    }
}


//static unsigned long func_draw_signal = 0x004CD55E;
static unsigned long CapturedTechBuildings_Jmp = 0x004CD537;
static unsigned long CapturedTechBuildings_JmpBack = CapturedTechBuildings_Jmp + 6;
__declspec(naked) void inline CapturedTechBuildings()
{
    __asm {
        cmp dword ptr [esi+1452],53
        je start
        cmp dword ptr [esi+1452],84
        jb exitt
        cmp dword ptr [esi+1452],90
        ja exitt

        start:
        
        push eax

        mov eax,[esi+0x24]
        lea eax,[eax+0x007F586E]
        sub [eax],1

        
        //mov eax,[ebx+0x24]
        //lea eax,[eax+0x007F586E]
        //add [eax],1

        pop eax

        exitt:
        mov ecx, 0x0080874D
        mov cl, [ecx]
        and ecx, 0xFF
        jmp[CapturedTechBuildings_JmpBack]
    }
}


static unsigned long AntiAbuseHumanCenters_Jmp = 0x00452E31;
static unsigned long AntiAbuseHumanCenters_JmpBack = AntiAbuseHumanCenters_Jmp + 13;
__declspec(naked) void inline AntiAbuseHumanCenters()
{
    __asm {      

        cmp dword ptr [ebx+889],53
        jne originalcode

        push eax

        mov eax,[ebx+0x24]
        mov al,[eax+0x007F586E]
        cmp al, 100
        ja outt
        cmp al, human_limit // max centers

        pop eax
        jb originalcode

        //сброс приказа
        push eax
        push ecx
        mov ecx,0x17
        xor eax,eax
        lea edi, [ebx+716]
        rep stosd
        mov [ebx+708], 0
        pop ecx
        pop eax
        mov edx,0x00458C63
        jmp edx

        outt:
        pop eax

        originalcode:
        push esi
        mov ecx, ebx
        mov dword ptr [ebx+1117], 17

        jmp[AntiAbuseHumanCenters_JmpBack]
    }
}

static unsigned long NoCaptureAllyBuildings_Jmp = 0x0054B0F9;
static unsigned long NoCaptureAllyBuildings_JmpBack = NoCaptureAllyBuildings_Jmp + 6;
__declspec(naked) void inline NoCaptureAllyBuildings()
{
    __asm {
        mov ecx,[ebx+1186]
        cmp ecx, 7

        mov ecx,[ebx+1178]
        jne originalcode
        test ecx, ecx
        jz originalcode

        push ecx
        push ebx


        mov ebx,[ecx+36] // игрок - хозяин здания
                
        lea ebx,[ebx+ebx*8]
        mov al,[ebx+ebx*8+0x008087EA] // взять команду


        mov ebx,0x0080874D // игрок - я
        xor ecx, ecx
        mov cl,[ebx]
        
        lea ecx,[ecx+ecx*8]
        mov ecx,[ecx+ecx*8+0x008087EA] // взять команду
        and ecx, 0xFF

        
        cmp al,cl
        jne enemy_building

            // same_team:
        pop ebx
        pop ecx
        mov ecx,0
        mov dword ptr [ebx+1178], 0
        jmp originalcode

        enemy_building:
        pop ebx
        pop ecx

        originalcode:
        jmp[NoCaptureAllyBuildings_JmpBack]
    }
}


//static unsigned long NoCaptureAllyBuildings_Jmp = 0x0054B0F9;
//static unsigned long NoCaptureAllyBuildings_JmpBack = NoCaptureAllyBuildings_Jmp + 6;
//__declspec(naked) void inline NoCaptureAllyBuildings()
//{
//    __asm {
//        mov ecx,[ebx+1186]
//        cmp ecx, 7
//
//        mov ecx,[ebx+1178]
//        jne originalcode
//        test ecx, ecx
//        jz originalcode
//
//        push ecx
//
//        push ebx
//        mov ebx,[ecx+36] // player
//        push edx
//        mov edx,-1
//        jmp loopy
//
//            // start
//        loopy_pre:
//        pop ecx
//
//        loopy:
//        inc edx
//        cmp dl,8
//        jnb enemy_building
//        xor eax,eax
//
//        mov al,bl
//        cmp al,dl // не сравнивать с собой
//        je loopy
//        
//        lea eax,[eax+eax*8]
//        mov al,[eax+eax*8+0x008087EA] // взять команду игрока
//        push ecx
//        lea ecx,[edx+edx*8]
//        lea ecx,[ecx+ecx*8+0x008087EB]
//        push edx
//        mov edx,[ecx]
//        test edx,edx
//        pop edx
//        jz loopy_pre
//        dec ecx
//        mov cl,[ecx] // взять команду игрока-счетчика
//        cmp cl,al
//        pop ecx
//        jne loopy
//
//        // same_team:
//        pop edx
//        pop ebx
//        pop ecx
//        mov ecx,0
//        mov dword ptr [ebx+1178], 0
//        jmp originalcode
//
//        enemy_building:
//        pop edx
//        pop ebx
//        pop ecx
//
//        originalcode:
//        jmp[NoCaptureAllyBuildings_JmpBack]
//    }
//}

static unsigned long ModifyAimGpsV2_Jmp = 0x004C3902;
static unsigned long ModifyAimGpsV2_JmpBack = ModifyAimGpsV2_Jmp + 7;
__declspec(naked) void inline ModifyAimGpsV2()
{
    __asm {
        push ebx
        push edi

        cmp [edi+565], 63
        je idle

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
        mov eax,[edx+227] // move flag
        test eax,eax
        jz idle

        // moving     
        //push eax
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
        cmp eax, 1 // Check if too close   
        pop edx
        pop ecx
        //pop eax
        jbe idle
        //---

        mov ecx, eax
        imul ecx, 201 // distance
        push ecx

        mov edx, [edi+565]
        lea eax, [edx*2]
        lea edx, [eax+eax*2]
        mov edx, [edx*4+0x00792CA0] // id типа снаряда
        push edx
        mov eax, 0x004025AE // func_get_speed
        call eax 
        pop ecx

        mov edx, eax
        mov eax, ecx
        mov ecx, edx

        xor edx, edx
        div ecx // тиков полёта снаряда до цели (eax)

        mov ecx, [esi+12]
        mov cl, [ecx+97] // submarine speed
        and ecx,0xFF
        imul eax, ecx // !
        mov ecx, eax // смещение
            
        mov edx,[esi+0x0C]
        mov eax,[edx+175] //направление движения
        cmp eax, 0x2FFE
        jae vertical
        
        // horizontal
        test eax,eax
        jnz non_zero
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
        cmp edi, ebx
        jne adjust

        //sar ecx,1

        adjust:
        imul edi,ecx
        imul ebx,ecx
            
        mov edx,[esi+0x0C]
        movsx eax,word ptr [edx+65] // X*200
        add eax,edi
        mov dword ptr [esi+0x20],eax

        movsx eax,word ptr [edx+67]
        add eax,ebx
        mov dword ptr [esi+0x24],eax
        jmp skip_vertical


        vertical:
        sar ecx, 1
        mov ebx,[esi+0x0C]
        movsx ebx,word ptr [ebx+69] // Z*200
        cmp eax, 0x2FFE
        je up
            
        down:
        sub ebx, ecx
        cmp ebx, 100
        ja set_vertical
        mov ebx, 100
        jmp set_vertical

        up:
        add ecx, eax
        cmp ecx, 1110
        jb set_vertical
        mov ecx, 1110

        set_vertical:
        mov dword ptr [esi+0x28],ebx
        jmp outt


        skip_vertical:
        mov ebx,[esi+12]
        movsx ecx,word ptr [ebx+69]
        mov dword ptr [esi+0x28],ecx

        outt:
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
        
        cmp [edi+565], 63
        je idle

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
        
        cmp [esi+565], 63
        je idle

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

        push ebx // ecx free, edi = target ptr
        push eax
        push ecx

                // target has order check
        mov eax,[edi+159]
        test eax,eax
        jz exitt
                // move check
        mov eax,[edi+227] // move flag (0, 1, 2)
        test eax,eax
        jz exitt



            // moving
        //mov eax,[edi+0x9F] // order
        //mov ecx,[edi+0xA3]           // path length
        //lea ecx,[ecx+ecx*8]
        //// movsx eax, word ptr [eax+48] //X target in order
        //movsx ebx, word ptr [edi+0x47] // X current
        //cmp bx, [eax+ecx*8-0x48] // X target in order
        //jne horizontal
        //                       // mov eax,[edi+9F] //order
        //    // movsx eax, word ptr [eax+4A] //Y target in order
        //movsx ebx, word ptr [edi+0x49] // Y current
        //cmp bx, [eax+ecx*8-0x46] // Y target in order
        //jne horizontal


        // vertical
            // Calc distance
        push ecx
        push edx
                // mov edi, [ebp-0x14]
        movsx eax,word ptr [edi+0x4B]
        push eax
        movsx ecx,word ptr [edi+0x49]
        push ecx
        movsx edx,word ptr [edi+0x47]
        push edx
        movsx eax,word ptr [esi+0x4B]
        push eax
        movsx ecx,word ptr [esi+0x49]
        push ecx
        movsx edx,word ptr [esi+0x47]
        push edx
        mov eax, 0x006AADD0
        call eax
        cmp eax, 1           // Check if too close  
        pop edx
        pop ecx
        jbe exitt
            //---
          
            // imul eax, 2 // тиков полёта снаряда до цели (примерная скорость снаряда = 100)
        mov ecx, eax
        imul ecx, 201 // distance
        push edx
        push ecx
        mov edx, [esi+1946]
        push edx
        mov eax, 0x004025AE // func_get_speed
        call eax
        pop ecx 

        mov edx, eax
        mov eax, ecx
        mov ecx, edx

        xor edx, edx
        div ecx // тиков полёта снаряда до цели

            // sub eax,2 //корректировка
            // mov ecx, [esi+12]
        mov cl, [edi+97] // submarine speed
        and ecx,0xFF
        imul eax, ecx
        mov ecx, eax
        
        mov eax,[edi+175] //направление движения
        cmp eax, 0x2FFE
        //jb horizontal
        jae vertical

        
        // horizontal
        //mov eax,[edi+175]
        test eax,eax
        jnz non_zero
        mov eax,1 // X
        mov ebx,0 // Y
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
        ja exittt
        mov eax,1 // 315
        jmp calc

        degree_180:
        mov eax,-1
        mov ebx,0 // 180
        jmp calc

        under_180:
        mov ebx,-1

        cmp eax,90
        jne not_90
        mov eax,0 // 90
        jmp calc

        not_90:
        cmp eax,45
        je degree_45
        mov eax,-1 // 135
        jmp calc

        degree_45:
        mov eax,1 // 45
        jmp calc

        degree_270:
        mov eax,0 // 270
        jmp calc

        degree_225:
        mov eax,-1 // 225


        calc:
        //cmp eax, ebx
        //jne adjust 

        test eax, eax
        jz adjust

            
        sar ecx,1
            
        adjust:
        imul eax,ecx
        imul ebx,ecx

        //mov edx,[esi+0x0C]
        pop edx
        push ecx
        movsx ecx,word ptr [edi+65] // X*200
        add ecx,eax
        mov [ebp-0x84],cx
        pop ecx

        movsx eax,word ptr [edi+67]
        add eax,ebx
        mov [ebp-0x82],ax
        jmp skip


        //test eax,eax
        //jz calc_Y
        //mov ax,[ebp-0x84] // X target final
        //jns inceasing_X
        //    // decreasing_X:
        //xor ecx,ecx
        //mov cl,[edi+0x61] //реальная скорость
        //             // sub ecx,#17
        //imul ecx,7
        //sub eax,ecx // add to X axis

        //set_X:
        //mov [ebp-0x84],ax
        //jmp exitt

        //inceasing_X:
        //xor ecx,ecx
        //mov cl,[edi+0x61] //реальная скорость, от 6 до 21
        //             // sub ecx,#17
        //imul ecx,7
        //add eax,ecx // add to X axis
        //jmp set_X


        //calc_Y:
        //test ebx,ebx
        //mov ax,[ebp-0x82] // Y target final
        //jns inceasing_Y
        //    // decreasing_Y:
        //xor ecx,ecx
        //mov cl,[edi+0x61] //реальная скорость
        //             // sub ecx,#17
        //imul ecx,7
        //sub eax,ecx // add to Y axis

        //set_Y:
        //mov [ebp-0x82],ax
        //jmp exitt

        //inceasing_Y:
        //xor ecx,ecx
        //mov cl,[edi+0x61] //реальная скорость
        //             // sub ecx,#17
        //imul ecx,7
        //add eax,ecx          // add to X axis
        //jmp set_Y



        vertical:
        pop edx
        sar ecx, 1
        movsx edx,word ptr [edi+69] // Z*200
        cmp eax, 0x2FFE
        je up
        cmp eax, 0x4FFE
        je down
        jmp skip
            
        down:
            // mov ebx,[esi+0x0C]
            // movsx ecx,word ptr [edi+69] // Z*200
        sub dx, cx
        cmp dx, 100
        ja put_bottom
        mov dx, 100
        put_bottom:
            // mov dword ptr [esi+0x28],ecx
        jmp exitt

        up:
            // mov ebx,[esi+0x0C]
            // movsx ecx,word ptr [edi+69]
        add dx, cx
        cmp dx, 1110
        jb put_top
        mov dx, 1110
        put_top:
            // mov dword ptr [esi+0x28],ecx

        skip:
        jmp exitt

        exittt:
        pop edx

        exitt:
        pop ecx
        pop eax
        pop ebx

        jmp[AimPredictionSubmarines_JmpBack]
    }
}

static unsigned long AimPredictionSubmarinesDef0_Jmp = 0x004614A0;
static unsigned long AimPredictionSubmarinesDef0_JmpBack = AimPredictionSubmarinesDef0_Jmp + 15;
__declspec(naked) void inline AimPredictionSubmarinesDef0()
{
    __asm {
        push edi
        push eax
        push edx
        push ecx
            // get target pointer
        mov ecx, [esi+1155]
        push ecx
        mov ecx, [esi+1163]
        push ecx
        mov ecx, [esi+1159]
        push ecx
        mov ecx, 0x7FA174
        mov eax, 0x4028BA
        call eax
        mov edi, eax
            //
        pop ecx
        pop edx
        pop eax
        
        mov [ebp-0x4A], dx
        mov dx,[ebp-0x18] // Z target final

        push ebx // ecx free, edi = target ptr
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
        mov ecx,[edi+0xA3]           // path length
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
            // jmp exitt

            // vertical
        cmp [edi+227], 0
        jz skip
        mov ebx,[edi+175] //направление движения
        cmp ebx, 0x2FFE
        jb skip

            // Calc distance
        push ecx
        push edx
                // mov edi, [ebp-0x14]
        movsx eax,word ptr [edi+0x4B]
        push eax
        movsx ecx,word ptr [edi+0x49]
        push ecx
        movsx edx,word ptr [edi+0x47]
        push edx
        movsx eax,word ptr [esi+0x4B]
        push eax
        movsx ecx,word ptr [esi+0x49]
        push ecx
        movsx edx,word ptr [esi+0x47]
        push edx
        mov eax, 0x006AADD0
        call eax
        pop edx
        pop ecx
            //---
            // imul eax, 2 // тиков полёта снаряда до цели (примерная скорость снаряда = 100)
        mov ecx, eax
        imul ecx, 201 // distance
        push edx
        push ecx
        mov edx, [esi+1946]
        push edx
        mov eax, 0x004025AE // func_get_speed
        call eax
        pop ecx 

        mov edx, eax
        mov eax, ecx
        mov ecx, edx

        xor edx, edx
        div ecx // тиков полёта снаряда до цели

            // sub eax,2 //корректировка
            // mov ecx, [esi+12]
        mov cl, [edi+98] // half submarine speed
        and ecx,0xFF
        imul eax, ecx
        cmp ebx, 0x2FFE
        pop edx
        je up
        cmp ebx, 0x4FFE
        je down
        jmp skip
            
        down:
                   // mov ebx,[esi+0x0C]
                   // movsx ecx,word ptr [edi+69] // Z*200
        sub dx, ax
        cmp dx, 100
        ja put_bottom
        mov dx, 100
        put_bottom:
                   // mov dword ptr [esi+0x28],ecx
        jmp exitt

        up:
                   // mov ebx,[esi+0x0C]
                   // movsx ecx,word ptr [edi+69]
        add dx, ax
        cmp dx, 1110
        jb put_top
        mov dx, 1110
        put_top:
            // mov dword ptr [esi+0x28],ecx
        jmp exitt

        skip:
        jmp exitt


        horizontal: // define direction
        mov eax,[edi+0xAF]
        test eax,eax
        jnz non_zero
        mov eax,1 // X
        mov ebx,0 // Y
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
        ja exitt
        mov eax,1 // 315
        jmp calc

        degree_180:
        mov eax,-1
        mov ebx,0          // 180
        jmp calc

        under_180:
        mov ebx,-1

        // dimension_2:
        cmp eax,90
        jne not_90
        mov eax,0 // 90
        jmp calc

        not_90:
        cmp eax,45
        je degree_45
        mov eax,-1 // 135
        jmp calc

        degree_45:
        mov eax,1 // 45
        jmp calc

        degree_270:
        mov eax,0 // 270
        jmp calc

        degree_225:
        mov eax,-1 // 225


        calc:
        test eax,eax
        jz calc_Y
        mov ax,[ebp-0x84] // X target final
        jns inceasing_X
            // decreasing_X:
        xor ecx,ecx
        mov cl,[edi+0x61] //реальная скорость
                     // sub ecx,#17
        imul ecx,7
        sub eax,ecx // add to X axis

        set_X:
        mov [ebp-0x84],ax
        jmp exitt

        inceasing_X:
        xor ecx,ecx
        mov cl,[edi+0x61] //реальная скорость, от 6 до 21
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
        add eax,ecx          // add to X axis
        jmp set_Y


        exitt:
        pop ecx
        pop eax
        pop ebx
        pop edi
        mov [ebp-0x48], dx
        mov edx,[esi+0x24]

        jmp[AimPredictionSubmarinesDef0_JmpBack]
    }
}


static unsigned long AimPredictionSubmarinesDef1_Jmp = 0x00461A54;
static unsigned long AimPredictionSubmarinesDef1_JmpBack = AimPredictionSubmarinesDef1_Jmp + 15;
__declspec(naked) void inline AimPredictionSubmarinesDef1()
{
    __asm {
        push edi
        push eax
        push edx
        push ecx
        // get target pointer
        mov ecx, [esi+1155]
        push ecx
        mov ecx, [esi+1163]
        push ecx
        mov ecx, [esi+1159]
        push ecx
        mov ecx, 0x7FA174
        mov eax, 0x4028BA
        call eax
        mov edi, eax
        //
        pop ecx
        pop edx
        pop eax
        
        mov [ebp-0x4A], dx
        mov dx,[ebp-0x18] // Z target final

        push ebx // ecx free, edi = target ptr
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
        mov ecx,[edi+0xA3]           // path length
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
        //jmp exitt

        //vertical
        cmp [edi+227], 0
        jz skip
        mov ebx,[edi+175]            //направление движения
        cmp ebx, 0x2FFE
        jb skip

            // Calc distance
        push ecx
        push edx
                // mov edi, [ebp-0x14]
        movsx eax,word ptr [edi+0x4B]
        push eax
        movsx ecx,word ptr [edi+0x49]
        push ecx
        movsx edx,word ptr [edi+0x47]
        push edx
        movsx eax,word ptr [esi+0x4B]
        push eax
        movsx ecx,word ptr [esi+0x49]
        push ecx
        movsx edx,word ptr [esi+0x47]
        push edx
        mov eax, 0x006AADD0
        call eax
        pop edx
        pop ecx
            //---
            // imul eax, 2 // тиков полёта снаряда до цели (примерная скорость снаряда = 100)
        mov ecx, eax
        imul ecx, 201 // distance
        push edx
        push ecx
        mov edx, [esi+1946]
        push edx
        mov eax, 0x004025AE // func_get_speed
        call eax
        pop ecx 

        mov edx, eax
        mov eax, ecx
        mov ecx, edx

        xor edx, edx
        div ecx // тиков полёта снаряда до цели

            // sub eax,2 //корректировка
            // mov ecx, [esi+12]
        mov cl, [edi+98] // half submarine speed
        and ecx,0xFF
        imul eax, ecx
        cmp ebx, 0x2FFE
        pop edx
        je up
        cmp ebx, 0x4FFE
        je down
        jmp skip
            
        down:
                   // mov ebx,[esi+0x0C]
                   // movsx ecx,word ptr [edi+69] // Z*200
        sub dx, ax
        cmp dx, 100
        ja put_bottom
        mov dx, 100
        put_bottom:
                   // mov dword ptr [esi+0x28],ecx
        jmp exitt

        up:
                   // mov ebx,[esi+0x0C]
                   // movsx ecx,word ptr [edi+69]
        add dx, ax
        cmp dx, 1110
        jb put_top
        mov dx, 1110
        put_top:
            // mov dword ptr [esi+0x28],ecx
        jmp exitt

        skip:
        jmp exitt


        horizontal: // define direction
        mov eax,[edi+0xAF]
        test eax,eax
        jnz non_zero
        mov eax,1 // X
        mov ebx,0 // Y
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
        ja exitt
        mov eax,1 // 315
        jmp calc

        degree_180:
        mov eax,-1
        mov ebx,0          // 180
        jmp calc

        under_180:
        mov ebx,-1

        // dimension_2:
        cmp eax,90
        jne not_90
        mov eax,0 // 90
        jmp calc

        not_90:
        cmp eax,45
        je degree_45
        mov eax,-1 // 135
        jmp calc

        degree_45:
        mov eax,1 // 45
        jmp calc

        degree_270:
        mov eax,0 // 270
        jmp calc

        degree_225:
        mov eax,-1 // 225


        calc:
        test eax,eax
        jz calc_Y
        mov ax,[ebp-0x84] // X target final
        jns inceasing_X
            // decreasing_X:
        xor ecx,ecx
        mov cl,[edi+0x61] //реальная скорость
                     // sub ecx,#17
        imul ecx,7
        sub eax,ecx // add to X axis

        set_X:
        mov [ebp-0x84],ax
        jmp exitt

        inceasing_X:
        xor ecx,ecx
        mov cl,[edi+0x61] //реальная скорость, от 6 до 21
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
        add eax,ecx          // add to X axis
        jmp set_Y


        exitt:
        pop ecx
        pop eax
        pop ebx
        pop edi
        mov [ebp-0x48], dx
        mov edx,[esi+0x24]

        jmp[AimPredictionSubmarinesDef1_JmpBack]
    }
}

static unsigned long AimPredictionSubmarinesDef2_Jmp = 0x0046113A;
static unsigned long AimPredictionSubmarinesDef2_JmpBack = AimPredictionSubmarinesDef2_Jmp + 15;
__declspec(naked) void inline AimPredictionSubmarinesDef2()
{
    __asm {
        push edi
        push eax
        push edx
        push ecx
            // get target pointer
        mov ecx, [esi+1155]
        push ecx
        mov ecx, [esi+1163]
        push ecx
        mov ecx, [esi+1159]
        push ecx
        mov ecx, 0x7FA174
        mov eax, 0x4028BA
        call eax
        mov edi, eax
            //
        pop ecx
        pop edx
        pop eax

        mov [ebp-0x4A], dx
        mov dx,[ebp-0x18] // Z target final

        push ebx // ecx free, edi = target ptr
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
        mov ecx,[edi+0xA3]           // path length
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

            // vertical old
            // mov eax,[edi+0x9F]     // order
            // movsx ebx, word ptr [edi+0x4B] // Z current
            // sub ebx, [eax+ecx*8-0x44] // Z target in order
            // je exitt         // must never be triggered

            // xor ecx,ecx
            // mov cl,[edi+0x61] //реальная скорость
            //             // sub ecx,#17
            // imul ecx,5
            // test ebx,ebx
            // js going_up
            // sub edx,ecx
            // jmp exitt

            // going_up:
            // add edx,ecx
            // jmp exitt


        cmp [edi+227], 0
        jz skip
        mov ebx,[edi+175] //направление движения
        cmp ebx, 0x2FFE
        jb skip

            // Calc distance
        push ecx
        push edx
                // mov edi, [ebp-0x14]
        movsx eax,word ptr [edi+0x4B]
        push eax
        movsx ecx,word ptr [edi+0x49]
        push ecx
        movsx edx,word ptr [edi+0x47]
        push edx
        movsx eax,word ptr [esi+0x4B]
        push eax
        movsx ecx,word ptr [esi+0x49]
        push ecx
        movsx edx,word ptr [esi+0x47]
        push edx
        mov eax, 0x006AADD0
        call eax
        pop edx
        pop ecx
            //---
            // imul eax, 2 // тиков полёта снаряда до цели (примерная скорость снаряда = 100)
        mov ecx, eax
        imul ecx, 201 // distance
        push edx
        push ecx
        mov edx, [esi+1946]
        push edx
        mov eax, 0x004025AE // func_get_speed
        call eax
        pop ecx 

        mov edx, eax
        mov eax, ecx
        mov ecx, edx

        xor edx, edx
        div ecx // тиков полёта снаряда до цели

            // sub eax,2 //корректировка
            // mov ecx, [esi+12]
        mov cl, [edi+98] // half submarine speed
        and ecx,0xFF
        imul eax, ecx
        cmp ebx, 0x2FFE
        pop edx
        je up
        cmp ebx, 0x4FFE
        je down
        jmp skip
            
        down:
                   // mov ebx,[esi+0x0C]
                   // movsx ecx,word ptr [edi+69] // Z*200
        sub dx, ax
        cmp dx, 100
        ja put_bottom
        mov dx, 100
        put_bottom:
                   // mov dword ptr [esi+0x28],ecx
        jmp exitt

        up:
                   // mov ebx,[esi+0x0C]
                   // movsx ecx,word ptr [edi+69]
        add dx, ax
        cmp dx, 1110
        jb put_top
        mov dx, 1110
        put_top:
            // mov dword ptr [esi+0x28],ecx
        jmp exitt

        skip:
        jmp exitt


        horizontal: // define direction
        mov eax,[edi+0xAF]
        test eax,eax
        jnz non_zero
        mov eax,1 // X
        mov ebx,0 // Y
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
        ja exitt
        mov eax,1 // 315
        jmp calc

        degree_180:
        mov eax,-1
        mov ebx,0          // 180
        jmp calc

        under_180:
        mov ebx,-1

        // dimension_2:
        cmp eax,90
        jne not_90
        mov eax,0 // 90
        jmp calc

        not_90:
        cmp eax,45
        je degree_45
        mov eax,-1 // 135
        jmp calc

        degree_45:
        mov eax,1 // 45
        jmp calc

        degree_270:
        mov eax,0 // 270
        jmp calc

        degree_225:
        mov eax,-1 // 225


        calc:
        test eax,eax
        jz calc_Y
        mov ax,[ebp-0x84] // X target final
        jns inceasing_X
            // decreasing_X:
        xor ecx,ecx
        mov cl,[edi+0x61] //реальная скорость
                     // sub ecx,#17
        imul ecx,7
        sub eax,ecx // add to X axis

        set_X:
        mov [ebp-0x84],ax
        jmp exitt

        inceasing_X:
        xor ecx,ecx
        mov cl,[edi+0x61] //реальная скорость, от 6 до 21
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
        add eax,ecx          // add to X axis
        jmp set_Y


        exitt:
        pop ecx
        pop eax
        pop ebx
        pop edi
        mov [ebp-0x48], dx
        mov edx,[esi+0x24]

        jmp[AimPredictionSubmarinesDef2_JmpBack]
    }
}


static unsigned long AimPredictionSubmarinesDef3_Jmp = 0x004617C5;
static unsigned long AimPredictionSubmarinesDef3_JmpBack = AimPredictionSubmarinesDef3_Jmp + 15;
__declspec(naked) void inline AimPredictionSubmarinesDef3()
{
    __asm {
        push edi
        push eax
        push edx
        push ecx
            // get target pointer
        mov ecx, [esi+1155]
        push ecx
        mov ecx, [esi+1163]
        push ecx
        mov ecx, [esi+1159]
        push ecx
        mov ecx, 0x7FA174
        mov eax, 0x4028BA
        call eax
        mov edi, eax
            //
        pop ecx
        pop edx
        pop eax

        mov [ebp-0x4A], dx
        mov dx,[ebp-0x18] // Z target final

        push ebx // ecx free, edi = target ptr
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
        mov ecx,[edi+0xA3]           // path length
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

            // vertical old
            // mov eax,[edi+0x9F]     // order
            // movsx ebx, word ptr [edi+0x4B] // Z current
            // sub ebx, [eax+ecx*8-0x44] // Z target in order
            // je exitt         // must never be triggered

            // xor ecx,ecx
            // mov cl,[edi+0x61] //реальная скорость
            //             // sub ecx,#17
            // imul ecx,5
            // test ebx,ebx
            // js going_up
            // sub edx,ecx
            // jmp exitt

            // going_up:
            // add edx,ecx
            // jmp exitt


        cmp [edi+227], 0
        jz skip
        mov ebx,[edi+175] //направление движения
        cmp ebx, 0x2FFE
        jb skip

            // Calc distance
        push ecx
        push edx
                // mov edi, [ebp-0x14]
        movsx eax,word ptr [edi+0x4B]
        push eax
        movsx ecx,word ptr [edi+0x49]
        push ecx
        movsx edx,word ptr [edi+0x47]
        push edx
        movsx eax,word ptr [esi+0x4B]
        push eax
        movsx ecx,word ptr [esi+0x49]
        push ecx
        movsx edx,word ptr [esi+0x47]
        push edx
        mov eax, 0x006AADD0
        call eax
        pop edx
        pop ecx
            //---
            // imul eax, 2 // тиков полёта снаряда до цели (примерная скорость снаряда = 100)
        mov ecx, eax
        imul ecx, 201 // distance
        push edx
        push ecx
        mov edx, [esi+1946]
        push edx
        mov eax, 0x004025AE // func_get_speed
        call eax
        pop ecx 

        mov edx, eax
        mov eax, ecx
        mov ecx, edx

        xor edx, edx
        div ecx // тиков полёта снаряда до цели

            // sub eax,2 //корректировка
            // mov ecx, [esi+12]
        mov cl, [edi+98] // half submarine speed
        and ecx,0xFF
        imul eax, ecx
        cmp ebx, 0x2FFE
        pop edx
        je up
        cmp ebx, 0x4FFE
        je down
        jmp skip
            
        down:
                   // mov ebx,[esi+0x0C]
                   // movsx ecx,word ptr [edi+69] // Z*200
        sub dx, ax
        cmp dx, 100
        ja put_bottom
        mov dx, 100
        put_bottom:
                   // mov dword ptr [esi+0x28],ecx
        jmp exitt

        up:
                   // mov ebx,[esi+0x0C]
                   // movsx ecx,word ptr [edi+69]
        add dx, ax
        cmp dx, 1110
        jb put_top
        mov dx, 1110
        put_top:
            // mov dword ptr [esi+0x28],ecx
        jmp exitt

        skip:
        jmp exitt


        horizontal: // define direction
        mov eax,[edi+0xAF]
        test eax,eax
        jnz non_zero
        mov eax,1 // X
        mov ebx,0 // Y
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
        ja exitt
        mov eax,1 // 315
        jmp calc

        degree_180:
        mov eax,-1
        mov ebx,0          // 180
        jmp calc

        under_180:
        mov ebx,-1

        // dimension_2:
        cmp eax,90
        jne not_90
        mov eax,0 // 90
        jmp calc

        not_90:
        cmp eax,45
        je degree_45
        mov eax,-1 // 135
        jmp calc

        degree_45:
        mov eax,1 // 45
        jmp calc

        degree_270:
        mov eax,0 // 270
        jmp calc

        degree_225:
        mov eax,-1 // 225


        calc:
        test eax,eax
        jz calc_Y
        mov ax,[ebp-0x84] // X target final
        jns inceasing_X
            // decreasing_X:
        xor ecx,ecx
        mov cl,[edi+0x61] //реальная скорость
                     // sub ecx,#17
        imul ecx,7
        sub eax,ecx // add to X axis

        set_X:
        mov [ebp-0x84],ax
        jmp exitt

        inceasing_X:
        xor ecx,ecx
        mov cl,[edi+0x61] //реальная скорость, от 6 до 21
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
        add eax,ecx          // add to X axis
        jmp set_Y


        exitt:
        pop ecx
        pop eax
        pop ebx
        pop edi
        mov [ebp-0x48], dx
        mov edx,[esi+0x24]

        jmp[AimPredictionSubmarinesDef3_JmpBack]
    }
}



static unsigned long AimPredictionSubmarinesDef4_Jmp = 0x004614A0;
static unsigned long AimPredictionSubmarinesDef4_JmpBack = AimPredictionSubmarinesDef4_Jmp + 15;
__declspec(naked) void inline AimPredictionSubmarinesDef4()
{
    __asm {
        push edi
        push eax
        push edx
        push ecx
            // get target pointer
        mov ecx, [esi+1155]
        push ecx
        mov ecx, [esi+1163]
        push ecx
        mov ecx, [esi+1159]
        push ecx
        mov ecx, 0x7FA174
        mov eax, 0x4028BA
        call eax
        mov edi, eax
            //
        pop ecx
        pop edx
        pop eax

        mov [ebp-0x4A], dx
        mov dx,[ebp-0x18] // Z target final

        push ebx // ecx free, edi = target ptr
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
        mov ecx,[edi+0xA3]           // path length
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

            // vertical old
            // mov eax,[edi+0x9F]     // order
            // movsx ebx, word ptr [edi+0x4B] // Z current
            // sub ebx, [eax+ecx*8-0x44] // Z target in order
            // je exitt         // must never be triggered

            // xor ecx,ecx
            // mov cl,[edi+0x61] //реальная скорость
            //             // sub ecx,#17
            // imul ecx,5
            // test ebx,ebx
            // js going_up
            // sub edx,ecx
            // jmp exitt

            // going_up:
            // add edx,ecx
            // jmp exitt


        cmp [edi+227], 0
        jz skip
        mov ebx,[edi+175] //направление движения
        cmp ebx, 0x2FFE
        jb skip

            // Calc distance
        push ecx
        push edx
                // mov edi, [ebp-0x14]
        movsx eax,word ptr [edi+0x4B]
        push eax
        movsx ecx,word ptr [edi+0x49]
        push ecx
        movsx edx,word ptr [edi+0x47]
        push edx
        movsx eax,word ptr [esi+0x4B]
        push eax
        movsx ecx,word ptr [esi+0x49]
        push ecx
        movsx edx,word ptr [esi+0x47]
        push edx
        mov eax, 0x006AADD0
        call eax
        pop edx
        pop ecx
            //---
            // imul eax, 2 // тиков полёта снаряда до цели (примерная скорость снаряда = 100)
        mov ecx, eax
        imul ecx, 201 // distance
        push edx
        push ecx
        mov edx, [esi+1946]
        push edx
        mov eax, 0x004025AE // func_get_speed
        call eax
        pop ecx 

        mov edx, eax
        mov eax, ecx
        mov ecx, edx

        xor edx, edx
        div ecx // тиков полёта снаряда до цели

            // sub eax,2 //корректировка
            // mov ecx, [esi+12]
        mov cl, [edi+98] // half submarine speed
        and ecx,0xFF
        imul eax, ecx
        cmp ebx, 0x2FFE
        pop edx
        je up
        cmp ebx, 0x4FFE
        je down
        jmp skip
            
        down:
                   // mov ebx,[esi+0x0C]
                   // movsx ecx,word ptr [edi+69] // Z*200
        sub dx, ax
        cmp dx, 100
        ja put_bottom
        mov dx, 100
        put_bottom:
                   // mov dword ptr [esi+0x28],ecx
        jmp exitt

        up:
                   // mov ebx,[esi+0x0C]
                   // movsx ecx,word ptr [edi+69]
        add dx, ax
        cmp dx, 1110
        jb put_top
        mov dx, 1110
        put_top:
            // mov dword ptr [esi+0x28],ecx
        jmp exitt

        skip:
        jmp exitt


        horizontal: // define direction
        mov eax,[edi+0xAF]
        test eax,eax
        jnz non_zero
        mov eax,1 // X
        mov ebx,0 // Y
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
        ja exitt
        mov eax,1 // 315
        jmp calc

        degree_180:
        mov eax,-1
        mov ebx,0          // 180
        jmp calc

        under_180:
        mov ebx,-1

        // dimension_2:
        cmp eax,90
        jne not_90
        mov eax,0 // 90
        jmp calc

        not_90:
        cmp eax,45
        je degree_45
        mov eax,-1 // 135
        jmp calc

        degree_45:
        mov eax,1 // 45
        jmp calc

        degree_270:
        mov eax,0 // 270
        jmp calc

        degree_225:
        mov eax,-1 // 225


        calc:
        test eax,eax
        jz calc_Y
        mov ax,[ebp-0x84] // X target final
        jns inceasing_X
            // decreasing_X:
        xor ecx,ecx
        mov cl,[edi+0x61] //реальная скорость
                     // sub ecx,#17
        imul ecx,7
        sub eax,ecx // add to X axis

        set_X:
        mov [ebp-0x84],ax
        jmp exitt

        inceasing_X:
        xor ecx,ecx
        mov cl,[edi+0x61] //реальная скорость, от 6 до 21
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
        add eax,ecx          // add to X axis
        jmp set_Y


        exitt:
        pop ecx
        pop eax
        pop ebx
        pop edi
        mov [ebp-0x48], dx
        mov edx,[esi+0x24]

        jmp[AimPredictionSubmarinesDef4_JmpBack]
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


static unsigned long Regen20Percent_Jmp = 0x004D715E;
static unsigned long Regen20Percent_JmpBack = Regen20Percent_Jmp + 7;
__declspec(naked) void inline Regen20Percent()
{
    __asm {
        shl ecx,2
        mul ecx
        shr edx,5
        jmp[Regen20Percent_JmpBack]
    }
}

static DWORD soliton_pulse_cost = GetPrivateProfileInt(L"Soliton", L"Pulse_cost", 0, ini_file);
static unsigned long EnergyForSoliton_Jmp = 0x0060D0CB;
static unsigned long EnergyForSoliton_JmpBack = EnergyForSoliton_Jmp + 9;
__declspec(naked) void inline EnergyForSoliton()
{
    __asm {
        push edx
        push ecx
        push eax

        cmp edi, 1 // When = 1, pulse animation start
        jne checkstate
        test eax, eax // N of branch (0...5)
        jnz checkstate
                

        mov eax,[ebx+36] // field owner
        push eax
        mov eax, 0x004036A7 // j_func_current_energy
        call eax

        cmp eax, soliton_pulse_cost // pulse cost
        jb stall
        mov [ebx+556], 1
        push soliton_pulse_cost // pulse cost
        mov eax,[ebx+36] // field owner
        push eax
        mov eax, 0x004043F9 // j_func_take_energy_1
        call eax

        mov eax,[ebx+36] // field owner
        push eax
        mov eax, 0x00404B8D // j_func_update_resources_panel
        call eax

        pop eax
        pop ecx
        pop edx
        jmp active

        stall:
        mov [ebx+556], 0
        
        checkstate:
        pop eax
        pop ecx
        pop edx
        push eax
        mov al, [ebx+556]
        test eax, eax
        pop eax
        jnz active          // field is ON 
        mov eax, 0x0060D18D // field is OFF
        jmp eax

        active:
        mov edx, [esi+ecx+4] 
        imul edi, [esi+ecx+56]

        jmp[EnergyForSoliton_JmpBack]
    }
}


static unsigned long MinesDetectionAllies_Jmp = 0x00494E8D;
static unsigned long MinesDetectionAllies_JmpBack = MinesDetectionAllies_Jmp + 9;
__declspec(naked) void inline MinesDetectionAllies()
{
    __asm {
        push ecx

        mov eax,[esi+0x18]
        mov edx,[esi+257]
        push -1
        push eax
        mov eax,[esi+0x24]
        push edx
        movsx edx,word ptr [esi+0x5F]
        push eax
        push edx
        movsx eax,word ptr [esi+0x5D]
        movsx edx,word ptr [esi+0x5B]
        push eax
        push edx
        mov eax, 0x00401848
        call eax
        
        pop ecx

        push edx  
        push eax
        push ebx
        mov ebx,[esi+0x24]
        push ebx

        //start:              
        mov edx,-1
        jmp loopy

        loopy_pre:
        pop ecx

        loopy:
        inc edx
        cmp dl,8
        jnb outt
        xor eax,eax

        mov al,bl
        cmp al,dl // не сравнивать с собой
        je loopy
        
        lea eax,[eax+eax*8]
        mov al,[eax+eax*8+0x008087EA] // взять команду игрока
        push ecx
        lea ecx,[edx+edx*8]
        lea ecx,[ecx+ecx*8+0x008087EB]
        push edx
        mov edx,[ecx]
        test edx,edx
        pop edx
        jz loopy_pre
        dec ecx
        mov cl,[ecx] // взять команду игрока-счетчика
        //mov cl,[ecx+ecx*8+0x008087EA] // взять команду игрока-счетчика
        cmp cl,al
        mov al,cl
        pop ecx
        jne loopy  
        push ecx      
        mov dword ptr [esi+0x24],edx
        push edx

        //originalcode:
        mov eax,[esi+0x18]
        mov edx,[esi+257]
        push -1
        push eax
        mov eax,[esi+0x24]
        push edx
        movsx edx,word ptr [esi+0x5F]
        push eax
        push edx
        movsx eax,word ptr [esi+0x5D]
        movsx edx,word ptr [esi+0x5B]
        push eax
        push edx
        mov eax, 0x00401848
        call eax

        pop edx
        pop ecx
        jmp loopy

        outt:
        pop ebx
        mov dword ptr [esi+0x24],ebx
        pop ebx
        pop eax
        pop edx
        jmp[MinesDetectionAllies_JmpBack]
    }
}


static unsigned long LasMinesDetectionAllies_Jmp = 0x00494E3E;
static unsigned long LasMinesDetectionAllies_JmpBack = LasMinesDetectionAllies_Jmp + 9;
__declspec(naked) void inline LasMinesDetectionAllies()
{
    __asm {
        push ecx

        mov eax,[esi+0x18]
        mov edx,[esi+257]
        push -1
        push eax
        mov eax,[esi+0x24]
        push edx
        movsx edx,word ptr [esi+95]
        push eax
        push edx
        movsx eax,word ptr [esi+93]
        movsx edx,word ptr [esi+91]
        push eax
        push edx
        mov eax, 0x0040205E
        call eax
        
        pop ecx

        push edx  
        push eax
        push ebx
        mov ebx,[esi+0x24]
        push ebx

        //start:              
        mov edx,-1
        jmp loopy

        loopy_pre:
        pop ecx

        loopy:
        inc edx
        cmp dl,8
        jnb outt
        xor eax,eax

        mov al,bl
        cmp al,dl // не сравнивать с собой
        je loopy
        
        lea eax,[eax+eax*8]
        mov al,[eax+eax*8+0x008087EA] // взять команду игрока
        push ecx
        lea ecx,[edx+edx*8]
        lea ecx,[ecx+ecx*8+0x008087EB]
        push edx
        mov edx,[ecx]
        test edx,edx
        pop edx
        jz loopy_pre
        dec ecx
        mov cl,[ecx] // взять команду игрока-счетчика
        //mov cl,[ecx+ecx*8+0x008087EA] // взять команду игрока-счетчика
        cmp cl,al
        mov al,cl
        pop ecx
        jne loopy  
        push ecx      
        mov dword ptr [esi+0x24],edx
        push edx

        //originalcode:
        mov eax,[esi+0x18]
        mov edx,[esi+257]
        push -1
        push eax
        mov eax,[esi+0x24]
        push edx
        movsx edx,word ptr [esi+95]
        push eax
        push edx
        movsx eax,word ptr [esi+93]
        movsx edx,word ptr [esi+91]
        push eax
        push edx
        mov eax, 0x0040205E
        call eax

        pop edx
        pop ecx
        jmp loopy

        outt:
        pop ebx
        mov dword ptr [esi+0x24],ebx
        pop ebx
        pop eax
        pop edx
        jmp[LasMinesDetectionAllies_JmpBack]
    }
}

static unsigned long InvisDetectionLoopAlliesBoats_Jmp = 0x0041C4C1;
static unsigned long InvisDetectionLoopAlliesBoats_JmpBack = InvisDetectionLoopAlliesBoats_Jmp + 9;
__declspec(naked) void inline InvisDetectionLoopAlliesBoats()
{
    __asm {
        push ecx

        mov edx,[esi+0x18]
        mov eax,[esi+257]
        movsx ecx,word ptr [esi+0x5F]
        push -1
        push edx
        movsx edx,word ptr [esi+0x5D]
        mov [esi+269],eax
        push eax
        mov eax,[esi+0x24]
        push eax
        push ecx
        movsx eax,word ptr [esi+0x5B]
        mov ecx, 0x00802A88
        mov ecx,[ecx]
        push edx
        push eax
        mov eax, 0x0040141F
        call eax

        pop ecx

        push edx  
        push eax
        push ebx
        mov ebx,[esi+0x24]
        push ebx

            // start:              
        mov edx,-1
        jmp loopy

        loopy_pre:
        pop ecx

        loopy:
        inc edx
        cmp dl,8
        jnb outt
        xor eax,eax

        mov al,bl
        cmp al,dl // не сравнивать с собой
        je loopy
        
        lea eax,[eax+eax*8]
        mov al,[eax+eax*8+0x008087EA] // взять команду игрока
        push ecx
        lea ecx,[edx+edx*8]
        lea ecx,[ecx+ecx*8+0x008087EB]
        push edx
        mov edx,[ecx]
        test edx,edx
        pop edx
        jz loopy_pre
        dec ecx
        mov cl,[ecx] // взять команду игрока-счетчика
        // mov cl,[ecx+ecx*8+0x008087EA] // взять команду игрока-счетчика
        cmp cl,al
        mov al,cl
        pop ecx
        jne loopy  
        push ecx      
        mov dword ptr [esi+0x24],edx
        push edx

            // originalcode:
        mov edx,[esi+0x18]
        mov eax,[esi+257]
        movsx ecx,word ptr [esi+0x5F]
        push -1
        push edx
        movsx edx,word ptr [esi+0x5D]
        mov [esi+269],eax
        push eax
        mov eax,[esi+0x24]
        push eax
        push ecx
        movsx eax,word ptr [esi+0x5B]
        mov ecx, 0x00802A88
        mov ecx,[ecx]
        push edx
        push eax
        mov eax, 0x0040141F
        call eax

        pop edx
        pop ecx
        jmp loopy

        outt:
        pop ebx
        mov dword ptr [esi+0x24],ebx
        pop ebx
        pop eax
        pop edx

        jmp[InvisDetectionLoopAlliesBoats_JmpBack]
    }
}

static unsigned long MineShow_Jmp = 0x00622722;
static unsigned long MyMinesObservationForAllies_Jmp = 0x006226E4;
static unsigned long MyMinesObservationForAllies_JmpBack = MyMinesObservationForAllies_Jmp + 8;
__declspec(naked) void inline MyMinesObservationForAllies()
{
    __asm {
        push eax

        lea eax,[eax+eax*8]
        mov al,[eax+eax*8+0x008087EA] // взять команду текущего игрока

        lea ecx,[ecx+ecx*8]
        lea ecx,[ecx+ecx*8+0x008087EB]  

        push edx
        mov edx,[ecx]
        test edx,edx
        pop edx
        jz not_my_team

        dec ecx
        mov cl,[ecx] // взять команду игрока-хозяина мины
        cmp cl,al
        pop eax
        jne not_my_team

        xor ecx,ecx
        mov cl,[esi+685]
        jmp[MineShow_Jmp]

        not_my_team:
        xor ecx,ecx
        mov cl,[esi+685]
        jmp[MyMinesObservationForAllies_JmpBack]
    }
}

static unsigned long InvisDetectionLoopAllies_Jmp = 0x0041D1B9;
static unsigned long InvisDetectionLoopAllies_JmpBack = InvisDetectionLoopAllies_Jmp + 5;
__declspec(naked) void inline InvisDetectionLoopAllies()
{
    __asm {
        push ecx
        mov edx,[esi+0x18]
        push -1
        push edx
        push eax
        movsx edx,word ptr [esi+0x5F]
        mov eax,[esi+0x24]
        push eax
        push edx
        movsx eax,word ptr [esi+0x5D]
        movsx edx,word ptr [esi+0x5B]
        push eax
        push edx
        mov eax, 0x0040141F
        call eax
        pop ecx

        push edx  
        push eax
        push ebx
        mov ebx,[esi+0x24]
        push ebx

        //start:              
        mov edx,-1
        jmp loopy

        loopy_pre:
        pop ecx

        loopy:
        inc edx
        //mov eax,0x00808AAF // кол-во игроков в игре
        //cmp dl,[eax]
        cmp dl,8
        jnb outt
        xor eax,eax

        mov al,bl
        cmp al,dl // не сравнивать с собой
        je loopy
        
        lea eax,[eax+eax*8]
        mov al,[eax+eax*8+0x008087EA] // взять команду игрока
        push ecx
        lea ecx,[edx+edx*8]
        lea ecx,[ecx+ecx*8+0x008087EB]
        push edx
        mov edx,[ecx]
        test edx,edx
        pop edx
        jz loopy_pre
        dec ecx
        mov cl,[ecx] // взять команду игрока-счетчика
        //mov cl,[ecx+ecx*8+0x008087EA] // взять команду игрока-счетчика
        cmp cl,al
        mov al,cl
        pop ecx
        jne loopy  
        push ecx      
        mov dword ptr [esi+0x24],edx
        push edx

        //originalcode:
        mov edx,[esi+0x18]
        push -1
        push edx
        mov eax,[ebp+8]
        push eax
        movsx edx,word ptr [esi+0x5F]
        //mov eax,[esi+0x24]
        mov eax,[esi+0x24]
        push eax
        push edx
        movsx eax,word ptr [esi+0x5D]
        movsx edx,word ptr [esi+0x5B]
        push eax
        push edx
        mov eax, 0x0040141F
        call eax
        pop edx
        pop ecx
        jmp loopy

        outt:
        pop ebx
        mov dword ptr [esi+0x24],ebx
        pop ebx
        pop eax
        pop edx

        jmp[InvisDetectionLoopAllies_JmpBack]
    }
}



static unsigned long ShowAllyMines_Jmp = 0x006226FB;
static unsigned long ShowAllyMines_JmpBack = ShowAllyMines_Jmp + 9;
__declspec(naked) void inline ShowAllyMines()
{
    __asm {
        mov eax,0x00402865
        call eax
        test eax,eax
        jnz ok
        push ebx
        //mov ebx,[esi+0x24]
        mov ebx, 0x0080874D
        mov ebx, [ebx]
        and ebx, 0xFF
        push edx
        mov edx,-1
        jmp loopy

        //start
        loopy_pre:
        pop ecx

        loopy:
        inc edx
        cmp dl,8
        jnb outt
        xor eax,eax

        mov al,bl
        cmp al,dl // не сравнивать с собой
        je loopy
        
        lea eax,[eax+eax*8]
        mov al,[eax+eax*8+0x008087EA] // взять команду игрока
        push ecx
        lea ecx,[edx+edx*8]
        lea ecx,[ecx+ecx*8+0x008087EB]
        push edx
        mov edx,[ecx]
        test edx,edx
        pop edx
        jz loopy_pre
        dec ecx
        mov cl,[ecx] // взять команду игрока-счетчика
        cmp cl,al
        //mov al,cl
        pop ecx
        jne loopy  
        jmp ok2        

        outt:
        pop edx
        pop ebx

        jmp[ShowAllyMines_JmpBack]
        
        ok2:
        //mov bh, dl
        //pop edx
        //pop ebx
        push edx
        and ecx, 0xFF
        push ecx
        mov ecx, esi
        mov eax,0x00402865
        call eax
        test eax,eax
        pop edx
        jnz ok
        //mov dl, bh
        jmp loopy

        ok:
        mov eax, 0x00622722
        jmp eax
    }
}



static unsigned long ShowAllyLasMines_Jmp = 0x00622710;
static unsigned long ShowAllyLasMines_JmpBack = ShowAllyLasMines_Jmp + 9;
__declspec(naked) void inline ShowAllyLasMines()
{
    __asm {
        mov eax,0x00401811
        call eax
        test eax,eax
        jnz ok
        push ebx
        //mov ebx,[esi+0x24]
        mov ebx, 0x0080874D
        mov ebx, [ebx]
        and ebx, 0xFF
        push edx
        mov edx,-1
        jmp loopy

        //start
        loopy_pre:
        pop ecx

        loopy:
        inc edx
        cmp dl,8
        jnb outt
        xor eax,eax

        mov al,bl
        cmp al,dl // не сравнивать с собой
        je loopy
        
        lea eax,[eax+eax*8]
        mov al,[eax+eax*8+0x008087EA] // взять команду игрока
        push ecx
        lea ecx,[edx+edx*8]
        lea ecx,[ecx+ecx*8+0x008087EB]
        push edx
        mov edx,[ecx]
        test edx,edx
        pop edx
        jz loopy_pre
        dec ecx
        mov cl,[ecx] // взять команду игрока-счетчика
        cmp cl,al
        //mov al,cl
        pop ecx
        jne loopy  
        jmp ok2        

        outt:
        pop edx
        pop ebx

        jmp[ShowAllyLasMines_JmpBack]
        
        ok2:
        //mov bh, dl
        //pop edx
        //pop ebx
        push edx
        and ecx, 0xFF
        push ecx
        mov ecx, esi
        mov eax,0x00401811
        call eax
        test eax,eax
        pop edx
        jnz ok
        //mov dl, bh
        jmp loopy

        ok:
        mov eax, 0x00622722
        jmp eax
    }
}

//
//static unsigned long PingMap_Jmp = 0x00547B44;
//static unsigned long PingMap_JmpBack = PingMap_Jmp + 5;
//__declspec(naked) void inline PingMap()
//{
//    __asm {
//        push ecx
//        push edx
//
//            // save stack state
//        mov ecx,[ebp-4]
//        push ecx
//        mov ecx,[ebp-8]
//        push ecx
//        mov ecx,[ebp-0xC]
//        push ecx
//
//
//        mov edx, 0x00807598 // some big struct
//        mov edx,[edx]
//        // Get float cursor map gps
//        mov esi,[ebx+0x4B6]
//        mov edi,[ebx+0x4B2]
//        lea ecx,[ebp-4]
//        lea eax,[ebp-8]
//        push ecx
//        lea ecx,[ebp-0xC]
//        push eax
//        mov eax,[ebx+0xC9]
//        push ecx
//        mov ecx,[ebx+0xC5]
//        sub eax,esi
//        sub ecx,edi
//        push eax
//        push ecx
//        mov ecx,edx
//        mov eax,0x006E1DD0
//        call eax
//        test eax,eax
//        jz outt
//
//        // to int gps + Call ping
//        // Y округлить вниз
//        fld dword ptr [ebp-8] 
//        mov eax,0x0079070C
//        fmul dword ptr [eax]
//        mov eax,0x0072E288
//        call eax
//        // Y преобразовать в координату миникарты
//        push ebx
//        mov ebx,[esp]
//        mov [esp],eax
//        fild [esp]
//        mov [esp],ebx
//        pop ebx
//        push ecx 
//        mov eax,0x007904F8
//        fmul dword ptr [eax]
//        mov eax,0x007904F4
//        fadd dword ptr [eax]
//        fstp dword ptr [esp]
//
//        // X округлить вниз
//        fld dword ptr [ebp-0xC]
//        mov eax,0x0079070C
//        fmul dword ptr [eax]
//        mov eax,0x0072E288
//        call eax
//        // X преобразовать в координату миникарты
//        push ebx
//        mov ebx,[esp]
//        mov [esp],eax
//        fild [esp]
//        mov [esp],ebx
//        pop ebx
//        push ecx
//        mov eax,0x007904F8
//        fmul dword ptr [eax]
//        mov eax,0x007904F4
//        fadd dword ptr [eax]
//        fstp dword ptr [esp]
//        push 1
//        mov eax,0x00402D5B
//        call eax
//        add esp,0xC
//        //
//
//        outt:
//        // restore stack state
//        pop ecx
//        mov [ebp-4],ecx
//        pop ecx
//        mov [ebp-8],ecx
//        pop ecx
//        mov [ebp-0xC],ecx
//
//        pop edx
//        pop ecx
//
//        mov al, 0x0080734C
//        jmp[PingMap_JmpBack]
//    }
//}

static unsigned long PingMap_Jmp = 0x00547B44;
static unsigned long PingMap_JmpBack = PingMap_Jmp + 5;
__declspec(naked) void inline PingMap()
{
    __asm {
        push ecx
        push edx

            // save stack state
        mov ecx,[ebp-4]
        push ecx
        mov ecx,[ebp-8]
        push ecx
        mov ecx,[ebp-0xC]
        push ecx


        mov edx, 0x00807598 // some big struct
        mov edx,[edx]
        // Get float cursor map gps
        mov esi,[ebx+0x4B6]
        mov edi,[ebx+0x4B2]
        lea ecx,[ebp-4]
        lea eax,[ebp-8]
        push ecx
        lea ecx,[ebp-12]
        push eax
        mov eax,[ebx+0xC9]
        push ecx
        mov ecx,[ebx+0xC5]
        sub eax,esi
        sub ecx,edi
        push eax
        push ecx
        mov ecx,edx
        mov eax,0x006E1DD0
        call eax
        test eax,eax
        jz outt

        // to int gps + Call ping
        // Y округлить вниз
        fld dword ptr [ebp-8] 
        mov eax,0x0079070C // 0.1
        fmul dword ptr [eax]
        mov eax,0x0072E288 // __ftol
        call eax

        mov [ebp-8],eax
        mov dword ptr [ebp-4],0 // Z=0, no, use as flag


        // X округлить вниз
        fld dword ptr [ebp-0xC]
        mov eax,0x0079070C // 0.1
        fmul dword ptr [eax]
        mov eax,0x0072E288 // __ftol
        call eax

        mov [ebp-12],eax
        
        mov ecx,0x00802A38
        mov ecx,[ecx]
        push -1
        lea edx,[ebp-12]
        push 0
        push edx
        push 19 // new command type
        mov eax,0x00403C33
        call eax

        outt:
        // restore stack state
        pop ecx
        mov [ebp-4],ecx
        pop ecx
        mov [ebp-8],ecx
        pop ecx
        mov [ebp-0xC],ecx

        pop edx
        pop ecx

        mov eax, 0x0080734C
        mov al, [eax]
        jmp[PingMap_JmpBack]
    }
}

static unsigned long PingMapSendMail_Jmp = 0x00437712;
static unsigned long PingMapSendMail_JmpBack = PingMapSendMail_Jmp + 5;
__declspec(naked) void inline PingMapSendMail()
{
    __asm {
        push ecx
        push 1
        mov ecx,ebx
        //sub esi,13
        cmp [esi-13],19
        //add esi,13
        je ping
        jmp exitt
        
        ping:
        mov [ebp-0x44],10
        jmp exitt

        exitt:
        jmp[PingMapSendMail_JmpBack]
    }
}

static unsigned long PingMapAddInfoMail_Jmp = 0x00438216;
static unsigned long PingMapAddInfoMail_JmpBack = PingMapAddInfoMail_Jmp + 7;
__declspec(naked) void inline PingMapAddInfoMail()
{
    __asm {
        // edx free
        cmp [esi+14],36
        jne originalcode
        mov byte ptr [ebp-0x162],1
        jmp exitt

        originalcode:
        mov byte ptr [ebp-0x162],0

        exitt:
        jmp[PingMapAddInfoMail_JmpBack]
    }
}


static unsigned long PingMapInterceptCommand_Jmp = 0x004984EB;
static unsigned long PingMapInterceptCommand_JmpBack = PingMapInterceptCommand_Jmp + 5;
__declspec(naked) void inline PingMapInterceptCommand()
{
    __asm {        
        pop edi
        cmp edi,1
        push edi
        jne outt

        cmp [ebx+227],67 // move
        jne originalcode
        cmp [ebx+225],10 // flag
        jne originalcode

        /////////////////
        pop esi
        push ecx
        push eax
        xor eax,eax

        mov ecx,[ebp-4]
        push ecx
        mov ecx,[ebp-8]
        push ecx
            
            
        // to int gps + Call ping
        // Y 
        mov ax, word ptr [ebx+223]
        // Y преобразовать в координату миникарты
        push ebx
        mov ebx,[esp]
        mov [esp],eax
        fild [esp]
        mov [esp],ebx
        pop ebx
        push ecx
        mov eax,0x007904F8
        fmul dword ptr [eax]
        mov eax,0x007904F4
        fadd dword ptr [eax]
        fstp dword ptr [esp]
            
        // X 
        mov ax, word ptr [ebx+221]
        // X преобразовать в координату миникарты
        push ebx
        mov ebx,[esp]
        mov [esp],eax
        fild [esp]
        mov [esp],ebx
        pop ebx
        push ecx
        mov eax,0x007904F8
        fmul dword ptr [eax]
        mov eax,0x007904F4
        fadd dword ptr [eax]
        fstp dword ptr [esp]

        push 1
        mov eax,0x00402D5B
        call eax
        add esp,0xC
        //
            
        //outt:
        // restore stack state
        pop ecx
        mov [ebp-8],ecx
        pop ecx
        mov [ebp-4],ecx

        // clear command buffer
        mov ecx,0x15
        xor eax,eax
        push edi
        push esi
        mov esi,ebx
        lea edi,[esi+137]
        rep stosd
        mov [esi+101],eax

        pop esi
        pop edi
        pop eax
        pop ecx
        ///////////////////
        mov eax,2
        jmp exitt

        outt:
        mov eax,2
        pop esi
        jmp exitt

        originalcode:
        mov eax,0x0040304E // func_init_way
        call eax

        exitt:
        jmp[PingMapInterceptCommand_JmpBack]
    }
}

static unsigned long PatrolMidButtonSI_Jmp = 0x00487998;
static unsigned long PatrolMidButtonSI_JmpBack = PatrolMidButtonSI_Jmp + 8;
__declspec(naked) void inline PatrolMidButtonSI()
{
    __asm {
        mov byte ptr [esi+12], 72
        mov byte ptr [esi+13], 47
        mov byte ptr [esi+14], 6
        mov byte ptr [esi+20], 1

        jmp[PatrolMidButtonSI_JmpBack]
    }
}

static unsigned long PatrolMidButtonSIBIO_Jmp = 0x00487EF5;
static unsigned long PatrolMidButtonSIBIO_JmpBack = PatrolMidButtonSIBIO_Jmp + 8;
__declspec(naked) void inline PatrolMidButtonSIBIO()
{
    __asm {
        mov byte ptr [esi+9], 8
        mov byte ptr [esi+13], 47
        mov byte ptr [esi+14], 6

        jmp[PatrolMidButtonSIBIO_JmpBack]
    }
}

static unsigned long PatrolMidButtonSIPara_Jmp = 0x00488002;
static unsigned long PatrolMidButtonSIPara_JmpBack = PatrolMidButtonSIPara_Jmp + 8;
__declspec(naked) void inline PatrolMidButtonSIPara()
{
    __asm {
        mov byte ptr [esi+13], 47
        mov byte ptr [esi+14], 6
        mov byte ptr [esi+20], 1

        jmp[PatrolMidButtonSIPara_JmpBack]
    }
}

static unsigned long PatrolMidButtonSIGroup_Jmp = 0x0044D6E3;
static unsigned long PatrolMidButtonSIGroup_JmpBack = PatrolMidButtonSIGroup_Jmp + 10;
__declspec(naked) void inline PatrolMidButtonSIGroup()
{
    __asm {
        mov word ptr [edi+8], 0x2F01
        mov word ptr [edi+10], 0x0601


        jmp[PatrolMidButtonSIGroup_JmpBack]
    }
}

static unsigned long SIModulesAllInOne_Jmp = 0x004E7FF1;
static unsigned long SIModulesAllInOne_JmpBack = SIModulesAllInOne_Jmp + 7;
__declspec(naked) void inline SIModulesAllInOne()
{
    __asm {
        add esi, 300
        inc eax
        add edi, 300

        jmp[SIModulesAllInOne_JmpBack]
    }
}

static unsigned long SIModulesAllInOne2_Jmp = 0x004E3270;
static unsigned long SIModulesAllInOne2_JmpBack = SIModulesAllInOne2_Jmp + 7;
__declspec(naked) void inline SIModulesAllInOne2()
{
    __asm {
        lea eax, [eax+eax*2]
        lea ecx, [eax+eax*4-1260]

        jmp[SIModulesAllInOne2_JmpBack]
    }
}

static unsigned long SIModulesAllInOne3_Jmp = 0x004C03CC;
static unsigned long SIModulesAllInOne3_JmpBack = SIModulesAllInOne3_Jmp + 7;
__declspec(naked) void inline SIModulesAllInOne3()
{
    __asm {
        lea eax, [eax+eax*2]
        lea ecx, [eax+eax*4-1260]

        jmp[SIModulesAllInOne3_JmpBack]
    }
}

static unsigned long Select_jmp = 0x0044B7F1;
static unsigned long FlagshipsSelection_Jmp = 0x0044B7A0;
static unsigned long FlagshipsSelection_JmpBack = FlagshipsSelection_Jmp + 5;
__declspec(naked) void inline FlagshipsSelection()
{
    __asm {
        cmp eax, 38
        jb originalcode
        cmp eax, 40
        ja originalcode

        jmp[Select_jmp]
        
        originalcode:
        add eax, 0x41
        mov ecx, eax
        jmp[FlagshipsSelection_JmpBack]
    }
}

static unsigned long OpenBldMenuOnSelection_Jmp = 0x00434213;
static unsigned long OpenBldMenuOnSelection_JmpBack = OpenBldMenuOnSelection_Jmp + 5;
__declspec(naked) void inline OpenBldMenuOnSelection()
{
    __asm {

        cmp [esi+1783], 12
        je builder
        cmp [esi+1783], 24
        jb originalcode
        cmp [esi+1783], 25
        ja originalcode
        
        builder:
        push ecx
        push eax
        push edx
        mov ecx, 0x00801684
        mov ecx, [ecx]
        test ecx, ecx
        jz outt
        cmp word ptr [ecx+370], 2
        jnz outt
        push 1
        mov eax, 0x00401A73 // func_open_close_bld_obj_panel
        call eax
        
        outt:
        pop edx
        pop eax
        pop ecx

        originalcode:
        mov edx, dword ptr [ebp+8]
        mov al, [esi+36]
        jmp[OpenBldMenuOnSelection_JmpBack]
    }
}

static unsigned long CanBuild_Jmp = 0x004AEC9D;
static unsigned long NoBuild_Jmp = 0x004AEC96;


static unsigned long AllySiliconMinesCheckPlacing_Jmp1 = 0x004AE901;
static unsigned long AllySiliconMinesCheckPlacing_Jmp2 = 0x004AE90E;
static unsigned long AllySiliconMinesCheckPlacing_Jmp3 = 0x004AE980;

__declspec(naked) void inline AllySiliconMinesCheckPlacing()
{
    __asm {
        push ebx
        mov ebx,[ebp+0x18] // player
        push edx
        mov edx,-1
        jmp loopy

        // start
        loopy_pre:
        pop ecx

        loopy:
        inc edx
        cmp dl,8
        jnb can_build
        xor eax,eax

        mov al,bl
        //cmp al,dl // не сравнивать с собой
        //je loopy
        
        lea eax,[eax+eax*8]
        mov al,[eax+eax*8+0x008087EA] // взять команду игрока
        push ecx
        lea ecx,[edx+edx*8]
        lea ecx,[ecx+ecx*8+0x008087EB]
        push edx
        mov edx,[ecx]
        test edx,edx
        pop edx
        jz loopy_pre
        dec ecx
        mov cl,[ecx] // взять команду игрока-счетчика
        cmp cl,al
        pop ecx
        jne loopy  

        //same_team:
        push edx
        mov esi, edx
        and esi, 0xFF
        lea eax,[esi+esi*4]
        lea ecx,[esi+eax*8]
        lea edx,[esi+ecx*2]
        shl edx,04
        add edx,esi
        mov ecx,[edx*2+0x007F57F6]
        lea edi,[edx*2+0x007F57F6]
        pop edx
        test ecx,ecx
        jz loopy // нет отслеживающего объекта всех шахт у игрока

        mov eax,[ecx+0xC] 
        xor esi,esi
        test eax,eax
        jng loopy // кол-во шахт <= 0

        some_area_3:
        lea eax,[ebp-0xC]
        push edx
        mov edx,esi
        push eax
        mov eax,0x006ACC70
        call eax // CopyDataChunk
        lea ecx,[ebp-4]
        lea edx,[ebp-2]
        push ecx
        mov ecx,[ebp-0xC]
        lea eax,[ebp+0x2A]
        push edx
        push eax
        mov eax,0x004018C5
        call eax // j_func_write_coords_to_stack
        movsx eax,word ptr [ebp+0x2A]
        mov ecx,[ebp+8]
        cmp eax,ecx
        mov cx,[ebp-2]
        jne some_area
        mov ebx,[ebp+0xC]
        movsx edx,cx
        cmp edx,ebx
        jne some_area
        movsx edx,word ptr [ebp-4]
        cmp edx,[ebp+0x10]
        jne some_area
        pop edx 
        jmp some_area_2

        some_area:
        sub eax,[ebp+8]
        cdq 
        xor eax,edx
        sub eax,edx
        cmp eax,0xF
        pop edx
        jg some_area_2
        push edx
        mov edx,[ebp+0xC]
        movsx eax,cx
        sub eax,edx
        cdq 
        xor eax,edx
        sub eax,edx
        cmp eax,0xF
        pop edx
        jng no_build

        some_area_2:
        mov ecx,[edi]
        inc esi
        cmp esi,[ecx+0xC]
        //pop edx
        jl some_area_3 
        jmp loopy

        can_build:
        pop edx
        pop ebx
        jmp[CanBuild_Jmp]

        no_build:
        pop edx
        pop ebx
        jmp[NoBuild_Jmp]

    }
}


static DWORD corium_steal = GetPrivateProfileInt(L"Cyberworm", L"Corium_steal", 100, ini_file);
static unsigned long CyberWormCoriumSteal_Jmp = 0x004636BD;
static unsigned long CyberWormCoriumSteal_JmpBack = CyberWormCoriumSteal_Jmp + 5;
__declspec(naked) void inline CyberWormCoriumSteal()
{
    __asm {
        mov ebx, eax
        cmp ebx, corium_steal

        jmp[CyberWormCoriumSteal_JmpBack]
    }
}

static unsigned long LasAbsorb2TimesLess_Jmp = 0x004BB375;
static unsigned long LasAbsorb2TimesLess_JmpBack = LasAbsorb2TimesLess_Jmp + 5;
__declspec(naked) void inline LasAbsorb2TimesLess()
{
    __asm {
        sub eax, edx
        sar eax, 2
        push eax

        jmp[LasAbsorb2TimesLess_JmpBack]
    }
}


static unsigned long LasAbsorbSubmarines_Jmp = 0x00459E58;
static unsigned long LasAbsorbSubmarines_JmpBack = LasAbsorbSubmarines_Jmp + 5;
__declspec(naked) void inline LasAbsorbSubmarines()
{
    __asm {
        // free eax, ecx, edx

        mov edx,[edi+4]
        cmp edx,155
        jl outt
        cmp edx,158
        jle laser_shot
        cmp edx,165
        jne outt

        laser_shot:
        mov eax,[ebx+0x24]
        mov ecx,0x007FA174
        mov ecx,[ecx]
        push 104
        push eax
        mov eax,0x0040186B
        call eax
        test eax,eax
        je outt
        mov eax,[edi] // damage
        mov ecx,ebx
        cdq 
        sar eax,2
        push eax
        mov eax, 0x00403D6E
        call eax

        outt:
        mov edx, [ebx+0x24]
        push 101

        jmp[LasAbsorbSubmarines_JmpBack]
    }
}

static unsigned long ContinueMoveSmallDelay_Jmp = 0x0045FA9B;
static unsigned long ContinueMoveSmallDelay_JmpBack = ContinueMoveSmallDelay_Jmp + 7;
__declspec(naked) void inline ContinueMoveSmallDelay()
{
    __asm {
        cmp ax, 5

        jmp[ContinueMoveSmallDelay_JmpBack]
    }
}

//static unsigned long NoOffsetFromMapBorderIfValue_Jmp = 0x00675B1E;
//static unsigned long NoOffsetFromMapBorderIfValue_JmpBack = NoOffsetFromMapBorderIfValue_Jmp + 5;
//__declspec(naked) void inline NoOffsetFromMapBorderIfValue()
//{
//    __asm {
//        cmp [ebp+0x20], 252
//        jne originalcode
//        mov esi, 0
//
//        originalcode:
//        mov esi, 1
//        jmp[NoOffsetFromMapBorderIfValue_JmpBack]
//    }
//}

static unsigned long still_wrong_Jmp = 0x006613BA;
static unsigned long AIPlaceBuildingNearUnsuitable_Jmp = 0x0066121A;
static unsigned long AIPlaceBuildingNearUnsuitable_JmpBack = AIPlaceBuildingNearUnsuitable_Jmp + 7;
__declspec(naked) void inline AIPlaceBuildingNearUnsuitable()
{
    __asm {

        lea eax,[ebx+0x12]
        push 0x000000FD
        lea ecx,[ebx+0x10]
        push eax
        lea edx,[ebx+0x0E]

        xor eax, eax

        mov ax,word ptr [ebx+0x12]
        push ecx
        xor ecx, ecx
        mov cx,word ptr [ebx+0x10]
        push edx
        xor edx, edx
        mov dx,word ptr [ebx+0x0E]
        push eax
        push ecx
        push edx
        mov eax, 0x00401D9D //j_func_find_closest_available_coords
        call eax
        //call ST.exe+0x1D9D
        add esp, 0x1C



        //movsx ebx,word ptr [ebx+0x0E]   // x order
        //mov [ebp-0x10],ebx // put x order ptr

        //mov ebx,[ebp+8] // take order obj again
        //movsx ebx,word ptr [ebx+0x10]   // y order
        //mov [ebp-0x14],ebx // put y order ptr

        //mov ebx,[ebp+8] // take order obj again
        //movsx ebx,word ptr [ebx+0x12]   // z order
        //mov [ebp-0x18],ebx // put z order ptr
        
        //mov eax,[esi+0x00000284] // tactitian
        mov edi,[ebp-0x04] // building id

        movsx eax,word ptr [ebx+0x0E] // x order
        movsx edx,word ptr [ebx+0x10] // y order
        movsx ecx,word ptr [ebx+0x12] // z order



        mov ebx,[ebp-0x0C]
        mov edi,[edi]
        push ebx
        push ecx
        push edx
        push eax
        lea eax,[ebp-0x18] // take z order ptr
        lea ecx,[ebp-0x14] // take y order ptr
        push eax
        mov eax,[esi+0x24] // player
        lea edx,[ebp-0x10] // take x order ptr
        push ecx
        push edx
        push edi
        push eax
        mov eax, 0x00403F03 //j_func_ai_tloChkOrFindBuildingPlace
        call eax
        add esp,0x24

        test eax,eax
        je still_wrong
        jmp[AIPlaceBuildingNearUnsuitable_JmpBack]

        still_wrong:
        jmp[still_wrong_Jmp]
    }
}

//static unsigned long AIGetMapSizeCase_Jmp = 0x0067780D;
//static unsigned long AIGetMapSizeCase_JmpBack = AIGetMapSizeCase_Jmp + 5;
//__declspec(naked) void inline AIGetMapSizeCase()
//{
//    __asm {
//        cmp [ebp+8], 226
//        jne originalcode
//        cmp [ebp+0x1C], 200
//        jne originalcode
//        
//        mov eax, 0x007FB240 // map_size_x
//        mov ax, [eax]
//        mov word ptr [ebp+0xC], ax
//        mov word ptr [ebp-4], ax
//        mov [ebp+0x10], 1
//        and eax, 0xFFFF
//        mov esp, ebp
//        pop ebp
//        retn
//
//        originalcode:
//        mov edx, [ebp+0x1C]
//        test edx, edx
//        jmp[AIGetMapSizeCase_JmpBack]
//    }
//}

//static unsigned long AIGetMapSizeCase_out = 0x004B2051;
//static unsigned long AIGetMapSizeCase_Jmp = 0x004B1FF0;
//static unsigned long AIGetMapSizeCase_JmpBack = AIGetMapSizeCase_Jmp + 5;
//__declspec(naked) void inline AIGetMapSizeCase()
//{
//    __asm {
//        cmp [ebp+0x20], 200
//        jne originalcode
//        
//        xor edx, edx
//        mov eax, 0x007FB240 // map_size_x
//        mov dx, [eax]
//        jmp[AIGetMapSizeCase_out]
//
//        originalcode:
//        mov eax, [ebp+0x20]
//        add eax, esi
//        jmp[AIGetMapSizeCase_JmpBack]
//    }
//}

static BYTE plugin_version = 7;
static BYTE author_number = GetPrivateProfileInt(L"GameVersion", L"Author_id", 1, ini_file);
static BYTE version_number = GetPrivateProfileInt(L"GameVersion", L"Version", 0, ini_file);
static unsigned long ChangeGameVersion_Jmp = 0x005B324F;
static unsigned long ChangeGameVersion_JmpBack = ChangeGameVersion_Jmp + 5;
__declspec(naked) void inline ChangeGameVersion()
{
    __asm {
        mov eax, 0x00807DD5
        //mov dword ptr [eax], 0x01030000 // 0x0102002A - standart, 0x0102001A - V2, 0x01030000 - V3
        //mov dword ptr [eax], 0x01020041

        push ebx
        mov bl, plugin_version
        mov byte ptr [eax+3], bl
        
        mov bl, author_number
        mov byte ptr [eax+2], bl
        
        mov bl, version_number
        mov byte ptr [eax], bl
        pop ebx

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

    // Hard length limit of 15...
    unsigned char bytesToCopy[] = { 0xE9, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
                                    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
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

    size_t WriteTriple(void *addr, const void *data, size_t size)
    {
        Write((uint8_t *)addr, data, size);
        Write((uint8_t *)((char *)addr + 4), data, size);
        return Write((uint8_t *)((char *)addr + 8), data, size);
    }
    size_t WriteDual(void *addr, const void *data, size_t size)
    {
        Write((uint8_t *)addr, data, size);
        return Write((uint8_t *)((char *)addr + 4), data, size);
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
    size_t WriteU32Triple     (void *addr, uint32_t     value) { return WriteTriple(addr, &value, sizeof(value)); }
    size_t WriteU32Dual     (void *addr, uint32_t     value) { return WriteDual(addr, &value, sizeof(value)); }

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
