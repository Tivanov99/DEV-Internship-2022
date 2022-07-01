#pragma once
#include <string>
#include "Structures.h"
#include <iostream>
using namespace std;

class PhoneTypesService
{
public:
	PhoneTypesService()
	{

	};
	void SetPhoneType(string sorce, PhoneType* phone) {
		size_t LengthOfArray = sizeof(phone->PHONE_TYPE) / sizeof(char);

		if (sorce.length() <= LengthOfArray) {
			for (size_t i = 0; i < sorce.size(); i++)
			{
				phone->PHONE_TYPE[i] = sorce[i];
			}
		}
		else {
			cout << "Too long sorce";
		}
	};

	void AddPhoneTypeElements(CPhoneTypesArray& phoneTypes) {
		try
		{
			PhoneType* pMobilePhoneType = NULL;
			pMobilePhoneType = new PhoneType();
			SetPhoneType("mobile", pMobilePhoneType);

			PhoneType* pHomePhoneType = NULL;
			pHomePhoneType = new PhoneType();
			SetPhoneType("home", pHomePhoneType);

			PhoneType* pOfficePhoneType = NULL;
			pOfficePhoneType = new PhoneType();
			SetPhoneType("office", pOfficePhoneType);

			phoneTypes.Add(pMobilePhoneType);
			phoneTypes.Add(pHomePhoneType);
			phoneTypes.Add(pOfficePhoneType);
		}
		catch (const std::exception&)
		{
			cout << "Invalid 'Add' operation!";
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
			cout << "Something goes wrong, press again!";
		}
	}

	PhoneType* GetPointerAtIndex(int index, CPhoneTypesArray& oPhoneTypesArray) {
		try
		{
			ValidateArguments(index, oPhoneTypesArray);
			throw invalid_argument("Something goes wrong, press again!");

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
			oPhoneTypesArray.RemoveAt(index, count);
			oPhoneTypesArray.FreeExtra();
		}
		catch (exception ex)
		{
			cout << ex.what();
		}
	}
};

