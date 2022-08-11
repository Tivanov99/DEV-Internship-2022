
// CitiesView.cpp : implementation of the CCitiesView class
//
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PhoneBook.h"
#endif

#include "CitiesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CitiesDocument.h"
#include "CitiesDialog.h"



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
	ON_UPDATE_COMMAND_UI(ID_EDIT_CONTEXT_INSERT, &CCitiesView::ManageContextMenuItems)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CONTEXT_DELETE, &CCitiesView::ManageContextMenuItems)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CONTEXT_READ_DATA, &CCitiesView::ManageContextMenuItems)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CONTEXT_EDIT, &CCitiesView::ManageContextMenuItems)
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

void CCitiesView::ManageContextMenuItems(CCmdUI* pCmdUI)
{
	CListCtrl& LSCCitiesList = GetListCtrl();

	UINT uSelectedCount = LSCCitiesList.GetSelectedCount();

	if (pCmdUI->m_nID == ID_EDIT_CONTEXT_INSERT && uSelectedCount == 0)
	{
		pCmdUI->Enable(true);
		return;
	}

	if (pCmdUI->m_nID == ID_EDIT_CONTEXT_INSERT && uSelectedCount > 0)
	{
		pCmdUI->Enable(false);
		return;
	}

	if (uSelectedCount == 0)
		pCmdUI->Enable(false);
}

void CCitiesView::OnInitialUpdate()
{
	//CListView::OnInitialUpdate();

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
	LSCCitiesList.InsertColumn(nColumnNumber++, _T("Име"), LVCFMT_LEFT, nColumnWidth, 1);
	LSCCitiesList.InsertColumn(nColumnNumber++, _T("Област"), LVCFMT_CENTER, nColumnWidth, 1);
	LSCCitiesList.InsertColumn(nColumnNumber, _T("Пощенски код"), LVCFMT_CENTER, nColumnWidth, 1);
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

	CListCtrl& LSCCitiesList = GetListCtrl();

	CCitiesDocument* pCitiesDocument = GetDocument();

	long* lId = (long*)&pHint;

	switch (lHint)
	{
	case ContextMenuOperations::InsertRecord:
		InsertNewRecordToCListCtrl(pCitiesDocument->GetCityById(*lId));
		break;
	case ContextMenuOperations::Delete:
		LSCCitiesList.DeleteItem(nNumberOfSelectedRow);
		break;
	case ContextMenuOperations::Edit:
		UpdateRecord(*lId);
		break;
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

	CCitiesDialog oCitiesDialog(DialogWindowActions::EditData, *pCity);

	if (oCitiesDialog.DoModal() != IDOK)
		return;

	CCitiesDocument* pCitiesDocument = GetDocument();

	if (!pCitiesDocument->UpdateCity(*pCity))
		return;

	UpdateRecord(pCity->lID);
}


void CCitiesView::OnContextMenuInsert()
{
	CITIES oCity;
	CCitiesDialog oCitiesDialog(DialogWindowActions::InsertData, oCity);

	if (oCitiesDialog.DoModal() != IDOK)
		return;

	CCitiesDocument* pCitiesDocument = GetDocument();

	if (!pCitiesDocument->InsertCity(oCity))
		return;
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
	CCitiesDialog oCitiesDialog(DialogWindowActions::ReadData, *pCity);
	oCitiesDialog.DoModal();
}

void CCitiesView::UpdateRecord(long lID)
{
	CCitiesDocument* oCitiesDocument = GetDocument();
	CITIES* pUpdatedCity = oCitiesDocument->GetCityById(lID);

	CString strPostalCode;
	strPostalCode.Format(_T("%d"), pUpdatedCity->lPostalCode);

	const int nSelectedRow = GetSelectedRowNumber();

	CListCtrl& oListCtrl = GetListCtrl();
	int nColumnNumber = 0;

	oListCtrl.SetItemText(nSelectedRow, nColumnNumber++, pUpdatedCity->szCityName);
	oListCtrl.SetItemText(nSelectedRow, nColumnNumber++, pUpdatedCity->szAreaName);
	oListCtrl.SetItemText(nSelectedRow, nColumnNumber, strPostalCode);
	oListCtrl.SetItemData(nSelectedRow, reinterpret_cast<DWORD_PTR>(pUpdatedCity));
}
