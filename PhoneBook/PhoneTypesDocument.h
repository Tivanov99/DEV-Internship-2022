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
	/// <summary>Функция която изчита всички телефонни типове от базата.</summary>
	const CPhoneTypesArray& GetAllPhoneTypes();
	/// <summary>Функция която изчита телефонен тип от базата според уникален идентификатор 'lID'.</summary>
	PHONE_TYPES* GetPhoneTypeById(long lID);
	/// <summary>Функция която изтрива телефонен тип от базата според уникален идентификатор 'lID'.</summary>
	bool DeletePhoneTypeById(long lID);
	/// <summary>Функция която актуализира телефонен тип от базата според уникален идентификатор 'lID'.</summary>
	/// <param "recPhoneType">Референция към обект който съдържа актуализираната информация.</param>
	bool UpdatePhoneType(PHONE_TYPES& recPhoneType);
	/// <summary>Функция която добавя нов запис към базата.</summary>
	/// <param name="recPhoneType">Референция към обект който ще бъде добавен към базата.</param>
	bool InsertPhoneType(PHONE_TYPES& recPhoneType);
private:
	/// <summary>Функция която актуализира view-то.</summary>
	void OnUpdateAllViews(LPARAM lHint, CObject* pHint);
	/// <summary>Функция която изтрива запис от хранилището 'm_oPhoneTypesArray' чието 'ID' отговаря на 'lID'.</summary>
	/// <param name="lID">Уникален идентификатор за всеки запис.</param>
	bool DeletePhoneTypeFromPhoneTypesArray(long lID);
	/// <summary>Функция която добавя запис към хранилището</summary>
	/// <param name="recPhoneType">Референция към обект който ще бъде добавен в хранилището 'm_oPhoneTypesArray'.</param>
	bool AddPhoneTypeToPhoneTypesArray(PHONE_TYPES& recPhoneType);
	/// <summary>Функция която връща позицията в хранилището 'm_oPhoneTypesArray', на обект чието 'ID' отговаря на 'lID'.</summary>
	/// <param name="lID">Уникален идентификатор за всеки запис.</param>
	INT_PTR GetPhoneTypeIndexFromPhoneTypesArray(long lID);
	/// <summary>Функция която добавя нов запис в хранилището 'm_oPhoneTypesArray'.</summary>
	/// <param name="lID">Уникален идентификатор за всеки запис.</param>
	/// <param name="recPhoneType">Референкция към обект който съдържа актуализираната инфромация.</param>
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

