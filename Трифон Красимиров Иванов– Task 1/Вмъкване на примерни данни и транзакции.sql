USE [PhoneBook]

BEGIN TRY
	BEGIN TRANSACTION
		INSERT INTO [CITIES]
			([CITY_NAME],[AREA_NAME],[POSTAL_CODE], [UPDATE_COUNTER])
			VALUES
			('Бургас','Бургас',8000,1),
			('Пловдив', 'Пловдив',4000,1),	
			('Варна','Варна',9000,1),
			('София','София',1000,1);
	
		INSERT INTO [PERSONS]
			([FIRST_NAME],[SECOND_NAME],[LAST_NAME],[CITY_ID],[ADDRESS],[UPDATE_COUNTER],[EGN])
			VALUES
			('Трифон','Красимиров','Иванов',1,'Жк.Възраждане/Ул.Цар Калоян №24',1,9999999999),
			('Христо','Стоянов','Петров',2,'Жк.Тракия/Ул.Лозенград №3',1,9999999999),
			('Георги','Ангелов','Анастасов',1,'Жк.Лазур/Ул.Христо Ботев №9',1,9999999999),
			('Трифон','Красимиров','Иванов',3,'Жк.Студентски град/Ул.Парижка комуна №8',1,9999999999)
	
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
			'Жк.Славейков/Ул "Любен Каравелов №42"'
	WHERE [ADDRESS] = 
			'Жк.Студентски град/Ул.Парижка комуна №8'
	WAITFOR DELAY '00:00:10'
COMMIT
SELECT * FROM [PERSONS] WITH (NOLOCK) 

SELECT * FROM [PERSONS]

BEGIN TRANSACTION
	UPDATE [PERSONS] SET [FIRST_NAME] ='Кирчо'
	WHERE [ADDRESS] = 
			'Жк.Студентски град/Ул.Парижка комуна №8'
	WAITFOR DELAY '00:00:10'
COMMIT

SELECT * FROM [PERSONS]





SELECT * FROM [PERSONS]

DELETE [PERSONS] WHERE [ADDRESS] = 'Жк.Славейков/Ул "Любен Каравелов №42"'

SELECT * FROM [PERSONS]

ROLLBACK TRANSACTION [CHANGE_PERSON_ADDRESS]

SELECT * FROM [PERSONS]


BEGIN TRY
	BEGIN TRANSACTION 
		UPDATE [PERSONS]
		SET [LAST_NAME] = 'Михайлов'
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
					('Стоян','Калинов','Стефанов',3,'Жк.Възраждане/Ул.Пробуда №11',1,12345678904)
	SAVE TRANSACTION [TEST_TRANSACTION]
	DELETE FROM [PERSONS] WHERE [SECOND_NAME] ='Калинов'
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
						[FIRST_NAME] ='Георги' AND
						[SECOND_NAME]='Ангелов' AND
						[LAST_NAME] = 'Анастасов')
						
				UPDATE [PERSONS]
					SET [CITY_ID] = 1
					WHERE
					[ID]= @SELECTED_PERSON_ID

				INSERT INTO [PERSONS]
				([FIRST_NAME],[SECOND_NAME],[LAST_NAME],[CITY_ID],[ADDRESS],[UPDATE_COUNTER],[EGN])
				VALUES
				('Петър','Калоянов','Стоянов',1,'Жк.Възраждане/Ул.Цар Калоян №24',1,null)
		COMMIT TRANSACTION
END TRY
BEGIN CATCH
		SELECT ERROR_MESSAGE() AS ErrorMessage
END CATCH
