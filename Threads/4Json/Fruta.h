#pragma once

#include <string>
#include "ICodable.h"

class Fruta: public ICodable
{
public:

	unsigned int semilla = 0;
	std::string hexDeColor="";
	virtual Json::Value Code() override;

	virtual void Decode(Json::Value json) override;
};

