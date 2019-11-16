%{

/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"

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
esc_wo_bsnr     ({dbs}|{bsq}|{bst}|{bsz}|{bsx}{hex})
str_char_w_bsnr ({str_char}|{bsn}|{bsr})
valid_bsnr_usage({str_char_w_bsnr}*({bsn}|{bsr}){str_char_w_bsnr}+|{str_char_w_bsnr}+({bsn}|{bsr}){str_char_w_bsnr}*)
undef_esc       ((\\)[^\\\"nrt0x])
whitespace		([\t\n ])

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
{letter}({letter}|{digit})*                                    return ID;
{pos_digit}{digit}*          			                        return NUM;
{digit}                                                         return NUM;
{quote}({str_char}|{esc_wo_bsnr}|{valid_bsnr_usage})*{quote}    return STRING;
{quote}[^\"\n]*({str_char}|\")                                  return STRING;
{quote}                                                         return STRING;
{whitespace}			                                    	return -1;
.		                                                        printf("Error %s\n", yytext); exit(0);

%%