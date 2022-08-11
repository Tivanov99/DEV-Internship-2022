#pragma once
#include "PersonsDocument.h"


class CPersonsView :public CListView
{
protected: // create from serialization only
	CPersonsView() noexcept;
	DECLARE_DYNCREATE(CPersonsView)

	// Attributes
public:
	/// <summary>Връща документ чрез който се достъпват информацията от базата данни.</summary>
	CPersonsDocument* GetDocument() const;

	//Methods
private:
	/// <summary>Фунцкия която определя коя опция от контекстното меню може да бъде използвана при клик на десен бутон.</summary>
	void ManageContextMenuItems(CCmdUI* pCmdUI);
	/// <summary>Функция която попълва цялата информация за хората.</summary>
	void FillView();
	/// <summary>Метод добавящ всички колони към подадена като аргумент лист контрола.</summary>
	void AddColumns();
	/// <summary>Връща указател записан в 'item data' при добавянето на записа в CListCtrl.</summary>
	PERSONS* GetSelectedRecordItemData();
	/// <summary>Според това къде потребител е кликнал връща номер на ред (-1 когато не е кликнато на нито един от запситие,и освен това извежда и предупредително съобщение, в  противен случай номер на ред).</summary>
	const int GetSelectedRowNumber();
	/// <summary>Добавя нов запис към лист контролата.</summary>
	/// <param name="pPerson">Пойнтър представляващ нов запис</param>
	void InsertNewRecordToCListCtrl(PERSONS* pPerson);

	void UpdateRecord(long lID);
	/// <summary>Конфигурира всичко нужно за държанието и изгледа на лист контролата.</summary>
	void ConfigurateCListCtrl();
	
	// Overrides
	//----------------
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;
protected:
	/// <summary>Метод подготвящ всично нужно по CListCtrl при стартирането на програмата.</summary>
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CPersonsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	// Generated message map functions
protected:
	/// <summary>Функция която се грижи за визуализирането на контекстното меню.</summary>
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	/// <summary>Изтрива посочен запис при десен клик върху запис във view-то и 'Delete' от контекстното меню.</summary>
	afx_msg void OnContextMenuDelete();
	/// <summary>При десен клик върху запис извиква диалогов прозорец попълнен с неговите данни.</summary>
	afx_msg void OnEditContextReadData();
	/// <summary>При десен клик без значение къде е извършен той и 'InsertRecord' от контекстното меню извиква диалогов прозорец в който да бъдат попълнени данните на записа.</summary>
	afx_msg void OnContextMenuInsert();
	/// <summary>При десен клик върху запис извиква диалогов прозорец попълнен с неговите данни даващ възможност за редакция.</summary>
	afx_msg void OnContextMenuEdit();
};
