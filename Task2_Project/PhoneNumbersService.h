#pragma once
#include <string>
#include "Structures.h"
#include <iostream>
using namespace std;
class PhoneNumbersService
{
private:
	string ConvertToString(char* phoneNumber) {
		string sValue;
		sValue = phoneNumber;
		return sValue;
	}
public:
	PhoneNumbersService()
	{

	};

	void SetPhoneNumber(string sorce, PhoneNumber* phoneNumber) {
		size_t LengthOfArray = sizeof(phoneNumber->PHONE_NUMBER) / sizeof(char);

		if (sorce.length() <= LengthOfArray) {
			for (size_t i = 0; i < sorce.size(); i++)
			{
				phoneNumber->PHONE_NUMBER[i] = sorce[i];
			}
		}
		else {
			cout << "Too long sorce";
		}
	};

	void AddDefaultPhoneNumbersElements(CPhoneNumbersArray& phoneNumbers) {
		try
		{
			PhoneNumber* pMobilePhoneType = NULL;
			pMobilePhoneType = new PhoneNumber();
			SetPhoneNumber("mobile", pMobilePhoneType);

			PhoneNumber* pHomePhoneType = NULL;
			pHomePhoneType = new PhoneNumber();
			SetPhoneNumber("home", pHomePhoneType);

			PhoneNumber* pOfficePhoneType = NULL;
			pOfficePhoneType = new PhoneNumber();
			SetPhoneNumber("office", pOfficePhoneType);

			phoneNumbers.Add(pMobilePhoneType);
			phoneNumbers.Add(pHomePhoneType);
			phoneNumbers.Add(pOfficePhoneType);
		}
		catch (const std::exception&)
		{
			cout << "Invalid 'Add' operation!";
		}

	}

	void ValidateArguments(int index, CPhoneNumbersArray& oPhoneNumbersArray) {
		if (oPhoneNumbersArray.IsEmpty())
		{
			throw invalid_argument("The array is empty!");
		}
		else if (index > oPhoneNumbersArray.GetCount()) {
			throw invalid_argument("Index out of range!");
		}
		else if (index < 0) {
			throw invalid_argument("Index should be possitive!");
		}
	};

	void ShowElementInfoAtIndex(int index, CPhoneNumbersArray& oPhoneTypesArray) {
		try
		{
			ValidateArguments(index, oPhoneTypesArray);
			PhoneNumber* pTemp = NULL;
			pTemp = oPhoneTypesArray.GetAt(index);
			cout << "Selected item info: " << "memory address: " << &pTemp << " value:" << pTemp->PHONE_NUMBER << endl;
		}
		catch (const std::exception&)
		{
			cout << "Something goes wrong, press again!";
		}
	}

	PhoneNumber* GetPointerAtIndex(int index, CPhoneNumbersArray& oPhoneTypesArray) {
		try
		{
			ValidateArguments(index, oPhoneTypesArray);
			throw invalid_argument("Something goes wrong, press again!");

			PhoneNumber* pPhoneType = NULL;
			pPhoneType = oPhoneTypesArray.ElementAt(index);
			return pPhoneType;
		}
		catch (exception& ex)
		{
			cout << ex.what();
		}
	};

	void RemoveAt(int index, int count, CPhoneNumbersArray& oPhoneTypesArray) {
		try
		{
			ValidateArguments(index, oPhoneTypesArray);
			oPhoneTypesArray.RemoveAt(index, count);
			oPhoneTypesArray.FreeExtra();
		}
		catch (exception ex)
		{
			cout << ex.what();
		}
	};

	void ChangePhoneNumber(string oldPhoneNumber, string newPhoneNumber, CPhoneNumbersArray& oPhoneTypesArray) {
		for (size_t i = 0; i < oPhoneTypesArray.GetSize(); i++)
		{
			string currentPhoneNumber =NULL;
			currentPhoneNumber = ConvertToString(oPhoneTypesArray[i]->PHONE_NUMBER);

			if (currentPhoneNumber._Equal(oldPhoneNumber)) {
				for (size_t s = 0; s < currentPhoneNumber.length(); s++)
				{
					oPhoneTypesArray[s]->PHONE_NUMBER[s] = currentPhoneNumber[s];
				}
				break;
			}
		}
	}
};

