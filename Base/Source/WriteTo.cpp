#include "writeTo.h"

bool writeToFile(string& name)
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

	//use C-String for address for speed: optional - convert to string
	//string n(name);

	ofstream myfile(name, ios::out | ios::app);	//overloaded constructor to open a text file imm. after declaration
	char randWords[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '10'};

	/**
		everytime write to file, the original will be replaced
		SO, use ios::app to set input position at endline of file, and stream adds string from there
	**/
	if(myfile.is_open())
	{
		myfile << randWords[rand() % 10] << ' ';
		myfile << randWords[rand() % 10] << ' ';
		myfile << randWords[rand() % 10] << "\n";
		myfile.close();	//rmb to close !!
		/**
			close(); close file and inform OS so resources become available again.
			flushes the associated buffers and close the file. Stream object (myfile) can
			be reused to open another file, and the file is availble for opening by other processes
		**/
	}
	else
		return false;
	
	return true;
}

bool writeToFile(string& name, string word)
{
	ofstream myfile(name, ios::out | ios::app);	//overloaded constructor to open a text file imm. after declaration
	
	deleteChar(word, ' ');
	if(myfile.is_open())
	{
		myfile << word + "\n";
		myfile.close();
	}
	else
		return false;

	return true;
}

bool emptyFile(string& name)
{
	ofstream myfile(name);
	if(myfile.is_open())
	{
		myfile << "";
		myfile.close();
	}
	else
		return false;

	return true;
}

bool deleteFromFile(string& name, int line)
{
	ifstream myfile(name);	//to read from txt file aka input
	/** static so that sentence will always be in mem. and char pointer
	to it will not be invalid **/
	static string sentence = "";	
	const char* ptr = NULL;

	if( myfile.is_open())
	{
		vector<string> tmp_storage;	//temp. store all strings of the vector except line to be deleted
		for(int i = 0; getline(myfile, sentence); ++i)
		{
			if(i != line - 1)
				tmp_storage.push_back(sentence);
		}
		
		myfile.close();

		emptyFile(name);//if line exceeds/deceeds eof, nothing is deleted
		ofstream writeBack(name, ios::out | ios::app);	//writeback to file aka output set cursor to end
		//write back to file
		if(writeBack.is_open())
		{
			for(int i = 0; i < tmp_storage.size(); ++i)
				writeBack << tmp_storage[i] + '\n';
			
			writeBack.close();
		}
		else
			return false;

		return true;
	}
	else
		cout << "Error: File not found" << endl;

	return false;	//return true is in if(myfile.is_open()){}
}