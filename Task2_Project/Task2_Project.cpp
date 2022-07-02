// Task2_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "Task2_Project.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Structures.h"
#include "PhoneTypesService.h"
#include "PhoneNumbersService.h"
#include "CityService.h"


// The one and only application object

CWinApp theApp;

using namespace std;


void ManagePhoneTypes() {
	CPhoneTypesArray oPhoneTypesArray;
	PhoneTypesService service;

	service.AddPhoneTypeElements(oPhoneTypesArray);
	service.AddPhoneTypeElements(oPhoneTypesArray);
	service.AddPhoneTypeElements(oPhoneTypesArray);

	service.RemoveAt(0, 2, oPhoneTypesArray);

	PhoneType* pTemp = service.GetPointerAtIndex(0, oPhoneTypesArray);

	service.GetPointerAtIndex(17, oPhoneTypesArray);
}

void ManagePhoneNumbers() {
	PhoneNumberService service;
	CPhoneNumbersArray oPhoneTypesArray;

	service.AddDefaultPhoneNumbersElements(oPhoneTypesArray);
	service.AddDefaultPhoneNumbersElements(oPhoneTypesArray);
	service.AddDefaultPhoneNumbersElements(oPhoneTypesArray);

	service.RemoveAt(0, 2, oPhoneTypesArray);

	PhoneNumber* pTemp = service.GetPointerAtIndex(0, oPhoneTypesArray);


	service.ShowElementInfoAtIndex(2, oPhoneTypesArray);

	PhoneNumber* pPhoneNumber = NULL;
	pPhoneNumber = service.GetPointerAtIndex(2, oPhoneTypesArray);

	service.ChangePhoneNumber("0895467264", "0888888888", oPhoneTypesArray);

	service.ShowElementInfoAtIndex(2, oPhoneTypesArray);


	service.ChangePhoneNumber(pPhoneNumber, "0999999999");
	service.ShowElementInfoAtIndex(2, oPhoneTypesArray);
}

void CityNameChanging(CityService& service, CCitiesArray& oCitiesArray) {
	City* pCity = NULL;
	pCity = service.GetPointerAtIndex(2, oCitiesArray);

	service.ChangeCityName("Ruse", "RuseFirst", oCitiesArray);

	service.ShowElementInfoAtIndex(2, oCitiesArray);

	service.ChangeCityName(pCity, "RuseSecond");

	service.ShowElementInfoAtIndex(2, oCitiesArray);
}

void CityAreaNameChanging(CityService& service, CCitiesArray& oCitiesArray) {
	City* pCity = NULL;
	pCity = service.GetPointerAtIndex(2, oCitiesArray);

	service.ChangeCityAreaName(pCity, "RunskaFirst");

	service.ShowElementInfoAtIndex(2, oCitiesArray);

	service.ChangeCityAreaName("RunskaFirst", "RunskaSecond", oCitiesArray);

	service.ShowElementInfoAtIndex(2, oCitiesArray);
}

void CityPostalCodeChanging(CityService& service, CCitiesArray& oCitiesArray) {
	City* pCity = NULL;
	pCity = service.GetPointerAtIndex(2, oCitiesArray);

	service.ChangeCityPosalCode("RuseSecond", 9999, oCitiesArray);

	service.ShowElementInfoAtIndex(2, oCitiesArray);

	service.ChangeCityPostalCode(pCity, 11111);
	service.ShowElementInfoAtIndex(2, oCitiesArray);
}

void ManageCities() {
	CityService service;
	CCitiesArray oCitiesArray;

	service.AddCityElements(oCitiesArray);
	service.AddCityElements(oCitiesArray);
	service.AddCityElements(oCitiesArray);

	service.RemoveAt(0, 2, oCitiesArray);

	City* pTemp = service.GetPointerAtIndex(0, oCitiesArray);

	service.ShowElementInfoAtIndex(2, oCitiesArray);

	CityNameChanging(service, oCitiesArray);
	CityAreaNameChanging(service, oCitiesArray);
	CityPostalCodeChanging(service, oCitiesArray);
}

void CStringExample() {
	CString strDummy = _T("This is a test!\t");

	//_tprintf(_T("%s"), (LPCTSTR)strDummy);


	strDummy.AppendFormat(_T("%s"),_T("Just a test!"));

	_tprintf(_T("%s"), (LPCTSTR)strDummy);

	//CAtlString str = _T("Some data:\t");

	//str.AppendFormat(_T("X value = %.2f\n"), 12345.12345);
	//_tprintf_s(_T("%s"), (LPCTSTR)str);

	/*
	int nCompareResult = strDummy.Compare(strSecondDummy);

	string resultMessage = nCompareResult < 0 ? "Value compare is different" :
		nCompareResult >0 ? "Compared value is different" :
		"Values are equal";
	cout << resultMessage << endl;


	strDummy.AppendChar('!');

	cout << char(strDummy[3]) << endl;

	strDummy.Delete(0, 5);

	CString strResult = strDummy.Right(5);

	for (size_t i = 0; i < strResult.GetLength(); i++)
	{
		cout << char(strResult[i]);
	}

	char cValueFound;
	cValueFound = strDummy.Find('T', 1);
	cout << cValueFound << endl;

	cout << strDummy.Delete(0, 4);*/
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
			arr.RemoveAt(0,3);
			arr.FreeExtra();
		}
		catch (const std::exception&)
		{
				
		}
	}

}

int main()
{
	/*CArrayExample();*/
	CStringExample();
	/*ManageCities();
	ManagePhoneTypes();
	ManagePhoneNumbers();*/

	//int nRetCode = 0;

	//	HMODULE hModule = ::GetModuleHandle(nullptr);

	//	if (hModule != nullptr)
	//	{
	//	    // initialize MFC and print and error on failure
	//	    if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
	//	    {
	//	        // TODO: code your application's behavior here.
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