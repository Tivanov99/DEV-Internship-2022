#pragma once
#include <atldbcli.h>
class DbConnector
{
	// Constants
	// ----------------

	static const LPCSTR lpszUnableToConnectServer;
	static const LPCSTR lpszUnableToOpenSession;

	// Constructor / Destructor
	// ----------------
public:
	DbConnector();
	~DbConnector();

	// Methods
	// ----------------
public:
	/// <summary>
	///  ������� ����� ������� ���-���.
	/// </summary>
	CDBPropSet GetDBPropSet() const;

	/// <summary>
	///  ������� ����� ������ ����� � ������ ��� ������.
	/// </summary>
	bool OpenDbConnectionAndSession();

	/// <summary>
	///  ������� ����� ������� �������� ��� ������.
	/// </summary>
	void  CloseDbConnectionAndSession();

	/// <summary>
	/// Getter
	/// </summary>
	CSession& GetSession();

	// Members
	// -------------
private:
	CDataSource m_oDataSource;
	CSession m_oSession;
};

