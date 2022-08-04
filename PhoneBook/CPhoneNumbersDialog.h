#pragma once
#include "afxdialogex.h"
#include "Structures.h"


// CPhoneNumbersDialog dialog

class CPhoneNumbersDialog : public CDialog
{
	DECLARE_DYNAMIC(CPhoneNumbersDialog)

	//Constructor/Destructor
	//-----------------
public:
	CPhoneNumbersDialog(PHONE_NUMBERS& recPhoneNumber,CPhoneTypesArray& oPhonetypesArray, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPhoneNumbersDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHONE_NUMBERS_DIALOG };
#endif

	//Methods
	//-----------------
private:
	void FillInputFileds();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	//Overrides
	//-----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	/// <summary>
	///���������� ���������� �������� ��� ���������� � ������� ������ ����� �� ��������� ����� � ��������; 
	/// </summary>
	/// <returns></returns>
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	//Members
	//-----------------
private:
	/// <summary>
	/// ������ �������� ����� ������������� ��������� �����.
	/// </summary>
	PHONE_NUMBERS& m_recPhoneNumber;

	/// <summary>
	/// ������ �������� ������ ������ ��������� �����
	/// </summary>
	CPhoneTypesArray& m_oPhonetypesArray;

	/// <summary>
	/// ������ ������������� ������ ���� �� ����� ��������� ����� � �������.
	/// </summary>
	CComboBox m_cmbPhoneTypes;

	/// <summary>
	/// ������ ������������� �������� ���� �� ��������� ����� � �������.
	/// </summary>
	CEdit m_edbPhoneNumber;
};
