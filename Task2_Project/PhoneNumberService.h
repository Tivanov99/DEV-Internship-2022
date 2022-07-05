#pragma once
#include <string>
#include "Structures.h"
#include "BaseService.h"

using namespace std;

class PhoneNumberService :public BaseService<PHONE_NUMBERS>
{
private:
	string ConvertToString(char* phoneNumber);
public:
	void AddDefaultElements(CPhoneNumbersArray& oArray) override;
	void SetPhoneNumber(string sorce, PHONE_NUMBERS& phoneNumber);
	void ShowElementInfoAtIndex(const int nIndex, const CPhoneNumbersArray& oArray) override;
	void ChangePhoneNumber(string oldPhoneNumber, string newPhoneNumber, CPhoneNumbersArray& oPhoneTypesArray);
	void ChangePhoneNumber(PHONE_NUMBERS& pOldPhoneNumberElement, string newPhoneNumber);
};

