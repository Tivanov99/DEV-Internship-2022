#include "pch.h"
#include "PhoneTypeService.h"
#include "BaseService.h"

using namespace std;

PhoneTypeService::PhoneTypeService() {};
PhoneTypeService::~PhoneTypeService()
{
	while (phoneTypeArray.GetCount() > 0)
	{
		delete phoneTypeArray.GetAt(phoneTypeArray.GetCount() - 1);
	}
	phoneTypeArray.RemoveAll();
};

PHONE_TYPES* PhoneTypeService::GetByPhoneType(CString& strPhoneType)
{
	for (INT_PTR i = 0; i < phoneTypeArray.GetCount(); i++)
	{
		PHONE_TYPES* pPhoneType = phoneTypeArray.GetAt(i);
		CString strCurrentPhoneType;
		strCurrentPhoneType.Format(_T("%s"), pPhoneType->szPHONE_TYPE);
		if (strPhoneType != strCurrentPhoneType)
			continue;

		return pPhoneType;
	}
};

void PhoneTypeService:: SetPhoneType(const CString& strType, PHONE_TYPES& oPhone)
{
	TCHAR* szBuffer = _tcsdup(strType);
	_tcscpy_s(oPhone.szPHONE_TYPE, szBuffer);
};


void PhoneTypeService::ShowElementInfoAtIndex(const long lIndex)
{
		PHONE_TYPES* pTemp = phoneTypeArray.GetAt(lIndex);
		if (pTemp == NULL)
			return;

		cout << "Selected item info: " << "memory address: " << &pTemp << " value:" <<  endl;
};
void PhoneTypeService::AddDefaultElements()
{
		PHONE_TYPES oMobilePhoneType;
		CString strMobile = _T("mobile");
		SetPhoneType(strMobile, oMobilePhoneType);


		PHONE_TYPES oHomePhoneType;
		CString strHome = _T("home");
		SetPhoneType(strHome, oHomePhoneType);


		PHONE_TYPES oOfficePhoneType;
		CString strOffice = _T("office");
		SetPhoneType(strOffice, oOfficePhoneType);


		PHONE_TYPES* pMobilePhoneType = new PHONE_TYPES;
		*pMobilePhoneType = oMobilePhoneType;

		PHONE_TYPES* pHomePhoneType = new PHONE_TYPES;
		*pHomePhoneType = oHomePhoneType;

		PHONE_TYPES* pOfficePhoneType = new PHONE_TYPES;
		*pOfficePhoneType = oOfficePhoneType;

		phoneTypeArray.Add(pMobilePhoneType);
		phoneTypeArray.Add(pHomePhoneType);
		phoneTypeArray.Add(pOfficePhoneType);
};

