USE [PhoneBook]

DROP TABLE IF EXISTS [PHONE_NUMBERS]
DROP TABLE IF EXISTS [PERSONS]
DROP TABLE IF EXISTS [CITIES]
DROP TABLE IF EXISTS [PHONE_TYPES]

CREATE TABLE
	[CITIES]
	(
		[ID] INT IDENTITY (1,1) NOT NULL,
		[UPDATE_COUNTER] INT NOT NULL,
		[CITY_NAME] NVARCHAR(32)NOT NULL UNIQUE,
		[AREA_NAME] NVARCHAR(32)NOT NULL,
		[POSTAL_CODE] INT NOT NULL,
		CONSTRAINT [PK_CITIES_ID]
		PRIMARY KEY ([ID])
	)
EXEC sp_addextendedproperty @name='CITIES_Table_Description', 
@value='Таблица съдържаща инфрормацията за градовете.',
@level0type=N'SCHEMA',@level0name=N'dbo', 
@level1type=N'TABLE',@level1name=N'CITIES'

exec sp_AddExtendedProperty
'MS_Description',
'Уникален идентификатор на запис в таблицата (32)бита',
'SCHEMA', 'dbo',
'TABLE', 'CITIES',
'COLUMN', 'ID'

exec sp_AddExtendedProperty
'MS_Description',
'Версия на ред (32)бита (задължителен запис)',
'SCHEMA', 'dbo',
'TABLE', 'CITIES',
'COLUMN', 'UPDATE_COUNTER'

exec sp_addextendedproperty
'MS_Description',
'Таблица съдържаща (задължителен запис) областите (512)бита',
'SCHEMA', 'dbo',
'TABLE', 'CITIES',
'COLUMN', 'CITY_NAME'

exec sp_addextendedproperty
'MS_Description',
'Таблица съдържаща (задължителен запис) градовете (512)бита',
'SCHEMA', 'dbo',
'TABLE', 'CITIES',
'COLUMN', 'AREA_NAME'

exec sp_addextendedproperty
'MS_Description',
'Таблица съдържаща (задължителен запис) пощенските кодове (32)бита',
'SCHEMA', 'dbo',
'TABLE', 'CITIES',
'COLUMN', 'POSTAL_CODE'
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
EXEC sp_addextendedproperty @name='PHONE_TYPES_Table_Description', 
@value='Таблица съдържаща инфрормацията за типовете телефони.',
@level0type=N'SCHEMA',@level0name=N'dbo', 
@level1type=N'TABLE',@level1name=N'PHONE_TYPES'

exec sp_addextendedproperty
'MS_Description',
'Уникален идентификатор на запис в таблицата (32)бита',
'SCHEMA', 'dbo',
'TABLE', 'PHONE_TYPES',
'COLUMN', 'ID'

exec sp_addextendedproperty
'MS_Description',
'Версия на ред (32)бита (задължителен запис)',
'SCHEMA', 'dbo',
'TABLE', 'PHONE_TYPES',
'COLUMN', 'UPDATE_COUNTER'

exec sp_addextendedproperty
'MS_Description',
'Колона съдържаща (задължителен запис) типовете телефони (128)бита',
'SCHEMA', 'dbo',
'TABLE', 'PHONE_TYPES',
'COLUMN', 'PHONE_TYPE'

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
EXEC sp_addextendedproperty @name='PERSONS_Table_Description', 
@value='Таблица съдържаща инфрормацията за хора.',
@level0type=N'SCHEMA',@level0name=N'dbo', 
@level1type=N'TABLE',@level1name=N'PERSONS'



exec sp_addextendedproperty
'MS_Description',
'Уникален идентификатор на запис в таблицата (32)бита',
'SCHEMA', 'dbo',
'TABLE', 'PERSONS',
'COLUMN', 'ID'

exec sp_addextendedproperty
'MS_Description',
'Версия на ред (32)бита (задължителен запис)',
'SCHEMA', 'dbo',
'TABLE', 'PERSONS',
'COLUMN', 'UPDATE_COUNTER'

exec sp_addextendedproperty
'MS_Description',
'Таблица съхраняваща (задължителен запис) името (256)бита',
'SCHEMA', 'dbo',
'TABLE', 'PERSONS',
'COLUMN', 'FIRST_NAME'

exec sp_addextendedproperty
'MS_Description',
'Таблица съхраняваща (задължителен запис) презимето (256)бита',
'SCHEMA', 'dbo',
'TABLE', 'PERSONS',
'COLUMN', 'SECOND_NAME'

exec sp_addextendedproperty
'MS_Description',
'Таблица съхраняваща (задължителен запис) фамилията (256)бита',
'SCHEMA', 'dbo',
'TABLE', 'PERSONS',
'COLUMN', 'LAST_NAME'

exec sp_addextendedproperty
'MS_Description',
'Таблица съхраняваща (задължителен запис) егн-то (64)бита',
'SCHEMA', 'dbo',
'TABLE', 'PERSONS',
'COLUMN', 'CITY_ID'

exec sp_addextendedproperty
'MS_Description',
'Задължителен вторичен ключ рефериращ таблицата "CITTIES" и колоната "ID"  (64)бита',
'SCHEMA', 'dbo',
'TABLE', 'PERSONS',
'COLUMN', 'UCN'

exec sp_addextendedproperty
'MS_Description',
'Таблица съхраняваща (задължителен запис) егн-то (512)бита',
'SCHEMA', 'dbo',
'TABLE', 'PERSONS',
'COLUMN', 'ADDRESS'

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
	EXEC sp_addextendedproperty @name='PHONE_NUMBERS_Table_Description', 
@value='Таблица съдържаща инфрормацията за телефонни номера, типове телефони и хора.',
@level0type=N'SCHEMA',@level0name=N'dbo', 
@level1type=N'TABLE',@level1name=N'PHONE_NUMBERS'

exec sp_addextendedproperty
'MS_Description',
'Уникален идентификатор на запис в таблицата (32)бита',
'SCHEMA', 'dbo',
'TABLE', 'PHONE_NUMBERS',
'COLUMN', 'ID'

exec sp_addextendedproperty
'MS_Description',
'Версия на ред (32)бита (задължителен запис)',
'SCHEMA', 'dbo',
'TABLE', 'PHONE_NUMBERS',
'COLUMN', 'UPDATE_COUNTER'

exec sp_addextendedproperty
'MS_Description',
'Задължителен вторичен ключ рефериращ таблицата "PERSONS" и колоната "ID"  (64)бита',
'SCHEMA', 'dbo',
'TABLE', 'PHONE_NUMBERS',
'COLUMN', 'PERSON_ID'

exec sp_addextendedproperty
'MS_Description',
'Задължителен вторичен ключ рефериращ таблицата "PHONE_NUMBERS" и колоната "ID"  (64)бита',
'SCHEMA', 'dbo',
'TABLE', 'PHONE_NUMBERS',
'COLUMN', 'PHONE_TYPE_ID'

exec sp_addextendedproperty
'MS_Description',
'Таблица съхраняваща (задължителен запис) телефонен номер (32)бита',
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



