#include "WindowsFramework.h"
#include "GFXApi.h"
HHOOK WindowsFramework::hHKeyboardHook;
LPARAM WindowsFramework::lOldLParam;
WindowsFramework::Callback WindowsFramework::cCustomProcess;

LRESULT WindowsFramework::KeyboardProcedure(int nCode, WPARAM wParam, LPARAM lParam)
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
