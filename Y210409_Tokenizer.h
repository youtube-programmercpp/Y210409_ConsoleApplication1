// Y210409_Tokenizer.h Copyright(C) 2021 http://youtube.com/programmercpp
#pragma once
#include <string>
#include <istream>

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
