#pragma once
#include "Structures.h"
#include "DialogWindowEnumeration.h"
#include "TextDataValidator.h"
#include <map>
using namespace std;




class CPersonsDialog : public CDialog
{
	//Constants
	// ----------------
	DECLARE_DYNAMIC(CPersonsDialog)

public:
	CPersonsDialog(DialogWindowActions eOperations, PERSONS& recPerson, CCitiesArray& oCitiesArray,
		CPhoneNumbersArray& oPhoneNumbersArray,  map<long, PHONE_TYPES*>& oMap, CWnd* pParent = nullptr);  // standard constructor
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
	void UpdateListCtrlRecord();

	PHONE_NUMBERS* GetSelectedRecordItemData();

	void ManageContextMenuItems(CCmdUI* pCmdUI);

	/// <summary>
	/// ������� ������ ������ ������ � ������� ������ �� 'm_recPerson'.
	/// </summary>
	void FillPersonDataFields();

	/// <summary>
	/// ������� 'm_cmbCitiesNames' � ������ ������� ������ ���� �������� 'oCitiesArray' ��� ����������� �� �������.
	/// </summary>
	void FillCitiesComboBox();

	/// <summary>
	/// ������� 'm_lscPersonPhoneNumbers' � ������ ��������� ������ ������ ���� �������� 'oCitiesArray' ��� ����������� �� �������.
	/// </summary>
	void FillPhoneNumbers();

	/// <summary>
	/// ������ ��������� � 'm_eOperation' ������ ��� �� ���������.
	/// </summary>
	void SetDialogTitle();

	void ConfiguratePhoneNumbersLsc();

	// Overrides
	// ----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	/// <summary>
	///���������� ���������� �������� ��� ���������� � ������� ������ ����� �� ��������� ����� � ��������; 
	/// </summary>
	/// <returns></returns>
	virtual BOOL OnInitDialog();

	/// <summary>
	/// ������� �� ��� ������� �� ������ '��'.
	/// </summary>
	virtual void OnOK();

	// Members
	// ----------------
private:

	/// <summary>
	/// ������ �������� ������ ��������� ������ �� �������� Person.
	/// </summary>
	CPhoneNumbersArray& m_oPhoneNumbersArray;

	/// <summary>
	/// ������ �������� ������� ����� ID-�� �� ������ ������ ��������� ������ � �������� ��������� �� ������.
	/// </summary>
	 map<long, PHONE_TYPES*>& m_oMap;

	/// <summary>
	/// ���������� ��� ������� ����� ��� ����������� �� �������.
	/// </summary>
	PERSONS& m_recPerson;

	/// <summary>
	/// ���������� ��� ������� �����  ��� ����������� �� ������� ����� ������� ������ �������.
	/// </summary>
	CCitiesArray& m_oCitiesArray;

	/// <summary>
	/// ������ �������� ����� �� �������� �������� ������� ���� �������� ��� ����������� �� �������.
	/// </summary>
	DialogWindowActions m_eOperation;

	/// <summary>
	/// ������ ��������� �� �������� ���� ��������� ����� �� ��������.
	/// </summary>
	CEdit m_edbPersonFirstName;

	/// <summary>
	/// ������ ��������� �� �������� ���� ��������� ��������� �� ��������.
	/// </summary>
	CEdit m_edbPersonSecondName;

	/// <summary>
	/// ������ ��������� �� �������� ���� ��������� ��������� ��� �� ��������.
	/// </summary>
	CEdit m_edbPersonLastName;

	/// <summary>
	/// ������ ��������� �� �������� ���� ��������� ���-�� �� ��������.
	/// </summary>
	CEdit m_edbPersonUcn;

	/// <summary>
	/// ������ ��������� �� �������� ���� � ������ ������� � ����.
	/// </summary>
	CComboBox m_cmbCitiesNames;

	/// <summary>
	/// ������ ��������� �� ������ ��������� ������ � ����.
	/// </summary>
	CListCtrl m_lscPersonPhoneNumbers;

	/// <summary>
	/// ������ ������� � ����������� �� ���������� ��� �������� ������� ������.
	/// </summary>
	TextDataValidator m_oTextValidator;
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnContextMenuEdit();
	afx_msg void OnContextMenuDelete();
	afx_msg void OnContextMenuReadData();
	afx_msg void OnContextMenuInsert();
};

