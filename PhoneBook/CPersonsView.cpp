#include "pch.h"
#include "CPersonsView.h"
#include "resource.h"
#include "PhoneBook.h"
#include "CPersonsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <map>

IMPLEMENT_DYNCREATE(CPersonsView, CListView)


BEGIN_MESSAGE_MAP(CPersonsView, CListView)

	ON_WM_CONTEXTMENU()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_EDIT_CONTEXT_DELETE, &CPersonsView::OnContextMenuDelete)
	ON_COMMAND(ID_EDIT_CONTEXT_READ_DATA, &CPersonsView::OnEditContextReadData)
	ON_COMMAND(ID_EDIT_CONTEXT_INSERT, &CPersonsView::OnContextMenuInsert)
	ON_COMMAND(ID_EDIT_CONTEXT_EDIT, &CPersonsView::OnContextMenuEdit)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CONTEXT_EDIT, &CPersonsView::ManageContextMenuItems)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CONTEXT_READ_DATA, &CPersonsView::ManageContextMenuItems)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CONTEXT_DELETE, &CPersonsView::ManageContextMenuItems)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CONTEXT_INSERT, &CPersonsView::ManageContextMenuItems)


END_MESSAGE_MAP()

CPersonsView::CPersonsView() noexcept {};

CPersonsView::~CPersonsView() {};

void CPersonsView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

void CPersonsView::ManageContextMenuItems(CCmdUI* pCmdUI)
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

BOOL CPersonsView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CListView::PreCreateWindow(cs);
}

#ifdef _DEBUG
void CPersonsView::AssertValid() const
{
	CListView::AssertValid();
}

void CPersonsView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CPersonsDocument* CPersonsView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPersonsDocument)));
	return (CPersonsDocument*)m_pDocument;
};
#endif //_DEBUG



void CPersonsView::OnInitialUpdate()
{
	//CListView::OnInitialUpdate();

	ConfigurateCListCtrl();

	FillView();
}

void CPersonsView::ConfigurateCListCtrl()
{
	CListCtrl& LSCCitiesList = GetListCtrl();

	LSCCitiesList.SetExtendedStyle(LSCCitiesList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	LSCCitiesList.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	AddColumns();
}

void CPersonsView::AddColumns()
{
	CListCtrl& LSCCitiesList = GetListCtrl();
	int nColumnNumber = 0;
	LSCCitiesList.InsertColumn(nColumnNumber++, _T("Име"), LVCFMT_LEFT, GlobalConstants::_nColumnWidth, 1);
	LSCCitiesList.InsertColumn(nColumnNumber++, _T("Фамилия"), LVCFMT_CENTER, GlobalConstants::_nColumnWidth, 1);
}

void CPersonsView::FillView()
{
	CListCtrl& оListCtrl = GetListCtrl();

	CPersonsDocument* pPersonsDocument = GetDocument();

	const CPersonsArray& oPersonsArray = pPersonsDocument->GetAllPersons();

	for (INT_PTR i = 0; i < oPersonsArray.GetCount(); i++)
	{
		PERSONS* pCurrentPerson = oPersonsArray.GetAt(i);
		if (pCurrentPerson == NULL)
			continue;

		InsertNewRecordToCListCtrl(pCurrentPerson);
	}
}

const int CPersonsView::GetSelectedRowNumber()
{
	CListCtrl& LSCCitiesList = GetListCtrl();
	const int nSelectedRow = LSCCitiesList.GetSelectionMark();
	return nSelectedRow;
}

PERSONS* CPersonsView::GetSelectedRecordItemData()
{
	const int nSelectedRow = GetSelectedRowNumber();
	
	CListCtrl& оListCtrl = GetListCtrl();
	PERSONS* pPerson = reinterpret_cast<PERSONS*>(оListCtrl.GetItemData(nSelectedRow));
	return pPerson;
}

void CPersonsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	int nNumberOfSelectedRow = GetSelectedRowNumber();

	CListCtrl& LSCCitiesList = GetListCtrl();

	CPersonsDocument* pPersonDocument = GetDocument();

	switch (lHint)
	{
	case ContextMenuOperations::InsertRecord:
		InsertNewRecordToCListCtrl(pPersonDocument->GetPersonById((long)pHint));
		break;
	case ContextMenuOperations::Delete:
		LSCCitiesList.DeleteItem(nNumberOfSelectedRow);
		break;
	case ContextMenuOperations::Edit:
		break;
	default:
		break;
	}
}

