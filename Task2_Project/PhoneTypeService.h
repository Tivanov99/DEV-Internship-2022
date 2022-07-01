#pragma once
#include "Structures.h"
#include <exception>
#include <stdexcept>
#include <iostream>
using namespace std;
class PhoneTypeService
{
private:
	CPhoneTypesArray oPhoneTypesArray;

public:
	PhoneTypeService()
	{

	};
	void FillPhoneType(string sorce, PhoneType* phone) {
		size_t LengthOfArray = sizeof(phone->PHONE_TYPE) / sizeof(char);

		if (sorce.length() <= LengthOfArray) {
			for (size_t i = 0; i < sorce.size(); i++)
			{
				phone->PHONE_TYPE[i] = sorce[i];
			}
		}
		else {
			cout << "Too long sorce" << endl;
		}
	};

	void AddPhoneTypeElements(CPhoneTypesArray& phoneTypes) {
		try
		{
			PhoneType* pMobilePhoneType = NULL;
			pMobilePhoneType = new PhoneType();
			FillPhoneType("mobile", pMobilePhoneType);

			PhoneType* pHomePhoneType = NULL;
			pHomePhoneType = new PhoneType();
			FillPhoneType("home", pHomePhoneType);

			PhoneType* pOfficePhoneType = NULL;
			pOfficePhoneType = new PhoneType();
			FillPhoneType("office", pOfficePhoneType);

			phoneTypes.Add(pMobilePhoneType);
			phoneTypes.Add(pHomePhoneType);
			phoneTypes.Add(pOfficePhoneType);
		}
		catch (const std::exception&)
		{
			cout << "Invalid 'Add' operation!"<< endl;
		}
	}

	void ValidateArguments(int index, CPhoneTypesArray& oPhoneTypesArray) {
		if (oPhoneTypesArray.IsEmpty())
		{
			throw invalid_argument("The array is empty!");
		}
		else if (index > oPhoneTypesArray.GetCount()) {
			throw invalid_argument("Index out of range!");
		}
		else if (index < 0) {
			throw invalid_argument("Index should be possitive!");
		}
	};

	void ShowElementInfoAtIndex(int index, CPhoneTypesArray& oPhoneTypesArray) {
		try
		{
			ValidateArguments(index, oPhoneTypesArray);
			PhoneType* pTemp = NULL;
			pTemp = oPhoneTypesArray.GetAt(index);
			cout << "Selected item info: " << "memory address: " << &pTemp << " value:" << pTemp->PHONE_TYPE << endl;
		}
		catch (const std::exception&)
		{
			cout << "Something goes wrong, try again!" << endl;
		}
	}

	PhoneType* GetPointerAtIndex(int index, CPhoneTypesArray& oPhoneTypesArray) {
		try
		{
			ValidateArguments(index, oPhoneTypesArray);
			throw invalid_argument("Something goes wrong, try again!");

			PhoneType* pPhoneType = NULL;
			pPhoneType = oPhoneTypesArray.ElementAt(index);
			return pPhoneType;
		}
		catch (exception& ex)
		{
			cout << ex.what();
		}
	};

	void RemoveAt(int index, int count, CPhoneTypesArray& oPhoneTypesArray) {
		try
		{
			ValidateArguments(index, oPhoneTypesArray);
			oPhoneTypesArray.RemoveAt(0, 5);
		}
		catch (exception ex)
		{
			cout << ex.what()<< endl;
		}
	}
};

