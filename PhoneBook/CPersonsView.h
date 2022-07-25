#pragma once
#include "CPersonsDocument.h"

class CPersonsView :public CListView
{
protected: // create from serialization only
	CPersonsView() noexcept;
	DECLARE_DYNCREATE(CPersonsView)

	// Attributes
public:
	/// <summary>
	/// ����� �������� ���� ����� �� ��������� ������������ �� ������ �����.
	/// </summary>
	/// <returns>�������� �� ���������.</returns>
	CPersonsDocument* GetDocument() const;

	//Methods
public:
	/// <summary>
	/// ������� ����� ������� ������ ���������� �� ���������.
	/// </summary>
	/// <param name="LSCCitiesList">���� �������� � ����� �� �� �������� �������.</param>
	/// <param name="oPersonsArray">����� �������� ������ ������ �� ��������� ��������� �� ������.</param>
	void FillView(CListCtrl& LSCCitiesList, const CSelfClearingTypedPtrArray<PERSONS>& oPersonsArray);

	/// <summary>
	/// ����� ������� ������ ������ ��� �������� ���� �������� ���� ��������.
	/// </summary>
	/// <param name="LSCCitiesList">���� �������� ��� ����� �� ����� �������� ��������.</param>
	void AddColumns(CListCtrl& LSCCitiesList);

};

