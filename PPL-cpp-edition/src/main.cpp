#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "parser/Lexer.hpp"

using namespace std;


int main() {
	std::cout << "Hello, World!\nHello PPL!" << std::endl;

	string filename = "C:\\Users\\User\\Desktop\\C++\\programming language\\PPL-cpp-edition\\PPL-cpp-edition\\src\\tests\\main.ppl";
	/*
	string filename;
	std::cin >> filename;
	*/

	std::ifstream file(filename); // Открываем файл для чтения
	if (!file) {
		std::cerr << "Не удалось открыть файл." << std::endl;
		return 1;
	}

	std::stringstream buffer;
	buffer << file.rdbuf(); // Считываем содержимое файла в буфер stringstream

	file.close();
	
	std::string code = buffer.str(); // Получаем строку из буфера

	Lexer lexer(code, filename);
	LexerOutput lexerOutput = lexer.tokenize();

	if (!lexerOutput.errors.empty()) {
		for (const auto error : lexerOutput.errors) {
			std::cout << error->What() << std::endl;
		}
	}
	else {
		std::vector<Token> tokens = lexerOutput.tokens;

		for (const Token token : tokens) {
			std::cout << token.type << " " << token.value << " " << token.row << "[" << token.col1 << ":" << token.col2 << "]" << std::endl;
		}
	}
	return 0;
}