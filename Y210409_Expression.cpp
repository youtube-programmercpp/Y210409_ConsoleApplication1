// Y210409_Expression.h Copyright(C) 2021 http://youtube.com/programmercpp
#include "Y210409_Expression.h"

//
//	Expression
//
Expression::~Expression()
{
}

//
//	Expression_Constant
//
Expression_Constant::Expression_Constant(const std::string& s)
	: s(s)
{
}
int Expression_Constant::Evaluate() const
{
	return std::stoi(s);
}

//
//	Expression_Binary
//
Expression_Binary::Expression_Binary
(std::unique_ptr<Expression>&& left
	, int (Expression_Binary::*p_operator)() const
	, std::unique_ptr<Expression>&& right)
	: left      (std::move(left))
	, p_operator(p_operator)
	, right     (std::move(right))
{
}
int Expression_Binary::Evaluate_Add() const
{
	return left->Evaluate() + right->Evaluate();
}
int Expression_Binary::Evaluate_Sub() const
{
	return left->Evaluate() - right->Evaluate();
}
int Expression_Binary::Evaluate_Mul() const
{
	return left->Evaluate() * right->Evaluate();
}
int Expression_Binary::Evaluate_Div() const
{
	return left->Evaluate() / right->Evaluate();
}
int Expression_Binary::Evaluate() const
{
	return (this->*p_operator)();
}
