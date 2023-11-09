#pragma once
#include <vector>
#include "..\lexer\Token.hpp"
#include "..\lexer\TokenType.hpp"
#include "Statement.hpp"

class AST {
private:
	std::vector<Token> tokens;
	std::vector<Statement> statements;
};