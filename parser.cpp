#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include <vector>
#include "parser.h"
#include "lexer.h"
#include "inputbuf.h"

using namespace std;

void Parser::syntax_error() {
    cout << "SYNTAX ERROR !!!\n";
    exit(1);
}

Token Parser::expect(TokenType expected_type) {
    Token t = lexer.GetToken();
    if (t.token_type != expected_type)
        syntax_error();
    return t;
}

Parser::Parser() {
    for (int i = 0; i < 100; ++i) {
        mem.push_back(0);
    }
    mem_counter = 0;
}

//Grammar -> Rule_list HASH
void Parser::parse_grammar() {
    parse_ruleList();
    expect(HASH);

    Token t = lexer.GetToken();
    if (t.token_type != END_OF_FILE) {
        syntax_error();
    }
    return;
}

//Rule_list -> Rule Rule_list | Rule
//FIRST(Rule_list) = {ID}
//FOLLOW(Rule_list) = {HASH}
void Parser::parse_ruleList() {
    Token t1, t2;
    t1 = lexer.peek(1);
    t2 = lexer.peek(2);
    if ((t1.token_type == ID) && (t2.token_type == ARROW)) {
        parse_rule();
        t1 = lexer.peek(1);
        t2 = lexer.peek(2);
        if ((t1.token_type == ID) && (t2.token_type == ARROW)) {
            parse_ruleList();
        }
        else if ((t1.token_type == HASH)) {
            return;
        }
        else {
            syntax_error();
        }
    }
    else {
        syntax_error();
    }
}

//Rule -> ID ARROW Right_hand_side STAR
//FIRST(Rule) = {ID}
//FOLLOW(Rule) = {HASH}
void Parser::parse_rule() {
    Token t1, t2;
    t1 = lexer.peek(1);
    t2 = lexer.peek(2);
	if ((t1.token_type == ID) && (t2.token_type == ARROW)) {
		t1 = expect(ID);
        LHS = t1.lexeme;
		expect(ARROW);
		t1 = lexer.peek(1);
		if (t1.token_type == ID) {
			parse_rightHandSide();
			t1 = lexer.peek(1);
			if (t1.token_type == STAR) {
				expect(STAR);
				return;
			}
			else {
				syntax_error();
			}
		}
		else if (t1.token_type == STAR) {
			expect(STAR);
			return;
		}
		else {
			syntax_error();
		}
	}
	else {
		syntax_error();
	}
}

//Right_hand_side -> Id_list | epsilon
//FIRST(Right_hand_side) = {ID, epsilon}
//FOLLOW(Right_hand_side) = {STAR}
void Parser::parse_rightHandSide() {
    Token t;
    t = lexer.peek(1);
    if (t.token_type == ID) {
        parse_idList();
        return;
    }
    else if (t.token_type == STAR) {
        return;
    }
    else {
        syntax_error();
    }
}


//Id_list -> ID Id_list | ID
//FIRST(Id_list) = {ID}
//FOLLOW(Id_list) = {STAR}
void Parser::parse_idList() {
	Token t;
	t = lexer.peek(1);
	if (t.token_type == ID) {
		t = expect(ID);
        RHS.push_back(t.lexeme);
		t = lexer.peek(1);
		if (t.token_type == ID) {
			parse_idList();
            t = lexer.peek(1);
            if (t.token_type == STAR) {
			    return;
		    }
            else {
                syntax_error();
            }
        }
        else if (t.token_type == STAR) {
            return;
        }
		else {
			syntax_error();
		}
	}
	else {
		syntax_error();
	}
}