// Y210409_Parser.h Copyright(C) 2021 http://youtube.com/programmercpp
#pragma once
#include "Y210409_Token.h"
#include "Y210409_Tokenizer.h"
#include "Y210409_Expression.h"
class Parser
{
public:
	Parser(std::istream& istm);
private:
	Tokenizer tokenizer;
	Token     t        ;
public:
	std::unique_ptr<Expression> ParseExpressionPrimary(std::istream& istm);
	std::unique_ptr<Expression> ParseExpressionMultiplicative(std::istream& istm);
	std::unique_ptr<Expression> ParseExpressionAdditive(std::istream& istm);
	std::unique_ptr<Expression> ParseExpression(std::istream& istm);
};