#include "pch.h"
#include "CCitiesDocument.h"


IMPLEMENT_DYNCREATE(CCitiesDocument, CDocument)

BEGIN_MESSAGE_MAP(CCitiesDocument, CDocument)
END_MESSAGE_MAP()


CCitiesDocument::CCitiesDocument()noexcept {};
CCitiesDocument::~CCitiesDocument() {};


BOOL CCitiesDocument::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	m_CitiesData.SelectAll(m_oCitiesArray);
	return TRUE;
};

// CCitiesDoc serialization

void CCitiesDocument::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

const CSelfClearingTypedPtrArray< CITIES>& CCitiesDocument::GetAllCities()
{
	return m_oCitiesArray;
}

CITIES* CCitiesDocument::GetCityById(long lID)
{
	CITIES* pCity = m_oCitiesArray.GetAt(lID - 1);
	if (pCity == NULL)
	{
		AfxMessageBox(_T("Somethin wrong with record. Try again."));
	}
	return pCity;
}

CITIES* CCitiesDocument::GetLastCityRecord()
{
	return m_CitiesData.SelectLast();
}

#ifdef _DEBUG
void CCitiesDocument::AssertValid() const
{
	CDocument::AssertValid();
}

void CCitiesDocument::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

bool CCitiesDocument::DeleteCityById(long lID)
{
	const bool bDeleteResult = m_CitiesData.DeleteWhereID(lID);

	if (!bDeleteResult)
	{
		TRACE(_T("Deletion from database returned error. City id: %d"), lID);
		return false;
	}

	//TODO: Pass hint for deleted record and object which contains data for remove from listctrl.
	OnUpdateAllViews(ContextMenuOperations::Delete, NULL);
	return true;
}

void CCitiesDocument::OnUpdateAllViews(LPARAM lHint, CObject* pHint)
{
	UpdateAllViews(NULL, lHint, pHint);
}

bool CCitiesDocument::UpdateCity(CITIES& recCity)
{
	bool bUpdate = m_CitiesData.UpdateWhereID(recCity.lID, recCity);
	if (!bUpdate)
		return false;

	CITIES oCity;
	m_CitiesData.SelectWhereID(recCity.lID, oCity);
	//TODO: Chech here for object ?
	//OnUpdateAllViews(ContextMenuOperations::Edit, &oCity);
	return true;
}
bool CCitiesDocument::InsertCity(CITIES& recCity)
{
	bool bInsert = m_CitiesData.Insert(recCity);
	if (!bInsert)
		return false;

	//TODO: Chech here for object ?
	//OnUpdateAllViews(ContextMenuOperations::Edit, &oCity);
	return true;
}