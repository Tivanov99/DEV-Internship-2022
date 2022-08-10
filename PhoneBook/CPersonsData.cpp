#include "pch.h"
#include "CPersonsData.h"
#include "CPhoneNumbersTable.h"
#include "CPhoneTypesTable.h"

CPersonsData::CPersonsData()
{
};
CPersonsData::~CPersonsData() {};

bool CPersonsData::SelectAllPhoneNumbersByPersonId(long lPersonID, CPhoneNumbersArray& oPhoneNumbersArray)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CPhoneNumbersTable oPhoneNumbersTable(pDatabaseConnector->GetSession());

	CString strWhereClause;
	strWhereClause.Format(SqlQueries::WherePersonID, lPersonID);

	if (!oPhoneNumbersTable.SelectBySpecificColumnWhereID(oPhoneNumbersArray, strWhereClause))
	{
		pDatabaseConnector->CloseSession();
		return false;
	}

	pDatabaseConnector->CloseSession();

	return true;
}

bool CPersonsData::SelectAllPhoneTypes(CPhoneTypesArray& oPhoneTypesArray)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CPhoneTypesTable oPhoneTypesTable(pDatabaseConnector->GetSession());

	if (!oPhoneTypesTable.SelectAll(oPhoneTypesArray))
	{
		pDatabaseConnector->CloseSession();
		return false;
	}
	pDatabaseConnector->CloseSession();

	return true;
}

bool CPersonsData::SelectAllCities(CCitiesArray& oCitiesArray)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CCitiesTable oCitiesTable(pDatabaseConnector->GetSession());

	if (!oCitiesTable.SelectAll(oCitiesArray))
	{
		pDatabaseConnector->CloseSession();
		return false;
	}

	pDatabaseConnector->CloseSession();
	return true;
}
bool CPersonsData::SelectAll(CPersonsArray& oPersonsArray)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CPersonsTable îPersonsTable(pDatabaseConnector->GetSession());
	if (!îPersonsTable.SelectAll(oPersonsArray))
	{
		pDatabaseConnector->CloseSession();
		return false;
	}

	pDatabaseConnector->CloseSession();
	return true;
}

bool CPersonsData::SelectWhereID(const long lID, PERSONS& recPersons)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (pDatabaseConnector->OpenSession())
		return false;

	CPersonsTable îPersonsTable(pDatabaseConnector->GetSession());

	if (!îPersonsTable.SelectWhereID(lID, recPersons))
	{
		pDatabaseConnector->CloseSession();
		return false;
	}

	pDatabaseConnector->CloseSession();
	return true;
}

bool CPersonsData::UpdateWhereID(const long lID, const PERSONS& recPersons)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (pDatabaseConnector->OpenSession())
		return false;

	CSession oSession = pDatabaseConnector->GetSession();
	CPersonsTable îPersonsTable(oSession);

	if (!îPersonsTable.UpdateWhereID(lID, recPersons))
	{
		pDatabaseConnector->CloseSession();
		return false;
	}

	pDatabaseConnector->CloseSession();

	return true;
}

bool CPersonsData::InsertPersonAndPhoneNumbers(PERSONS& recPersons, CPhoneNumbersArray& oPhoneNumbersArray)
{
	DataBaseConnector* pDbConnector = DataBaseConnector::GetInstance();
	CSession oSession = pDbConnector->GetSession();

	if (!pDbConnector->OpenSession())
		return false;

	if (oSession.StartTransaction() != S_OK)
	{
		pDbConnector->CloseSession();
		return false;
	}

	CPersonsTable oPersonsTable(oSession);

	if (!oPersonsTable.InsertRecord(recPersons))
	{
		pDbConnector->AbortTransactionAndCloseSession();
		return false;
	}
	if (!InsertPhoneNumbers(oPhoneNumbersArray))
	{
		pDbConnector->AbortTransactionAndCloseSession();
		return false;
	}
	oSession.Commit();
	oSession.Close();
	return true;
}

bool CPersonsData::DeleteWhereID(const long lID)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CPersonsTable îPersonsTable(pDatabaseConnector->GetSession());

	if (!îPersonsTable.DeleteWhereID(lID))
	{
		pDatabaseConnector->CloseSession();
		return false;
	}

	pDatabaseConnector->CloseSession();
	return true;
}

