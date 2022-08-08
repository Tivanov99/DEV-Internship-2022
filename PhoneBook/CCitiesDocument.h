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
	/// <summary>������� ����� ������ ������ ������ �� ��������� �� ������ � �� ������ � 'm_oCitiesArray'.</summary>
	/// <returns></returns>
	const CCitiesArray& GetAllCities();
	/// <summary>������� ����� ������� � ����� ����� �� ������ �� ���� ������ �������� �������� � �������� 'ID'.</summary>
	/// <param name="lID"></param>
	/// <returns></returns>
	CITIES* GetCityById(long lID);
	/// <summary>������� ����� ������� ����� �� ������ �� ���� ������ �������� �������� � �������� 'ID'.</summary>
	/// <param name="lID"></param>
	/// <returns></returns>
	bool DeleteCityById(long lID);
	/// <summary>������� ����� ������� ��������� ���� �������� ����� ��� ������ � ��� �� ������� ��������� �� ���� ��� ������ �� ������.</summary>
	/// <param name="recCity"></param>
	/// <returns></returns>
	bool UpdateCity(CITIES& recCity);
	/// <summary>������� ����� ������ ��� ����� ��� ������.</summary>
	/// <param name="recCity"></param>
	/// <returns></returns>
	CITIES* InsertCity(CITIES& recCity);
private:
	/// <summary>������� ��� ����� ��� ������� ������� �� �������� �� ������� � ����������� view-��.</summary>
	/// <param name="lHint"></param>
	/// <param name="pHint"></param>
	void OnUpdateAllViews(LPARAM lHint, CObject* pHint);
	/// <summary>������� ����� ������� ����� ������ �������� 'ID' �� ������ ����� �� ������� ���� ��������� 'm_oCitiesArray'.</summary>
	/// <param name="lID">�������� ������������� ������ ����� �� �� ������ �����.</param>
	/// <returns>��� ������� ��������� ����� 'true' � �������� ������ 'false'.</returns>
	bool DeleteCityFromCitiesArray(long lID);
	/// <summary>������� ����� ������ ����� ��� ������ ����� �� ������� ���� ��������� 'm_oCitiesArray'.</summary>
	/// <param name="recCity">����� ����� �� ���� ������� ��� ����������� 'm_oCitiesArray'.</param>
	/// <returns>��� ������� �������� ����� 'true' � �������� ������ 'false'</returns>
	CITIES* AddCityToCitiesArray(CITIES& recCity);
	/// <summary>����� ��������� �� ����� �� ������ ����� ����� � �������� ������������� 'ID' � ����������� 'm_oCitiesArray'.</summary>
	/// <param name="lID">�������� ������������� �� ����� �� �� ����� �����.</param>
	/// <returns>��� �������� �� ������ ����� ��������� �� ����� �� ������, � �������� ������ -1.</returns>
	long GetCityIndexFromCitiesArray(long lID);
	//Members
	//---------------------
private:
	/// <summary>����� ����� ������� ������ ������ �� ������. �������� ���� ���������.</summary>
	CCitiesArray m_oCitiesArray;
	/// <summary>������ ���� ����� �� �������� ���������������� �� ��������� ���� 'CCitiesData'.</summary>
	CCitiesData m_CitiesData;
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

