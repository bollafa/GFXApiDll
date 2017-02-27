#include "WindowsFramework.h"
#include "GFXApi.h"
HHOOK WindowsFramework::hHKeyboardHook;
WPARAM WindowsFramework::lOldLParam;
WindowsFramework::Callback WindowsFramework::cCustomProcess;

/*LRESULT WindowsFramework::KeyboardProcedure(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0)
	{

		if (HIWORD(lParam) & KF_UP && lOldLParam != lParam)
		{
			
			cCustomProcess(wParam);
		}

		lOldLParam = lParam;
	}
	return CallNextHookEx(hHKeyboardHook, nCode, wParam, lParam);
}

void WindowsFramework::HookKeyBoard(Callback cProcess)
{
	cCustomProcess = cProcess;
	hHKeyboardHook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProcedure, NULL, GetCurrentThreadId());
}*/

LRESULT CALLBACK WindowsFramework::KeyboardProcedure(int nCode, WPARAM wParam, LPARAM lParam)
{
	//std::cout << " Probably won't see me ;(" << std::endl;
	if (nCode >= 0)
	{
		KBDLLHOOKSTRUCT* pStruct = (KBDLLHOOKSTRUCT*)lParam;
		//std::cout << " Outside If wParam : " << (wParam == WM_KEYUP) << std::endl;
		//std::cout << "lOldLParam: " << lOldLParam << "\npStruct->vkCode: " << pStruct->vkCode << std::endl;
		if (wParam == WM_KEYUP && lOldLParam != wParam)
		{
			//std::cout << "Inside If" << std::endl;
			cCustomProcess(pStruct->vkCode);
		}

		lOldLParam = wParam;
	}
	return CallNextHookEx(hHKeyboardHook, nCode, wParam, lParam);
}
/*LRESULT CALLBACK WindowsFramework::KeyboardProcedure(int nCode, WPARAM wParam, LPARAM lParam)
{
	//std::cout << " Probably won't see me ;(" << std::endl;
	if (nCode >= 0)
	{
		CWPSTRUCT* pStruct = (CWPSTRUCT*)lParam;
	//	std::cout << " Outside If wParam : " << (pStruct->message == WM_KEYUP)  << "pStruct->message = " << pStruct->message << std::endl;
		if (pStruct->message == 135)
		{
			std::cout << "Inside If" << std::endl;
			cCustomProcess(pStruct->lParam);
		}

		//lOldLParam = pStruct->vkCode;
	}
	return CallNextHookEx(hHKeyboardHook, nCode, wParam, lParam);
}*/

void WindowsFramework::HookKeyBoard(Callback cProcess)
{
	cCustomProcess = cProcess;
	hHKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProcedure, NULL, 0);
}

std::wstring WindowsFramework::GetCurrentWindowTitle()
{
	HWND hCurrentWindow = GetForegroundWindow();
	char Title[MAX_PATH];
	if (hCurrentWindow)
	{


		GetWindowTextA(hCurrentWindow, Title, 256);
	}
	std::string Temp(Title);

	return std::wstring(Temp.begin(),Temp.end());
}
