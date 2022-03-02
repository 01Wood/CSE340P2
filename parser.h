#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <map>
#include <vector>
#include "lexer.h"
using namespace std;

vector<int> mem;
int mem_counter;
map<string, int> location;
int next_available = 0;
vector<int> inputs;
int next_input = 0;


class Parser {
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

