USE [PhoneBook]

ALTER TABLE 	[PERSONS]
DROP CONSTRAINT IF EXISTS [FK_PERSONS_CITY_ID];

ALTER TABLE 	[PHONE_NUMBERS]
DROP CONSTRAINT IF EXISTS	[FK_PHONE_NUMBERS_PERSON_ID], 
				[FK_PHONE_NUMBERS_PHONE_TYPE_ID];

DROP TABLE IF EXISTS [CITIES]
CREATE TABLE
	[CITIES]
	(
		[ID] INT IDENTITY (1,1) NOT NULL,
		[UPDATE_COUNTER] INT NOT NULL,
		[CITY_NAME] NVARCHAR(50)NOT NULL,
		[AREA_NAME] NVARCHAR(40)NOT NULL,
		[POSTAL_CODE] INT NOT NULL,
		CONSTRAINT [PK_CITIES_ID]
		PRIMARY KEY CLUSTERED ([ID])
	)


DROP TABLE IF EXISTS [PHONE_TYPES]
CREATE TABLE
	[PHONE_TYPES]
	(
		[ID] INT IDENTITY (1,1) NOT NULL,
		[UPDATE_COUNTER] INT,
		[PHONE_TYPE] VARCHAR(6) UNIQUE,
		CONSTRAINT [CK_PHONE_TYPES_PHONE_TYPE]
				CHECK (
						[PHONE_TYPE]='Mobile' 
						OR [PHONE_TYPE]='Home'
						OR [PHONE_TYPE]='Work'
					  ),
		CONSTRAINT [PK_PHONE_TYPES_ID]
		PRIMARY KEY CLUSTERED ([ID])
	)


DROP TABLE IF EXISTS [PERSONS]
CREATE TABLE
	[PERSONS]
	(
		[ID] INT IDENTITY (1,1) NOT NULL,
		[UPDATE_COUNTER] INT NOT NULL,
		[FIRST_NAME] NVARCHAR(40) NOT NULL,
		[SECOND_NAME] NVARCHAR(40) NOT NULL,
		[LAST_NAME] NVARCHAR(50) NOT NULL,
		[CITY_ID] INT NOT NULL,
		[ADDRESS] NVARCHAR(200) NOT NULL,
		CONSTRAINT [FK_PERSONS_CITY_ID] 
		FOREIGN KEY ([CITY_ID])
		REFERENCES [CITIES]([ID]),
		CONSTRAINT [PK_PERSONS_ID]
		PRIMARY KEY CLUSTERED([ID])
	)


DROP TABLE IF EXISTS [PHONE_NUMBERS]
CREATE TABLE
	[PHONE_NUMBERS]
	(
		[ID] INT IDENTITY (1,1) NOT NULL, 
		[UPDATE_COUNTER] INT NOT NULL,
		[PERSON_ID] INT NOT NULL,
		[PHONE_TYPE_ID] INT NOT NULL,
		[PHONE_NUMBER]
		VARCHAR(10) NOT NULL,

		CONSTRAINT CK_PHONE_NUMBERS_PHONE_NUMBER
			CHECK (LEN([PHONE_NUMBER])=10 ),

		CONSTRAINT [FK_PHONE_NUMBERS_PERSON_ID]
			FOREIGN KEY  ([PERSON_ID]) 
			REFERENCES [PERSONS] ([ID])
			ON DELETE CASCADE,

		CONSTRAINT [FK_PHONE_NUMBERS_PHONE_TYPE_ID]
			FOREIGN KEY ([PHONE_TYPE_ID])
			REFERENCES [PHONE_TYPES] ([ID]),

		CONSTRAINT [PK_PHONE_NUMBERS_ID]
			PRIMARY KEY CLUSTERED([ID])
	)