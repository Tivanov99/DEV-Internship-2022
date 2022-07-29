#pragma once
#include "DialogWindowEnumeration.h"
#include "Structures.h"
#include "DataValidator.h"
class CPersonsDialog : public CDialog
{
	//Constants
	// ----------------
	DECLARE_DYNAMIC(CPersonsDialog)

public:
	CPersonsDialog(DialogWindowActions eOperations, PERSONS& recPerson, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPersonsDialog();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSONS_DIALOG };
#endif
	DECLARE_MESSAGE_MAP()

private:
	/// <summary>
	/// ������� ������ ������ ������ � ������� ������ �� 'm_recCity'.
	/// </summary>
	void FillingInputFields();

	/// <summary>
	/// ������ ��������� � 'm_eOperation' ������ ��� �� ��������� � �� ������ �� ������������� �� ����������.
	/// </summary>
	void SetDialogTitle();

	/// <summary>
	/// ����� ��������� �������� �� ������ �� �������� ���.
	/// </summary>
	/// <returns>����� ��������� �������� � ������ �� �������� ���.</returns>
	long GetPostalCodeFromInputFiled();

	/// <summary>
	/// ������ ��������� ��������� � �������� �� ������� ����� ������� �� ���������.
	/// </summary>
	void SetDataToRecord();
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

	/// <summary>
	/// ������ �������� ����� �� �������� �������� ������� ���� �������� ��� ����������� �� �������.
	/// </summary>
	DialogWindowActions m_eOperation;

	/// <summary>
	/// ������ �������� ������ �� ���������� �� ���������� � ���������� ������.
	/// </summary>
	DataValidator m_oDataValidator;
};

