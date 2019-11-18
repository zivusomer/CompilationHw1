#include <iostream>
#include <cstring>
#include <string>
#include "tokens.hpp"
using std::string;

void handleErrors(const string& token_str, const string& yystring) {
    if (token_str == "ERROR_UNCLOSED_STRING") {
        printf("Error unclosed string\n");
        exit(0);
    } else if (token_str == "ERROR_UNDEFINED_ESCAPE_SEQ") {
        printf("Error undefined escape sequence %c\n", yystring[yystring.length() - 1]);
        exit(0);
    } else if (token_str == "ERROR_UNDEFINED_ESCAPE_SEQ_HEX_1") {
        printf("Error undefined escape sequence x%c\n", yystring[yystring.length() - 1]);
        exit(0);
    } else if (token_str == "ERROR_UNDEFINED_ESCAPE_SEQ_HEX_2") {
        printf("Error undefined escape sequence x%c%c\n", yystring[yystring.length() - 2], yystring[yystring.length() - 1]);
        exit(0);
    }
    exit(-1);
}

void printToken(const string& token_str) {
    string yystring = yytext;
    if (token_str.rfind("ERROR", 0) == 0) { // Error was found at lexema
        handleErrors(token_str, yystring);
    } else if(token_str == "COMMENT") {
        yystring = "//";
    } else if (token_str == "WHITESPACE"){
        return;
    }
    printf("%d %s %s\n", yylineno, token_str.c_str(), yystring.c_str());
    //cout << yylineno << " " << token << " " << yystring << endl;
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
            case WHITESPACE: printToken("WHITESPACE"); break;
            case ERROR_UNCLOSED_STRING: printToken("ERROR_UNCLOSED_STRING"); break;
            case ERROR_UNDEFINED_ESCAPE_SEQ: printToken("ERROR_UNDEFINED_ESCAPE_SEQ"); break;
            case ERROR_UNDEFINED_ESCAPE_SEQ_HEX_1: printToken("ERROR_UNDEFINED_ESCAPE_SEQ_HEX_1"); break;
            case ERROR_UNDEFINED_ESCAPE_SEQ_HEX_2: printToken("ERROR_UNDEFINED_ESCAPE_SEQ_HEX_2"); break;
            case ERROR_CHAR: printToken("ERROR_CHAR"); break;
            default: break;
	    }
	}
	return 0;
}