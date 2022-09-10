#include <Windows.h>
#include "Game.h"
#include "includes/IniReader/IniReader.h"
#include "includes/Injector/injector.hpp"

struct Vec3
{
	float x;
	float y;
	float z;
};

bool IsPressed(int key)
{
	return GetAsyncKeyState(key) & 0x8000;
}

int HK_Left, HK_Right, HK_Up, HK_Down;
float DisableTilts = 0;
float CamAngle = 0;
float CamSpeed;
int __cdecl CreateLookAtMatrixHook(void* outMatrix, Vec3* from, Vec3* to, Vec3* up)
{
	float Target = 0;
	bool isLeft = IsPressed(HK_Left);
	bool isRight = IsPressed(HK_Right);
	bool isUp = IsPressed(HK_Up);
	bool isDown = IsPressed(HK_Down);

	if (isLeft) Target = 360 - 85;
	if (isRight) Target = 85;
	if (isDown) Target = 180;
	if (isUp && isLeft) Target = 360 - 43;
	if (isUp && isRight) Target = 43;
	if (isDown && isLeft) Target = 360 - 135;
	if (isDown && isRight) Target = 135;

	int dir = CamAngle < Target ? 1 : -1;
	dir = abs(CamAngle - Target) > abs(360 - abs((CamAngle - Target))) ? -dir : dir;
	if (CamAngle != Target)
	{
		float step = *Game::DeltaTime * CamSpeed * dir;

		if (abs(step) > abs(CamAngle - Target))
		{
			CamAngle = Target;
		}
		else
		{
			CamAngle += step;
			if (CamAngle > 360) CamAngle -= 360;
			if (CamAngle < 0) CamAngle += 360;
		}
	}

	if (CamAngle != 0)
	{
		DisableTilts = -1000;
		float angle = CamAngle * 3.14f / 180.0f;
		Vec3 newFrom;
		newFrom.x = cos(angle) * (from->x - to->x) - sin(angle) * (from->y - to->y) + to->x;
		newFrom.y = sin(angle) * (from->x - to->x) + cos(angle) * (from->y - to->y) + to->y;
		newFrom.z = from->z;
		*from = newFrom;
	}
	else
	{
		DisableTilts = 0;
	}

	return Game::eCreateLookAtMatrix(outMatrix, from, to, up);
}

void Init()
{
	CIniReader iniReader(Game::IniName);
	if (iniReader.ReadInteger("CAMERA", "Enabled", 0) == 1)
	{
		HK_Left = iniReader.ReadInteger("CAMERA", "LookLeftKey", 0);
		HK_Right = iniReader.ReadInteger("CAMERA", "LookRightKey", 0);
		HK_Up = iniReader.ReadInteger("CAMERA", "LookForwardKey", 0);
		HK_Down = iniReader.ReadInteger("CAMERA", "LookBackKey", 0);

		CamSpeed = iniReader.ReadFloat("CAMERA", "Speed", 600);
		injector::MakeCALL(Game::HookAddr, CreateLookAtMatrixHook, true);
		injector::WriteMemory<float*>(Game::DisableTiltsAddr, &DisableTilts, true);
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA(NULL);
		IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)(base);
		IMAGE_NT_HEADERS* nt = (IMAGE_NT_HEADERS*)(base + dos->e_lfanew);

		if ((base + nt->OptionalHeader.AddressOfEntryPoint + (0x400000 - base)) == Game::Entry) // Check if .exe file is compatible - Thanks to thelink2012 and MWisBest
		{
			Init();
		}
		else
		{
			MessageBoxA(NULL, Game::Error, Game::Name, MB_ICONERROR);
			return FALSE;
		}
	}
	break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}