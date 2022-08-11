#pragma once
#include <atldbcli.h>

class DataBaseConnector
{
	static DataBaseConnector* m_pInstance;
	
	// Constants
	// ----------------
private:

	static const LPCSTR lpszUnableToConnectServer;
	static const LPCSTR lpszUnableToOpenSession;

	// Constructor / Destructor
	// ----------------
private:
	DataBaseConnector();
	~DataBaseConnector();

	// Methods
	// ----------------
public:
	/// <summary>������� ����� ������� ���-���.</summary>
	bool GetDBPropSet();
	/// <summary>������� ����� ������ ����� � ������ ��� ������.</summary>
	bool OpenDbConnection();
	/// <summary>������� ����� ������� �������� ��� ������.</summary>
	void  CloseDbConnection();
	/// <summary> Getter</summary>
	CSession& GetSession();
	/// <summary>����� ������ ��������� �� ���� ����</summary>
	static DataBaseConnector* GetInstance();
	/// <summary>�������� �� �����.</summary>
	bool OpenSession();
	/// <summary>������� ����� ������� �������.</summary>
	void CloseSession();
	/// <summary>������� ����� ������� ������� � �������� ������������.</summary>
	void AbortTransactionAndCloseSession();
	// Members
	// -------------
private:
	/// <summary>������ ���� ����� ����� ������ �� ��������������. </summary>
	CDataSource m_oDataSource;
	/// <summary>������ �������� ������� ����� � ����� ��� �������� ��� ������.</summary>
	CSession m_oSession;

	CDBPropSet m_oDbPropSet;
};

