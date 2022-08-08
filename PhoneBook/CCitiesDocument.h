#pragma once
#include "CCitiesData.h"


class CCitiesDocument :public CDocument
{
protected: // create from serialization only
	/// <summary>Constructor</summary>
	/// <returns></returns>
	CCitiesDocument() noexcept;

	DECLARE_DYNCREATE(CCitiesDocument)
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
	/// <summary>
	/// Destructor
	/// </summary>
	virtual ~CCitiesDocument();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	//Methods
public:
	/// <summary>Функция която изчита всички записи на градовете от базата и ги записа в 'm_oCitiesArray'.</summary>
	/// <returns></returns>
	const CCitiesArray& GetAllCities();
	/// <summary>Функция която прочива и връща запис от базата на град според неговата стойност в колоната 'ID'.</summary>
	/// <param name="lID"></param>
	/// <returns></returns>
	CITIES* GetCityById(long lID);
	/// <summary>Функция която изтрива запис от базата на град според неговата стойност в колоната 'ID'.</summary>
	/// <param name="lID"></param>
	/// <returns></returns>
	bool DeleteCityById(long lID);
	/// <summary>Функция която изпраща получения като аргумент запис към базата и там се налагат промените от него към записа от базата.</summary>
	/// <param name="recCity"></param>
	/// <returns></returns>
	bool UpdateCity(CITIES& recCity);
	/// <summary>Функция която добавя нов запис към базата.</summary>
	/// <param name="recCity"></param>
	/// <returns></returns>
	CITIES* InsertCity(CITIES& recCity);
private:
	/// <summary>Функция при която при някаква промяна на записите се извиква и актуализира view-то.</summary>
	/// <param name="lHint"></param>
	/// <param name="pHint"></param>
	void OnUpdateAllViews(LPARAM lHint, CObject* pHint);
	/// <summary>Функция която изтрива запис според ноговото 'ID' от масива който се изолзва като хранилище 'm_oCitiesArray'.</summary>
	/// <param name="lID">Уникален идентификатор според който ще се изтрие запис.</param>
	/// <returns>При успешно изтриване връща 'true' в противен случай 'false'.</returns>
	bool DeleteCityFromCitiesArray(long lID);
	/// <summary>Функция която добавя запис към масива който се изолзва като хранилище 'm_oCitiesArray'.</summary>
	/// <param name="recCity">Обект който ще бъде добавен към хранилището 'm_oCitiesArray'.</param>
	/// <returns>При успешно добавяне връща 'true' в противен случай 'false'</returns>
	CITIES* AddCityToCitiesArray(CITIES& recCity);
	/// <summary>Връща позицията на която се намира даден запис с уникален идентификатор 'ID' в хранилището 'm_oCitiesArray'.</summary>
	/// <param name="lID">Уникален идентификатор по който ще се търси запис.</param>
	/// <returns>При намиране на записа връща позицията на която се намира, в противен случай -1.</returns>
	long GetCityIndexFromCitiesArray(long lID);
	//Members
	//---------------------
private:
	/// <summary>Масив който съдържа всички записи от базата. Използва като хранилище.</summary>
	CCitiesArray m_oCitiesArray;
	/// <summary>Мембър чрез който се достъпва функционалността на табличния клас 'CCitiesData'.</summary>
	CCitiesData m_CitiesData;
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