bool CPersonsData::DeletePersonAndPhoneNumbers(const long lID)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CSession oSession = pDatabaseConnector->GetSession();

	if (oSession.StartTransaction() != S_OK)
	{
		pDatabaseConnector->AbortTransactionAndCloseSession();
		return false;
	}

	CPhoneNumbersTable oPhoneNumbersTable(oSession);

	CString strSqlQuery;
	strSqlQuery.Format(SqlQueries::WherePersonID, lID);

	if (!oPhoneNumbersTable.DeleteBySpecificColumnWhereID(lID, strSqlQuery))
	{
		pDatabaseConnector->AbortTransactionAndCloseSession();
		return false;
	}

	CPersonsTable îPersonsTable(oSession);
	if (!îPersonsTable.DeleteWhereID(lID))
	{
		pDatabaseConnector->AbortTransactionAndCloseSession();
		return false;
	}

	oSession.Commit();
	pDatabaseConnector->CloseSession();
	return true;
}

bool CPersonsData::UpdatePersonAndPhoneNumbers(const PERSONS& recPersons, CPhoneNumbersArray& oModifiedPhoneNumbersArray)
{
	CPhoneNumbersArray oPhoneNumbersArray;
	if (!SelectAllPhoneNumbersByPersonId(recPersons.lID, oPhoneNumbersArray))
		return false;

	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();
	if (!pDatabaseConnector->OpenSession())
		return false;

	CSession oSession = pDatabaseConnector->GetSession();
	if (oSession.StartTransaction()!= S_OK)
		return false;

	CPersonsTable îPersonsTable(oSession);
	if (!îPersonsTable.UpdateWhereID(recPersons.lID, recPersons))
	{
		pDatabaseConnector->AbortTransactionAndCloseSession();
		return false;
	}

	for (INT_PTR i = 0; i < oPhoneNumbersArray.GetCount(); i++)
	{
		PHONE_NUMBERS* pCurrentOriginalPhoneNumber = oPhoneNumbersArray.GetAt(i);
		if (pCurrentOriginalPhoneNumber == NULL)
			continue;
		if (!UpdatePhoneNumbers(*pCurrentOriginalPhoneNumber, oModifiedPhoneNumbersArray))
		{
			pDatabaseConnector->AbortTransactionAndCloseSession();
			return false;
		}
	}
	if (!InsertPhoneNumbers(oModifiedPhoneNumbersArray))
	{
		pDatabaseConnector->AbortTransactionAndCloseSession();
		return false;
	}

	oSession.Commit();
	pDatabaseConnector->CloseSession();
	return true;
}
bool CPersonsData::InsertPhoneNumbers(CPhoneNumbersArray& oPhoneNumbersArray)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();
	CPhoneNumbersTable oPhoneNumbersTable(pDatabaseConnector->GetSession());

	for (INT_PTR i = 0; i < oPhoneNumbersArray.GetCount(); i++)
	{
		PHONE_NUMBERS* pCurrentPhoneNumber = oPhoneNumbersArray.GetAt(i);
		if (pCurrentPhoneNumber != NULL)
			if (!oPhoneNumbersTable.InsertRecord(*pCurrentPhoneNumber))
				return false;
	}
	return true;
}

bool CPersonsData::UpdatePhoneNumbers(PHONE_NUMBERS& pCurrentOriginalPhoneNumber,CPhoneNumbersArray& oModifiedPhoneNumbersArray)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();
	CPhoneNumbersTable oPhoneNumbersTable(pDatabaseConnector->GetSession());

	bool bFound = false;
	for (INT_PTR s = 0; s < oModifiedPhoneNumbersArray.GetCount(); s++)
	{
		PHONE_NUMBERS* pCurrentModifiedPhoneNumber = oModifiedPhoneNumbersArray.GetAt(s);
		if (pCurrentModifiedPhoneNumber == NULL)
			continue;

		if (pCurrentOriginalPhoneNumber.lID == pCurrentModifiedPhoneNumber->lID)
		{
			if (ComparePhoneNumbers(*pCurrentModifiedPhoneNumber, pCurrentOriginalPhoneNumber))
				if (!oPhoneNumbersTable.UpdateWhereID(pCurrentModifiedPhoneNumber->lID, *pCurrentModifiedPhoneNumber))
					return false;
			oModifiedPhoneNumbersArray.RemoveAt(s);
			bFound= true;
			break;
		}
	}
	if (!bFound)
	{
		if (!oPhoneNumbersTable.DeleteWhereID(pCurrentOriginalPhoneNumber.lID))
		{
			return false;
		}
	}
	return true;
}

bool CPersonsData::ComparePhoneNumbers(PHONE_NUMBERS& oComparedPhoneNumber, PHONE_NUMBERS& oPhoneNumberComparator)
{
	if (oPhoneNumberComparator.lPhoneTypeId != oComparedPhoneNumber.lPhoneTypeId)
		return true;

	if (_tcscmp(oPhoneNumberComparator.szPhoneNumber, oComparedPhoneNumber.szPhoneNumber) != 0)
		return true;

	return false;
}
