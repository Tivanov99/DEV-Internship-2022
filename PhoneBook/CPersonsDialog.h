#pragma once
#include "Structures.h"
#include "DialogWindowEnumeration.h"
#include "TextDataValidator.h"
#include <map>
#include "CSelfClearingMap.h"
using namespace std;




class CPersonsDialog : public CDialog
{
	//Constants
	// ----------------
	DECLARE_DYNAMIC(CPersonsDialog)

public:
	CPersonsDialog(DialogWindowActions eOperations, PERSONS& recPerson, CCitiesArray& oCitiesArray,
		CPhoneNumbersArray& oPhoneNumbersArray, CSelfClearingMap<long, PHONE_TYPES*>& oPhoneTypesMap, CWnd* pParent = nullptr);  // standard constructor
	virtual ~CPersonsDialog();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSONS_DIALOG };
#endif
	DECLARE_MESSAGE_MAP()

	// Methods
	// ----------------

public:
	void OnContextMenu(CWnd* /*pWnd*/, CPoint point);
private:
	/// <summary>������� ����� ����������� ���� ���������� ����� ������� ����������� ������.</summary>
	void UpdateListCtrlRecord();
	/// <summary>������� ����� ������ ��� ����� ��� ���� ���������� ����� ������� ����������� ������.</summary>
	/// <param name="pPhoneNumber">����� ����� �� ���� �������,</param>
	void InsertRecordToListCtrl(PHONE_NUMBERS* pPhoneNumber);
	/// <summary>������� ����� ����� item data �� ������� ����� �� ���� ����������.</summary>
	PHONE_NUMBERS* GetSelectedRecordItemData();
	/// <summary>������� ����� �������� ��� ������� �� ������������ ���� ���� �� ���� ����������.</summary>
	void ManageContextMenuItems(CCmdUI* pCmdUI);
	/// <summary>������� ������ ������ ������ � ������� ������ �� 'm_recPerson'.</summary>
	void FillPersonDataFields();
	/// <summary>������� 'm_cmbCitiesNames' � ������ ������� ������ ���� �������� 'oCitiesArray' ��� ����������� �� �������.</summary>
	void FillCitiesComboBox();
	/// <summary>������� 'm_lscPersonPhoneNumbers' � ������ ��������� ������ ������ ���� �������� 'oCitiesArray' ��� ����������� �� �������.</summary>
	void FillPhoneNumbers();
	/// <summary>������ ��������� � 'm_eOperation' ������ ��� �� ���������.</summary>
	void SetDialogTitle();
	/// <summary>������� ����� ����������� ���� ���������� � ����� �� �������� ������ ��������� ������.</summary>
	void ConfiguratePhoneNumbersLsc();

	// Overrides
	// ----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	/// <summary>���������� ���������� �������� ��� ���������� � ������� ������ ����� �� ��������� ����� � ��������; </summary>
	virtual BOOL OnInitDialog();
	/// <summary>������� �� ��� ������� �� ������ '��'.</summary>
	virtual void OnOK();

	// Members
	// ----------------
private:
	/// <summary>������ �������� ������ ��������� ������ �� �������� Person.</summary>
	CPhoneNumbersArray& m_oPhoneNumbersArray;
	/// <summary>������ �������� ������� ����� ID-�� �� ������ ������ ��������� ������ � �������� ��������� �� ������.</summary>
	CSelfClearingMap<long, PHONE_TYPES*>& m_oPhoneTypesMap;
	/// <summary>���������� ��� ������� ����� ��� ����������� �� �������.</summary>
	PERSONS& m_recPerson;
	/// <summary>���������� ��� ������� �����  ��� ����������� �� ������� ����� ������� ������ �������.</summary>
	CCitiesArray& m_oCitiesArray;
	/// <summary>������ �������� ����� �� �������� �������� ������� ���� �������� ��� ����������� �� �������.</summary>
	DialogWindowActions m_eOperation;
	/// <summary>������ ��������� �� �������� ���� ��������� ����� �� ��������.</summary>
	CEdit m_edbPersonFirstName;
	/// <summary>������ ��������� �� �������� ���� ��������� ��������� �� ��������.</summary>
	CEdit m_edbPersonSecondName;
	/// <summary>������ ��������� �� �������� ���� ��������� ��������� ��� �� ��������.</summary>
	CEdit m_edbPersonLastName;
	/// <summary>������ ��������� �� �������� ���� ��������� ���-�� �� ��������.</summary>
	CEdit m_edbPersonUcn;
	/// <summary>������ ��������� �� �������� ���� � ������ ������� � ����.</summary>
	CComboBox m_cmbCitiesNames;
	/// <summary> ������ ��������� �� ������ ��������� ������ � ����.</summary>
	CListCtrl m_lscPersonPhoneNumbers;
	/// <summary>������ ������� � ����������� �� ���������� ��� �������� ������� ������.</summary>
	TextDataValidator m_oTextValidator;
public:
	/// <summary>������� ��� ����������� �� ������ 'Cancel' � ���������� ��������.</summary>
	afx_msg void OnBnClickedCancel();
	/// <summary>������� ��� ���������� �� 'Edit' �� ������������ ���� ����� ���� ���������� �� �������� �� �����.</summary>
	afx_msg void OnContextMenuEdit();
	/// <summary>������� ��� ���������� �� 'Delete' �� ������������ ���� ����� ���� ���������� �� ��������� �� �����.</summary>
	afx_msg void OnContextMenuDelete();
	/// <summary>������� ��� ���������� �� 'Read data' �� ������������ ���� ����� ���� ���������� �� �������� �� �����.</summary>
	afx_msg void OnContextMenuReadData();
	/// <summary>������� ��� ���������� �� 'Insert' �� ������������ ���� ����� ���� ���������� �� �������� �� ��� �����.</summary>
	afx_msg void OnContextMenuInsert();
};

