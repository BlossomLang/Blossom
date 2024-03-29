#ifndef BLOSSOM_TOOLCHAIN_PARSER
#define BLOSSOM_TOOLCHAIN_PARSER

#include "../../commons/Logger.h"

#include <vector>
#include <iostream>
#include "../lexar/Token.h"

class Parser {

public:
	Token parseTokens(std::vector<Token> t) {
		std::vector<Token> sub;

		bool hasParenthesisOpened = false;
		std::vector<Token> stack;

		//Token main = getSubTokens(-1, TokenGroupType::MAIN, t);
		return getSubTokens(-1, GroupType::MAIN, t);
	}

private:
Token getSubTokens(int startIndex, GroupType groupType, std::vector<Token> tokens) {
	std::vector<Token> stack;
	bool ended = false;

	for (int i = startIndex + 1; i < tokens.size(); ++i) {
		Token token = tokens[i];

		if(isTypeClosing(token.type)) {
			if(getGroupType(token.type) == groupType) {
				ended = true;
				break;
			}
		}
		else if(isTypeOpening(token.type)) {
			Token group = getSubTokens(i, getGroupType(token.type), tokens);
			stack.push_back(group);
		}
		else {
			stack.push_back(token);
		}
	}

	if(ended || groupType == MAIN) {
		return Token(groupType, stack);
	}
	else {
		Logger::global().error("Parser", "The Token Group was not closed before eof!");
	}
} 
};

#endif