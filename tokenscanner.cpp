/*
* File: tokenscanner.cpp
* ----------------------
* This file implements the TokenScanner class. Most of the methods
* are straightforward enough to require no additional documentation.
*/
#include <cctype>
#include <string>
#include "tokenscanner.h"
//#include "stdafx.h"



using namespace std;
TokenScanner::TokenScanner() 
	{
	/* Empty */
	}
TokenScanner::TokenScanner(string str) 
	{
	setInput(str);
	}
void TokenScanner::setInput(string str) 
	{
	buffer = str;
	
	start = 0;
	end = 0;
	bufferEndReached = false;

	}
bool TokenScanner::hasMoreTokens() 
	{
	//if (ignoreWhitespaceFlag) skipWhitespace();
	return !bufferEndReached;
	}
/*
* Implementation notes: nextToken
* -------------------------------
* This method starts by looking at the character at the current character
* indicated by the index cp. If that index is past the end of the string,
* nextToken returns the empty string. If that character is alphanumeric,
* nextToken scans ahead until it finds the end of that word; if not,
* nextToken returns that character as a one-character string.
*/


void TokenScanner::setSeparator(string separe)
{

	separeToken = separe;
	if (separeToken == "\t")
	{
		m_delta = 0;		// pour le separateur TAB, un seul tab est présent entre chaque token
	}
	else 

	{
		m_delta = 0;		// pour le séparateur  ", il y a un séparateur au début et à la fin de chaque token.  On doit ajuster le calcul pour la recherche...
	};

};

string TokenScanner::nextToken() 
{


	
		
	if (!bufferEndReached)
	{
		
		start = end + 1; // buffer.find(separeToken, end);
			
			 
		if (start == std::string::npos) 	bufferEndReached = true;

		if (!bufferEndReached)
		{
			end = buffer.find(separeToken, start);
			if (end == std::string::npos)
				{
				bufferEndReached = true;
				};

			return buffer.substr(start, end - start);
		}
		else
		{
			return "0";
		}

				
	}
	else
	{
			return "0";
	}

			
	


	
}

string TokenScanner::firstToken()
{


	   start = 0;
		
	
		end = buffer.find(separeToken, start);
		if (end == std::string::npos)
		{
			bufferEndReached = true;
			return "0";
		};
		
		return buffer.substr(start, end - start );
	
}

void TokenScanner::ignoreWhitespace(bool flag) 
	{
	ignoreWhitespaceFlag = flag;
	}
/*
* Implementation notes: skipWhitespace
* ------------------------------------
* This method is a private method and is therefore not exported. It
* does, however, need to be declared in the private section of the
* class, which is contained in the tokenscannerpriv.h file. This
* method is called from both hasMoreTokens and nextToken.
*/
void TokenScanner::skipWhitespace() 
	{
	
	}