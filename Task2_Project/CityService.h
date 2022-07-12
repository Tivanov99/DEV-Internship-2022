#pragma once
#include <string>
#include "Structures.h"
#include "BaseService.h";
using namespace std;

class CityService : public BaseService<CITIES>
{
private:
	///<summary>Функция задаваща сойност на 'CITY_NAME' на подаден като аругмент показател</summary>
	/// <param name="strCityName">Името на град което ще бъде зададено като стойност</param>
	/// <param name="oCity">Обект чието "szCITY_NAME" ще бъде зададено с подадената стойност от "strCityName"</param>
	void SetCityName(const CString &strCityName, CITIES& oCity);

	///<summary>Функция задаваща сойност на 'AREA_NAME' на подаден като аругмент показател</summary>
	/// <param name="strAreaName">Името на област което ще бъде зададено като стойност</param>
	/// <param name="oCity"> Името на околност което ще бъде зададено като стойност на "szAREA_NAME"</param>
	void SetAreaName(const CString &strAreaName, CITIES& oCity);

	///<summary>Функция задаваща сойност на 'POSTAL_CODE' на подаден като аругмент показател</summary>
	/// <param name="nPostalCode">Пощенски код който ще бъде зададен като стойност</param>
	/// <param name="oCity">Името на околност което ще бъде зададено като стойност на "lPOSTAL_CODE"</param>
	void SetPostalCode(const int nPostalCode, CITIES& oCity);

	CCitiesArray oCities;
public:
	CityService();
	~CityService();
	
	///<summary>Функция променяща 'CITY_NAME' стойността на обект чието текущо име е подадено като аргумент 'strCurrentCityName'.</summary>
	/// <param name="strCurrentCityName">Текущото име на градът.</param>
	/// <param name="strNewCityName">Новото име на градът.</param>
	/// <param name="oCitiesArray">Масивът в който ще се търси град по подаденото текущо име "strCurrentCityName".</param>
	void ChangeCityName(const CString &strCurrentCityName, const CString &strNewCityName, CCitiesArray& oCitiesArray);

	///<summary>Функция променяща 'CITY_NAME' на обект подаден като аргумент.</summary>
	/// <param name="оOldCity">Референция към обект.</param>
	/// <param name="newCityName">Новото име на градът.</param>
	void ChangeCityName(CITIES& оOldCity, const CString &newCityName);

	///<summary>Функция променяща 'AREA_NAME' стойността на обект чието текущо име е подадено като аргумент 'oldCityAreaName'.</summary>
	/// <param name="newCityName">Текущото име на областта.</param>
	/// <param name="strNewCityAreaName">Новото име на областта.</param>
	/// <param name="oCitiesArray">Масив в който ще се търси обект по стойността "strCurrentCityAreaName".</param>
	void ChangeCityAreaName(const CString &strCurrentCityAreaName, const CString &strNewCityAreaName, CCitiesArray& oCitiesArray);

	///<summary>Функция променяща 'AREA_NAME' на обект подаден като аргумент.</summary>
	/// <param name="pOldCity">Референция към обект.</param>
	/// <param name="strNewAreaName">Стойност с която ще бъде подменена текущата намираща се в "szAREA_NAME".</param>
	void ChangeCityAreaName(CITIES& oOldCity, const CString &strNewAreaName);

	///<summary>Функция променяща 'POSTAL_CODE' стойността на обект чието текущо име е подадено като аргумент 'strCityName'.</summary>
	/// <param name="strCityName">Текущото име на градът.</param>
	/// <param name="nNewCityPosalCode">Нов пощенски код.</param>
	/// <param name="oCitiesArray">Масив в който ще се търси обект по стоиността 'strCityName'.param>
	void ChangeCityPosalCodeByCityName(const CString &strCityName, const int nNewCityPosalCode, CCitiesArray& oCitiesArray);
	
	///<summary>Функция променяща 'POSTAL_CODE' стойността на обект подаден като аргумент 'pCity'.</summary>
	/// <param name="оCity">Референция към обект.</param>
	/// <param name="nNewPostalCode">Нов пощенски код.</param>
	void ChangeCityPostalCode(CITIES& оCity, const int nNewPostalCode);

	///<summary>
		/// Функция добавяща всички дефоутни елементи в подаден масив като
		/// аргумент, пренаписана от базов клас 'BaseService'.
	///  </summary>
	/// <param name="citiesArray">Масив в който ще се добавят всички стойности.</param>
	void AddDefaultElements(CCitiesArray& citiesArray) override;

	///<summary>Функция принтираща информация за обект намиращ се на позицията на nIndex, пренаписана от базов клас 'BaseService'.</summary>
	/// <param name="nIndex">Позиция в масива.</param>
	/// <param name="oArray">Масив със стойности.</param> 
	void ShowElementInfoAtIndex(const int nIndex, const CCitiesArray& oArray)override;
};


