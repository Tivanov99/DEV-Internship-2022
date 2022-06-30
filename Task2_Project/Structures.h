#pragma once
#include <WinBase.h>
#include <string>

/// <summary>
///  ������� ��������� CITIES ������������� �� ��������� 'CITIES'
/// </summary>
struct CITIES {
	/// <summary>���������� ��������� �������� ���� �� �������� 'ID' � ��������� 'CITIES'</summary>
	int nID;
	/// <summary>?</summary>
	int nUPDATE_COUNTER;
	/// <summary>���������� ��������� ���������� �� ������ 'CITY_NAME' � ��������� 'CITIES'</summary>
	char  CITY_NAME[32];
	/// <summary>���������� ��������� ���������� �� ������ 'AREA_NAME' � ��������� 'CITIES'</summary>
	char AREA_NAME[32];
	/// <summary>���������� ��������� ���������� �� ������ 'POSTAL_CODE' � ��������� 'CITIES'</summary>
	int nPOSTAL_CODE;

	CITIES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

/// <summary>
///  ������� ��������� PERSONS ������������� �� ��������� 'PERSONS'
/// </summary>
struct PERSONS {
	/// <summary>���������� ��������� �������� ���� �� �������� 'ID' � ��������� 'PERSONS'</summary>
	int nID;
	/// <summary>?</summary>
	int nUPDATE_COUNTER;
	/// <summary>���������� ��������� ���������� �� ������ 'FIRST_NAME' � ���������  'PERSONS'</summary>
	char FIRST_NAME[32];
	/// <summary>���������� ��������� ���������� �� ������ 'SECOND_NAME' � ���������  'PERSONS'</summary>
	char SECOND_NAME[32];
	/// <summary>���������� ��������� ���������� �� �������� 'LAST_NAME' � ���������  'PERSONS'</summary>
	char LAST_NAME[32];
	/// <summary>���������� ��������� �������� ���� (�� ������ 'CITY_ID' � ���������  'PERSONS')
	/// <summary>����� ��� ��������� 'CITIES' � ������ 'ID'</summary>
	int nCITY_ID;
	/// <summary>���������� ��������� ���������� �� �������� 'ADDRESS' � ���������  'PERSONS'</summary>
	char ADDRESS[256];

	PERSONS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

/// <summary>
///  ������� ��������� 'PHONE_NUMBERS' ������������� �� ��������� 'PHONE_NUMBERS'
/// </summary>
struct PHONE_NUMBERS {
	/// <summary>���������� ��������� �������� ���� �� �������� 'ID' � ��������� 'PHONE_NUMBERS'</summary>
	int nID;
	/// <summary>?</summary>
	int nUPDATE_COUNTER;
	/// <summary>���������� ��������� �������� ���� (�� ������ 'PHONE_TYPE_ID' � ���������  'PHONE_TYPES')
	/// <summary>����� ��� �������� 'ID' � ��������� 'PHONE_NUMBERS'</summary>;
	int nPHONE_TYPE_ID;
	/// <summary>���������� ��������� ���������� �� �������� 'PHONE_NUMBER' � ���������  'PHONE_NUMBERS'</summary>
	char PHONE_NUMBER[16];
	PHONE_NUMBERS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

/// <summary>
///  ������� ��������� PHONE_TYPES ������������� �� ��������� 'PHONE_TYPES'
/// </summary>
struct PHONE_TYPES {
	/// <summary>���������� ��������� �������� ���� �� �������� 'ID' � ��������� 'PHONE_TYPES'</summary>
	int ID;
	/// <summary>?</summary>
	int UPDATE_COUNTER;
	/// <summary>���������� ��������� ���������� �� �������� 'PHONE_TYPE' � ���������  'PHONE_TYPES'</summary>
	char PHONE_TYPE[16];
	PHONE_TYPES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};


typedef CTypedPtrArray < CPtrArray, PHONE_NUMBERS> CPhoneNumbersArray;

typedef CTypedPtrArray < CPtrArray, CITIES> CCitiesArray;

typedef CTypedPtrArray < CPtrArray, PERSONS> CPersonsArray;

typedef CTypedPtrArray < CPtrArray, PHONE_TYPES> CPhoneTypesArray;