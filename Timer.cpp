#include "Timer.h"
#include <thread>
#include <Windows.h>
#include<iostream>

void StartTimer(unsigned long timeRequiereMilliseconds, OnTimeElapsed onTimeElapsed)
{
	std::thread* thread = new std::thread([timeRequiereMilliseconds, onTimeElapsed]()
		{
			Sleep(timeRequiereMilliseconds);
			onTimeElapsed();
		});
}