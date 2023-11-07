CREATE TABLE IF NOT EXISTS AIRCLIP (
    userName TEXT NOT NULL,
    userID VARCHAR(6) PRIMARY KEY CHECK (userID GLOB 'us[a-z][a-z][0-9][0-9]'),
    deviceID VARCHAR(6) NOT NULL UNIQUE CHECK (deviceID GLOB 'de[a-z][a-z][0-9][0-9]'),
    deviceName TEXT NOT NULL
);


INSERT INTO AIRCLIP (userName, userID, deviceID, deviceName)
VALUES ('Peter', 'uspe00', 'depe00', 'hpLaptop');


-- userID format -> us(a-z)(a-z)(0-9)(0-9)
-- deviceID format -> de(a-z)(a-z)(0-9)(0-9)


-- -------------- User tables --------------

DROP TABLE User;

CREATE TABLE IF NOT EXISTS User (
    userID INTEGER PRIMARY KEY AUTOINCREMENT,
    userName TEXT NOT NULL,
    username TEXT NOT NULL,
    password TEXT NOT NULL
);


INSERT INTO User (username, password)
VALUES ('jboersen', 'Password123');

INSERT INTO User (username, password)
VALUES ('jboersen2', 'Password123!');

INSERT INTO User (username, password)
VALUES ('kboersen', 'Password123?');


select *
from User;

-- Shows database data
select *
from sqlite_master;