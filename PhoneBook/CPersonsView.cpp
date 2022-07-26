#include "pch.h"
#include "CPersonsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CPersonsView, CListView)


//BEGIN_MESSAGE_MAP(CPersonsView, CListView)
//	ON_WM_CONTEXTMENU()
//	ON_WM_RBUTTONUP()
//	ON_WM_LBUTTONDBLCLK()
//	/*ON_COMMAND(ID_EDIT_CONTEXT_DELETE, &CCitiesView::OnContextMenuDelete)
//	ON_COMMAND(ID_EDIT_CONTEXT_EDIT, &CCitiesView::OnContextMenuEdit)
//	ON_COMMAND(ID_EDIT_CONTEXT_INSERT, &CCitiesView::OnContextMenuInsert)*/
//END_MESSAGE_MAP()

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

	const CSelfClearingTypedPtrArray<PERSONS>& oCSelfClearingPtrCitiesArray = pCPersonsDocument->GetAllPersons();
	FillView(LSCCitiesList, oCSelfClearingPtrCitiesArray);
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
	LSCCitiesList.InsertColumn(nColumnNumber, _T("Име"), LVCFMT_LEFT, nColumnWidth, 1);
	LSCCitiesList.InsertColumn(++nColumnNumber, _T("Презиме"), LVCFMT_CENTER, nColumnWidth, 1);
	LSCCitiesList.InsertColumn(++nColumnNumber, _T("Фамилия"), LVCFMT_CENTER, nColumnWidth, 1);

}