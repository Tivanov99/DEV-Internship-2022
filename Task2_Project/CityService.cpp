#pragma once
#include "pch.h"
#include "CityService.h"
#include "resource.h"

using namespace std;

CityService::CityService(){};
CityService::~CityService()
{
	while (oCities.GetCount() > 0)
	{
		delete oCities.GetAt(oCities.GetCount() - 1);
	}
	oCities.RemoveAll();
};

CITIES* CityService::GetByAreaName(const CString& strCityAreaName)
{
	for (INT_PTR i = 0; i < oCities.GetCount(); i++)
	{
		CITIES* pCity = oCities.GetAt(i);
		CString srtCurrentCityName;
		srtCurrentCityName.Format(_T("%s"), pCity->szAREA_NAME);
		if (srtCurrentCityName != strCityAreaName)
			continue;

		return pCity;
	}
};

CITIES* CityService::GetByCityName(const CString& strCityName)
{
	for (INT_PTR i = 0; i < oCities.GetCount(); i++)
	{
		CITIES* pCity = oCities.GetAt(i);
		CString srtCurrentCityName;
		srtCurrentCityName.Format(_T("%s"), pCity->szAREA_NAME);
		if (srtCurrentCityName != strCityName)
			continue;

		return pCity;
	}
};

CITIES* CityService::GetByPostalCode(const long lPostalCode)
{
	for (INT_PTR i = 0; i < oCities.GetCount(); i++)
	{
		CITIES* pCity = oCities.GetAt(i);
		
		if (pCity->lPOSTAL_CODE != lPostalCode)
			continue;

		return pCity;
	}
};

void CityService::SetCityName(const CString& szSorce, CITIES& city)
{
	int nLengthOfArray = sizeof(city.szCITY_NAME) / sizeof(char);

	if (szSorce.GetLength() > nLengthOfArray)
		return;
	TCHAR* szBuffer = _tcsdup(szSorce);
	_tcscpy_s(city.szCITY_NAME, szBuffer);
};

void CityService::SetAreaName(const CString& sorce, CITIES& city)
{
	int nLengthOfArray = sizeof(city.szAREA_NAME) / sizeof(TCHAR);
	if (sorce.GetLength() > nLengthOfArray)
		return;

	TCHAR* szBuffer = _tcsdup(sorce);
	_tcscpy_s(city.szAREA_NAME, szBuffer);
};

void CityService::SetPostalCode(const int nSorce, CITIES& city)
{
	if (nSorce > 0)
		city.lPOSTAL_CODE = nSorce;
};

void CityService::AddDefaultElements()
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

void CityService::ShowElementInfoAtIndex(const int nIndex)
{
	if (nIndex > oCities.GetCount())
		return;

	CITIES* pCity = oCities.GetAt(nIndex);

	if (pCity == NULL)
		return;

	CString info;
	info.Format(_T("City Name : %s, Postal Code : %d, Area Name : %s\n"),
		pCity->szCITY_NAME, pCity->lPOSTAL_CODE, pCity->szAREA_NAME);
	_tprintf(_T("%s"), (LPCTSTR)info);
};

void CityService::ChangeCityName(const CString& strCityName, const CString& strNewCityName)
{
	for (INT_PTR i = 0; i < oCities.GetCount(); i++)
	{
		CITIES* pCity = oCities.GetAt(i);
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

void CityService::ChangeCityName(CITIES& oCity, const CString& newCityName)
{
	TCHAR* szBuffer = _tcsdup(newCityName);
	_tcscpy_s(oCity.szCITY_NAME, szBuffer);
}
void CityService::ChangeCityAreaName(const CString& strCityAreaName, const CString& strNewCityAreaName)
{
	for (INT_PTR i = 0; i < oCities.GetSize(); i++)
	{
		CITIES* pCurrentCity = oCities.GetAt(i);
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

void CityService::ChangeCityPosalCodeByCityName(const CString& strCityName, const int nNewCityPosalCode)
{
	for (INT_PTR i = 0; i < oCities.GetSize(); i++)
	{
		CITIES* pCurrentCity = oCities.GetAt(i);
		if (pCurrentCity == NULL)
			continue;

		CString currentCityName;
		currentCityName.Format(_T("%s"), pCurrentCity->szCITY_NAME);

		if (currentCityName == strCityName)
		{
			pCurrentCity->lPOSTAL_CODE = nNewCityPosalCode;
			break;
		}
	}
};

void CityService::ChangeCityPostalCode(CITIES& pCity, const int nNewPostalCode)
{
	if (nNewPostalCode > 0)
	{
		pCity.lPOSTAL_CODE = nNewPostalCode;
	}
};