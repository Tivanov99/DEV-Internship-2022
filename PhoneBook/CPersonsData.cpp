#include "pch.h"
#include "CPersonsData.h"

bool CPersonsData::SelectAll(CSelfClearingTypedPtrArray<PERSONS>& oPersonsArray)
{
	return false;
}

bool CPersonsData::SelectWhereID(const long lID, PERSONS& recPersons)
{
	return false;
}

bool CPersonsData::UpdateWhereID(const long lID, const PERSONS& recPersons)
{
	return false;
}

bool CPersonsData::Insert(const PERSONS& recPersons)
{
	return false;
}

bool CPersonsData::DeleteWhereID(const long lID)
{
	return false;
}
