#pragma once
#include <exception>
#include <string>
#include "Error.hpp"

using namespace std;

class LexerE : public Error {
public:
    LexerE(string& code, string& filename, int row, int col1, int col2);
    int row;
    int col1;
    int col2;
    string& code;
    string& filename;
};

class NumberTokenizeE : public LexerE {
public:
    NumberTokenizeE(string& code, string& filename, int row, int col1, int col2);
    const string What() const override;
};

class MultiCommentTokenizeE : public LexerE {
public:
    MultiCommentTokenizeE(string& code, string& filename, int row, int col);
    const string What() const override;
};

class StringNotCompleteE : public LexerE {
public:
    StringNotCompleteE(string& code, string& filename, int row, int col1, int col2);
    const string What() const override;
};
