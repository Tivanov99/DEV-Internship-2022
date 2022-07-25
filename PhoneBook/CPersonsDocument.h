#pragma once
#include "Structures.h"
#include "CSelfClearingTypedPtrArray.h"

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
	const CSelfClearingTypedPtrArray<PERSONS>& GetAllCities();
	PERSONS* GetPersonById(long lID);
	bool DeletePersonById(long lID);
	bool UpdatePerson(PERSONS& recCity);
	bool InsertPerson(PERSONS& recCity);

private:
	void OnUpdateAllViews(LPARAM lHint, CObject* pHint);
	//Members

private:
	CSelfClearingTypedPtrArray< PERSONS> m_oPersonsArray;
	CCitiesData m_PersonsData;

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

