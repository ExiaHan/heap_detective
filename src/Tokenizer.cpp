#include "Tokenizer.h"

Tokenizer::Tokenizer() : buffer(""), token(""), delimiter(DEFAULT_DELIMITER)
{
	currPos = buffer.begin();
}

Tokenizer::Tokenizer(const std::string& str, const std::string& delimiter) : buffer(str), token(""), delimiter(delimiter)
{
	currPos = buffer.begin();
}

Tokenizer::~Tokenizer()
{
}

void Tokenizer::set(const std::string& str, const std::string& delimiter)
{
	this->buffer = str;
	this->delimiter = delimiter;
	this->currPos = buffer.begin();
}

void Tokenizer::setString(const std::string& str)
{
	this->buffer = str;
	this->currPos = buffer.begin();
}

void Tokenizer::setDelimiter(const std::string& delimiter)
{
	this->delimiter = delimiter;
	this->currPos = buffer.begin();
}

std::string Tokenizer::next()
{
	if(buffer.size() <= 0) 
		return "";           

    	token.clear();                              

    	this->skipDelimiter();                     

    	while(currPos != buffer.end() && !isDelimiter(*currPos))
    	{
        	token += *currPos;
        	++currPos;
    	}

    	return token;
}

void Tokenizer::skipDelimiter()
{
	while(currPos != buffer.end() && isDelimiter(*currPos))
		++currPos;
}

bool Tokenizer::isDelimiter(char c)
{
	return (delimiter.find(c) != std::string::npos);
}


