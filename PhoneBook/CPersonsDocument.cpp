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

#ifdef _DEBUG
void CPersonsDocument::AssertValid() const
{
	CDocument::AssertValid();
}

void CPersonsDocument::Dump(CDumpContext& dc) const
{
	CPersonsDocument::Dump(dc);
}
#endif //_DEBUG

PERSONS* CPersonsDocument::GetPersonById(long lID)
{
	PERSONS* pPerson = m_oPersonsArray.GetAt(lID);
	if (pPerson == NULL)
	{
		AfxMessageBox(_T("Failed to read data about person."));
	}
	return pPerson;
}

bool CPersonsDocument::DeletePersonById(long lID)
{
	const bool bDeleteResult = m_ÓPersonsData.DeleteWhereID(lID);

	if (!bDeleteResult)
		return false;

	DeletePersonFromPersonsArray(lID);

	//TODO: Pass hint for deleted record and object which contains data for remove from listctrl.
	OnUpdateAllViews(ContextMenuOperations::Delete, NULL);
	return true;
}

bool CPersonsDocument::GetAllCities(CCitiesArray& oCitiesArray)
{
	if (!m_ÓPersonsData.SelectAllCities(oCitiesArray))
		return false;

	return true;
}

void CPersonsDocument::OnUpdateAllViews(LPARAM lHint, CObject* pHint)
{
	UpdateAllViews(NULL, lHint, pHint);
}

bool CPersonsDocument::UpdatePerson(PERSONS& recPerson)
{
	bool bUpdate = m_ÓPersonsData.UpdateWhereID(recPerson.lID, recPerson);
	if (!bUpdate)
		return false;

	PERSONS oPerson;
	m_ÓPersonsData.SelectWhereID(recPerson.lID, oPerson);


	//TODO: Chech here for object ?
	//OnUpdateAllViews(ContextMenuOperations::EditData, &oPerson);
	return true;
}
bool CPersonsDocument::InsertPerson(PERSONS& recCity)
{
	bool bInsert = m_ÓPersonsData.InsertRecord(recCity);
	if (!bInsert)
		return false;

	AddPersonToPersonsArray(recCity);

	//TODO: Chech here for object ?
	//OnUpdateAllViews(ContextMenuOperations::EditData, &oPerson);
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

		if (pPerson->lID != lID)
			continue;

		return i;
	}

	return -1;
}

bool CPersonsDocument::GetPersonPhoneNumbers(long lPersonID, CPhoneNumbersArray& oPhoneNumbersArray)
{
	if (m_ÓPersonsData.SelectAllPhoneNumbers(lPersonID, oPhoneNumbersArray))
		return false;

	return true;
}