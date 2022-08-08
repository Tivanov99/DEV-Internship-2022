#pragma once
class TextDataValidator
{
	// Constructor/Destructor
	// ----------------
public:
	TextDataValidator();
	~TextDataValidator();

	// Methods
	// ----------------
public:
	/// <summary>Валидира текстови данни идващи от променлива на входно поле подадена като аргумент, и при възникване на грешка конструира и връща поянително съобщение.</summary>
	/// <param name="strData">Референция на въведената стойност.</param>
	/// <param name="nMinLenght">Константна минимална дължина на текстовото поле.</param>
	/// <returns>Съобщение съдържащо допуснатите грешки, ако има такива.</returns>
	CString ValidateTextData(const CString& strData, const int nMinLenght) const;

private:
	/// <summary>Проверява текстово поле дали съсържа друг символ освен дуква и цифра.</summary>
	/// <param name="strValue">Референция от попълнената стойност в текстовото после</param>
	/// <returns>true ако няма символ освен числа и букви в противен случай false.</returns>
	bool CheckForSymbols(const CString& strValue) const;
};

