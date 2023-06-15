#pragma once

namespace Game
{
	const int Entry = 0x007C4040;
	const char* Name = "NFSMW - Orbit Camera 1.1";
	const char* Error = "This .exe is not supported.\nPlease use v1.3 English speed.exe (5,75 MB (6.029.312 bytes)).";
	const char* IniName = "NFSMWOrbitCamera.ini";

	float* DeltaTime = (float*)0x009259BC;
	static auto eCreateLookAtMatrix = (int(__cdecl*)(void*, void*, void*, void*))0x006CF0A0;
	void* HookAddr = (void*)0X0047DCBC;
	void* DisableTiltsAddr = (void*)0X0047D506;
}