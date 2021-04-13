#include "pch.h"
#include "Hooking.h"
#include "Processes.h"

DWORD flyInitOrig;
void __declspec(naked) flyInitHook() {
    __asm {
        // Check if 'c' is pressed
        mov dl, byte ptr ds:[0x975E91]
        cmp dl, 0x80
        jne exitEarly
        // Check if player already is in vehicle
        push 0x5E
        mov eax, 0x411495
        call eax
        add esp, 4
        and eax, 1
        test eax, eax
        je exitEarly
        // Check if the entity is the glider
        mov edx, [ebp+8]
        mov eax, [edx]
        cmp eax, 0x52444C47
        jne exitEarly
        // Move the glider address into "EnteredVehicle" variable
        mov edx, [ebp+8]
        mov dword ptr ds:[0x5DE1E90], edx
        // Jump to the end of the glider entry function and return 1
        mov edi, 0x451D41
        jmp edi

	exitEarly:
        mov edx, dword ptr ds:[0x975E90]
        jmp [flyInitOrig]
    }
}

DWORD flyOrig;
void __declspec(naked) flyHook() {
    __asm {
        // Check whether glider is in entry mode
        mov ecx, [ebp-0x4]
        movsx edx, byte ptr [ecx+0x23]
        cmp edx, 3
        jne exitEarly
        // Check whether 'c' key is pressed
        mov al, byte ptr ds:[0x975E91]
        cmp al, 0x80
        jne exitEarly
        // Check whether EnteredVehicle == aEntity
        mov ecx, dword ptr ds:[0x5DE1E90]
        cmp ecx, [ebp+0x8]
        jne exitEarly
        // Set x coord of glider to player
        mov edx, dword ptr ds:[0x9CCB10]
        mov ecx, [edx+0x3C]
        mov edx, [ebp+0x8]
        mov dword ptr ds:[edx+0x3C], ecx
        // Set y coord of glider to player
        mov edx, dword ptr ds:[0x9CCB10]
        mov ecx, [edx+0x40]
        mov edx, [ebp+0x8]
        mov dword ptr ds:[edx+0x40], ecx
        // Set z coord of glider to player
        mov edx, dword ptr ds:[0x9CCB10]
        mov ecx, [edx+0x44]
        mov edx, [ebp+0x8]
        mov dword ptr ds:[edx+0x44], ecx
        // Jump to the update movement code
        mov edx, 0x452399
        jmp edx

    exitEarly:
        mov edx, [ebp-0x4]
        movsx eax, byte ptr [edx+0x23]
        jmp [flyOrig]
    }
}


DWORD WINAPI MainThread(HMODULE hModule)
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    int flyInitLen = 6;
    DWORD flyInitAddr = 0x451CDF;
    flyInitOrig = flyInitAddr + flyInitLen;
    Hook((void*)flyInitAddr, flyInitHook, flyInitLen);

    int flyLen = 7;
    DWORD flyAddr = 0x45243D;
    flyOrig = flyAddr + flyLen;
    Hook((void*)flyAddr, flyHook, flyLen);

    while (true)
    {
        if (GetAsyncKeyState(VK_END) & 1)
        {
            break;
        }
    }
    
    if (f)
		fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr));
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

/*

        if (GetAsyncKeyState(VK_NUMPAD0) & 1)
        {
            longJump = !longJump;

            std::cout << "Changing long jump state to " << longJump << std::endl;

            if (longJump)
                PatchBytes((BYTE*)(moduleBase + 0x005749B0), (BYTE*)"\x00\x00\x20\x42", 4);
            else
                PatchBytes((BYTE*)(moduleBase + 0x005749B0), (BYTE*)"\x00\x00\x70\x41", 4);
        }
*/
