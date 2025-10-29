#pragma once
#include <thread>
#include <Windows.h>
#include <functional>
class Timer
{
	public:
		typedef std::function<void()> OnTimeElapsed;
		typedef std::function<bool()> StartingLoopTimer;
		
};

