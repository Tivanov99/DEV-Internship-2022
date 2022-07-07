#pragma once
#include "pch.h"
#include "CityService.h"
#include "resource.h"

using namespace std;


void CityService::SetCityName(const CString& sorce, CITIES& city) {
	int nLengthOfArray = sizeof(city.szCITY_NAME) / sizeof(char);

	if (sorce.GetLength() <= nLengthOfArray) {
		for (int i = 0; i < sorce.GetLength(); i++)
		{
			city.szCITY_NAME[i] = sorce[i];
		}
	}
	else {
		cout << "Too long city name!" << endl;
	}
};

void CityService::SetAreaName(const CString& sorce, CITIES& city) {
	int nLengthOfArray = sizeof(city.szCITY_NAME) / sizeof(char);

	if (sorce.GetLength() <= nLengthOfArray) {
		for (int i = 0; i < sorce.GetLength(); i++)
		{
			city.szAREA_NAME[i] = sorce[i];
		}
	}
	else {
		cout << "Too long city name!" << endl;
	}
};

void CityService::SetPostalCode(const int nSorce, CITIES& city)
{
	if (nSorce > 0) {
		city.lPOSTAL_CODE = nSorce;
	}
	else {
		cout << "Too long city name!" << endl;
	}
};

void CityService::AddDefaultElements(CCitiesArray& oCities)
{
	CITIES pBurgasCity;
	//pBurgasCity = new CITIES();
	CString strBurgasCityName = _T("Bugras");
	CString strBurgasAreaName = _T("Bugras");
	SetCityName(strBurgasCityName, pBurgasCity);
	SetAreaName(strBurgasAreaName, pBurgasCity);
	SetPostalCode(8000, pBurgasCity);

	CITIES pVarnaCity;
	//pVarnaCity = new CITIES();
	CString strVarnaCityName = _T("Varna");
	CString strVarnaAreaName = _T("Varna");
	SetCityName(strVarnaCityName, pVarnaCity);
	SetAreaName(strVarnaAreaName, pVarnaCity);
	SetPostalCode(9000, pVarnaCity);

	/*CITIES* pSofiaCity = NULL;
	pSofiaCity = new CITIES();
	CString strSofiaCityName = _T("Sofia");
	CString strSofiaAreaName = _T("Sofia");
	SetCityName(strSofiaCityName, pSofiaCity);
	SetAreaName(strSofiaAreaName, pSofiaCity);
	SetPostalCode(1000, pSofiaCity);

	CITIES* pPlovidCity = NULL;
	pPlovidCity = new CITIES();
	CString strPlovdivCityName = _T("Plovdiv");
	CString strPlovdivAreaName = _T("Plovdiv");
	SetCityName(strPlovdivCityName, pPlovidCity);
	SetAreaName(strPlovdivAreaName, pPlovidCity);
	SetPostalCode(3000, pPlovidCity);

	CITIES* pRuseCity = NULL;
	pRuseCity = new CITIES();
	CString strRuseCityName = _T("Ruse");
	CString strRuseAreaName = _T("Ruse");
	SetCityName(strRuseCityName, pRuseCity);
	SetAreaName(strRuseAreaName, pRuseCity);
	SetPostalCode(4700, pRuseCity);

	CITIES* pVelinGradCity = NULL;
	pVelinGradCity = new CITIES();
	CString strVelinGradCityName = _T("VelinGrad");
	CString strVelinGradAreaName = _T("Pazardzhik");
	SetCityName(strVelinGradCityName, pVelinGradCity);
	SetAreaName(strVelinGradAreaName, pVelinGradCity);
	SetPostalCode(6000, pVelinGradCity);*/

	//TODO check how to coppy stack obeject to heap !

	CITIES* pBurgas = new CITIES(pBurgasCity);
	CITIES* pVarna = new CITIES(pVarnaCity);

	oCities.Add(pBurgas);
	oCities.Add(pVarna);
	//oCities.Add(pSofiaCity);
	//oCities.Add(pPlovidCity);
	//oCities.Add(pRuseCity);
	//oCities.Add(pVelinGradCity);
};

void CityService::ShowElementInfoAtIndex(const int nIndex, const CCitiesArray& oArray) {
	try
	{
		ValidateIndex(nIndex, oArray.GetSize());

		CITIES* pCity = NULL;
		pCity = oArray.GetAt(nIndex);

	/*	CString strCityName = pCity->szCITY_NAME;
		CString strAreaName = pCity->szAREA_NAME;*/

		cout << "Selected item info: " << "memory address: " << &pCity
			<< " City Name :" << strCityName
			<< " Postal Code " << pCity->lPOSTAL_CODE
			<< " Area Name " <<  *strAreaName << endl;
	}
	catch (const std::exception&)
	{
		cout << "Something goes wrong, try again!" << endl;
	}
};

void CityService::ChangeCityName(const CString& strCurrentCityName, const CString& newCityName, CCitiesArray& oCitiesArray)
{
	for (INT_PTR i = 0; i < oCitiesArray.GetCount(); i++)
	{
		CITIES* pCity = oCitiesArray.GetAt(i);
		if (pCity == NULL)
			continue;

		CString currentCityName;
		currentCityName.AppendFormat(_T("%s"), (LPCWSTR)pCity->szCITY_NAME);

		if (currentCityName == strCurrentCityName) {
		

			//TODO : check copy from one array to other, already exist method !
			/*pOldCity->szCITY_NAME[s] = newCityName[s];
			}
			break;*/
		}
	}
};

void CityService::ChangeCityName(CITIES& pOldCity, const CString& newCityName)
{
	for (size_t s = 0; s < newCityName.GetLength(); s++)
	{
		pOldCity.szCITY_NAME[s] = newCityName[s];
	}
}
void CityService::ChangeCityAreaName(const CString& oldCityAreaName, const CString& newCityAreaName, CCitiesArray& oCitiesArray)
{
	for (size_t i = 0; i < oCitiesArray.GetSize(); i++)
	{
		CString currentCityAreaName = oCitiesArray[i]->szCITY_NAME;

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
};
void CityService::ChangeCityAreaName(CITIES& pOldCity, const CString& newAreaName)
{
	for (size_t s = 0; s < newAreaName.GetLength(); s++)
	{
		pOldCity.szAREA_NAME[s] = newAreaName[s];
	}
};

void CityService::ChangeCityPosalCode(const CString& cityName, const int nNewCityPosalCode, CCitiesArray& oCitiesArray)
{

	for (size_t i = 0; i < oCitiesArray.GetSize(); i++)
	{
		for (size_t i = 0; i < oCitiesArray.GetSize(); i++)
		{
			CString currentCityName = oCitiesArray[i]->szCITY_NAME;

			if (currentCityName == cityName) {
				CITIES* pCity = NULL;
				pCity = oCitiesArray[i];

				pCity->lPOSTAL_CODE = nNewCityPosalCode;
				break;
			}
		}
	}
};

void CityService::ChangeCityPostalCode(CITIES& pCity, const int nNewPostalCode)
{
	if (nNewPostalCode > 0) {
		pCity.lPOSTAL_CODE = nNewPostalCode;
	}
};