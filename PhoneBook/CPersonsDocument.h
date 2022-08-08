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
	/// <summary>Функция която изчита всички записи свързани с абонатите от таблицата 'PERSONS'.</summary>
	/// <returns>Връща масив съдържащ всички абонати.</returns>
	const CPersonsArray& GetAllPersons();
	/// <summary>Функция която изчита запис с уникален идентификатор 'ID' което отговаря на 'lID' от таблицата 'PERSONS'.</summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се изчете конкретен запис.</param>
	/// <returns>Връща указател съдържащ информацията на записа.</returns>
	PERSONS* GetPersonById(long lID);
	/// <summary>Функция която изтрива запис от базата с уникален идентификатор 'ID' което отговаря на 'lID'.</summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се изчете конкретен запис.</param>
	/// <returns>При успешно изпълнение връща 'true' в противен случай 'false'</returns>
	bool DeletePersonById(long lID);
	/// <summary>Функция която актуализира информацията за запис.</summary>
	/// <param name="recPerson">Референция към обект който съдържа актуализираната инфромация за запис.</param>
	/// <returns>При успешно изпълнение връща 'true' в противен случай 'false'</returns>
	bool UpdatePerson(PERSONS& recPerson);
	/// <summary>Функция която добавя нов запис в базата.</summary>
	/// <param name="recPerson">Референция към обект който ще бъде добавен в базата.</param>
	/// <returns>При успешно изпълнение връща 'true' в противен случай 'false'</returns>
	bool InsertPerson(PERSONS& recPerson);
	/// <summary>Функция която изтрива запис от таблицата 'PERSONS' чието 'ID' отговаря на 'lID' и също така изтрива всички записи от таблицата 'PHONE_NUMBERS' чието 'PERSON_ID' отговаря на 'lID'.</summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се изтрие конкретен запис.</param>
	/// <returns>При успешно изпълнение връща 'true' в противен случай 'false'</returns>
	bool DeletePersonAndPhoneNumbers(long lID);
	/// <summary>Функция която актуализира всички записи от таблицата 'PHONE_NUMBERS' чието 'PERSON_ID' отговаря на 'lPersonID'.</summary>
	/// <param name="lPersonID">Уникален идентификатор чрез който ще се изтрие конкретен запис.</param>
	/// <param name="oPhoneNumbersMap">Буфер съдържащ всички телефонни номера.</param>
	/// <returns>При успешно изпълнение връща 'true' в противен случай 'false'</returns>
	bool UpdatePersonPhoneNumbers(long lPersonID, CSelfClearingMap<long, PHONE_NUMBERS*>& oPhoneNumbersMap);
	/// <summary>Фукция която изчита всички записи от таблицата 'PHONE_NUMBERS' чийто 'PERSON_ID' е идентично с 'lPersonID'. </summary>
	/// <param name="lPersonID">Уникален идентификатор чрез който ще се изтрие конкретен запис.</param>
	/// <param name="oPhoneNumbersMap">Буфер където ще се запишат всички изчетени от базата записи.</param>
	/// <returns>При успешно изпълнение връща 'true' в противен случай 'false'</returns>
	bool GetPersonPhoneNumbers(long lPersonID, CSelfClearingMap<long, PHONE_NUMBERS*>& oPhoneNumbersMap);
	/// <summary>Функция която изчита всички записи свързани с градовете от таблицата 'CITIES'.</summary>
	/// <param name="oCitiesArray">Масив където се записват всички стойности.</param>
	/// <returns>При успешно изпълнение връща 'true' в противен случай 'false'</returns>
	bool GetAllCities(CCitiesArray& oCitiesArray);
	/// <summary>Функция която изчита всички записи свързани с градовете от таблицата 'PHONE_TYPES'.</summary>
	/// <param name="oPhoneTypesArray">Масив където се записват всички стойности.</param>
	/// <returns>При успешно изпълнение връща 'true' в противен случай 'false'</returns>
	bool GetAllPhoneTypes(CPhoneTypesArray& oPhoneTypesArray);

	
	bool GetAllPhoneTypes(CSelfClearingMap<long, PHONE_TYPES*>& oMap);
private:
	void OnUpdateAllViews(LPARAM lHint, CObject* pHint);
	/// <summary>Фунцкия изтриваща запис от 'm_oPersonsArray' чието 'ID' отговаря на 'lPersonId'.</summary>
	/// <param name="lPersonID">Уникален идентификатор чрез който ще се изтрие конкретен запис.</param>
	/// <returns>При успешно изпълнение връща 'true' в противен случай 'false'</returns>
	bool DeletePersonFromPersonsArray(long lPersonId);
	/// <summary>Фунцкия добавяща запис от 'm_oPersonsArray'.</summary>
	/// <param name="recPerson">Референция към обект който ще бъде добавен в масива 'm_oPersonsArray'</param>
	/// <returns>При успешно изпълнение връща 'true' в противен случай 'false'</returns>
	PERSONS* AddPersonToPersonsArray(PERSONS& recPerson);
	/// <summary>Функция която връша запис от масива 'm_oPersonsArray' според неговото 'ID'.</summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси конкретен запис.</param>
	/// <returns>Обект чието 'ID' отговаря на 'lID'.</returns>
	long GetPersonIndexFromPersonsArray(long lID);
	/// <summary>Функция която връща 'PHONE_TYPES' обект според неговото 'ID'.</summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се търси конкретен запис.</param>
	/// <param name="oPhoneTypesArray">Масив в който ще се търси обект чийто 'ID' е идентично с 'lID'</param>
	/// <returns>Обект чието 'ID' отговаря на 'lID'.</returns>
	PHONE_TYPES* GetPhoneTypeById(long lID, CPhoneTypesArray& oPhoneTypesArray);

	//Members
	//------------------------
private:
	/// <summary>Мембър съдържащ всички изчетени записи от базата.(Използва се като хранилище).</summary>
	CPersonsArray m_oPersonsArray;
	/// <summary>Мембър чрез който се достъпва бизнеслогиката за таблицата 'PERSONS'.</summary>
	CPersonsData m_оPersonsData;
	/// <summary>Мембър чрез който се достъпва бизнеслогиката за таблицата 'PHONE_NUMBERS'.</summary>
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

