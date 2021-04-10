// Y210409_Parser.h Copyright(C) 2021 http://youtube.com/programmercpp
#include "Y210409_Parser.h"
#include "Y210409_Expression.h"

Parser::Parser(std::istream& istm)
	: tokenizer(istm)
	, t(tokenizer.Read(istm))
{
}
std::unique_ptr<Expression> Parser::ParseExpressionPrimary(std::istream& istm)
{
	if (t == Token::Type::IntegerConstant) {
		auto s = t.Extract();
		t = tokenizer.Read(istm);
		return std::make_unique<Expression_Constant>(s);
	}
	else if (t == Token::Type::ParenLeft) {
		t = tokenizer.Read(istm);
		auto retval = ParseExpression(istm);
		if (t == Token::Type::ParenRight) {
			t = tokenizer.Read(istm);
			return retval;
		}
		else
			throw std::runtime_error("閉じ括弧がありません。");
	}
	else
		throw std::runtime_error("構文エラー");
}

std::unique_ptr<Expression> Parser::ParseExpressionMultiplicative(std::istream& istm)
{
	for (auto x = ParseExpressionPrimary(istm);;) {
		if (t == Token::Type::OperatorMul) {
			t = tokenizer.Read(istm);
			x = std::make_unique<Expression_Binary>
			( std::move(x)
			, &Expression_Binary::Evaluate_Mul
			, ParseExpressionMultiplicative(istm)
			);
		}
		else if (t == Token::Type::OperatorDiv) {
			t = tokenizer.Read(istm);
			x = std::make_unique<Expression_Binary>
			( std::move(x)
			, &Expression_Binary::Evaluate_Div
			, ParseExpressionMultiplicative(istm)
			);
		}
		else
			return x;
	}
}
std::unique_ptr<Expression> Parser::ParseExpressionAdditive(std::istream& istm)
{
	for (auto x = ParseExpressionMultiplicative(istm);;) {
		if (t == Token::Type::OperatorAdd) {
			t = tokenizer.Read(istm);
			x = std::make_unique<Expression_Binary>
			( std::move(x)
			, &Expression_Binary::Evaluate_Add
			, ParseExpressionMultiplicative(istm)
			);
		}
		else if (t == Token::Type::OperatorSub) {
			t = tokenizer.Read(istm);
			x = std::make_unique<Expression_Binary>
			( std::move(x)
			, &Expression_Binary::Evaluate_Sub
			, ParseExpressionMultiplicative(istm)
			);
		}
		else
			return x;
	}
}
std::unique_ptr<Expression> Parser::ParseExpression(std::istream& istm)
{
	return ParseExpressionAdditive(istm);
}
