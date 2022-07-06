#pragma once
#include "pch.h"
#include "CityService.h"
#include "resource.h"

using namespace std;

string CityService::ConvertToString(char* phoneNumber) {
	string sValue;
	sValue = phoneNumber;
	return sValue;
}

void CityService::SetCityName(const CString &sorce, CITIES* city) {
	int nLengthOfArray = sizeof(city->szCITY_NAME) / sizeof(char);

	if (sorce.GetLength() <= nLengthOfArray) {
		for (int i = 0; i < sorce.GetLength(); i++)
		{
			city->szCITY_NAME[i] = sorce[i];
		}
	}
	else {
		cout << "Too long city name!" << endl;
	}
};

void CityService::SetAreaName(const CString &sorce, CITIES* city) {
	int nLengthOfArray = sizeof(city->szCITY_NAME) / sizeof(char);

	if (sorce.GetLength() <= nLengthOfArray) {
		for (int i = 0; i < sorce.GetLength(); i++)
		{
			city->szAREA_NAME[i] = sorce[i];
		}
	}
	else {
		cout << "Too long city name!" << endl;
	}
};

void CityService::SetPostalCode(const int nSorce, CITIES* city) {
	if (nSorce > 0) {
		city->nPOSTAL_CODE = nSorce;
	}
	else {
		cout << "Too long city name!" << endl;
	}
};

void CityService::AddDefaultElements(CCitiesArray& oCities) {
		CITIES* pBurgasCity= NULL;
		pBurgasCity = new CITIES();
		CString strBurgasCityName = _T("Bugras");
		CString strBurgasAreaName = _T("Bugras");
		SetCityName(strBurgasCityName, pBurgasCity);
		SetAreaName(strBurgasAreaName, pBurgasCity);
		SetPostalCode(8000, pBurgasCity);

		CITIES* pVarnaCity = NULL;
		pVarnaCity= new CITIES();
		CString strVarnaCityName = _T("Varna");
		CString strVarnaAreaName = _T("Varna");
		SetCityName(strVarnaCityName, pVarnaCity);
		SetAreaName(strVarnaAreaName, pVarnaCity);
		SetPostalCode(9000, pVarnaCity);

		CITIES* pSofiaCity=NULL;
		pSofiaCity=new CITIES();
		CString strSofiaCityName = _T("Sofia");
		CString strSofiaAreaName = _T("Sofia");
		SetCityName(strSofiaCityName, pSofiaCity);
		SetAreaName(strSofiaAreaName, pSofiaCity);
		SetPostalCode(1000, pSofiaCity);

		CITIES* pPlovidCity=NULL;
		pPlovidCity= new CITIES();
		CString strPlovdivCityName = _T("Plovdiv");
		CString strPlovdivAreaName = _T("Plovdiv");
		SetCityName(strPlovdivCityName, pPlovidCity);
		SetAreaName(strPlovdivAreaName, pPlovidCity);
		SetPostalCode(3000, pPlovidCity);

		CITIES* pRuseCity=NULL;
		pRuseCity = new CITIES();
		CString strRuseCityName = _T("Ruse");
		CString strRuseAreaName = _T("Ruse");
		SetCityName(strRuseCityName, pRuseCity);
		SetAreaName(strRuseAreaName, pRuseCity);
		SetPostalCode(4700, pRuseCity);

		CITIES* pVelinGradCity= NULL;
		pVelinGradCity = new CITIES();
		CString strVelinGradCityName = _T("VelinGrad");
		CString strVelinGradAreaName = _T("Pazardzhik");
		SetCityName(strVelinGradCityName, pVelinGradCity);
		SetAreaName(strVelinGradAreaName, pVelinGradCity);
		SetPostalCode(6000, pVelinGradCity);


		oCities.Add(pBurgasCity);
		oCities.Add(pVarnaCity);
		oCities.Add(pSofiaCity);
		oCities.Add(pPlovidCity);
		oCities.Add(pRuseCity);
		oCities.Add(pVelinGradCity);
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

void CityService::ChangeCityName(const CString &oldCityName, const CString &newCityName, CCitiesArray& oCitiesArray)
{
	for (size_t i = 0; i < oCitiesArray.GetSize(); i++)
	{
		CString currentCityName;
		currentCityName.AppendFormat(_T("%c"),(LPCWSTR)oCitiesArray[i]->szCITY_NAME);

		if (currentCityName == oldCityName) {
			CITIES* pOldCity = NULL;
			pOldCity = oCitiesArray[i];

			for (size_t s = 0; s < newCityName.GetLength(); s++)
			{
				pOldCity->szCITY_NAME[s] = newCityName[s];
			}
			break;
		}
	}
}

void CityService::ChangeCityName(CITIES& pOldCity, const CString &newCityName)
{
	string sCityName = ConvertToString(pOldCity.szCITY_NAME);


	for (size_t s = 0; s < newCityName.GetLength(); s++)
	{
		pOldCity.szCITY_NAME[s] = newCityName[s];
	}
}
void CityService::ChangeCityAreaName(const CString &oldCityAreaName, const CString &newCityAreaName, CCitiesArray& oCitiesArray)
{
	for (size_t i = 0; i < oCitiesArray.GetSize(); i++)
	{
		CString currentCityAreaName;
		currentCityAreaName.AppendFormat(_T("%c"), (LPCWSTR)oCitiesArray[i]->szCITY_NAME);

		if (currentCityAreaName == oldCityAreaName) {
			CITIES* pOldCity = NULL;
			pOldCity = oCitiesArray[i];

			for (size_t s = 0; s < newCityAreaName.GetLength(); s++)
			{
				pOldCity->szAREA_NAME[s] = newCityAreaName[s];
			}
			break;
		}
	}
}
void CityService::ChangeCityAreaName(CITIES& pOldCity, const string newAreaName)
{
	string sOldAreaName = ConvertToString(pOldCity.szCITY_NAME);

	for (size_t s = 0; s < newAreaName.length(); s++)
	{
		pOldCity.szAREA_NAME[s] = newAreaName[s];
	}
}
void CityService::ChangeCityPosalCode(const CString &cityName, const int nNewCityPosalCode, CCitiesArray& oCitiesArray)
{

	for (size_t i = 0; i < oCitiesArray.GetSize(); i++)
	{
		for (size_t i = 0; i < oCitiesArray.GetSize(); i++)
		{
			CString currentCityName;
			currentCityName.AppendFormat(_T("%c"), (LPCWSTR)oCitiesArray[i]->szCITY_NAME);

			if (currentCityName == cityName) {
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