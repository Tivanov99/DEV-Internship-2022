#include "pch.h"
#include "PhoneTypeService.h"
#include "BaseService.h"

using namespace std;

PhoneTypeService::PhoneTypeService() {};
PhoneTypeService::~PhoneTypeService() {};

void PhoneTypeService:: SetPhoneType(CString& strType, PHONE_TYPES& oPhone)
{
	CString strBuffer;
	strBuffer.Format(_T("%s"), strType);

	TCHAR* szBuffer = _tcsdup(strBuffer);
	_tcscpy_s(oPhone.szPHONE_TYPE, szBuffer);
};


void PhoneTypeService::ShowElementInfoAtIndex(const int nIndex, const CPhoneTypesArray& oArray)
{
		PHONE_TYPES* pTemp = oArray.GetAt(nIndex);
		if (pTemp == NULL)
			return;

		cout << "Selected item info: " << "memory address: " << &pTemp << " value:" <<  endl;
};
void PhoneTypeService::AddDefaultElements(CPhoneTypesArray& oArray)
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

		oArray.Add(pMobilePhoneType);
		oArray.Add(pHomePhoneType);
		oArray.Add(pOfficePhoneType);
};

