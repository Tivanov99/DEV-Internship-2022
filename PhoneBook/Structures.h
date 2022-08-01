#pragma once
#include <afxtempl.h>
#include "GlobalConstants.h"
#include "CSelfClearingTypedPtrArray.h"

/// <summary>
///  ������� ��������� CITIES ������������� �� ��������� 'CITIES'
/// </summary>

struct CITIES
{
	/// <summary>���������� ��������� �������� ���� �� �������� 'ID' � ��������� 'CITIES'</summary>
	
	long lID;

	/// <summary>���������� ��������� �������� ������ �� �����.</summary>
	long lUpdateCounter;
	/// <summary>���������� ��������� ���������� �� ������ 'CITY_NAME' � ��������� 'CITIES'</summary>
	TCHAR szCITY_NAME[GlobalConstants::_nCityNameSize];
	/// <summary>���������� ��������� ���������� �� ������ 'AREA_NAME' � ��������� 'CITIES'</summary>
	TCHAR szAREA_NAME[GlobalConstants::_nCityAreaNameSize];
	/// <summary>���������� ��������� ���������� �� ������ 'POSTAL_CODE' � ��������� 'CITIES'</summary>
	long lPOSTAL_CODE;

	~CITIES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};


/// <summary>
///  ������� ��������� PERSONS ������������� �� ��������� 'PERSONS'
/// </summary>
struct PERSONS {
	/// <summary>���������� ��������� �������� ���� �� �������� 'ID' � ��������� 'PERSONS'</summary>
	long lID;
	/// <summary>?</summary>
	long lUpdateCounter;
	/// <summary>���������� ��������� ���������� �� ������ 'FIRST_NAME' � ���������  'PERSONS'.</summary>
	TCHAR szFIRST_NAME[GlobalConstants::_nPersonFirstNameSize];
	/// <summary>���������� ��������� ���������� �� ������ 'SECOND_NAME' � ���������  'PERSONS'.</summary>
	TCHAR szSECOND_NAME[GlobalConstants::_nPersonSecondNameSize];
	/// <summary>���������� ��������� ���������� �� �������� 'LAST_NAME' � ���������  'PERSONS'.</summary>
	TCHAR szLAST_NAME[GlobalConstants::_nPersonLastNameSize];
	/// <summary>���������� ��������� ���������� �� �������� UCN � ���������  'PERSONS'.</summary>
	TCHAR szUCN[GlobalConstants::_nPersonUcnSize];
	/// <summary>���������� ��������� �������� ���� (�� ������ 'CITY_ID' � ���������  'PERSONS').
	/// <summary>����� ��� ��������� 'CITIES' � ������ 'ID'.</summary>
	long lCITY_ID;
	/// <summary>���������� ��������� ���������� �� �������� 'ADDRESS' � ���������  'PERSONS'.</summary>
	TCHAR szADDRESS[GlobalConstants::_nPersonAddressSize];

	~PERSONS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

/// <summary>
///  ������� ��������� 'PHONE_NUMBERS' ������������� �� ��������� 'PHONE_NUMBERS'
/// </summary>
struct PHONE_NUMBERS {
	/// <summary>���������� ��������� �������� ���� �� �������� 'ID' � ��������� 'PHONE_NUMBERS'</summary>
	long lID;

	/// <summary>?</summary>
	long lUpdateCounter;

	/// <summary>
		/// ���������� ��������� �������� ���� ����� ��� �������� 'ID' � ��������� 'PERSONS'</summary>;
	/// </summary>
	long lPERSON_ID;

	/// <summary>
		/// ���������� ��������� �������� ���� (�� ������ 'PHONE_TYPE_ID' � ��������� 'PHONE_TYPES')
		/// ����� ��� �������� 'ID' � ��������� 'PHONE_NUMBERS'</summary>;
	/// </summary>
	long lPHONE_TYPE_ID;

	/// <summary>���������� ��������� ���������� �� �������� 'PHONE_NUMBER' � ���������  'PHONE_NUMBERS'</summary>
	TCHAR szPHONE_NUMBER[GlobalConstants::_nPhoneNumberSize];

	~PHONE_NUMBERS()
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
	long lUpdateCounter;
	/// <summary>���������� ��������� ���������� �� �������� 'PHONE_TYPE' � ���������  'PHONE_TYPES'</summary>
	TCHAR szPHONE_TYPE[PHONE_TYPE_SIZE];
	~PHONE_TYPES()
	{
		SecureZeroMemory(this, sizeof(*this));
	};
};

typedef CSelfClearingTypedPtrArray<CITIES> CCitiesArray;
typedef CSelfClearingTypedPtrArray<PERSONS> CPersonsArray;
typedef CSelfClearingTypedPtrArray<PHONE_NUMBERS> CPhoneNumbersArray;
typedef CSelfClearingTypedPtrArray<PHONE_TYPES> CPhoneTypesArray;