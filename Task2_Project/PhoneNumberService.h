#pragma once
#include <string>
#include "Structures.h"
#include "BaseService.h"

using namespace std;

class PhoneNumberService :public BaseService
{
private:
	string ConvertToString(char* phoneNumber);
public:
	void SetPhoneNumber(string sorce, PhoneNumber* phoneNumber);
	void AddDefaultPhoneNumbersElements(CPhoneNumbersArray& phoneNumbers);
	void ShowElementInfoAtIndex(const int index, CPhoneNumbersArray& oPhoneTypesArray);
	PhoneNumber* GetPointerAtIndex(int index);
	void RemoveAt(int index, int count, CPhoneNumbersArray& oPhoneTypesArray);
	void ChangePhoneNumber(string oldPhoneNumber, string newPhoneNumber, CPhoneNumbersArray& oPhoneTypesArray);
	void ChangePhoneNumber(PhoneNumber* pOldPhoneNumberElement, string newPhoneNumber);
	template<class T> T* GetPointerAtIndex(const int nIndex, CTypedPtrArray<CPtrArray, class T*>& elementsCollection);
};

