#include "pch.h"
#include "CitiesDataValidator.h"


CCitiesDataValidator::CCitiesDataValidator() {};
CCitiesDataValidator::~CCitiesDataValidator() {};


bool CCitiesDataValidator::ValidatePostalCode(const long& lPostalCode)const
{
	return	lPostalCode <= 0 ? false : true;
}
