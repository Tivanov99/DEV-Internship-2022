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
	/// ����� �������� ���� ����� �� ��������� ������������ �� ������ �����.
	/// </summary>
	/// <returns>�������� �� ���������.</returns>
	CPersonsDocument* GetDocument() const;

	//Methods
private:
	/// <summary>
	/// ������� ����� ������� ������ ���������� �� ���������.
	/// </summary>
	/// <param name="LSCCitiesList">���� �������� � ����� �� �� �������� �������.</param>
	/// <param name="oPersonsArray">����� �������� ������ ������ �� ��������� ��������� �� ������.</param>
	void FillView(CListCtrl& LSCCitiesList, const CSelfClearingTypedPtrArray<PERSONS>& oPersonsArray);

	/// <summary>
	/// ����� ������� ������ ������ ��� �������� ���� �������� ���� ��������.
	/// </summary>
	/// <param name="LSCCitiesList">���� �������� ��� ����� �� ����� �������� ��������.</param>
	void AddColumns(CListCtrl& LSCCitiesList);

	/// <summary>
	 /// ����� �������� ������� � 'item data' ��� ���������� �� ������ � CListCtrl.
	 /// </summary>
	 /// <returns></returns>
	PERSONS* GetSelectedRecordItemData();

	/// <summary>
	/// ������ ���� ���� ���������� � ������� ����� ����� �� ��� (-1 ������ �� � �������� �� ���� ���� �� ��������,� ����� ���� ������� � ��������������� ���������, �  �������� ������ ����� �� ���).
	/// </summary>
	/// <returns>����� �� ��� � ��������� -1 �� N</returns>
	const int GetNumberOfSelectedRow();

	/// <summary>
	/// ������ ��� ����� ��� ���� ����������.
	/// </summary>
	/// <param name="pPerson">������� ������������� ��� �����</param>
	void InsertNewItemToCListCtrl(PERSONS* pPerson);

	/// <summary>
	/// ����������� ������ ����� �� ���������� � ������� �� ���� ����������.
	/// </summary>
	void ConfigurateCListCtrl();

	// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;

protected:
	/// <summary>
	/// ����� ��������� ������ ����� �� CListCtrl ��� ������������ �� ����������.
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
