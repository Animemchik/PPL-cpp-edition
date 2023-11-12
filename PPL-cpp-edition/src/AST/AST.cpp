#include "AST.hpp"

AST::AST(string& code, string& filename, std::vector<Token> tokens) : code(code), filename(filename), tokens(tokens), pos(0), size(tokens.size()) {
	TEOF.type = tEOF;
}

Statement AST::parse() {
    BlockStatement result;
    while (!match(tEOF)) {
        result.statements.push_back(statement());
    }
    return result;
}

Statement AST::block() {
    BlockStatement block;
    consume(LBRACE);
    while (!match(RBRACE)) {
        block.statements.push_back(statement());
    }
    return block;
}

Statement AST::statementOrBlock() {
    if (lookMatch(0, LBRACE)) return block();
    return statement();
}

Statement AST::statement() {
    if (match(PRINT)) {
        consume(LPAREN);
        const Expression expr = expression();
        consume(RPAREN);
        return PrintStatement(expr);
    }
    if (match(PRINTLN)) {
        consume(LPAREN);
        const Expression expr = expression();
        consume(RPAREN);
        return PrintlnStatement(expr);
    }
    if (match(IF)) {
        return ifElse();
    }
    if (match(WHILE)) {
        return whileStatement();
    }
    if (match(DO_WHILE)) {
        return doWhileStatement();
    }
    if (match(FOR)) {
        return forStatement();
    }
    if (match(BREAK)) {
        return BreakStatement();
    }
    if (match(CONTINUE)) {
        return ContinueStatement();
    }
    if (match(FUNC)) {
        return functionDefine();
    }
    if (match(RETURN)) {
        return ReturnStatement(expression());
    }
    if (match(INCLUDE)) {
        return IncludeStatement(expression());
    }
    if (lookMatch(0, WORD) && lookMatch(1, LPAREN)) {
        return FunctionStatement(function());
    }
    return assignmentStatement();
}

FunctionalExpression AST::function() {
    const string name = consume(WORD).value;
    consume(LPAREN);
    FunctionalExpression function(name);
    while (!match(RPAREN)) {
        function.arguments.push_back(expression());
        match(COMMA);
    }
    return function;
}

Expression AST::logicalAnd() {
    return Expression();
}

Expression AST::equality() {
    Expression result = conditional();

    if (match(EQEQ)) {
        return ConditionalExpression(c_EQUALS, result, conditional());
    }
    if (match(EXCLEQ)) {
        return ConditionalExpression(c_NOT_EQUALS, result, conditional());
    }

    return result;
}

Expression AST::conditional() {
    Expression result = additive();

    while (true) {
        if (match(LT)) {
            result = ConditionalExpression(c_LT, result, additive());
            continue;
        }
        if (match(LTEQ)) {
            result = ConditionalExpression(c_LTEQ, result, additive());
            continue;
        }
        if (match(GT)) {
            result = ConditionalExpression(c_GT, result, additive());
            continue;
        }
        if (match(GTEQ)) {
            result = ConditionalExpression(c_GTEQ, result, additive());
            continue;
        }
        break;
    }

    return result;
}

Expression AST::additive() {
    Expression result = multiplicative();

    while (true) {
        if (match(PLUS)) {
            result = BinaryExpression('+', result, multiplicative());
            continue;
        }
        if (match(MINUS)) {
            result = BinaryExpression('-', result, multiplicative());
            continue;
        }
        break;
    }

    return result;
}

Expression AST::multiplicative() {
    Expression result = unary();

    while (true) {
        // 2 * 6 / 3
        if (match(MULTI)) {
            result = BinaryExpression('*', result, unary());
            continue;
        }
        if (match(DIVIDE)) {
            result = BinaryExpression('/', result, unary());
            continue;
        }
        if (match(PERCENT)) {
            result = BinaryExpression('%', result, unary());
            continue;
        }
        break;
    }

    return result;
}

Expression AST::unary() {
    if (match(MINUS)) {
        return UnaryExpression('-', primary());
    }
    return primary();
}

Expression AST::primary() {
    const Token current = get(0);
    if (match(NUMBER)) {
        return ValueExpression(current.value);
    }
    if (match(HEX)) {
        return ValueExpression(current.value);
    }
    if (lookMatch(0, WORD) && lookMatch(1, LPAREN)) {
        return function();
    }
    if (lookMatch(0, WORD) && lookMatch(1, LBRACKET)) {
        return element();
    }
    if (lookMatch(0, LBRACKET)) {
        return array();
    }
    if (match(WORD)) {
        return VariableExpression(current.value);
    }
    if (match(STRING)) {
        return ValueExpression(current.value);
    }
    if (match(LPAREN)) {
        Expression result = expression();
        match(RPAREN);
        return result;
    }
    errors.push_back(new Error());
}

Token AST::consume(TokenType type)
{
    const Token current = get(0);
    if (type != current.type) errors.push_back(new Error());
    pos++;
    return current;
}

bool AST::match(TokenType type) {
    const Token current = get(0);
    if (type != current.type) return false;
    pos++;
    return true;
}

bool AST::lookMatch(int8_t pos, TokenType type) {
    return get(pos).type == type;
}

Token AST::get(int8_t relativePosition) {
    const int position = pos + relativePosition;
    if (position >= size) return TEOF;
    return tokens[position];
}
