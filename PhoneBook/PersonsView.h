#pragma once
#include "CPersonsDocument.h"
class CPersonsView : public CListView
{
protected:
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
	/// Функция която попълва цялата информация за хората.
	/// </summary>
	/// <param name="LSCCitiesList">Лист контрола в която ще се попълват данните.</param>
	/// <param name="oPersonsArray">Масив съдържащ всички записи за градовете прочетени от базата.</param>
	void FillView(CListCtrl& LSCCitiesList, const CSelfClearingTypedPtrArray<PERSONS>& oPersonsArray);

	/// <summary>
	/// Метод добавящ всички колони към подадена като аргумент лист контрола.
	/// </summary>
	/// <param name="LSCCitiesList">Лист контрола към която ще бъдат добавени колините.</param>
	void AddColumns(CListCtrl& LSCCitiesList);
private:
	/// <summary>
	/// Връща указател записан в 'item data' при добавянето на записа в CListCtrl.
	/// </summary>
	/// <returns></returns>
	PERSONS* GetSelectedRecordItemData();

	/// <summary>
	/// Според това къде потребител е кликнал връща номер на ред (-1 когато не е кликнато на нито един от запситие,и освен това извежда и предупредително съобщение, в  противен случай номер на ред).
	/// </summary>
	/// <returns>Номер на ред в диапазона -1 до N</returns>
	const int GetNumberOfSelectedRow();

	/// <summary>
	/// Метод връщащ броя на колоните в CListCtrl.
	/// </summary>
	/// <returns>Цяло число представящо брой на колоните.</returns>
	const int GetColumnCount();

	/// <summary>
	/// Добавя нов запис към лист контролата.
	/// </summary>
	/// <param name="pCity">Пойнтър представляващ нов запис</param>
	void InsertNewItemToCListCtrl(CITIES* pCity);

	/// <summary>
	/// Конфигурира всичко нужно за държанието и изгледа на лист контролата.
	/// </summary>
	void ConfigurateCListCtrl();

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
	virtual ~CPersonsView();
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
};

#ifndef _DEBUG  // debug version in CitiesView.cpp
inline CPersonsDocument* CPersonsView::GetDocument() const
{
	return reinterpret_cast<CPersonsDocument*>(m_pDocument);
}
#endif
