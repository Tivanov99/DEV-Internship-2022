#pragma once
#include "afxdialogex.h"
#include "Structures.h"


// CCitiesDialog dialog

class CCitiesDialog : public CDialog
{
	//Constants
	// ----------------
	int nMaxCityNameLenght = 32;
	int nMinCityNameLenght = 4;

	int nMaxCityAreaNameLenght = 32;
	int nMinCityAreaNameLenght = 4;

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
	void SetDialogWindowAndOkButtonText();

	/// <summary>
	/// �������� �������� ����� ������ �� ���������� �� ������ ���� �������� ���� ��������, � ��� ���������� �� ������ ���������� � ����� ���������� ���������.
	/// </summary>
	/// <param name="oEdit">���������� �� ���������� ������������ ������ ����.</param>
	/// <param name="nMinLenght">���������� ��������� ������� �� ���������� ����.</param>
	/// <param name="nMaxLenght">���������� ���������� ������� �� ���������� ����.</param>
	/// <returns>��������� ��������� ����������� ������, ��� ��� ������.</returns>
	CString ValidateTextData(const CEdit& oEdit, const int nMinLenght, const int nMaxLenght);

	/// <summary>
	/// �������� '�������� ���' ��� ��������� �� �����.
	/// </summary>
	/// <returns>���� 'true' ��� 'false' ������ ���� ���� ����� � �������.</returns>
	bool ValidatePostalCode();
	bool CheckForNotAllowedChars(const CString& strValue);
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
	CEdit StrCitiesName;

	/// <summary>
	/// ������ ��������� �� �������� ���� ��������� ����� �� ��������.
	/// </summary>
	CEdit StrAreaName;
	
	/// <summary>
	/// ������ ��������� �� �������� ���� ��������� �������� ���.
	/// </summary>
	CEdit StrPostalCode;

	/// <summary>
	/// ������ �������� ����� �� �������� �������� ������� ���� �������� ��� ����������� �� �������.
	/// </summary>
	ContextMenuOperations m_eOperations;
public:
	CButton btn_Ok;
};

