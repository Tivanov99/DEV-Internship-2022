#pragma once
#include "Structures.h"
#include "PhoneTypesData.h"
class CPhoneTypesDocument :public CDocument
{
protected: // create from serialization only
	CPhoneTypesDocument() noexcept;
	DECLARE_DYNCREATE(CPhoneTypesDocument)

	// Attributes
public:

	// Operations
public:

	// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// Implementation
public:
	virtual ~CPhoneTypesDocument();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	//Methods
public:
	/// <summary>������� ����� ������ ������ ��������� ������ �� ������.</summary>
	const CPhoneTypesArray& GetAllPhoneTypes();
	/// <summary>������� ����� ������ ��������� ��� �� ������ ������ �������� ������������� 'lID'.</summary>
	PHONE_TYPES* GetPhoneTypeById(long lID);
	/// <summary>������� ����� ������� ��������� ��� �� ������ ������ �������� ������������� 'lID'.</summary>
	bool DeletePhoneTypeById(long lID);
	/// <summary>������� ����� ����������� ��������� ��� �� ������ ������ �������� ������������� 'lID'.</summary>
	/// <param "recPhoneType">���������� ��� ����� ����� ������� ��������������� ����������.</param>
	bool UpdatePhoneType(PHONE_TYPES& recPhoneType);
	/// <summary>������� ����� ������ ��� ����� ��� ������.</summary>
	/// <param name="recPhoneType">���������� ��� ����� ����� �� ���� ������� ��� ������.</param>
	bool InsertPhoneType(PHONE_TYPES& recPhoneType);
private:
	/// <summary>������� ����� ����������� view-��.</summary>
	void OnUpdateAllViews(LPARAM lHint, CObject* pHint);
	/// <summary>������� ����� ������� ����� �� ����������� 'm_oPhoneTypesArray' ����� 'ID' �������� �� 'lID'.</summary>
	/// <param name="lID">�������� ������������� �� ����� �����.</param>
	bool DeletePhoneTypeFromPhoneTypesArray(long lID);
	/// <summary>������� ����� ������ ����� ��� �����������</summary>
	/// <param name="recPhoneType">���������� ��� ����� ����� �� ���� ������� � ����������� 'm_oPhoneTypesArray'.</param>
	bool AddPhoneTypeToPhoneTypesArray(PHONE_TYPES& recPhoneType);
	/// <summary>������� ����� ����� ��������� � ����������� 'm_oPhoneTypesArray', �� ����� ����� 'ID' �������� �� 'lID'.</summary>
	/// <param name="lID">�������� ������������� �� ����� �����.</param>
	INT_PTR GetPhoneTypeIndexFromPhoneTypesArray(long lID);
	/// <summary>������� ����� ������ ��� ����� � ����������� 'm_oPhoneTypesArray'.</summary>
	/// <param name="lID">�������� ������������� �� ����� �����.</param>
	/// <param name="recPhoneType">����������� ��� ����� ����� ������� ��������������� ����������.</param>
	void UpdatePhoneTypesArray(long lID, PHONE_TYPES& recPhoneType);

	//Members
private:
	CPhoneTypesArray m_oPhoneTypesArray;
	CPhoneTypesData m_PhoneTypesData;

protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

};

