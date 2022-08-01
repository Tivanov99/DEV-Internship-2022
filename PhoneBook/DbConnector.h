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

public:
	// Methods
	// ----------------

	/// <summary>
	///  Функция която създава рол-сет.
	/// </summary>
	CDBPropSet GetDBPropSet() const;

	/// <summary>
	///  Функция която отваря сесия и връзка към базата.
	/// </summary>
	bool OpenDbConnectionAndSession();

	/// <summary>
	///  Функция която затваря връзката към базата.
	/// </summary>
	void  CloseDbConnectionAndSession();

	// Members
	// -------------
public:
	CDataSource m_oDataSource;
	CSession m_oSession;
};

