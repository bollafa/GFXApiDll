#include "D3D9Policy.h"
#include "GFXApi.h"
#include "WindowsFramework.h"

D3D9Policy::pPresent D3D9Policy::oPresent = NULL;
D3D9Policy::pReset D3D9Policy::oReset = NULL;
D3D9Policy::pEndScene D3D9Policy::oEndScene = NULL;
LPDIRECT3DDEVICE9 D3D9Policy::pCurrentDevice = NULL;
LPDIRECT3DDEVICE9 D3D9Policy::pOldDevice = NULL;
std::vector < std::pair<ID3DXFont*, std::string> > D3D9Policy::vFonts;
std::vector < std::tuple<std::string, int, std::string> > D3D9Policy::vPreFonts;
POINT D3D9Policy::scSize;
bool D3D9Policy::bDeviceHasChanged = false;
/*
Creates a dummy d3d9 device in the given window handle
@Params : HWND, the window handle to create the device in. GetDesktopWindow() might work aswell.
returns : ERROR_NO_HANDLE : d3d9.dll is not loaded yet or not loaded at all.
	: ERROR_CREATING_INTERFACE : Error while creating the Direct3DCreate9 interface
	: ERROR_CREATING_DEVICE: Error while creating the d3d9 device.
	: OK : No errors at all . !

	TODO : different error codes.DONE!!!
	*/
void D3D9Policy::StartPolicy(INIT_TYPE init)
{
	////std::cout << "D3D9 POLICY" << std::endl;
	/*if (GetModuleHandle("d3d9.dll") == NULL)
		return ERROR_NO_HANDLE; // It hasn't been loaded so we return an error */

								//Create the d3d9 interface
	typedef IDirect3D9* (__stdcall *dDirectCreate9)(UINT SDKVersion);
	dDirectCreate9 dCreate9 = (dDirectCreate9)GetProcAddress(GetModuleHandle("d3d9.dll"), "Direct3DCreate9");
	if (NULL == (pDirectInterface = dCreate9(D3D_SDK_VERSION)))// Check if it has failed
	{
		//LOG ERROR ERROR_CREATING_INTERFACE; // It has failed so we return ERROR_CREATING_INTERFACE.
		////std::cout << "ERROR_CREATING_INTERFACE" << std::endl;

	}
		
	

										 //Create the D3DPresent Parameters
	D3DPRESENT_PARAMETERS d3dPresentParameters;
	//Clear out memory to initialize all of them to NULL ( 0 )
	ZeroMemory(&d3dPresentParameters, sizeof(D3DPRESENT_PARAMETERS));
	//Set needed values
	d3dPresentParameters.hDeviceWindow = GetDesktopWindow();
	d3dPresentParameters.Windowed = TRUE;
	d3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//Check if we Created the Device succesfully
	if (pDirectInterface->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetDesktopWindow(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPresentParameters, &pDevice) != D3D_OK)
	{
		// LOG return ERROR_CREATING_DEVICE; //Error while creating the device.
		////std::cout << "ERROR_CREATING_DEVICE" << std::endl;
	}
	
									  //Everything is ok so we return  OK ( succesful ) 
	//return OK;

	// Start HOOKING'''
	if (init == INIT_TYPE::REGULAR)
	{
		oPresent = DetourHookVMTFunctionIndex(pDevice, iPresent, HookPresent);
		////std::cout << "REGULAR" << std::endl;
	}
		
	else if (init == INIT_TYPE::ALTERNATIVE)
	{
		oEndScene = DetourHookVMTFunctionIndex(pDevice, iEndScene, HookEndScene);
		////std::cout << "ALTERNATIVE" << std::endl;
	}
			
	oReset = DetourHookVMTFunctionIndex(pDevice, iReset, HookReset);

	////std::cout << "Somehow I am here" << pDevice << std::endl;
}

void D3D9Policy::EnableHooks()
{
	MH_EnableHook(MH_ALL_HOOKS);
}

void D3D9Policy::DrawRect(D3DRECT _rectPos)
{
	pCurrentDevice->Clear(1, &_rectPos, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 0, 0), 0, 0);
}

