
// CitiesView.cpp : implementation of the CCitiesView class
//
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PhoneBook.h"
#endif

#include "CitiesDoc.h"
#include "CitiesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CCitiesDocument.h"
#include "CCitiesDialog.h"


// CCitiesView

IMPLEMENT_DYNCREATE(CCitiesView, CListView)

BEGIN_MESSAGE_MAP(CCitiesView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_TABLES_CITIES, &CCitiesView::OnTablesCities)
END_MESSAGE_MAP()

// CCitiesView construction/destruction

CCitiesView::CCitiesView() noexcept
{
	// TODO: add construction code here

}

CCitiesView::~CCitiesView()
{
}

BOOL CCitiesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

void CCitiesView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CListCtrl& LSCCitiesList = GetListCtrl();

	LSCCitiesList.InsertItem(0, _T("Varna"));
	LSCCitiesList.InsertItem(1, _T("Burgas"));
	LSCCitiesList.InsertItem(2, _T("Sofia"));
	LSCCitiesList.InsertItem(3, _T("Plovdiv"));


	LSCCitiesList.InsertColumn(0, _T("Име"), LVCFMT_CENTER, 120,1);
	LSCCitiesList.InsertColumn(1, _T("Регион"), LVCFMT_CENTER,120,1);
	LSCCitiesList.InsertColumn(2, _T("Пощенски код"), LVCFMT_CENTER, 120,1);

	LSCCitiesList.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);


	LSCCitiesList.SetItemText(0,1,_T("Варна"));
	LSCCitiesList.SetItemText(0,2, _T("9000"));

	LSCCitiesList.SetItemText(1,1, _T("Бургас"));
	LSCCitiesList.SetItemText(1, 2,_T("8000"));
				  
	LSCCitiesList.SetItemText(2,1, _T("София"));
	LSCCitiesList.SetItemText(2,2, _T("1000"));
				  
	LSCCitiesList.SetItemText(3,1, _T("Пловдив"));
	LSCCitiesList.SetItemText(3,2, _T("4000"));


	CCitiesDocument cDoc = GetDocument();
	m_pDocument->OnNewDocument();

	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

void CCitiesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCitiesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCitiesView diagnostics

#ifdef _DEBUG
void CCitiesView::AssertValid() const
{
	CListView::AssertValid();
}

void CCitiesView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CCitiesDoc* CCitiesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCitiesDoc)));
	return (CCitiesDoc*)m_pDocument;
};
#endif //_DEBUG


// CCitiesView message handlers


void CCitiesView::OnTablesCities()
{
	/*CCitiesDialog oCitiesDialog;
	oCitiesDialog.DoModal();*/
}
