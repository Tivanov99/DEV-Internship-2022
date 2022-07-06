#include "pch.h"
#include "PhoneNumberService.h"

void PhoneNumberService::SetPhoneNumber(const CString &sorce, PHONE_NUMBERS& phoneNumber) {
	size_t LengthOfArray = sizeof(phoneNumber.szPHONE_NUMBER) / sizeof(char);

	if (sorce.GetLength() <= LengthOfArray) {
		for (size_t i = 0; i < sorce.GetLength(); i++)
		{
			phoneNumber.szPHONE_NUMBER[i] = sorce[i];
		}
	}
	else {
		cout << "Too long sorce" << endl;
	}
};

//CHECK HERE!!!!
void PhoneNumberService::AddDefaultElements(CPhoneNumbersArray &oArray) {
	try
	{
		CString strFirstPhoneNumber = _T("0893668829");
		PHONE_NUMBERS* pFirstPhoneNumber = NULL;
		pFirstPhoneNumber = new PHONE_NUMBERS();
		SetPhoneNumber(strFirstPhoneNumber, *pFirstPhoneNumber);


		CString strSecondPhoneNumber = _T("0883737518");
		PHONE_NUMBERS* pSecondPhoneNumber = NULL;
		pSecondPhoneNumber = new PHONE_NUMBERS();
		SetPhoneNumber(strSecondPhoneNumber, *pSecondPhoneNumber);

		CString strThirdPhoneNumber = _T("0875462946");
		PHONE_NUMBERS* pThirdPhoneNumber = NULL;
		pThirdPhoneNumber = new PHONE_NUMBERS();
		SetPhoneNumber(strThirdPhoneNumber, *pThirdPhoneNumber);


		CString strFourthPhoneNumber = _T("0886372847");
		PHONE_NUMBERS* pFourthPhoneNumber = NULL;
		pFourthPhoneNumber = new PHONE_NUMBERS();
		SetPhoneNumber(strFourthPhoneNumber, *pFourthPhoneNumber);

		CString strFifthPhoneNumber = _T("0895467264");
		PHONE_NUMBERS* pFifthPhoneNumber = NULL;
		pFifthPhoneNumber = new PHONE_NUMBERS();
		SetPhoneNumber(strFifthPhoneNumber, *pFifthPhoneNumber);

		CString strSixthPhoneNumber = _T("0895467264");
		PHONE_NUMBERS* pSixthPhoneNumber = NULL;
		pSixthPhoneNumber = new PHONE_NUMBERS();
		SetPhoneNumber(strSixthPhoneNumber, *pSixthPhoneNumber);

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