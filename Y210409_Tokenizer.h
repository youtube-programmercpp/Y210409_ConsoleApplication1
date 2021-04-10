#pragma once
#include <string>
#include <istream>
#include <ostream>

class Token;

class Tokenizer {
public:
	Tokenizer(std::istream& istm);
private:
	int ch;
public:
	bool IsDecimal() const;
	bool IsOctal() const;
	bool IsHexadecimal() const;
	std::string ReadSequence(std::istream& istm, bool (Tokenizer::*p)() const, std::string&& s);
	Token Read(std::istream& istm);
};
