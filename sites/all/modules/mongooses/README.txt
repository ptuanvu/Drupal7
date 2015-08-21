This module exposes a fictional 'mongooses' table to views. A dump of the sample SQL table is in the included mongooses.sql file. Only useful for playing with.

To make this work, import the data from the included mongooses.sql file into your Drupal database.
The data in mongooses.sql comes from http://inaturalist.org.

mysql> source mongooses.sql

Then put the mongooses folder in sites/all/modules, and enable it. 
