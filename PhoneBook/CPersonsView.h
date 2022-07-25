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
};

