#include <iostream>
#include <cstring>
#include <string>
#include "tokens.hpp"
using namespace std;
#include <string>

void checkUndefinedESC(string basicString);

void removeQuotes(string& yystring){
    yystring.erase(0,1);
    yystring.erase(yystring.length() -1, 1);
}

//assumes char before 'next' in string is backslash
string fix_bs(char next) {
    switch(next) {
        case 'n': return "\n";
        case 'r': return "\r";
        case 't': return "\t";
        case '\\': return "\\";
        case '\"': return "\"";
        case 'x': return "x"; //hexa
        default: return "error"; //error;
    }
}

string ascii(char a, char b) {
    a = tolower(a); b = tolower(b);
    a = '0' <= a && a <= '9' ? (a-'0') : (a-'a' + 10);
    b = '0' <= b && b <= '9' ? (b-'0') : (b-'a' + 10);
    char sum = a*16 + b;
    //if(sum >= 32 && sum <= 126)
    return string(1,sum);
    //return "error"; //error;
}

void handleSpecialChars(string& yystring) {
    if (yystring.length() < 2) return;
    for(int i = 0; i < yystring.length() - 1; i++) {
        if(yystring[i] != '\\') continue;
        char next = yystring[i + 1];
        string replacement = fix_bs(next);
        if(replacement != "x") {
            yystring.replace(i, 2, replacement);
        }
        else {
            // printf("i+2 = %c, i+3 = %c\n", yystring[i+2],yystring[i+3]);
            string res = ascii(yystring[i+2],yystring[i+3]);
            //cout << "res = " << res << endl;
            if (res != "error"){
                yystring.replace(i, 4, res);
            } else {
                printf("tf");
                // HANDLE ERROR
                //error_handle("in_string");
            }
        }
    } //TODO: Handle errors within string
}

bool InRangeHexa(char x) {
    char lx = tolower(x);
    return (lx <= 'f' && lx >= 'a') || (lx >= '0' && lx <= '9');
}

void checkUndefinedESC(string text) {
    text.pop_back();
    for(int i = 0; i < text.length() - 1; i++) {
        if(text[i] == '\\' && fix_bs(text[i+1]) == "error") {
            printf("Error undefined escape sequence %c\n", text[i+1]);
            exit(0);
        }
        if(text[i] == '\\' && text[i+1] == 'x') { //check legal hexa
            if(!(text.length() - i >= 4 && InRangeHexa(text[i + 2]) && InRangeHexa(text[i+3]))) {
                printf("Error undefined escape sequence x");
                if (i + 2 < text.length()) printf("%c", text[i + 2]);
                if (i + 3 < text.length()) printf("%c", text[i + 3]);
                printf("\n");
                exit(0);
            }
        }
    }
}

void checkQuotes(string yystring) {
    if(yystring.length() == 1 || yystring[0] != '\"' || yystring[yystring.length()-1] != '\"') {
        printf("Error unclosed string\n");
        exit(0);
    }
}

void checkLastBS(string yystring) {
    int l = yystring.length();
    if(l >= 2 && yystring[l - 2] == '\\') {
        printf("Error unclosed string\n");
        exit(0);
    }
}

void handleStringErrors(string& yystring) {
    checkLastBS(yystring);
    checkQuotes(yystring);
    checkUndefinedESC(yystring);
}

void printToken(const char* token) {
    string yystring = yytext;
    if (strcmp(token, "STRING") == 0){ //need to check all cases & errors for strings
        handleStringErrors(yystring); //if there is an error, we will exit. otherwise, continue to handle string
        removeQuotes(yystring);
        handleSpecialChars(yystring);
    }
    else if(strcmp(token, "COMMENT") == 0) {
        yystring = "\\\\";
    }
    cout << yylineno << " " << token << " " << yystring << endl;
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