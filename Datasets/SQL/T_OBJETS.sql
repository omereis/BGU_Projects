USE DATASETS;

DROP TABLE IF EXISTS T_OBJECTS;

CREATE TABLE T_OBJECTS (
  OBJECT_ID INT(11) NOT NULL,
  DATASET_ID INT(11) NOT NULL,
  OBJ_NAME VARCHAR(25),
  OBJ_TYPE VARCHAR(25),
  PRIMARY KEY (OBJECT_ID)
) ENGINE=INNODB DEFAULT CHARSET=utf8;

/*Data for the table t_objects */

INSERT  INTO T_OBJECTS(OBJECT_ID,DATASET_ID,OBJ_NAME,OBJ_TYPE) VALUES (1,2,'o1',NULL);
