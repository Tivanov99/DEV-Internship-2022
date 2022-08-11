#pragma once
#include <afxstr.h>
#include "TextDataValidator.h"
class CCitiesDataValidator : public TextDataValidator
{
public:
	// Constructor/Destructor
	// ----------------
	CCitiesDataValidator();
	~CCitiesDataValidator();
public:
	/// <summary>Валидира 'пощенски код' при обработка на запис.</summary>
	/// <param name="lPostalCode">Референция на въведената стойност.</param>
	bool ValidatePostalCode(const long& lPostalCode) const;
};

