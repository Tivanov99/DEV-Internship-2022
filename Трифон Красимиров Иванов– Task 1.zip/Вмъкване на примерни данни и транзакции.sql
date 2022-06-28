USE [PhoneBook]

BEGIN TRANSACTION

INSERT INTO [CITIES]
	([CITY_NAME],[AREA_NAME],[POSTAL_CODE])
	VALUES
	('Бургас','Бургас',8000),
	('Пловдив', 'Пловдив',4000),	
	('Варна','Варна',9000),
	('София','София',1000);

INSERT INTO [PERSONS]
	([FIRST_NAME],[SECOND_NAME],[LAST_NAME],[CITY_ID],[ADDRESS])
	VALUES
	('Трифон','Красимиров','Иванов',1,'Жк.Възраждане/Ул.Цар Калоян №24'),
	('Христо','Стоянов','Петров',2,'Жк.Тракия/Ул.Лозенград №3'),
	('Георги','Ангелов','Анастасов',1,'Жк.Лазур/Ул.Христо Ботев №9'),
	('Трифон','Красимиров','Иванов',4,'Жк.Студентски град/Ул.Парижка комуна №8')


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
COMMIT TRANSACTION
