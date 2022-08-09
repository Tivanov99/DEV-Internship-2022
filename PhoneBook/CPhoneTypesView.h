#pragma once
#include "CPhoneTypesDocument.h"
class CPhoneTypesView :public CListView
{
protected: // create from serialization only
	CPhoneTypesView() noexcept;
	DECLARE_DYNCREATE(CPhoneTypesView)

	// Attributes
public:
	/// <summary>����� �������� ���� ����� �� �������� ������������ �� ������ �����.</summary>
	/// <returns>�������� �� ���������.</returns>
	CPhoneTypesDocument* GetDocument() const;

	//Methods
	//-------------
private:
	/// <summary>������� ����� ������� ������ ���������� �� ���������.</summary>
	/// <param name="�ListCtrl">���� �������� � ����� �� �� �������� �������.</param>
	/// <param name="oCitiesArray">����� �������� ������ ������ �� ��������� ��������� �� ������.</param>
	void FillView();
	/// <summary>����� ������� ������ ������ ��� �������� ���� �������� ���� ��������.</summary>
	/// <param name="�ListCtrl">���� �������� ��� ����� �� ����� �������� ��������.</param>
	void AddColumns(CListCtrl& �ListCtrl);
	/// <summary>����� �������� ������� � 'item data' ��� ���������� �� ������ � CListCtrl.</summary>
	/// <returns></returns>
	PHONE_TYPES* GetSelectedRecordItemData();
	/// <summary>������ ���� ���� ���������� � ������� ����� ����� �� ��� (-1 ������ �� � �������� �� ���� ���� �� ��������,� ����� ���� ������� � ��������������� ���������, �  �������� ������ ����� �� ���).</summary>
	/// <returns>����� �� ��� � ��������� -1 �� N</returns>
	const int GetSelectedRowNumber();
	/// <summary>������ ��� ����� ��� ���� ����������.</summary>
	/// <param name="pPhoneType">������� ������������� ��� �����</param>
	void InsertNewRecordToCListCtrl(PHONE_TYPES* pPhoneType);
	/// <summary>����������� ������ ����� �� ���������� � ������� �� ���� ����������.</summary>
	void ConfigurateCListCtrl();
	/// <summary>������� ������� ��������� � ���� �� ����� ����� � ��� ����������.</summary>
	/// <param name="pPhoneType">���������� ����� ������� ������ ���������.</param>
	void UpdateRecord(PHONE_TYPES& pPhoneType);
	// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;
protected:
	/// <summary>����� ��������� ������ ����� �� CListCtrl ��� ������������ �� ����������.</summary>
	virtual void OnInitialUpdate(); // called first time after construct
// Implementation
public:
	virtual ~CPhoneTypesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	/// <summary>������� ����������� ����� ���� �� �������.</summary>
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	/// <summary>������� ����� �� ����� �� ��������������� �� ������������ ����.</summary>
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

private:
	///// <summary>������� ������� ����� ��� ����� ���� ����� ����� ��� view-�� � 'Delete' �� ������������ ����.</summary>
	//afx_msg void OnContextMenuDelete();
	///// <summary>��� ����� ���� ����� ����� ������� �������� �������� �������� � �������� ����� ����� ���������� �� ��������.</summary>
	//afx_msg void OnContextMenuEdit();
	///// <summary>��� ����� ���� ��� �������� ���� � �������� ��� � 'InsertRecord' �� ������������ ���� ������� �������� �������� � ����� �� ����� ��������� ������� �� ������.</summary>
	//afx_msg void OnContextMenuInsert();
	///// <summary>��� ����� ���� ����� ����� ������� �������� �������� �������� � �������� �����.</summary>
	//afx_msg void OnEditContextReadData();
public:
	afx_msg void OnEditContextReadData();
	afx_msg void OnEditContextEdit();
	afx_msg void OnEditContextDelete();
	afx_msg void OnEditContextInsert();
};

