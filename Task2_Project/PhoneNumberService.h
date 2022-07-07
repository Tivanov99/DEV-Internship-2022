#pragma once
#include <string>
#include "Structures.h"
#include "BaseService.h"

using namespace std;

class PhoneNumberService :public BaseService<PHONE_NUMBERS>
{
private:
	//<summary>������� 'PHONE_NUMBER' �� ����� ������� ���� �������� 'phoneNumber'.</summary>
	void SetPhoneNumber(const CString& sorce, PHONE_NUMBERS& phoneNumber);
public:

	PhoneNumberService()
	{

	}
	~PhoneNumberService() {

	}
	//<summary>������� �������� ������ �������� �������� � ������� �����
	//���� �������� ����������� �� ����� ���� 'BaseService'.</summary>
	void AddDefaultElements(CPhoneNumbersArray& oArray) override;
	//<summary>������� ���������� ���������� �� ����� ������� �� �� ��������� �� nIndex,
	//����� ��� ������ � ������������ ����������� �� ����� ���� 'BaseService'.</summary>
	void ShowElementInfoAtIndex(const int nIndex, const CPhoneNumbersArray& oArray) override;
	//<summary>������� ��������� ���������� �� 'PHONE_NUMBER' �� ����� ����� ������ ������� � 'oldPhoneNumber'.</summary>
	void ChangePhoneNumber(const CString &strPhoneNumber, const CString &strNewPhoneNumber, CPhoneNumbersArray& oPhoneTypesArray);
	//<summary>������� ��������� ���������� �� 'PHONE_NUMBER' �� ����� ������� ���� �������� 'pOldPhoneNumberElement' .</summary>
	void ChangePhoneNumber(PHONE_NUMBERS& pOldPhoneNumberElement, const CString &strNewPhoneNumber);
};

