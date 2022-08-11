#include "pch.h"
#include "PhoneNumbersTable.h"
#include "ErrorVisualizator.h"


CPhoneNumbersTable::CPhoneNumbersTable(CSession& oSession)
	:CBaseTable(oSession,_T("PHONE_NUMBERS"))
{
};
CPhoneNumbersTable::~CPhoneNumbersTable() {};