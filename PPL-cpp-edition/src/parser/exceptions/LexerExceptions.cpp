#include "LexerExceptions.hpp"
#include <string>
#include <sstream>
#include <iostream>

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

// -------
LexerE::LexerE(string& code, string& filename, int row, int col1, int col2) : row(row), col1(col1), col2(col2), code(code), filename(filename) {}
// -------


// -------
NumberTokenizeE::NumberTokenizeE(string& code, string& filename, int row, int col1, int col2) : LexerE(code, filename, row, col1, col2) {}
const std::string NumberTokenizeE::What() const {
    std::string errorMessage = "Exception in file \"" + filename + "\"\nUnable to tokenize a number at row " + std::to_string(row) +
        " col " + std::to_string(col1) + ":" + std::to_string(col2) + '\n' + string_with_arrows(code, col1, col2, row);
    return errorMessage;
}
// -------


// -------
MultiCommentTokenizeE::MultiCommentTokenizeE(string& code, string& filename, int row, int col) : LexerE(code, filename, row, col-1, col) {}
const std::string MultiCommentTokenizeE::What() const {
    std::string errorMessage = "Exception in file \"" + filename + "\"\nNot ended multi comment at row " + std::to_string(row) +
        " col " + std::to_string(col1) + ":" + std::to_string(col2) + '\n' + string_with_arrows(code, col1, col2, row);
    return errorMessage;
}
// -------


// -------
StringNotCompleteE::StringNotCompleteE(string& code, string& filename, int row, int col1, int col2) : LexerE(code, filename, row, col1, col2) {}
const std::string StringNotCompleteE::What() const {
    std::string errorMessage = "Exception in file \"" + filename + "\"\nNot ended string at row " + std::to_string(row) +
        " col " + std::to_string(col1) + ":" + std::to_string(col2) + '\n' + string_with_arrows(code, col1, col2, row);
    return errorMessage;
}
// -------

