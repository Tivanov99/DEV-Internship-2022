#pragma once
#include <afxtempl.h>
#include "GlobalConstants.h"
#include "CSelfClearingTypedPtrArray.h"

/// <summary>
///  Дискова структура CITIES предназначена за таблицата 'CITIES'
/// </summary>

struct CITIES
{
	/// <summary>Променлива съдържаща първичен ключ от колоната 'ID' в таблицата 'CITIES'</summary>
	
	long lID;

	/// <summary>Променлива съдържаща текущата версия на запис.</summary>
	long lUpdateCounter;
	/// <summary>Променлива съдържаща стойността от колона 'CITY_NAME' в таблицата 'CITIES'</summary>
	TCHAR szCITY_NAME[GlobalConstants::_nCityNameSize];
	/// <summary>Променлива съдържаща стойността от колона 'AREA_NAME' в таблицата 'CITIES'</summary>
	TCHAR szAREA_NAME[GlobalConstants::_nCityAreaNameSize];
	/// <summary>Променлива съдържаща стойността от колона 'POSTAL_CODE' в таблицата 'CITIES'</summary>
	long lPOSTAL_CODE;

	~CITIES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};


/// <summary>
///  Дискова структура PERSONS предназначена за таблицата 'PERSONS'
/// </summary>
struct PERSONS {
	/// <summary>Променлива съдържаща първичен ключ от колоната 'ID' в таблицата 'PERSONS'</summary>
	long lID;
	/// <summary>?</summary>
	long lUpdateCounter;
	/// <summary>Променлива съдържаща стойността от колона 'FIRST_NAME' в таблицата  'PERSONS'.</summary>
	TCHAR szFIRST_NAME[GlobalConstants::_nPersonFirstNameSize];
	/// <summary>Променлива съдържаща стойността от колона 'SECOND_NAME' в таблицата  'PERSONS'.</summary>
	TCHAR szSECOND_NAME[GlobalConstants::_nPersonSecondNameSize];
	/// <summary>Променлива съдържаща стойността от колоната 'LAST_NAME' в таблицата  'PERSONS'.</summary>
	TCHAR szLAST_NAME[GlobalConstants::_nPersonLastNameSize];
	/// <summary>Променлива съдържаща стойността от колоната UCN в таблицата  'PERSONS'.</summary>
	TCHAR szUCN[GlobalConstants::_nPersonUcnSize];
	/// <summary>Променлива съдържаща вторичен ключ (от колона 'CITY_ID' в таблицата  'PERSONS').
	/// <summary>сочещ към таблицата 'CITIES' и колона 'ID'.</summary>
	long lCITY_ID;
	/// <summary>Променлива съдържаща стойността от колоната 'ADDRESS' в таблицата  'PERSONS'.</summary>
	TCHAR szADDRESS[GlobalConstants::_nPersonAddressSize];

	~PERSONS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

/// <summary>
///  Дискова структура 'PHONE_NUMBERS' предназначена за таблицата 'PHONE_NUMBERS'
/// </summary>
struct PHONE_NUMBERS {
	/// <summary>Променлива съдържаща първичен ключ от колоната 'ID' в таблицата 'PHONE_NUMBERS'</summary>
	long lID;

	/// <summary>?</summary>
	long lUpdateCounter;

	/// <summary>
		/// Променлива съдържаща вторичен ключ сочещ към колоната 'ID' в таблицата 'PERSONS'</summary>;
	/// </summary>
	long lPERSON_ID;

	/// <summary>
		/// Променлива съдържаща вторичен ключ (от колона 'PHONE_TYPE_ID' в таблицата 'PHONE_TYPES')
		/// сочещ към колоната 'ID' в таблицата 'PHONE_NUMBERS'</summary>;
	/// </summary>
	long lPHONE_TYPE_ID;

	/// <summary>Променлива съдържаща стойността от колоната 'PHONE_NUMBER' в таблицата  'PHONE_NUMBERS'</summary>
	TCHAR szPHONE_NUMBER[GlobalConstants::_nPhoneNumberSize];

	~PHONE_NUMBERS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

#define PHONE_TYPE_SIZE	16
/// <summary>
///  Дискова структура PHONE_TYPES предназначена за таблицата 'PHONE_TYPES'
/// </summary>
struct PHONE_TYPES {
	/// <summary>Променлива съдържаща първичен ключ от колоната 'ID' в таблицата 'PHONE_TYPES'</summary>
	long lID;
	/// <summary>?</summary>
	long lUpdateCounter;
	/// <summary>Променлива съдържаща стойността от колоната 'PHONE_TYPE' в таблицата  'PHONE_TYPES'</summary>
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