#pragma once
#include "PersonsDocument.h"


class CPersonsView :public CListView
{
protected: // create from serialization only
	CPersonsView() noexcept;
	DECLARE_DYNCREATE(CPersonsView)

	// Attributes
public:
	/// <summary>����� �������� ���� ����� �� ��������� ������������ �� ������ �����.</summary>
	CPersonsDocument* GetDocument() const;

	//Methods
private:
	/// <summary>������� ����� �������� ��� ����� �� ������������ ���� ���� �� ���� ���������� ��� ���� �� ����� �����.</summary>
	void ManageContextMenuItems(CCmdUI* pCmdUI);
	/// <summary>������� ����� ������� ������ ���������� �� ������.</summary>
	void FillView();
	/// <summary>����� ������� ������ ������ ��� �������� ���� �������� ���� ��������.</summary>
	void AddColumns();
	/// <summary>����� �������� ������� � 'item data' ��� ���������� �� ������ � CListCtrl.</summary>
	PERSONS* GetSelectedRecordItemData();
	/// <summary>������ ���� ���� ���������� � ������� ����� ����� �� ��� (-1 ������ �� � �������� �� ���� ���� �� ��������,� ����� ���� ������� � ��������������� ���������, �  �������� ������ ����� �� ���).</summary>
	const int GetSelectedRowNumber();
	/// <summary>������ ��� ����� ��� ���� ����������.</summary>
	/// <param name="pPerson">������� ������������� ��� �����</param>
	void InsertNewRecordToCListCtrl(PERSONS* pPerson);

	void UpdateRecord(long lID);
	/// <summary>����������� ������ ����� �� ���������� � ������� �� ���� ����������.</summary>
	void ConfigurateCListCtrl();
	
	// Overrides
	//----------------
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;
protected:
	/// <summary>����� ��������� ������ ����� �� CListCtrl ��� ������������ �� ����������.</summary>
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CPersonsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	// Generated message map functions
protected:
	/// <summary>������� ����� �� ����� �� ��������������� �� ������������ ����.</summary>
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	/// <summary>������� ������� ����� ��� ����� ���� ����� ����� ��� view-�� � 'Delete' �� ������������ ����.</summary>
	afx_msg void OnContextMenuDelete();
	/// <summary>��� ����� ���� ����� ����� ������� �������� �������� �������� � �������� �����.</summary>
	afx_msg void OnEditContextReadData();
	/// <summary>��� ����� ���� ��� �������� ���� � �������� ��� � 'InsertRecord' �� ������������ ���� ������� �������� �������� � ����� �� ����� ��������� ������� �� ������.</summary>
	afx_msg void OnContextMenuInsert();
	/// <summary>��� ����� ���� ����� ����� ������� �������� �������� �������� � �������� ����� ����� ���������� �� ��������.</summary>
	afx_msg void OnContextMenuEdit();
};
