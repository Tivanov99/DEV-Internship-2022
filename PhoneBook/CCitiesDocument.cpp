#include "pch.h"
#include "CCitiesDocument.h"


IMPLEMENT_DYNCREATE(CCitiesDocument, CDocument)

BEGIN_MESSAGE_MAP(CCitiesDocument, CDocument)
END_MESSAGE_MAP()


CCitiesDocument::CCitiesDocument()noexcept {};
CCitiesDocument::~CCitiesDocument() {
};


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

const CSelfClearingTypedPtrArray<CITIES>& CCitiesDocument::GetAllPersons()
{
	return m_oCitiesArray;
}

CITIES* CCitiesDocument::GetCityById(long lID)
{
	CITIES* pCity = m_oCitiesArray.GetAt(lID);
	if (pCity == NULL)
	{
		AfxMessageBox(_T("Somethin wrong with record. Try again."));
	}
	return pCity;
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

	m_oCitiesArray.RemoveAt(lID);

	//TODO: Pass hint for deleted record and object which contains data for remove from listctrl.
	OnUpdateAllViews(ContextMenuOperations::Delete, NULL);
	return true;
}

void CCitiesDocument::OnUpdateAllViews(LPARAM lHint, CObject* pHint)
{
	UpdateAllViews(NULL, lHint, pHint);
}

void CCitiesDocument::DeleteCityByIdFromCitiesArray(long lID)
{
	long lIndex = GetCityIndexById(lID);

	if (lIndex == -1)
		return;

	CITIES* pCity = m_oCitiesArray.GetAt(lIndex);

	m_oCitiesArray.RemoveAt(lIndex);

}

void CCitiesDocument::AddCityToCitiesArray(CITIES& recCity)
{
}

long CCitiesDocument::GetCityIndexById(long lID)
{
	if (lID < 0 || lID >= m_oCitiesArray.GetCount())
	{
		AfxMessageBox(_T("The city was not found in the document! City Id - %d"), lID);
	}

	for (INT_PTR i = 0; i < m_oCitiesArray.GetCount(); i++)
	{
		CITIES* pCity = m_oCitiesArray.GetAt(i);

		if (pCity->lID != lID)
			continue;

		return i;
	}

	return -1;
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
