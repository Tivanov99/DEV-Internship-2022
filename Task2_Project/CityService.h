#pragma once
#include <string>
#include "Structures.h"
#include "BaseService.h";
using namespace std;

class CityService : public BaseService<CITIES>
{
private:
	//<summary>Функция задаваща сойност на 'CITY_NAME' на подаден като аругмент показател</summary>
	void SetCityName(const CString &sorce, CITIES* city);
	//<summary>Функция задаваща сойност на 'AREA_NAME' на подаден като аругмент показател</summary>
	void SetAreaName(const CString &sorce, CITIES* city);
	//<summary>Функция задаваща сойност на 'POSTAL_CODE' на подаден като аругмент показател</summary>
	void SetPostalCode(const int nSorce, CITIES* city);
public:

	CityService()
	{

	}
	~CityService() {

	};
	//<summary>Функция добавяща всички дефоутни елементи в подаден масив като аргумент, пренаписана от базов клас 'BaseService' </summary>
	void AddDefaultElements(CCitiesArray& oCities) override;
	//<summary>Функция принтираща информация за обект намиращ се на позицията на nIndex, пренаписана от базов клас 'BaseService'.</summary>
	void ShowElementInfoAtIndex(const int nIndex, const CCitiesArray &oArray)override;
	//<summary>Функция променяща 'CITY_NAME' стойността на обект чието текущо име е подадено като първи аргумент 'oldCityName'.</summary>
	void ChangeCityName(const CString &oldCityName, const CString &newCityName, CCitiesArray& oCitiesArray);
	//<summary>Функция променяща 'CITY_NAME' на обект подаден като аргумент.</summary>
	void ChangeCityName(CITIES& pOldCity, const CString &newCityName);
	//<summary>Функция променяща 'AREA_NAME' стойността на обект чието текущо име е подадено като първи аргумент 'oldCityAreaName'.</summary>
	void ChangeCityAreaName(const CString &oldCityAreaName, const CString &newCityAreaName, CCitiesArray& oCitiesArray);
	//<summary>Функция променяща 'AREA_NAME' на обект подаден като аргумент.</summary>
	void ChangeCityAreaName(CITIES& pOldCity, const CString &newAreaName);
	//<summary>Функция променяща 'POSTAL_CODE' стойността на обект чието текущо име е подадено като първи аргумент 'cityName'.</summary>
	void ChangeCityPosalCode(const CString &cityName, const int nNewCityPosalCode, CCitiesArray& oCitiesArray);
	//<summary>Функция променяща 'POSTAL_CODE' стойността на обект подаден като първи аргумент.</summary>
	void ChangeCityPostalCode(CITIES& pCity, const int nNewPostalCode);
};


