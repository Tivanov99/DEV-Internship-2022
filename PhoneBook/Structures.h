#pragma once
#include <afxtempl.h>



#define CITY_NAME_SIZE	32
#define AREA_NAME_SIZE	32

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
	TCHAR szCITY_NAME[CITY_NAME_SIZE];
	/// <summary>Променлива съдържаща стойността от колона 'AREA_NAME' в таблицата 'CITIES'</summary>
	TCHAR szAREA_NAME[AREA_NAME_SIZE];
	/// <summary>Променлива съдържаща стойността от колона 'POSTAL_CODE' в таблицата 'CITIES'</summary>
	long lPOSTAL_CODE;

	~CITIES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

#define FIRST_NAME_SIZE		32
#define SECOND_NAME_SIZE	32
#define LAST_NAME_SIZE		32
#define ADDRESS_SIZE		256

/// <summary>
///  Дискова структура PERSONS предназначена за таблицата 'PERSONS'
/// </summary>
struct PERSONS {
	/// <summary>Променлива съдържаща първичен ключ от колоната 'ID' в таблицата 'PERSONS'</summary>
	long lID;
	/// <summary>?</summary>
	long lUpdateCounter;
	/// <summary>Променлива съдържаща стойността от колона 'FIRST_NAME' в таблицата  'PERSONS'</summary>
	TCHAR szFIRST_NAME[FIRST_NAME_SIZE];
	/// <summary>Променлива съдържаща стойността от колона 'SECOND_NAME' в таблицата  'PERSONS'</summary>
	char szSECOND_NAME[SECOND_NAME_SIZE];
	/// <summary>Променлива съдържаща стойността от колоната 'LAST_NAME' в таблицата  'PERSONS'</summary>
	TCHAR szLAST_NAME[LAST_NAME_SIZE];
	/// <summary>Променлива съдържаща вторичен ключ (от колона 'CITY_ID' в таблицата  'PERSONS')
	/// <summary>сочещ към таблицата 'CITIES' и колона 'ID'</summary>
	long lCITY_ID;
	/// <summary>Променлива съдържаща стойността от колоната 'ADDRESS' в таблицата  'PERSONS'</summary>
	TCHAR szADDRESS[ADDRESS_SIZE];

	PERSONS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

#define PHONE_NUMBER_SIZE	16

/// <summary>
///  Дискова структура 'PHONE_NUMBERS' предназначена за таблицата 'PHONE_NUMBERS'
/// </summary>
struct PHONE_NUMBERS {
	/// <summary>Променлива съдържаща първичен ключ от колоната 'ID' в таблицата 'PHONE_NUMBERS'</summary>
	long lID;
	/// <summary>?</summary>
	long lUpdateCounter;
	/// <summary>
		/// Променлива съдържаща вторичен ключ (от колона 'PHONE_TYPE_ID' в таблицата 'PHONE_TYPES')
		/// сочещ към колоната 'ID' в таблицата 'PHONE_NUMBERS'</summary>;
	/// </summary>
	long lPHONE_TYPE_ID;
	/// <summary>Променлива съдържаща стойността от колоната 'PHONE_NUMBER' в таблицата  'PHONE_NUMBERS'</summary>
	TCHAR szPHONE_NUMBER[PHONE_NUMBER_SIZE];

	PHONE_NUMBERS()
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
	PHONE_TYPES()
	{
		SecureZeroMemory(this, sizeof(*this));
	};
};

//typedef CSelfClearingTypedPtrArray<CITIES> CCitiesArray;
enum ContextMenuOperations
{
	Edit,
	Delete,
	Create
};

