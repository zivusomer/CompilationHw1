#include <iostream>
#include "tokens.hpp"
using namespace std;

void printToken(const char* token) {
    cout << yylineno << " " << token << " " << yytext << endl;
}

int main()
{
	int token;
	while(token = yylex()) {
	    switch(token) {
	        case VOID: printToken("VOID"); break;
            case INT: printToken("INT"); break;
            case BYTE: printToken("BYTE"); break;
            case B: printToken("B"); break;
            case BOOL: printToken("BOOL"); break;
            case AND: printToken("AND"); break;
            case OR: printToken("OR"); break;
            case NOT: printToken("NOT"); break;
            case TRUE: printToken("TRUE"); break;
            case FALSE: printToken("FALSE"); break;
            case RETURN: printToken("RETURN"); break;
            case IF: printToken("IF"); break;
            case ELSE: printToken("ELSE"); break;
            case WHILE: printToken("WHILE"); break;
            case BREAK: printToken("BREAK"); break;
            case CONTINUE: printToken("CONTINUE"); break;
            case SC: printToken("SC"); break;
            case COMMA: printToken("COMMA"); break;
            case LPAREN: printToken("LPAREN"); break;
            case RPAREN: printToken("RPAREN"); break;
            case LBRACE: printToken("LBRACE"); break;
            case RBRACE: printToken("RBRACE"); break;
            case ASSIGN: printToken("ASSIGN"); break;
            case RELOP: printToken("RELOP"); break;
            case BINOP: printToken("BINOP"); break;
            case COMMENT: printToken("COMMENT"); break;
            case ID: printToken("ID"); break;
            case NUM: printToken("NUM"); break;
            case STRING: printToken("STRING"); break;
            default: return 0; break; //add error handle here
	    }
	}
	return 0;
}