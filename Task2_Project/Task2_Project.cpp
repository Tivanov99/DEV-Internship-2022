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

	service.ChangePhoneNumber("0895467264", "0888888888", oPhoneTypesArray);

	service.ShowElementInfoAtIndex(2, oPhoneTypesArray);


	service.ChangePhoneNumber(*oPhoneTypesArray[0], "0999999999");
	service.ShowElementInfoAtIndex(2, oPhoneTypesArray);
}

void CityNameChanging(CityService& service, CCitiesArray& oCitiesArray) {

	CITIES* pCity = NULL;
	pCity = service.GetPointerAtIndex(2, oCitiesArray);

	service.ChangeCityName("Ruse", "RuseFirst", oCitiesArray);

	service.ShowElementInfoAtIndex(2, oCitiesArray);

	//service.ChangeCityName(pCity, "RuseSecond");

	service.ShowElementInfoAtIndex(2, oCitiesArray);
}

void CityAreaNameChanging(CityService& service, CCitiesArray& oCitiesArray) {
	CITIES* pCity = NULL;
	pCity = service.GetPointerAtIndex(2, oCitiesArray);

	//service.ChangeCityAreaName(pCity, "RunskaFirst");

	service.ShowElementInfoAtIndex(2, oCitiesArray);

	service.ChangeCityAreaName("RunskaFirst", "RunskaSecond", oCitiesArray);

	service.ShowElementInfoAtIndex(2, oCitiesArray);
}

void CityPostalCodeChanging(CityService& service, CCitiesArray& oCitiesArray) {
	CITIES* pCity = NULL;
	pCity = service.GetPointerAtIndex(2, oCitiesArray);

	service.ChangeCityPosalCode("RuseSecond", 9999, oCitiesArray);

	service.ShowElementInfoAtIndex(2, oCitiesArray);

	//service.ChangeCityPostalCode(pCity, 11111);
	service.ShowElementInfoAtIndex(2, oCitiesArray);
}

void ManageCities() {
	CityService service;

	CCitiesArray oCitiesArray;

	service.AddDefaultElements(oCitiesArray);

	service.RemoveAt(0, 2, oCitiesArray);

	CITIES* pTemp = service.GetPointerAtIndex(0, oCitiesArray);

	service.ShowElementInfoAtIndex(2, oCitiesArray);

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
	/*CArrayExample();
	CStringExample();
	ManageCities();
	ManagePhoneTypes();*/
	ManagePhoneNumbers()



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