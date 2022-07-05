#pragma once
#include <string>
#include "Structures.h"
#include "BaseService.h";
using namespace std;

class CityService : public BaseService<CITIES>
{
private:
	string ConvertToString(char* phoneNumber);
	void SetCityName(const string sorce, CITIES& city);
	void SetPostalCode(const string sorce, CITIES& city);
	void SetPostalCode(const int nSorce, CITIES& city);
public:
	void AddCityElements(CCitiesArray& oCities);
	void ValidateArguments(const int nIndex, CCitiesArray& oCitiesArray);
	void ShowElementInfoAtIndex(const int nIndex, CCitiesArray& oCitiesArray);
	void ChangeCityName(string const& oldCityName, string const& newCityName, CCitiesArray& oCitiesArray);
	void ChangeCityName(CITIES& pOldCity, string const &newCityName);
	void ChangeCityAreaName(string const& oldCityAreaName, string const& newCityAreaName, CCitiesArray& oCitiesArray);
	void ChangeCityAreaName(CITIES& pOldCity, const string newAreaName);
	void ChangeCityPosalCode(string cityName, const int nNewCityPosalCode, CCitiesArray& oCitiesArray);
	void ChangeCityPostalCode(CITIES& pCity, const int nNewPostalCode);
};


