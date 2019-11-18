%{

/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"
#define MAX_BUFF_SIZE 1024
char ascii(char a, char b);

char str_buff[MAX_BUFF_SIZE];
char *str_buff_ptr;

%}

%option yylineno
%option noyywrap
void            (void)
int             (int)
byte            (byte)
b               (b)
bool            (bool)
and             (and)
or              (or)
not             (not)
true            (true)
false           (false)
return          (return)
if              (if)
else            (else)
while           (while)
break           (break)
continue        (continue)
sc              (;)
comma           (,)
quote           (\")
lparen          (\()
rparen          (\))
lbrace          (\{)
rbrace          (\})
assign          (=)
eq              (==)
neq             (!=)
st              (<)
lt              (>)
seq             (<=)
leq             (>=)
plus            (\+)
minus           (\-)
mul             (\*)
div             (\/)
bs              (\\)
dbs             (\\\\)
ds              (\/\/)
pos_digit       ([1-9])
digit   		([0-9])
letter  		([a-zA-Z])
digit_letter    ({digit}|{letter})
underscore      (_)
letter_         ({letter}|{underscore})
bsx             (\\x)
bsn             (\\n)
bsr             (\\r)
bsq             (\\\")
bst             (\\t)
bsz             (\\0)
hex             ([0-9a-fA-F]{2})
str_char        ([^\"\\\n\r])
whitespace		([\t\n ])

%x str
%%

{void}                                                          return VOID;
{int}                                                           return INT;
{byte}                                                          return BYTE;
{b}                                                             return B;
{bool}                                                          return BOOL;
{and}                                                           return AND;
{or}                                                            return OR;
{not}                                                           return NOT;
{true}                                                          return TRUE;
{false}                                                         return FALSE;
{return}                                                        return RETURN;
{if}                                                            return IF;
{else}                                                          return ELSE;
{while}                                                         return WHILE;
{break}                                                         return BREAK;
{continue}                                                      return CONTINUE;
{sc}                                                            return SC;
{comma}                                                         return COMMA;
{lparen}                                                        return LPAREN;
{rparen}                                                        return RPAREN;
{lbrace}                                                        return LBRACE;
{rbrace}                                                        return RBRACE;
{assign}                                                        return ASSIGN;
{eq}|{neq}|{st}|{lt}|{seq}|{leq}                                return RELOP;
{plus}|{minus}|{mul}|{div}                                      return BINOP;
{ds}.*                                                          return COMMENT;
{letter}({letter}|{digit})*                                     return ID;
{pos_digit}{digit}*          			                        return NUM;
{digit}                                                         return NUM;

{quote}                                                         {
                                                                    str_buff_ptr = str_buff;
                                                                    BEGIN(str);
                                                                }

<str>{quote}                                                    {
                                                                    BEGIN(INITIAL);
                                                                    *str_buff_ptr = '\0';
                                                                    yytext = str_buff;
                                                                    return STRING;
                                                                }

<str>{bs}                                                       *str_buff_ptr++ = '\\';
<str>{bsq}                                                      *str_buff_ptr++ = '\"';
<str>{bsn}                                                      *str_buff_ptr++ = '\n';
<str>{bsr}                                                      *str_buff_ptr++ = '\r';
<str>{bst}                                                      *str_buff_ptr++ = '\t';
<str>{bsz}                                                      *str_buff_ptr++ = '\0';
<str>{bsx}{hex}                                                 *str_buff_ptr++ = ascii(yytext[2], yytext[3]);

<str>[\n\r]                                                     return ERROR_UNCLOSED_STRING;
<str>{bsx}{digit_letter}                                        return ERROR_UNDEFINED_ESCAPE_SEQ_HEX_1;
<str>{bsx}{digit_letter}{digit_letter}                          return ERROR_UNDEFINED_ESCAPE_SEQ_HEX_2;
<str>{bs}.                                                      return ERROR_UNDEFINED_ESCAPE_SEQ;

<str>{str_char}+                                                 {
                                                                    char *current_char = yytext;
                                                                    while (*current_char){
                                                                        *str_buff_ptr++ = *current_char++;
                                                                    }
                                                                }

{whitespace}			                                    	return WHITESPACE;
.		                                                        printf("Error %s\n", yytext); exit(0);

%%

char ascii(char a, char b) {
    a = 'A' <= a && a <= 'Z' ? a - 'A' + 'a' : a;
    b = 'A' <= b && b <= 'Z' ? b - 'A' + 'a' : b;
    a = '0' <= a && a <= '9' ? (a-'0') : (a-'a' + 10);
    b = '0' <= b && b <= '9' ? (b-'0') : (b-'a' + 10);
    char sum = a*16 + b;
    return sum;
}