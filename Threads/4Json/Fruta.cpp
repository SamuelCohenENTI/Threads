#include "Fruta.h"

Json::Value Fruta::Code()
{
	Json::Value json;

	json["semillas"] = semillas;
	json["hexDeColor"] = hexDeColor;

	return json;
}

void Fruta::Decode(Json::Value json)
{
	semillas = json["semillas"].asInt();
	hexDeColor = json["hexDeColor"].asString();
}
