#ifndef UTILITIES_H
#define UTILITIES_H
#include <iostream>
#include <string>
using namespace std;

/* treating this as a library: utilities
for string functions like search term etc..
*/

bool searchTerm(string client, string matchee);
void deleteChar(string& word, char del);
int stringToInt(string& num);

//get the first encounter integer from this string
int getNumberFromRange(string& original);
int getNumberFromRange(string& original, int skip);	//can skip over encouter how many

#endif