#pragma once
#include <string>
#include "Structures.h"
using namespace std;

class CityService
{
private:
	string ConvertToString(char* phoneNumber);
	void SetCityName(string sorce, City* city);
	void SetPostalCode(string sorce, City* city);
	void SetPostalCode(int nSorce, City* city);
public:
	void AddCityElements(CCitiesArray& oCities);
	void ValidateArguments(int nIndex, CCitiesArray& oCitiesArray);
	void ShowElementInfoAtIndex(int nIndex, CCitiesArray& oCitiesArray);
	City* GetPointerAtIndex(const int& index, CCitiesArray& oCitiesArray);
	void RemoveAt(int nIndex, int nCount, CCitiesArray& oCitiesArray);
	void ChangeCityName(string oldCityName, string newCityName, CCitiesArray& oCitiesArray);
	void ChangeCityName(City* pOldCity, string newCityName);
	void ChangeCityAreaName(string oldCityAreaName, string newCityAreaName, CCitiesArray& oCitiesArray);
	void ChangeCityAreaName(City* pOldCity, string newAreaName);
	void ChangeCityPosalCode(string cityName, int nNewCityPosalCode, CCitiesArray& oCitiesArray);
	void ChangeCityPostalCode(City* pCity, int nNewPostalCode);
};


