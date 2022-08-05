#pragma once
#include "Structures.h"
#include "CPersonsData.h"
#include "CPhoneNumbersData.h"

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
public:
	const CPersonsArray& GetAllPersons();
	PERSONS* GetPersonById(long lID);
	bool DeletePersonById(long lID);
	bool UpdatePerson(PERSONS& recPerson);
	bool InsertPerson(PERSONS& recPerson);

	bool DeletePersonAndPhoneNumbers(long lID);

	bool UpdatePersonPhoneNumbers(long lPersonID,map<long, PHONE_NUMBERS*>& oPhoneNumbersMap);

	bool GetPersonPhoneNumbers(long lPersonID, map<long, PHONE_NUMBERS*>& oPhoneNumbersMap);

	bool GetAllCities(CCitiesArray& oCitiesArray);
	bool GetAllPhoneTypes(CPhoneTypesArray& oPhoneTypesArray);
	bool GetAllPhoneTypes(map<long, PHONE_TYPES*>& oMap);
private:
	void OnUpdateAllViews(LPARAM lHint, CObject* pHint);
	bool DeletePersonFromPersonsArray(long lPersonId);
	PERSONS* AddPersonToPersonsArray(PERSONS& recPerson);
	long GetPersonIndexFromPersonsArray(long lID);
	PHONE_TYPES* GetPhoneTypeById(long lID, CPhoneTypesArray& oPhoneTypesArray);

	//Members
	//------------------------
private:
	CPersonsArray m_oPersonsArray;
	CPersonsData m_ÓPersonsData;
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

