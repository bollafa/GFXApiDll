#pragma once
#include "..\stdafx.h"

struct Time
{
	DWORD dwHours = NULL;
	DWORD dwMinutes = NULL;
	float fSeconds = NULL;

};
std::stringstream& operator<<(std::stringstream& out, Time cTime);
class CTimer
{
private:
	DWORD dwStartedTime;
	DWORD dwCurrentTime;
	DWORD dwElapsedTime;
	Time FormattedTime;
	bool bPaused;
public:

	void StartTimer();
	void PauseTimer(); // Pauses it and can be started again from that time. Example : current time : 5 secs, pause() , start() after 10 min+ , 5 secs and going up
	void StopTimer(); // Completely stops and goes forward to the next thing
	void UnPauseTimer();
	void Update();
	Time& GetFormattedTime();
	bool &isPaused() { return bPaused; };
	CTimer() : dwStartedTime(NULL), dwCurrentTime(NULL), dwElapsedTime(NULL), bPaused(true)
	{

	}




};