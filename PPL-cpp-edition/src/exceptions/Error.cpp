#include "Error.hpp"
#include <sstream>

const std::string Error::What() const {
	return "Error";
}

std::string string_with_arrows(const std::string& code, unsigned int col1, unsigned int col2, unsigned int row) {
    std::stringstream result;
    std::istringstream textStream(code);
    std::string line;
    int lineNumber = 1;

    while (std::getline(textStream, line)) {
        if (lineNumber == row) break;
        lineNumber++;
    }
    result << line << '\n';
    for (int i = 0; i < col1 - 1; i++) {
        result << ' ';
    }
    for (int i = 0; i < col2 - col1 + 1; i++) {
        result << '^';
    }
    return result.str();
}
