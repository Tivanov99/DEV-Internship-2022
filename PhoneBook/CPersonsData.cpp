#include "pch.h"
#include "CPersonsData.h"

bool CPersonsData::SelectAll(CSelfClearingTypedPtrArray<PERSONS>& oPersonsArray)
{
	return m_PersonsTable.SelectAll(oPersonsArray);
}

bool CPersonsData::SelectWhereID(const long lID, PERSONS& recPersons)
{
	return m_PersonsTable.SelectWhereID(lID,recPersons);
}

bool CPersonsData::UpdateWhereID(const long lID, const PERSONS& recPersons)
{
	return m_PersonsTable.UpdateWhereID(lID,recPersons);
}

bool CPersonsData::Insert(const PERSONS& recPersons)
{
	return m_PersonsTable.Insert(recPersons);
}

bool CPersonsData::DeleteWhereID(const long lID)
{
	return m_PersonsTable.DeleteWhereID(lID);
}
