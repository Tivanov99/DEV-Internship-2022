#pragma once
#include "Structures.h"
#include "CPersonsData.h"
#include "CPhoneNumbersData.h"
#include "CSelfClearingMap.h"


class CPersonsDocument :public CDocument
{
protected: // create from serialization only
	CPersonsDocument() noexcept;
	DECLARE_DYNCREATE(CPersonsDocument)

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
	virtual ~CPersonsDocument();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//Methods
	//--------------------
public:
	/// <summary>������� ����� ������ ������ ������ �������� � ��������� �� ��������� 'PERSONS'.</summary>
	/// <returns>����� ����� �������� ������ �������.</returns>
	const CPersonsArray& GetAllPersons();
	/// <summary>������� ����� ������ ����� � �������� ������������� 'ID' ����� �������� �� 'lID' �� ��������� 'PERSONS'.</summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ������ ��������� �����.</param>
	/// <returns>����� �������� �������� ������������ �� ������.</returns>
	PERSONS* GetPersonById(long lID);
	/// <summary>������� ����� ������� ����� �� ������ � �������� ������������� 'ID' ����� �������� �� 'lID'.</summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ������ ��������� �����.</param>
	/// <returns>��� ������� ���������� ����� 'true' � �������� ������ 'false'</returns>
	bool DeletePersonById(long lID);
	/// <summary>������� ����� ����������� ������������ �� �����.</summary>
	/// <param name="recPerson">���������� ��� ����� ����� ������� ��������������� ���������� �� �����.</param>
	/// <returns>��� ������� ���������� ����� 'true' � �������� ������ 'false'</returns>
	bool UpdatePerson(PERSONS& recPerson);
	/// <summary>������� ����� ������ ��� ����� � ������.</summary>
	/// <param name="recPerson">���������� ��� ����� ����� �� ���� ������� � ������.</param>
	/// <returns>��� ������� ���������� ����� 'true' � �������� ������ 'false'</returns>
	bool InsertPerson(PERSONS& recPerson);
	/// <summary>������� ����� ������� ����� �� ��������� 'PERSONS' ����� 'ID' �������� �� 'lID' � ���� ���� ������� ������ ������ �� ��������� 'PHONE_NUMBERS' ����� 'PERSON_ID' �������� �� 'lID'.</summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ������ ��������� �����.</param>
	/// <returns>��� ������� ���������� ����� 'true' � �������� ������ 'false'</returns>
	bool DeletePersonAndPhoneNumbers(long lID);
	/// <summary>������� ����� ����������� ������ ������ �� ��������� 'PHONE_NUMBERS' ����� 'PERSON_ID' �������� �� 'lPersonID'.</summary>
	/// <param name="lPersonID">�������� ������������� ���� ����� �� �� ������ ��������� �����.</param>
	/// <param name="oPhoneNumbersMap">����� �������� ������ ��������� ������.</param>
	/// <returns>��� ������� ���������� ����� 'true' � �������� ������ 'false'</returns>
	bool UpdatePersonPhoneNumbers(long lPersonID, CSelfClearingMap<long, PHONE_NUMBERS*>& oPhoneNumbersMap);
	/// <summary>������ ����� ������ ������ ������ �� ��������� 'PHONE_NUMBERS' ����� 'PERSON_ID' � ��������� � 'lPersonID'. </summary>
	/// <param name="lPersonID">�������� ������������� ���� ����� �� �� ������ ��������� �����.</param>
	/// <param name="oPhoneNumbersMap">����� ������ �� �� ������� ������ �������� �� ������ ������.</param>
	/// <returns>��� ������� ���������� ����� 'true' � �������� ������ 'false'</returns>
	bool GetPersonPhoneNumbers(long lPersonID, CSelfClearingMap<long, PHONE_NUMBERS*>& oPhoneNumbersMap);
	/// <summary>������� ����� ������ ������ ������ �������� � ��������� �� ��������� 'CITIES'.</summary>
	/// <param name="oCitiesArray">����� ������ �� �������� ������ ���������.</param>
	/// <returns>��� ������� ���������� ����� 'true' � �������� ������ 'false'</returns>
	bool GetAllCities(CCitiesArray& oCitiesArray);
	/// <summary>������� ����� ������ ������ ������ �������� � ��������� �� ��������� 'PHONE_TYPES'.</summary>
	/// <param name="oPhoneTypesArray">����� ������ �� �������� ������ ���������.</param>
	/// <returns>��� ������� ���������� ����� 'true' � �������� ������ 'false'</returns>
	bool GetAllPhoneTypes(CPhoneTypesArray& oPhoneTypesArray);

	
	bool GetAllPhoneTypes(CSelfClearingMap<long, PHONE_TYPES*>& oMap);
private:
	void OnUpdateAllViews(LPARAM lHint, CObject* pHint);
	/// <summary>������� ��������� ����� �� 'm_oPersonsArray' ����� 'ID' �������� �� 'lPersonId'.</summary>
	/// <param name="lPersonID">�������� ������������� ���� ����� �� �� ������ ��������� �����.</param>
	/// <returns>��� ������� ���������� ����� 'true' � �������� ������ 'false'</returns>
	bool DeletePersonFromPersonsArray(long lPersonId);
	/// <summary>������� �������� ����� �� 'm_oPersonsArray'.</summary>
	/// <param name="recPerson">���������� ��� ����� ����� �� ���� ������� � ������ 'm_oPersonsArray'</param>
	/// <returns>��� ������� ���������� ����� 'true' � �������� ������ 'false'</returns>
	PERSONS* AddPersonToPersonsArray(PERSONS& recPerson);
	/// <summary>������� ����� ����� ����� �� ������ 'm_oPersonsArray' ������ �������� 'ID'.</summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ��������� �����.</param>
	/// <returns>����� ����� 'ID' �������� �� 'lID'.</returns>
	long GetPersonIndexFromPersonsArray(long lID);
	/// <summary>������� ����� ����� 'PHONE_TYPES' ����� ������ �������� 'ID'.</summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ����� ��������� �����.</param>
	/// <param name="oPhoneTypesArray">����� � ����� �� �� ����� ����� ����� 'ID' � ��������� � 'lID'</param>
	/// <returns>����� ����� 'ID' �������� �� 'lID'.</returns>
	PHONE_TYPES* GetPhoneTypeById(long lID, CPhoneTypesArray& oPhoneTypesArray);

	//Members
	//------------------------
private:
	/// <summary>������ �������� ������ �������� ������ �� ������.(�������� �� ���� ���������).</summary>
	CPersonsArray m_oPersonsArray;
	/// <summary>������ ���� ����� �� �������� �������������� �� ��������� 'PERSONS'.</summary>
	CPersonsData m_�PersonsData;
	/// <summary>������ ���� ����� �� �������� �������������� �� ��������� 'PHONE_NUMBERS'.</summary>
	CPhoneNumbersData m_oPhoneNumbersData;
	
protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

