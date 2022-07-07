#include "pch.h"
#include "PhoneTypeService.h"
#include "BaseService.h"

using namespace std;


void PhoneTypeService::SetPhoneType(CString& strType, PHONE_TYPES* oPhone)
{
	for (size_t i = 0; i < strType.GetLength(); i++)
	{
		oPhone->szPHONE_TYPE[i] = strType[i];
	}
};


void PhoneTypeService::ShowElementInfoAtIndex(const int nIndex, const CPhoneTypesArray& oArray)
{
	try
	{
		ValidateIndex(nIndex, oArray.GetCount() - 1);
		PHONE_TYPES* pTemp = NULL;
		pTemp = oArray.GetAt(nIndex);
		cout << "Selected item info: " << "memory address: " << &pTemp << " value:" <<  endl;
	}
	catch (const std::exception&)
	{
		cout << "Something goes wrong, press again!";
	}
};
void PhoneTypeService::AddDefaultElements(CPhoneTypesArray& oArray)
{
		PHONE_TYPES* pMobilePhoneType;
		pMobilePhoneType = new PHONE_TYPES();
		CString strMobile = _T("mobile");
		SetPhoneType(strMobile, pMobilePhoneType);

		PHONE_TYPES* pHomePhoneType;
		pHomePhoneType= new PHONE_TYPES();
		CString strHome = _T("home");
		SetPhoneType(strHome, pHomePhoneType);

		PHONE_TYPES* pOfficePhoneType;
		pOfficePhoneType = new PHONE_TYPES();
		CString strOffice = _T("office");
		SetPhoneType(strOffice, pOfficePhoneType);

		oArray.Add(pMobilePhoneType);
		oArray.Add(pHomePhoneType);
		oArray.Add(pOfficePhoneType);
};

