#pragma once
#include "BaseService.h";

class PhoneTypeService: BaseService
{
public:
	void SetPhoneType(const string sorce, PHONE_TYPES& phone);
	//void AddPhoneTypeElements(CPhoneTypesArray& phoneTypes);
	//void ShowElementInfoAtIndex(const int index, CPhoneTypesArray& oPhoneTypesArray);
	//PHONE_TYPES* GetPointerAtIndex(const int index, CPhoneTypesArray& oPhoneTypesArray);
};

