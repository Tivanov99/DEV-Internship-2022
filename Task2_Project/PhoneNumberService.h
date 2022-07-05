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
	template<class T> void AddDefaultElements(CTypedPtrArray<CPtrArray, class T*>& elementsCollection);
	void SetPhoneNumber(string sorce, PHONE_NUMBERS& phoneNumber);
	void ShowElementInfoAtIndex(const int index, CPhoneNumbersArray& oPhoneTypesArray);
	void ChangePhoneNumber(string oldPhoneNumber, string newPhoneNumber, CPhoneNumbersArray& oPhoneTypesArray);
	void ChangePhoneNumber(PHONE_NUMBERS& pOldPhoneNumberElement, string newPhoneNumber);
};

