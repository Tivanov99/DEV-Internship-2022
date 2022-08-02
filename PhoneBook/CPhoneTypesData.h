#pragma once
#include "Structures.h"
#include "CPhoneTypesTable.h"
class CPhoneTypesData
{
public:
	CPhoneTypesData();
	~CPhoneTypesData();

	// Methods
	// ----------------

	/// <summary>
	///  Функция която чете всики записи от таблицата "PHONE_TYPES" и ги добавя в подаден като аргумент масив.
	/// </summary>
	/// <param name="oPhoneTyesArray">Масив в който ще бъдат записани всички прочетени данни.</param>
	bool SelectAll(CPhoneTypesArray& oPhoneTyesArray);

	/// <summary>
	///  Функция която чете запис от таблицата "PHONE_TYPES" чието ID отговаря на "lID" и го презаписва в "recPhoneType" аргумента.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	/// <param name="recPhoneType">Референция която ще присвои резултата от функцията</param>
	bool SelectWhereID(const long lID, PHONE_TYPES& recPhoneType);

	/// <summary>
	///  Функция която прави промяна на запис от таблицата "PHONE_TYPES" чието ID отговаря на "lID" аргумента,
	///  и ще приложи промените от аргумента "recPhoneType" в записа извлечен от базата.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	/// <param name="recPhoneType">Референция която съдържа вече променените данни.</param>
	bool UpdateWhereID(const long lID, const PHONE_TYPES& recPhoneType);

	/// <summary>
	///  Функция която добавя запис подаден като аргумент към таблицата "PHONE_TYPES".
	/// </summary>
	/// <param name="recPhoneType">Референция която съдържа нов обект.</param>
	bool InsertRecord(const PHONE_TYPES& recPhoneType);

	/// <summary>
	///  Функция която изтрива запис от таблицата "PHONE_TYPES" който отговавя на "lID" аргумента.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	bool DeleteWhereID(const long lID);

private:
	/// <summary>
	/// Мембър за достъп до класът съдържащ бизнес логиката.
	/// </summary>
	CPhoneTypesTable m_PhoneTypesTable;

	CSession m_oSession;
};

