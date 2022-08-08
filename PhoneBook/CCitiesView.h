
// CitiesView.h : interface of the CCitiesView class
//

#pragma once
#include "CCitiesDocument.h"


class CCitiesView : public CListView
{
protected: // create from serialization only
	CCitiesView() noexcept;
	DECLARE_DYNCREATE(CCitiesView)

	// Attributes
public:
	/// <summary>
	/// Връща документ чрез който се достъпва информацията от базата данни.
	/// </summary>
	/// <returns>Указател на документа.</returns>
	CCitiesDocument* GetDocument() const;

	//Methods
private:
	/// <summary>
	/// Функция която попълва цялата информация за градовете.
	/// </summary>
	/// <param name="оListCtrl">Лист контрола в която ще се попълват данните.</param>
	/// <param name="oCitiesArray">Масив съдържащ всички записи за градовете прочетени от базата.</param>
	void FillView();

	/// <summary>
	/// Метод добавящ всички колони към подадена като аргумент лист контрола.
	/// </summary>
	/// <param name="оListCtrl">Лист контрола към която ще бъдат добавени колините.</param>
	void AddColumns(CListCtrl& оListCtrl);

	/// <summary>
	/// Връща указател записан в 'item data' при добавянето на записа в CListCtrl.
	/// </summary>
	/// <returns></returns>
	CITIES* GetSelectedRecordItemData();

	/// <summary>
	/// Според това къде потребител е кликнал връща номер на ред (-1 когато не е кликнато на нито един от запситие,и освен това извежда и предупредително съобщение, в  противен случай номер на ред).
	/// </summary>
	/// <returns>Номер на ред в диапазона -1 до N</returns>
	const int GetSelectedRowNumber();

	/// <summary>
	/// Добавя нов запис към лист контролата.
	/// </summary>
	/// <param name="pCity">Пойнтър представляващ нов запис</param>
	void InsertNewRecordToCListCtrl(CITIES* pCity);

	/// <summary>
	/// Конфигурира всичко нужно за държанието и изгледа на лист контролата.
	/// </summary>
	void ConfigurateCListCtrl();

	/// <summary>
	/// Подменя старите стойности с нови на запис който е бил редактиран.
	/// </summary>
	/// <param name="pCity">Референция която сърържа новите стойности.</param>
	void UpdateRecord(CITIES& pCity);
	// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;

protected:
	/// <summary>
	/// Метод подготвящ всично нужно по CListCtrl при стартирането на програмата.
	/// </summary>
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CCitiesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

private:
	/// <summary>
	///Изтрива посочен запис при десен клик върху запис във view-то и 'Delete' от контекстното меню.
	/// </summary>
	afx_msg void OnContextMenuDelete();

	/// <summary>
	/// При десен клик върху запис извиква диалогов прозорец попълнен с неговите данни даващ възможност за редакция.
	/// </summary>
	afx_msg void OnContextMenuEdit();

	/// <summary>
	/// При десен клик без значение къде е извършен той и 'InsertRecord' от контекстното меню извиква диалогов прозорец в който да бъдат попълнени данните на записа.
	/// </summary>
	afx_msg void OnContextMenuInsert();

	/// <summary>
	/// При десен клик върху запис извиква диалогов прозорец попълнен с неговите данни.
	/// </summary>
	afx_msg void OnEditContextReadData();
};

#ifndef _DEBUG  // debug version in CitiesView.cpp
inline CCitiesDocument* CCitiesView::GetDocument() const
{
	return reinterpret_cast<CCitiesDocument*>(m_pDocument);
}
#endif

