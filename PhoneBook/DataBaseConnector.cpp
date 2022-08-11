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

//TODO: Chech here.
CDBPropSet DataBaseConnector::GetDBPropSet() const
{
	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	if (!oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-6RL5K65"))) // ������
		return oDBPropSet;
	if (!oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI")))
		return oDBPropSet;
	if (!oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("PhoneBook")))// ���� �����
		return oDBPropSet;
	if (!oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false))
		return oDBPropSet;
	if (!oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L))
		return oDBPropSet;
	if (!oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4)))
		return oDBPropSet;
	return oDBPropSet;
};

bool DataBaseConnector::OpenDbConnection()
{
	CDBPropSet& oDBPropSet = GetDBPropSet();

	// ��������� �� ��� ������ �����
	HRESULT hResult = m_oDataSource.Open(_T("SQLOLEDB"), &oDBPropSet);

	//�������� ������ ��� ��
	if (hResult != S_OK)
	{
		ErrorMessageVisualizator::ShowErrorMessage(lpszUnableToConnectServer, NULL);
		return false;
	}

	return true;
};
bool DataBaseConnector::OpenSession()
{
	// �������� �����
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