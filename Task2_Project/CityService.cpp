#pragma once
#include "pch.h"
#include "CityService.h"
#include "resource.h"

using namespace std;

CityService::CityService(){};
CityService::~CityService()
{
	//todo: use for 
	while (citiesArray.GetCount() > 0)
	{
		delete citiesArray.GetAt(citiesArray.GetCount() - 1);
		citiesArray[i] = NULL;
	}
	citiesArray.RemoveAll();
};	

CITIES* CityService::GetByAreaName(const CString& strCityAreaName)
{
	for (INT_PTR i = 0; i < m_oCitiesArray.GetCount(); i++)
	{
		//TODO: CHECLK FOR NULL
		CITIES* pCity = citiesArray.GetAt(i);
		if (pCity == NULL)
			continue;

		CString srtCurrentCityName;
		srtCurrentCityName.Format(_T("%s"), pCity->szAREA_NAME);
		if (srtCurrentCityName != strCityAreaName)
			continue;

		return pCity;
	}
};

CITIES* CityService::GetByCityName(const CString& strCityName)
{
	for (INT_PTR i = 0; i < citiesArray.GetCount(); i++)
	{
		CITIES* pCity = citiesArray.GetAt(i);
		CString srtCurrentCityName;
		srtCurrentCityName.Format(_T("%s"), pCity->szAREA_NAME);
		if (srtCurrentCityName != strCityName)
			continue;

		return pCity;
	}
};

CITIES* CityService::GetByPostalCode(const long lPostalCode)
{
	for (INT_PTR i = 0; i < citiesArray.GetCount(); i++)
	{
		CITIES* pCity = citiesArray.GetAt(i);
		
		if (pCity->lPOSTAL_CODE != lPostalCode)
			continue;

		return pCity;
	}
};

void CityService::SetCityName(const CString& strCityName, CITIES& oCity)
{
	int nLengthOfArray = sizeof(oCity.szCITY_NAME) / sizeof(char);

	if (strCityName.GetLength() > nLengthOfArray)
		return;
	TCHAR* szBuffer = _tcsdup(strCityName);
	_tcscpy_s(oCity.szCITY_NAME, szBuffer);
};

void CityService::SetAreaName(const CString& strAreaName, CITIES& oCity)
{
	int nLengthOfArray = sizeof(oCity.szAREA_NAME) / sizeof(TCHAR);
	if (strAreaName.GetLength() > nLengthOfArray)
		return;

	TCHAR* szBuffer = _tcsdup(strAreaName);
	_tcscpy_s(oCity.szAREA_NAME, szBuffer);
};
//TODO: REMOVE
void CitySeEMOrvice::SetPostalCode(const long lSorce, CITIES& oCity)
{
	if (lSorce > 0)
		oCity.lPOSTAL_CODE = lSorce;
};

void CityService::AddDefaultElements()
{
	CITIES oBurgasCity;
	CString strBurgasCityName = _T("Bugras");
	CString strBurgasAreaName = _T("Bugras");
	SetCityName(strBurgasCityName, oBurgasCity);
	SetAreaName(strBurgasAreaName, oBurgasCity);
	SetPostalCode(8000, oBurgasCity);

	//TODO: CHECK HERE, SKIP CSTRING OBEJCTS
	CITIES oVarnaCity;
	consdCString strVarnaCityName = _T("Varna");
	consdCString strVarnaAreaName = _T("Varna");
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

	citiesArray.Add(pBurgas);
	citiesArray.Add(pVarna);
	citiesArray.Add(pSofiaCity);
	citiesArray.Add(pPlovidCity);
	citiesArray.Add(pRuseCity);
	citiesArray.Add(pVelinGradCity);
};

void CityService::ShowElementInfoAtIndex(const long lIndex)
{
	if (lIndex > citiesArray.GetCount())
		return;

	CITIES* pCity = citiesArray.GetAt(lIndex);

	if (pCity == NULL)
		return;

	CString info;
	info.Format(_T("City Name : %s, Postal Code : %d, Area Name : %s\n"),
		pCity->szCITY_NAME, pCity->lPOSTAL_CODE, pCity->szAREA_NAME);
	_tprintf(_T("%s"), (LPCTSTR)info);
};

void CityService::ChangeCityName(const CString& strCityName, const CString& strNewCityName)
{
	for (INT_PTR i = 0; i < citiesArray.GetCount(); i++)
	{
		CITIES* pCity = citiesArray.GetAt(i);
		if (pCity == NULL)
			continue;

		CString strCurrentCityName;
		strCurrentCityName.Format(_T("%s"), pCity->szCITY_NAME);

		if (strCurrentCityName == strCityName)
		{
			TCHAR* szBuffer = _tcsdup(strNewCityName);
			_tcscpy_s(pCity->szCITY_NAME, szBuffer);
			break;
		}
	}
};

void CityService::ChangeCityName(CITIES& oCity, const CString& strNewCityName)
{
	TCHAR* szBuffer = _tcsdup(strNewCityName);
	_tcscpy_s(oCity.szCITY_NAME, szBuffer);
}
void CityService::ChangeCityAreaName(const CString& strCityAreaName, const CString& strNewCityAreaName)
{
	for (INT_PTR i = 0; i < citiesArray.GetSize(); i++)
	{
		CITIES* pCurrentCity = citiesArray.GetAt(i);
		if (pCurrentCity == NULL)
			continue;

		CString strCurrentCityAreaName;
		strCurrentCityAreaName.Format(_T("%s"), pCurrentCity->szAREA_NAME);

		if (strCurrentCityAreaName == strCityAreaName)
		{
			TCHAR* szBuffer = _tcsdup(strNewCityAreaName);
			_tcscpy_s(pCurrentCity->szAREA_NAME, szBuffer);
			break;
		}
	}
};
void CityService::ChangeCityAreaName(CITIES& pOldCity, const CString& strNewAreaName)
{
	TCHAR* szBuffer = _tcsdup(strNewAreaName);
	_tcscpy_s(pOldCity.szAREA_NAME, szBuffer);
};

void CityService::ChangeCityPosalCodeByCityName(const CString& strCityName, const long lNewCityPosalCode)
{
	for (INT_PTR i = 0; i < citiesArray.GetSize(); i++)
	{
		CITIES* pCurrentCity = citiesArray.GetAt(i);
		if (pCurrentCity == NULL)
			continue;

		CString currentCityName;
		currentCityName.Format(_T("%s"), pCurrentCity->szCITY_NAME);

		if (currentCityName == strCityName)
		{
			pCurrentCity->lPOSTAL_CODE = lNewCityPosalCode;
			break;
		}
	}
};

void CityService::ChangeCityPostalCode(CITIES& pCity, const long lNewPostalCode)
{
	if (lNewPostalCode > 0)
	{
		pCity.lPOSTAL_CODE = lNewPostalCode;
	}
};