// Task2_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "Task2_Project.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Structures.h"


// The one and only application object

CWinApp theApp;

using namespace std;


void FillPhoneType(string sorce, PhoneType* phone) {
	size_t LengthOfArray = sizeof(phone->PHONE_TYPE) / sizeof(char);
	cout << LengthOfArray;

	if (sorce.length() <= LengthOfArray) {
		for (size_t i = 0; i < sorce.size(); i++)
		{
			phone->PHONE_TYPE[i] = sorce[i];
		}
	}
	else {
		cout << "Too long sorce";
	}
};

void ShowNElementInfo(CPhoneTypesArray& phoneTypes, int index) {
	cout << phoneTypes[index]->PHONE_TYPE << "     " << &phoneTypes[index]->PHONE_TYPE << "\n";
};

void AddPhoneTypeElements(CPhoneTypesArray& phoneTypes) {
	PhoneType* pMobilePhoneType = NULL;
	pMobilePhoneType = new PhoneType();
	FillPhoneType("mobile", pMobilePhoneType);

	PhoneType* pHomePhoneType = NULL;
	pHomePhoneType = new PhoneType();
	FillPhoneType("home", pHomePhoneType);

	PhoneType* pOfficePhoneType = NULL;
	pOfficePhoneType = new PhoneType();
	FillPhoneType("office", pOfficePhoneType);

	phoneTypes.Add(pMobilePhoneType);
	phoneTypes.Add(pHomePhoneType);
	phoneTypes.Add(pOfficePhoneType);

	//cout << "INSIDE INSERT METHOD POINTER REFERENCE: " << &phoneTypes[0]->PHONE_TYPE << " VALUE: " << phoneTypes[0]->PHONE_TYPE << "\n";
	//cout << "AFTER DELTE STATEMENT: " << &phoneTypes[0]->PHONE_TYPE << " VALUE: " << phoneTypes[0]->PHONE_TYPE << "\n";
}
int main()
{
	CPhoneNumbersArray oPhoneNumbersArray;
	CCitiesArray cities;
	CPersonsArray persons;

	CPhoneTypesArray phoneTypes;

	AddPhoneTypeElements(phoneTypes);
	phoneTypes.FreeExtra();
	phoneTypes.RemoveAt(0, 2);
	cout << "AFTER DELTE STATEMENT: " << &phoneTypes[0]->PHONE_TYPE << " VALUE: " << phoneTypes[0]->PHONE_TYPE << "\n";
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
