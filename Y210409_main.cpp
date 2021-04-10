// Y210409_main.cpp Copyright(C) 2021 http://youtube.com/programmercpp
#include <iostream>
#include <sstream>
#include <exception>

#if 0
#include "Y210409_Token.h"
#include "Y210409_Tokenizer.h"
int main()
{
	try {
		Tokenizer t(std::cin);
		for (;;) {
			const auto token = t.Read(std::cin);
			if (token == Token::Type::End)
				break;
			else
				std::cout << token << '\n';
		}
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}
#else
#include "Y210409_Parser.h"
void test(std::istream&& istm)
{
	std::cout << Parser(istm).ParseExpression(istm)->Evaluate() << '\n';
}
int main()
{
	try {
		std::string s;
		while (std::getline(std::cin, s)) {
			test(std::istringstream(s));
		}
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}
#endif
