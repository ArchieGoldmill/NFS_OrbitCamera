#pragma once

namespace Game
{
	const int Entry = 0x0087E926;
	const char* Name = "NFSC - Orbit Camera 1.1";
	const char* Error = "This .exe is not supported.\nPlease use v1.4 English nfsc.exe (6,88 MB (7.217.152 bytes)).";
	const char* IniName = "NFSCOrbitCamera.ini";

	float* DeltaTime = (float*)0x00A99A5C;
	bool* IsPaused = (bool*)0;
	static auto eCreateLookAtMatrix = (int(__cdecl*)(void*, void*, void*, void*))0x0071B430;
	void* HookAddr = (void*)0x00492E5B;
	void* DisableTiltsAddr = (void*)0x00492353;
}