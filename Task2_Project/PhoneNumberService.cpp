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

void PhoneNumberService::AddDefaultElements(CPhoneNumbersArray& phoneNumbers) {
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

		phoneNumbers.Add(pFirstPhoneNumber);
		phoneNumbers.Add(pSecondPhoneNumber);
		phoneNumbers.Add(pThirdPhoneNumber);
		phoneNumbers.Add(pFourthPhoneNumber);
		phoneNumbers.Add(pFifthPhoneNumber);
		phoneNumbers.Add(pSixthPhoneNumber);
	}
	catch (const std::exception&)
	{
		cout << "Invalid 'Add' operation!" << endl;
	}
}

void PhoneNumberService::ShowElementInfoAtIndex(const int index, CPhoneNumbersArray& oPhoneTypesArray) {
	try
	{
		ValidateIndex(index, oPhoneTypesArray.GetSize());
		PHONE_NUMBERS* pTemp = NULL;
		pTemp = oPhoneTypesArray.GetAt(index);
		cout << "Selected item info: " << "memory address: " << &pTemp << " value:" << pTemp->szPHONE_NUMBER << endl;
	}
	catch (const std::exception&)
	{
		cout << "Something goes wrong, try again!" << endl;
	}
}

void PhoneNumberService::RemoveAt(const int index, const int count, CPhoneNumbersArray& oPhoneTypesArray) {
	try
	{
		ValidateIndex(index, oPhoneTypesArray.GetSize());
		oPhoneTypesArray.RemoveAt(index, count);
		oPhoneTypesArray.FreeExtra();
	}
	catch (exception ex)
	{
		cout << ex.what();
	}
};

void PhoneNumberService::ChangePhoneNumber(string oldPhoneNumber, string newPhoneNumber, CPhoneNumbersArray& oPhoneTypesArray)
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
template<class T> T* PhoneNumberService::GetPointerAtIndex(const int nIndex, CTypedPtrArray<CPtrArray, class T*>& elementsCollection)
{
	try
	{
		ValidateIndex(index, oPhoneTypesArray);

		PhoneNumber* pPhoneType = NULL;
		pPhoneType = oPhoneTypesArray.ElementAt(index);
		return pPhoneType;
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
	}
};
void PhoneNumberService::ChangePhoneNumber(PHONE_NUMBERS* pOldPhoneNumberElement, string newPhoneNumber)
{
	string sOldPhoneNumber = ConvertToString(pOldPhoneNumberElement->szPHONE_NUMBER);

	for (size_t s = 0; s < newPhoneNumber.length(); s++)
	{
		pOldPhoneNumberElement->szPHONE_NUMBER[s] = newPhoneNumber[s];
	}
}