#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <map>
#include <vector>
#include "lexer.h"
using namespace std;

class Parser {

	vector<int> mem;
	int mem_counter;
	string LHS;
	vector<string> RHS;

public:
	Parser();
	LexicalAnalyzer lexer;
	Token expect(TokenType expected_type);
	void parse_grammar();
	void parse_ruleList();
	void parse_rule();
	void parse_rightHandSide();
	void parse_idList();
	void syntax_error();
};

#endif

