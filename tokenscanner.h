#pragma once

/*
* File: tokenscanner.h
* --------------------
* This file exports a simple TokenScanner class that divides a string
* into individual logical units called tokens. In this version
* of the package, tokens come in two forms:
*
* 1. Strings of consecutive letters and digits representing words
* 2. One-character strings representing punctuation or separators
*
* The use of the TokenScanner class is illustrated by the following code
* pattern, which reads the tokens in the string variable input:
*
* TokenScanner scanner;
* scanner.setInput(input);
* while (scanner.hasMoreTokens()) {
* string token = scanner.nextToken();
* . . . process the token . . .
* }
*
* This version of the TokenScanner class includes the ignoreWhitespace
* method. The other options available in the library version of the
* class are included as exercises in the text.
*/
#ifndef _tokenscanner_h
#define _tokenscanner_h
#include <string>
#include <cstring>

/*
* Class: TokenScanner
* -------------------
* This class is used to represent a single instance of a scanner.
*/
class TokenScanner {
public:
	/*
	* Constructor: TokenScanner
	* Usage: TokenScanner scanner;
	* TokenScanner scanner(str);
	* ---------------------------------
	* Initializes a scanner object. The initial token stream comes from
	* the string str, if it is specified. The default constructor creates
	* a scanner with an empty token stream.
	*/
	TokenScanner();
	TokenScanner(std::string str);
	
		/*
		* Method: setInput
		* Usage: scanner.setInput(str);
		* -----------------------------
		* Sets the input for this scanner to the specified string. Any
		* previous input string is discarded.
		*/
		void setInput(std::string str);
	/*
	* Method: hasMoreTokens
	* Usage: if (scanner.hasMoreTokens()) . . .
	* -----------------------------------------
	* Returns true if there are additional tokens for this scanner to read.
	*/
	bool hasMoreTokens();
	/*
	* Method: nextToken
	* Usage: token = scanner.nextToken();
	* -----------------------------------
	* Returns the next token from this scanner. If called when no tokens
	* are available, nextToken returns the empty string.
	*/

	void setSeparator(std::string separe);

	// Methode qui identifie le separateur entre les token de texte.

	void setDifferentFirst(bool state)
	{

		m_differentFirstToken = state;
	};

	std::string firstToken();
	// pour le premier token, le début (start) est toujours à 0

	std::string nextToken();
	/*
	* Method: ignoreWhitespace()
	* Usage: scanner.ignoreWhitespace();
	* ----------------------------------
	* Tells the scanner to ignore whitespace characters. By default, the
	* nextToken method treats whitespace characters (typically spaces and
	* tabs) just like any other punctuation mark and returns them as
	* single-character tokens. Calling
	*
	* scanner.ignoreWhitespace();
	*
	* changes this behavior so that the scanner ignore whitespace characters.
	*/
	void ignoreWhitespace(bool flag);

	/*
	* File: tokenscannerpriv.h
	* ------------------------
	* This file contains the private section for the TokenScanner class.
	*/

	/* Instance variables */
	std::string buffer; /* The input string containing the tokens */
	
	std::size_t start; // premier " qui identifie le debut du token
	std::size_t end; // deuxieme " qui identifie la fin du token

	bool ignoreWhitespaceFlag; /* Flag set by a call to ignoreWhitespace */
	bool bufferEndReached; // indique que le dernier token a ete trouve.

	bool m_differentFirstToken;	// pour le cas où le premier token ne commence pas par un séparateur.  Ex: fichier quicken.txt.

	std::string separeToken;  // caractere qui separe les token.  Peut etre " ou \t ou autre si necessaire.
							   
					  /* Private methods */
	void skipWhitespace();

	int m_delta;

private:

};
#endif
