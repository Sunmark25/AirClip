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