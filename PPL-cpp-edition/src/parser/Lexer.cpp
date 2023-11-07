#include <sstream>
#include <iostream>
#include "Lexer.hpp"
#include "exceptions/LexerExceptions.hpp"

string Lexer::OPERATOR_CHARS = "+-*/%()=<>[]{},!&|^~?:;";

map<string, TokenType> Lexer::OPERATORS = {
	{"+",			PLUS},
	{"-",			MINUS},
	{"*",			MULTI},
	{"/",			DIVIDE},
	{"=",			EQ},
	{"%",			PERCENT},

	{"++",			PLUSPLUS},
	{"--",			MINUSMINUS},

	{"+=",			PLUSEQ},
	{"-=",			MINUSEQ},
	{"*=",			MULTIEQ},
	{"/=",			DIVIDEEQ},
	{"%=",			PERCENTEQ},

	{"&=",			AMPEQ},
	{"^=",			CARETEQ},
	{"|=",			BAREQ},
	{"::=",			COLONCOLONEQ},

	{"<<",			LTLT},
	{">>",			GTGT},
	{">>>",			GTGTGT},

	{"<<=",			LTLTEQ},
	{">>=",			GTGTEQ},
	{">>>=",		GTGTGTEQ},

	{"==",			EQEQ},
	{"!=",			EXCLEQ},
	{"<",			LT},
	{"<=",			LTEQ},
	{">",			GT},
	{">=",			GTEQ},

	{"&&",			AND},
	{"||",			OR},
	{"!",			NOT},
	
	{"@",			AT},
	
	{"->",			MINUSGT},
	{"&",			AMP},
	{"|",			BAR},
	
	{"?",			QUESTION},
	{":",			COLON},
	
	{"^",			CARET},
	
	{"~",			TILDE},
	
	{"(",			LPAREN},
	{")",			RPAREN},
	{"[",			LBRACKET},
	{"]",			RBRACKET},
	{"{",			LBRACE},
	{"}",			RBRACE},
	
	{",",			COMMA},
	{".",			DOT},
	{";",			SEMICOLON}
};

map<string, TokenType> Lexer::KEYWORDS = {
	{"public",		PUBLIC},
	{"private",		PRIVATE},
	{"protect",		PROTECTED},
	{"final",		FINAL},
	{"static",		STATIC},
	{"func",		FUNC},
	{"class",		CLASS},
	{"new",			NEW},
	{"interface",	INTERFACE},
	{"enum",		ENUM},
	{"if",			IF},
	{"else",		ELSE},
	{"for",			FOR},
	{"while",		WHILE},
	{"do",			DO_WHILE},
	{"break",		BREAK},
	{"continue",	CONTINUE},
	{"return",		RETURN},
	{"include",		INCLUDE},
	{"using",		USING},
	{"foreach",		FOREACH},
	{"switch",		SWITCH},
	{"case",		CASE},
	{"throw",		THROW},
	{"try",			TRY},
	{"catch",		CATCH},
	{"namespace",	NAMESPACE},
	{"and",			AND},
	{"or",			OR},
	{"not",			NOT}
};

Lexer::Lexer(string& code, string& filename) : code(code), filename(filename), size(code.length()), pos(0), col(1), row(1) {}

LexerOutput Lexer::tokenize() {
	while (pos < size) {
		const char current = peek(0);
		if (std::isalpha(current)) {
			tokenizeWord();
		} else if (std::isalnum(current)) {
			tokenizeNumber();
		} else if (current == '\'') {
			tokenizeChar();
		} else if (current == '"') {
			tokenizeString();
		} else if (OPERATOR_CHARS.find(current) != std::string::npos) {
			tokenizeOperator();
		} else {
			next();
		}
	}
	addToken(tEOF, col);
	LexerOutput output;
	output.tokens = tokens;
	output.errors = errors;
	return output;
}

void Lexer::tokenizeOperator() {
	char current = peek(0);
	if (current == '/') {
		if (peek(1) == '/') {
			next(); // skip /
			next(); // skip /
			tokenizeComment();
			return;
		}
		else if (peek(1) == '*') {
			next(); // skip /
			next(); // skip *
			tokenizeMultilineComment();
			return;
		}
	}
	std::stringstream builder;
	unsigned int col1 = col;
	std::string text;
	while (true) {
		text = builder.str();
		if (OPERATORS.find(text + current) == OPERATORS.end() && !builder.str().empty()) {
			addToken(OPERATORS[text], col1);
			return;
		}
		builder << current;
		current = next();
	}
}

