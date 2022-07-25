#pragma once

#include <atldbcli.h>
#include <iostream>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include "Structures.h"
#include "CSelfClearingTypedPtrArray.h"

template<class T>
class CTable
{

private:
	/// <summary>
	///  Функция която отваря сесия и връзка към базата.
	/// </summary>
	bool OpenDbConnectionAndSession();

	/// <summary>
	///  Функция която създава рол-сет.
	/// </summary>
	CDBPropSet GetDBPropSet() const;

	/// <summary>
	///  Функция която създава рол-сет предназначен за модифициране на данни.
	/// </summary>
	CDBPropSet GetModifyDBPropSet() const;

	/// <summary>
	///  Функция която изпълнява дадена заявка към отворена връзка.
	/// </summary>
	/// <param name="strQuery">Обект съдържащ текущата заявка.</param> 
	/// <param name="nQueryAccessor">
		///Целочислено число което определя дали ще
		/// се модифицират данните или не. 0 - не модофицра / 1 модифицира.
	/// </param>  
	bool ExecuteQuery(const CString& strQuery, const int nQueryAccessor);

	/// <summary>
	///  Функция която затваря връзката към базата.
	/// </summary>
	void CloseDbConnectionAndSession();

	/// <summary>
	///  Функция която извежда съобщение при неуспешен опит за прочитане на резултат от заявка.
	/// </summary>
	/// <param name="hResult">Обект съдържащ съобщението на възникналата грешка.</param> 
	/// <param name="strErrorMessage">Обект който съдържа подробно разяснение за текущата грешка.</param>  
	/// <param name="strQuery">Обект който съдържа текущата заявка.</param> 
	void ShowErrorMessage(const LPCSTR strErrorMessage, const CString& strQuery = NULL);

	// Overrides
	// -------------

	// Members
	// -------------
	CDataSource m_oDataSource;
	CSession m_oSession;
};

