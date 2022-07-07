#pragma once
#include "pch.h"
#include "CityService.h"
#include "resource.h"

using namespace std;

void CityService::SetCityName(const CString& sorce, CITIES& city) {
	int nLengthOfArray = sizeof(city.szCITY_NAME) / sizeof(char);

	//TODO : check copy from one array to other, already exist method !

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

	//TODO : check copy from one array to other, already exist method !

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
	if (nSorce > 0) 
	city.lPOSTAL_CODE = nSorce;
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

	CITIES* pCity = oArray.GetAt(nIndex);

	if (pCity == NULL)
		return;

	CString info;
	info.Format(_T("City Name : %s, Postal Code : %d, Area Name : %s\n"),
		pCity->szCITY_NAME, pCity->lPOSTAL_CODE, pCity->szAREA_NAME);
	_tprintf(_T("%s"), (LPCTSTR)info);
};

void CityService::ChangeCityName(const CString& strCityName, const CString& strNewCityName, CCitiesArray& oCitiesArray)
{
	for (INT_PTR i = 0; i < oCitiesArray.GetCount(); i++)
	{
		CITIES* pCity = oCitiesArray.GetAt(i);
		if (pCity == NULL)
			continue;

		CString strCurrentCityName;
		strCurrentCityName.Format(_T("%s"), pCity->szCITY_NAME);

		if (strCurrentCityName == strCityName)
		{
			//TODO : check copy from one array to other, already exist method !

			//pOldCity->szCITY_NAME[s] = newCityName[s];
			break;
		}
	}
};

void CityService::ChangeCityName(CITIES& pOldCity, const CString& newCityName)
{
	//TODO : check copy from one array to other, already exist method !

	for (size_t s = 0; s < newCityName.GetLength(); s++)
	{
		pOldCity.szCITY_NAME[s] = newCityName[s];
	}
}
void CityService::ChangeCityAreaName(const CString& strCityAreaName, const CString& strNewCityAreaName, CCitiesArray& oCitiesArray)
{
	for (INT_PTR i = 0; i < oCitiesArray.GetSize(); i++)
	{
		CITIES* pCurrentCity = oCitiesArray.GetAt(i);
		if (pCurrentCity == NULL)
			continue;

		CString strCurrentCityAreaName;
		strCurrentCityAreaName.Format(_T("%s"), pCurrentCity->szAREA_NAME);

		if (strCurrentCityAreaName == strCityAreaName)
		{
			//TODO : check copy from one array to other, already exist method !
			/*for (size_t s = 0; s < strNewCityAreaName.GetLength(); s++)
			{
				pOldCity->szAREA_NAME[s] = strNewCityAreaName[s];
			}*/
			break;
		}
	}
};
void CityService::ChangeCityAreaName(CITIES& pOldCity, const CString& strNewAreaName)
{
	//TODO : check copy from one array to other, already exist method !

	for (size_t s = 0; s < strNewAreaName.GetLength(); s++)
	{
		pOldCity.szAREA_NAME[s] = strNewAreaName[s];
	}
};

void CityService::ChangeCityPosalCode(const CString& strCityName, const int nNewCityPosalCode, CCitiesArray& oCitiesArray)
{
	for (INT_PTR i = 0; i < oCitiesArray.GetSize(); i++)
	{
		CITIES* pCurrentCity = oCitiesArray.GetAt(i);
		if (pCurrentCity == NULL)
			continue;

		CString currentCityName;
		currentCityName.Format(_T("%s"), pCurrentCity->szCITY_NAME);

		if (currentCityName == strCityName) {

			//TODO : check copy from one array to other, already exist method !

			pCurrentCity->lPOSTAL_CODE = nNewCityPosalCode;
			break;
		}
	}
};

void CityService::ChangeCityPostalCode(CITIES& pCity, const int nNewPostalCode)
{
	if (nNewPostalCode > 0 )
	{
		pCity.lPOSTAL_CODE = nNewPostalCode;
	}
};