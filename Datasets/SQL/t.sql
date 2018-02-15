/*
SQLyog Community v9.20 
MySQL - 5.5.15 : Database - datasets
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
CREATE DATABASE /*!32312 IF NOT EXISTS*/`datasets` /*!40100 DEFAULT CHARACTER SET utf8 */;

USE `datasets`;

/*Table structure for table `t_objects` */

DROP TABLE IF EXISTS `t_objects`;

CREATE TABLE `t_objects` (
  `OBJECT_ID` int(11) NOT NULL,
  `DATASET_ID` int(11) NOT NULL,
  `OBJ_NAME` varchar(25) DEFAULT NULL,
  `OBJ_TYPE` varchar(25) DEFAULT NULL,
  PRIMARY KEY (`OBJECT_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Data for the table `t_objects` */

insert  into `t_objects`(`OBJECT_ID`,`DATASET_ID`,`OBJ_NAME`,`OBJ_TYPE`) values (1,2,'o1',NULL);

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
