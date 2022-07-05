#pragma once
#include "BaseService.h";

class PhoneTypeService : public BaseService<PHONE_TYPES>
{
public:
	void SetPhoneType(const string sorce, PHONE_TYPES& phone);
	void AddDefaultElements(CPhoneTypesArray& phoneTypes) override;
	void ShowElementInfoAtIndex(const int nIndex, const CPhoneTypesArray& oPhoneTypesArray) override;
};

