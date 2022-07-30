#pragma once
#include "Structures.h"
#include "afxdialogex.h"
#include "Structures.h"
#include "DataValidator.h"
#include "Enumerations.h"
#include "DialogWindowEnumeration.h"
#include "../../ListCtrl/ComboListCtrl.h"


class CPersonsDialog : public CDialog
{
	//Constants
	// ----------------
	DECLARE_DYNAMIC(CPersonsDialog)

public:
	CPersonsDialog(DialogWindowActions eOperations, PERSONS& recPerson,CCitiesArray& oCitiesArray, CWnd* pParent = nullptr);  // standard constructor
	virtual ~CPersonsDialog();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSONS_DIALOG };
#endif
	DECLARE_MESSAGE_MAP()

private:
	/// <summary>
	/// ������� ������ ������ ������ � ������� ������ �� 'm_recPerson'.
	/// </summary>
	void FillingInputFields();

	/// <summary>
	/// ������ ��������� � 'm_eOperation' ������ ��� �� ���������.
	/// </summary>
	void SetDialogTitle();

	/*/// <summary>
	/// ����� ��������� �������� �� ������ �� �������� ���.
	/// </summary>
	/// <returns>����� ��������� �������� � ������ �� �������� ���.</returns>
	long GetPostalCodeFromInputFiled();

	/// <summary>
	/// ������ ��������� ��������� � �������� �� ������� ����� ������� �� ���������.
	/// </summary>
	void SetDataToRecord();*/
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
	/// ���������� ��� ������� ����� ��� ����������� �� �������.
	/// </summary>
	PERSONS& m_recPerson;

	CCitiesArray& m_oCitiesArray;

	/// <summary>
	/// ������ �������� ����� �� �������� �������� ������� ���� �������� ��� ����������� �� �������.
	/// </summary>
	DialogWindowActions m_eOperation;

	/// <summary>
	/// ������ �������� ������ �� ���������� �� ���������� � ���������� ������.
	/// </summary>
	DataValidator m_oDataValidator;

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
};

