#include "pch.h"
#include "PhoneNumberService.h"

string PhoneNumberService::ConvertToString(char* phoneNumber) {
	string sValue;
	sValue = phoneNumber;
	return sValue;
};


void PhoneNumberService::SetPhoneNumber(string sorce, PHONE_NUMBERS& phoneNumber) {
	size_t LengthOfArray = sizeof(phoneNumber.szPHONE_NUMBER) / sizeof(char);

	if (sorce.length() <= LengthOfArray) {
		for (size_t i = 0; i < sorce.size(); i++)
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
		PHONE_NUMBERS* pFirstPhoneNumber = NULL;
		pFirstPhoneNumber = new PHONE_NUMBERS();
		SetPhoneNumber("0893668829", *pFirstPhoneNumber);

		PHONE_NUMBERS* pSecondPhoneNumber = NULL;
		pSecondPhoneNumber = new PHONE_NUMBERS();
		SetPhoneNumber("0883737518", *pSecondPhoneNumber);

		PHONE_NUMBERS* pThirdPhoneNumber = NULL;
		pThirdPhoneNumber = new PHONE_NUMBERS();
		SetPhoneNumber("0875462946", *pThirdPhoneNumber);

		PHONE_NUMBERS* pFourthPhoneNumber = NULL;
		pFourthPhoneNumber = new PHONE_NUMBERS();
		SetPhoneNumber("0886372847", *pFourthPhoneNumber);

		PHONE_NUMBERS* pFifthPhoneNumber = NULL;
		pFifthPhoneNumber = new PHONE_NUMBERS();
		SetPhoneNumber("0895467264", *pFifthPhoneNumber);

		PHONE_NUMBERS* pSixthPhoneNumber = NULL;
		pSixthPhoneNumber = new PHONE_NUMBERS();
		SetPhoneNumber("0891937373", *pSixthPhoneNumber);

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
(string oldPhoneNumber, string newPhoneNumber, CPhoneNumbersArray& oPhoneTypesArray)
{
	for (size_t i = 0; i < oPhoneTypesArray.GetSize(); i++)
	{
		string currentPhoneNumber;
		currentPhoneNumber = ConvertToString(oPhoneTypesArray[i]->szPHONE_NUMBER);

		if (currentPhoneNumber._Equal(oldPhoneNumber)) {
			PHONE_NUMBERS* pOldPhoneNumber = NULL;
			pOldPhoneNumber = oPhoneTypesArray[i];

			for (size_t s = 0; s < currentPhoneNumber.length(); s++)
			{
				pOldPhoneNumber->szPHONE_NUMBER[s] = newPhoneNumber[s];
			}
			break;
		}
	}
}
void PhoneNumberService::ChangePhoneNumber(PHONE_NUMBERS& pOldPhoneNumberElement, string newPhoneNumber)
{
	string sOldPhoneNumber = ConvertToString(pOldPhoneNumberElement.szPHONE_NUMBER);

	for (size_t s = 0; s < newPhoneNumber.length(); s++)
	{
		pOldPhoneNumberElement.szPHONE_NUMBER[s] = newPhoneNumber[s];
	}
}