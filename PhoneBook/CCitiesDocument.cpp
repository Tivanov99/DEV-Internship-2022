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

const CSelfClearingTypedPtrArray< CITIES>& CCitiesDocument::GetAllData()
{
	return oCitiesSelfClearingPtrArray;
}

CITIES* CCitiesDocument::GetCityById(long lID)
{

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
