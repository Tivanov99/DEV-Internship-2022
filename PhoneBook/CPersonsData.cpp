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

	CPersonsTable �PersonsTable(pDatabaseConnector->GetSession());
	if (!�PersonsTable.SelectAll(oPersonsArray))
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

	CPersonsTable �PersonsTable(pDatabaseConnector->GetSession());

	if (!�PersonsTable.SelectWhereID(lID, recPersons))
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
	CPersonsTable �PersonsTable(oSession);

	if (!�PersonsTable.UpdateWhereID(lID, recPersons))
	{
		pDatabaseConnector->CloseSession();
		return false;
	}

	pDatabaseConnector->CloseSession();

	return true;
}

bool CPersonsData::InsertRecord(const PERSONS& recPersons)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CPersonsTable �PersonsTable(pDatabaseConnector->GetSession());

	if (!�PersonsTable.InsertRecord(recPersons))
	{
		pDatabaseConnector->CloseSession();
		return false;
	}

	pDatabaseConnector->CloseSession();

	return true;
}

bool CPersonsData::DeleteWhereID(const long lID)
{
	DataBaseConnector* pDatabaseConnector = DataBaseConnector::GetInstance();

	if (!pDatabaseConnector->OpenSession())
		return false;

	CPersonsTable �PersonsTable(pDatabaseConnector->GetSession());

	if (!�PersonsTable.DeleteWhereID(lID))
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
		oSession.Abort();
		pDatabaseConnector->CloseSession();
		return false;
	}

	CPhoneNumbersTable oPhoneNumbersTable(oSession);

	CString strSqlQuery;
	strSqlQuery.Format(SqlQueries::WherePersonID, lID);

	if (!oPhoneNumbersTable.DeleteBySpecificColumnWhereID(lID, strSqlQuery))
	{
		oSession.Abort();
		pDatabaseConnector->CloseSession();
		return false;
	}

	CPersonsTable �PersonsTable(oSession);
	if (!�PersonsTable.DeleteWhereID(lID))
	{
		oSession.Abort();
		pDatabaseConnector->CloseSession();
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

	if (oSession.StartTransaction() != S_OK)
		return false;

	CPersonsTable �PersonsTable(oSession);

	if (!�PersonsTable.UpdateWhereID(recPersons.lID, recPersons))
	{
		oSession.Abort();
		pDatabaseConnector->CloseSession();
		return false;
	}
	CPhoneNumbersTable oPhoneNumbersTable(oSession);

	for (INT_PTR i = 0; i < oPhoneNumbersArray.GetCount(); i++)
	{
		PHONE_NUMBERS* pCurrentOriginalPhoneNumber = oPhoneNumbersArray.GetAt(i);
		if (pCurrentOriginalPhoneNumber == NULL)
			continue;

		bool bFound = false;

		for (INT_PTR s = 0; s < oModifiedPhoneNumbersArray.GetCount(); s++)
		{
			PHONE_NUMBERS* pCurrentModifiedPhoneNumber = oModifiedPhoneNumbersArray.GetAt(i);
			if (pCurrentModifiedPhoneNumber == NULL)
				continue;

			if (pCurrentOriginalPhoneNumber->lID == pCurrentModifiedPhoneNumber->lID)
			{
				if (ComparePhoneNumbers(*pCurrentModifiedPhoneNumber, *pCurrentOriginalPhoneNumber))
					if (!oPhoneNumbersTable.UpdateWhereID(pCurrentModifiedPhoneNumber->lID, *pCurrentModifiedPhoneNumber))
					{
						oSession.Abort();
						pDatabaseConnector->CloseSession();
						return false;
					}
				bFound = true;
				oModifiedPhoneNumbersArray.RemoveAt(s);
				break;
			}
		}

		if (!bFound)
		{
			if (!oPhoneNumbersTable.DeleteWhereID(pCurrentOriginalPhoneNumber->lID))
			{
				oSession.Abort();
				pDatabaseConnector->CloseSession();
				return false;
			}
			continue;
		}
	}
	//Insert
	for (INT_PTR i = 0; i < oModifiedPhoneNumbersArray.GetCount(); i++)
	{
		PHONE_NUMBERS* pCurrentPhoneNumber = oModifiedPhoneNumbersArray.GetAt(i);
		if (pCurrentPhoneNumber != NULL)
			if (!oPhoneNumbersTable.InsertRecord(*pCurrentPhoneNumber))
			{
				oSession.Abort();
				pDatabaseConnector->CloseSession();
				return false;
			}
	}
	oSession.Commit();
	pDatabaseConnector->CloseSession();
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
