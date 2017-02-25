#include "stdafx.h"
// Make a precompiled header out of this
#include "GFXApi\GFXApi.h"
#include "GFXApi\D3D9Policy.h"
#include "GFXApi\WindowsFramework.h"
#include "GFXApi\D3D11Policy.h"
// ------
//Turn this into a class later

GFXBaseGeneric* gfxBase = nullptr;



void CheckTypesAndCreateGFX()
{
	//std::cout << "D3D9.DLL MODULE" << GetModuleHandle("d3d9.dll") << std::endl;
	//std::cout << "D3D11.DLL MODULE" << GetModuleHandle("d3d11.dll") << std::endl;
	if (GetModuleHandle("dxgi.dll"))
	{
		// It uses d3d9 ! ( naive prediction )
		gfxBase = GFXBase<D3D11Policy>::GetInstance();
		return;
	}
	if (GetModuleHandle("d3d9.dll"))
	{

		// It uses d3d9 ! ( naive prediction )
		gfxBase = GFXBase<D3D9Policy>::GetInstance();
		return;
	}
	
	//std::cout << "None found!!!" << std::endl;
}
// -------

struct point { int x, y; };
DWORD WINAPI Start(LPVOID lParam)
{
	//DELETE BEGIN
	//AllocConsole();
	//freopen("CONOUT$", "w", stdout);
	//DELETE END
	CheckTypesAndCreateGFX();
	if (gfxBase != nullptr)
	{
		//std::cout << "I cry evertm" << std::endl;
		//std::wcout << WindowsFramework::GetCurrentWindowTitle() << std::endl;
		gfxBase->Init(REGULAR);
		//gfxBase->Init(ALTERNATIVE);
		
	}
	//std::cout << " ;)" << std::endl;
	return 0;
}
BOOL WINAPI DllMain(HINSTANCE dllInstance, WPARAM fdwReason, LPVOID lParam)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(dllInstance);
		CreateThread(NULL, NULL, Start, NULL, NULL, NULL);
		return TRUE;
		break;

	case DLL_PROCESS_DETACH:
		
		break;

	default:
		break;



	}




	return TRUE;
}