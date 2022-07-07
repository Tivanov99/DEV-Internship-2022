#pragma once
#include "BaseService.h";
#include "Structures.h";

class PhoneTypeService : public BaseService<PHONE_TYPES>
{
private:
	//<summary>������� �������� �������� �� ������ 'PHONE_TYPE'�� ������� �����</summary>
	void SetPhoneType(CString& strType, PHONE_TYPES& oPhone);
public:
	PhoneTypeService()
	{

	}
	~PhoneTypeService()
	{

	}
	//<summary>������� �������� ������ �������� �������� � ������� �����
	//���� �������� ����������� �� ����� ���� 'BaseService'.</summary>
	void AddDefaultElements(CPhoneTypesArray& oArray) override;
	//<summary>������� ���������� ���������� �� ����� ������� �� �� ��������� �� nIndex,
	//����� ��� ������ � ������������ ����������� �� ����� ���� 'BaseService'.</summary>
	void ShowElementInfoAtIndex(const int nIndex, const CPhoneTypesArray& oArray) override;
};

