#include "pch.h"
#include "CitiesDocument.h"


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

void CCitiesDocument::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

const CCitiesArray& CCitiesDocument::GetAllCities()
{
	return m_oCitiesArray;
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

CITIES* CCitiesDocument::GetCityById(long lID)
{
	INT_PTR lIndex = GetCityIndexFromCitiesArray(lID);
	if (lIndex == -1)
		return NULL;

	CITIES* pCity = m_oCitiesArray.GetAt(lIndex);

	if (pCity == NULL)
	{
		AfxMessageBox(_T("Failed to read data about person."));
		return NULL;
	}
	return pCity;
}

bool CCitiesDocument::DeleteCityById(long lID)
{
	const bool bDeleteResult = m_CitiesData.DeleteWhereID(lID);

	if (!bDeleteResult)
	{
		AfxMessageBox(_T("Deletion from database returned error. City id: %d"), lID);
		return false;
	}

	DeleteCityFromCitiesArray(lID);

	OnUpdateAllViews(ContextMenuOperations::Delete, (CObject*)lID);
	return true;
}

void CCitiesDocument::OnUpdateAllViews(LPARAM lHint, CObject* pHint)
{
	UpdateAllViews(NULL, lHint, pHint);
}

bool CCitiesDocument::UpdateCity(CITIES& recCity)
{
	if (!m_CitiesData.UpdateCityById(recCity.lID, recCity))
		return false;

	OnUpdateAllViews(ContextMenuOperations::Edit, (CObject*)(recCity.lID));
	return true;
}

bool CCitiesDocument::InsertCity(CITIES& recCity)
{
	if (!m_CitiesData.InsertRecord(recCity))
		return false;
	
	if (!AddCityToCitiesArray(recCity))
		return false;

	OnUpdateAllViews(ContextMenuOperations::InsertRecord, (CObject*)recCity.lID);

	return true;
}

bool CCitiesDocument::DeleteCityFromCitiesArray(long lCityId)
{
	INT_PTR lCityIndex = GetCityIndexFromCitiesArray(lCityId);

	if (lCityIndex == -1)
		return false;

	m_oCitiesArray.RemovePointerAt(lCityIndex);

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
		return NULL;
	}
	m_oCitiesArray.Add(pCity);
	return pCity;
}

INT_PTR CCitiesDocument::GetCityIndexFromCitiesArray(long lID)
{
	if (lID < 0 )
	{
		AfxMessageBox(_T("City with ID  - (%d)  was not found in the document."), lID);
		return -1;
	}

	for (INT_PTR i = 0; i < m_oCitiesArray.GetCount(); i++)
	{
		CITIES* pCity = m_oCitiesArray.GetAt(i);

		if (pCity == NULL || pCity->lID != lID)
			continue;

		return i;
	}

	return -1;
}