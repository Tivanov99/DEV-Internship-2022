USE [PhoneBook]

CREATE OR ALTER PROCEDURE SP_ADD_TABLE_DESCRIPTION
(
    @TABLE_NAME NVARCHAR,
    @TABLE_DESCRIPTION NVARCHAR
)
AS
BEGIN
    SELECT CONCAT(@TABLE_NAME,'_TABLE_DESCRIPTION') AS DESCRIPTION_NAME

    EXEC SP_ADDEXTENDEDPROPERTY @NAME=DESCRIPTION_NAME,
                                @VALUE=@TABLE_DESCRIPTION,
                                @LEVEL0TYPE=N'SCHEMA',
                                @LEVEL0NAME=N'DBO',
                                @LEVEL1TYPE=N'TABLE',
                                @LEVEL1NAME=@TABLE_NAME
END

CREATE OR ALTER PROCEDURE SP_ADD_COLUMN_DESCRIPTION
(
	@TABLE_NAME NVARCHAR,
	@COLUMN_NAME NVARCHAR,
	@COLUMN_DESCRIPTION NVARCHAR
)
AS
BEGIN
	exec sp_AddExtendedProperty'MS_Description',@COLUMN_DESCRIPTION,
								'TABLE', @TABLE_NAME,
								'COLUMN', @COLUMN_NAME
END

DROP TABLE IF EXISTS [PHONE_NUMBERS]
DROP TABLE IF EXISTS [PERSONS]
DROP TABLE IF EXISTS [CITIES]
DROP TABLE IF EXISTS [PHONE_TYPES]

exec sp_columns  [PHONE_NUMBERS] 


CREATE TABLE
	[CITIES]
	(
		[ID] INT IDENTITY (1,1) NOT NULL,
		[UPDATE_COUNTER] INT NOT NULL,
		[CITY_NAME] NVARCHAR(32)NOT NULL,
		[AREA_NAME] NVARCHAR(32)NOT NULL,
		[POSTAL_CODE] INT NOT NULL,
		CONSTRAINT [PK_CITIES_ID]
		PRIMARY KEY ([ID])
	)

EXEC SP_ADD_TABLE_DESCRIPTION 'CITIES','������� ��������� ������������� �� ���������.'
EXEC SP_ADD_COLUMN_DESCRIPTION 'CITIES','ID','�������� ������������� �� ����� � ��������� (32)����'
EXEC SP_ADD_COLUMN_DESCRIPTION 'CITIES','UPDATE_COUNTER','������ �� ��� (32)���� (������������ �����)'
EXEC SP_ADD_COLUMN_DESCRIPTION 'CITIES','CITY_NAME','������� ��������� (������������ �����) ��������� (512)����'
EXEC SP_ADD_COLUMN_DESCRIPTION 'CITIES','AREA_NAME','������� ��������� (������������ �����) ��������� (512)����'
EXEC SP_ADD_COLUMN_DESCRIPTION 'CITIES','POSTAL_CODE','������� ��������� (������������ �����) ���������� ������ (32)����'

CREATE UNIQUE INDEX UX_CITIES_CITY_NAME ON [CITIES]([CITY_NAME])

CREATE NONCLUSTERED INDEX IX_CITIES_CITY_NAME
ON [CITIES]([CITY_NAME] ASC)

CREATE NONCLUSTERED INDEX IX_CITIES__AREA_NAME
ON [CITIES]([AREA_NAME] ASC)



CREATE TABLE
	[PHONE_TYPES]
	(
		[ID] INT IDENTITY (1,1) NOT NULL,
		[UPDATE_COUNTER] INT NOT NULL,
		[PHONE_TYPE] VARCHAR(16) UNIQUE NOT NULL,
		CONSTRAINT [PK_PHONE_TYPES_ID]
		PRIMARY KEY ([ID])
	)

EXEC SP_ADD_TABLE_DESCRIPTION 'PHONE_TYPES','������� ��������� ������������� �� �������� ��������.'
EXEC SP_ADD_COLUMN_DESCRIPTION 'PHONE_TYPES','ID','�������� ������������� �� ����� � ��������� (32)����'
EXEC SP_ADD_COLUMN_DESCRIPTION 'PHONE_TYPES','UPDATE_COUNTER','������ �� ��� (32)���� (������������ �����)'
EXEC SP_ADD_COLUMN_DESCRIPTION 'PHONE_TYPES','PHONE_TYPE','������ ��������� (������������ �����) �������� �������� (128)����'


CREATE UNIQUE INDEX UX_PHONE_TYPES_PHONE_TYPE ON [PHONE_TYPES]([PHONE_TYPE])


