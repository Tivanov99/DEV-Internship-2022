#pragma once
	
#include <atldbcli.h>
#include <iostream>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include "Structures.h"
#include "CBaseTable.h"


using namespace std;

//TODO: USE ENUMERATION

#define NoneModifyColumnCode 0
#define ModifyColumnCode 1

class CCityAccessor
{
protected:
	CCityAccessor()
	{};
	~CCityAccessor() {
	};
	CITIES m_recCITY;

	BEGIN_ACCESSOR_MAP(CCityAccessor, 2)
		BEGIN_ACCESSOR(NoneModifyColumnCode, true)
		COLUMN_ENTRY(1, m_recCITY.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(ModifyColumnCode, true)
		COLUMN_ENTRY(2, m_recCITY.lUpdateCounter)
		COLUMN_ENTRY(3, m_recCITY.szCITY_NAME)
		COLUMN_ENTRY(4, m_recCITY.szAREA_NAME)
		COLUMN_ENTRY(5, m_recCITY.lPOSTAL_CODE)
		END_ACCESSOR()
	END_ACCESSOR_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

/// <summary>���� �� ������ � ������� CITIES</summary>
class CCitiesTable : public CBaseTable<CITIES, CCityAccessor>
{
	// Constants
	// ----------------
//private:
//	static const LPCSTR lpszSelectAllById;
//	static const LPCSTR lpszSelectAll;   
//	static const LPCSTR lpszEmptySelect;
	

	// Constructor / Destructor
	// ----------------
public:
	CCitiesTable(CSession& oSession);
	~CCitiesTable();
	
//	// Methods
//	// -------------
//public:
//	/// <summary>
//	///  ������� ����� ���� ����� ������ �� ��������� "CITIES" � �� ������ � ������� ���� �������� �����.
//	/// </summary>
//	/// <param name="oCitiesArray">����� � ����� �� ����� �������� ������ ��������� �����.</param>
//	bool SelectAll(CCitiesArray& oCitiesArray) override;
//
//	/// <summary>
//	///  ������� ����� ���� ����� �� ��������� "CITIES" ����� ID �������� �� "lID" � �� ���������� � "recCities" ���������.
//	/// </summary>
//	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
//	/// <param name="recCities">���������� ����� �� ������� ��������� �� ���������</param>
//	bool SelectWhereID(const long lID, CITIES& recCities) override;
//
//	/// <summary>
//	///  ������� ����� ����� ������� �� ����� �� ��������� "CITIES" ����� ID �������� �� "lID" ���������,
//	///  � �� ������� ��������� �� ��������� "recCities" � ������ �������� �� ������.
//	/// </summary>
//	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
//	/// <param name="recCities">���������� ����� ������� ���� ����������� �����.</param>
//	bool UpdateWhereID(const long lID, const CITIES& recCities) override;
//
//	/// <summary>
//	///  ������� ����� ������ ����� ������� ���� �������� ��� ��������� "CITIES".
//	/// </summary>
//	/// <param name="recCities">���������� ����� ������� ��� �����.</param>
//	bool InsertRecord(const CITIES& recCities) override;
//
//	/// <summary>
//	///  ������� ����� ������� ����� �� ��������� "CITIES" ����� �������� �� "lID" ���������.
//	/// </summary>
//	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ����� � ������.</param>
//	bool DeleteWhereID(const long lID) override;
//
//private:
//	/// <summary>
//	///  ������� ����� ��������� ������ ������ ��� �������� ������.
//	/// </summary>
//	/// <param name="strQuery">����� �������� �������� ������.</param> 
//	/// <param name="nQueryAccessor">
//		///����������� ����� ����� �������� ���� ��
//		/// �� ����������� ������� ��� ��. 0 - �� ��������� / 1 ����������.
//	/// </param>  
//	bool ExecuteQuery(const CString& strQuery, AccessorTypes eQueryAccessor) override;
//
//	/// <summary>
//	/// ������� row-set.
//	/// </summary>
//	void virtual CloseRowSet() override;
};
