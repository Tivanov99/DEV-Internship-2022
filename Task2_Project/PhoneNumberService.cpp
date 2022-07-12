#include "pch.h"
#include "PhoneNumberService.h"

PhoneNumberService::PhoneNumberService()
{

};
PhoneNumberService::~PhoneNumberService()
{

};

void PhoneNumberService::SetPhoneNumber(const CString& strSorce, PHONE_NUMBERS& oPhoneNumber)
{
	size_t LengthOfArray = sizeof(oPhoneNumber.szPHONE_NUMBER) / sizeof(char);

	if (strSorce.GetLength() > LengthOfArray)
		return;

	TCHAR* szBuffer = _tcsdup(strSorce);
	_tcscpy_s(oPhoneNumber.szPHONE_NUMBER, szBuffer);
};

void PhoneNumberService::AddDefaultElements(CPhoneNumbersArray& oArray) {
	try
	{
		CString strFirstPhoneNumber = _T("0893668829");
		PHONE_NUMBERS oFirstPhoneNumber;
		SetPhoneNumber(strFirstPhoneNumber, oFirstPhoneNumber);

		CString strSecondPhoneNumber = _T("0883737518");
		PHONE_NUMBERS oSecondPhoneNumber;
		SetPhoneNumber(strSecondPhoneNumber, oSecondPhoneNumber);


		CString strThirdPhoneNumber = _T("0875462946");
		PHONE_NUMBERS oThirdPhoneNumber;
		SetPhoneNumber(strThirdPhoneNumber, oThirdPhoneNumber);

		CString strFourthPhoneNumber = _T("0886372847");
		PHONE_NUMBERS oFourthPhoneNumber;
		SetPhoneNumber(strFourthPhoneNumber, oFourthPhoneNumber);


		CString strFifthPhoneNumber = _T("0895467264");
		PHONE_NUMBERS oFifthPhoneNumber;
		SetPhoneNumber(strFifthPhoneNumber, oFifthPhoneNumber);

		CString strSixthPhoneNumber = _T("0895467264");
		PHONE_NUMBERS oSixthPhoneNumber;
		SetPhoneNumber(strSixthPhoneNumber, oSixthPhoneNumber);


		PHONE_NUMBERS* pFirstPhoneNumber = new PHONE_NUMBERS;
		*pFirstPhoneNumber = oFirstPhoneNumber;

		PHONE_NUMBERS* pSecondPhoneNumber = new PHONE_NUMBERS;
		*pSecondPhoneNumber = oSecondPhoneNumber;

		PHONE_NUMBERS* pThirdPhoneNumber = new PHONE_NUMBERS;
		*pThirdPhoneNumber = oThirdPhoneNumber;

		PHONE_NUMBERS* pFourthPhoneNumber = new PHONE_NUMBERS;
		*pFourthPhoneNumber = oFourthPhoneNumber;

		PHONE_NUMBERS* pFifthPhoneNumber = new PHONE_NUMBERS;
		*pFifthPhoneNumber = oFifthPhoneNumber;

		PHONE_NUMBERS* pSixthPhoneNumber = new PHONE_NUMBERS;
		*pSixthPhoneNumber = oSixthPhoneNumber;


		oArray.Add(pFirstPhoneNumber);
		oArray.Add(pSecondPhoneNumber);
		oArray.Add(pThirdPhoneNumber);
		oArray.Add(pFourthPhoneNumber);
		oArray.Add(pFifthPhoneNumber);
		oArray.Add(pSixthPhoneNumber);
	}
	catch (const std::exception&)
	{
		cout << "Invalid 'Add' operation!" << endl;
	}
}

void PhoneNumberService::ShowElementInfoAtIndex(const int nIndex, const CPhoneNumbersArray& oArray) {

	if (nIndex > oArray.GetCount() - 1)
		return;

	PHONE_NUMBERS* pTemp = oArray.GetAt(nIndex);

	if (pTemp == NULL)
		return;

	cout << "Selected item info: " << "memory address: " << &pTemp << " value:" << pTemp->szPHONE_NUMBER << endl;
}

void PhoneNumberService::ChangePhoneNumber
(const CString& oldPhoneNumber, const CString& strNewPhoneNumber, CPhoneNumbersArray& oPhoneTypesArray)
{
	for (INT_PTR i = 0; i < oPhoneTypesArray.GetCount(); i++)
	{
		PHONE_NUMBERS* pPhoneNumber = oPhoneTypesArray.GetAt(i);

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