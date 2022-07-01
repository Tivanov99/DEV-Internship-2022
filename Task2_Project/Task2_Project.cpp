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
}

void CityAreaNameChaning(CityService& service, CCitiesArray& oCitiesArray) {
	City* pCity = NULL;
	pCity = service.GetPointerAtIndex(2, oCitiesArray);

	service.ChangeCityAreaName(pCity, "RunskaFirst");

	service.ShowElementInfoAtIndex(2, oCitiesArray);

	service.ChangeCityAreaName("RunskaFirst", "RunskaSecond", oCitiesArray);

	service.ShowElementInfoAtIndex(2, oCitiesArray);
}

void CityPostalCodeChange(CityService& service, CCitiesArray& oCitiesArray) {
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
	/*service.AddCityElements(oCitiesArray);
	service.AddCityElements(oCitiesArray);*/

	service.RemoveAt(0, 2, oCitiesArray);

	City* pTemp = service.GetPointerAtIndex(0, oCitiesArray);

	service.ShowElementInfoAtIndex(2, oCitiesArray);

	CityNameChanging(service, oCitiesArray);
	CityAreaNameChaning(service, oCitiesArray);
	CityPostalCodeChange(service, oCitiesArray);
}




int main()
{
	CPersonsArray oPersonsArray;
	ManageCities();
	//ManagePhoneTypes();
	//ManagePhoneNumbers();
}

void Hide() {
	//int nRetCode = 0;

		//HMODULE hModule = ::GetModuleHandle(nullptr);

		//if (hModule != nullptr)
		//{
		//    // initialize MFC and print and error on failure
		//    if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
		//    {
		//        // TODO: code your application's behavior here.
		//        wprintf(L"Fatal Error: MFC initialization failed\n");
		//        nRetCode = 1;
		//    }
		//    else
		//    {
		//        // TODO: code your application's behavior here.
		//    }
		//}
		//else
		//{
		//    // TODO: change error code to suit your needs
		//    wprintf(L"Fatal Error: GetModuleHandle failed\n");
		//    nRetCode = 1;
		//}

		//return nRetCode;
}


