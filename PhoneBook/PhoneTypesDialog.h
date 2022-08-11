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
	/// <summary>Според командата в 'm_eOperation' задава име на прозореца и на бутона за потвърждаване на операцията.</summary>
	void SetDialogTitle();
	/// <summary>Задава сойносите попълнени в полетата на записът който подлежи на обработка.</summary>
	void SetDataToRecord();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	/// <summary>Надстройва диалоговия прозорец при стартиране и попълва всички данни на подадения обект в полетата; </summary>
	virtual BOOL OnInitDialog();
private:
	/// <summary>звиква се при натиска не бутона 'Ок'.</summary>
	afx_msg void OnBnClickedOk();

	// Members
	// ----------------
private:
	CEdit m_edbPhoneType;
	PHONE_TYPES& m_recPhoneType;
	DialogWindowActions m_eOperation;
};

