-- MySQL dump 10.13  Distrib 8.0.30, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: banksimul
-- ------------------------------------------------------
-- Server version	8.0.29

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `asiakas`
--

DROP TABLE IF EXISTS `asiakas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `asiakas` (
  `id_asiakas` int NOT NULL AUTO_INCREMENT,
  `fname` varchar(45) DEFAULT NULL,
  `lname` varchar(45) DEFAULT NULL,
  `address` varchar(255) DEFAULT NULL,
  `phoneNumber` varchar(13) DEFAULT NULL,
  PRIMARY KEY (`id_asiakas`),
  UNIQUE KEY `id_asiakas_UNIQUE` (`id_asiakas`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `asiakas`
--

LOCK TABLES `asiakas` WRITE;
/*!40000 ALTER TABLE `asiakas` DISABLE KEYS */;
INSERT INTO `asiakas` VALUES (1,'Masa','Nuutinpoika','Jeboukatu 1, 96200 Rovaniemi','+358507869999'),(2,'Maija','Nuutintyttö','Jeboukatu 2, 90250 Oulu','+358507869666');
/*!40000 ALTER TABLE `asiakas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `kortinoikeus`
--

DROP TABLE IF EXISTS `kortinoikeus`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `kortinoikeus` (
  `id_oikeus` int NOT NULL,
  `id_tili` char(10) NOT NULL,
  `id_card` char(10) NOT NULL,
  PRIMARY KEY (`id_oikeus`),
  UNIQUE KEY `id_oikeus_UNIQUE` (`id_oikeus`),
  KEY `id_tili_idx` (`id_tili`),
  KEY `id_card_idx` (`id_card`) /*!80000 INVISIBLE */,
  CONSTRAINT `id_card_ko` FOREIGN KEY (`id_card`) REFERENCES `tunnus` (`id_card`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `id_tili_ko` FOREIGN KEY (`id_tili`) REFERENCES `tili` (`id_tili`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `kortinoikeus`
--

LOCK TABLES `kortinoikeus` WRITE;
/*!40000 ALTER TABLE `kortinoikeus` DISABLE KEYS */;
INSERT INTO `kortinoikeus` VALUES (1,'12345KGBQW','1122334455');
/*!40000 ALTER TABLE `kortinoikeus` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tili`
--

DROP TABLE IF EXISTS `tili`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tili` (
  `id_tili` char(10) NOT NULL,
  `account_balance` float DEFAULT NULL,
  PRIMARY KEY (`id_tili`),
  UNIQUE KEY `id_tili_UNIQUE` (`id_tili`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tili`
--

LOCK TABLES `tili` WRITE;
/*!40000 ALTER TABLE `tili` DISABLE KEYS */;
INSERT INTO `tili` VALUES ('12345KGBQW',400.14);
/*!40000 ALTER TABLE `tili` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tilioikeus`
--

DROP TABLE IF EXISTS `tilioikeus`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tilioikeus` (
  `id_tilioikeus` int NOT NULL,
  `id_tili` char(10) NOT NULL,
  `id_asiakas` int NOT NULL,
  PRIMARY KEY (`id_tilioikeus`),
  UNIQUE KEY `id_tilioikeus_UNIQUE` (`id_tilioikeus`),
  KEY `id_tili_idx` (`id_tili`),
  KEY `id_asiakas_idx` (`id_asiakas`),
  CONSTRAINT `id_asiakas` FOREIGN KEY (`id_asiakas`) REFERENCES `asiakas` (`id_asiakas`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `id_tili` FOREIGN KEY (`id_tili`) REFERENCES `tili` (`id_tili`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tilioikeus`
--

LOCK TABLES `tilioikeus` WRITE;
/*!40000 ALTER TABLE `tilioikeus` DISABLE KEYS */;
INSERT INTO `tilioikeus` VALUES (1,'12345KGBQW',1);
/*!40000 ALTER TABLE `tilioikeus` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tilitapahtuma`
--

DROP TABLE IF EXISTS `tilitapahtuma`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tilitapahtuma` (
  `id_tapahtuma` int NOT NULL AUTO_INCREMENT,
  `id_tili` char(10) NOT NULL,
  `date` datetime DEFAULT NULL,
  `transaction` varchar(45) DEFAULT NULL,
  `amount` float DEFAULT NULL,
  `id_card` char(10) NOT NULL,
  PRIMARY KEY (`id_tapahtuma`),
  UNIQUE KEY `id_tapahtuma_UNIQUE` (`id_tapahtuma`),
  KEY `id_tili_idx` (`id_tili`),
  CONSTRAINT `id_tili_tt` FOREIGN KEY (`id_tili`) REFERENCES `tili` (`id_tili`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tilitapahtuma`
--

LOCK TABLES `tilitapahtuma` WRITE;
/*!40000 ALTER TABLE `tilitapahtuma` DISABLE KEYS */;
INSERT INTO `tilitapahtuma` VALUES (1,'12345KGBQW','2022-12-09 04:03:45','Nosto',100,'1122334455'),(2,'12345KGBQW','2022-12-09 04:04:16','Nosto',250,'1122334455'),(3,'12345KGBQW','2022-12-09 04:04:24','Nosto',500,'1122334455');
/*!40000 ALTER TABLE `tilitapahtuma` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tunnus`
--

DROP TABLE IF EXISTS `tunnus`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tunnus` (
  `id_card` char(10) NOT NULL,
  `card_pin` varchar(255) NOT NULL,
  `id_asiakas` int NOT NULL,
  `lukitus` tinyint DEFAULT NULL,
  PRIMARY KEY (`id_card`),
  UNIQUE KEY `id_card_UNIQUE` (`id_card`),
  KEY `id_asiakas_idx` (`id_asiakas`),
  CONSTRAINT `id_asiakas_tunnus` FOREIGN KEY (`id_asiakas`) REFERENCES `asiakas` (`id_asiakas`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tunnus`
--

LOCK TABLES `tunnus` WRITE;
/*!40000 ALTER TABLE `tunnus` DISABLE KEYS */;
INSERT INTO `tunnus` VALUES ('1122334455','$2a$10$ktZFsmdNXj9Bs1NesJBgguzfvjzEl7Qv7Ydpc8O04GxSFVQR9756C',1,7),('1234567890','$2a$10$84i7Uzyulby6KaeDfBiJFeCpLZVnFy2iIab3qOkz.859tVR1OS16K',1,0),('5555566666','$2a$10$ea/Ar3j3MG1bdYEY00j3auy4RG8NRzS9Up1kax98UXC.1X/0bE1nu',1,0);
/*!40000 ALTER TABLE `tunnus` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-12-10 20:36:19
