#pragma once
#include <iostream>
#include "ThreadsTutorial/tutorial.h "
#include "InputSystem/InputSystem.h"
#include "utils/ConsoleControl.h"

#include <functional>
#include <string>
#include <list>
#include "Class Timer/Timer.h"

typedef std::function<int(int, int)> SumaFunction;
typedef std::list<std::list<int>> lista;

void TestLambdasMolonas(std::function<int(int,int)> funcionMolona)
{

	std::cout << "Hay una funcion que esta en una variable" << std::endl;
	
	int number = funcionMolona(5, 7);
	std::cout << "Y se esta ejecutando: " <<number <<std::endl;
}

void Test1(lista lista)
{
	
}
int main()
{
	/*std::cout << "Start" << std::endl;
	Timer::StartTimer(3000, []())
	{
	}*/
	int times;
	int maxTimes = 5;

	Timer::StartingLoopTimer(1000, [&times,maxTimes]()
		{
			CC::Lock();
			std::cout << "1 seconds have passed" << std::endl;
			CC::Unlock();
			times++;
			return times < maxTimes;
		});
	std::cout << "End" << std::endl;
	
	
	
	
	/*
std::string name = "PEPE";

std::list<std::list<int>>listaConCosas;
	SumaFunction funcionQueHaceCosasPeroEsUnaVariable = [name](int a,int b)
		{
			std::cout << "Esto no se como pero funciona y me dice mi nombre-> " << name<<std::endl;
			return a+b;
		};
	
	TestLambdasMolonas(funcionQueHaceCosasPeroEsUnaVariable);
	

	InputSystem* iS = new InputSystem();
	InputSystem::KeyBinding* kb = iS->AddListener(K_1, [iS]()
		{
			CC::Lock();
			std::cout << "Pressed 1" << std::endl;
			CC::Unlock();
		});

	while (true)
	{

	}
}*/
	
