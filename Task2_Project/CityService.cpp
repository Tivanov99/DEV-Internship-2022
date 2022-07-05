#pragma once
#include "pch.h"
#include "CityService.h"
#include "resource.h"
#include <iostream>
#include "BaseService.cpp"

using namespace std;

string CityService::ConvertToString(char* phoneNumber) {
	string sValue;
	sValue = phoneNumber;
	return sValue;
}

void CityService::SetCityName(const string sorce, CITIES& city) {
	int nLengthOfArray = sizeof(city.szCITY_NAME) / sizeof(char);

	if (sorce.length() <= nLengthOfArray) {
		for (int i = 0; i < sorce.size(); i++)
		{
			city.szCITY_NAME[i] = sorce[i];
		}
	}
	else {
		cout << "Too long city name!" << endl;
	}
};

void CityService::SetPostalCode(const string sorce, CITIES& city) {
	int nLengthOfArray = sizeof(city.szCITY_NAME) / sizeof(char);

	if (sorce.length() <= nLengthOfArray) {
		for (int i = 0; i < sorce.size(); i++)
		{
			city.szAREA_NAME[i] = sorce[i];
		}
	}
	else {
		cout << "Too long city name!" << endl;
	}
};

void CityService::SetPostalCode(const int nSorce, CITIES& city) {
	if (nSorce > 0) {
		city.nPOSTAL_CODE = nSorce;
	}
	else {
		cout << "Too long city name!" << endl;
	}
};

void CityService::AddDefaultElements(CCitiesArray& oCities) {
	try
	{
		CITIES pBurgasCity;
		SetCityName("Bugras", pBurgasCity);
		SetPostalCode("Bugras", pBurgasCity);
		SetPostalCode(8000, pBurgasCity);

		CITIES pVarnaCity;
		SetCityName("Varna", pVarnaCity);
		SetPostalCode("Varna",pVarnaCity);
		SetPostalCode(9000, pVarnaCity);

		CITIES pSofiaCity ;
		SetCityName("Sofia", pSofiaCity);
		SetPostalCode("Sofia",pSofiaCity);
		SetPostalCode(1000, pSofiaCity);

		CITIES pPlovidCity;
		SetCityName("Plovdiv", pPlovidCity);
		SetPostalCode("Plovdiv", pPlovidCity);
		SetPostalCode(3000, pPlovidCity);

		CITIES pRuseCity ;
		SetCityName("Ruse", pRuseCity);
		SetPostalCode("Ruse", pRuseCity);
		SetPostalCode(4700, pRuseCity);

		CITIES pVelinGradCity;
		SetCityName("VelinGrad", pVelinGradCity);
		SetPostalCode("Pazardzhik", pVelinGradCity);
		SetPostalCode(6000, pVelinGradCity);

		oCities.Add(&pBurgasCity);
		oCities.Add(&pVarnaCity);
		oCities.Add(&pSofiaCity);
		oCities.Add(&pPlovidCity);
		oCities.Add(&pRuseCity);
		oCities.Add(&pVelinGradCity);
	}
	catch (const std::exception&)
	{
		cout << "Invalid 'Add' operation!" << endl;
	}
};

void CityService::ValidateArguments(const int nIndex, CCitiesArray& oCitiesArray) {
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

void CityService::ShowElementInfoAtIndex(const int nIndex, const CCitiesArray& oArray) {
	try
	{
		ValidateIndex(nIndex, oArray.GetSize());
		CITIES* pCity = NULL;
		pCity = oArray.GetAt(nIndex);
		cout << "Selected item info: " << "memory address: " << &pCity
			<< " City Name :" << pCity->szCITY_NAME
			<< " Postal Code " << pCity->nPOSTAL_CODE
			<< " Area Name " << pCity->szAREA_NAME << endl;
	}
	catch (const std::exception&)
	{
		cout << "Something goes wrong, try again!" << endl;
	}
}

void CityService::ChangeCityName(string const &oldCityName, string const &newCityName, CCitiesArray& oCitiesArray)
{
	for (size_t i = 0; i < oCitiesArray.GetSize(); i++)
	{
		string currentCityName;
		currentCityName = ConvertToString(oCitiesArray[i]->szCITY_NAME);

		if (currentCityName._Equal(oldCityName)) {
			CITIES* pOldCity = NULL;
			pOldCity = oCitiesArray[i];

			for (size_t s = 0; s < newCityName.length(); s++)
			{
				pOldCity->szCITY_NAME[s] = newCityName[s];
			}
			break;
		}
	}
}

void CityService::ChangeCityName(CITIES& pOldCity, string const &newCityName)
{
	string sCityName = ConvertToString(pOldCity.szCITY_NAME);


	for (size_t s = 0; s < newCityName.length(); s++)
	{
		pOldCity.szCITY_NAME[s] = newCityName[s];
	}
}
void CityService::ChangeCityAreaName (string const &oldCityAreaName,string const &newCityAreaName, CCitiesArray& oCitiesArray)
{
	for (size_t i = 0; i < oCitiesArray.GetSize(); i++)
	{
		string currentCityAreaName;
		currentCityAreaName = ConvertToString(oCitiesArray[i]->szAREA_NAME);

		if (currentCityAreaName._Equal(oldCityAreaName)) {
			CITIES* pOldCity = NULL;
			pOldCity = oCitiesArray[i];

			for (size_t s = 0; s < newCityAreaName.length(); s++)
			{
				pOldCity->szAREA_NAME[s] = newCityAreaName[s];
			}
			break;
		}
	}
}
void CityService::ChangeCityAreaName(CITIES& pOldCity,const string newAreaName)
{
	string sOldAreaName = ConvertToString(pOldCity.szCITY_NAME);

	for (size_t s = 0; s < newAreaName.length(); s++)
	{
		pOldCity.szAREA_NAME[s] = newAreaName[s];
	}
}
void CityService::ChangeCityPosalCode(const string cityName,const int nNewCityPosalCode, CCitiesArray& oCitiesArray)
{

	for (size_t i = 0; i < oCitiesArray.GetSize(); i++)
	{
		for (size_t i = 0; i < oCitiesArray.GetSize(); i++)
		{
			string currentCityName;
			currentCityName = ConvertToString(oCitiesArray[i]->szCITY_NAME);

			if (currentCityName._Equal(cityName)) {
				CITIES* pCity = NULL;
				pCity = oCitiesArray[i];

				pCity->nPOSTAL_CODE = nNewCityPosalCode;
				break;
			}
		}
	}
}
void CityService::ChangeCityPostalCode(CITIES& pCity, const int nNewPostalCode)
{
	if (nNewPostalCode > 0) {
		pCity.nPOSTAL_CODE = nNewPostalCode;
	}
}