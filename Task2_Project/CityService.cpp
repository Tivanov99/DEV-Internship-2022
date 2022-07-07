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
	CITIES oBurgasCity;
	CString strBurgasCityName = _T("Bugras");
	CString strBurgasAreaName = _T("Bugras");
	SetCityName(strBurgasCityName, oBurgasCity);
	SetAreaName(strBurgasAreaName, oBurgasCity);
	SetPostalCode(8000, oBurgasCity);

	CITIES oVarnaCity;
	CString strVarnaCityName = _T("Varna");
	CString strVarnaAreaName = _T("Varna");
	SetCityName(strVarnaCityName, oVarnaCity);
	SetAreaName(strVarnaAreaName, oVarnaCity);
	SetPostalCode(9000, oVarnaCity);


	CITIES oSofiaCity;
	CString strSofiaCityName = _T("Sofia");
	CString strSofiaAreaName = _T("Sofia");
	SetCityName(strSofiaCityName, oSofiaCity);
	SetAreaName(strSofiaAreaName, oSofiaCity);
	SetPostalCode(1000, oSofiaCity);


	CITIES oPlovidCity;
	CString strPlovdivCityName = _T("Plovdiv");
	CString strPlovdivAreaName = _T("Plovdiv");
	SetCityName(strPlovdivCityName, oPlovidCity);
	SetAreaName(strPlovdivAreaName, oPlovidCity);
	SetPostalCode(3000, oPlovidCity);


	CITIES oRuseCity;
	CString strRuseCityName = _T("Ruse");
	CString strRuseAreaName = _T("Ruse");
	SetCityName(strRuseCityName, oRuseCity);
	SetAreaName(strRuseAreaName, oRuseCity);
	SetPostalCode(4700, oRuseCity);


	CITIES oVelinGradCity;
	CString strVelinGradCityName = _T("VelinGrad");
	CString strVelinGradAreaName = _T("Pazardzhik");
	SetCityName(strVelinGradCityName, oVelinGradCity);
	SetAreaName(strVelinGradAreaName, oVelinGradCity);
	SetPostalCode(6000, oVelinGradCity);

	//TODO check how to coppy stack obeject to heap !

	CITIES* pBurgas = new CITIES;
	*pBurgas = oBurgasCity;

	CITIES* pVarna = new CITIES;
	*pVarna = oVarnaCity;

	CITIES* pVelinGradCity = new CITIES;
	*pVelinGradCity = oVelinGradCity;

	CITIES* pSofiaCity = new CITIES;
	*pSofiaCity = oSofiaCity;

	CITIES* pPlovidCity = new CITIES;
	*pPlovidCity = oPlovidCity;

	CITIES* pRuseCity = new CITIES;
	*pRuseCity = oRuseCity;

	oCities.Add(pBurgas);
	oCities.Add(pVarna);
	oCities.Add(pSofiaCity);
	oCities.Add(pPlovidCity);
	oCities.Add(pRuseCity);
	oCities.Add(pVelinGradCity);
};

void CityService::ShowElementInfoAtIndex(const int nIndex, const CCitiesArray& oArray)
{
	ValidateIndex(nIndex, oArray.GetCount());

	CITIES* pCity = NULL;
	pCity = oArray.GetAt(nIndex);
	CString info;
	info.Format(_T("City Name : %s, Postal Code : %d, Area Name : %s\n"),
		pCity->szCITY_NAME, pCity->lPOSTAL_CODE, pCity->szAREA_NAME);
	_tprintf(_T("%s"), (LPCTSTR)info);
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