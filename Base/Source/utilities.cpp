#include "utilities.h"

//client: string to be compared, matchee: string used to match
bool c, m;
bool searchTerm(string client, string matchee)
{
	c = client.length();
	m = matchee.length();

	if( !c && !m )	return true;
	if( !c || !m ) return false;

	for(int j = 0; j < client.length(); ++j)
	{
		bool c= true;
		if(matchee[0] == client[j])
		{
			if(matchee.length() < 2 || (matchee.length() == 1 && j == client.length() - 1))
			return true;

			if(client.length() - (j + 1) >= matchee.length() - 1)
			{
				int index = 1;
				for(int i = j + 1; i < client.length(); ++i, ++index)
				{
					if(client[i] != matchee[index])
					{
						c = false;
						break;	//continue search
					}
					if(index == matchee.length() - 1)
						return true;
				}
				if(c == true)
					return true;
			}
			else
				return false;
		}
		else if(j == client.length() - 1)
			return false;
	}
	return false;
}

void deleteChar(string& word, char del)
{
	int lastChar = 0;
	bool c = false;
	for(int i = 0; i < word.length(); ++i)
	{
		if(word[i]  == del)
		{
			if(c == false)
			{
				c = true;
				lastChar = i;
			}
		}
		else
			c = false;
	}

	if(c == true)
		word.resize(lastChar);
}

int stringToInt(string& num)
{
	int numm = 0;

	int j = 1;
	for(int i = num.length() - 1; i >= 0; --i, j *= 10)
	{
		numm += (num[i] - 48) * j;
	}

	return numm;
}

int getNumberFromRange(string& original)
{
	bool start = false;

	string returnVal = "";

	for(int i = 0; i < original.length(); ++i)
	{
		if( original[i] >= '0' && original[i] <= '9' )
		{
			start = true;
			returnVal += original[i];
		}
		else
		{
			if( start )
				break;	//reach end of number
		}
	}

	return stringToInt(returnVal);
}

int getNumberFromRange(string& original, int skip)
{
	bool start = false;

	string returnVal = "";

	for(int i = 0; i < original.length(); ++i)
	{
		if( original[i] >= '0' && original[i] <= '9' )
		{
			start = true;
			returnVal += original[i];
		}
		else
		{
			if( start )
			{
				if( skip == 0 )
					break;
				else
				{
					returnVal = "";
					--skip;
				}
			}
		}
	}

	return stringToInt(returnVal);
}