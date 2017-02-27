#pragma once
#include "../stdafx.h"

class WindowsFramework // Win 6.1 for now
{
private:
	typedef void(*Callback)(DWORD32 vkKeyValue);
	
	static Callback cCustomProcess;
	static HHOOK hHKeyboardHook;
	static WPARAM lOldLParam;
	
public:
	static LRESULT CALLBACK KeyboardProcedure(int nCode, WPARAM wParam, LPARAM lParam);

	static void HookKeyBoard(Callback cProcess);
	static std::wstring GetCurrentWindowTitle();
};
