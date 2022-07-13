#include "pch.h"
#include "PhoneTypeService.h"
#include "BaseService.h"

using namespace std;

PhoneTypeService::PhoneTypeService() {};
PhoneTypeService::~PhoneTypeService(){};

PHONE_TYPES* PhoneTypeService::GetByPhoneType(CString& strPhoneType)
{
	for (INT_PTR i = 0; i < phoneTypeArray.GetCount(); i++)
	{
		PHONE_TYPES* pPhoneType = phoneTypeArray.GetAt(i);
		if (pPhoneType == NULL)
			continue;

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
		SetPhoneType(_T("mobile"), oMobilePhoneType);

		PHONE_TYPES oHomePhoneType;
		SetPhoneType(_T("home"), oHomePhoneType);

		PHONE_TYPES oOfficePhoneType;
		SetPhoneType(_T("office"), oOfficePhoneType);

		phoneTypeArray.Add(CreatePointer(oMobilePhoneType));
		phoneTypeArray.Add(CreatePointer(oHomePhoneType));
		phoneTypeArray.Add(CreatePointer(oOfficePhoneType));
};

