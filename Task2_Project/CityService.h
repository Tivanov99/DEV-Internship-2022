#pragma once
#include <string>
#include "Structures.h"
#include "BaseService.h";
using namespace std;

class CityService : public BaseService<CITIES>
{
private:

	///<summary>Функция задаваща всички стойности на подаден като аругмент показател</summary>
	///<param name="strCityName">Името на град което ще бъде зададено като стойност</param>
	///<param name="strAreaName">Името на област което ще бъде зададено като стойност</param>
	///<param name="oCity">Обект чието "szCITY_NAME" ще бъде зададено с подадената стойност от "strCityName"</param>
	///<param name="lPostalCode">Обект чието "szCITY_NAME" ще бъде зададено с подадената стойност от "strCityName"</param>
	void SetCityData(const CString& strCityName, const CString& strAreaNamem, const long lPostalCode, CITIES& oCity);

	CCitiesArray citiesArray;
public:
	CityService();
	~CityService();

	///<summary>Функция връщата указател като резултат която търси обект по име на област'strCityAreaName'.</summary>
	///<param name="strCityAreaName">Име на област</param>
	CITIES* GetCityByAreaName(const CString& strCityAreaName);

	///<summary>Функция връщата указател като резултат която търси обект по име на град'strCityName'.</summary>
	///<param name="strCityName">Име на град</param>
	CITIES* GetCityByCityName(const CString& strCityName);

	///<summary>Функция връщата указател като резултат която търси обект по пощенски код 'lPostalCode'.</summary>
	///<param name="lPostalCode">Пощенски код</param>
	CITIES* GetCityByPostalCode(const long lPostalCode);

	///<summary>
		/// Функция променяща 'CITY_NAME' стойността на обект
		///  чието текущо име е подадено като аргумент 'strCurrentCityName'.
	///</summary>
	///<param name="strCurrentCityName">Текущото име на градът.</param>
	///<param name="strNewCityName">Новото име на градът.</param>
	///<param name="oCitiesArray">Масивът в който ще се търси град по подаденото текущо име "strCurrentCityName".</param>
	void ChangeCityName(const CString& strCurrentCityName, const CString& strNewCityName);

	///<summary>Функция променяща 'CITY_NAME' на обект подаден като аргумент.</summary>
	///<param name="оCity">Референция към обект.</param>
	///<param name="newCityName">Новото име на градът.</param>
	void ChangeCityName(CITIES& оCity, const CString& strNewCityName);

	///<summary>
		/// Функция променяща 'AREA_NAME' стойността на обект
		///чието текущо име е подадено като аргумент 'strCurrentCityAreaName'.
	///</summary>
	///<param name="newCityName">Текущото име на областта.</param>
	///<param name="strNewCityAreaName">Новото име на областта.</param>
	///<param name="oCitiesArray">Масив в който ще се търси обект по стойността "strCurrentCityAreaName".</param>
	void ChangeCityAreaName(const CString& strCurrentCityAreaName, const CString& strNewCityAreaName);

	///<summary>Функция променяща 'AREA_NAME' на обект подаден като аргумент.</summary>
	///<param name="oCity">Референция към обект.</param>
	///<param name="strNewAreaName">Стойност с която ще бъде подменена текущата намираща се в "szAREA_NAME".</param>
	void ChangeCityAreaName(CITIES& oCity, const CString& strNewAreaName);

	///<summary>
		///Функция променяща 'POSTAL_CODE' стойността на обект
		///чието текущо име е подадено като аргумент 'strCityName'.
	///</summary>
	///<param name="strCityName">Текущото име на градът.</param>
	///<param name="nNewCityPosalCode">Нов пощенски код.</param>
	///<param name="oCitiesArray">Масив в който ще се търси обект по стоиността 'strCityName'.param>
	void ChangeCityPosalCodeByCityName(const CString& strCityName, const long lNewCityPosalCode);
	///<summary>Функция променяща 'POSTAL_CODE' стойността на обект подаден като аргумент 'pCity'.</summary>
	///<param name="оCity">Референция към обект.</param>
	///<param name="nNewPostalCode">Нов пощенски код.</param>
	void ChangeCityPostalCode(CITIES& оCity, const long lNewPostalCode);


	///<summary>
		/// Функция добавяща всички дефоутни елементи в подаден масив като
		/// аргумент, пренаписана от базов клас 'BaseService'.
	///</summary>
	/// <param name="citiesArray">Масив в който ще се добавят всички стойности.</param>
	void AddDefaultElements() override;

	///<summary>
		///Функция принтираща информация за обект намиращ
		///се на позицията на nIndex, пренаписана от базов клас 'BaseService'.
	///</summary>
	///<param name="nIndex">Позиция в масива.</param>
	///<param name="oArray">Масив със стойности.</param> 
	void ShowElementInfoAtIndex(const long lIndex)override;
};


