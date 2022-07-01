#pragma once
#include <string>
#include "Structures.h"
#include <iostream>
using namespace std;


class CityService
{
private:
	string ConvertToString(char* phoneNumber) {
		string sValue;
		sValue = phoneNumber;
		return sValue;
	}
	void SetCityName(string sorce, City* city) {
		int nLengthOfArray = sizeof(city->CITY_NAME) / sizeof(char);

		if (sorce.length() <= nLengthOfArray) {
			for (int i = 0; i < sorce.size(); i++)
			{
				city->CITY_NAME[i] = sorce[i];
			}
		}
		else {
			cout << "Too long city name!" << endl;
		}
	};
	void SetPostalCode(string sorce, City* city) {
		int nLengthOfArray = sizeof(city->CITY_NAME) / sizeof(char);

		if (sorce.length() <= nLengthOfArray) {
			for (int i = 0; i < sorce.size(); i++)
			{
				city->AREA_NAME[i] = sorce[i];
			}
		}
		else {
			cout << "Too long city name!" << endl;
		}
	};
	void SetPostalCode(int nSorce, City* city) {
		if (nSorce>0) {
			city->nPOSTAL_CODE = nSorce;
		}
		else {
			cout << "Too long city name!" << endl;
		}
	};
public:
	CityService()
	{

	};

	void AddDefaultPhoneNumbersElements(CCitiesArray& oCities) {
		try
		{
			City* pBurgasCity = NULL;
			pBurgasCity = new City();
			SetCityName("Bugras", pBurgasCity);
			SetPostalCode("Bugras", pBurgasCity);
			SetPostalCode(8000, pBurgasCity);

			City* pVarnaCity = NULL;
			pVarnaCity = new City();
			SetCityName("Varna", pVarnaCity);
			SetPostalCode("Varna", pBurgasCity);
			SetPostalCode(9000, pBurgasCity);

			City* pSofiaCity = NULL;
			pSofiaCity = new City();
			SetCityName("Sofia", pSofiaCity);
			SetPostalCode("Sofia", pBurgasCity);
			SetPostalCode(1000, pBurgasCity);

			City* pPlovidCity = NULL;
			pPlovidCity = new City();
			SetCityName("Plovdiv", pPlovidCity);
			SetPostalCode("Plovdiv", pBurgasCity);
			SetPostalCode(3000, pBurgasCity);

			City* pRuseCity = NULL;
			pRuseCity = new City();
			SetCityName("Ruse", pRuseCity);
			SetPostalCode("Ruse", pBurgasCity);
			SetPostalCode(4700, pBurgasCity);

			City* pVelinGradCity = NULL;
			pVelinGradCity = new City();
			SetCityName("VelinGrad", pVelinGradCity);
			SetPostalCode("Pazardzhik", pBurgasCity);
			SetPostalCode(6000, pBurgasCity);

			oCities.Add(pBurgasCity);
			oCities.Add(pVarnaCity);
			oCities.Add(pSofiaCity);
			oCities.Add(pPlovidCity);
			oCities.Add(pRuseCity);
			oCities.Add(pVelinGradCity);
		}
		catch (const std::exception&)
		{
			cout << "Invalid 'Add' operation!" << endl;
		}

	}

	void ValidateArguments(int nIndex, CCitiesArray& oCitiesArray) {
		if (oCitiesArray.IsEmpty())
		{
			throw invalid_argument("The array is empty!");
		}
		else if (nIndex > oCitiesArray.GetCount()) {
			throw invalid_argument("Index out of range!");
		}
		else if (nIndex < 0) {
			throw invalid_argument("Index should be possitive!");
		}
	};

	void ShowElementInfoAtIndex(int nIndex, CCitiesArray& oCitiesArray) {
		try
		{
			ValidateArguments(nIndex, oCitiesArray);
			City* pCity = NULL;
			pCity = oCitiesArray.GetAt(nIndex);
			cout << "Selected item info: " << "memory address: " << &pCity
				<< " City Name :" << pCity->CITY_NAME
				<< " Postal Code " << pCity->nPOSTAL_CODE
				<< " Area Name " << pCity->AREA_NAME << endl;
		}
		catch (const std::exception&)
		{
			cout << "Something goes wrong, try again!" << endl;
		}
	}

