USE DATASETS;

DROP TABLE IF EXISTS T_OBJECTS;

CREATE TABLE T_OBJECTS (
  OBJECT_ID INT(11) NOT NULL,
  DATASET_ID INT(11),
  OBJ_NAME VARCHAR(25),
  OBJ_TYPE VARCHAR(25),
  PRIMARY KEY (OBJECT_ID)
) ENGINE=INNODB DEFAULT CHARSET=utf8;

ALTER TABLE T_OBJECTS ADD FOREIGN KEY FK_T_OBJ_DS (DATASET_ID) REFERENCES T_DATASETS (DATASET_ID) ON UPDATE CASCADE ON DELETE CASCADE;

/*Data for the table t_objects */

/*
INSERT  INTO T_OBJECTS(OBJECT_ID) VALUES (1);
*/

