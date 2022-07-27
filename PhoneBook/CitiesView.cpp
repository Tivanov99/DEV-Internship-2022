
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

	ConfigurateCListCtrl();
	
	FillView();
}

void CCitiesView::ConfigurateCListCtrl()
{
	CListCtrl& �ListCtrl = GetListCtrl();

	�ListCtrl.SetExtendedStyle(�ListCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	�ListCtrl.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	AddColumns(�ListCtrl);
}

void CCitiesView::AddColumns(CListCtrl& LSCCitiesList)
{
	const int nColumnWidth = 120;
	int nColumnNumber = 0;
	LSCCitiesList.InsertColumn(nColumnNumber, _T("���"), LVCFMT_LEFT, nColumnWidth, 1);
	LSCCitiesList.InsertColumn(++nColumnNumber, _T("������"), LVCFMT_CENTER, nColumnWidth, 1);
	LSCCitiesList.InsertColumn(++nColumnNumber, _T("�������� ���"), LVCFMT_CENTER, nColumnWidth, 1);
}

void CCitiesView::FillView()
{
	CListCtrl& �ListCtrl = GetListCtrl();

	CCitiesDocument* pCCitiesDocument = GetDocument();

	const CSelfClearingTypedPtrArray<CITIES>& oCitiesArray = pCCitiesDocument->GetAllPersons();

	for (INT_PTR i = 0; i < oCitiesArray.GetCount(); i++)
	{
		CITIES* pCurrentCity = oCitiesArray.GetAt(i);
		if (pCurrentCity == NULL)
			continue;

		InsertNewItemToCListCtrl(pCurrentCity);
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
	CListCtrl& �ListCtrl = GetListCtrl();
	const int nSelectedRow = �ListCtrl.GetSelectionMark();
	return nSelectedRow;
}

CITIES* CCitiesView::GetSelectedRecordItemData()
{
	const int nSelectedRow = GetNumberOfSelectedRow();
	if (nSelectedRow == -1)
	{
		AfxMessageBox(_T("This function is only called on record!"));
		return NULL;
	}
	CListCtrl& �ListCtrl = GetListCtrl();
	CITIES* pCity = reinterpret_cast<CITIES*>(�ListCtrl.GetItemData(nSelectedRow));
	return pCity;
}

const int CCitiesView::GetColumnCount()
{
	CListCtrl& �ListCtrl = GetListCtrl();

	CHeaderCtrl* oHeaderCtrl = �ListCtrl.GetHeaderCtrl();

	int nColumnCount = oHeaderCtrl->GetItemCount();

	return nColumnCount;
}
//

void CCitiesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	int nNumberOfSelectedRow = GetNumberOfSelectedRow();
	CListCtrl& �ListCtrl = GetListCtrl();

	switch (lHint)
	{
	case ContextMenuOperations::Create: break;
	case ContextMenuOperations::Delete:
		�ListCtrl.DeleteItem(nNumberOfSelectedRow);
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

	const int msgboxID = MessageBox(
		(LPCWSTR)L"Do you want the record to be deleted?",
		(LPCWSTR)L"Delete record.",
		MB_ICONINFORMATION | IDOK
	);

	if (msgboxID == IDOK)
	{
		CCitiesDocument* pCitiesDocument = GetDocument();
		if (!pCitiesDocument->DeleteCityById(pCity->lID))
			return;

		OnInitialUpdate();

		/*const int nSelectedRow = GetNumberOfSelectedRow();

		CListCtrl& �ListCtrl = GetListCtrl();
		�ListCtrl.DeleteItem(nSelectedRow);*/
	}
}

void CCitiesView::OnContextMenuEdit()
{
	CITIES* pCity = GetSelectedRecordItemData();
	if (pCity == NULL)
		return;

	CCitiesDialog oCitiesDialog(ContextMenuOperations::Edit, *pCity);

	if (oCitiesDialog.DoModal() != IDOK)
	{
		return;
	}

	CCitiesDocument* pCitiesDocument = GetDocument();

	
	if (!pCitiesDocument->UpdateCity(*pCity))
		return;

		CString strPostalCode;
		strPostalCode.Format(_T("%d"), pCity->lPOSTAL_CODE);

		const int nSelectedRow = GetNumberOfSelectedRow();
		CListCtrl& �ListCtrl = GetListCtrl();
		int nColumnNumber = 0;

		�ListCtrl.SetItemText(nSelectedRow, nColumnNumber++, pCity->szCITY_NAME);
		�ListCtrl.SetItemText(nSelectedRow, nColumnNumber++, pCity->szAREA_NAME);
		�ListCtrl.SetItemText(nSelectedRow, nColumnNumber, strPostalCode);
}

void CCitiesView::InsertNewItemToCListCtrl(CITIES* pCity)
{
	CListCtrl& �ListCtrl = GetListCtrl();

	const int nRow = �ListCtrl.GetItemCount();

	�ListCtrl.InsertItem(nRow, pCity->szCITY_NAME);

	int nColumnNumber = 1;

	�ListCtrl.SetItemText(nRow, nColumnNumber++, pCity->szAREA_NAME);

	CString strPostalCode;
	strPostalCode.Format(_T("%d"), pCity->lPOSTAL_CODE);
	�ListCtrl.SetItemText(nRow, nColumnNumber, strPostalCode);

	�ListCtrl.SetItemData(nRow, reinterpret_cast<DWORD_PTR>(pCity));
}

void CCitiesView::OnContextMenuInsert()
{
	CITIES oCity;

	CCitiesDialog oCitiesDialog(ContextMenuOperations::Create, oCity);

	if (oCitiesDialog.DoModal() != IDOK)
	{
		return;
	}

	CCitiesDocument* pCitiesDoc = GetDocument();

	if (!pCitiesDoc->InsertCity(oCity))
		return;

	/*CITIES* pCity = pCitiesDoc->GetLastCityRecord();

	if (pCity == NULL)
		return;
	InsertNewItemToCListCtrl(pCity);*/

	//TODO: Use OnUpdateAllViews method from CCitiesDocument.
}
