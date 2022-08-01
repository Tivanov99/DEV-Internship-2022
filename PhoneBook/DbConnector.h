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

