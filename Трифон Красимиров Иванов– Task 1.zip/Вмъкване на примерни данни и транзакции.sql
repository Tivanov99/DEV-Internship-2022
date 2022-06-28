USE [PhoneBook]

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
COMMIT TRANSACTION
