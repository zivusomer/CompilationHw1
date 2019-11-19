#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include "tokens.hpp"
using std::string;
using std::stack;
using std::vector;
using std::pair;

int calculateOp(int a, int b, const string& op) {
	if (op == "+") return a + b;
	if (op == "-") return a - b;
	if (op == "*") return a * b;
	if (op == "/") return a / b;
	return -1;
}

int main()
{
    int token;
    vector<pair<string,int>> initial_vector;
    stack<int> work_stack;
    const char* enumStrings[35] = {"", "VOID", "INT", "BYTE", "B", "BOOL", "AND",
							  "OR", "NOT", "TRUE", "FALSE", "RETURN", "IF", "ELSE",
							  "WHILE", "BREAK", "CONTINUE", "SC", "COMMA",
							  "LPAREN", "RPAREN", "LBRACE", "RBRACE", "ASSIGN",
							  "RELOP", "BINOP", "COMMENT", "ID", "NUM", "STRING",
							  "WHITESPACE", "ERROR_UNCLOSED_STRING", "ERROR_UNDEFINED_ESCAPE_SEQ",
							  "ERROR_UNDEFINED_ESCAPE_SEQ_HEX_1", "ERROR_UNDEFINED_ESCAPE_SEQ_HEX_2"};

	while(token = yylex()) {
	    string yystring = yytext;
		if (token == WHITESPACE){
		    // End of equation
            if (yystring == "\n") break;
            // Space
            continue;
		}
		// Invalid token
		if (token != NUM && token != BINOP){
		    if (string(enumStrings[token]).rfind("ERROR", 0) == 0){
		        printf("Error: STRING\n");
		    } else {
                printf("Error: %s\n", enumStrings[token]);
		    }
			exit(0);
		}

		pair<string, int> currentPair(string(yytext), token);
		initial_vector.push_back(currentPair);
	}

	for (int i = initial_vector.size() - 1; i >=0; --i) {
		if (initial_vector[i].second == NUM) {
			work_stack.push(stoi(initial_vector[i].first));
		} else {
			// Not enough operands at the expression
			if (work_stack.size() < 2){
				printf("Error: Bad Expression\n");
				exit(0);
			}
			int a = work_stack.top();
			work_stack.pop();
			int b = work_stack.top();
			work_stack.pop();
			string op = initial_vector[i].first;
			work_stack.push(calculateOp(a, b, op));
		}
	}

	// Not enough operators at the expression
	if (work_stack.size() > 1){
		printf("Error: Bad Expression\n");
		exit(0);
	}
	printf("%d\n", work_stack.top());
	return 0;
}