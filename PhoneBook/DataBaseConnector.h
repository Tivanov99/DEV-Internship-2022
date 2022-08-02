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

	static DataBaseConnector* GetInstance();

	// Members
	// -------------
private:
	CDataSource m_oDataSource;
	CSession m_oSession;
};

