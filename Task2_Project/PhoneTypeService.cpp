#pragma once
#include "pch.h"
#include "PhoneTypeService.h"
#include <string>
#include "Structures.h"
#include <iostream>
using namespace std;

void PhoneTypeService::SetPhoneType(const string sorce, PHONE_TYPES& phone) {
	size_t LengthOfArray = sizeof(phone.szPHONE_TYPE) / sizeof(char);

	if (sorce.length() <= LengthOfArray) {
		for (size_t i = 0; i < sorce.size(); i++)
		{
			phone.szPHONE_TYPE[i] = sorce[i];
		}
	}
	else {
		cout << "Too long sorce";
	}
};

void PhoneTypeService::AddDefaultElements(CPhoneTypesArray& phoneTypes)
{
	try
	{
		PHONE_TYPES pMobilePhoneType ;
		SetPhoneType("mobile",pMobilePhoneType);

		PHONE_TYPES pHomePhoneType ;
		SetPhoneType("home", pHomePhoneType);

		PHONE_TYPES pOfficePhoneType;
		SetPhoneType("office", pOfficePhoneType);

		phoneTypes.Add(&pMobilePhoneType);
		phoneTypes.Add(&pHomePhoneType);
		phoneTypes.Add(&pOfficePhoneType);
	}
	catch (const std::exception&)
	{
		cout << "Invalid 'Add' operation!";
	}
};

void PhoneTypeService::ShowElementInfoAtIndex(const int nIndex, const CPhoneTypesArray &oPhoneTypesArray)
{
	try
	{
		ValidateIndex(nIndex, oPhoneTypesArray.GetCount()-1);
		PHONE_TYPES* pTemp = NULL;
		pTemp = oPhoneTypesArray.GetAt(nIndex);
		cout << "Selected item info: " << "memory address: " << &pTemp << " value:" << pTemp->szPHONE_TYPE << endl;
	}
	catch (const std::exception&)
	{
		cout << "Something goes wrong, press again!";
	}
};


