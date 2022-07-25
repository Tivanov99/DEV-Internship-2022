#pragma once
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
	const CSelfClearingTypedPtrArray< CITIES>& GetAllCities();
	CITIES* GetCityById(long lID);
	bool DeleteCityById(long lID);
	bool UpdateCity(CITIES& recCity);
	bool InsertCity(CITIES& recCity);
};

