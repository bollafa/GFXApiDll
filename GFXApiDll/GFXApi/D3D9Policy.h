#pragma once
#include "..\stdafx.h"
#include "GFXApi.h"
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
class D3D9Policy
{
private:
	
protected:
	union sRGBA {

		
		struct
		{
			
			BYTE B;
			BYTE G;
			BYTE R;
			BYTE A;
			
		};

		DWORD Color;

	};
	enum D3D9_ERROR
	{
		ERROR_CREATING_INTERFACE,
		ERROR_CREATING_DEVICE
	};
	
	void StartPolicy(INIT_TYPE init);
	void EnableHooks();
	void DrawRect(D3DRECT _rectPos);
	static void AddFont(std::string sFontID, int iSize, std::string sCustomFontName);
	static POINT & GetScreenSize();
	static void PrintWithFont(std::string sFontName, std::string sText, RECT pt_Coordinates, sRGBA RGBA);
private:
	static POINT scSize;
	static POINT GetDisplaySize();
	static std::vector < std::pair<ID3DXFont*, std::string> > vFonts;
	static std::vector < std::tuple<std::string, int, std::string> > vPreFonts;
	static void CreateFonts();
	static void OnLostDevice();
	static void OnResetDevice();
	
	static void PostFont(std::string sFontID, int iSize, std::string sCustomFontName);
	
	enum D3D9_VMT
	{
		iEndScene = 42,
		iPresent = 17,
		iReset = 16
	};
	LPDIRECT3D9 pDirectInterface; // D3D9 Interface
	LPDIRECT3DDEVICE9 pDevice;

	static LPDIRECT3DDEVICE9 pCurrentDevice;
	static LPDIRECT3DDEVICE9 pOldDevice;
	static bool bDeviceHasChanged;

	typedef HRESULT (WINAPI *pPresent)(LPDIRECT3DDEVICE9 _this, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion);
	static pPresent oPresent;

	
	typedef HRESULT(WINAPI *pEndScene)(LPDIRECT3DDEVICE9);
	static pEndScene oEndScene;
	typedef HRESULT(WINAPI *pReset)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
	static pReset oReset;


	static HRESULT WINAPI HookPresent(LPDIRECT3DDEVICE9 _this, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion) ;
	static HRESULT WINAPI HookReset (LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
	static HRESULT WINAPI HookEndScene(LPDIRECT3DDEVICE9 _this);
	static void Trampoline(DWORD32 vkKey);

	

};