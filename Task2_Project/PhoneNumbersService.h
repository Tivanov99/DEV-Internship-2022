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
			string currentPhoneNumber;
			currentPhoneNumber = ConvertToString(oPhoneTypesArray[i]->PHONE_NUMBER);

			if (currentPhoneNumber._Equal(oldPhoneNumber)) {
				for (size_t s = 0; s < currentPhoneNumber.length(); s++)
				{
					oPhoneTypesArray[s]->PHONE_NUMBER[s] = newPhoneNumber[s];
				}
				break;
			}
		}
	}
};

