#pragma once
#include "Structures.h"
#include "DbConnector.h"

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
	/// <summary>
	///  Функция която чете всики записи от таблицата "PHONE_NUMBERS" и ги добавя в подаден като аргумент масив.
	/// </summary>
	/// <param name="oPhoneNumbersArray">Масив в който ще бъдат записани всички прочетени данни.</param>
	bool SelectAll(CPhoneNumbersArray& oPhoneNumbersArray);

	/// <summary>
	///  Функция която чете запис от таблицата "PHONE_NUMBERS" чието ID отговаря на "lID" и го презаписва в "recPhoneNumbers" аргумента.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	/// <param name="recPhoneNumbers">Референция която ще присвои резултата от функцията</param>
	bool SelectWhereID(const long lID, PHONE_NUMBERS& recPhoneNumbers);

	/// <summary>
	///  Функция която прави промяна на запис от таблицата "PHONE_NUMBERS" чието ID отговаря на "lID" аргумента,
	///  и ще приложи промените от аргумента "recPhoneNumbers" в записа извлечен от базата.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	/// <param name="recPhoneNumbers">Референция която съдържа вече променените данни.</param>
	bool UpdateWhereID(const long lID, const PHONE_NUMBERS& recPhoneNumbers);

	/// <summary>
	///  Функция която добавя запис подаден като аргумент към таблицата "PHONE_NUMBERS".
	/// </summary>
	/// <param name="recPhoneNumbers">Референция която съдържа нов обект.</param>
	bool InsertRecord(const PHONE_NUMBERS& recPhoneNumbers);

	/// <summary>
	///  Функция която изтрива запис от таблицата "CITIES" който отговавя на "lID" аргумента.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	bool DeleteWhereID(const long lID);

	// Members
	// ----------------
private:
	/// <summary>
	/// Мембър за достъп до класът съдържащ бизнес логиката.
	/// </summary>
	DbConnector m_oDbConnector;
};

