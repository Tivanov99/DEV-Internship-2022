#pragma once
#include "pch.h"
#include "PhoneTypeService.h"
#include <string>
#include "Structures.h"
#include <iostream>
using namespace std;




void PhoneTypeService::ShowElementInfoAtIndex(const int nIndex, const CPhoneTypesArray& oPhoneTypesArray)
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
void PhoneTypeService::AddDefaultElements(CPhoneTypesArray& phoneTypes)
{
	try
	{
		PHONE_TYPES pMobilePhoneType;
		CString strMobile = _T("mobile");
		SetPhoneType(strMobile, pMobilePhoneType);

		PHONE_TYPES pHomePhoneType;
		CString strHome = _T("home");
		SetPhoneType(strHome, pHomePhoneType);

		PHONE_TYPES pOfficePhoneType;
		CString strOffice = _T("office");
		SetPhoneType(strOffice, pOfficePhoneType);

		phoneTypes.Add(&pMobilePhoneType);
		phoneTypes.Add(&pHomePhoneType);
		phoneTypes.Add(&pOfficePhoneType);
	}
	catch (const std::exception&)
	{
		cout << "Invalid 'Add' operation!";
	}
};

void PhoneTypeService::SetPhoneType(CString &strType, PHONE_TYPES &oPhone)
{
	//if (oPhone==NULL) {
		for (size_t i = 0; i < strType.GetLength(); i++)
		{
			oPhone.szPHONE_TYPE[i] = strType[i];
		}
	//}
}


