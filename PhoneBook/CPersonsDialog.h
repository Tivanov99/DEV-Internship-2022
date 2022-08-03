#pragma once
#include "Structures.h"
#include "DialogWindowEnumeration.h"
#include "TextDataValidator.h"


class CPersonsDialog : public CDialog
{
	//Constants
	// ----------------
	DECLARE_DYNAMIC(CPersonsDialog)

public:
	CPersonsDialog(DialogWindowActions eOperations, PERSONS& recPerson,CCitiesArray& oCitiesArray
		, CPhoneNumbersArray& oPhoneNumbersArray, CPhoneTypesArray& oPhoneTypesArray, CWnd* pParent = nullptr);  // standard constructor
	virtual ~CPersonsDialog();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSONS_DIALOG };
#endif
	DECLARE_MESSAGE_MAP()

	// Methods
	// ----------------
private:
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
	/// ���������� ��� ������� ����� ��� ����������� �� �������.
	/// </summary>
	PERSONS& m_recPerson;

	/// <summary>
	/// ���������� ��� ������� �����  ��� ����������� �� ������� ����� ������� ������ �������.
	/// </summary>
	const CCitiesArray& m_oCitiesArray;

	/// <summary>
	/// ���������� ��� ������� �����  ��� ����������� �� ������� ����� ������� ������ ��������� ������.
	/// </summary>
	CPhoneNumbersArray& m_oPhoneNumbersArray;

	/// <summary>
	/// ���������� ��� ������� �����  ��� ����������� �� ������� ����� ������� ������ ������ ��������� ������.
	/// </summary>
	const CPhoneTypesArray& m_oPhoneTypesArray;

	/// <summary>
	/// ������ �������� ����� �� �������� �������� ������� ���� �������� ��� ����������� �� �������.
	/// </summary>
	DialogWindowActions m_eOperation;

	/// <summary>
	/// ������ �������� ������ �� ���������� �� ���������� � ���������� ������.
	/// </summary>
	//CCitiesDataValidator m_oDataValidator;

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
};

