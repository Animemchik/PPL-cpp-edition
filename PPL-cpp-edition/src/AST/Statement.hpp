#pragma once
#include "Node.hpp"

class Statement : public Node {};

class BlockStatement : public Statement {
public:
	vector<Statement> statements;

	BlockStatement() {};
};

class PrintStatement : public Statement {
public:
	Expression expression;

	PrintStatement(Expression expression) : expression(expression) {};
};

class PrintlnStatement : public Statement {
public:
	Expression expression;

	PrintlnStatement(Expression expression) : expression(expression) {};
};

class BreakStatement : public Statement {
public:
	BreakStatement() {};
};

class ContinueStatement : public Statement {
public:
	ContinueStatement() {};
};

class ReturnStatement : public Statement {
public:
	Expression expression;
	ReturnStatement(Expression expression) : expression(expression) {};
};

class IncludeStatement : public Statement {
public:
	Expression expression;

	IncludeStatement(Expression expression) : expression(expression) {};
};

class FunctionStatement : public Statement {
public:
	FunctionalExpression function;
	FunctionStatement(FunctionalExpression function) : function(function) {};
};

