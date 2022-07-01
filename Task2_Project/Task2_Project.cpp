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


void FillPhoneType(string sorce, char destination[]) {
	for (size_t i = 0; i < sorce.size(); i++)
	{
		destination[i] = sorce[i];
	}
};

void CreatePhoneTypes() {

	string sMobileType = "mobile";
	string sHomeType = "home";
	string sOfficeType = "office";

	PhoneType  oMobilePhoneType;
	oMobilePhoneType.ID = 1;
	FillPhoneType(sMobileType, oMobilePhoneType.PHONE_TYPE);

	PhoneType oHomePhoneType;
	oHomePhoneType.ID = 2;
	FillPhoneType(sHomeType, oHomePhoneType.PHONE_TYPE);

	PhoneType oOfficePhoneType;
	oOfficePhoneType.ID = 3;
	FillPhoneType(sOfficeType, oOfficePhoneType.PHONE_TYPE);


	CPhoneTypesArray phoneTypes;

	phoneTypes.Add(&oMobilePhoneType);
	phoneTypes.SetAtGrow(phoneTypes.GetSize(), &oHomePhoneType);
	phoneTypes.SetAtGrow(phoneTypes.GetSize(), &oOfficePhoneType);

	char value[16];
	int size = strlen(phoneTypes[0]->PHONE_TYPE);

	for (size_t i = 0; i < size; i++)
	{
		value[i] = phoneTypes[0]->PHONE_TYPE[i];
	}

	cout << &value << "   " << value << "\n";
	cout << "CTypedPtrArray\n";
	cout << phoneTypes[0]->PHONE_TYPE << "\n";

	PhoneType* pFirstEl;
	pFirstEl = phoneTypes[0];
	
	cout << "New pointer and pointer from ctypedptrarray references";
	cout << &pFirstEl << "\n";
	cout << &phoneTypes[0] << endl;


	cout << "Memory addreses";
	cout << &phoneTypes[0]->PHONE_TYPE << "\n";
	cout << &pFirstEl->PHONE_TYPE << "\n";
	cout << &phoneTypes[0]->ID << "\n";
	cout << &pFirstEl->ID<< endl;


	//Цялостна информация
	cout << phoneTypes[1]->PHONE_TYPE << "     " << *phoneTypes[1]->PHONE_TYPE << "  " << *phoneTypes[1]->PHONE_TYPE << "  " << &phoneTypes[1]->PHONE_TYPE << "\n";

	/*cout << phoneTypes[0]->PHONE_TYPE << "\n";
	cout << phoneTypes[1]->PHONE_TYPE << "\n";
	cout << phoneTypes[2]->PHONE_TYPE << "\n";*/
	FillPhoneType("dadada", phoneTypes[0]->PHONE_TYPE);

	cout << phoneTypes[0]->PHONE_TYPE << "\n";
}

int main()
{
	CPhoneNumbersArray numbers;
	CCitiesArray cities;
	CPersonsArray persons;

	CreatePhoneTypes();



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
