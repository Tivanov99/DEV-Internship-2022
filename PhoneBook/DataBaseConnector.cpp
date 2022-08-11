#include "pch.h"
#include "DataBaseConnector.h"
#include "ErrorVisualizator.h"


const LPCSTR DataBaseConnector::lpszUnableToConnectServer = "Unable to connect to SQL Server database. Error: %d";
const LPCSTR DataBaseConnector::lpszUnableToOpenSession = "Unable to open session. Error: %d";

DataBaseConnector::DataBaseConnector() {};
DataBaseConnector :: ~DataBaseConnector() 
{
	m_pInstance = NULL;
	delete m_pInstance;
};

DataBaseConnector* DataBaseConnector::m_pInstance = NULL;

void DataBaseConnector::CloseDbConnection()
{
	m_oDataSource.Close();
};

bool DataBaseConnector::GetDBPropSet()
{
	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);

	if (!oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-6RL5K65")))// сървър
	{
		AfxMessageBox(_T("Failed to add 'DBPROP_INIT_DATASOURCE' property to CDBPropSet!"));
		return false;
	}
	if (!oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI")))
	{
		AfxMessageBox(_T("Failed to add 'DBPROP_AUTH_INTEGRATED' property to CDBPropSet!"));
		return false;
	}
	if (!oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("PhoneBook")))// база данни
	{
		AfxMessageBox(_T("Failed to add 'DBPROP_INIT_CATALOG' property to CDBPropSet!"));
		return false;
	}
	if (!oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false))
	{
		AfxMessageBox(_T("Failed to add 'DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO' property to CDBPropSet!"));
		return false;
	}
	if (!oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L))
	{
		AfxMessageBox(_T("Failed to add 'DBPROP_INIT_LCID' property to CDBPropSet!"));
		return false;
	}
	if (!oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4)))
	{
		AfxMessageBox(_T("Failed to add 'DBPROP_INIT_PROMPT' property to CDBPropSet!"));
		return false;
	}

	m_oDbPropSet = oDBPropSet;
	return true;
};

bool DataBaseConnector::OpenDbConnection()
{
	GetDBPropSet();

	// Свързваме се към базата данни
	HRESULT hResult = m_oDataSource.Open(_T("SQLOLEDB"), &m_oDbPropSet);

	//Отваряме връзка към дб
	if (hResult != S_OK)
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszUnableToConnectServer, NULL);
		return false;
	}

	return true;
};
bool DataBaseConnector::OpenSession()
{
	// Отваряме сесия
	if (m_oSession.Open(m_oDataSource) != S_OK)
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
void DataBaseConnector::CloseSession()
{
	m_oSession.Close();
}

void DataBaseConnector::AbortTransactionAndCloseSession()
{
	m_oSession.Abort();
	CloseSession();
}

DataBaseConnector* DataBaseConnector::GetInstance()
{
	if (!m_pInstance)
		m_pInstance = new DataBaseConnector;

	return m_pInstance;
}