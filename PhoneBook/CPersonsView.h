#pragma once
#include "CPersonsDocument.h"

class CPersonsView :public CListView
{
protected: // create from serialization only
	CPersonsView() noexcept;
	DECLARE_DYNCREATE(CPersonsView)

	// Attributes
public:
	/// <summary>
	/// Връща документ чрез който се достъпват информацията от базата данни.
	/// </summary>
	/// <returns>Указател на документа.</returns>
	CPersonsDocument* GetDocument() const;

	//Methods
public:
	/// <summary>
	/// Функция която попълва цялата информация за градовете.
	/// </summary>
	/// <param name="LSCCitiesList">Лист контрола в която ще се попълват данните.</param>
	/// <param name="oPersonsArray">Масив съдържащ всички записи за градовете прочетени от базата.</param>
	void FillView(CListCtrl& LSCCitiesList, const CSelfClearingTypedPtrArray<PERSONS>& oPersonsArray);

	/// <summary>
	/// Метод добавящ всички колони към подадена като аргумент лист контрола.
	/// </summary>
	/// <param name="LSCCitiesList">Лист контрола към която ще бъдат добавени колините.</param>
	void AddColumns(CListCtrl& LSCCitiesList);

};

