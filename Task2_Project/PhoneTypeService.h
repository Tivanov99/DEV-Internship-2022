#pragma once
class PhoneTypeService
{
public:
	void SetPhoneType(string sorce, PhoneType* phone);
	void AddPhoneTypeElements(CPhoneTypesArray& phoneTypes);
	void ValidateArguments(int index, CPhoneTypesArray& oPhoneTypesArray);
	void ShowElementInfoAtIndex(int index, CPhoneTypesArray& oPhoneTypesArray);
	PhoneType* GetPointerAtIndex(const int index, CPhoneTypesArray& oPhoneTypesArray);
	void RemoveAt(int index, int count, CPhoneTypesArray& oPhoneTypesArray);
};

