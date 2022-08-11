#pragma once
#include "Structures.h"
#include "PersonsData.h"
#include "PhoneNumbersData.h"
#include "SelfClearingMap.h"
#include "PersonsFull.h"


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
	PERSONS* GetPersonByIdFromPersonsArray(long lID);
	/// <summary>������� ����� ������ ��� ����� � ������.</summary>
	/// <param name="oPersonInfo">���������� ��� ����� ����� ������� ����� � �������� ���������� � ���� ����� ������� ������ ������������� ������ �� ����������� ������.</param>
	bool InsertRecord(CPersonsFull& oPersonInfo);
	/// <summary>������� ����� ������� ����� �� ��������� 'PERSONS' ����� 'ID' �������� �� 'lID' � ���� ���� ������� ������ ������ �� ��������� 'PHONE_NUMBERS' ����� 'PERSON_ID' �������� �� 'lID'.</summary>
	/// <param name="lID">�������� ������������� ���� ����� �� �� ������ ��������� �����.</param>
	bool DeletePersonAndPhoneNumbers(long lID);
	/// <summary>������ ����� ������ ������ ������ �� ��������� 'PHONE_NUMBERS' ����� 'PERSON_ID' � ��������� � 'lPersonID'. </summary>
	/// <param name="lPersonID">�������� ������������� ���� ����� �� �� ������ ��������� �����.</param>
	/// <param name="oPhoneNumbersArray">����� ������ �� �� ������� ������ �������� �� ������ ������.</param>
	bool GetPersonPhoneNumbers(long lPersonID, CPhoneNumbersArray& oPhoneNumbersArray);
	/// <summary>������� ����� ������ ������ ������ �������� � ��������� �� ��������� 'CITIES'.</summary>
	/// <param name="oCitiesArray">����� ������ �� �������� ������ ���������.</param>
	bool GetAllCities(CCitiesArray& oCitiesArray);
	/// <summary>������� ����� ������ ������ ������ �������� � ��������� �� ��������� 'PHONE_TYPES'.</summary>
	/// <param name="oPhoneTypesArray">����� ������ �� �������� ������ ���������.</param>
	bool GetAllPhoneTypes(CPhoneTypesArray& oPhoneTypesArray);
	/// <summary>������� ����� ������ ������ ��������� ������.</summary>
	/// <param name="oMap">��� � ����� �� �������� ������ �������� ������ �� ������.</param>
	bool GetAllPhoneTypes(CSelfClearingMap<long, PHONE_TYPES*>& oMap);
	/// <summary>������� ����� ����������� ������ ��������� ������ �� ������� ����� � ���� �����.</summary>
	/// <param name="oPersonInfo">���������� ��� ����� ����� ������� ����� � �������� ���������� � ���� ����� ������� ������ ������������� ������ �� ����������� ������.</param>
	bool UpdatePersonAndPhoneNumbers(CPersonsFull& oPersonInfo);
	/// <summary>������� ����� ����� ���� ������ �������� ������������� 'lID'.</summary>
	/// <param name="lID">�������� �������������</param>
	/// <param name="oCity">���������� ��� ����� ������ �� �� ������ �����</param>
	/// <returns></returns>
	bool GetCityById(long lID, CITIES& oCity);
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
	INT_PTR GetPersonIndexFromPersonsArray(long lID);
	/// <summary>������� ����� ����������� ������� �� ������ �� �����������.</summary>
	/// <param name="lID">�������� ������������� �� ����� ������.</param>
	/// <param name="recUpdatedPerson">���������� ��� ����� ����� ������� �������������� ����������.</param>
	void UpdatePersonFromPersonsArray(long lID, PERSONS& recUpdatedPerson);

	//Members
	//------------------------
private:
	/// <summary>������ �������� ������ �������� ������ �� ������.(�������� �� ���� ���������).</summary>
	CPersonsArray m_oPersonsArray;
	/// <summary>������ ���� ����� �� �������� �������������� �� ��������� 'PERSONS'.</summary>
	CPersonsData m_�PersonsData;
	/// <summary>������ ���� ����� �� �������� �������������� �� ��������� 'PHONE_NUMBERS'.</summary>
	CPhoneNumbersData m_oPhoneNumbersData;
	
	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

