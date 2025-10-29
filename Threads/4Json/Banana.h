#pragma once
#include "Fruta.h"
class Banana: public Fruta
{
public:
	int bananidad = 0;

	virtual Json::Value Code() override;

	virtual void Decode(Json::Value json) override;

};

