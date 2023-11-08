CREATE TABLE IF NOT EXISTS AIRCLIP (
    userName TEXT NOT NULL,
    userID VARCHAR(6) PRIMARY KEY CHECK (userID GLOB 'us[a-z][a-z][0-9][0-9]'),
    deviceID VARCHAR(6) NOT NULL UNIQUE CHECK (deviceID GLOB 'de[a-z][a-z][0-9][0-9]'),
    deviceName TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS CLIPBOARDENTRY (
    clipboardEntryID VARCHAR(8) PRIMARY KEY AUTOINCREMENT,
    userID VARCHAR(6) NOT NULL UNIQUE,
    content TEXT,
    contentPath TEXT,
    contentType TEXT NOT NULL,
    CONSTRAINT contentType CHECK (contentType IN ('text', 'image', 'file'))
    );


INSERT INTO AIRCLIP (userName, userID, deviceID, deviceName)
VALUES ('Peter', 'uspe00', 'depe00', 'hpLaptop');



-- userID format -> us(a-z)(a-z)(0-9)(0-9)
-- deviceID format -> de(a-z)(a-z)(0-9)(0-9)
-- clipboardEntryID -> cl(0-9)(0-9)(0-9)(0-9)(0-9)(0-9)


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


select *
from User;

-- Shows database data
select *
from sqlite_master;