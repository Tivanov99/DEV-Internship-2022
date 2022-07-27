#pragma once
#include "afxdialogex.h"
#include "Structures.h"
#include "Enumerations.h"


// CCitiesDialog dialog

class CCitiesDialog : public CDialog
{
	//Constants
	// ----------------
	DECLARE_DYNAMIC(CCitiesDialog)

	// Constructor / Destructor
	// ----------------
public:
	CCitiesDialog(ContextMenuOperations eOperations, CITIES& recCity, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CCitiesDialog();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CITIES_DIALOG };
#endif
	DECLARE_MESSAGE_MAP()

	// Methods
	// ----------------
private:
	/// <summary>
	/// ������� ������ ������ ������ � ������� ������ �� 'm_recCity'.
	/// </summary>
	void FillingInputFields();

	/// <summary>
	/// ������ ��������� � 'm_eOperations' ������ ��� �� ��������� � �� ������ �� ������������� �� ����������.
	/// </summary>
	void SetDialogTitle();

	/// <summary>
	/// �������� �������� ����� ������ �� ���������� �� ������ ���� �������� ���� ��������, � ��� ���������� �� ������ ���������� � ����� ���������� ���������.
	/// </summary>
	/// <param name="oEdit">���������� �� ���������� ������������ ������ ����.</param>
	/// <param name="nMinLenght">���������� ��������� ������� �� ���������� ����.</param>
	/// <returns>��������� ��������� ����������� ������, ��� ��� ������.</returns>
	CString ValidateTextData(const CEdit& oEdit, const int nMinLenght);

	/// <summary>
	/// �������� '�������� ���' ��� ��������� �� �����.
	/// </summary>
	/// <returns>���� 'true' ��� 'false' ������ ���� ���� ����� � �������.</returns>
	bool ValidatePostalCode();
	bool CheckForSymbols(const CString& strValue) const;
	long GetPostalCodeFromInputFiled();
	void SetDataToRecord();
	// Overrides
	// ----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	// Members
	// ----------------
private:
	/// <summary>
	/// ���������� ��� ������� ����� ��� ����������� �� �������.
	/// </summary>
	CITIES& m_recCity;

	/// <summary>
	/// ������ ��������� �� �������� ���� ��������� ����� �� ������.
	/// </summary>
	CEdit m_edbCityName;

	/// <summary>
	/// ������ ��������� �� �������� ���� ��������� ����� �� ��������.
	/// </summary>
	CEdit m_edbCityAreaName;
	
	/// <summary>
	/// ������ ��������� �� �������� ���� ��������� �������� ���.
	/// </summary>
	CEdit m_edbCityPostalCode;

	/// <summary>
	/// ������ �������� ����� �� �������� �������� ������� ���� �������� ��� ����������� �� �������.
	/// </summary>
	ContextMenuOperations m_eOperations;
private:
	CButton btn_Ok;
};

