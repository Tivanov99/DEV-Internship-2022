#include "pch.h"
#include "CPhoneNumbersTable.h"

const LPCSTR CPhoneNumbersTable::lpszSelectById = "SELECT * FROM PHONE_NUMBERS WHERE ID = %d";
const LPCSTR CPhoneNumbersTable::lpszSelectAll = "SELECT * FROM PHONE_NUMBERS";
const LPCSTR CPhoneNumbersTable::lpszEmptySelect = "SELECT TOP 0 * FROM PHONE_NUMBERS";

CPhoneNumbersTable::CPhoneNumbersTable() {};
CPhoneNumbersTable::~CPhoneNumbersTable() {};

bool CPhoneNumbersTable::SelectAll(CPhoneNumbersArray& oArray)
{

}


bool CPhoneNumbersTable::SelectWhereID(const long lID, PHONE_NUMBERS& rec)
{

};

bool CPhoneNumbersTable::UpdateWhereID(const long lID, const PHONE_NUMBERS& rec)
{

};

bool CPhoneNumbersTable::Insert(const PHONE_NUMBERS& rec)
{

};

bool CPhoneNumbersTable::DeleteWhereID(const long lID)
{

};