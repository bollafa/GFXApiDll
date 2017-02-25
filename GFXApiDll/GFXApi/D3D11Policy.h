#pragma once
#include "..\stdafx.h"
#include "GFXApi.h"
#include <D3D11.h>
#pragma comment(lib,"d3d11.lib")

class D3D11Policy
{
private:
	
	ID3D11Device* pDevice;
	IDXGISwapChain* pSwap;
	ID3D11DeviceContext* pDeviceContext;
	static ID3D11Device* pCurrentDevice;
	static ID3D11DeviceContext* pCurrentDeviceContext;
	static IDXGISwapChain* pCurrentSwapChain;
	static bool bDeviceHasChanged;
	typedef HRESULT(WINAPI *D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	static D3D11PresentHook oPresent;

	static HRESULT(WINAPI D3D11PresentHooked) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	
	static std::vector < std::pair<IFW1FontWrapper*, std::string> > vFonts;
	static std::vector < std::tuple<std::string, int, std::string> > vPreFonts;
	static void PostFont(std::string sFontID, int iSize, std::string sCustomFontName);
	

	static POINT scSize;
	static POINT GetDisplaySize();
	static void CreateFonts();
	static void Trampoline(DWORD32 vkKey);
protected:
	union sRGBA {
		struct
		{
			BYTE R;
			BYTE G;
			BYTE B;
			BYTE A;

		};

		DWORD Color;

	};
	void StartPolicy(INIT_TYPE init);
	void EnableHooks();
	static void AddFont(std::string sFontID, int iSize, std::string sCustomFontName);
	static POINT & GetScreenSize();
	static void PrintWithFont(std::string sFontName, std::string sText, RECT pt_Coordinates, sRGBA RGBA);
};