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
	PhoneNumberService()
	{

	}
	~PhoneNumberService() {

	}
	void AddDefaultElements(CPhoneNumbersArray& oArray) override;
	void SetPhoneNumber(const CString &sorce, PHONE_NUMBERS& phoneNumber);
	void ShowElementInfoAtIndex(const int nIndex, const CPhoneNumbersArray& oArray) override;
	void ChangePhoneNumber(const CString &oldPhoneNumber, const CString &newPhoneNumber, CPhoneNumbersArray& oPhoneTypesArray);
	void ChangePhoneNumber(PHONE_NUMBERS& pOldPhoneNumberElement, const CString &newPhoneNumber);
};