void UpdateRecord(PERSONS* pPerson)
{

}


void CPersonsView::InsertNewRecordToCListCtrl(PERSONS* pPerson)
{
	CListCtrl& LSCCitiesList = GetListCtrl();

	const int nRow = LSCCitiesList.GetItemCount();

	LSCCitiesList.InsertItem(nRow, pPerson->szFIRST_NAME);

	int nColumnNumber = 1;

	LSCCitiesList.SetItemText(nRow, nColumnNumber, pPerson->szLAST_NAME);

	LSCCitiesList.SetItemData(nRow, reinterpret_cast<DWORD_PTR>(pPerson));
}

void CPersonsView::OnContextMenuDelete()
{
	const PERSONS* pPerson = GetSelectedRecordItemData();
	if (pPerson == NULL)
		return;

	CString strMessage;
	strMessage.Format(_T("Do you want the record to be deleted? First name : %s Last name : %s"), pPerson->szFIRST_NAME, pPerson->szLAST_NAME);

	const int msgboxID = MessageBox(
		(LPCWSTR)strMessage,
		(LPCWSTR)L"Delete record.",
		MB_ICONINFORMATION | IDOK
	);

	if (msgboxID == IDOK)
	{
		CPersonsDocument* pPersonsDocument = GetDocument();

		pPersonsDocument->DeletePersonById(pPerson->lID);
	}
}


void CPersonsView::OnEditContextReadData()
{
	PERSONS* pPerson = GetSelectedRecordItemData();

	if (pPerson == NULL)
		return;

	PERSONS oPerson = *pPerson;

	CPersonsDocument* pPersonDocument = GetDocument();

	CCitiesArray oCitiesArray;
	pPersonDocument->GetAllCities(oCitiesArray);

	CPhoneNumbersArray oPhoneNumbersArray;
	pPersonDocument->GetPersonPhoneNumbers(pPerson->lID, oPhoneNumbersArray);

	map<long, PHONE_TYPES*> oMap;

	//pPersonDocument->GetAllPhoneTypes(oMap, pPerson->lID);

	CPersonsDialog oPersonsDialog(DialogWindowActions::ReadData, oPerson, oCitiesArray, oPhoneNumbersArray, oMap);

	if (!oPersonsDialog.DoModal())
		return;
}


void CPersonsView::OnContextMenuInsert()
{
	CPersonsDocument* pPersonDocument = GetDocument();

	CCitiesArray oCitiesArray;
	pPersonDocument->GetAllCities(oCitiesArray);

	CPhoneNumbersArray oPhoneNumbersArray;

	map<long, PHONE_TYPES*> oMap;

	PERSONS oPerson;
	oPerson.lUpdateCounter = 0;

	CPersonsDialog oPersonsDialog(DialogWindowActions::InsertData, oPerson, oCitiesArray, oPhoneNumbersArray, oMap);

	if (!oPersonsDialog.DoModal())
		return;

	bool bInsertResult = pPersonDocument->InsertPerson(oPerson);
	if (!bInsertResult)
		AfxMessageBox(_T("Record insert failed."));
	//TODO: Check for inserting phone numbers
}


void CPersonsView::OnContextMenuEdit()
{
	PERSONS* pPerson = GetSelectedRecordItemData();

	if (pPerson == NULL)
		return;

	PERSONS oPerson = *pPerson;
	CPersonsDocument* pPersonDocument = GetDocument();

	CCitiesArray oCitiesArray;
	pPersonDocument->GetAllCities(oCitiesArray);

	CPhoneNumbersArray oPhoneNumbersArray;
	pPersonDocument->GetPersonPhoneNumbers(pPerson->lID, oPhoneNumbersArray);

	map<long, PHONE_TYPES*> oMap;

	pPersonDocument->GetAllPhoneTypes(oMap);

	CPersonsDialog oPersonsDialog(DialogWindowActions::EditData, oPerson, oCitiesArray, oPhoneNumbersArray, oMap);

	if (oPersonsDialog.DoModal() != IDOK)
		return;

	bool bResult = pPersonDocument->UpdatePerson(oPerson);
	if (!bResult)
		AfxMessageBox(_T("Record update failed."));
}
