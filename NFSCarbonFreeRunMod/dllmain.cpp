#include "pch.h"
#include <Windows.h>
#include "injector.hpp"


DWORD newRaceHashCheckExit = 0x5DC927;
void _declspec(naked) newRaceHashCheck() {
	_asm {
	if_statements:
		cmp eax, 0x4603D0DE
		je[true_return]
		cmp eax, 0x47342756
		je[true_return]
		cmp eax, 0x7C9134FB
		jmp[newRaceHashCheckExit]
	true_return:
		jmp[newRaceHashCheckExit]
	}
}

DWORD WINAPI MainThread() {
	DWORD originalmethod = 0x5DC922;
	injector::MakeJMP(originalmethod, newRaceHashCheck, true);

	return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		MainThread();
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

