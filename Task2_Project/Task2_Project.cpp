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
	CString strDummy = _T("This is a dummy object!\t");

	strDummy.AppendFormat(_T("%s"), _T("Just a test!"));

	_tprintf(_T("%s"), (LPCTSTR)strDummy);

	CString comparedDummy = _T("This is a dummy object!\tJust a test!");

	int compareResult = strDummy.Compare((LPCTSTR)comparedDummy);

	string resultMessage;

	switch (compareResult)
	{
	case -1: resultMessage = "\nCompared value is greater."; break;
	case 1: resultMessage = "\nCompared value is less."; break;
	default:
		resultMessage = "\nValues are equal!";
		break;
	}

	cout << resultMessage << endl;


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