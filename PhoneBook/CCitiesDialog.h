#pragma once
#include "afxdialogex.h"
#include "Structures.h"
#include "Enumerations.h"
#include "DataValidator.h"


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


	/// <summary>
	/// ������ �������� ������ �� ���������� �� ���������� � ���������� ������.
	/// </summary>
	DataValidator m_oDataValidator;
private:
	CButton btn_Ok;
};

