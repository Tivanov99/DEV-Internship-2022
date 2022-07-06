// Task2_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "Task2_Project.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CityService.h"
#include "PhoneNumberService.h"
#include "CStringService.h"



// The one and only application object

CWinApp theApp;

using namespace std;


//void ManagePhoneTypes() {
//	CPhoneTypesArray oPhoneTypesArray;
//	//PhoneTypeService service;
//
//	service.AddDefaultElements(oPhoneTypesArray);
//	
//
//	service.RemoveAt(0, 2, oPhoneTypesArray);
//
//	PHONE_TYPES* pTemp = service.GetPointerAtIndex(0, oPhoneTypesArray);
//
//	service.GetPointerAtIndex(17, oPhoneTypesArray);
//}

void ManagePhoneNumbers() {
	PhoneNumberService service;

	CPhoneNumbersArray oPhoneTypesArray;

	service.AddDefaultElements(oPhoneTypesArray);

	service.RemoveAt(0, 2, oPhoneTypesArray);

	//PHONE_NUMBER* pTemp = service.GetPointerAtIndex(0, oPhoneTypesArray);


	service.ShowElementInfoAtIndex(2, oPhoneTypesArray);

	//PHONE_NUMBER* pPhoneNumber = NULL;
	//pPhoneNumber = service.GetPointerAtIndex(2, oPhoneTypesArray);
	CString strNewPhoneNumber = _T("0888888888");

	PHONE_NUMBERS pPhoneNumber = *oPhoneTypesArray[0];
	service.ChangePhoneNumber(pPhoneNumber,strNewPhoneNumber);
	service.ShowElementInfoAtIndex(2, oPhoneTypesArray);

	CString strOldPhoneNumber = _T("0886372847");
	CString strPhoneNumber = _T("0999999999");
	service.ChangePhoneNumber(strOldPhoneNumber, strPhoneNumber, oPhoneTypesArray);
	service.ShowElementInfoAtIndex(2, oPhoneTypesArray);
}

void CityNameChanging(CityService& service, CCitiesArray& oCitiesArray) {

	CITIES* pCity = NULL;
	pCity = service.GetPointerAtIndex(2, oCitiesArray);

	CString strRuseCityOldName = _T("Ruse");
	CString strRuseCityNewName = _T("RuseFirst");

	service.ChangeCityName(strRuseCityOldName, strRuseCityNewName, oCitiesArray);

	service.ShowElementInfoAtIndex(2, oCitiesArray);

	CString strRuseCitySecondNewName = _T("RuseSecond");
	CITIES oCity = *oCitiesArray[2];
	service.ChangeCityName(oCity, strRuseCitySecondNewName);

	service.ShowElementInfoAtIndex(2, oCitiesArray);
}

void CityAreaNameChanging(CityService& service, CCitiesArray& oCitiesArray) {
	CITIES oCity;
	oCity = *oCitiesArray[2];

	CString strCityAreaName = _T("RunskaFirst");
	service.ChangeCityAreaName(oCity, strCityAreaName);

	service.ShowElementInfoAtIndex(2, oCitiesArray);

	CString strOldCityAreaName = _T("RunskaFirst");
	CString strNewCityAreaName = _T("RunskaSecond");

	service.ChangeCityAreaName(strOldCityAreaName, strNewCityAreaName, oCitiesArray);

	service.ShowElementInfoAtIndex(2, oCitiesArray);
}

void CityPostalCodeChanging(CityService& service, CCitiesArray& oCitiesArray)
{
	CString strRuseCityOldName = _T("RuseSecond");
	service.ChangeCityPosalCode(strRuseCityOldName, 9999, oCitiesArray);

	service.ShowElementInfoAtIndex(2, oCitiesArray);

	CITIES oCity = *oCitiesArray[2];
	service.ChangeCityPostalCode(oCity, 11111);
	service.ShowElementInfoAtIndex(2, oCitiesArray);
}

void ManageCities() {
	CityService service;

	CCitiesArray oCitiesArray;

	service.AddDefaultElements(oCitiesArray);

	service.RemoveAt(0, 2, oCitiesArray);
	service.ShowElementInfoAtIndex(2, oCitiesArray);

	CITIES* pTemp = service.GetPointerAtIndex(0, oCitiesArray);


	CityNameChanging(service, oCitiesArray);
	CityAreaNameChanging(service, oCitiesArray);
	CityPostalCodeChanging(service, oCitiesArray);
}


void CStringExample() {
	CString strDummy = _T("This is a dummy object!\t");
	CStringService strService;

	strService.PrintCStringAsString(strDummy);
	int nArgCount = 5;
	strService.AppendListOfIntegerArgs(strDummy, nArgCount, 10, 20, 30, 40, 50);

	strDummy.AppendFormat(_T("%s"),(LPCWSTR)"Just Test");
	strService.PrintCStringAsString(strDummy);

	CString comparedDummy = _T("This is a dummy object!\tJust a test!");
}



void CArrayExample() {
	CArray<int, int> arr;

	CArray <int, int> secondCArray;
	secondCArray.Add(20);
	secondCArray.Add(30);
	secondCArray.Add(40);
	secondCArray.Add(1);
	secondCArray.Add(9);

	arr.Append(secondCArray);

	for (size_t i = 0; i < arr.GetCount(); i++)
	{
		cout << arr[i] << " ";
	}

	if (arr.GetCount() > 0) {
		try
		{
			arr.RemoveAt(0, 3);
			arr.FreeExtra();
		}
		catch (const std::exception&)
		{

		}
	}

}


int main()
{
	ManageCities();/*
	CArrayExample();
	CStringExample();
	ManagePhoneTypes();*/
	//ManagePhoneNumbers()



	//int nRetCode = 0;

	//	HMODULE hModule = ::GetModuleHandle(nullptr);

	//	if (hModule != nullptr)
	//	{
	//	    // initialize MFC and print and error on failure
	//	    if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
	//	    {
	;	//	        // TODO: code your application's behavior here.
		//	        wprintf(L"Fatal Error: MFC initialization failed\n");
		//	        nRetCode = 1;
		//	    }
		//	    else
		//	    {
		//	        // TODO: code your application's behavior here.
		//	    }
		//	}
		//	else
		//	{
		//	    // TODO: change error code to suit your needs
		//	    wprintf(L"Fatal Error: GetModuleHandle failed\n");
		//	    nRetCode = 1;
		//	}

		//	return nRetCode;
}