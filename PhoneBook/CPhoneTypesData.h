#pragma once
#include "Structures.h"
#include "CPhoneTypesTable.h"
class CPhoneTypesData
{
public:
	CPhoneTypesData();
	~CPhoneTypesData();

	// Methods
	// ----------------

	/// <summary>
	///  ������� ����� ���� ����� ������ �� ��������� "PHONE_TYPES" � �� ������ � ������� ���� �������� �����.
	/// </summary>
	/// <param name="oPhoneTyesArray">����� � ����� �� ����� �������� ������ ��������� �����.</param>
	bool SelectAll(CPhoneTypesArray& oPhoneTyesArray);

	/// <summary>
	///  ������� ����� ���� ����� �� ��������� "PHONE_TYPES" ����� ID �������� �� "lID" � �� ���������� � "recPhoneType" ���������.
	/// </summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	/// <param name="recPhoneType">���������� ����� �� ������� ��������� �� ���������</param>
	bool SelectWhereID(const long lID, PHONE_TYPES& recPhoneType);

	/// <summary>
	///  ������� ����� ����� ������� �� ����� �� ��������� "PHONE_TYPES" ����� ID �������� �� "lID" ���������,
	///  � �� ������� ��������� �� ��������� "recPhoneType" � ������ �������� �� ������.
	/// </summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	/// <param name="recPhoneType">���������� ����� ������� ���� ����������� �����.</param>
	bool UpdateWhereID(const long lID, const PHONE_TYPES& recPhoneType);

	/// <summary>
	///  ������� ����� ������ ����� ������� ���� �������� ��� ��������� "PHONE_TYPES".
	/// </summary>
	/// <param name="recPhoneType">���������� ����� ������� ��� �����.</param>
	bool InsertRecord(const PHONE_TYPES& recPhoneType);

	/// <summary>
	///  ������� ����� ������� ����� �� ��������� "PHONE_TYPES" ����� �������� �� "lID" ���������.
	/// </summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	bool DeleteWhereID(const long lID);

private:
	/// <summary>
	/// ������ �� ������ �� ������ �������� ������ ��������.
	/// </summary>
	CPhoneTypesTable m_PhoneTypesTable;

	CSession m_oSession;
};

