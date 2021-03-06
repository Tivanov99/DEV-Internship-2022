#pragma once
#include "pch.h"
#include "CityService.h"
#include "resource.h"

using namespace std;

CityService::CityService(){};
CityService::~CityService()
{
	for (INT_PTR i = 0; i < citiesArray.GetCount(); i++)
	{
		delete citiesArray.GetAt(i);
		citiesArray[i] = NULL;
	}
	citiesArray.RemoveAll();
};	

void CityService::SetCityData(const CString& strCityName, const CString& strAreaName, const long lPostalCode, CITIES& oCity)
{
	oCity.lPOSTAL_CODE = lPostalCode;

	int nCityNameArrayLength = sizeof(oCity.szCITY_NAME) / sizeof(char);

	if (strCityName.GetLength() > nCityNameArrayLength)
		return;
	TCHAR* szCityNameBuffer = _tcsdup(strCityName);
	_tcscpy_s(oCity.szCITY_NAME, szCityNameBuffer);

	int nCityAreaNameArrayLength = sizeof(oCity.szAREA_NAME) / sizeof(TCHAR);
	if (strAreaName.GetLength() > nCityAreaNameArrayLength)
		return;

	TCHAR* szAreaNameBuffer = _tcsdup(strAreaName);
	_tcscpy_s(oCity.szAREA_NAME, szAreaNameBuffer);
};

CITIES* CityService::GetCityByAreaName(const CString& strCityAreaName)
{
	for (INT_PTR i = 0; i < citiesArray.GetCount(); i++)
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

CITIES* CityService::GetCityByCityName(const CString& strCityName)
{
	for (INT_PTR i = 0; i < citiesArray.GetCount(); i++)
	{
		CITIES* pCity = citiesArray.GetAt(i);
		if (pCity == NULL)
			continue;

		CString srtCurrentCityName;
		srtCurrentCityName.Format(_T("%s"), pCity->szAREA_NAME);
		if (srtCurrentCityName != strCityName)
			continue;

		return pCity;
	}
};

CITIES* CityService::GetCityByPostalCode(const long lPostalCode)
{
	for (INT_PTR i = 0; i < citiesArray.GetCount(); i++)
	{
		CITIES* pCity = citiesArray.GetAt(i);
		if (pCity == NULL)
			continue;
		
		if (pCity->lPOSTAL_CODE != lPostalCode)
			continue;

		return pCity;
	}
};


void CityService::AddDefaultElements()
{
	CITIES oBurgasCity;
	SetCityData(_T("Bugras"), _T("Bugras"), 8000, oBurgasCity);

	CITIES oVarnaCity;
	SetCityData(_T("Varna"), _T("Varna"), 9000, oVarnaCity);

	CITIES oSofiaCity;
	SetCityData(_T("Sofia"), _T("Sofia"), 1000, oSofiaCity);

	CITIES oPlovidCity;
	SetCityData(_T("Plovdiv"), _T("Plovdiv"), 3000, oPlovidCity);

	CITIES oRuseCity;
	SetCityData(_T("Ruse"), _T("Ruse"), 4700, oRuseCity);

	CITIES oVelinGradCity;
	SetCityData(_T("VelinGrad"), _T("Pazardzhik"), 6000, oVelinGradCity);


	oSelfClearingTypedArray.Add(CreatePointer(oBurgasCity));
	oSelfClearingTypedArray.Add(CreatePointer(oVarnaCity));
	oSelfClearingTypedArray.Add(CreatePointer(oSofiaCity));
	oSelfClearingTypedArray.Add(CreatePointer(oPlovidCity));
	oSelfClearingTypedArray.Add(CreatePointer(oRuseCity));
	oSelfClearingTypedArray.Add(CreatePointer(oVelinGradCity));
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