#pragma once
#include "CCitiesTable.h"

class CCitiesData
{
	// Constructor / Destructor
	// ----------------
public:
	CCitiesData();
	~CCitiesData();

	// Methods
	// ----------------

	/// <summary>
	///  Функция която чете всики записи от таблицата "CITIES" и ги добавя в подаден като аргумент масив.
	/// </summary>
	/// <param name="oCitiesArray">Масив в който ще бъдат записани всички прочетени данни.</param>
	bool SelectAll(CCitiesArray& oCitiesArray);

	/// <summary>
	///  Функция която чете запис от таблицата "CITIES" чието ID отговаря на "lID" и го презаписва в "recCities" аргумента.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	/// <param name="recCities">Референция която ще присвои резултата от функцията</param>
	bool SelectWhereID(const long lID, CITIES& recCities);

	/// <summary>
	///  Функция която прави промяна на запис от таблицата "CITIES" чието ID отговаря на "lID" аргумента,
	///  и ще приложи промените от аргумента "recCities" в записа извлечен от базата.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	/// <param name="recCities">Референция която съдържа вече променените данни.</param>
	bool UpdateWhereID(const long lID, const CITIES& recCities);

	/// <summary>
	///  Функция която добавя запис подаден като аргумент към таблицата "CITIES".
	/// </summary>
	/// <param name="recCities">Референция която съдържа нов обект.</param>
	bool InsertRecord(const CITIES& recCities);

	/// <summary>
	///  Функция която изтрива запис от таблицата "CITIES" който отговавя на "lID" аргумента.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	bool DeleteWhereID(const long lID);

private:
	/// <summary>
	/// Мембър за достъп до класът съдържащ бизнес логиката.
	/// </summary>
	CCitiesTable m_CitiesTable;

	/// <summary>
	/// Мембър съдържащ сесията.
	/// </summary>
	CSession m_oSession;
};

