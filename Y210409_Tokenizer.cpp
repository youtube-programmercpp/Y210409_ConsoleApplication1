// Y210409_Tokenizer.cpp Copyright(C) 2021 http://youtube.com/programmercpp
#include <iostream>
#include <string>
#include <stdexcept>

#include "Y210409_Token.h"
#include "Y210409_Tokenizer.h"

Tokenizer::Tokenizer(std::istream& istm)
	: ch(istm.get())
{
}
bool Tokenizer::IsDecimal() const
{
	switch (ch) {
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9': 
		return true;
	default:
		return false;
	}
}
bool Tokenizer::IsOctal() const
{
	switch (ch) {
	case '0': case '1': case '2': case '3':
	case '4': case '5': case '6': case '7':
		return true;
	default:
		return false;
	}
}
bool Tokenizer::IsHexadecimal() const
{
	switch (ch) {
	case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7':
	case '8': case '9': case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': 
	/*               */ case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
		return true;
	default:
		return false;
	}
}
std::string Tokenizer::ReadSequence(std::istream& istm, bool (Tokenizer::*p)() const, std::string&& s)
{
	while ((this->*p)()) {
		s.append(1, ch);
		ch = istm.get();
	}
	return std::move(s);
}
Token Tokenizer::Read(std::istream& istm)
{
	switch (ch) {
	case EOF:
		return Token(Token::Type::End, {});
	case '0':
		switch (ch = istm.get()) {
		case 'x':
		case 'X':
			//hexadecimal
			ch = istm.get();
			if (IsHexadecimal()) {
				std::string s = "0x";
				s.append(1, ch);
				ch = istm.get();
				return Token(Token::Type::IntegerConstant, ReadSequence(istm, &Tokenizer::IsHexadecimal, std::move(s)));
			}
			else
				throw std::runtime_error("error C2059: 構文エラー: 'サフィックスが無効です。'");
		default:
			//octal
			return Token(Token::Type::IntegerConstant, ReadSequence(istm, &Tokenizer::IsOctal, std::string(1, '0')));
		}
	case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
		//decimal
		{
			std::string s(1, ch);
			ch = istm.get();
			return Token(Token::Type::IntegerConstant, ReadSequence(istm, &Tokenizer::IsDecimal, std::move(s)));
		}
	case '+': ch = istm.get(); return Token(Token::Type::OperatorAdd, std::string(1, '+'));
	case '-': ch = istm.get(); return Token(Token::Type::OperatorSub, std::string(1, '-'));
	case '*': ch = istm.get(); return Token(Token::Type::OperatorMul, std::string(1, '*'));
	case '/': ch = istm.get(); return Token(Token::Type::OperatorDiv, std::string(1, '/'));
	case '(': ch = istm.get(); return Token(Token::Type::ParenLeft  , std::string(1, '('));
	case ')': ch = istm.get(); return Token(Token::Type::ParenRight , std::string(1, ')'));
	case ' ': case '\t': case '\n':
		ch = istm.get();
		return Read(istm);
	default:
		throw std::runtime_error("字句解析失敗");
	}
}

