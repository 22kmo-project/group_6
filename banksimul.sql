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
  `id_user` int NOT NULL,
  `fname` varchar(45) DEFAULT NULL,
  `lname` varchar(45) DEFAULT NULL,
  `address` varchar(45) DEFAULT NULL,
  `phoneNumber` varchar(12) DEFAULT NULL,
  PRIMARY KEY (`id_user`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `asiakas`
--

LOCK TABLES `asiakas` WRITE;
/*!40000 ALTER TABLE `asiakas` DISABLE KEYS */;
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
  `id_card` int NOT NULL,
  PRIMARY KEY (`id_oikeus`),
  KEY `id_tili_idx` (`id_tili`),
  KEY `id_card_idx` (`id_card`),
  CONSTRAINT `id_card_ko` FOREIGN KEY (`id_card`) REFERENCES `tunnus` (`id_card`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `id_tili_ko` FOREIGN KEY (`id_tili`) REFERENCES `tili` (`id_tili`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `kortinoikeus`
--

LOCK TABLES `kortinoikeus` WRITE;
/*!40000 ALTER TABLE `kortinoikeus` DISABLE KEYS */;
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
  `account_balance` int DEFAULT NULL,
  `id_card` int NOT NULL,
  PRIMARY KEY (`id_tili`),
  UNIQUE KEY `id_tili_UNIQUE` (`id_tili`),
  KEY `id_card_idx` (`id_card`),
  CONSTRAINT `id_card` FOREIGN KEY (`id_card`) REFERENCES `kortinoikeus` (`id_card`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tili`
--

LOCK TABLES `tili` WRITE;
/*!40000 ALTER TABLE `tili` DISABLE KEYS */;
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
  `id_user` int NOT NULL,
  PRIMARY KEY (`id_tilioikeus`),
  KEY `id_tili_idx` (`id_tili`),
  KEY `id_user_idx` (`id_user`),
  CONSTRAINT `id_tili` FOREIGN KEY (`id_tili`) REFERENCES `tili` (`id_tili`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `id_user` FOREIGN KEY (`id_user`) REFERENCES `asiakas` (`id_user`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tilioikeus`
--

LOCK TABLES `tilioikeus` WRITE;
/*!40000 ALTER TABLE `tilioikeus` DISABLE KEYS */;
/*!40000 ALTER TABLE `tilioikeus` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tilitapahtumat`
--

DROP TABLE IF EXISTS `tilitapahtumat`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tilitapahtumat` (
  `id_tapahtuma` int NOT NULL AUTO_INCREMENT,
  `id_tili` char(10) NOT NULL,
  `date` datetime DEFAULT NULL,
  `transaction` varchar(45) DEFAULT NULL,
  `amount` int DEFAULT NULL,
  `id_card` int NOT NULL,
  PRIMARY KEY (`id_tapahtuma`),
  KEY `id_tili_idx` (`id_tili`),
  KEY `id_card_idx` (`id_card`),
  CONSTRAINT `id_card_tt` FOREIGN KEY (`id_card`) REFERENCES `tili` (`id_card`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `id_tili_tt` FOREIGN KEY (`id_tili`) REFERENCES `tili` (`id_tili`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tilitapahtumat`
--

LOCK TABLES `tilitapahtumat` WRITE;
/*!40000 ALTER TABLE `tilitapahtumat` DISABLE KEYS */;
/*!40000 ALTER TABLE `tilitapahtumat` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tunnus`
--

DROP TABLE IF EXISTS `tunnus`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tunnus` (
  `id_card` int NOT NULL,
  `card_pin` int DEFAULT NULL,
  PRIMARY KEY (`id_card`),
  UNIQUE KEY `id_card_UNIQUE` (`id_card`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tunnus`
--

LOCK TABLES `tunnus` WRITE;
/*!40000 ALTER TABLE `tunnus` DISABLE KEYS */;
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

-- Dump completed on 2022-11-21 11:51:19
