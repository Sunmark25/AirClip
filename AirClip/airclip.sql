CREATE TABLE IF NOT EXISTS User (
    userID VARCHAR(6) PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE,
    password TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS ClipboardEntry (
    clipboardEntryID VARCHAR(8) PRIMARY KEY AUTOINCREMENT,
    timeAdded TEXT,
    deviceID VARCHAR(6) NOT NULL,
    userTag TEXT,
    content TEXT,
    contentPath TEXT
);

CREATE TABLE IF NOT EXISTS Device(
    deviceID VARCHAR(6) PRIMARY KEY AUTOINCREMENT,
    deviceName TEXT NOT NULL,
    userID VARCHAR(6) NOT NULL
);

-- Time Format Must use ISO8601 string format
-- YYYY-MM-DD_HH:MM:SS
-- E.g. 2016-12-01_18:20:05


-- -------------- TABLES THAT WORK WITH QUERIES --------------

DROP TABLE AIRCLIP;

CREATE TABLE IF NOT EXISTS AIRCLIP (
                                       userName TEXT NOT NULL,
                                       userID INTEGER PRIMARY KEY AUTOINCREMENT,
                                       deviceID INTEGER NOT NULL UNIQUE,
                                       deviceName TEXT NOT NULL
);

DROP TABLE CLIPBOARDENTRY;

CREATE TABLE IF NOT EXISTS CLIPBOARDENTRY (
                                              clipboardEntryID INTEGER PRIMARY KEY AUTOINCREMENT,
                                              userID INTEGER NOT NULL,
                                              content TEXT,
                                              contentPath TEXT,
                                              contentType TEXT NOT NULL,
                                              CONSTRAINT contentType CHECK (contentType IN ('text', 'image', 'file'))
);


INSERT INTO AIRCLIP (userName, deviceID, deviceName)
VALUES ('Peter', 1, 'hpLaptop');

SELECT * FROM AIRCLIP;

SELECT * FROM CLIPBOARDENTRY;


-- -------------- User tables --------------

-- DROP TABLE User;

CREATE TABLE IF NOT EXISTS User (
                                    userID INTEGER PRIMARY KEY AUTOINCREMENT,
                                    username TEXT NOT NULL,
                                    password TEXT NOT NULL,
                                    fullName TEXT NOT NULL
);


INSERT INTO User (username, password, fullName)
VALUES ('jboersen', 'Password123', 'Jarrett Boersen');

INSERT INTO User (username, password, fullName)
VALUES ('jsmith', 'Password123!', 'John Smith');

INSERT INTO User (username, password, fullName)
VALUES ('tcook', 'I<3Apple!', 'Tim Cook');


select * from User;

select * from Device;

select * from ClipboardEntry;


SELECT * FROM ClipboardEntry WHERE deviceID = 1 ORDER BY timeAdded DESC LIMIT 1;

select * from Device inner join User on User.userID=Device.userID where User.userID=1;

SELECT * FROM ClipboardEntry WHERE deviceID = (SELECT Device.deviceID FROM Device INNER JOIN User ON User.userID=Device.userID WHERE User.userID=1) ORDER BY timeAdded DESC LIMIT 1;
SELECT * FROM ClipboardEntry WHERE deviceID = (SELECT Device.deviceID FROM Device INNER JOIN User ON User.userID=Device.userID WHERE User.username='Benz') ORDER BY timeAdded DESC LIMIT 1;


-- Shows database data
select *
from sqlite_master;