void Lexer::tokenizeWord() {
	char current = peek(0);
	unsigned int col1 = col;
	std::stringstream result;
	while (std::isalpha(current) || std::isalnum(current) || current == '_') {
		result << current;
		current = next();
	}

	const std::string word = result.str();
	if (KEYWORDS.find(word) != KEYWORDS.end()) {
		addToken(KEYWORDS[word], col1);
		return;
	}

	addToken(WORD, word, col1);
}

void Lexer::tokenizeString() {
	char current = next();

	std::stringstream builder;
	unsigned int col1 = col;
	while (true) {
		if (current == '\0') {
			errors.push_back(new StringNotCompleteE(code, filename, row, col1, col));
			return;
		}
		if (current == '\n') {
			errors.push_back(new StringNotCompleteE(code, filename, row, col, col));
			return;
		}

		if (current == '\\') {
			current = next();
			switch (current) {
				case '0': {
					current = next();
					builder << '\0';
					continue;
				}
				case 't': {
					current = next();
					builder << '\t';
					continue;
				}
				case '"': {
					current = next();
					builder << '"';
						continue;
				}
				case 'n': {
					current = next();
					builder << '\n';
						continue;
				}
				case 'b': {
					current = next();
					builder << '\b';
						continue;
				}
				case 'f': {
					current = next();
					builder << '\f';
						continue;
				}
				case 'r': {
					current = next();
					builder << '\r';
						continue;
				}
				case 'u': {
					int rollbackPosition = pos;
					while (current == 'u') current = next();
					int escapedValue = 0;
					for (int i = 12; i >= 0 && escapedValue != -1; i -= 4) {
						if (std::isxdigit(current)) {
							escapedValue |= (std::isdigit(current) ? current - '0' : std::tolower(current) - 'a' + 10) << i;
						}
						else {
							escapedValue = -1;
						}
						current = next();
					}

					if (escapedValue >= 0) {
						builder << static_cast<char>(escapedValue);
					}
					else {
						// Rollback
						builder << "\\u";
						pos = rollbackPosition;
					}
					continue;
				}
			}
			builder << '\\';
			continue;
		}
		builder << current;
		current = next();
		if (current == '"') {
			next(); // skip "
			break;
		}
	}
	addToken(STRING, builder.str(), col1);
}

void Lexer::tokenizeChar() {}

void Lexer::tokenizeNumber() {
	char current = peek(0);
	if (current == '0' && (peek(1) == 'x' || peek(1) == 'X')) {
		tokenizeHexNumber();
	}
	unsigned int col1 = col;
	bool dot = false;
	std::stringstream result;
	while (std::isalnum(current) || current == '.' || current == '_') {
		if (current == '.') {
			if (dot) {
				errors.push_back(new NumberTokenizeE(code, filename, row, col1, col));
				break;
			}
			dot = true;
		}
		if (current == '_') {
			current = next(); // skip _
			continue;
		}
		result << current;
		current = next();
	}
	addToken(NUMBER, result.str(), col1);
}

void Lexer::tokenizeHexNumber() {
	next(); // skip 0
	next(); // skip x
	unsigned int col1 = col;
	char current = peek(0);
	std::stringstream result;
	while (std::isxdigit(current)) {
		result << current;
		current = next();
	}
	addToken(HEX, result.str(), col1);
}

void Lexer::tokenizeComment() {
	char current = peek(0);
	if (current == '/' && peek(1) == '/') {
		tokenizeMultilineComment();
	}
	unsigned int col1 = col;
	std::stringstream result;
	while (current != '\n' && current != '\0') {
		result << current;
		current = next();
	}
	addToken(COMMENT, result.str(), col1);
}

void Lexer::tokenizeMultilineComment() {
	char current = peek(0);
	unsigned int col1 = col;
	std::stringstream result;
	while (current != '*' && peek(1) != '/') {
		if (current == '\0') {
			errors.push_back(new MultiCommentTokenizeE(code, filename, row, col));
			break;
		}
		result << current;
		current = next();
	}
	addToken(MULTICOMMENT, result.str(), col1);
	next();	// skip *
	next();	// skip /
}

char Lexer::next() {
	pos++;
	const char current = peek(0);
	if (current == '\n') {
		row++;
		col = 1;
	} else col++;
	return current;
}

char Lexer::peek(int8_t relativePos)
{
	return code[pos+relativePos];
}

void Lexer::addToken(TokenType type, unsigned int col1) {
	addToken(type, "", col1);
}

void Lexer::addToken(TokenType type, string value, unsigned int col1) {
	Token t;
	t.type = type;
	t.value = value;
	t.row = row;
	t.col1 = col1;
	t.col2 = col;
	tokens.push_back(t);
}
