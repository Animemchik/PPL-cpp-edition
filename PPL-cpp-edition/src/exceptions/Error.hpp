#pragma once
#include <string>

class Error {
public:
	virtual const std::string What() const;
};

std::string string_with_arrows(const std::string& code, unsigned int col1, unsigned int col2, unsigned int row);