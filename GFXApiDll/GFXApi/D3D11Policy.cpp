#include "..\stdafx.h"
#include "D3D11Policy.h"
#include "GFXApi.h"
#include "WindowsFramework.h"



D3D11Policy::D3D11PresentHook D3D11Policy::oPresent;
bool D3D11Policy::bDeviceHasChanged = false;
ID3D11Device *D3D11Policy::pCurrentDevice = NULL;
ID3D11DeviceContext* D3D11Policy::pCurrentDeviceContext = NULL;
IDXGISwapChain* D3D11Policy::pCurrentSwapChain = NULL;

POINT D3D11Policy::scSize;


std::vector < std::pair<IFW1FontWrapper*, std::string> > D3D11Policy::vFonts;
std::vector < std::tuple<std::string, int, std::string> > D3D11Policy::vPreFonts;



IFW1Factory *pFW1Factory = NULL;
IFW1FontWrapper *pFontWrapper = NULL;

ID3D11Resource* pRenderTargetTexture = NULL;

ID3D11RenderTargetView* g_pRenderTargetView = NULL;


void D3D11Policy::CreateFonts()
{
	for (auto it = vPreFonts.begin(); it != vPreFonts.end(); ++it)
	{
		PostFont(std::get<0>(*it), std::get<1>(*it), std::get<2>(*it));


	}
}

void D3D11Policy::Trampoline(DWORD32 vkKey)
{
	GFXBase<D3D11Policy>::GetInstance()->Callbacked(vkKey);
}


HRESULT (WINAPI D3D11Policy::D3D11PresentHooked)(IDXGISwapChain * pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (pSwapChain != pCurrentSwapChain)
		bDeviceHasChanged = false;
	if (!bDeviceHasChanged)
	{
		pCurrentSwapChain = pSwapChain;
		pSwapChain->GetDevice(__uuidof(pCurrentDevice), (void**)&pCurrentDevice);
		pCurrentDevice->GetImmediateContext(&pCurrentDeviceContext);
		FW1CreateFactory(FW1_VERSION, &pFW1Factory);
		//pFW1Factory->CreateFontWrapper(pCurrentDevice, L"Tahoma", &pFontWrapper);

		scSize = GetDisplaySize();

		//use the back buffer address to create the render target
		if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pRenderTargetTexture)))
		{
			pCurrentDevice->CreateRenderTargetView(pRenderTargetTexture, NULL, &g_pRenderTargetView);
			pRenderTargetTexture->Release();
		//	std::cout << "It Worked!!!!" << std::endl;
		}
		CreateFonts();
		WindowsFramework::HookKeyBoard(Trampoline);
		bDeviceHasChanged = true;
	}
	pCurrentDeviceContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);
	//pFontWrapper->DrawString(pCurrentDeviceContext, L"D3DBBBBook by bolos", 48, 16.0f, 16.0f, 0xffff1612, FW1_RESTORESTATE);

	GFXBase<D3D11Policy>::GetInstance()->OnDraw();
	
	return oPresent(pSwapChain, SyncInterval, Flags);
}
void D3D11Policy::PostFont(std::string sFontID, int iSize, std::string sCustomFontName)
{
	std::pair <IFW1FontWrapper*, std::string> Temp;

	pFW1Factory->CreateFontWrapper(pCurrentDevice, (LPCWSTR)(sFontID.c_str()), &Temp.first);
	Temp.second = sCustomFontName;
	vFonts.push_back(Temp);

}
POINT D3D11Policy::GetDisplaySize()
{
	DXGI_SWAP_CHAIN_DESC temp;
	pCurrentSwapChain->GetDesc(&temp);

	

	return{ (LONG)temp.BufferDesc.Width,(LONG)temp.BufferDesc.Height };
}
void D3D11Policy::StartPolicy(INIT_TYPE init)
{
	//std::cout << "D3D11 POLICY" << std::endl;
	HWND hWnd = GetDesktopWindow();
	// Setting up the swap chain description
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = hWnd; // If it doesnt work change to GetForegroundWindow() : GetDesktopWindow()
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	D3D_FEATURE_LEVEL  FeatureLevelsRequested = D3D_FEATURE_LEVEL_11_0;
	UINT               numLevelsRequested = 1;
	D3D_FEATURE_LEVEL  FeatureLevelsSupported;
	typedef HRESULT (WINAPI *customD3D11CreateDeviceAndSwapChain)(
		__in_opt IDXGIAdapter* pAdapter,
		D3D_DRIVER_TYPE DriverType,
		HMODULE Software,
		UINT Flags,
		__in_ecount_opt(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
		UINT FeatureLevels,
		UINT SDKVersion,
		__in_opt CONST DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
		__out_opt IDXGISwapChain** ppSwapChain,
		__out_opt ID3D11Device** ppDevice,
		__out_opt D3D_FEATURE_LEVEL* pFeatureLevel,
		__out_opt ID3D11DeviceContext** ppImmediateContext);

	customD3D11CreateDeviceAndSwapChain CreateD3D11 = (customD3D11CreateDeviceAndSwapChain)GetProcAddress(GetModuleHandle("d3d11.dll"), "D3D11CreateDeviceAndSwapChain");
	HRESULT hr;
	if ((hr = CreateD3D11(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, &FeatureLevelsRequested, numLevelsRequested, D3D11_SDK_VERSION, &swapChainDesc, &pSwap, &pDevice, NULL, &pDeviceContext)) != S_OK)
	{
		//std::cout << "D3D11CREATEDEVICEANDSWAPCHAIN FAILED YUHUUUUUUUUUUUUU" << std::endl;
		//std::cout << std::hex << +hr << std::endl;
		
	}
	
	//std::cout << "awd" << std::endl;
	oPresent = DetourHookVMTFunctionIndex(pSwap, 8, D3D11PresentHooked);

	pDevice->Release();
	pSwap->Release();
}

void D3D11Policy::EnableHooks()
{
	MH_EnableHook(MH_ALL_HOOKS);
}

void D3D11Policy::AddFont(std::string sFontID, int iSize, std::string sCustomFontName)
{
	auto Temp = std::make_tuple(sFontID, iSize, sCustomFontName);
	vPreFonts.push_back(Temp);
}

POINT & D3D11Policy::GetScreenSize()
{
	return scSize;
}
 
void D3D11Policy::PrintWithFont(std::string sFontName, std::string sText, RECT pt_Coordinates, sRGBA RGBA)
{
	for (auto it = vFonts.begin(); it != vFonts.end(); ++it)
	{
		if (it->first)
			if (it->second == sFontName)
			{//0xffff1612
				//std::cout << "Dafuq man" << std::endl;
				//pCurrentDeviceContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);
				for(auto wt = vPreFonts.begin(); wt != vPreFonts.end(); ++wt)
					if (std::get<2>(*wt) == sFontName)
					{
						it->first->DrawString(pCurrentDeviceContext, std::wstring(sText.begin(), sText.end()).c_str(), std::get<1>(*wt), pt_Coordinates.left, pt_Coordinates.top, RGBA.Color, FW1_RESTORESTATE);
						//std::cout << std::hex << +RGBA.Color << std::endl;
					}
						
				
				break;
			}

	}
}
