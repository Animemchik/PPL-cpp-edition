#include "LexerExceptions.hpp"
#include <string>

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


// -------
InvalidCharLiteralE::InvalidCharLiteralE(string& code, string& filename, int row, int col)
    : LexerE(code, filename, row, col - 2, col - 1) {}

const std::string InvalidCharLiteralE::What() const {
    std::string errorMessage = "Exception in file \"" + filename + "\"\nInvalid character literal at row " + std::to_string(row) +
        " col " + std::to_string(col1) + ":" + std::to_string(col2) + '\n' + string_with_arrows(code, col1, col2, row);
    return errorMessage;
}
// -------

// -------
EmptyCharE::EmptyCharE(string& code, string& filename, int row, int col)
    : LexerE(code, filename, row, col - 2, col - 1) {}

const std::string EmptyCharE::What() const {
    std::string errorMessage = "Exception in file \"" + filename + "\"\nEmpty character literal at row " + std::to_string(row) +
        " col " + std::to_string(col1) + ":" + std::to_string(col2) + '\n' + string_with_arrows(code, col1, col2, row);
    return errorMessage;
}
// -------

// -------
CharNotCompleteE::CharNotCompleteE(string& code, string& filename, int row, int col)
    : LexerE(code, filename, row, col - 2, col - 1) {}

const std::string CharNotCompleteE::What() const {
    std::string errorMessage = "Exception in file \"" + filename + "\"\nNot ended character literal at row " + std::to_string(row) +
        " col " + std::to_string(col1) + ":" + std::to_string(col2) + '\n' + string_with_arrows(code, col1, col2, row);
    return errorMessage;
}
// -------
