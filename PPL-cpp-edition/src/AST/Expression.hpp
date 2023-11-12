#pragma once
#include "Node.hpp"

enum ConditionalOperator {
	c_EQUALS,			// ==
	c_NOT_EQUALS,		// !=
	c_LT,				// <
	c_LTEQ,			// <=
	c_GT,				// >
	c_GTEQ,			// >=
	c_AND,			// &&
	c_OR				// ||
};

class Expression : public Node {};

class FunctionalExpression : public Expression {
public:
	string name;
	vector<Expression> arguments;
	FunctionalExpression(string name) : name(name) {}
	FunctionalExpression(string name, vector<Expression> arguments) : name(name), arguments(arguments) {}
};

class ValueExpression : public Expression {
public:
	string value;
	ValueExpression(string value) : value(value) {}
};

class VariableExpression : public Expression {
public:
	string name;
	VariableExpression(string name) : name(name) {}
};

class UnaryExpression : public Expression {
public:
	Expression expr;
	char op;
	UnaryExpression(char op, Expression expr) : expr(expr), op(op) {}
};

class BinaryExpression : public Expression {
public:
	Expression expr1, expr2;
	char op;
	BinaryExpression(char op, Expression expr1, Expression expr2) : expr1(expr1), expr2(expr2), op(op) {}
};

class ConditionalExpression : public Expression {
public:
	const Expression expr1;
	const Expression expr2;
	const ConditionalOperator op;
	ConditionalExpression(ConditionalOperator op, Expression expr1, Expression expr2) : op(op), expr1(expr1), expr2(expr2) {}

};