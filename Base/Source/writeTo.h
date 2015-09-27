#ifndef WRITETO_H
#define WRITETO_H
/* stream classes */
/*
	ofstream: stream class to write to files (OUTPUT)
	ifstream: stream class to read from files (INPUT)
	fstream: stream class to both read and write to files

cin is an object of class istream and cout is an object of class ostream, we can use file stream the same way
we are using them for cin and cout, only difference is to associate these streams with physical files
*/
#include <iostream>
#include <fstream>	

/* utilities */
#include <string>
#include <vector>
#include "utilities.h"
#include <ctime>
using namespace std;

bool writeToFile(string& name);
bool writeToFile(string& name, string word);
bool deleteFromFile(string& name, int line);
bool emptyFile(string& name);

#endif