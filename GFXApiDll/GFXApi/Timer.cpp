#include "Timer.h"

void CTimer::StartTimer()
{
	dwStartedTime = GetTickCount();
	bPaused = false;
}

void CTimer::PauseTimer()
{
	bPaused = true;
}

void CTimer::StopTimer()
{

}

void CTimer::UnPauseTimer()
{
	dwStartedTime = GetTickCount() - (dwCurrentTime - dwStartedTime);
	bPaused = false;
}

void CTimer::Update()
{
	if (!bPaused)
		dwCurrentTime = GetTickCount();
}

Time & CTimer::GetFormattedTime()
{
	FormattedTime.fSeconds = ((float)((dwCurrentTime - dwStartedTime) % 60000)) / (float)1000;
	FormattedTime.dwMinutes = (dwCurrentTime - dwStartedTime) / 60000;
	FormattedTime.dwHours = FormattedTime.dwMinutes / 60;
	return FormattedTime;
}

std::stringstream & operator<<(std::stringstream & out, Time cTime)
{
//	out << "ºTIMEº    " << cTime.dwHours << ":" << cTime.dwMinutes << ":" << cTime.fSeconds;
	out << "" << cTime.dwHours << ":" << cTime.dwMinutes << ":" << cTime.fSeconds;
	return out;
}
