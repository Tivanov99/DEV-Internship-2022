#include "pch.h"
#include "PhoneNumberService.h"

PhoneNumberService::PhoneNumberService()
{

};
PhoneNumberService::~PhoneNumberService()
{
	while (phoneNumbersArray.GetCount() > 0)
	{
		delete phoneNumbersArray.GetAt(phoneNumbersArray.GetCount() - 1);
	}
	phoneNumbersArray.RemoveAll();
};
PHONE_NUMBERS* PhoneNumberService::GetByPhoneNumber(CString& strPhoneNumber)
{
	for (INT_PTR i = 0; i < phoneNumbersArray.GetCount(); i++)
	{
		PHONE_NUMBERS* pPhoneNumber = phoneNumbersArray.GetAt(i);
		if (pPhoneNumber == NULL)
			continue;

		CString strCurrentPhoneNumber;
		strCurrentPhoneNumber.Format(_T("%s"), pPhoneNumber->szPHONE_NUMBER);
		if (strPhoneNumber != strCurrentPhoneNumber)
			continue;

		return pPhoneNumber;
	}
};

void PhoneNumberService::SetPhoneNumber(const CString& strSorce, PHONE_NUMBERS& oPhoneNumber)
{
	size_t LengthOfArray = sizeof(oPhoneNumber.szPHONE_NUMBER) / sizeof(char);

	if (strSorce.GetLength() > LengthOfArray)
		return;

	TCHAR* szBuffer = _tcsdup(strSorce);
	_tcscpy_s(oPhoneNumber.szPHONE_NUMBER, szBuffer);
};

void PhoneNumberService::AddDefaultElements()
{
		PHONE_NUMBERS oFirstPhoneNumber;
		SetPhoneNumber(_T("0893668829"), oFirstPhoneNumber);

		PHONE_NUMBERS oSecondPhoneNumber;
		SetPhoneNumber(_T("0883737518"), oSecondPhoneNumber);

		PHONE_NUMBERS oThirdPhoneNumber;
		SetPhoneNumber(_T("0875462946"), oThirdPhoneNumber);

		PHONE_NUMBERS oFourthPhoneNumber;
		SetPhoneNumber(_T("0886372847"), oFourthPhoneNumber);

		PHONE_NUMBERS oFifthPhoneNumber;
		SetPhoneNumber(_T("0895467264"), oFifthPhoneNumber);

		PHONE_NUMBERS oSixthPhoneNumber;
		SetPhoneNumber(_T("0895467264"), oSixthPhoneNumber);

		oSelfClearingTypedArray.Add(CreatePointer(oFirstPhoneNumber));
		oSelfClearingTypedArray.Add(CreatePointer(oSecondPhoneNumber));
		oSelfClearingTypedArray.Add(CreatePointer(oThirdPhoneNumber));
		oSelfClearingTypedArray.Add(CreatePointer(oFourthPhoneNumber));
		oSelfClearingTypedArray.Add(CreatePointer(oFifthPhoneNumber));
		oSelfClearingTypedArray.Add(CreatePointer(oSixthPhoneNumber));
}

void PhoneNumberService::ShowElementInfoAtIndex(const long lIndex) {

	if (lIndex > phoneNumbersArray.GetCount() - 1)
		return;

	PHONE_NUMBERS* pTemp = phoneNumbersArray.GetAt(lIndex);

	if (pTemp == NULL)
		return;

	cout << "Selected item info: " << "memory address: " << &pTemp << " value:" << pTemp->szPHONE_NUMBER << endl;
}

void PhoneNumberService::ChangePhoneNumber(const CString& oldPhoneNumber, const CString& strNewPhoneNumber)
{
	for (INT_PTR i = 0; i < oSelfClearingTypedArray.GetCount(); i++)
	{
		PHONE_NUMBERS* pPhoneNumber = oSelfClearingTypedArray.GetAt(i);
		if (pPhoneNumber == NULL)
			continue;

		CString currentPhoneNumber;
		currentPhoneNumber.Format(_T("%s"), pPhoneNumber->szPHONE_NUMBER);

		if (currentPhoneNumber == oldPhoneNumber)
		{
			TCHAR* szBuffer = _tcsdup(strNewPhoneNumber);
			_tcscpy_s(pPhoneNumber->szPHONE_NUMBER, szBuffer);
			break;
		}
	}
}
void PhoneNumberService::ChangePhoneNumber(PHONE_NUMBERS& pOldPhoneNumberElement, const CString& strNewPhoneNumber)
{
	CString sOldPhoneNumber;
	sOldPhoneNumber.Format(_T("%s"), pOldPhoneNumberElement.szPHONE_NUMBER);

	TCHAR* szBuffer = _tcsdup(sOldPhoneNumber);
	_tcscpy_s(pOldPhoneNumberElement.szPHONE_NUMBER, szBuffer);
}