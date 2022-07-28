
// CitiesView.h : interface of the CCitiesView class
//

#pragma once
#include "CitiesDoc.h"
#include "CCitiesDocument.h"


class CCitiesView : public CListView
{
protected: // create from serialization only
	CCitiesView() noexcept;
	DECLARE_DYNCREATE(CCitiesView)

	// Attributes
public:
	/// <summary>
	/// ����� �������� ���� ����� �� �������� ������������ �� ������ �����.
	/// </summary>
	/// <returns>�������� �� ���������.</returns>
	CCitiesDocument* GetDocument() const;

	//Methods
private:
	/// <summary>
	/// ������� ����� ������� ������ ���������� �� ���������.
	/// </summary>
	/// <param name="�ListCtrl">���� �������� � ����� �� �� �������� �������.</param>
	/// <param name="oCitiesArray">����� �������� ������ ������ �� ��������� ��������� �� ������.</param>
	void FillView();

	/// <summary>
	/// ����� ������� ������ ������ ��� �������� ���� �������� ���� ��������.
	/// </summary>
	/// <param name="�ListCtrl">���� �������� ��� ����� �� ����� �������� ��������.</param>
	void AddColumns(CListCtrl& �ListCtrl);

	 /// <summary>
	 /// ����� �������� ������� � 'item data' ��� ���������� �� ������ � CListCtrl.
	 /// </summary>
	 /// <returns></returns>
	 CITIES* GetSelectedRecordItemData();

	/// <summary>
	/// ������ ���� ���� ���������� � ������� ����� ����� �� ��� (-1 ������ �� � �������� �� ���� ���� �� ��������,� ����� ���� ������� � ��������������� ���������, �  �������� ������ ����� �� ���).
	/// </summary>
	/// <returns>����� �� ��� � ��������� -1 �� N</returns>
	const int GetSelectedRowNumber();

	/// <summary>
	/// ����� ������ ���� �� �������� � CListCtrl.
	/// </summary>
	/// <returns>���� ����� ����������� ���� �� ��������.</returns>
	const int GetColumnCount();

	/// <summary>
	/// ������ ��� ����� ��� ���� ����������.
	/// </summary>
	/// <param name="pCity">������� ������������� ��� �����</param>
	void InsertNewRecordToCListCtrl(CITIES* pCity);

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
	///������� ������� ����� ��� ����� ���� ����� ����� ��� view-�� � 'Delete' �� ������������ ����.
	/// </summary>
	afx_msg void OnContextMenuDelete();

	/// <summary>
	/// ��� ����� ���� ����� ����� ������� �������� �������� �������� � �������� �����.
	/// </summary>
	afx_msg void OnContextMenuEdit();

	/// <summary>
	/// ��� ����� ���� ��� �������� ���� � �������� ��� � 'Insert' �� ������������ ���� ������� �������� �������� � ����� �� ����� ��������� ������� �� ������.
	/// </summary>
	afx_msg void OnContextMenuInsert();
};

#ifndef _DEBUG  // debug version in CitiesView.cpp
inline CCitiesDocument* CCitiesView::GetDocument() const
{
	return reinterpret_cast<CCitiesDocument*>(m_pDocument);
}
#endif

