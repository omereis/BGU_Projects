USE DATASETS;

DROP TABLE IF EXISTS T_CONTACTS;

CREATE TABLE T_CONTACTS
(
	CONTACT_ID	INTEGER NOT NULL PRIMARY KEY,
	DATASET_ID	INTEGER,
	CONTACT_NAME	VARCHAR(100),
	PHONE			VARCHAR (20),
	EMAIL			VARCHAR (100),
	COMMENTS		VARCHAR (100)
);