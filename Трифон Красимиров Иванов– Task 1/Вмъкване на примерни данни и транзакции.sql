USE [PhoneBook]

--CREATE DATABASE [PhoneBook]
BEGIN TRANSACTION
	INSERT INTO [CITIES]
		([CITY_NAME],[AREA_NAME],[POSTAL_CODE])
		VALUES
		('������','������',8000),
		('�������', '�������',4000),	
		('�����','�����',9000),
		('�����','�����',1000);

	INSERT INTO [PERSONS]
		([FIRST_NAME],[SECOND_NAME],[LAST_NAME],[CITY_ID],[ADDRESS])
		VALUES
		('������','����������','������',1,'��.����������/��.��� ������ �24'),
		('������','�������','������',2,'��.������/��.��������� �3'),
		('������','�������','���������',1,'��.�����/��.������ ����� �9'),
		('������','����������','������',4,'��.���������� ����/��.������� ������ �8')

	INSERT INTO [PHONE_TYPES] 
		(PHONE_TYPE) VALUES
		('Home'),
		('Mobile'),
		('Work')

	INSERT INTO [PHONE_NUMBERS]
		([PERSON_ID],[PHONE_NUMBER],[PHONE_TYPE_ID])
		VALUES
		(1,'0893668829',2),
		(2,'0899628177',3),
		(3,'0876351840',1),
		(4,'0882183197',2)

	IF(@@ERROR>0)
		BEGIN 
			ROLLBACK TRANSACTION 
		END
	ELSE
		BEGIN 
			COMMIT TRANSACTION
		END

BEGIN TRANSACTION
	UPDATE [PERSONS] SET [ADDRESS] =
			'��.���������/�� "����� ��������� �42"'
	WHERE [ADDRESS] = 
			'��.���������� ����/��.������� ������ �8'
SAVE TRANSACTION [CHANGE_PERSON_ADDRESS]

SELECT * FROM [PERSONS]

DELETE [PERSONS] WHERE [ADDRESS] = '��.���������/�� "����� ��������� �42"'

SELECT * FROM [PERSONS]

ROLLBACK TRANSACTION [CHANGE_PERSON_ADDRESS]

SELECT * FROM [PERSONS]

BEGIN TRANSACTION
	DECLARE @SELECTED_PERSON_ID INT =
		(SELECT [ID] FROM PERSONS
			WHERE
			[FIRST_NAME] ='������' AND
			[SECOND_NAME]='�������' AND
			[LAST_NAME] = '���������')

	UPDATE [PERSONS]
		SET [CITY_ID] = 3
		WHERE
		[ID]= @SELECTED_PERSON_ID

	UPDATE [PHONE_NUMBERS]
		SET [PHONE_NUMBER] = '0896812111'
		WHERE[PERSON_ID] = @SELECTED_PERSON_ID
	IF(@@ERROR>0)
		BEGIN
			ROLLBACK TRANSACTION 
		END
	ELSE
		BEGIN
			COMMIT TRANSACTION
		END


BEGIN TRANSACTION 
	UPDATE [PERSONS]
	SET [LAST_NAME] = '��������'
	WHERE [ID] = 4

	UPDATE [PHONE_NUMBERS]
		SET [PHONE_NUMBER] = '088611379'
		WHERE [PERSON_ID] = 4

	IF(@@ERROR>0)
		BEGIN
			ROLLBACK TRANSACTION 
		END
	ELSE
		BEGIN
			COMMIT TRANSACTION
		END

SELECT * FROM [PERSONS]

SELECT * FROM [PHONE_NUMBERS]







