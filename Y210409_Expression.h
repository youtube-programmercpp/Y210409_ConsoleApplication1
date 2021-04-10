// Y210409_Expression.h Copyright(C) 2021 http://youtube.com/programmercpp
#pragma once
#include <memory>
#include <string>
class Expression
{
public:
	virtual ~Expression();
	virtual int Evaluate() const = 0;
};
class Expression_Constant : public Expression {
public:
	Expression_Constant(const std::string& s);
private:
	std::string s;
private:
	virtual int Evaluate() const override;
};
class Expression_Binary : public Expression {
public:
	Expression_Binary
	( std::unique_ptr<Expression>&& left
	, int (Expression_Binary::*p_operator)() const
	, std::unique_ptr<Expression>&& right
	);
private:
	std::unique_ptr<Expression> left, right;
	int (Expression_Binary::*p_operator)() const;
public:
	int Evaluate_Add() const;
	int Evaluate_Sub() const;
	int Evaluate_Mul() const;
	int Evaluate_Div() const;
private:
	virtual int Evaluate() const override;
};
