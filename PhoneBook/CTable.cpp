#include "pch.h"
#include "CTable.h"

void CTable<T>::CloseDbConnectionAndSession()
{
	Close();
	m_oSession.Close();
	m_oDataSource.Close();
};


void CTable<T>::ShowErrorMessage(const LPCSTR strErrorMessage, const CString& strQuery)
{
	CString strError;
	if (strQuery.GetString() != NULL)
	{
		strError.Format((CString)strErrorMessage, strQuery);
	}
	else
	{
		strError.Format((CString)strErrorMessage);
	}
	AfxMessageBox(strError);
}

CDBPropSet CTable<T>::GetDBPropSet()const
{
	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-6RL5K65"));	// сървър
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("PhoneBook"));	// база данни
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));

	return oDBPropSet;
}

CDBPropSet CTable<T>::GetModifyDBPropSet() const
{
	CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
	oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
	oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	return oUpdateDBPropSet;
}

bool CTable<T>::OpenDbConnectionAndSession()
{
	CDBPropSet& oDBPropSet = GetDBPropSet();

	// Свързваме се към базата данни
	HRESULT hResult = m_oDataSource.Open(_T("SQLOLEDB"), &oDBPropSet);

	//Отваряме връзка към дб
	if (FAILED(hResult))
	{
		AfxMessageBox((CString)lpszUnableToConnectServer, hResult);
		return false;
	}

	// Отваряме сесия
	hResult = m_oSession.Open(m_oDataSource);
	if (FAILED(hResult))
	{
		AfxMessageBox((CString)lpszUnableToOpenSession, hResult);
		m_oDataSource.Close();
		return false;
	}
	return true;
};

bool CTable<T>::ExecuteQuery(const CString& strQuery, const int nQueryAccessor)
{
	if (nQueryAccessor != NoneModifyColumnCode && nQueryAccessor != ModifyColumnCode)
	{
		ShowErrorMessage(lpszErrorInvalidQueryAcessor, strQuery);
		return false;
	}
	if (nQueryAccessor == NoneModifyColumnCode)
	{
		//изпълняваме команда
		if (FAILED(Open(m_oSession, strQuery)))
		{
			ShowErrorMessage(lpszErrorExecutingQuery, strQuery);
			return false;
		}
	}
	else if (nQueryAccessor == ModifyColumnCode)
	{
		//настройваме row-set
		CDBPropSet oUpdateDBPropSet = GetModifyDBPropSet();
		//изпълняваме команда
		if (FAILED(Open(m_oSession, strQuery, &oUpdateDBPropSet)))
		{
			ShowErrorMessage(lpszErrorExecutingQuery, strQuery);
			return false;
		}
	}
	return true;
}