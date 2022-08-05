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
	CPersonsDocument::Dump(dc);
}

const CPersonsArray& CPersonsDocument::GetAllPersons()
{
	return m_oPersonsArray;
}

bool CPersonsDocument::GetAllPhoneTypes(CPhoneTypesArray& oPhoneTypesArray)
{
	if (!m_ÓPersonsData.SelectAllPhoneTypes(oPhoneTypesArray))
		return false;

	return true;
}

PERSONS* CPersonsDocument::GetPersonById(long lID)
{
	PERSONS* pPerson = m_oPersonsArray.GetAt(lID);
	if (pPerson == NULL)
		AfxMessageBox(_T("Failed to read data about person."));

	return pPerson;
}

bool CPersonsDocument::DeletePersonById(long lID)
{
	if (!m_ÓPersonsData.DeletePersonAndPhoneNumbers(lID))
		return false;

	DeletePersonFromPersonsArray(lID);

	//TODO: Pass hint for deleted record and object which contains data for remove from listctrl.
	OnUpdateAllViews(ContextMenuOperations::Delete, (CObject*)lID);
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

bool CPersonsDocument::UpdatePerson(PERSONS& recPerson)
{
	if (!m_ÓPersonsData.UpdateWhereID(recPerson.lID, recPerson))
		return false;

	//view-ÚÓ ‚ÁÂÏ‡ Á‡ÔËÒ‡ ÓÚ Ï‡ÒË‚‡ ÍÓÈÚÓ Â ÚÛÍ!

	OnUpdateAllViews(ContextMenuOperations::Edit, (CObject*)recPerson.lID);
	return true;
}
bool CPersonsDocument::InsertPerson(PERSONS& recPerson)
{
	if (!m_ÓPersonsData.InsertRecord(recPerson))
		return false;

	AddPersonToPersonsArray(recPerson);

	//TODO: Chech here for object ?
	OnUpdateAllViews(ContextMenuOperations::InsertRecord, (CObject*)recPerson.lID);
	return true;
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

bool CPersonsDocument::GetAllPhoneTypes(map<long, PHONE_TYPES*>& oMap)
{
	CPhoneTypesArray oPhoneTypesArray;
	if (!m_ÓPersonsData.SelectAllPhoneTypes(oPhoneTypesArray))
		return false;

	for (INT_PTR i = 0; i < oPhoneTypesArray.GetCount(); i++)
	{
		PHONE_TYPES* pPhoneType = new PHONE_TYPES();

		*pPhoneType = *oPhoneTypesArray.GetAt(i);
			
		if (pPhoneType == NULL)
			continue;

		oMap.insert(pair<long, PHONE_TYPES*>(pPhoneType->lID, pPhoneType));
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
