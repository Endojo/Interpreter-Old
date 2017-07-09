#include "CodeReader.h"
#include <sstream>
#include <cctype>
#include <Windows.h>

struct FileStream
{
	FileStream(const std::string &fileName) : mPos(0)
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
		if (mPos == mContent.size())
			return false;

		for (auto it = TokenTypeNames.begin(); it != TokenTypeNames.end(); ++it)
		{
			size_t token_length = it->first.size();

			if (strncmp(mContent.c_str() + mPos, it->first.c_str(), token_length) == 0)
			{
				//next token was found
				mPos += token_length;
				tok.type = it->second;

				if (tok.type == TokType::COMMENT)
					tok.str = getLine('\n');

				break;
			}
		}

		skipWS();
		return true;
	}

	size_t mPos;
	std::string mContent;
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
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		out << DEBUG.find(it->type)->second << " ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		out << it->str << std::endl;
	}

	return out;
}