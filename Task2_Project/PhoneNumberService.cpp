#include "pch.h"
#include "PhoneNumberService.h"

void PhoneNumberService::SetPhoneNumber(const CString &sorce, PHONE_NUMBERS& phoneNumber)
{
	size_t LengthOfArray = sizeof(phoneNumber.szPHONE_NUMBER) / sizeof(char);

	if (sorce.GetLength() > LengthOfArray)
		return;
	
	TCHAR* szBuffer = _tcsdup(sorce);
	_tcscpy_s(phoneNumber.szPHONE_NUMBER, szBuffer);
};

//CHECK HERE!!!!
void PhoneNumberService::AddDefaultElements(CPhoneNumbersArray &oArray) {
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

//CHECK HERE
void PhoneNumberService::ShowElementInfoAtIndex(const int nIndex, const CPhoneNumbersArray& oArray) {
	try
	{
		ValidateIndex(nIndex, oArray.GetCount()-1);
		PHONE_NUMBERS* pTemp = NULL;
		pTemp = oArray.GetAt(nIndex);
		cout << "Selected item info: " << "memory address: " << &pTemp << " value:" << pTemp->szPHONE_NUMBER << endl;
	}
	catch (const std::exception&)
	{
		cout << "Something goes wrong, try again!" << endl;
	}
}

void PhoneNumberService::ChangePhoneNumber
(const CString &oldPhoneNumber, const CString &newPhoneNumber, CPhoneNumbersArray& oPhoneTypesArray)
{
	for (size_t i = 0; i < oPhoneTypesArray.GetSize(); i++)
	{
		CString currentPhoneNumber = oPhoneTypesArray[i]->szPHONE_NUMBER;

		if (currentPhoneNumber == oldPhoneNumber) {
			PHONE_NUMBERS* pOldPhoneNumber = NULL;
			pOldPhoneNumber = oPhoneTypesArray[i];

			for (size_t s = 0; s < currentPhoneNumber.GetLength(); s++)
			{
				pOldPhoneNumber->szPHONE_NUMBER[s] = newPhoneNumber[s];
			}
			break;
		}
	}
}
void PhoneNumberService::ChangePhoneNumber(PHONE_NUMBERS& pOldPhoneNumberElement, const CString &newPhoneNumber)
{
	CString sOldPhoneNumber =pOldPhoneNumberElement.szPHONE_NUMBER;

	for (size_t s = 0; s < newPhoneNumber.GetLength(); s++)
	{
		pOldPhoneNumberElement.szPHONE_NUMBER[s] = newPhoneNumber[s];
	}
}