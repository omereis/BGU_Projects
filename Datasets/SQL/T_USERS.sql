USE DATASETS;

DROP TABLE IF EXISTS T_USERS;

CREATE TABLE T_USERS (
  USER_ID	INT(11) NOT NULL,
  USERNAME	VARCHAR(50) NOT NULL,
  PASSWD	VARCHAR(50) DEFAULT NULL,
  FIRST_NAME	VARCHAR(50) DEFAULT NULL,
  LAST_NAME	VARCHAR(50) DEFAULT NULL,
  PRIMARY KEY (USER_ID,USERNAME),
  UNIQUE (USERNAME)
);
