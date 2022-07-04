#pragma once
#pragma once
#include <WinBase.h>
#include <string>
#include <atldbcli.h>
#include <iostream>
#include <afx.h>
using namespace std;

/// <summary>
///  Дискова структура CITIES предназначена за таблицата 'CITIES'
/// </summary>
struct CITIES {
	/// <summary>Променлива съдържаща първичен ключ от колоната 'ID' в таблицата 'CITIES'</summary>
	int nID;
	/// <summary>?</summary>
	int nUPDATE_COUNTER;
	/// <summary>Променлива съдържаща стойността от колона 'CITY_NAME' в таблицата 'CITIES'</summary>
	char  CITY_NAME[32];
	/// <summary>Променлива съдържаща стойността от колона 'AREA_NAME' в таблицата 'CITIES'</summary>
	char AREA_NAME[32];
	/// <summary>Променлива съдържаща стойността от колона 'POSTAL_CODE' в таблицата 'CITIES'</summary>
	int nPOSTAL_CODE;

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
	char FIRST_NAME[32];
	/// <summary>Променлива съдържаща стойността от колона 'SECOND_NAME' в таблицата  'PERSONS'</summary>
	char SECOND_NAME[32];
	/// <summary>Променлива съдържаща стойността от колоната 'LAST_NAME' в таблицата  'PERSONS'</summary>
	char LAST_NAME[32];
	/// <summary>Променлива съдържаща вторичен ключ (от колона 'CITY_ID' в таблицата  'PERSONS')
	/// <summary>сочещ към таблицата 'CITIES' и колона 'ID'</summary>
	int nCITY_ID;
	/// <summary>Променлива съдържаща стойността от колоната 'ADDRESS' в таблицата  'PERSONS'</summary>
	char ADDRESS[256];

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
	char PHONE_NUMBER[16];
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
	char PHONE_TYPE[16];
	PHONE_TYPES()
	{
		SecureZeroMemory(this, sizeof(*this));
	};
};

typedef PHONE_TYPES PhoneType;
typedef CITIES City;
typedef PERSONS Person;
typedef PHONE_NUMBERS PhoneNumber;


typedef CTypedPtrArray < CPtrArray, PhoneType*> CPhoneTypesArray;

typedef CTypedPtrArray < CPtrArray, City*> CCitiesArray;

typedef CTypedPtrArray < CPtrArray, Person*> CPersonsArray;

typedef CTypedPtrArray < CPtrArray, PhoneNumber*> CPhoneNumbersArray;

//ACCESSORS

class CCitiesAccessor
{
protected:
	City m_recCity;

	BEGIN_ACCESSOR_MAP(CCitiesAccessor, 2)
		BEGIN_ACCESSOR(0, true)
		COLUMN_ENTRY(1, m_recCity.nID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(1, true)
		COLUMN_ENTRY(2, m_recCity.nUPDATE_COUNTER)
		COLUMN_ENTRY(3, m_recCity.CITY_NAME)
		COLUMN_ENTRY(4, m_recCity.AREA_NAME)
		COLUMN_ENTRY(5, m_recCity.nPOSTAL_CODE)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};

/// <summary>Клас за работа с таблица CITIES</summary>

class CCitiesTable : private CCommand<CAccessor<CCitiesAccessor>>
{
public:
	BOOL LoadCustomers();
	BOOL UpdateCustomer();
};