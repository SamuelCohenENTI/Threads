#pragma once
#include <iostream>
#include "ThreadsTutorial/tutorial.h "
#include "InputSystem/InputSystem.h"
#include "utils/ConsoleControl.h"

#include <functional>
#include <string>
#include <list>
#include "Class Timer/Timer.h"
#include <json/json.h>
#include <fstream>


#include "Json/ICodable.h"
#include "Json/Banana.h"
#include "Json/Manzana.h"



/*
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
	
}*/
/*
class Player   // Codable-> serializable + deserializable
{

public:
	int life = 0;
	std::string name = "Test Player";
	unsigned int coins = 0;

	Player() {}
	~Player() {};

	void Decode(Json::Value json)  //Deserializar
	{
		life = json["life"].asInt();
		name = json["name"].asString();
		coins = json["coins"].asUInt();
	}

	

	Json::Value Encode()  //Serializable
	{
		Json::Value json;
		json["life"] = life;
		json["name"] = name;
		json["coins"] = coins;

		return json;
	}
};
*/
int main()
{

	ICodable::SaveDecodeProcess<Banana>();
	ICodable::SaveDecodeProcess<Manzana>();

	std::vector<Fruta*> frutas;
	{
			new Banana(),
			new Manzana()

	};

	frutas[1]->semillas = 1000;

	Json::Value jsonArray = Json::Value(Json::arrayValue);
	for (Fruta* fruta : frutas)
	{
		jsonArray.append(fruta->Code());
	}

	std::ofstream jsonWriterFile = std::ofstream("FutasTest.json", std::ofstream::binary);

	if (!jsonWriteFile.fail())
	{
		jsonWriterFile << jsonArray;
		jsonWriterFile.close();
	}

	std::cout << "Finish write";
	std::ifstream jsonReadFile = std::ifstream("FrutasTest.json", std::ifstream::binary);
	std::vector<Fruta*> readFrutas;

	if (!jsonReadFile.fail())
	{
		Json::Value readJson;
		jsonReadFile >> readJson;

		for (Json::Value value : readJson)
		{
			Fruta* f = ICodable::FromJson<Fruta>(value);
			readFrutas.push_back(f);
		}
	}

	/*
	Player* player = new Player();
	player->coins = 5;
	player->life = 50;
	player->name = "Gundemaro";

	Json::Value newJson;
	newJson["Player"] = player->Encode();
	std::ofstream* jsonWriteFile = new std::ofstream("PlayerParseTest.json", std::ofstream::binary);
	*/


	/*std::cout << "Start" << std::endl;
	Timer::StartTimer(3000, []())
	{
	}
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
	*/
	
	
	
	
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
}
*/
	;
