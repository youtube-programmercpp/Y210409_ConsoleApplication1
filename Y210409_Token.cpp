// Y210409_Token.cpp Copyright(C) 2021 http://youtube.com/programmercpp
#include <iostream>
#include <string>
#include <stdexcept>
#include "Y210409_Token.h"

Token::Token(Type t, std::string&& s)
	: t(t)
	, s(std::move(s))
{
}
std::string Token::Extract()
{
	return std::move(s);
}
bool Token::operator==(Type t) const
{
	return this->t == t;
}
std::ostream& operator<<(std::ostream& ostm, const Token::Type t)
{
	switch (t) {
#define	TokenType(name)	case Token::Type::name: ostm << #name; break;
	TokenType(IntegerConstant)
	TokenType(OperatorAdd    )
	TokenType(OperatorSub    )
	TokenType(OperatorMul    )
	TokenType(OperatorDiv    )
	TokenType(ParenLeft      )
	TokenType(ParenRight     )
	TokenType(End            )
#undef	TokenType
	default:
		ostm << "?";
		break;
	}
	return ostm;
}
std::ostream& operator<<(std::ostream& ostm, const Token& r)
{
	return ostm << "{ " << r.t << ", " << r.s << " }";
}
