-- MySQL dump 10.13  Distrib 5.1.41, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: mongooses
-- ------------------------------------------------------
-- Server version	5.1.41-3ubuntu12.10-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `mongooses`
--

DROP TABLE IF EXISTS `mongooses`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `mongooses` (
  `sighting_date` date DEFAULT NULL,
  `description` varchar(500) DEFAULT NULL,
  `id` int(11) NOT NULL,
  `place_name` varchar(500) DEFAULT NULL,
  `uid` int(11) DEFAULT NULL,
  `scientific_name` varchar(100) DEFAULT NULL,
  `common_name` varchar(100) DEFAULT NULL,
  `url` varchar(500) DEFAULT NULL,
  `image_url` varchar(500) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `mongooses`
--

LOCK TABLES `mongooses` WRITE;
/*!40000 ALTER TABLE `mongooses` DISABLE KEYS */;
INSERT INTO `mongooses` VALUES ('2011-10-09','This guy would run through the grass for a few meters  stop  standup on hind legs to get a better view  look around  then run through the grass again. Not sure if it was looking for prey or predators.',34466,'Etosha',998,'Cynictis penicillata','Yellow Mongoose','http://inaturalist.org/observations/34466','http://farm7.static.flickr.com/6115/6223632992_0d3030e8a1_s.jpg'),('2011-09-22','Very large group = 20+.\nThe common dwarf mongoose and Somali dwarf mongoose overlap in W Kenya  but I\'ve never seen a Somali dwarf so am a little unsure of distinguishing marks in such a variable colored species.  Dark color makes me lean common dwarf.',32038,'Tsavo East NP, Kenya',1000,'Helogale','','http://inaturalist.org/observations/32038','http://lh5.ggpht.com/-FT2oGYdAv50/TnsfFPatjRI/AAAAAAAACws/PR0DNDALKAM/s72-c/P1090428.jpg'),('2011-09-04','',29970,'Kottappadi, Kerala, India',1,'Herpestes edwardsii','Indian Grey Mongoose','http://inaturalist.org/observations/29970','http://farm7.static.flickr.com/6071/6111624062_a59c3dd522_s.jpg'),('2011-07-24','A few meters away from a <a href=\"http://www.inaturalist.org/observations/25891\">meerkat family</a>.',25892,'Trans-Kalahari Highway, Botswana',1000,'Cynictis penicillata','Yellow Mongoose','http://inaturalist.org/observations/25892','http://lh4.ggpht.com/-dVC5bSZiGn0/TiwbbMHj-0I/AAAAAAAAB_E/yBL8spAwDpw/s72-c/P1030760.jpg'),('2011-07-14','Location approximate.  Commonly seen.',24855,'Okwa Valley, Ghanzi District, Botswana',1000,'Cynictis penicillata','Yellow Mongoose','http://inaturalist.org/observations/24855','http://lh6.ggpht.com/-IhPoQ1c2Ojk/Th5t_7b0OfI/AAAAAAAABrA/_f04eQaMK5g/s72-c/P1070202.jpg'),('2011-07-07','',24224,'Okwa Valley, Ghanzi District, Botswana',1000,'Herpestes sanguineus','Slender Mongoose','http://inaturalist.org/observations/24224','http://lh4.ggpht.com/-dTLIn5H537M/ThZQUvTDEHI/AAAAAAAABms/DZeDHyotjjI/s72-c/P1070844.jpg'),('2011-05-29','Hawaiian goose  or Nene  that was re-introduced into Hakalau in 1996. It was eradicated due to excessive depredation by mongoose and rats. But it is doing much better today thanks for heavy conservation intervention.  ',18767,'Hakalau Forest, Hawaii, Hawaii',533,'Branta sandvicensis','Hawaiian Goose','http://inaturalist.org/observations/18767','http://static.inaturalist.org/photos/34319/square.jpg'),('2011-05-25','',18355,'Tarangire NP, Tanzania',1000,'Mungos mungo','Banded Mongoose','http://inaturalist.org/observations/18355','http://lh6.ggpht.com/-l_TUvBkNxt4/Td2hiuLySHI/AAAAAAAAA1w/hz9p_2CoICM/s72-c/P1090459.jpg'),('2011-05-25','',18341,'Tarangire NP, Tanzania',1000,'Helogale parvula','Common Dwarf Mongoose','http://inaturalist.org/observations/18341','http://lh3.ggpht.com/-qJYA7FKmhrg/Td2h1qebBEI/AAAAAAAAA2U/hnb_Nzyt7pQ/s72-c/P1090479.jpg'),('2011-03-22','Neat little social mongooses.',13171,'skukuza',477,'Helogale parvula','Common Dwarf Mongoose','http://inaturalist.org/observations/13171','http://farm6.static.flickr.com/5258/5549056044_f9d6e2bc83_s.jpg'),('2011-03-21','There was a whole family of these social mongooses running round Skukuza',13129,'skukuza',477,'Mungos mungo','Banded Mongoose','http://inaturalist.org/observations/13129','http://farm6.static.flickr.com/5057/5547395672_f70c487f67_s.jpg'),('2011-01-12','',9643,'skukuza',477,'Herpestes flavescens','Slender Mongoose','http://inaturalist.org/observations/9643','http://farm6.static.flickr.com/5207/5228654242_2e19b12613_s.jpg'),('2010-01-17','Actually this animal is common in Malvan area. Since I had seen lot of them in my earlier visits to the same place. I remember the event when I saw complete family of the Mongoose with three juveniles and two adults.\nEven I saw the same animal in the day time through the running train. ',4295,'Malvan, Maharashtra, India.',215,'Herpestes javanicus','Indian mongoose','http://inaturalist.org/observations/4295',''),('2009-04-05','Couldn\'t get close enough for a decent pic without one of them popping down a hole.',2222,'Chaco Canyon, NM',169,'Cynomys gunnisoni','Gunnison\'s prairie dog','http://inaturalist.org/observations/2222','http://farm4.static.flickr.com/3077/3417087688_4163b73472_s.jpg');
/*!40000 ALTER TABLE `mongooses` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2011-12-14 11:59:33
