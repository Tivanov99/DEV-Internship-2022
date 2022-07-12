#pragma once
#include "BaseService.h";
#include "Structures.h";

class PhoneTypeService : public BaseService<PHONE_TYPES>
{
private:
	///<summary>������� �������� �������� �� ������ 'PHONE_TYPE' �� ������� ����� ���� ��������.</summary>
	/// <param name="strType">��� ��������� �����.</param>
	/// <param name="oPhone">���������� ��� �����.</param>
	void SetPhoneType(CString& strType, PHONE_TYPES& oPhone);
public:
	PhoneTypeService();
	~PhoneTypeService();

	///<summary>
		/// ������� �������� ������ �������� �������� � ������� ����� ���� ��������.
		/// ������� ����������� �� ����� ���� 'BaseService'.
	/// </summary>
	///<param name="citiesArray">����� � ����� �� �� ������� ������ ���������.</param>
	void AddDefaultElements(CPhoneTypesArray& oArray) override;

	///<summary>
		///������� ���������� ���������� �� ����� ������� �� �� ��������� �� nIndex.
		///������� ����������� �� ����� ���� 'BaseService'.
	///</summary>
	/// <param name="�nIndex">������� �� �������� � ������.</param>
	/// <param name="�oArray">����� � ��������.</param>
	void ShowElementInfoAtIndex(const int nIndex, const CPhoneTypesArray& oArray) override;
};

