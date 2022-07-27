#include "pch.h"
#include "CPersonsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Enumerations.h"

IMPLEMENT_DYNCREATE(CPersonsView, CListView)


BEGIN_MESSAGE_MAP(CPersonsView, CListView)
	/*ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()*/
	/*ON_COMMAND(ID_EDIT_CONTEXT_DELETE, &CCitiesView::OnContextMenuDelete)
	ON_COMMAND(ID_EDIT_CONTEXT_EDIT, &CCitiesView::OnContextMenuEdit)
	ON_COMMAND(ID_EDIT_CONTEXT_INSERT, &CCitiesView::OnContextMenuInsert)*/
END_MESSAGE_MAP()

// CCitiesView construction/destruction

CPersonsView::CPersonsView() noexcept {};

CPersonsView::~CPersonsView() {};


BOOL CPersonsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CPersonsView::PreCreateWindow(cs);
}

void CPersonsView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	ConfigurateCListCtrl();

	CListCtrl& LSCCitiesList = GetListCtrl();
	CPersonsDocument* pCPersonsDocument = GetDocument();

	const CSelfClearingTypedPtrArray<PERSONS>& oCSelfClearingPtrPersonsArray = pCPersonsDocument->GetAllPersons();
	FillView(LSCCitiesList, oCSelfClearingPtrPersonsArray);
}

void CPersonsView::ConfigurateCListCtrl()
{
	CListCtrl& LSCCitiesList = GetListCtrl();

	LSCCitiesList.SetExtendedStyle(LSCCitiesList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	LSCCitiesList.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	AddColumns(LSCCitiesList);
}

void CPersonsView::AddColumns(CListCtrl& LSCCitiesList)
{
	const int nColumnWidth = 120;
	int nColumnNumber = 0;
	LSCCitiesList.InsertColumn(nColumnNumber++, _T("Име"), LVCFMT_LEFT, nColumnWidth, 1);
	LSCCitiesList.InsertColumn(nColumnNumber++, _T("Презиме"), LVCFMT_CENTER, nColumnWidth, 1);
	LSCCitiesList.InsertColumn(nColumnNumber++, _T("Фамилия"), LVCFMT_CENTER, nColumnWidth, 1);
	LSCCitiesList.InsertColumn(nColumnNumber, _T("Телефонен номер"), LVCFMT_CENTER, nColumnWidth, 1);
}

void CPersonsView::FillView(CListCtrl& LSCCitiesList, const CSelfClearingTypedPtrArray<PERSONS>& oPersonsArray)
{
	for (INT_PTR i = 0; i < oPersonsArray.GetCount(); i++)
	{
		PERSONS* pCurrentPerson = oPersonsArray.GetAt(i);
		if (pCurrentPerson == NULL)
			continue;

		InsertNewItemToCListCtrl(pCurrentPerson);
	}
}

// CCitiesView diagnostics

#ifdef _DEBUG
void CPersonsView::AssertValid() const
{
	CPersonsView::AssertValid();
}

void CPersonsView::Dump(CDumpContext& dc) const
{
	CPersonsView::Dump(dc);
}

CPersonsDocument* CPersonsView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPersonsDocument)));
	return (CPersonsDocument*)m_pDocument;
};
#endif //_DEBUG

const int CPersonsView::GetNumberOfSelectedRow()
{
	CListCtrl& LSCCitiesList = GetListCtrl();
	const int nSelectedRow = LSCCitiesList.GetSelectionMark();
	return nSelectedRow;
}

PERSONS* CPersonsView::GetSelectedRecordItemData()
{
	/*const int nSelectedRow = GetNumberOfSelectedRow();
	if (nSelectedRow == -1)
	{
		AfxMessageBox(_T("This function is only called on record!"));
		return NULL;
	}
	CListCtrl& LSCCitiesList = GetListCtrl();

	PERSONS* pPerson = reinterpret_cast<PERSONS*>(LSCCitiesList.GetItemData(nSelectedRow));
	return pPerson;*/
	return NULL;
}

const int CPersonsView::GetColumnCount()
{
	CListCtrl& LSCCitiesList = GetListCtrl();

	CHeaderCtrl* oHeaderCtrl = LSCCitiesList.GetHeaderCtrl();

	int nColumnCount = oHeaderCtrl->GetItemCount();

	return nColumnCount;
}
//

void CPersonsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
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

void CPersonsView::InsertNewItemToCListCtrl(PERSONS* pPerson)
{
	CListCtrl& LSCCitiesList = GetListCtrl();

	const int nRow = LSCCitiesList.GetItemCount();

	LSCCitiesList.InsertItem(nRow, pPerson->szFIRST_NAME);

	int nColumnNumber = 1;

	LSCCitiesList.SetItemText(nRow, nColumnNumber++, pPerson->szSECOND_NAME);

	LSCCitiesList.SetItemText(nRow, nColumnNumber++, pPerson->szLAST_NAME);


	/*CString strPostalCode;
	strPostalCode.Format(_T("%d"), pCity->lPOSTAL_CODE);
	LSCCitiesList.SetItemText(nRow, nColumnNumber, strPostalCode);

	LSCCitiesList.SetItemData(nRow, reinterpret_cast<DWORD_PTR>(pCity));*/
}