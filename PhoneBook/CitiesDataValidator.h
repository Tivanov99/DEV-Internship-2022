#pragma once
#include <afxstr.h>
#include "TextDataValidator.h"
class CCitiesDataValidator : public TextDataValidator
{
public:
	CCitiesDataValidator();
	~CCitiesDataValidator();
public:
	/// <summary>
	/// Валидира 'пощенски код' при обработка на запис.
	/// </summary>
	/// /// <param name="lPostalCode">Референция на въведената стойност.</param>
	/// <returns>Въща 'true' или 'false' според това дали всико е валидно.</returns>
	bool ValidatePostalCode(const long& lPostalCode) const;
};

