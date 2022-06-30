declare @Path varchar(100)
set @Path = 'C:\Users\Public\Desktop\DATA'
EXEC master.dbo.xp_create_subdir @Path

DROP DATABASE IF EXISTS [PhoneBook]

CREATE DATABASE [PhoneBook]
ON PRIMARY
  ( NAME='PhoneBook_Primary',
    FILENAME=
       'C:\Users\Public\Desktop\DATA\PhoneBook_Prm.mdf',
    SIZE=500MB,
    MAXSIZE=700MB,
    FILEGROWTH=1MB),
FILEGROUP MyDB_FG1
  ( NAME = 'PhoneBook_FG1_Dat1',
    FILENAME =
       'C:\Users\Public\Desktop\DATA\PhoneBook_FG1_Dat1.mdf',
    SIZE = 1MB,
    MAXSIZE=10MB,
    FILEGROWTH=1MB),
  ( NAME = 'PhoneBook_FG1_Dat2',
    FILENAME =
	'C:\Users\Public\Desktop\DATA\PhoneBook_FG1_2.ndf',
    SIZE = 1MB,
    MAXSIZE=10MB,
    FILEGROWTH=1MB)
