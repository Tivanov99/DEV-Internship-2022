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
	/// <summary>Функция която създава рол-сет.</summary>
	bool GetDBPropSet();
	/// <summary>Функция която отваря сесия и връзка към базата.</summary>
	bool OpenDbConnection();
	/// <summary>Функция която затваря връзката към базата.</summary>
	void  CloseDbConnection();
	/// <summary> Getter</summary>
	CSession& GetSession();
	/// <summary>Метод връщащ инстанция от този клас</summary>
	static DataBaseConnector* GetInstance();
	/// <summary>Отваряне на сесия.</summary>
	bool OpenSession();
	/// <summary>Функция която затваря сесията.</summary>
	void CloseSession();
	/// <summary>Функция която затваря сесията и абортира транзакцията.</summary>
	void AbortTransactionAndCloseSession();
	// Members
	// -------------
private:
	/// <summary>Мембър чрез който имаме достъп до бизнеслогиката. </summary>
	CDataSource m_oDataSource;
	/// <summary>Мембър съдържащ сесията която е нужна при заявките към базата.</summary>
	CSession m_oSession;

	CDBPropSet m_oDbPropSet;
};

