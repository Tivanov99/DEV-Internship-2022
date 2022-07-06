#pragma once
#include <WinBase.h>
#include <string>

#define CITY_NAME_SIZE	32
#define AREA_NAME_SIZE	32

/// <summary>
///  ������� ��������� CITIES ������������� �� ��������� 'CITIES'
/// </summary>
struct CITIES 
{
	/// <summary>���������� ��������� �������� ���� �� �������� 'ID' � ��������� 'CITIES'</summary>
	long lID;
	/// <summary>?</summary>
	long lUPDATE_COUNTER;
	/// <summary>���������� ��������� ���������� �� ������ 'CITY_NAME' � ��������� 'CITIES'</summary>
	TCHAR szCITY_NAME[32];
	/// <summary>���������� ��������� ���������� �� ������ 'AREA_NAME' � ��������� 'CITIES'</summary>
	TCHAR szAREA_NAME[32];
	/// <summary>���������� ��������� ���������� �� ������ 'POSTAL_CODE' � ��������� 'CITIES'</summary>
	long lPOSTAL_CODE;

	CITIES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

#define FIRST_NAME_SIZE		32
#define SECOND_NAME_SIZE	32
#define LAST_NAME_SIZE		32
#define ADDRESS_SIZE		256

/// <summary>
///  ������� ��������� PERSONS ������������� �� ��������� 'PERSONS'
/// </summary>
struct PERSONS {
	/// <summary>���������� ��������� �������� ���� �� �������� 'ID' � ��������� 'PERSONS'</summary>
	long lID;
	/// <summary>?</summary>
	long lUPDATE_COUNTER;
	/// <summary>���������� ��������� ���������� �� ������ 'FIRST_NAME' � ���������  'PERSONS'</summary>
	TCHAR szFIRST_NAME[32];
	/// <summary>���������� ��������� ���������� �� ������ 'SECOND_NAME' � ���������  'PERSONS'</summary>
	char szSECOND_NAME[32];
	/// <summary>���������� ��������� ���������� �� �������� 'LAST_NAME' � ���������  'PERSONS'</summary>
	TCHAR szLAST_NAME[32];
	/// <summary>���������� ��������� �������� ���� (�� ������ 'CITY_ID' � ���������  'PERSONS')
	/// <summary>����� ��� ��������� 'CITIES' � ������ 'ID'</summary>
	long lCITY_ID;
	/// <summary>���������� ��������� ���������� �� �������� 'ADDRESS' � ���������  'PERSONS'</summary>
	TCHAR szADDRESS[256];

	PERSONS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

#define PHONE_NUMBER_SIZE	16

/// <summary>
///  ������� ��������� 'PHONE_NUMBERS' ������������� �� ��������� 'PHONE_NUMBERS'
/// </summary>
struct PHONE_NUMBERS {
	/// <summary>���������� ��������� �������� ���� �� �������� 'ID' � ��������� 'PHONE_NUMBERS'</summary>
	long lID;
	/// <summary>?</summary>
	long lUPDATE_COUNTER;
	/// <summary>���������� ��������� �������� ���� (�� ������ 'PHONE_TYPE_ID' � ���������  'PHONE_TYPES')
	/// <summary>����� ��� �������� 'ID' � ��������� 'PHONE_NUMBERS'</summary>;
	long lPHONE_TYPE_ID;
	/// <summary>���������� ��������� ���������� �� �������� 'PHONE_NUMBER' � ���������  'PHONE_NUMBERS'</summary>
	TCHAR szPHONE_NUMBER[16];

	PHONE_NUMBERS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

#define PHONE_TYPE_SIZE	16
/// <summary>
///  ������� ��������� PHONE_TYPES ������������� �� ��������� 'PHONE_TYPES'
/// </summary>
struct PHONE_TYPES {
	/// <summary>���������� ��������� �������� ���� �� �������� 'ID' � ��������� 'PHONE_TYPES'</summary>
	long lID;
	/// <summary>?</summary>
	long lUPDATE_COUNTER;
	/// <summary>���������� ��������� ���������� �� �������� 'PHONE_TYPE' � ���������  'PHONE_TYPES'</summary>
	TCHAR szPHONE_TYPE[16];
	PHONE_TYPES()
	{
		SecureZeroMemory(this, sizeof(*this));
	};
};

// <summary>type-def ����������� CTypedPtrArray ����� �������� CPtrArray ��������� � ��������� PHONE_TYPES< / summary >
typedef CTypedPtrArray < CPtrArray, PHONE_TYPES*> CPhoneTypesArray;

// <summary>type-def ����������� CTypedPtrArray ����� �������� CPtrArray ��������� � ��������� CITIES< / summary >
typedef CTypedPtrArray < CPtrArray, CITIES*> CCitiesArray;


// <summary>type-def ����������� CTypedPtrArray ����� �������� CPtrArray ��������� � ��������� PERSONS< / summary >
typedef CTypedPtrArray < CPtrArray, PERSONS*> CPersonsArray;

// <summary>type-def ����������� CTypedPtrArray ����� �������� CPtrArray ��������� � ��������� PHONE_NUMBERS< / summary >
typedef CTypedPtrArray < CPtrArray, PHONE_NUMBERS*> CPhoneNumbersArray;