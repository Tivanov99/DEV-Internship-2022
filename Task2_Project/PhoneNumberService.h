#pragma once
#include <string>
#include "Structures.h"
#include "BaseService.h"

using namespace std;

class PhoneNumberService :public BaseService<PHONE_NUMBERS>
{
private:
	///<summary>
		/// ������� 'PHONE_NUMBER' ��� ���������� 'oPhoneNumber' �� ����� ������� ���� �������� 'phoneNumber'.
	/// </summary>
	/// <param name="strPhoneNumber">��������� �����.</param>
	/// <param name="oPhoneNumber">���������� ��� �����.</param>
	void SetPhoneNumber(const CString& strPhoneNumber, PHONE_NUMBERS& oPhoneNumber);

	CPhoneNumbersArray phoneNumbersArray;
public:

	PhoneNumberService();
	~PhoneNumberService();

	///<summary>
		/// ������� ����� ����� �������� ���� �������� ���� ������� �� 'strPhoneNumber'.
	///</summary>
	/// <param name="strPhoneNumber">��������� �����.</param>
	PHONE_NUMBERS* GetByPhoneNumber(CString& strPhoneNumber);


	///<summary>
		//������� ��������� ���������� �� 'PHONE_NUMBER' �� ����� ����� ������ ������� � 'oldPhoneNumber'.
	///</summary>
	/// <param name="strCurrentPhoneNumber">����� ��������� �����.</param>
	/// <param name="strNewPhoneNumber">��� ��������� �����.</param>
	void ChangePhoneNumber(const CString &strCurrentPhoneNumber, const CString &strNewPhoneNumber);


	///<summary>
		/// ������� ��������� ���������� �� 'PHONE_NUMBER' �� ����� ������� ���� �������� 'pOldPhoneNumberElement' .
	/// </summary>
	/// <param name="�PhoneNumber">���������� ��� �����.</param>
	/// <param name="strNewPhoneNumber">��� ��������� �����.</param>
	void ChangePhoneNumber(PHONE_NUMBERS& �PhoneNumber, const CString &strNewPhoneNumber);
	
	///<summary>
		///������� ���������� ���������� �� ����� ������� �� �� ��������� �� nIndex.
		///������� ����������� �� ����� ���� 'BaseService'.
	///</summary>
	/// <param name="�nIndex">������� �� �������� � ������.</param>
	/// <param name="�oArray">����� � ��������.</param>
	void ShowElementInfoAtIndex(const long lIndex) override;
	
	///<summary>
		/// ������� �������� ������ �������� �������� � ������� ����� ���� ��������.
		/// ������� ����������� �� ����� ���� 'BaseService'.
	/// </summary>
	///<param name="citiesArray">����� � ����� �� �� ������� ������ ���������.</param>
	void AddDefaultElements() override;
};