void D3D9Policy::AddFont(std::string sFontID, int iSize, std::string sCustomFontName)
{
	auto Temp = std::make_tuple(sFontID,iSize,sCustomFontName);
	vPreFonts.push_back(Temp);
	
}

POINT &  D3D9Policy::GetScreenSize()
{
	return scSize;
}

void D3D9Policy::PostFont(std::string sFontID, int iSize, std::string sCustomFontName)
{
	std::pair <ID3DXFont*, std::string> pairTemp;
	// Custom Bold - 
	if (D3DXCreateFont(pCurrentDevice, iSize, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, sCustomFontName.c_str(), &pairTemp.first) == S_OK)
	{
		pairTemp.second = sCustomFontName;
		vFonts.push_back(pairTemp);

	}
}



void D3D9Policy::CreateFonts()
{
	for (auto it = vPreFonts.begin(); it != vPreFonts.end(); ++it)
	{
		PostFont(std::get<0>(*it), std::get<1>(*it), std::get<2>(*it));


	}
}

void D3D9Policy::OnLostDevice()
{
	for (auto it = vFonts.begin(); it != vFonts.end(); ++it)
	{
		if (it->first)
			it->first->OnLostDevice();

	}
}

void D3D9Policy::OnResetDevice()
{
	for (auto it = vFonts.begin(); it != vFonts.end(); ++it)
	{
		if (it->first)
			it->first->OnResetDevice();

	}
}

POINT D3D9Policy::GetDisplaySize()
{
	D3DDISPLAYMODE d3dDisplayMode;
	pCurrentDevice->GetDisplayMode(0, &d3dDisplayMode);
	
	return { (LONG)d3dDisplayMode.Width,(LONG)d3dDisplayMode.Height };
}


HRESULT WINAPI D3D9Policy::HookPresent(LPDIRECT3DDEVICE9 _this, CONST RECT * pSourceRect, CONST RECT * pDestRect, HWND hDestWindowOverride, CONST RGNDATA * pDirtyRegion)
{
	if (pCurrentDevice != _this)
	{
		pCurrentDevice = _this;

	}
	if (!bDeviceHasChanged)
	{
		CreateFonts();
		//scSize = GetDisplaySize();
		WindowsFramework::HookKeyBoard(Trampoline);
		bDeviceHasChanged = true;
	}
	scSize = GetDisplaySize();
	

	// Drawing sht goes here ---
	GFXBase<D3D9Policy>::GetInstance()->OnDraw();
	// ---

	return oPresent(_this,pSourceRect,pDestRect,hDestWindowOverride,pDirtyRegion);
}

HRESULT WINAPI D3D9Policy::HookReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS * pPresentationParameters)
{
	// On Lost Device Here
	OnLostDevice();

	HRESULT midOScene = oReset(pDevice, pPresentationParameters);

	//On Reset Device goes here
	if (midOScene == S_OK)
		OnResetDevice();

	
	return midOScene;
}

HRESULT D3D9Policy::HookEndScene(LPDIRECT3DDEVICE9 _this)
{
	if (pCurrentDevice != _this)
	{
		pCurrentDevice = _this;

	}
	if (!bDeviceHasChanged)
	{
		CreateFonts();
		
		WindowsFramework::HookKeyBoard(Trampoline);
		bDeviceHasChanged = true;
	}

	scSize = GetDisplaySize();

	// Drawing sht goes here ---
	GFXBase<D3D9Policy>::GetInstance()->OnDraw();

	return oEndScene(_this);
}

void D3D9Policy::Trampoline(DWORD32 vkKey)
{
	GFXBase<D3D9Policy>::GetInstance()->Callbacked(vkKey);
}


void D3D9Policy::PrintWithFont(std::string sFontName, std::string sText, RECT pt_Coordinates, sRGBA RGBA)
{
	
	for (auto it = vFonts.begin(); it != vFonts.end(); ++it)
	{
		if (it->first)
			if (it->second == sFontName)
			{
				it->first->DrawTextA(NULL, sText.c_str(), -1, &pt_Coordinates, DT_LEFT | DT_NOCLIP, RGBA.Color);
				break;
			}
			
				
		

	}
}