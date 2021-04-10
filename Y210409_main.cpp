#include <iostream>
#include <string>
#include <stdexcept>

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
