#pragma once
#include <vector>
#include "..\lexer\Token.hpp"
#include "..\lexer\TokenType.hpp"
#include "../exceptions/Error.hpp"
#include "Expression.hpp"
#include "Statement.hpp"

using namespace std;

class AST {
private:
	string& code;
	string& filename;
	std::vector<Token> tokens;
	std::vector<Error*> errors;
	unsigned int pos;
	size_t size;
	Token TEOF;
public:
	AST(string& code, string& filename, std::vector<Token> tokens);
	Statement parse();
	Statement block();
	Statement statementOrBlock();
	Statement statement();
	FunctionalExpression function();
	FunctionDefineStatement functionDefine();
	Statement assignmentStatement();
	Statement ifElse();
	Statement whileStatement();
	Statement doWhileStatement();
	Statement forStatement();
	Expression array();
	ArrayAccessExpression element();
	Expression expression();
	Expression logicalOr();
	Expression logicalAnd();
	Expression equality();
	Expression conditional();
	Expression additive();
	Expression multiplicative();
	Expression unary();
	Expression primary();
	Token consume(TokenType type);
	bool match(TokenType type);
	bool lookMatch(int8_t pos, TokenType type);
	Token get(int8_t relativePosition);
};