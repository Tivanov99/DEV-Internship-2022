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
	CDocument::Dump(dc);
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
	if (!m_PhoneTypesData.DeleteWhereID(lID))
	{
		CString strErrorMessage;
		strErrorMessage.Format(_T("Deletion from database returned error. Phone type id: %d"), lID);
		AfxMessageBox(strErrorMessage);
		return false;
	}

	if (!DeletePhoneTypeFromPhoneTypesArray(lID))
		return false;

	OnUpdateAllViews(ContextMenuOperations::Delete, (CObject*)lID);
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


	OnUpdateAllViews(ContextMenuOperations::Edit, (CObject*)recPhoneType.lID);
	return true;
}

bool CPhoneTypesDocument::InsertPhoneType(PHONE_TYPES& recPhoneType)
{
	if (!m_PhoneTypesData.InsertRecord(recPhoneType))
		return false;

	if (!AddPhoneTypeToPhoneTypesArray(recPhoneType))
		return false;

	OnUpdateAllViews(ContextMenuOperations::Edit, (CObject*)recPhoneType.lID);
	return true;
}

bool CPhoneTypesDocument::DeletePhoneTypeFromPhoneTypesArray(long lID)
{
	if (lID == -1)
	{
		AfxMessageBox(_T("The phone type was not found in the document! Phone type Id - %d"), lID);
		return false;
	}

	long lPhoneTypeIndex = GetPhoneTypeIndexFromPhoneTypesArray(lID);

	if (lPhoneTypeIndex == -1)
		return false;

	PHONE_TYPES* pPhoneNumber = m_oPhoneTypesArray.GetAt(lPhoneTypeIndex);
	if (pPhoneNumber == NULL)
		return false;

	delete pPhoneNumber;
	pPhoneNumber = NULL;
	m_oPhoneTypesArray.RemoveAt(lPhoneTypeIndex);

	return true;
}

bool CPhoneTypesDocument::AddPhoneTypeToPhoneTypesArray(PHONE_TYPES& recPhoneType)
{
	PHONE_TYPES* pPhoneType = new PHONE_TYPES();
	*pPhoneType = recPhoneType;
	if (pPhoneType == NULL)
	{
		delete pPhoneType;
		AfxMessageBox(_T("Failed to add phone type to document."));
		return false;
	}
	m_oPhoneTypesArray.Add(pPhoneType);
	return true;
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

void CPhoneTypesDocument::UpdatePhoneTypesArray(long lID, PHONE_TYPES& recPhoneType)
{
	long lPersonIndex = GetPhoneTypeIndexFromPhoneTypesArray(lID);

	if (lPersonIndex == -1)
		return;

	PHONE_TYPES* pPhoneType = m_oPhoneTypesArray.GetAt(lPersonIndex);
	*pPhoneType = recPhoneType;
}
