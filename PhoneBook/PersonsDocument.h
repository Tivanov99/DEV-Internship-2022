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
	/// <summary>Функция която изчита всички записи свързани с абонатите от таблицата 'PERSONS'.</summary>
	/// <returns>Връща масив съдържащ всички абонати.</returns>
	const CPersonsArray& GetAllPersons();
	/// <summary>Функция която изчита запис с уникален идентификатор 'ID' което отговаря на 'lID' от таблицата 'PERSONS'.</summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се изчете конкретен запис.</param>
	/// <returns>Връща указател съдържащ информацията на записа.</returns>
	PERSONS* GetPersonByIdFromPersonsArray(long lID);
	/// <summary>Функция която добавя нов запис в базата.</summary>
	/// <param name="oPersonInfo">Референция към обект който съдържа обект с актуална информация и асив който съдържа всички актуализирани записи за телефонните номера.</param>
	bool InsertRecord(CPersonsFull& oPersonInfo);
	/// <summary>Функция която изтрива запис от таблицата 'PERSONS' чието 'ID' отговаря на 'lID' и също така изтрива всички записи от таблицата 'PHONE_NUMBERS' чието 'PERSON_ID' отговаря на 'lID'.</summary>
	/// <param name="lID">Уникален идентификатор чрез който ще се изтрие конкретен запис.</param>
	bool DeletePersonAndPhoneNumbers(long lID);
	/// <summary>Фукция която изчита всички записи от таблицата 'PHONE_NUMBERS' чийто 'PERSON_ID' е идентично с 'lPersonID'. </summary>
	/// <param name="lPersonID">Уникален идентификатор чрез който ще се изтрие конкретен запис.</param>
	/// <param name="oPhoneNumbersArray">Буфер където ще се запишат всички изчетени от базата записи.</param>
	bool GetPersonPhoneNumbers(long lPersonID, CPhoneNumbersArray& oPhoneNumbersArray);
	/// <summary>Функция която изчита всички записи свързани с градовете от таблицата 'CITIES'.</summary>
	/// <param name="oCitiesArray">Масив където се записват всички стойности.</param>
	bool GetAllCities(CCitiesArray& oCitiesArray);
	/// <summary>Функция която изчита всички записи свързани с градовете от таблицата 'PHONE_TYPES'.</summary>
	/// <param name="oPhoneTypesArray">Масив където се записват всички стойности.</param>
	bool GetAllPhoneTypes(CPhoneTypesArray& oPhoneTypesArray);
	/// <summary>Функция която изчита всички телефонни номера.</summary>
	/// <param name="oMap">Мап в който се записват всички изчетени записи от базата.</param>
	bool GetAllPhoneTypes(CSelfClearingMap<long, PHONE_TYPES*>& oMap);
	/// <summary>Функция която актуализира всички телефонни номера на контакт както и него самия.</summary>
	/// <param name="oPersonInfo">Референция към обект който съдържа обект с актуална информация и асив който съдържа всички актуализирани записи за телефонните номера.</param>
	bool UpdatePersonAndPhoneNumbers(CPersonsFull& oPersonInfo);
	/// <summary>Функция която връща град според уникален идентифокатор 'lID'.</summary>
	/// <param name="lID">Уникален идентифокатор</param>
	/// <param name="oCity">Референция към обект където ще се запише запис</param>
	/// <returns></returns>
	bool GetCityById(long lID, CITIES& oCity);
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
	INT_PTR GetPersonIndexFromPersonsArray(long lID);
	/// <summary>Функция която актуализира данните на абонат от хранилището.</summary>
	/// <param name="lID">Уникален идентификатор за всеки абонат.</param>
	/// <param name="recUpdatedPerson">Референция към обект който съдържа актуализиранта информация.</param>
	void UpdatePersonFromPersonsArray(long lID, PERSONS& recUpdatedPerson);

	//Members
	//------------------------
private:
	/// <summary>Мембър съдържащ всички изчетени записи от базата.(Използва се като хранилище).</summary>
	CPersonsArray m_oPersonsArray;
	/// <summary>Мембър чрез който се достъпва бизнеслогиката за таблицата 'PERSONS'.</summary>
	CPersonsData m_оPersonsData;
	/// <summary>Мембър чрез който се достъпва бизнеслогиката за таблицата 'PHONE_NUMBERS'.</summary>
	CPhoneNumbersData m_oPhoneNumbersData;
	
	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

