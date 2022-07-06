#pragma once
#include <string>
#include "Structures.h"
#include "BaseService.h";
using namespace std;

class CityService : public BaseService<CITIES>
{
private:
	string ConvertToString(char* phoneNumber);
	void SetCityName(const CString &sorce, CITIES* city);
	void SetAreaName(const CString &sorce, CITIES* city);
	void SetPostalCode(const int nSorce, CITIES* city);
public:
	void AddDefaultElements(CCitiesArray& oCities) override;
	void ValidateArguments(const int nIndex, CCitiesArray& oCitiesArray);
	void ShowElementInfoAtIndex(const int nIndex, const CCitiesArray &oArray)override;
	void ChangeCityName(const CString &oldCityName, const CString &newCityName, CCitiesArray& oCitiesArray);
	void ChangeCityName(CITIES& pOldCity, const CString &newCityName);
	void ChangeCityAreaName(const CString &oldCityAreaName, const CString &newCityAreaName, CCitiesArray& oCitiesArray);
	void ChangeCityAreaName(CITIES& pOldCity, const CString &newAreaName);
	void ChangeCityPosalCode(const CString &cityName, const int nNewCityPosalCode, CCitiesArray& oCitiesArray);
	void ChangeCityPostalCode(CITIES& pCity, const int nNewPostalCode);
};


