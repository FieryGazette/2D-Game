#include "readFrom.h"
/**/
/*
	Heads up: to change <bool readFromFile(string& name, string& text)> from
				match whole string to match semi to whole part of string, instruction inside function
*/
/**/

bool readFromFile(char* name)
{
	/**
		to open file:
		use open function; open(filename, mode);
		eg. myfile.open("dfsdf.txt", ios::in | ios::trunc)

		modes:
		second parameter of open function/overloaded constructor

		ios::in - open for input operations	(READ from file)
		ios::out - open for output operations (WRITE to file)
		ios::binary - open in binary mode
		ios::ate - set initial position at end of file
		ios::app - All output operations are performed at the end of the file, appending the content to the current content of the file.
		ios::trunc - if file opened for output and already exists, previous content deleted and replaced by new one

		combine modes:
		use bitwise OR (|); ios::in | ios::out | ios::trunc
	**/

	ifstream myfile(name);	//overloaded constructor to open a text file imm. after declaration
	string sentence = "";

	if( myfile.is_open())
	{
		int counter = 1;
		//no need to convert C-Style string to string if input uses C string
		//string can be assigned C-Style string, in this case, its just characters
		//on the text file, so C-Style string or string can take in stuff from it
		while(getline(myfile, sentence, '\n'))	//can also use !myfile.eof()
		{
			cout << counter << ":  " << sentence << endl;
			++counter;
		}
		myfile.close();
	}
	else
	{
		cout << "wtf whr the file" << endl;
		return false;
	}

	return true;
}

const char* readFromFile(char* name, int line)
{
	ifstream myfile(name);	//overloaded constructor to open a text file imm. after declaration
	/** static so that sentence will always be in mem. and char pointer
	to it will not be invalid **/
	static string sentence = "";	
	const char* ptr = NULL;

	if( myfile.is_open())
	{
		for(int i = 0; !myfile.eof() && i < line; ++i, getline(myfile, sentence)){}
		
		ptr = sentence.c_str();

		myfile.close();
		if(ptr == NULL)
			sentence = "Error 999: line not found u blind";
		return sentence.c_str();
	}
	else
	{
		sentence = "wtf whr the file";
		return sentence.c_str();
	}

	myfile.close();
	sentence = "";	//safeguard in case all tests fails...
	return sentence.c_str();
}

bool readFromFile(string& name, string& text)
{
	int line = 0;
	ifstream myfile(name);
	string sentence = "";

	if(myfile.is_open())
	{
		bool c = false;
		while(getline(myfile, sentence))
		{
			++line;

			//change to searchTerm(sentence, text) for matching both semi/whole of string
			if(sentence == text)
			{
				//cout << "Matched sentence: " << sentence << " --- Line: " << line << endl;
				c = true;
			}
		}

		myfile.close();

		if(c == false)
		{
			//cout << "error 998: cannot match word/no words to be searched" << endl;
			return false;
		}
		else
			return true;
	}
	else
	{
		//cout << "wtf whr the file" << endl;
		return false;
	}
}