#pragma once
#include "Structures.h"
#include "CPhoneTypesData.h"
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
	const CPhoneTypesArray& GetAllPhoneTypes();
	PHONE_TYPES* GetPhoneTypeById(long lID);
	bool DeletePhoneTypeById(long lID);
	bool UpdatePhoneType(PHONE_TYPES& recPhoneType);
	CITIES* InsertPhoneType(PHONE_TYPES& recPhoneType);
private:
	void OnUpdateAllViews(LPARAM lHint, CObject* pHint);
	bool DeletePhoneTypeFromPhoneTypesArray(long lID);
	CITIES* AddPhoneTypeToPhoneTypesArray(PHONE_TYPES& recPhoneType);
	//long GetCityIndexFromCitiesArray(long lID);

	//Members
private:
	CPhoneTypesArray m_oPhoneTypesArray;
	CPhoneTypesData m_CitiesData;

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

