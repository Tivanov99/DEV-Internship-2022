#pragma once
#include <afxtempl.h>
#include "GlobalConstants.h"
#include "CSelfClearingTypedPtrArray.h"
#include "CSelfClearingMap.h"

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
	TCHAR szCityName[GlobalConstants::_nCityNameSize];
	/// <summary>���������� ��������� ���������� �� ������ 'AREA_NAME' � ��������� 'CITIES'</summary>
	TCHAR szAreaName[GlobalConstants::_nCityAreaNameSize];
	/// <summary>���������� ��������� ���������� �� ������ 'POSTAL_CODE' � ��������� 'CITIES'</summary>
	long lPostalCode;

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
	long lID;
	/// <summary>?</summary>
	long lUpdateCounter;
	/// <summary>���������� ��������� ���������� �� ������ 'FIRST_NAME' � ���������  'PERSONS'.</summary>
	TCHAR szFirstName[GlobalConstants::_nPersonFirstNameSize];
	/// <summary>���������� ��������� ���������� �� ������ 'SECOND_NAME' � ���������  'PERSONS'.</summary>
	TCHAR szSecondName[GlobalConstants::_nPersonSecondNameSize];
	/// <summary>���������� ��������� ���������� �� �������� 'LAST_NAME' � ���������  'PERSONS'.</summary>
	TCHAR szLastName[GlobalConstants::_nPersonLastNameSize];
	/// <summary>���������� ��������� ���������� �� �������� UCN � ���������  'PERSONS'.</summary>
	TCHAR szUcn[GlobalConstants::_nPersonUcnSize];
	/// <summary>���������� ��������� �������� ���� (�� ������ 'CITY_ID' � ���������  'PERSONS').
	/// <summary>����� ��� ��������� 'CITIES' � ������ 'ID'.</summary>
	long lCityId;
	/// <summary>���������� ��������� ���������� �� �������� 'ADDRESS' � ���������  'PERSONS'.</summary>
	TCHAR szAddress[GlobalConstants::_nPersonAddressSize];

	PERSONS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

/// <summary>
///  ������� ��������� 'PHONE_NUMBERS' ������������� �� ��������� 'PHONE_NUMBERS'
/// </summary>
struct PHONE_NUMBERS 
{
	/// <summary>���������� ��������� �������� ���� �� �������� 'ID' � ��������� 'PHONE_NUMBERS'</summary>
	long lID;
	/// <summary>?</summary>
	long lUpdateCounter;
	/// <summary>
		/// ���������� ��������� �������� ���� ����� ��� �������� 'ID' � ��������� 'PERSONS'</summary>;
	/// </summary>
	long lPersonId;
	/// <summary>
		/// ���������� ��������� �������� ���� (�� ������ 'PHONE_TYPE_ID' � ��������� 'PHONE_TYPES')
		/// ����� ��� �������� 'ID' � ��������� 'PHONE_NUMBERS'</summary>;
	/// </summary>
	long lPhoneTypeId;

	/// <summary>���������� ��������� ���������� �� �������� 'PHONE_NUMBER' � ���������  'PHONE_NUMBERS'</summary>
	TCHAR szPhoneNumber[GlobalConstants::_nPhoneNumberSize];

	PHONE_NUMBERS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

#define PHONE_TYPE_SIZE	16
/// <summary>������� ��������� PHONE_TYPES ������������� �� ��������� 'PHONE_TYPES'</summary>
struct PHONE_TYPES {
	/// <summary>���������� ��������� �������� ���� �� �������� 'ID' � ��������� 'PHONE_TYPES'</summary>
	long lID;
	/// <summary>?</summary>
	long lUpdateCounter;
	/// <summary>���������� ��������� ���������� �� �������� 'PHONE_TYPE' � ���������  'PHONE_TYPES'</summary>
	TCHAR szPhoneType[PHONE_TYPE_SIZE];

	PHONE_TYPES()
	{
		SecureZeroMemory(this, sizeof(*this));
	};
};

typedef CSelfClearingTypedPtrArray<CITIES> CCitiesArray;
typedef CSelfClearingTypedPtrArray<PERSONS> CPersonsArray;
typedef CSelfClearingTypedPtrArray<PHONE_NUMBERS> CPhoneNumbersArray;
typedef CSelfClearingTypedPtrArray<PHONE_TYPES> CPhoneTypesArray;

typedef CSelfClearingMap<long, PHONE_NUMBERS*> CPhoneNumbersMap;
typedef CSelfClearingMap<long, PHONE_TYPES*> CPhoneTypesMap;
typedef CSelfClearingMap<long, CITIES*> CCitiesMap;
typedef CSelfClearingMap<long, PERSONS*> CPersonsMap;
