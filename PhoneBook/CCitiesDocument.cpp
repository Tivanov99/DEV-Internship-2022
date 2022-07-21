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
	m_CitiesData.SelectAll(oCitiesSelfClearingPtrArray);
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
	return oCitiesSelfClearingPtrArray;
}

CITIES* CCitiesDocument::GetCityById(long lID)
{
	CITIES* pCity = oCitiesSelfClearingPtrArray.GetAt(lID - 1);
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
	//TODO: Pass hint for deleted record and object which contains data for remove from listctrl.
	OnUpdateAllViews(NULL, NULL);
	return true;
}
void CCitiesDocument::OnUpdateAllViews(LPARAM lHint, CObject* pHint)
{
	UpdateAllViews(NULL, lHint, pHint);
}
