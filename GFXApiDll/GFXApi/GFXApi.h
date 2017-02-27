#pragma once
#include "..\stdafx.h"
#include "Timer.h"
#include "GUISystem.h"
#include "FileMgr.h"
#include "WindowsFramework.h"
#include <ShlObj.h>

#define COLOR_RGBA(r,g,b,a) \
    ((DWORD)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

enum INIT_TYPE
{
	REGULAR,
	ALTERNATIVE


};
class GFXBaseGeneric
{
private:

public:

	virtual void Init(INIT_TYPE init) = 0;
	virtual void Callbacked(DWORD32 vkKey) = 0;

};
template <typename GFXPolicy>
class GFXBase : private GFXPolicy, public GFXBaseGeneric
{
private:

	CTimer sTime;
	UIList<Time> uiTimeList;
	UIList<std::string> uiLapNameList;
	POINT TimeOffset;
	POINT LapNameOffset;
	std::wstring DocumentsPath;
	std::vector< std::tuple<int, int, int, int> > vColors;
	GFXBase() : TimeOffset({0,0}) , LapNameOffset({0,0})
	{
		if (MH_Initialize() != MH_OK)
		{
			//Shit happened
			//std::cout << "MH INIT FAILED YUHU PROPS YOU BASTARD" << std::endl;
	    }

		
	}
	


public:


	static GFXBase * GetInstance()
	{
		static GFXBase* singleton;
		if (singleton == nullptr)
			singleton = new GFXBase;
		return singleton;

	}
	void Init(INIT_TYPE init);
	void OnDraw();
	
	
	void Callbacked(DWORD32 vkKey);
};

template<typename GFXPolicy>
inline void GFXBase<GFXPolicy>::Init(INIT_TYPE init)
{

	

	GFXPolicy::StartPolicy(init);
	GFXPolicy::EnableHooks();

	//Add Fonts Here????

	GFXPolicy::AddFont("Arial", 48, "Timer");
	GFXPolicy::AddFont("Arial", 22, "Lap");
	

	PWSTR Magic = NULL;
	SHGetKnownFolderPath(FOLDERID_Documents, 0, 0, &Magic);

	

	std::wstringstream ws;
	ws << Magic << "\\BananaSplitter\\GameTimer.txt";
	std::wstringstream folder;
	folder << Magic << "\\BananaSplitter";
//	std::wcout << ws.str() << std::endl;
	std::wstring Tempo(folder.str());
	DocumentsPath.assign(Magic);
	if (!FileMgr::FileExists(ws.str()))
	{
		////std::cout << "FileDOESNTExist???" << std::endl;
		////std::cout << "Look Here:::: " << std::string(Tempo.begin(), Tempo.end()).c_str() << std::endl;
		CreateDirectory(std::string(Tempo.begin(), Tempo.end()).c_str(), NULL);
		////std::cout << "Error Code: " << GetLastError() << std::endl;
		FileMgr ShtTest(ws.str(), std::fstream::out);
		ShtTest.WriteString(std::string(""));
		ShtTest.Close();




	}
	else
	{
		////std::cout << "FileExists!!!" << std::endl;
		FileMgr HintNames(ws.str(),  std::fstream::in);
		uiLapNameList.AddWithVector(HintNames.VectorOfListNames());
		
		
		// Config Colors

		folder << "\\Config.txt";
		std::vector< std::tuple < int, int, int, int > > vTemp;
		vTemp.push_back(std::make_tuple(0, 255, 0, 255));
		vTemp.push_back(std::make_tuple(0, 255, 0, 255));
		vTemp.push_back(std::make_tuple(0, 255, 0, 255));
		if (!FileMgr::FileExists(folder.str()))
		{
			FileMgr ShtTest(folder.str(), std::fstream::out);
			ShtTest.WriteString(std::string("#Hint Color\n\n#LapColor\n\n#Current time color"));
			
			vColors = vTemp;

		}
		else
		{
			FileMgr Config(folder.str(), std::fstream::in);
			std::vector< std::tuple < int, int, int, int > > vToken =  Config.TokenRead(std::make_tuple(1, 2, 3, 4), ',');
			if (vToken.size() != 3)
			{
				vColors = vTemp;
			}
			else if (vToken.size() == 3)
			{
				vColors = vToken;

			}
		}
	} 
	
	
	
	////std::cout << "WHYYYYYYYYYYYYYYYYY" << std::endl;
	
	CoTaskMemFree(Magic);

}

template<typename GFXPolicy>
inline void GFXBase<GFXPolicy>::OnDraw()
{
	//Draw Everything we need, start with a simple text
	//GFXPolicy::Print({ 0,0,400,400 }, "Hello GFX WORLD!");
	//GFXPolicy::DrawRect({ 40,40,80,80 });
	//GFXPolicy::DrawRect({ 20,20,300,300 });
	////std::cout << "Hello ma lady" << std::endl;
	////std::cout << GFXPolicy::GetScreenSize().x << std::endl;
	sTime.Update();
	std::stringstream ssTime;
	ssTime << sTime.GetFormattedTime();
	POINT Temp = GFXPolicy::GetScreenSize();
	//GFXPolicy::sRGBA test = { .R = 40,.G = 0,.B = 0, .A = 0 };
	
	static auto CreateColor = [](BYTE r, BYTE g , BYTE b , BYTE a) -> GFXPolicy::sRGBA {  
		GFXPolicy::sRGBA temp;
		temp.R = r;
		temp.G = g;
		temp.B = b;
		temp.A = a;

		return temp;

	
	};
	static auto CreateColorWithTuple = [](std::tuple<BYTE,BYTE,BYTE,BYTE> _in) -> GFXPolicy::sRGBA {
		GFXPolicy::sRGBA temp;
		temp.R = std::get<0>(_in);
		temp.G = std::get<1>(_in);
		temp.B = std::get<2>(_in);
		temp.A = std::get<3>(_in);

		return temp;


	};
	////std::cout << Temp.x << " <--  X\n" << Temp.y << " <-- Y" << std::endl;
	//GFXPolicy::PrintWithFont("Lap", uiTimeList.Update(), {  Temp.x / 2 + Temp.x / 40,20 }, CreateColorWithTuple(vColors.at(1)) );
	//GFXPolicy::PrintWithFont("Lap", uiLapNameList.Update(), { Temp.x / 5 +  Temp.x / 5,20 }, CreateColorWithTuple(vColors.at(0)) );
	//GFXPolicy::PrintWithFont("Timer", ssTime.str(), { 20 + TimeOffset.x ,Temp.y / 2 + TimeOffset.y ,600,600 }, CreateColorWithTuple(vColors.at(2)) );

	GFXPolicy::PrintWithFont("Lap", uiTimeList.Update(), { Temp.x / 2 + Temp.x / 4 + Temp.x / 40,20 }, CreateColorWithTuple(vColors.at(1)) );
	GFXPolicy::PrintWithFont("Lap", uiLapNameList.Update(), { Temp.x / 2 + Temp.x / 7,20 }, CreateColorWithTuple(vColors.at(0)) );
	GFXPolicy::PrintWithFont("Timer", ssTime.str(), { 20 + TimeOffset.x ,Temp.y / 2 + TimeOffset.y ,600,600 }, CreateColorWithTuple(vColors.at(2)) );
}

template<typename GFXPolicy>
inline void GFXBase<GFXPolicy>::Callbacked(DWORD32 vkKey)
{
	std::wstringstream Convert;
	Convert << DocumentsPath;
	FileMgr* Temp;
	//std::cout << "key:" << vkKey << std::endl;
	switch (vkKey)
	{

	case VK_SPACE:
		if (sTime.isPaused())
			sTime.UnPauseTimer();
		else
			sTime.PauseTimer();
		break;
	case VK_NUMPAD0:
		uiTimeList.AddObject(sTime.GetFormattedTime());
		break;
	case VK_NUMPAD4:

		TimeOffset.x -= 10;
		break;
	case VK_NUMPAD6:

		TimeOffset.x += 10;
		break;
	case VK_NUMPAD2:

		TimeOffset.y += 10;
		break;
	case VK_NUMPAD8:

		TimeOffset.y -= 10;
		break;
	case VK_NUMPAD1:
		//std::cout << PrintConcLists(uiLapNameList, uiTimeList) << std::endl;
		//std::wcout << DocumentsPath << std::endl;
		//std::wcout << WindowsFramework::GetCurrentWindowTitle() << std::endl;
		break;
	case VK_NUMPAD7:
		//std::cout << "Saving....!" << std::endl;
		Convert << L"\\BananaSplitter\\Game Split " <<WindowsFramework::GetCurrentWindowTitle() << L" "<< GetTickCount() << L".txt";
		Temp = new FileMgr(Convert.str(), std::fstream::out);
		Temp->WriteString(PrintConcLists(uiLapNameList,uiTimeList) );
		
		Temp->Close();
		delete Temp;
		break;
	case VK_NUMPAD3:
		Convert << L"\\BananaSplitter\\GameTimer.txt";
		Temp = new FileMgr(Convert.str(), std::fstream::in);
		uiLapNameList.AddWithVector(Temp->VectorOfListNames());
		Temp->Close();
		delete Temp;
		break;

	}
}

