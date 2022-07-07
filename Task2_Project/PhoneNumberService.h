#pragma once
#include <string>
#include "Structures.h"
#include "BaseService.h"

using namespace std;

class PhoneNumberService :public BaseService<PHONE_NUMBERS>
{
private:
	//<summary>Попълва 'PHONE_NUMBER' на обект подаден като аргумент 'phoneNumber'.</summary>
	void SetPhoneNumber(const CString& sorce, PHONE_NUMBERS& phoneNumber);
public:

	PhoneNumberService()
	{

	}
	~PhoneNumberService() {

	}
	//<summary>Функция добавяща всички дефоутни елементи в подаден масив
	//като аргумент пренаписана от базов клас 'BaseService'.</summary>
	void AddDefaultElements(CPhoneNumbersArray& oArray) override;
	//<summary>Функция принтираща информация за обект намиращ се на позицията на nIndex,
	//всеки под сървис я импелеметира пренаписана от базов клас 'BaseService'.</summary>
	void ShowElementInfoAtIndex(const int nIndex, const CPhoneNumbersArray& oArray) override;
	//<summary>Функция променяща стойността на 'PHONE_NUMBER' на обект чиято текуща сойност е 'oldPhoneNumber'.</summary>
	void ChangePhoneNumber(const CString &strPhoneNumber, const CString &strNewPhoneNumber, CPhoneNumbersArray& oPhoneTypesArray);
	//<summary>Функция променяща стойността на 'PHONE_NUMBER' на обект подаден като аргумент 'pOldPhoneNumberElement' .</summary>
	void ChangePhoneNumber(PHONE_NUMBERS& pOldPhoneNumberElement, const CString &strNewPhoneNumber);
};

