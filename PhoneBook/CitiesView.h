
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
	CCitiesDocument* GetDocument() const;

	//Methods
public:
	/// <summary>
	/// ������� ����� ������� ������ ���������� �� ���������.
	/// </summary>
	/// <param name="LSCCitiesList">���� �������� � ����� �� �� �������� �������.</param>
	/// <param name="oCSelfClearingPtrArray">����� �������� ������ ������ �� ��������� ��������� �� ������.</param>
	void FillView(CListCtrl& LSCCitiesList, const CSelfClearingTypedPtrArray<CITIES>& oCSelfClearingPtrArray);

	/// <summary>
	/// ����� ������� ������ ������ ��� �������� ���� �������� ���� ��������.
	/// </summary>
	/// <param name="LSCCitiesList">���� �������� ��� ����� �� ����� �������� ��������.</param>
	void AddColumns(CListCtrl& LSCCitiesList);

	// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CCitiesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTablesCities();
};

#ifndef _DEBUG  // debug version in CitiesView.cpp
inline CCitiesDocument* CCitiesView::GetDocument() const
{
	return reinterpret_cast<CCitiesDocument*>(m_pDocument);
}
#endif

