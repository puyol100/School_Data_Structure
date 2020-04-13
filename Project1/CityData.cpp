#include "CityData.h"

CityData::CityData()
{
	LocationId = 0;//for location
	name = new char[50];//for city name
	country = new char[50];//for coutry name
}

CityData::~CityData()
{
}

int CityData::GetLocationId()
{
	return LocationId;
}

char * CityData::Getname()
{
	return name;
}

char * CityData::Getcountry()
{
	return country;
}

void CityData::SetLocationId(int LocationId)
{
	this->LocationId = LocationId;//setting location
}

void CityData::Setname(char * name)
{
	this->name = name;//setting name
}
void CityData::Setcountry(char * country)
{
	this->country = country;//setting country
}
