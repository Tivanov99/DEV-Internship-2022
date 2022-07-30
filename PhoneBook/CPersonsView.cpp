#include "pch.h"
#include "CPersonsView.h"
#include "resource.h"
#include "PhoneBook.h"
#include "CPersonsDialog.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CPersonsView, CListView)


BEGIN_MESSAGE_MAP(CPersonsView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_LBUTTONDBLCLK()
	/*ON_COMMAND(ID_EDIT_CONTEXT_DELETE, &CCitiesView::OnContextMenuDelete)
	ON_COMMAND(ID_EDIT_CONTEXT_EDIT, &CCitiesView::OnContextMenuEdit)
	ON_COMMAND(ID_EDIT_CONTEXT_INSERT, &CCitiesView::OnContextMenuInsert)*/
	ON_COMMAND(ID_EDIT_CONTEXT_DELETE, &CPersonsView::OnContextMenuDelete)
	ON_COMMAND(ID_EDIT_CONTEXT_READ_DATA, &CPersonsView::OnEditContextReadData)
	ON_COMMAND(ID_EDIT_CONTEXT_INSERT, &CPersonsView::OnContextMenuInsert)
	ON_COMMAND(ID_EDIT_CONTEXT_EDIT, &CPersonsView::OnContextMenuEdit)
END_MESSAGE_MAP()

// CCitiesView construction/destruction

CPersonsView::CPersonsView() noexcept {};

CPersonsView::~CPersonsView() {};

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

BOOL CPersonsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CListView::PreCreateWindow(cs);
}

void CPersonsView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	ConfigurateCListCtrl();

	FillView();
}

void CPersonsView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
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
	if (nSelectedRow == -1)
	{
		AfxMessageBox(_T("This function is only called on record!"));
		return NULL;
	}
	CListCtrl& оListCtrl = GetListCtrl();
	PERSONS* pPerson = reinterpret_cast<PERSONS*>(оListCtrl.GetItemData(nSelectedRow));
	return pPerson;
}

void CPersonsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	int nNumberOfSelectedRow = GetSelectedRowNumber();
	CListCtrl& LSCCitiesList = GetListCtrl();

	switch (lHint)
	{
	case ContextMenuOperations::Insert:
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

void CPersonsView::InsertNewRecordToCListCtrl(PERSONS* pPerson)
{
	CListCtrl& LSCCitiesList = GetListCtrl();

	const int nRow = LSCCitiesList.GetItemCount();

	LSCCitiesList.InsertItem(nRow, pPerson->szFIRST_NAME);

	int nColumnNumber = 1;

	LSCCitiesList.SetItemText(nRow, nColumnNumber++, pPerson->szSECOND_NAME);

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
	// TODO: Add your command handler code here
}


void CPersonsView::OnContextMenuInsert()
{
	// TODO: Add your command handler code here
}


void CPersonsView::OnContextMenuEdit()
{
	PERSONS* pPerson = GetSelectedRecordItemData();

	PERSONS oPerson = *pPerson;


	CPersonsDocument* pPersonDocument = GetDocument();

	CCitiesArray oCitiesArray;

	pPersonDocument->GetAllCities(oCitiesArray);
		
	CPersonsDialog oPersonsDialog(DialogWindowActions::EditData, oPerson, oCitiesArray);

	if (!oPersonsDialog.DoModal())
		return;

	// TODO: Add your command handler code here
}
