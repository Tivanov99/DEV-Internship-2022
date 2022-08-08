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
	CDBPropSet GetDBPropSet() const;
	/// <summary>������� ����� ������ ����� � ������ ��� ������.</summary>
	bool OpenDbConnectionAndSession();
	/// <summary>������� ����� ������� �������� ��� ������.</summary>
	void  CloseDbConnectionAndSession();
	/// <summary> Getter</summary>
	CSession& GetSession();
	/// <summary>����� ������ ��������� �� ���� ����</summary>
	/// <returns>��������� �� ���� ����</returns>
	static DataBaseConnector* GetInstance();
	// Members
	// -------------
private:
	/// <summary>������ ���� ����� ����� ������ �� ��������������. </summary>
	CDataSource m_oDataSource;
	/// <summary>������ �������� ������� ����� � ����� ��� �������� ��� ������.</summary>
	CSession m_oSession;
};

