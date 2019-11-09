#include <iostream>
#include "tokens.hpp"
using namespace std;
#include <stack>
#include <string>
#include <vector>

int calculateOp(int a, int b, const string& op) {
	if (op == "+") return a + b;
	if (op == "-") return a - b;
	if (op == "*") return a * b;
	if (op == "/") return a / b;
	return -1;
}

int main()
{
    vector<pair<string,int>> initial_vector;
    stack<int> work_stack;
    const char* enumStrings[30] = {"", "VOID", "INT", "BYTE", "B", "BOOL", "AND",
							  "OR", "NOT", "TRUE", "FALSE", "RETURN", "IF", "ELSE",
							  "WHILE", "BREAK", "CONTINUE", "SC", "COMMA",
							  "LPAREN", "RPAREN", "LBRACE", "RBRACE", "ASSIGN",
							  "RELOP", "BINOP", "COMMENT", "ID", "NUM", "STRING"};
	int token;
	while(token = yylex()) {
		string yystring = yytext;
		if (yystring == "\n") break;
		if (token == -1) continue;
		if (token != NUM && token != BINOP){
			printf("Error: %s\n", enumStrings[token]);
			exit(0);
		}

		pair<string, int> currentPair(string(yytext), token);
		initial_vector.push_back(currentPair);
	}
	for (int i = initial_vector.size() - 1; i >=0; --i) {
		if (initial_vector[i].second == NUM) {
			work_stack.push(stoi(initial_vector[i].first));
		} else {
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
	if (work_stack.size() > 1){
		printf("Error: Bad Expression\n");
		exit(0);
	}
	printf("%d\n", work_stack.top());
	return 0;
}