#ifndef READFROM_H
#define READFROM_H
/* stream classes */
#include <iostream>
#include <fstream>

/* utilities */
#include "utilities.h"
#include <string>
#include <vector>
using namespace std;
/* stream classes */
/*
	ofstream: stream class to write to files (OUTPUT)
	ifstream: stream class to read from files (INPUT)
	fstream: stream class to both read and write to files

cin is an object of class istream and cout is an object of class ostream, we can use file stream the same way
we are using them for cin and cout, only difference is to associate these streams with physical files
*/

/** TIPS **/
//use const char* if this function is called alot of times/multiple times
//C-Style string to match and print the line containing it, caller can use pointer/hardcode the text

//prints out content of text file
bool readFromFile(string& name);	

//prints out selected line in text file
const char* readFromFile(string& name, int line);	

//prints out matched text
bool readFromFile(string& name, string& text);	

#endif