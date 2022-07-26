#pragma once
#include "Structures.h"
#include "CSelfClearingTypedPtrArray.h";
#include "CPersonsTable.h"

class CPersonsData 
{
	// Constructor / Destructor
	// ----------------
public:
	CPersonsData();
	~CPersonsData();

	// Methods
	// ----------------

	/// <summary>
	///  Функция която чете всики записи от таблицата "PERSONS" и ги добавя в подаден като аргумент масив.
	/// </summary>
	/// <param name="oPersonsArray">Масив в който ще бъдат записани всички прочетени данни.</param>
	bool SelectAll(CSelfClearingTypedPtrArray<PERSONS>& oPersonsArray);

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
	CPersonsTable m_PersonsTable;
};

