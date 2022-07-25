#pragma once
#include "CCitiesData.h"

class CCitiesDocument :public CDocument
{
protected: // create from serialization only
	CCitiesDocument() noexcept;
	DECLARE_DYNCREATE(CCitiesDocument)

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
	virtual ~CCitiesDocument();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	//Methods
public:
	const CSelfClearingTypedPtrArray< CITIES>& GetAllCities();
	CITIES* GetCityById(long lID);
	bool DeleteCityById(long lID);
	bool UpdateCity(CITIES& recCity);
	bool InsertCity(CITIES& recCity);
private:
	void OnUpdateAllViews(LPARAM lHint, CObject* pHint);
	//Members
private:
	CSelfClearingTypedPtrArray< CITIES> m_oCitiesArray;
	CCitiesData m_CitiesData;

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

