#pragma once
#include "Structures.h"
#include "CPersonsTable.h"
#include "CCitiesTable.h"


class CPersonsData 
{
	// Constructor / Destructor
	// ----------------
public:
	// Methods
	// ----------------
	CPersonsData();
	~CPersonsData();

	/// <summary>
	///  Функция която чете всики записи от таблицата "CITIES" и ги добавя в подаден като аргумент масив.
	/// </summary>
	/// <param name="oCitiesArray">Масив в който ще бъдат записани всички прочетени данни.</param>
	bool SelectAllCities(CCitiesArray& oCitiesArray);

	/// <summary>
	///  Функция която чете всики записи от таблицата "PERSONS" и ги добавя в подаден като аргумент масив.
	/// </summary>
	/// <param name="oPersonsArray">Масив в който ще бъдат записани всички прочетени данни.</param>
	bool SelectAll(CPersonsArray& oPersonsArray);

	/// <summary>
	///  Функция която чете запис от таблицата "PERSONS" чието ID отговаря на "lID" и го презаписва в "recPersons" аргумента.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	/// <param name="recPersons">Референция която ще присвои резултата от функцията</param>
	bool SelectWhereID(const long lID, PERSONS& recPersons);

	/// <summary>
	///  Функция която прави промяна на запис от таблицата "PERSONS" чието ID отговаря на "lID" аргумента,
	///  и ще приложи промените от аргумента "recPersons" в записа извлечен от базата.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	/// <param name="recCities">Референция която съдържа вече променените данни.</param>
	bool UpdateWhereID(const long lID, const PERSONS& recPersons);

	/// <summary>
	///  Функция която добавя запис подаден като аргумент към таблицата "PERSONS".
	/// </summary>
	/// <param name="recPersons">Референция която съдържа нов обект.</param>
	bool Insert(const PERSONS& recPersons);

	/// <summary>
	///  Функция която изтрива запис от таблицата "PERSONS" който отговавя на "lID" аргумента.
	/// </summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси запис в базата.</param>
	bool DeleteWhereID(const long lID);
private:
	/// <summary>
	/// Мембър за достъп до класът съдържащ бизнес логиката.
	/// </summary>
	CPersonsTable m_oPersonsTable;

	CCitiesTable m_oCitiesTable;
};

