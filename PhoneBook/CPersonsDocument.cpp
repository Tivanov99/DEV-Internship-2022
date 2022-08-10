#include "pch.h"
#include "CPersonsDocument.h"

IMPLEMENT_DYNCREATE(CPersonsDocument, CDocument)

BEGIN_MESSAGE_MAP(CPersonsDocument, CDocument)
END_MESSAGE_MAP()

CPersonsDocument::CPersonsDocument()noexcept {};
CPersonsDocument::~CPersonsDocument() {};


BOOL CPersonsDocument::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	m_ÓPersonsData.SelectAll(m_oPersonsArray);
	return TRUE;
};

// CCitiesDoc serialization

void CPersonsDocument::Serialize(CArchive& ar)
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


#ifdef _DEBUG
void CPersonsDocument::AssertValid() const
{
	CDocument::AssertValid();
}
#endif //_DEBUG


void CPersonsDocument::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

const CPersonsArray& CPersonsDocument::GetAllPersons()
{
	return m_oPersonsArray;
}

PERSONS* CPersonsDocument::GetPersonByIdFromPersonsArray(long lID)
{
	for (INT_PTR i = 0; i < m_oPersonsArray.GetCount(); i++)
	{
		PERSONS* pPerson = m_oPersonsArray.GetAt(i);
		if (pPerson == NULL)
			continue;
		if (pPerson->lID == lID)
			return pPerson;
	}
	AfxMessageBox(_T("Failed to read data about person."));

	return NULL;
}

long CPersonsDocument::GetPersonIndexFromPersonsArray(long lID)
{
	if (lID < 0)
	{
		AfxMessageBox(_T("City with ID  - (%d)  was not found in the document."), lID);
		return -1;
	}

	for (INT_PTR i = 0; i < m_oPersonsArray.GetCount(); i++)
	{
		PERSONS* pPerson = m_oPersonsArray.GetAt(i);

		if (pPerson == NULL || pPerson->lID != lID)
			continue;

		return i;
	}

	return -1;
}

bool CPersonsDocument::GetPersonPhoneNumbers(long lPersonID, CPhoneNumbersArray& oPhoneNumbersArray)
{
	if (!m_ÓPersonsData.SelectAllPhoneNumbersByPersonId(lPersonID, oPhoneNumbersArray))
		return false;

	return true;
}

bool CPersonsDocument::GetAllPhoneTypes(CSelfClearingMap<long, PHONE_TYPES*>& oMap)
{
	CPhoneTypesArray oPhoneTypesArray;
	if (!m_ÓPersonsData.SelectAllPhoneTypes(oPhoneTypesArray))
		return false;

	for (INT_PTR i = 0; i < oPhoneTypesArray.GetCount(); i++)
	{
		PHONE_TYPES* pCurrentPhoneType = oPhoneTypesArray.GetAt(i);

		if (pCurrentPhoneType == NULL)
			continue;

		PHONE_TYPES* pPhoneType = new PHONE_TYPES();

		*pPhoneType = *pCurrentPhoneType;

		oMap.SetAt(pPhoneType->lID, pPhoneType);
	}
	return true;
}
PHONE_TYPES* CPersonsDocument::GetPhoneTypeById(long lID, CPhoneTypesArray& oPhoneTypesArray)
{
	for (INT_PTR i = 0; i < oPhoneTypesArray.GetCount(); i++)
	{
		PHONE_TYPES* pCurrentPhoneType = oPhoneTypesArray.GetAt(i);
		if (pCurrentPhoneType == NULL)
			continue;

		if (pCurrentPhoneType->lID == lID)
			return pCurrentPhoneType;
	}
	return NULL;
}

bool CPersonsDocument::GetAllPhoneTypes(CPhoneTypesArray& oPhoneTypesArray)
{
	if (!m_ÓPersonsData.SelectAllPhoneTypes(oPhoneTypesArray))
		return false;

	return true;
}

bool CPersonsDocument::GetAllCities(CCitiesArray& oCitiesArray)
{
	if (!m_ÓPersonsData.SelectAllCities(oCitiesArray))
		return false;

	return true;
}

void CPersonsDocument::OnUpdateAllViews(LPARAM lHint, CObject* pHint = NULL)
{
	UpdateAllViews(NULL, lHint, pHint);
}

bool CPersonsDocument::InsertRecord(PERSONS& recPerson, CPhoneNumbersArray& oPhoneNumbersArray)
{
	if (!m_ÓPersonsData.InsertPersonAndPhoneNumbers(recPerson, oPhoneNumbersArray))
		return false;

	AddPersonToPersonsArray(recPerson);

	OnUpdateAllViews(ContextMenuOperations::InsertRecord, (CObject*)recPerson.lID);
	return true;
}

bool CPersonsDocument::UpdatePersonAndPhoneNumbers(PERSONS& recPerson, CPhoneNumbersArray& oPhoneNumbersArray)
{
	if (!m_ÓPersonsData.UpdatePersonAndPhoneNumbers(recPerson, oPhoneNumbersArray))
		return false;

	UpdatePersonFromPersonsArray(recPerson.lID, recPerson);

	OnUpdateAllViews(ContextMenuOperations::Edit, (CObject*)recPerson.lID);
	return true;
}

bool CPersonsDocument::DeletePersonAndPhoneNumbers(long lID)
{
	if (!m_ÓPersonsData.DeletePersonAndPhoneNumbers(lID))
		return false;

	if(DeletePersonFromPersonsArray(lID));
		return false;

	OnUpdateAllViews(ContextMenuOperations::Delete, (CObject*)lID);

	return true;
}

PERSONS* CPersonsDocument::AddPersonToPersonsArray(PERSONS& recPerson)
{
	PERSONS* pPerson = new PERSONS();
	*pPerson = recPerson;
	if (pPerson == NULL)
	{
		delete pPerson;
		AfxMessageBox(_T("Failed to add city to document."));
		return NULL;
	}
	m_oPersonsArray.Add(pPerson);

	return pPerson;
}

bool CPersonsDocument::DeletePersonFromPersonsArray(long lPersonId)
{
	if (lPersonId == -1)
	{
		AfxMessageBox(_T("The person was not found in the document! Person Id - %d"), lPersonId);
		return false;
	}

	long lPersonIndex = GetPersonIndexFromPersonsArray(lPersonId);

	PERSONS* pPerson = m_oPersonsArray.GetAt(lPersonIndex);

	delete pPerson;
	pPerson = NULL;
	m_oPersonsArray.RemoveAt(lPersonIndex);
	return true;
}

void CPersonsDocument::UpdatePersonFromPersonsArray(long lID, PERSONS& recUpdatedPerson)
{
	long lPersonIndex = GetPersonIndexFromPersonsArray(lID);

	PERSONS* pPerson = m_oPersonsArray.GetAt(lPersonIndex);
	*pPerson = recUpdatedPerson;
}