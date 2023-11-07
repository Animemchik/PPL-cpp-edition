#pragma once

enum TokenType {
	
	// Data types
	WORD,           // a
	COMMENT,        // // hello
	MULTICOMMENT,   // /* hello */
	CHAR,           // 'a'
	STRING,         // "hello world"
	HEX,            // 0xC4
	NUMBER,         // 1024010240
	FLOAT,          // 1.131

	// keys
	PUBLIC,
	PRIVATE,
	PROTECTED,
	FINAL,
	STATIC,
	FUNC,           // func
	CLASS,          // class
	NEW,			// new Class()
	INTERFACE,      // interface
	ENUM,           // enum
	IF,             // if () {}
	ELSE,           // else {}
	FOR,            // for ( | | ) {}
	WHILE,          // while () {}
	DO_WHILE,       // do {} while ()
	BREAK,          // break
	CONTINUE,       // continue
	RETURN,         // return expr
	INCLUDE,        // include "smt.ppl"
	USING,          // using namespace
	FOREACH,        // foreach ( : ) {}
	SWITCH,         // switch() {}
	CASE,           // case() {}
	THROW,			// throw new Error
	TRY,			// try {}
	CATCH,			// catch (Error) {}
	NAMESPACE,		// namespace
	AND,            // and
	OR,             // or
	NOT,            // not
	
	// Binary symbols
	PLUS,           // +
	MINUS,          // -
	MULTI,          // *
	DIVIDE,         // /
	EQ,             // =
	PERCENT,        // %

	PLUSPLUS,       // ++
	MINUSMINUS,     // --

	PLUSEQ,         // +=
	MINUSEQ,        // -=
	MULTIEQ,        // *=
	DIVIDEEQ,       // /=
	PERCENTEQ,      // %=

	AMPEQ,			// &=
	CARETEQ,		// ^=
	BAREQ,			// |=
	COLONCOLONEQ,	// ::=

	LTLT,			// <<
	GTGT,			// >>
	GTGTGT,			// >>>
	LTLTEQ,			// <<=
	GTGTEQ,			// >>=
	GTGTGTEQ,		// >>>=
	

	// DOTDOT,			// ..
	// STARSTAR,		// **
	// QUESTIONCOLON,	// ?:
	// QUESTQUEST,		// ??

	// Conditional symbols
	EQEQ,           // ==
	EXCLEQ,         // !=
	LT,             // <
	LTEQ,           // <=
	GT,             // >
	GTEQ,           // >=
	MINUSGT,		// ->
	AT,				// @
	AMP,            // &
	BAR,            // |
	QUESTION,       // ?
	COLON,          // :
	CARET,          // ^
	TILDE,          // ~
	LPAREN,         // (
	RPAREN,         // )
	LBRACKET,       // [
	RBRACKET,       // ]
	LBRACE,         // {
	RBRACE,         // }
	COMMA,          // ,
	DOT,            // .
	SEMICOLON,      // ;
	PASS,           // "\n\t "
	tEOF             // End Of File
};