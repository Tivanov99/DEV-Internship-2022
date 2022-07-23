
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
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_EDIT_CONTEXT_DELETE, &CCitiesView::OnContextMenuDelete)
	ON_COMMAND(ID_EDIT_CONTEXT_EDIT, &CCitiesView::OnContextMenuEdit)
	ON_COMMAND(ID_EDIT_CONTEXT_INSERT, &CCitiesView::OnContextMenuInsert)
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


//TODO: Ask for view base class which will contains pure virtual method for fill view data.

void CCitiesView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CListCtrl& LSCCitiesList = GetListCtrl();

	LSCCitiesList.SetExtendedStyle(LSCCitiesList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	LSCCitiesList.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	CCitiesDocument* pCCitiesDocument = GetDocument();

	AddColumns(LSCCitiesList);
	const CSelfClearingTypedPtrArray<CITIES>& oCSelfClearingPtrCitiesArray = pCCitiesDocument->GetAllCities();
	FillView(LSCCitiesList, oCSelfClearingPtrCitiesArray);
}

void CCitiesView::AddColumns(CListCtrl& LSCCitiesList)
{
	const int nColumnWidth = 120;
	int nColumnNumber = 0;
	LSCCitiesList.InsertColumn(nColumnNumber, _T("Име"), LVCFMT_LEFT, nColumnWidth, 1);
	LSCCitiesList.InsertColumn(++nColumnNumber, _T("Регион"), LVCFMT_CENTER, nColumnWidth, 1);
	LSCCitiesList.InsertColumn(++nColumnNumber, _T("Пощенски код"), LVCFMT_CENTER, nColumnWidth, 1);
}

void CCitiesView::FillView(CListCtrl& LSCCitiesList, const CSelfClearingTypedPtrArray<CITIES>& oCSelfClearingPtrArray)
{
	for (INT_PTR i = 0; i < oCSelfClearingPtrArray.GetCount(); i++)
	{
		CITIES oCity;

		
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

		int nColumnCount = GetColumnCount();

		LSCCitiesList.InsertItem(nRowNumber, strCityName);
		LSCCitiesList.SetItemText(nRowNumber, nColumnNumber, strAreaName);
		LSCCitiesList.SetItemText(nRowNumber, ++nColumnNumber, strPostalCode);
		LSCCitiesList.SetItemData(nRowNumber, reinterpret_cast<DWORD_PTR>(oCurrentCity));
	}
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


const int CCitiesView::GetNumberOfSelectedRow()
{
	CListCtrl& LSCCitiesList = GetListCtrl();
	const int nSelectedRow = LSCCitiesList.GetSelectionMark();
	return nSelectedRow;
}

CITIES* CCitiesView::GetSelectedRecordData()
{
	const int nSelectedRow = GetNumberOfSelectedRow();
	if (nSelectedRow == -1)
	{
		AfxMessageBox(_T("This function is only called on record!"));
		return NULL;
	}
	CListCtrl& LSCCitiesList = GetListCtrl();
	CITIES* pCity = reinterpret_cast<CITIES*>(LSCCitiesList.GetItemData(nSelectedRow));
	return pCity;
}

const int CCitiesView::GetColumnCount()
{
	CListCtrl& LSCCitiesList = GetListCtrl();

	CHeaderCtrl* oHeaderCtrl = LSCCitiesList.GetHeaderCtrl();

	int nColumnCount = oHeaderCtrl->GetItemCount();

	return nColumnCount;
}
//

void CCitiesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	int nNumberOfSelectedRow = GetNumberOfSelectedRow();
	CListCtrl& LSCCitiesList = GetListCtrl();

	switch (lHint)
	{
	case ContextMenuOperations::Create: break;
	case ContextMenuOperations::Delete:
		LSCCitiesList.DeleteItem(nNumberOfSelectedRow);
		break;
	case ContextMenuOperations::Edit: break;
	default:
		break;
	}
}

void CCitiesView::OnContextMenuDelete()
{
	const CITIES* pCity = GetSelectedRecordData();
	if (pCity == NULL)
		return;

	const int msgboxID = MessageBox(
		(LPCWSTR)L"Do you want the record to be deleted?",
		(LPCWSTR)L"Delete record.",
		MB_ICONINFORMATION | IDOK
	);

	if (msgboxID == IDOK)
	{
		CCitiesDocument* oCitiesDoc = GetDocument();
		oCitiesDoc->DeleteCityById(pCity->lID);
	}
}

void CCitiesView::OnContextMenuEdit()
{
	CITIES* pCity = GetSelectedRecordData();
	if (pCity == NULL)
		return;

	CCitiesDialog oCitiesDialog(ContextMenuOperations::Edit, *pCity);

	if (oCitiesDialog.DoModal() != IDOK)
	{
		return;
	}

	CCitiesDocument* oCitiesDoc = GetDocument();
	oCitiesDoc->UpdateCity(*pCity);
}


void CCitiesView::OnContextMenuInsert()
{
	CITIES oCity;

	CCitiesDialog oCitiesDialog(ContextMenuOperations::Create, oCity);

	if (oCitiesDialog.DoModal() != IDOK)
	{
		return;
	}

	CCitiesDocument* oCitiesDoc = GetDocument();
	oCitiesDoc->InsertCity(oCity);
}
