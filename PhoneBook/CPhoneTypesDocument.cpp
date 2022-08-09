#include "pch.h"
#include "CPhoneTypesDocument.h"

IMPLEMENT_DYNCREATE(CPhoneTypesDocument, CDocument)

BEGIN_MESSAGE_MAP(CPhoneTypesDocument, CDocument)
END_MESSAGE_MAP()

CPhoneTypesDocument::CPhoneTypesDocument() noexcept {};

CPhoneTypesDocument::~CPhoneTypesDocument() {};

BOOL CPhoneTypesDocument::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	if (!m_PhoneTypesData.SelectAll(m_oPhoneTypesArray))
		return FALSE;
	return TRUE;
};

void CPhoneTypesDocument::Serialize(CArchive& ar)
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

const CPhoneTypesArray& CPhoneTypesDocument::GetAllPhoneTypes()
{
	return m_oPhoneTypesArray;
}


#ifdef _DEBUG
void CPhoneTypesDocument::AssertValid() const
{
	CDocument::AssertValid();
}

void CPhoneTypesDocument::Dump(CDumpContext& dc) const
{
	CPhoneTypesDocument::Dump(dc);
}
#endif //_DEBUG

PHONE_TYPES* CPhoneTypesDocument::GetPhoneTypeById(long lID)
{
	PHONE_TYPES* pPhoneType = m_oPhoneTypesArray.GetAt(lID);
	if (pPhoneType == NULL)
	{
		AfxMessageBox(_T("Somethin wrong with record. Try again."));
	}
	return pPhoneType;
}

bool CPhoneTypesDocument::DeletePhoneTypeById(long lID)
{
	const bool bDeleteResult = m_PhoneTypesData.DeleteWhereID(lID);

	if (!bDeleteResult)
	{
		TRACE(_T("Deletion from database returned error. Phone type id: %d"), lID);
		return false;
	}

	DeletePhoneTypeFromPhoneTypesArray(lID);

	//TODO: Pass hint for deleted record and object which contains data for remove from listctrl.
	OnUpdateAllViews(ContextMenuOperations::Delete, NULL);
	return true;
}

void CPhoneTypesDocument::OnUpdateAllViews(LPARAM lHint, CObject* pHint)
{
	UpdateAllViews(NULL, lHint, pHint);
}


bool CPhoneTypesDocument::UpdatePhoneType(PHONE_TYPES& recPhoneType)
{
	if (!m_PhoneTypesData.UpdateWhereID(recPhoneType.lID, recPhoneType))
		return false;

	long lCityIndex = GetPhoneTypeIndexFromPhoneTypesArray(recPhoneType.lID);

	PHONE_TYPES* pPhoneType = m_oPhoneTypesArray.GetAt(lCityIndex);
	*pPhoneType = recPhoneType;

	//TODO: Chech here for object ?
	//OnUpdateAllViews(ContextMenuOperations::EditData, &oCity);
	return true;
}

PHONE_TYPES* CPhoneTypesDocument::InsertPhoneType(PHONE_TYPES& recPhoneType)
{
	if (!m_PhoneTypesData.InsertRecord(recPhoneType))
		return NULL;

	PHONE_TYPES* pPhoneNumber = AddPhoneTypeToPhoneTypesArray(recPhoneType);


	//TODO: Chech here for object ?
	OnUpdateAllViews(ContextMenuOperations::Edit, NULL);
	return pPhoneNumber;
}

bool CPhoneTypesDocument::DeletePhoneTypeFromPhoneTypesArray(long lID)
{
	if (lID == -1)
	{
		AfxMessageBox(_T("The phone type was not found in the document! Phone type Id - %d"), lID);
		return false;
	}

	long lPhoneTypeIndex = GetPhoneTypeIndexFromPhoneTypesArray(lID);

	PHONE_TYPES* pPhoneNumber = m_oPhoneTypesArray.GetAt(lPhoneTypeIndex);

	delete pPhoneNumber;
	pPhoneNumber = NULL;
	m_oPhoneTypesArray.RemoveAt(lPhoneTypeIndex);

	return true;
}

PHONE_TYPES* CPhoneTypesDocument::AddPhoneTypeToPhoneTypesArray(PHONE_TYPES& recPhoneType)
{
	PHONE_TYPES* pPhoneType = new PHONE_TYPES();
	*pPhoneType = recPhoneType;
	if (pPhoneType == NULL)
	{
		delete pPhoneType;
		AfxMessageBox(_T("Failed to add phone type to document."));
	}
	m_oPhoneTypesArray.Add(pPhoneType);

	return pPhoneType;
}

long CPhoneTypesDocument::GetPhoneTypeIndexFromPhoneTypesArray(long lID)
{
	if (lID < 0)
	{
		AfxMessageBox(_T("Phone type with ID  - (%d)  was not found in the document."), lID);
		return -1;
	}

	for (INT_PTR i = 0; i < m_oPhoneTypesArray.GetCount(); i++)
	{
		PHONE_TYPES* pPhoneType = m_oPhoneTypesArray.GetAt(i);

		if (pPhoneType->lID != lID)
			continue;

		return i;
	}

	return -1;
}


