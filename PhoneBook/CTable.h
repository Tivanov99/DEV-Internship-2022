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
	///  ������� ����� ������ ����� � ������ ��� ������.
	/// </summary>
	bool OpenDbConnectionAndSession();

	/// <summary>
	///  ������� ����� ������� ���-���.
	/// </summary>
	CDBPropSet GetDBPropSet() const;

	/// <summary>
	///  ������� ����� ������� ���-��� ������������ �� ������������ �� �����.
	/// </summary>
	CDBPropSet GetModifyDBPropSet() const;

	/// <summary>
	///  ������� ����� ��������� ������ ������ ��� �������� ������.
	/// </summary>
	/// <param name="strQuery">����� �������� �������� ������.</param> 
	/// <param name="nQueryAccessor">
		///����������� ����� ����� �������� ���� ��
		/// �� ����������� ������� ��� ��. 0 - �� ��������� / 1 ����������.
	/// </param>  
	bool ExecuteQuery(const CString& strQuery, const int nQueryAccessor);

	/// <summary>
	///  ������� ����� ������� �������� ��� ������.
	/// </summary>
	void CloseDbConnectionAndSession();

	/// <summary>
	///  ������� ����� ������� ��������� ��� ��������� ���� �� ��������� �� �������� �� ������.
	/// </summary>
	/// <param name="hResult">����� �������� ����������� �� ������������ ������.</param> 
	/// <param name="strErrorMessage">����� ����� ������� �������� ���������� �� �������� ������.</param>  
	/// <param name="strQuery">����� ����� ������� �������� ������.</param> 
	void ShowErrorMessage(const LPCSTR strErrorMessage, const CString& strQuery = NULL);

	// Overrides
	// -------------

	// Members
	// -------------
	CDataSource m_oDataSource;
	CSession m_oSession;
};

