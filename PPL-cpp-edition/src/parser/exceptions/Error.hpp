#pragma once
#include <string>

class Error {
public:
	virtual const std::string What() const;
};