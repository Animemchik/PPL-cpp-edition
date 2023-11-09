#pragma once
#include "TokenType.hpp"
#include <string>

struct Token {
	TokenType type;
	std::string value;
	unsigned int col1, col2, row;
};