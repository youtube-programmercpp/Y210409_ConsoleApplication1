// Y210409_Token.h Copyright(C) 2021 http://youtube.com/programmercpp
#pragma once
#include <string>
#include <istream>
#include <ostream>
class Token {
public:
	enum class Type
	{ IntegerConstant
	, OperatorAdd
	, OperatorSub
	, OperatorMul
	, OperatorDiv
	, ParenLeft
	, ParenRight
	, End
	};
public:
	Token(Type t, std::string&& s);
private:
	Type        t;
	std::string s;
public:
	std::string Extract();
	bool operator==(Type t) const;
	friend std::ostream& operator<<(std::ostream& ostm, const Token::Type t);
	friend std::ostream& operator<<(std::ostream& ostm, const Token& r);
};
