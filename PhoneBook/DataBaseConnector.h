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
	CDBPropSet GetDBPropSet() const;
	/// <summary>Функция която отваря сесия и връзка към базата.</summary>
	/// <returns>Според това дали успешно е извършено действието връща 'true' в провитен случай 'false'</returns>
	bool OpenDbConnection();
	/// <summary>Функция която затваря връзката към базата.</summary>
	void  CloseDbConnectionAndSession();
	/// <summary> Getter</summary>
	CSession& GetSession();
	/// <summary>Метод връщащ инстанция от този клас</summary>
	/// <returns>Инстанция от този клас</returns>
	static DataBaseConnector* GetInstance();
	/// <summary>
	/// Отваряне на сесия.
	/// </summary>
	/// <returns>Според това дали успешно е извършено действието връща 'true' в провитен случай 'false'</returns>
	bool OpenSession();
	// Members
	// -------------
private:
	/// <summary>Мембър чрез който имаме достъп до бизнеслогиката. </summary>
	CDataSource m_oDataSource;
	/// <summary>Мембър съдържащ сесията която е нужна при заявките към базата.</summary>
	CSession m_oSession;
};

