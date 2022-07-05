#include "pch.h"
#include "PhoneNumberService.h"

string PhoneNumberService::ConvertToString(char* phoneNumber) {
	string sValue;
	sValue = phoneNumber;
	return sValue;
};


void PhoneNumberService::SetPhoneNumber(string sorce, PhoneNumber* phoneNumber) {
	size_t LengthOfArray = sizeof(phoneNumber->PHONE_NUMBER) / sizeof(char);

	if (sorce.length() <= LengthOfArray) {
		for (size_t i = 0; i < sorce.size(); i++)
		{
			phoneNumber->PHONE_NUMBER[i] = sorce[i];
		}
	}
	else {
		cout << "Too long sorce" << endl;
	}
};

void PhoneNumberService::AddDefaultPhoneNumbersElements(CPhoneNumbersArray& phoneNumbers) {
	try
	{
		PhoneNumber* pFirstPhoneNumber = NULL;
		pFirstPhoneNumber = new PhoneNumber();
		SetPhoneNumber("0893668829", pFirstPhoneNumber);

		PhoneNumber* pSecondPhoneNumber = NULL;
		pSecondPhoneNumber = new PhoneNumber();
		SetPhoneNumber("0883737518", pSecondPhoneNumber);

		PhoneNumber* pThirdPhoneNumber = NULL;
		pThirdPhoneNumber = new PhoneNumber();
		SetPhoneNumber("0875462946", pThirdPhoneNumber);

		PhoneNumber* pFourthPhoneNumber = NULL;
		pFourthPhoneNumber = new PhoneNumber();
		SetPhoneNumber("0886372847", pFourthPhoneNumber);

		PhoneNumber* pFifthPhoneNumber = NULL;
		pFifthPhoneNumber = new PhoneNumber();
		SetPhoneNumber("0895467264", pFifthPhoneNumber);

		PhoneNumber* pSixthPhoneNumber = NULL;
		pSixthPhoneNumber = new PhoneNumber();
		SetPhoneNumber("0891937373", pSixthPhoneNumber);

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
		PhoneNumber* pTemp = NULL;
		pTemp = oPhoneTypesArray.GetAt(index);
		cout << "Selected item info: " << "memory address: " << &pTemp << " value:" << pTemp->PHONE_NUMBER << endl;
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
		currentPhoneNumber = ConvertToString(oPhoneTypesArray[i]->PHONE_NUMBER);

		if (currentPhoneNumber._Equal(oldPhoneNumber)) {
			PhoneNumber* pOldPhoneNumber = NULL;
			pOldPhoneNumber = oPhoneTypesArray[i];

			for (size_t s = 0; s < currentPhoneNumber.length(); s++)
			{
				pOldPhoneNumber->PHONE_NUMBER[s] = newPhoneNumber[s];
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
void PhoneNumberService::ChangePhoneNumber(PhoneNumber* pOldPhoneNumberElement, string newPhoneNumber)
{
	string sOldPhoneNumber = ConvertToString(pOldPhoneNumberElement->PHONE_NUMBER);

	for (size_t s = 0; s < newPhoneNumber.length(); s++)
	{
		pOldPhoneNumberElement->PHONE_NUMBER[s] = newPhoneNumber[s];
	}
}