#pragma once
#include "Structures.h"
#include "CPersonsTable.h"
#include "CCitiesTable.h"
#include "DataBaseConnector.h"
#include <map>


class CPersonsData 
{
	// Constructor / Destructor
	// ----------------
public:
	
	CPersonsData();
	~CPersonsData();

	// Methods
	// ----------------
public:
	/// <summary>Функция която чете всики записи от таблицата "PHONE_TYPES" и ги добавя в подаден като аргумент масив.</summary>
	/// <param name="oCitiesArray">Масив в който ще бъдат записани всички прочетени данни.</param>
	bool SelectAllPhoneTypes(CPhoneTypesArray& oPhoneTypesArray);
	/// <summary>Функция която чете всики записи от таблицата "CITIES" и ги добавя в подаден като аргумент масив.</summary>
	/// <param name="oCitiesArray">Масив в който ще бъдат записани всички прочетени данни.</param>
	bool SelectAllCities(CCitiesArray& oCitiesArray);
	/// <summary>Функция която чете всики записи от таблицата "PHONE_NUMBERS" и ги добавя в подаден като аргумент масив.</summary>
	/// <param name="oPhoneNumbersArray">Масив в който ще бъдат записани всички прочетени данни.</param>
	bool SelectAllPhoneNumbersByPersonId(long lPersonID, CPhoneNumbersArray& oPhoneNumbersArray);
	/// <summary>Функция която чете всики записи от таблицата "PERSONS" и ги добавя в подаден като аргумент масив.</summary>
	/// <param name="oPersonsArray">Масив в който ще бъдат записани всички прочетени данни.</param>
	bool SelectAll(CPersonsArray& oPersonsArray);
	/// <summary>Функция която чете запис от таблицата "PERSONS" чието ID отговаря на "lID" и го презаписва в "recPersons" аргумента.</summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	/// <param name="recPersons">Референция която ще присвои резултата от функцията</param>
	bool SelectWhereID(const long lID, PERSONS& recPersons);
	/// <summary>Функция която прави промяна на запис от таблицата "PERSONS" чието ID отговаря на "lID" аргумента,и ще приложи промените от аргумента "recPersons" в записа извлечен от базата.</summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	/// <param name="recCities">Референция която съдържа вече променените данни.</param>
	bool UpdateWhereID(const long lID, const PERSONS& recPersons);
	/// <summary>Функция която добавя запис подаден като аргумент към таблицата "PERSONS".</summary>
	/// <param name="recPersons">Референция която съдържа нов обект.</param>
	bool InsertRecord(PERSONS& recPersons);
	/// <summary>Функция която изтрива запис от таблицата "PERSONS" който отговавя на "lID" аргумента.</summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	bool DeleteWhereID(const long lID);
	/// <summary>Функция която изтрива запис от таблицата 'PERSONS' чието ID отговаря на 'lID', и всички записи от таблицата 'PHONE_NUMBERS' чийто стойност от колоната 'PERSON_ID' са идентични с 'lID'.</summary>
	/// <param name="lID">Уникален идентификатор по който се изтриват записите от базата.</param>
	bool DeletePersonAndPhoneNumbers(const long lID);
	/// <summary>Функция която актуализира запис от таблицата 'PERSONS' чието ID отговаря на 'lPersonID', и всички записи от таблицата 'PHONE_NUMBERS' чийто стойност от колоната 'PERSON_ID' са идентични с 'lPersonID'.</summary>
	/// <param name="recPersons">Запис който съдържа актуалната информация.</param>
	/// <param name="oModifiedPhoneNumbersMap">Колекция съдържаща всички записи на телефонни номера след като е приключена работата с диалоговия прозорец.</param>
	bool UpdatePersonAndPhoneNumbers(const PERSONS& recPersons, CPhoneNumbersArray& oModifiedPhoneNumbersArray);

private:
	/// <summary>Сравнява 2 обекта за разлики между тях.</summary>
	/// <param name="oComparedPhoneNumber">Обект който ще бъде сравняван.</param>
	/// <param name="oPhoneNumberComparator">Обект с който ще се сравнява.</param>
	bool ComparePhoneNumbers(PHONE_NUMBERS& oComparedPhoneNumber, PHONE_NUMBERS& oPhoneNumberComparator);
	/// <summary>Функция която актуализира всички записи.</summary>
	/// <param name="pCurrentOriginalPhoneNumber">Запис който ще бъде проверено дали съществува в 'oModifiedPhoneNumbersArray'.</param>
	/// <param name="oModifiedPhoneNumbersArray">Сисък с вече актуализирани записи.</param>
	bool UpdatePhoneNumbers(PHONE_NUMBERS& pCurrentOriginalPhoneNumber,CPhoneNumbersArray& oModifiedPhoneNumbersArray);

	/// <summary>Функция която добавя записите в от 'oPhoneNumbersArray' в базата.</summary>
	/// <param name="oPhoneNumbersArray">Масив съдържащ всички нови записи.</param>
	bool InsertPhoneNumbers(CPhoneNumbersArray& oPhoneNumbersArray);
};

