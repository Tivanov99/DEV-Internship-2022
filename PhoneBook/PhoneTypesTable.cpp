#include "pch.h"
#include "PhoneTypesTable.h"


CPhoneTypesTable::CPhoneTypesTable(CSession& oSession)
	: CBaseTable(oSession,_T("PHONE_TYPES"))
{};

CPhoneTypesTable::~CPhoneTypesTable() {};
