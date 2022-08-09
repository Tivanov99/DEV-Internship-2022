﻿
// CitiesView.cpp : implementation of the CCitiesView class
//
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PhoneBook.h"
#endif

#include "CCitiesView.h"

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
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_EDIT_CONTEXT_DELETE, &CCitiesView::OnContextMenuDelete)
	ON_COMMAND(ID_EDIT_CONTEXT_EDIT, &CCitiesView::OnContextMenuEdit)
	ON_COMMAND(ID_EDIT_CONTEXT_INSERT, &CCitiesView::OnContextMenuInsert)
	ON_COMMAND(ID_EDIT_CONTEXT_READ_DATA, &CCitiesView::OnEditContextReadData)
END_MESSAGE_MAP()



// CCitiesView construction/destruction

CCitiesView::CCitiesView() noexcept
{
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

//TODO: Ask for view base class which will contains pure virtual method for fill view data.

void CCitiesView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	ConfigurateCListCtrl();

	FillView();
}

void CCitiesView::ConfigurateCListCtrl()
{
	CListCtrl& oListCtrl = GetListCtrl();

	oListCtrl.SetExtendedStyle(oListCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	oListCtrl.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	AddColumns(oListCtrl);
}

void CCitiesView::AddColumns(CListCtrl& LSCCitiesList)
{
	const int nColumnWidth = 120;
	int nColumnNumber = 0;
	LSCCitiesList.InsertColumn(nColumnNumber++, _T("���"), LVCFMT_LEFT, nColumnWidth, 1);
	LSCCitiesList.InsertColumn(nColumnNumber++, _T("������"), LVCFMT_CENTER, nColumnWidth, 1);
	LSCCitiesList.InsertColumn(nColumnNumber, _T("�������� ���"), LVCFMT_CENTER, nColumnWidth, 1);
}

void CCitiesView::FillView()
{
	CListCtrl& oListCtrl = GetListCtrl();

	CCitiesDocument* pCCitiesDocument = GetDocument();

	const CCitiesArray& oCitiesArray = pCCitiesDocument->GetAllCities();

	for (INT_PTR i = 0; i < oCitiesArray.GetCount(); i++)
	{
		CITIES* pCurrentCity = oCitiesArray.GetAt(i);
		if (pCurrentCity == NULL)
			continue;

		InsertNewRecordToCListCtrl(pCurrentCity);
	}
}

const int CCitiesView::GetSelectedRowNumber()
{
	CListCtrl& oListCtrl = GetListCtrl();
	const int nSelectedRow = oListCtrl.GetSelectionMark();
	return nSelectedRow;
}

CITIES* CCitiesView::GetSelectedRecordItemData()
{
	const int nSelectedRow = GetSelectedRowNumber();
	if (nSelectedRow == -1)
	{
		AfxMessageBox(_T("This function is only called on record!"));
		return NULL;
	}
	CListCtrl& oListCtrl = GetListCtrl();
	CITIES* pCity = reinterpret_cast<CITIES*>(oListCtrl.GetItemData(nSelectedRow));
	return pCity;
}

void CCitiesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	int nNumberOfSelectedRow = GetSelectedRowNumber();
	CListCtrl& oListCtrl = GetListCtrl();

	switch (lHint)
	{
	case ContextMenuOperations::InsertRecord:
		break;
	case ContextMenuOperations::Delete:
		oListCtrl.DeleteItem(nNumberOfSelectedRow);
		break;
	case ContextMenuOperations::Edit: break;
	default:
		break;
	}
}

void CCitiesView::OnContextMenuDelete()
{
	const CITIES* pCity = GetSelectedRecordItemData();
	if (pCity == NULL)
		return;

	CString strMessage;
	strMessage.Format(_T("Do you want the record to be deleted? City name : %s"), pCity->szCityName);

	const int msgboxID = MessageBox(
		(LPCWSTR)strMessage,
		(LPCWSTR)L"Delete record.",
		MB_ICONINFORMATION | IDOK
	);

	if (msgboxID == IDOK)
	{
		CCitiesDocument* pCitiesDocument = GetDocument();

		pCitiesDocument->DeleteCityById(pCity->lID);
	}
}

void CCitiesView::OnContextMenuEdit()
{
	CITIES* pCity = GetSelectedRecordItemData();
	if (pCity == NULL)
		return;

	CITIES oCity = *pCity;

	CCitiesDialog oCitiesDialog(DialogWindowActions::EditData, oCity);

	if (oCitiesDialog.DoModal() != IDOK)
		return;

	CCitiesDocument* pCitiesDocument = GetDocument();

	if (!pCitiesDocument->UpdateCity(oCity))
		return;

	UpdateRecord(oCity);
}


void CCitiesView::OnContextMenuInsert()
{
	CITIES oCity;
	oCity.lUpdateCounter = 0;

	CCitiesDialog oCitiesDialog(DialogWindowActions::InsertData, oCity);

	if (oCitiesDialog.DoModal() != IDOK)
		return;

	CCitiesDocument* pCitiesDoc = GetDocument();

	CITIES* pCity = pCitiesDoc->InsertCity(oCity);

	if (pCity == NULL)
		return;

	InsertNewRecordToCListCtrl(pCity);

	//TODO: Use OnUpdateAllViews method from CCitiesDocument.
}

void CCitiesView::InsertNewRecordToCListCtrl(CITIES* pCity)
{
	CListCtrl& oListCtrl = GetListCtrl();

	const int nRow = oListCtrl.GetItemCount();

	oListCtrl.InsertItem(nRow, pCity->szCityName);

	int nColumnNumber = 1;

	oListCtrl.SetItemText(nRow, nColumnNumber++, pCity->szAreaName);

	CString strPostalCode;
	strPostalCode.Format(_T("%d"), pCity->lPostalCode);
	oListCtrl.SetItemText(nRow, nColumnNumber, strPostalCode);

	oListCtrl.SetItemData(nRow, reinterpret_cast<DWORD_PTR>(pCity));
}

void CCitiesView::OnEditContextReadData()
{
	CITIES* pCity = GetSelectedRecordItemData();
	if (pCity == NULL)
		return;

	CITIES oCity = *pCity;

	CCitiesDialog oCitiesDialog(DialogWindowActions::ReadData, oCity);

	oCitiesDialog.DoModal();
}

void CCitiesView::UpdateRecord(CITIES& oCity)
{
	CString strPostalCode;
	strPostalCode.Format(_T("%d"), oCity.lPostalCode);

	const int nSelectedRow = GetSelectedRowNumber();
	CListCtrl& oListCtrl = GetListCtrl();
	int nColumnNumber = 0;

	oListCtrl.SetItemText(nSelectedRow, nColumnNumber++, oCity.szCityName);
	oListCtrl.SetItemText(nSelectedRow, nColumnNumber++, oCity.szAreaName);
	oListCtrl.SetItemText(nSelectedRow, nColumnNumber, strPostalCode);
}


