#pragma once

//reads in a code file and seperates it into a vector of lines

#include <fstream>
#include <string>
#include <vector>
#include <map>

enum class Token
{
	END_OF_FILE = 0,
	ASSIGNMENT,
	INTEGER,
	REAL,
	AUTO,
	VAR,
	COMMENT,
	SEMICOLON,
	STRING,
	NO_TOKEN
};

const std::map<std::string, Token> String2Token
{
	{ "=", Token::ASSIGNMENT },
	{ "int", Token::INTEGER  },
	{ "real", Token::REAL },
	{ "var", Token::VAR },
	{ "auto", Token::AUTO },
	{ "//" , Token::COMMENT  },
	{ ";", Token::SEMICOLON  },
	{ "\"", Token::STRING}
};

const std::map<Token, std::string> TOken2String
{
	{ Token::ASSIGNMENT, "ASSIGNMENT" },
	{ Token::INTEGER, "INT" },
	{ Token::REAL, "REAL" },
	{ Token::AUTO, "AUTO" },
	{ Token::VAR, "VAR" },
	{ Token::SEMICOLON, "SEMICOLON" },
	{ Token::STRING, "STRING" }
};

class FileParser
{
public:
	FileParser(const std::string &fileName);

	//useful for comments
	void skipLine();

	//reads in after it hits a String-end Token
	//and sets the position to after that
	std::string getString();

	//if this returns Token::NO_TOKEN the word after that
	//might be either a name of a variable or a number
	//use getWord() to read it in and parse it later
	Token getNextToken();

	//reads in until it hits the next token or whitespace
	std::string getWord();
};

parse()
{
	Token tok = FileParser.getNextToken();

	//parses the file into a stream of commands
	//this stream has to be able to hold
	// a) the tokens
	// b) strings, marked as such
	// c) arbitrary strings, later parsed to variable names or numbers

	while (tok)
	{
		if (tok == COMMENT)
			skipLine();

		else if (tok == NO_TOKEN)
		{
			string = FileParser.getWord();
			addToStream(string);
		}

		else if (tok == STRING)
		{
			string = FileParser.getString();
			addToStream(string);
		}

		else
			addToStream(tok);

		tok = FileParser.getNextToken();
	}
}

class CodeReader
{
public:
	CodeReader(const std::string &fileName);

	friend std::ostream& operator<< (std::ostream &out, const CodeReader &reader);

private:

	std::vector<Token> mCode;
};

std::ostream& operator<< (std::ostream &out, const CodeReader &reader);