	City* GetPointerAtIndex(int nIndex, CCitiesArray& oCitiesArray) {
		try
		{
			ValidateArguments(nIndex, oCitiesArray);

			City* pCity = NULL;
			pCity = oCitiesArray.ElementAt(nIndex);
			return pCity;
		}
		catch (exception& ex)
		{
			cout << ex.what() << endl;
		}
	};

	void RemoveAt(int nIndex, int nCount, CCitiesArray& oCitiesArray) {
		try
		{
			ValidateArguments(nIndex, oCitiesArray);
			oCitiesArray.RemoveAt(nIndex, nCount);
			oCitiesArray.FreeExtra();
		}
		catch (exception ex)
		{
			cout << ex.what();
		}
	};

	void ChangeCityName(string oldCityName, string newCityName, CCitiesArray& oCitiesArray)
	{

		for (size_t i = 0; i < oCitiesArray.GetSize(); i++)
		{
			string currentCityName;
			currentCityName = ConvertToString(oCitiesArray[i]->CITY_NAME);

			if (currentCityName._Equal(oldCityName)) {
				City* pOldCity = NULL;
				pOldCity = oCitiesArray[i];

				for (size_t s = 0; s < currentCityName.length(); s++)
				{
					pOldCity->CITY_NAME[s] = newCityName[s];
				}
				break;
			}
		}
	}
	void ChangeCityName(City* pOldCity, string newCityName)
	{
		string sCityName = ConvertToString(pOldCity->CITY_NAME);


		for (size_t s = 0; s < newCityName.length(); s++)
		{
			pOldCity->CITY_NAME[s] = newCityName[s];
		}
	}
	void ChangeCityAreaName(string oldCityAreaName, string newCityAreaName, CCitiesArray& oCitiesArray)
	{

		for (size_t i = 0; i < oCitiesArray.GetSize(); i++)
		{
			string currentCityAreaName;
			currentCityAreaName = ConvertToString(oCitiesArray[i]->AREA_NAME);

			if (currentCityAreaName._Equal(oldCityAreaName)) {
				City* pOldCity = NULL;
				pOldCity = oCitiesArray[i];

				for (size_t s = 0; s < currentCityAreaName.length(); s++)
				{
					pOldCity->AREA_NAME[s] = newCityAreaName[s];
				}
				break;
			}
		}
	}
	void ChangeCityAreaName(City* pOldCity, string newAreaName)
	{
		string sOldAreaName = ConvertToString(pOldCity->CITY_NAME);


		for (size_t s = 0; s < newAreaName.length(); s++)
		{
			pOldCity->AREA_NAME[s] = newAreaName[s];
		}
	}
	void ChangeCityName(string oldCityName, string newCityName, CCitiesArray& oCitiesArray)
	{

		for (size_t i = 0; i < oCitiesArray.GetSize(); i++)
		{
			string currentCityName;
			currentCityName = ConvertToString(oCitiesArray[i]->CITY_NAME);

			if (currentCityName._Equal(oldCityName)) {
				City* pOldCity = NULL;
				pOldCity = oCitiesArray[i];

				for (size_t s = 0; s < currentCityName.length(); s++)
				{
					pOldCity->CITY_NAME[s] = newCityName[s];
				}
				break;
			}
		}
	}
	void ChangeCityPosalCode(string cityName, int nNewCityPosalCode, CCitiesArray& oCitiesArray)
	{

		for (size_t i = 0; i < oCitiesArray.GetSize(); i++)
		{
			for (size_t i = 0; i < oCitiesArray.GetSize(); i++)
			{
				string currentCityName;
				currentCityName = ConvertToString(oCitiesArray[i]->CITY_NAME);

				if (currentCityName._Equal(cityName)) {
					City* pCity = NULL;
					pCity = oCitiesArray[i];

					pCity->nPOSTAL_CODE = nNewCityPosalCode;
					break;
				}
			}
		}
	}
	void ChangeCityPostalCode(City* pCity, int nNewPostalCode)
	{
		if (nNewPostalCode > 0) {
			pCity->nPOSTAL_CODE = nNewPostalCode;
		}
	}
};


