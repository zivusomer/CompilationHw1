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
	int token;
	while(token = yylex()) {
		string yystring = yytext;
		if (yystring == "\n") break;
		if (token == -1) continue;

		pair<string, int> currentPair(string(yytext), token);
		initial_vector.push_back(currentPair);
	}
	for (int i = initial_vector.size() - 1; i >=0; --i) {
		if (initial_vector[i].second == NUM) {
			work_stack.push(stoi(initial_vector[i].first));
		} else {
			int a = work_stack.top();
			work_stack.pop();
			int b = work_stack.top();
			work_stack.pop();
			string op = initial_vector[i].first;
			work_stack.push(calculateOp(a, b, op));
		}
	}
	printf("%d\n", work_stack.top());
	return 0;
}