
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
	LSCCitiesList.InsertColumn(0, _T("���"), LVCFMT_CENTER, 120,1);
	LSCCitiesList.InsertColumn(1, _T("������"), LVCFMT_CENTER,120,1);
	LSCCitiesList.InsertColumn(2, _T("�������� ���"), LVCFMT_CENTER, 120,1);


	LSCCitiesList.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	CCitiesDocument* doc = GetDocument();

	const CSelfClearingTypedPtrArray<CITIES>& oCSelfClearingPtrArray = doc->GetAllData();

	for (INT_PTR i = 0; i < oCSelfClearingPtrArray.GetCount(); i++)
	{
		CITIES* oCurrentCity = oCSelfClearingPtrArray.GetAt(i);
		if (oCurrentCity == NULL)
			continue;

		int nRowNumber = i;
		int nColumnNumber = 1;

		CString strCityName;
		strCityName.Format(_T("%s"), oCurrentCity->szCITY_NAME);

		CString strAreaName;
		strAreaName.Format(_T("%s"), oCurrentCity->szAREA_NAME);

		CString strPostalCode;
		strPostalCode.Format(_T("%d"), oCurrentCity->lPOSTAL_CODE);

		LSCCitiesList.InsertItem(nRowNumber, strCityName);
		LSCCitiesList.SetItemText(nRowNumber, nColumnNumber, strAreaName);
		LSCCitiesList.SetItemText(nRowNumber, ++nColumnNumber, strPostalCode);
	}

	// TODO: You may populate your ListView with items by directly acces�		sing
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

CCitiesDocument* CCitiesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCitiesDocument)));
	return (CCitiesDocument*)m_pDocument;
};
#endif //_DEBUG


// CCitiesView message handlers


void CCitiesView::OnTablesCities()
{
	/*CCitiesDialog oCitiesDialog;
	oCitiesDialog.DoModal();*/
}
