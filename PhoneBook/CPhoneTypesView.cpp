#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PhoneBook.h"
#endif

#include "CPhoneTypesView.h"
#include "resource.h"
#include "CPhoneTypesDialog.h"


IMPLEMENT_DYNCREATE(CPhoneTypesView, CListView)


BEGIN_MESSAGE_MAP(CPhoneTypesView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_EDIT_CONTEXT_READ_DATA, &CPhoneTypesView::OnEditContextReadData)
	ON_COMMAND(ID_EDIT_CONTEXT_EDIT, &CPhoneTypesView::OnEditContextEdit)
	ON_COMMAND(ID_EDIT_CONTEXT_DELETE, &CPhoneTypesView::OnEditContextDelete)
	ON_COMMAND(ID_EDIT_CONTEXT_INSERT, &CPhoneTypesView::OnEditContextInsert)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CONTEXT_READ_DATA, &CPhoneTypesView::ContextMenuItems)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CONTEXT_EDIT, &CPhoneTypesView::ContextMenuItems)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CONTEXT_DELETE, &CPhoneTypesView::ContextMenuItems)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CONTEXT_INSERT, &CPhoneTypesView::ContextMenuItems)
END_MESSAGE_MAP()

CPhoneTypesView::CPhoneTypesView() noexcept
{
}

CPhoneTypesView::~CPhoneTypesView()
{
}

BOOL CPhoneTypesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

#ifdef _DEBUG
void CPhoneTypesView::AssertValid() const
{
	CListView::AssertValid();
}

void CPhoneTypesView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CPhoneTypesDocument* CPhoneTypesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPhoneTypesDocument)));
	return (CPhoneTypesDocument*)m_pDocument;
};
#endif //_DEBUG

void CPhoneTypesView::ContextMenuItems(CCmdUI* pCmdUI)
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


void CPhoneTypesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

void CPhoneTypesView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	ConfigurateCListCtrl();

	FillView();
}

void CPhoneTypesView::ConfigurateCListCtrl()
{
	CListCtrl& oListCtrl = GetListCtrl();

	oListCtrl.SetExtendedStyle(oListCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	oListCtrl.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	AddColumns(oListCtrl);
}

void CPhoneTypesView::AddColumns(CListCtrl& LSCCitiesList)
{
	const int nColumnWidth = 160;
	int nColumnNumber = 0;
	LSCCitiesList.InsertColumn(nColumnNumber++, _T("Тип"), LVCFMT_LEFT, nColumnWidth, 1);
}

void CPhoneTypesView::FillView()
{
	CListCtrl& oListCtrl = GetListCtrl();

	CPhoneTypesDocument* pPhoneTypesDocument = GetDocument();

	const CPhoneTypesArray& oPhoneTypesArray = pPhoneTypesDocument->GetAllPhoneTypes();

	for (INT_PTR i = 0; i < oPhoneTypesArray.GetCount(); i++)
	{
		PHONE_TYPES* pCurrentPhoneType = oPhoneTypesArray.GetAt(i);
		if (pCurrentPhoneType == NULL)
			continue;

		InsertNewRecordToCListCtrl(pCurrentPhoneType);
	}
}

const int CPhoneTypesView::GetSelectedRowNumber()
{
	CListCtrl& oListCtrl = GetListCtrl();
	const int nSelectedRow = oListCtrl.GetSelectionMark();
	return nSelectedRow;
}

PHONE_TYPES* CPhoneTypesView::GetSelectedRecordItemData()
{
	const int nSelectedRow = GetSelectedRowNumber();
	if (nSelectedRow == -1)
	{
		AfxMessageBox(_T("This function is only called on record!"));
		return NULL;
	}
	CListCtrl& oListCtrl = GetListCtrl();
	PHONE_TYPES* pPhoneType = reinterpret_cast<PHONE_TYPES*>(oListCtrl.GetItemData(nSelectedRow));
	return pPhoneType;
}

void CPhoneTypesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
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

void CPhoneTypesView::InsertNewRecordToCListCtrl(PHONE_TYPES* pPhoneType)
{
	CListCtrl& oListCtrl = GetListCtrl();

	const int nRow = oListCtrl.GetItemCount();

	oListCtrl.InsertItem(nRow, pPhoneType->szPhoneType);

	oListCtrl.SetItemData(nRow, reinterpret_cast<DWORD_PTR>(pPhoneType));
}

void CPhoneTypesView::OnEditContextReadData()
{
	PHONE_TYPES* pPhoneType = GetSelectedRecordItemData();
	if (pPhoneType == NULL)
		return;

	PHONE_TYPES oPhoneType = *pPhoneType;

	CPhoneTypesDialog oPhoneTypesDialog(DialogWindowActions::ReadData, oPhoneType);

	oPhoneTypesDialog.DoModal();
}


void CPhoneTypesView::OnEditContextEdit()
{
	PHONE_TYPES* pPhoneType = GetSelectedRecordItemData();
	if (pPhoneType == NULL)
		return;

	PHONE_TYPES oPhoneType = *pPhoneType;

	CPhoneTypesDialog oPhoneTypesDialog(DialogWindowActions::EditData, oPhoneType);

	if (oPhoneTypesDialog.DoModal() != IDOK)
		return;

	CPhoneTypesDocument* pPhoneTypesDocument = GetDocument();

	if (!pPhoneTypesDocument->UpdatePhoneType(oPhoneType))
		return;

	//UpdateRecord(oPhoneType);
}


void CPhoneTypesView::OnEditContextDelete()
{
	const PHONE_TYPES* pPhoneType = GetSelectedRecordItemData();
	if (pPhoneType == NULL)
		return;

	CString strMessage;
	strMessage.Format(_T("Do you want the record to be deleted? Phone type name : %s"), pPhoneType->szPhoneType);

	const int msgboxID = MessageBox(
		(LPCWSTR)strMessage,
		(LPCWSTR)L"Delete record.",
		MB_ICONINFORMATION | IDOK
	);

	if (msgboxID == IDOK)
	{
		CPhoneTypesDocument* pPhoneTypesDocument = GetDocument();

		if (!pPhoneTypesDocument->DeletePhoneTypeById(pPhoneType->lID))
			return;
	}
}


void CPhoneTypesView::OnEditContextInsert()
{
	PHONE_TYPES oPhoneType;

	CPhoneTypesDialog oPhoneTypesDialog(DialogWindowActions::InsertData, oPhoneType);

	if (oPhoneTypesDialog.DoModal() != IDOK)
		return;

	CPhoneTypesDocument* pPhoneTypesDocument = GetDocument();

	if (!pPhoneTypesDocument->InsertPhoneType(oPhoneType))
		return;
	//TODO: Use OnUpdateAllViews method from CCitiesDocument.e
}

void CPhoneTypesView::UpdateRecord(PHONE_TYPES& pPhoneType)
{
	CString strPostalCode;
	strPostalCode.Format(_T("%s"), pPhoneType.szPhoneType);

	const int nSelectedRow = GetSelectedRowNumber();
	CListCtrl& oListCtrl = GetListCtrl();
	int nColumnNumber = 0;

	oListCtrl.SetItemText(nSelectedRow, nColumnNumber++, pPhoneType.szPhoneType);

}


