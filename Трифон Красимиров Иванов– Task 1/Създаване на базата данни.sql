DECLARE @DATABASE_FILE_PATH VARCHAR(100) = 'C:\Users\Public\Desktop\DATA'

DROP DATABASE IF EXISTS [PhoneBook]

CREATE DATABASE [PhoneBook]
ON PRIMARY
  ( NAME='PhoneBook_Primary',
    FILENAME=
       'C:\Users\Public\Desktop\DATA\PhoneBook_Prm.mdf',
    SIZE=1GB,
    MAXSIZE=5GB,
    FILEGROWTH=10%),
FILEGROUP MyDB_FG1
  ( NAME = 'PhoneBook_FG1_Dat1',
    FILENAME =
       'C:\Users\Public\Desktop\DATA\PhoneBook_FG1_Dat1.mdf',
    SIZE = 1MB,
    MAXSIZE=10MB,
    FILEGROWTH=10%),
  ( NAME = 'PhoneBook_FG1_Dat2',
    FILENAME =
	'C:\Users\Public\Desktop\DATA\PhoneBook_FG1_2.ndf',
    SIZE = 1MB,
    MAXSIZE=10MB,
    FILEGROWTH=10%)
