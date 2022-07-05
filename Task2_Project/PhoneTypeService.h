#pragma once
#include "BaseService.h";

class PhoneTypeService : public BaseService<PHONE_TYPES>
{
public:
	void AddDefaultElements(CPhoneTypesArray& phoneTypes) override ;
	void ShowElementInfoAtIndex(const int nIndex, const CPhoneTypesArray &oPhoneTypesArray) override;
	void SetPhoneType(CString &strType, PHONE_TYPES &oPhone);
};

