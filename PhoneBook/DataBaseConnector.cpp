#include "pch.h"
#include "DataBaseConnector.h"
#include "ErrorVisualizator.h"


const LPCSTR DataBaseConnector::lpszUnableToConnectServer = "Unable to connect to SQL Server database. Error: %d";
const LPCSTR DataBaseConnector::lpszUnableToOpenSession = "Unable to open session. Error: %d";

DataBaseConnector::DataBaseConnector() {};
DataBaseConnector :: ~DataBaseConnector() {};

void DataBaseConnector::CloseDbConnectionAndSession()
{
	m_oSession.Close();
	m_oDataSource.Close();
};


CDBPropSet DataBaseConnector::GetDBPropSet() const
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

bool DataBaseConnector::OpenDbConnectionAndSession()
{
	CDBPropSet& oDBPropSet = GetDBPropSet();

	// Свързваме се към базата данни
	HRESULT hResult = m_oDataSource.Open(_T("SQLOLEDB"), &oDBPropSet);

	//Отваряме връзка към дб
	if (hResult != S_OK)
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszUnableToConnectServer, NULL);
		return false;
	}

	// Отваряме сесия
	hResult = m_oSession.Open(m_oDataSource);
	if (hResult != S_OK)
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszUnableToOpenSession, NULL);
		m_oDataSource.Close();
		return false;
	}
	return true;
};

CSession& DataBaseConnector::GetSession()
{
	return m_oSession;
}

DataBaseConnector* DataBaseConnector::GetInstance()
{
	if (!m_pInstance)
		m_pInstance = new DataBaseConnector;

	return m_pInstance;
}