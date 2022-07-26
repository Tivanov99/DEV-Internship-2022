#pragma once
#include "pch.h"
#include "CBaseTable.h"

template <class T>

CBaseTable< T>::CBaseTable()
{};
template <class T>
CBaseTable<T>::~CBaseTable()
{};

template <class T>
CDBPropSet CBaseTable<T>::GetDBPropSet() const
{
	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-6RL5K65"));	// сървър
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("PhoneBook"));	// база данни
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));

	return oDBPropSet;
};

template <class T>
bool CBaseTable< T>::OpenDbConnectionAndSession()
{
	CDBPropSet& oDBPropSet = GetDBPropSet();

	// Свързваме се към базата данни
	HRESULT hResult = m_oDataSource.Open(_T("SQLOLEDB"), &oDBPropSet);

	//Отваряме връзка към дб
	if (hResult != S_OK)
	{
		ShowErrorMessage(lpszUnableToConnectServer, NULL);
		return false;
	}

	// Отваряме сесия
	hResult = m_oSession.Open(m_oDataSource);
	if (hResult!=S_OK)
	{
		ShowErrorMessage(lpszUnableToOpenSession,NULL);
		m_oDataSource.Close();
		return false;
	}
	return true;
};

template <class T>
CDBPropSet CBaseTable< T>::GetModifyDBPropSet() const
{
	CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
	oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
	oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	return oUpdateDBPropSet;
};

template <class T>
void CBaseTable<T>::ShowErrorMessage(const LPCSTR strErrorMessage, const CString& strQuery)
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