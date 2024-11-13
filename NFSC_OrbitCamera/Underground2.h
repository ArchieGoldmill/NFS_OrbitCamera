#pragma once

namespace Game
{
	const int Entry = 0x75BCC7;
	const char* Name = "NFSU2 - Orbit Camera 1.1";
	const char* Error = "This .exe is not supported.\nPlease use v1.2 NTSC speed2.exe (4,57 MB (4.800.512 bytes)).";
	const char* IniName = "NFSU2OrbitCamera.ini";

	float* DeltaTime = (float*)0x00865144;
	bool* IsPaused = (bool*)0x008384DC;
	static auto eCreateLookAtMatrix = (int(__cdecl*)(void*, void*, void*, void*))0x005BA9A0;
	void* HookAddr = (void*)0x00453B44;
	void* DisableTiltsAddr = (void*)0;
}