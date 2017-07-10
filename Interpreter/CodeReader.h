#pragma once

//reads in a code file and seperates it into a vector of lines

#include <fstream>
#include <string>
#include <vector>
#include <map>

enum class TokType
{
	ASSIGNMENT,
	INTEGER,
	REAL,
	AUTO,
	VAR,
	COMMENT,
	SEMICOLON,
	NUMBER,
	NAME,
	UNEXPECTED
};

struct Token
{
	std::string str;
	TokType type;
};

const std::map<std::string, TokType> TokenTypeNames
{
	{ "=", TokType::ASSIGNMENT },
	{ "int", TokType::INTEGER  },
	{ "real", TokType::REAL },
	{ "var", TokType::VAR },
	{ "auto", TokType::AUTO },
	{ "//" , TokType::COMMENT  },
	{ ";", TokType::SEMICOLON  }
};

const std::map<TokType, std::string> DEBUG
{
	{ TokType::ASSIGNMENT, "ASSIGNMENT" },
	{ TokType::INTEGER, "INT" },
	{ TokType::REAL, "REAL" },
	{ TokType::AUTO, "AUTO" },
	{ TokType::VAR, "VAR" },
	{ TokType::COMMENT, "COMMENT" },
	{ TokType::SEMICOLON, "SEMICOLON" },
	{ TokType::NAME, "NAME" },
	{ TokType::NUMBER, "NUMBER" },
	{ TokType::UNEXPECTED, "ERROR: UNEXPECTED" }
};

class CodeReader
{
public:
	CodeReader(const std::string &fileName);

	friend std::ostream& operator<< (std::ostream &out, const CodeReader &reader);

private:

	std::vector<Token> mCode;
};

std::ostream& operator<< (std::ostream &out, const CodeReader &reader);