#pragma once
#include "Structures.h"
#include "DataBaseConnector.h"

class CPhoneNumbersData
{
	// Constructor / Destructor
	// ----------------
public:
	CPhoneNumbersData();
	~CPhoneNumbersData();

	// Methods
	// ----------------
public:
	/// <summary>������� ����� ���� ����� ������ �� ��������� "PHONE_NUMBERS" � �� ������ � ������� ���� �������� �����.</summary>
	/// <param name="oPhoneNumbersArray">����� � ����� �� ����� �������� ������ ��������� �����.</param>
	bool SelectAll(CPhoneNumbersArray& oPhoneNumbersArray);
	/// <summary>������� ����� ���� ����� �� ��������� "PHONE_NUMBERS" ����� ID �������� �� "lID" � �� ���������� � "recPhoneNumbers" ���������.</summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	/// <param name="recPhoneNumbers">���������� ����� �� ������� ��������� �� ���������</param>
	bool SelectWhereID(const long lID, PHONE_NUMBERS& recPhoneNumbers);
	/// <summary>������� ����� ����� ������� �� ����� �� ��������� "PHONE_NUMBERS" ����� ID �������� �� "lID" ���������,� �� ������� ��������� �� ��������� "recPhoneNumbers" � ������ �������� �� ������.</summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	/// <param name="recPhoneNumbers">���������� ����� ������� ���� ����������� �����.</param>
	bool UpdateWhereID(const long lID, const PHONE_NUMBERS& recPhoneNumbers);
	/// <summary>������� ����� ������ ����� ������� ���� �������� ��� ��������� "PHONE_NUMBERS".</summary>
	/// <param name="recPhoneNumbers">���������� ����� ������� ��� �����.</param>
	bool InsertPhoneNumber(PHONE_NUMBERS& recPhoneNumbers);
	/// <summary>������� ����� ������� ����� �� ��������� "CITIES" ����� �������� �� "lID" ���������.</summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
	bool DeleteWhereID(const long lID);
};