CREATE TABLE
	[PERSONS]
	(
		[ID] INT IDENTITY (1,1) NOT NULL,
		[UPDATE_COUNTER] INT NOT NULL,
		[FIRST_NAME] NVARCHAR(32) NOT NULL,
		[SECOND_NAME] NVARCHAR(32) NOT NULL,
		[LAST_NAME] NVARCHAR(32) NOT NULL,
		[UCN] NVARCHAR(16) NOT NULL,		
		[CITY_ID] INT NOT NULL,
		[ADDRESS] NVARCHAR(256) NOT NULL,
		CONSTRAINT [PK_PERSONS_ID]
		PRIMARY KEY ([ID])
	)
EXEC SP_ADD_TABLE_DESCRIPTION 'PERSONS','������� ��������� ������������� �� ����.'
EXEC SP_ADD_COLUMN_DESCRIPTION 'PERSONS','UPDATE_COUNTER','������ �� ��� (32)���� (������������ �����)'
EXEC SP_ADD_COLUMN_DESCRIPTION 'PERSONS','FIRST_NAME','������� ����������� (������������ �����) ����� (256)����'
EXEC SP_ADD_COLUMN_DESCRIPTION 'PERSONS','SECOND_NAME','������� ����������� (������������ �����) ��������� (256)����'
EXEC SP_ADD_COLUMN_DESCRIPTION 'PERSONS','LAST_NAME','������� ����������� (������������ �����) ��������� (256)����'
EXEC SP_ADD_COLUMN_DESCRIPTION 'PERSONS','CITY_ID','������������ �������� ���� ��������� ��������� "CITTIES" � �������� "ID"  (64)����'
EXEC SP_ADD_COLUMN_DESCRIPTION 'PERSONS','UCN','������� ����������� (������������ �����) ���-�� (64)����'
EXEC SP_ADD_COLUMN_DESCRIPTION 'PERSONS','ADDRESS','������� ����������� (������������ �����) ���-�� (512)����'


CREATE NONCLUSTERED INDEX IX_PERSONS_FIRST_AND_LAST_NAME
ON [PERSONS]([FIRST_NAME], [LAST_NAME] ASC)

CREATE NONCLUSTERED INDEX IX_PERSONS_EGN
ON [PERSONS]([UCN] ASC)

ALTER TABLE [PERSONS]
ADD CONSTRAINT [FK_PERSONS_CITY_ID] 
		FOREIGN KEY ([CITY_ID])
		REFERENCES [CITIES]([ID])

CREATE TABLE
	[PHONE_NUMBERS]
	(
		[ID] INT IDENTITY (1,1) NOT NULL, 
		[UPDATE_COUNTER] INT NOT NULL,
		[PERSON_ID] INT NOT NULL,
		[PHONE_TYPE_ID] INT NOT NULL,
		[PHONE_NUMBER] VARCHAR(16) NOT NULL UNIQUE,
		CONSTRAINT [PK_PHONE_NUMBERS_ID]
			PRIMARY KEY([ID])
	)

EXEC SP_ADD_TABLE_DESCRIPTION 'PHONE_NUMBERS','������� ��������� ������������� �� ��������� ������, ������ �������� � ����.'


exec sp_addextendedproperty
'MS_Description',
'�������� ������������� �� ����� � ��������� (32)����',
'SCHEMA', 'dbo',
'TABLE', 'PHONE_NUMBERS',
'COLUMN', 'ID'

exec sp_addextendedproperty
'MS_Description',
'������ �� ��� (32)���� (������������ �����)',
'SCHEMA', 'dbo',
'TABLE', 'PHONE_NUMBERS',
'COLUMN', 'UPDATE_COUNTER'

exec sp_addextendedproperty
'MS_Description',
'������������ �������� ���� ��������� ��������� "PERSONS" � �������� "ID"  (64)����',
'SCHEMA', 'dbo',
'TABLE', 'PHONE_NUMBERS',
'COLUMN', 'PERSON_ID'

exec sp_addextendedproperty
'MS_Description',
'������������ �������� ���� ��������� ��������� "PHONE_NUMBERS" � �������� "ID"  (64)����',
'SCHEMA', 'dbo',
'TABLE', 'PHONE_NUMBERS',
'COLUMN', 'PHONE_TYPE_ID'

exec sp_addextendedproperty
'MS_Description',
'������� ����������� (������������ �����) ��������� ����� (32)����',
'SCHEMA', 'dbo',
'TABLE', 'PHONE_NUMBERS',
'COLUMN', 'PHONE_NUMBER'

ALTER TABLE [PHONE_NUMBERS]
ADD CONSTRAINT [FK_PHONE_NUMBERS_PERSON_ID]
			FOREIGN KEY  ([PERSON_ID]) 
			REFERENCES [PERSONS] ([ID])
			ON DELETE CASCADE,

CONSTRAINT [FK_PHONE_NUMBERS_PHONE_TYPE_ID]
			FOREIGN KEY ([PHONE_TYPE_ID])
			REFERENCES [PHONE_TYPES] ([ID])

CREATE NONCLUSTERED INDEX IX_PHONE_NUMBERS_PHONE_NUMBER
ON [PHONE_NUMBERS]([PHONE_NUMBER] ASC)



