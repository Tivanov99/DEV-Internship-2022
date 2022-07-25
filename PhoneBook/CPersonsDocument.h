#pragma once
#include "Structures.h"
#include "CSelfClearingTypedPtrArray.h"
#include "CPersonsData.h"

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
	PERSONS* GetCityById(long lID);
	bool DeleteCityById(long lID);
	bool UpdateCity(PERSONS& recCity);
	bool InsertCity(PERSONS& recCity);

private:
	void OnUpdateAllViews(LPARAM lHint, CObject* pHint);
	//Members

private:
	CSelfClearingTypedPtrArray< PERSONS> m_oPersonsArray;
	CPersonsData m_PersonsData;

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

