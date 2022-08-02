#include "pch.h"
#include "CPhoneTypesTable.h"


CPhoneTypesTable::CPhoneTypesTable(CSession& oSession)
	: CBaseTable(oSession,_T("PHONE_TYPES"))
{};

CPhoneTypesTable::~CPhoneTypesTable() {};
