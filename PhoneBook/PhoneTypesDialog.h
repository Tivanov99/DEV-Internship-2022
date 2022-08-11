#pragma once
#include "Structures.h"
#include "DialogWindowEnumeration.h"
class CPhoneTypesDialog : public CDialog
{
	DECLARE_DYNAMIC(CPhoneTypesDialog)
	// Constructor / Destructor
	// ----------------
public:
	CPhoneTypesDialog(DialogWindowActions eOperations,PHONE_TYPES& recPhoneType, CWnd* pParent = nullptr);
	~CPhoneTypesDialog();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHONE_TYPES_DIALOG};
#endif
	DECLARE_MESSAGE_MAP()

private:
	/// <summary>������ ��������� � 'm_eOperation' ������ ��� �� ��������� � �� ������ �� ������������� �� ����������.</summary>
	void SetDialogTitle();
	/// <summary>������ ��������� ��������� � �������� �� ������� ����� ������� �� ���������.</summary>
	void SetDataToRecord();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	/// <summary>���������� ���������� �������� ��� ���������� � ������� ������ ����� �� ��������� ����� � ��������; </summary>
	virtual BOOL OnInitDialog();
private:
	/// <summary>������ �� ��� ������� �� ������ '��'.</summary>
	afx_msg void OnBnClickedOk();

	// Members
	// ----------------
private:
	CEdit m_edbPhoneType;
	PHONE_TYPES& m_recPhoneType;
	DialogWindowActions m_eOperation;
};

