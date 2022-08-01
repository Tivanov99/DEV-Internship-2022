#include "pch.h"
#include "DbConnector.h"
#include "ErrorVisualizator.h"



const LPCSTR DbConnector::lpszUnableToConnectServer = "Unable to connect to SQL Server database. Error: %d";
const LPCSTR DbConnector::lpszUnableToOpenSession = "Unable to open session. Error: %d";

DbConnector::DbConnector() {};
DbConnector :: ~DbConnector() {};

void DbConnector::CloseDbConnectionAndSession()
{
	m_oSession.Close();
	m_oDataSource.Close();
};


CDBPropSet DbConnector::GetDBPropSet() const
{
	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-6RL5K65"));	// ������
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("PhoneBook"));	// ���� �����
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));

	return oDBPropSet;
};

bool DbConnector::OpenDbConnectionAndSession()
{
	CDBPropSet& oDBPropSet = GetDBPropSet();

	// ��������� �� ��� ������ �����
	HRESULT hResult = m_oDataSource.Open(_T("SQLOLEDB"), &oDBPropSet);

	//�������� ������ ��� ��
	if (hResult != S_OK)
	{
		ErrorVisualizator::ShowErrorMessage(lpszUnableToConnectServer, NULL);
		return false;
	}

	// �������� �����
	hResult = m_oSession.Open(m_oDataSource);
	if (hResult != S_OK)
	{
		ErrorVisualizator::ShowErrorMessage(lpszUnableToOpenSession, NULL);
		m_oDataSource.Close();
		return false;
	}
	return true;
};