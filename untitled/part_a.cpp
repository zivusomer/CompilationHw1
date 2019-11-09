#include <iostream>
#include <cstring>
#include "tokens.hpp"
using namespace std;

void removeQuotes(){
    for (size_t i = 1; i < yyleng - 1; ++i){
        yytext[i-1] = yytext[i];
    }
    yytext[yyleng - 2] = '\0';
}

void handleSpecialChars() {
    if (yyleng < 2) return;
    char temp_str[3] = "00";
    for (size_t i = 0; i < yyleng - 2; ++i){
        temp_str[0] = yytext[i];
        temp_str[1] = yytext[i + 1];
        if (strcmp(temp_str, "\\n") == 0){
            yytext[i] = '\n';
        } else if (strcmp(temp_str, "\\r") == 0) {
            yytext[i] = '\r';
        } else if (strcmp(temp_str, "\\t") == 0){
            yytext[i] = '\t';
        } else if (strcmp(temp_str, "\\\\") == 0) {
            yytext[i] = '\\';
        } else if (strcmp(temp_str, "\\\"") == 0){
            yytext[i] = '\"';
        } // TODO: remove the char used to be after the '\' at the yytext string
    }
}

void printToken(const char* token) {
    if (token == "STRING"){
        removeQuotes();
        handleSpecialChars();
    }
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
            default: return 0; //add error handle here
	    }
	}
	return 0;
}