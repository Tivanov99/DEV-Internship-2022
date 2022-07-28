#include "pch.h"
#include "CCitiesDocument.h"
#include "Enumerations.h"


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

const CSelfClearingTypedPtrArray<CITIES>& CCitiesDocument::GetAllCities()
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

	DeleteCityByIndexFromCitiesArray(lID);

	//TODO: Pass hint for deleted record and object which contains data for remove from listctrl.
	OnUpdateAllViews(ContextMenuOperations::Delete, NULL);
	return true;
}

void CCitiesDocument::OnUpdateAllViews(LPARAM lHint, CObject* pHint)
{
	UpdateAllViews(NULL, lHint, pHint);
}

bool CCitiesDocument::DeleteCityByIndexFromCitiesArray(long lIndex)
{
	if (lIndex == -1)
	{
		AfxMessageBox(_T("The city was not found in the document! City Id - %d"), lIndex);
		return false;
	}

	CITIES* pCity = m_oCitiesArray.GetAt(lIndex);

	delete pCity;
	pCity = NULL;
	m_oCitiesArray.RemoveAt(lIndex);

	return true;
}

CITIES* CCitiesDocument::AddCityToCitiesArray(CITIES& recCity)
{
	CITIES* pCity = new CITIES();
	*pCity = recCity;
	if (pCity == NULL)
	{
		delete pCity;
		AfxMessageBox(_T("Failed to add city to document."));
	}
	m_oCitiesArray.Add(pCity);

	return pCity;
}

long CCitiesDocument::GetCityIndexFromCitiesArrayById(long lID)
{
	if (lID < 0 )
	{
		AfxMessageBox(_T("City with ID  - (%d)  was not found in the document."), lID);
		return -1;
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
	if (!m_CitiesData.UpdateWhereID(recCity.lID, recCity))
		return false;

	long lCityIndex = GetCityIndexFromCitiesArrayById(recCity.lID);

	CITIES* pCity = m_oCitiesArray.GetAt(lCityIndex);
	*pCity = recCity;

	//TODO: Chech here for object ?
	//OnUpdateAllViews(ContextMenuOperations::Edit, &oCity);
	return true;
}

CITIES* CCitiesDocument::InsertCity(CITIES& recCity)
{
	if (!m_CitiesData.Insert(recCity))
		return NULL;
	
	CITIES* pCity = AddCityToCitiesArray(recCity);


	//TODO: Chech here for object ?
	//OnUpdateAllViews(ContextMenuOperations::Edit, &oCity);
	return pCity;
}
