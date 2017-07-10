#include "CodeReader.h"
#include <sstream>
#include <cctype>
#include <Windows.h>

struct FileStream
{
	FileStream(const std::string &fileName) : mPos(0), sane(true)
	{
		std::ifstream file(fileName, std::ios::binary);

		std::stringstream stream;
		stream << file.rdbuf();
		mContent = stream.str();

		file.close();
	}

	//reads in until newline was found
	std::string getLine(char delim)
	{
		size_t line_end = mContent.find(delim, mPos);
		std::string line = mContent.substr(mPos, line_end - mPos);

		if (line_end == std::string::npos)
			mPos = mContent.size();
		else
			mPos = line_end;

		return line;
	}

	//reads in all alphanumericals
	std::string getName()
	{
		std::string name;

		while (std::isalnum(mContent[mPos]))
		{
			name += mContent[mPos];
			mPos++;
		}

		return name;
	}

	//valid number characters
	bool isNumComponent(char c)
	{
		const char* valid = "0123456789+-.";
		return strchr(valid, c) != nullptr;
	}

	//reads in all valid number characters
	std::string getNum()
	{
		std::string num;

		while (isNumComponent(mContent[mPos]))
		{
			num += mContent[mPos];
			mPos++;
		}

		return num;
	}

	//reads in anything until the next whitespace
	std::string getWord()
	{
		std::string word;

		while (!std::isspace(mContent[mPos]))
		{
			word += mContent[mPos];
			mPos++;
		}

		return word;
	}

	//advances mPos
	void skipWS()
	{
		for (
			size_t size = mContent.size();
			(mPos < size) && std::isspace(mContent[mPos]);
			mPos++
			);
	}

	bool operator>>(Token &tok)
	{
		if (mPos == mContent.size() || !sane)
			return false;

		bool found = false;

		for (auto it = TokenTypeNames.begin(); it != TokenTypeNames.end() && !found; ++it)
		{
			size_t token_length = it->first.size();

			if (strncmp(mContent.c_str() + mPos, it->first.c_str(), token_length) == 0)
			{
				//next token was found
				mPos += token_length;
				tok.type = it->second;

				if (tok.type == TokType::COMMENT)
					tok.str = getLine('\n');

				found = true;
			}
		}

		//no matching token found
		if (!found)
		{
			if (std::isalpha(mContent[mPos]))
			{
				tok.type = TokType::NAME;
				tok.str = getName();
			}
			else if (isNumComponent(mContent[mPos]))
			{
				tok.type = TokType::NUMBER;
				tok.str = getNum();
			}
			else
			{
				tok.type = TokType::UNEXPECTED;
				tok.str = mContent[mPos];
				sane = false;
			}
		}

		skipWS();
		return true;
	}

	size_t mPos;
	std::string mContent;
	bool sane;
};

CodeReader::CodeReader(const std::string & fileName)
{
	FileStream stream(fileName);

	Token tok;

	while (stream >> tok)
	{
		mCode.push_back(tok);
		//clear string
		tok.str = "";
	}
}


std::ostream& operator<< (std::ostream &out, const CodeReader &reader)
{
	for (auto it = reader.mCode.begin(); it != reader.mCode.end(); ++it)
	{
		if (it->type == TokType::UNEXPECTED)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		else if (it->str.empty())
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		else
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);

		out << DEBUG.find(it->type)->second << " ";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

		out << it->str << std::endl;
	}

	return out;
}