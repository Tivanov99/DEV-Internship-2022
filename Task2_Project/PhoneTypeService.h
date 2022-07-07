#pragma once
#include "BaseService.h";
#include "Structures.h";

class PhoneTypeService : public BaseService<PHONE_TYPES>
{
private:
	//<summary>Функция задаваща стойност на мембър 'PHONE_TYPE'на подаден обект</summary>
	void SetPhoneType(CString& strType, PHONE_TYPES& oPhone);
public:
	PhoneTypeService()
	{

	}
	~PhoneTypeService()
	{

	}
	//<summary>Функция добавяща всички дефоутни елементи в подаден масив
	//като аргумент пренаписана от базов клас 'BaseService'.</summary>
	void AddDefaultElements(CPhoneTypesArray& oArray) override;
	//<summary>Функция принтираща информация за обект намиращ се на позицията на nIndex,
	//всеки под сървис я импелеметира пренаписана от базов клас 'BaseService'.</summary>
	void ShowElementInfoAtIndex(const int nIndex, const CPhoneTypesArray& oArray) override;
};

