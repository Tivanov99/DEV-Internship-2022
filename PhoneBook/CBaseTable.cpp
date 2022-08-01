#pragma once
#include "pch.h"
#include "CBaseTable.h"

template <class T>
CBaseTable< T>::CBaseTable(CSession& oSession)
	:m_oSession (oSession)
{
};

template <class T>
CBaseTable<T>::~CBaseTable()
{};


template <class T>
CDBPropSet CBaseTable< T>::GetModifyDBPropSet() const
{
	CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
	oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
	oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	return oUpdateDBPropSet;
};

