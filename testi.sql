-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: 24.11.2022 klo 19:17
-- Palvelimen versio: 8.0.31
-- PHP Version: 7.3.31-1~deb10u1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `bankdb`
--

DELIMITER $$
--
-- Proseduurit
--
CREATE DEFINER=`bank`@`%` PROCEDURE `balance` (IN `account` VARCHAR(20))   BEGIN
  update account set balance = balance-1 where idaccount=account;
  SELECT balance FROM account WHERE idaccount=account;
  END$$

CREATE DEFINER=`bank`@`%` PROCEDURE `transaction` (IN `transfer_account` INT, IN `amount` INT)   BEGIN 
DECLARE test1 INT default 0;
start TRANSACTION;
UPDATE account SET balance=balance-amount WHERE 
(idaccount=transfer_account AND balance>=amount) 
OR (idaccount=transfer_account AND credit<=balance-amount);
SET test1=ROW_COUNT();
IF (test1 > 0) THEN
COMMIT;
select balance from account where idaccount=transfer_account;
    ELSE
      ROLLBACK;
END IF;
END$$

DELIMITER ;

-- --------------------------------------------------------

--
-- Rakenne taululle `account`
--

CREATE TABLE `account` (
  `idaccount` varchar(20) NOT NULL,
  `cardnum` varchar(20) NOT NULL,
  `balance` decimal(19,4) DEFAULT NULL,
  `credit` decimal(19,4) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;

--
-- Vedos taulusta `account`
--

INSERT INTO `account` (`idaccount`, `cardnum`, `balance`, `credit`) VALUES
('10975', '18748397', '-800.0000', '-6000.0000'),
('18237', '18748397', '1272.0000', '0.0000'),
('28493', '85484187', '0.0000', '-2000.0000'),
('40816', '62027799', '848.0000', '0.0000'),
('44685', '98600838', '1224.0000', '0.0000'),
('49922', '92455754', '1312.0000', '0.0000'),
('58870', '87666351', '0.0000', '0.0000'),
('61109', '56641758', '88.0000', '0.0000'),
('66600', '08939469', '1112.0000', '0.0000'),
('67066', '63667722', '136.0000', '0.0000'),
('69308', '62027799', '0.0000', '-3000.0000'),
('7007', '02727495', '0.0000', '-7000.0000'),
('80315', '85484187', '1104.0000', '0.0000'),
('83610', '34940070', '1072.0000', '0.0000'),
('84968', '65941290', '1768.0000', '0.0000'),
('96205', '02727495', '288.0000', '0.0000'),
('97752', '87666351', '1480.0000', '0.0000'),
('98188', '77145500', '688.0000', '0.0000'),
('9943', '69333363', '-500.0000', '-6000.0000'),
('99966', '69333363', '125.0000', '0.0000');

--
-- Herättimet `account`
--
DELIMITER $$
CREATE TRIGGER `banklog` AFTER UPDATE ON `account` FOR EACH ROW BEGIN
IF (old.balance<new.balance  ) THEN
INSERT INTO log VALUES(NULL,NEW.idaccount,new.balance-old.balance,now(),'deposit_DBT');
ELSE IF (new.balance<0 AND old.balance>new.balance) THEN
INSERT INTO log VALUES(NULL,NEW.idaccount,old.balance-new.balance,now(),'withdrawal_CRD');
ELSE IF (old.balance>new.balance AND new.balance >= 0) THEN
INSERT INTO log VALUES(NULL,NEW.idaccount,old.balance-new.balance,now(),'withdrawal_DBT');
ELSE 
INSERT INTO log VALUES(NULL,NEW.idaccount,'0',now(),'dbError');
END IF;
END IF;
END IF;
END
$$
DELIMITER ;

-- --------------------------------------------------------

--
-- Rakenne taululle `card`
--

CREATE TABLE `card` (
  `cardnum` varchar(20) NOT NULL,
  `cardpin` varchar(255) NOT NULL,
  `iduser` int NOT NULL,
  `iscredit` tinyint(1) NOT NULL,
  `pin_tries` tinyint DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;

--
-- Vedos taulusta `card`
--

INSERT INTO `card` (`cardnum`, `cardpin`, `iduser`, `iscredit`, `pin_tries`) VALUES
('02727495', '$2a$10$yJ4uW0SN4vHLppQPezjSU.kN/g0AxMyYX4w8q4z697Qgz7cXGIvfW', 11, 1, 0),
('08939469', '$2a$10$6Eit9bl0.Z69ZaskGmzeueXCy16R69zGT9.uRJD57cOux9SWhkvWC', 9, 0, 0),
('18748397', '$2a$10$EcCAzoxuC4Ec0ptM//vdHOBPbcUiIVUiTu3gkXsXAmAVaHJeYap1a', 10, 1, 0),
('34940070', '$2a$10$q0AGWzwbaR6vZFhJB4LwE.ss5YiOpRB9eBpfXV3bpAuiRn0Alqs42', 2, 0, 0),
('56641758', '$2a$10$.D7e/BVn87zwbOJWcjR5Juni8LJ2TPT3aOGyrfyRh2LjYdj0F8g92', 5, 0, 0),
('62027799', '$2a$10$sqf7nUUDK/iqid6b323msedRkKBvrW//KyC83KCwodFjHZ.y0ZuCm', 6, 1, 0),
('63667722', '$2a$10$uC.vwoJPKxNK0k/N/Drs0eK.resngCdU9unRE5K8BbdsNZ3zZW3ue', 13, 0, 0),
('65941290', '$2a$10$zw8NSu9Yzt4ipvU1zG3BuO8NXehW6mOrGLxuSKuwVL7x8XuudjzQ.', 8, 0, 0),
('69333363', '$2a$10$563Y.ROLISMpqtHerTxA5eLoHLBsve7WdsT9ekYq8zbi3cEdd7J7W', 14, 1, 0),
('77145500', '$2a$10$9HJ.21wvHisFxGVdBIhBm.XlaDH4sWiV85pYqMS4DG9z2Hffvj/fa', 3, 0, 0),
('85484187', '$2a$10$F8Pv0lzBRiO.8aO.buKZXeM6D69IREErueyD/RX7SaDl4uWZ0EG.a', 1, 1, 0),
('87666351', '$2a$10$lmLhe3FrnoTAlv2FRorHLeefELfIoJXhMSQGXuzEJ9E.P8lcL9aHu', 4, 1, 0),
('92455754', '$2a$10$XFFC9.JGJUGiLFtt8kIONusDGENGpHCLDS.L9HcY7yJhenxT3DmsC', 12, 0, 0),
('98600838', '$2a$10$mct2zEzH3a/e1wYRJBM85O/KImbzMCGr3aOROZH.e1ZKiXC1DJ352', 7, 0, 0);

-- --------------------------------------------------------

--
-- Rakenne taululle `log`
--

CREATE TABLE `log` (
  `idlog` int NOT NULL,
  `idaccount` varchar(20) NOT NULL,
  `withdraw_amount` decimal(19,4) DEFAULT NULL,
  `transaction_time` datetime DEFAULT NULL,
  `transaction_type` varchar(15) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;

--
-- Vedos taulusta `log`
--

INSERT INTO `log` (`idlog`, `idaccount`, `withdraw_amount`, `transaction_time`, `transaction_type`) VALUES
(1, '48086', '20.0000', '2022-11-17 20:35:32', ''),
(2, '99966', '500.0000', '2022-11-24 13:27:46', ''),
(3, '99966', '300.0000', '2022-11-24 13:28:03', ''),
(4, '9943', '500.0000', '2022-11-24 13:34:07', ''),
(5, '99966', '5.0000', '2022-11-24 13:36:35', ''),
(6, '99966', '5.0000', '2022-11-24 13:36:45', ''),
(7, '99966', '5.0000', '2022-11-24 13:36:48', ''),
(8, '99966', '5.0000', '2022-11-24 13:38:50', ''),
(9, '99966', '3.0000', '2022-11-24 14:24:46', ''),
(10, '99966', '2.0000', '2022-11-24 14:35:38', ''),
(11, '99966', '5.0000', '2022-11-24 14:37:54', ''),
(12, '99966', '1.0000', '2022-11-24 17:14:06', ''),
(13, '99966', '1.0000', '2022-11-24 17:14:19', ''),
(15, '10975', '100.0000', '2022-11-24 17:35:31', ''),
(16, '10975', '-100.0000', '2022-11-24 17:37:10', ''),
(19, '99966', '1.0000', '2022-11-24 18:11:00', ''),
(20, '99966', '10.0000', '2022-11-24 19:06:46', 'withdrawal_DBT'),
(21, '10975', '500.0000', '2022-11-24 19:10:39', 'withdrawal_DBT'),
(22, '10975', '100.0000', '2022-11-24 19:12:00', 'withdrawal_DBT'),
(23, '10975', '100.0000', '2022-11-24 19:13:11', 'withdrawal_DBT'),
(24, '10975', '100.0000', '2022-11-24 19:14:02', 'withdrawal_CRD');

-- --------------------------------------------------------

--
-- Rakenne taululle `user`
--

CREATE TABLE `user` (
  `iduser` int NOT NULL,
  `fname` varchar(20) NOT NULL,
  `lname` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;

--
-- Vedos taulusta `user`
--

INSERT INTO `user` (`iduser`, `fname`, `lname`) VALUES
(1, 'Matti', 'Näsä'),
(2, 'Juha', 'Koistinen'),
(3, 'Mauno', 'Ahonen'),
(4, 'Pertti', 'Keinonen'),
(5, 'Sakari', 'Östermalm'),
(6, 'Esko', 'Mörkö'),
(7, 'Gerhard', 'Rihmakallo'),
(8, 'Kalervo', 'Jankko'),
(9, 'Maxwell', 'Gothenburg'),
(10, 'Elmeri', 'Hautamäki'),
(11, 'Dean', 'Kagelberg'),
(12, 'James', 'Kagelberg'),
(13, 'Raili', 'Rasinkangas'),
(14, 'Eugen', 'von Lahtinen');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `account`
--
ALTER TABLE `account`
  ADD PRIMARY KEY (`idaccount`),
  ADD UNIQUE KEY `idaccount_UNIQUE` (`idaccount`),
  ADD KEY `card_idx` (`cardnum`);

--
-- Indexes for table `card`
--
ALTER TABLE `card`
  ADD PRIMARY KEY (`cardnum`),
  ADD UNIQUE KEY `cardnum_UNIQUE` (`cardnum`),
  ADD KEY `user_idx` (`iduser`);

--
-- Indexes for table `log`
--
ALTER TABLE `log`
  ADD PRIMARY KEY (`idlog`),
  ADD KEY `idaccount_idx` (`idaccount`);

--
-- Indexes for table `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`iduser`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `log`
--
ALTER TABLE `log`
  MODIFY `idlog` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=25;

--
-- AUTO_INCREMENT for table `user`
--
ALTER TABLE `user`
  MODIFY `iduser` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=15;

--
-- Rajoitteet vedostauluille
--

--
-- Rajoitteet taululle `account`
--
ALTER TABLE `account`
  ADD CONSTRAINT `card` FOREIGN KEY (`cardnum`) REFERENCES `card` (`cardnum`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Rajoitteet taululle `card`
--
ALTER TABLE `card`
  ADD CONSTRAINT `user` FOREIGN KEY (`iduser`) REFERENCES `user` (`iduser`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Rajoitteet taululle `log`
--
ALTER TABLE `log`
  ADD CONSTRAINT `log_ibfk_1` FOREIGN KEY (`idaccount`) REFERENCES `account` (`idaccount`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;