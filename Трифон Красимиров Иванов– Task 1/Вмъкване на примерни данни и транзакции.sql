USE [PhoneBook]

BEGIN TRY
	BEGIN TRANSACTION
		INSERT INTO [CITIES]
			([CITY_NAME],[AREA_NAME],[POSTAL_CODE], [UPDATE_COUNTER])
			VALUES
			('������','������',8000,1),
			('�������', '�������',4000,1),	
			('�����','�����',9000,1),
			('�����','�����',1000,1);
	
		INSERT INTO [PERSONS]
			([FIRST_NAME],[SECOND_NAME],[LAST_NAME],[CITY_ID],[ADDRESS],[UPDATE_COUNTER],[EGN])
			VALUES
			('������','����������','������',1,'��.����������/��.��� ������ �24',1,9999999999),
			('������','�������','������',2,'��.������/��.��������� �3',1,9999999999),
			('������','�������','���������',1,'��.�����/��.������ ����� �9',1,9999999999),
			('������','����������','������',3,'��.���������� ����/��.������� ������ �8',1,9999999999)
	
		INSERT INTO [PHONE_TYPES] 
			([PHONE_TYPE],[UPDATE_COUNTER]) VALUES
			('Home',1),
			('Mobile',1),
			('Work',1)
	
		INSERT INTO [PHONE_NUMBERS]
			([PERSON_ID],[PHONE_NUMBER],[PHONE_TYPE_ID],[UPDATE_COUNTER])
			VALUES
			(1,'0893668829',2,1),
			(2,'0899628177',3,1),
			(3,'0876351840',1,1),
			(4,'0882183197',2,1)
		 COMMIT
END TRY
BEGIN CATCH
	 SELECT ERROR_MESSAGE() AS ErrorMessage
END CATCH


--Exclusive Lock 
BEGIN TRANSACTION
	UPDATE [PERSONS] SET [ADDRESS] =
			'��.���������/�� "����� ��������� �42"'
	WHERE [ADDRESS] = 
			'��.���������� ����/��.������� ������ �8'
	WAITFOR DELAY '00:00:10'
COMMIT
SELECT * FROM [PERSONS] WITH (NOLOCK) 

SELECT * FROM [PERSONS]

BEGIN TRANSACTION
	UPDATE [PERSONS] SET [FIRST_NAME] ='�����'
	WHERE [ADDRESS] = 
			'��.���������� ����/��.������� ������ �8'
	WAITFOR DELAY '00:00:10'
COMMIT

SELECT * FROM [PERSONS]





SELECT * FROM [PERSONS]

DELETE [PERSONS] WHERE [ADDRESS] = '��.���������/�� "����� ��������� �42"'

SELECT * FROM [PERSONS]

ROLLBACK TRANSACTION [CHANGE_PERSON_ADDRESS]

SELECT * FROM [PERSONS]


BEGIN TRY
	BEGIN TRANSACTION 
		UPDATE [PERSONS]
		SET [LAST_NAME] = '��������'
		WHERE [ID] = 4
	
		UPDATE [PHONE_NUMBERS]
			SET [PHONE_NUMBER] = '088611379'
			WHERE [PERSON_ID] = 4
	COMMIT TRANSACTION
END TRY
BEGIN CATCH
 		SELECT ERROR_MESSAGE() AS ErrorMessage
END CATCH


BEGIN TRY
	SELECT * FROM [PERSONS]

	BEGIN TRANSACTION
		INSERT INTO [PERSONS]
					([FIRST_NAME],[SECOND_NAME],[LAST_NAME],[CITY_ID],[ADDRESS],[UPDATE_COUNTER],[EGN])
					VALUES
					('�����','�������','��������',3,'��.����������/��.������� �11',1,12345678904)
	SAVE TRANSACTION [TEST_TRANSACTION]
	DELETE FROM [PERSONS] WHERE [SECOND_NAME] ='�������'
	SELECT * FROM [PERSONS]
	ROLLBACK TRANSACTION [TEST_TRANSACTION]
	COMMIT
	SELECT * FROM [PERSONS]

END TRY
BEGIN CATCH
 		SELECT ERROR_MESSAGE() AS ErrorMessage
END CATCH



BEGIN TRY
	BEGIN TRANSACTION
				DECLARE @SELECTED_PERSON_ID INT =
					(SELECT [ID] FROM PERSONS
						WHERE
						[FIRST_NAME] ='������' AND
						[SECOND_NAME]='�������' AND
						[LAST_NAME] = '���������')
						
				UPDATE [PERSONS]
					SET [CITY_ID] = 1
					WHERE
					[ID]= @SELECTED_PERSON_ID

				INSERT INTO [PERSONS]
				([FIRST_NAME],[SECOND_NAME],[LAST_NAME],[CITY_ID],[ADDRESS],[UPDATE_COUNTER],[EGN])
				VALUES
				('�����','��������','�������',1,'��.����������/��.��� ������ �24',1,null)
		COMMIT TRANSACTION
END TRY
BEGIN CATCH
		SELECT ERROR_MESSAGE() AS ErrorMessage
END CATCH
