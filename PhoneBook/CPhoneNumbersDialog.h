#pragma once
#include "afxdialogex.h"
#include "Structures.h"
#include <map>

using namespace std;


// CPhoneNumbersDialog dialog

class CPhoneNumbersDialog : public CDialog
{
	DECLARE_DYNAMIC(CPhoneNumbersDialog)

	//Constructor/Destructor
	//-----------------
public:
	CPhoneNumbersDialog(PHONE_NUMBERS& recPhoneNumber, map<long, PHONE_TYPES*>& oMap, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPhoneNumbersDialog();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHONE_NUMBERS_DIALOG };
#endif

	//Methods
	//-----------------
private:
	/// <summary>
	/// ������� ������ ������ � ������� �� ������ ����� � ������� ���� �������� 'recPhoneNumber' ��� ����������� �� �������.
	/// </summary>
	void FillInputFileds();
	/// <summary>
	/// ������� ����� ������� ������ �������� ����� ��� �������� ������ �� ������ 'm_recPhoneNumber' � ������� ��������� ��� ���� �� ������ 'Ok'.
	/// </summary>
	afx_msg void OnBnClickedOk();
	/// <summary>
	/// ������� ����� ������ ������ ��������� ������� � ������� ���������� �������� ��� ���� �� ������ 'Cancel'.
	/// </summary>
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
	/// ������ �������� ������� ����� ID-�� �� ������ ������ ��������� ������ � �������� ��������� �� ������.
	/// </summary>
	map<long, PHONE_TYPES*>& m_oPhoneTypesMap;

	/// <summary>
	/// ������ ������������� ������ ���� �� ����� ��������� ����� � �������.
	/// </summary>
	CComboBox m_cmbPhoneTypes;

	/// <summary>
	/// ������ ������������� �������� ���� �� ��������� ����� � �������.
	/// </summary>
	CEdit m_edbPhoneNumber;
};
