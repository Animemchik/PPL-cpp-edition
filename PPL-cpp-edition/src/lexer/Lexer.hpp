#pragma once
#include <stdint.h>
#include "TokenType.hpp"
#include "Token.hpp"
#include "exceptions/Error.hpp"
#include <string>
#include <map>
#include <vector>

using namespace std;

struct LexerOutput {
	std::vector<Token> tokens;
	std::vector<Error*> errors;
};

class Lexer {
	private:
		static string OPERATOR_CHARS;
		static map<string, TokenType> OPERATORS;
		static map<string, TokenType> KEYWORDS;
		string& code;
		string& filename;
		size_t size;
		unsigned long pos;
		unsigned int col, row;
		std::vector<Token> tokens;
		std::vector<Error*> errors;
	public:
		Lexer(string& code, string& filename);
		LexerOutput tokenize();
		void tokenizeOperator();
		void tokenizeWord();
		void tokenizeString();
		void tokenizeChar();
		void tokenizeNumber();
		void tokenizeHexNumber();
		void tokenizeComment();
		void tokenizeMultilineComment();
		void tokenizePass();
		char next();
		char peek(int8_t relativePos);
		void addToken(TokenType type, unsigned int col1);
		void addToken(TokenType type, string value, unsigned int col1);
};