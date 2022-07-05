#pragma once
#include <WinBase.h>
#include <string>

/// <summary>
///  Дискова структура CITIES предназначена за таблицата 'CITIES'
/// </summary>
struct CITIES 
{
	/// <summary>Променлива съдържаща първичен ключ от колоната 'ID' в таблицата 'CITIES'</summary>
	int nID;
	/// <summary>?</summary>
	int nUPDATE_COUNTER;
	/// <summary>Променлива съдържаща стойността от колона 'CITY_NAME' в таблицата 'CITIES'</summary>
	char  szCITY_NAME[32];
	/// <summary>Променлива съдържаща стойността от колона 'AREA_NAME' в таблицата 'CITIES'</summary>
	char szAREA_NAME[32];
	/// <summary>Променлива съдържаща стойността от колона 'POSTAL_CODE' в таблицата 'CITIES'</summary>
	int sznPOSTAL_CODE;

	CITIES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

/// <summary>
///  Дискова структура PERSONS предназначена за таблицата 'PERSONS'
/// </summary>
struct PERSONS {
	/// <summary>Променлива съдържаща първичен ключ от колоната 'ID' в таблицата 'PERSONS'</summary>
	int nID;
	/// <summary>?</summary>
	int nUPDATE_COUNTER;
	/// <summary>Променлива съдържаща стойността от колона 'FIRST_NAME' в таблицата  'PERSONS'</summary>
	char szFIRST_NAME[32];
	/// <summary>Променлива съдържаща стойността от колона 'SECOND_NAME' в таблицата  'PERSONS'</summary>
	char szSECOND_NAME[32];
	/// <summary>Променлива съдържаща стойността от колоната 'LAST_NAME' в таблицата  'PERSONS'</summary>
	char szLAST_NAME[32];
	/// <summary>Променлива съдържаща вторичен ключ (от колона 'CITY_ID' в таблицата  'PERSONS')
	/// <summary>сочещ към таблицата 'CITIES' и колона 'ID'</summary>
	int nCITY_ID;
	/// <summary>Променлива съдържаща стойността от колоната 'ADDRESS' в таблицата  'PERSONS'</summary>
	char szADDRESS[256];

	PERSONS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

/// <summary>
///  Дискова структура 'PHONE_NUMBERS' предназначена за таблицата 'PHONE_NUMBERS'
/// </summary>
struct PHONE_NUMBERS {
	/// <summary>Променлива съдържаща първичен ключ от колоната 'ID' в таблицата 'PHONE_NUMBERS'</summary>
	int nID;
	/// <summary>?</summary>
	int nUPDATE_COUNTER;
	/// <summary>Променлива съдържаща вторичен ключ (от колона 'PHONE_TYPE_ID' в таблицата  'PHONE_TYPES')
	/// <summary>сочещ към колоната 'ID' в таблицата 'PHONE_NUMBERS'</summary>;
	int nPHONE_TYPE_ID;
	/// <summary>Променлива съдържаща стойността от колоната 'PHONE_NUMBER' в таблицата  'PHONE_NUMBERS'</summary>
	char szPHONE_NUMBER[16];

	PHONE_NUMBERS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

/// <summary>
///  Дискова структура PHONE_TYPES предназначена за таблицата 'PHONE_TYPES'
/// </summary>
struct PHONE_TYPES {
	/// <summary>Променлива съдържаща първичен ключ от колоната 'ID' в таблицата 'PHONE_TYPES'</summary>
	int ID;
	/// <summary>?</summary>
	int UPDATE_COUNTER;
	/// <summary>Променлива съдържаща стойността от колоната 'PHONE_TYPE' в таблицата  'PHONE_TYPES'</summary>
	char szPHONE_TYPE[16];
	PHONE_TYPES()
	{
		SecureZeroMemory(this, sizeof(*this));
	};
};

typedef CTypedPtrArray < CPtrArray, PHONE_TYPES*> CPhoneTypesArray;

typedef CTypedPtrArray < CPtrArray, CITIES*> CCitiesArray;

typedef CTypedPtrArray < CPtrArray, PERSONS*> CPersonsArray;

typedef CTypedPtrArray < CPtrArray, PHONE_NUMBERS*> CPhoneNumbersArray;