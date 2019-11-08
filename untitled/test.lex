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
lparen          (()
rparen          ())
lbrace          ({)
rbrace          (})
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
ds              (\/\/)
dbs             (bs)(bs)
pos_digit       ([1-9])
digit   		([0-9])
letter  		([a-zA-Z])
letter_         (letter|_)
hex             ([0-9a-fA-F]{2})
hexa_exp        ((bs)[x](hex))
lfcr            (\\([n]|[r]))
lfcr_whole      (^lfcr$)
bsnr            (((.)*(lfcr)(.)+)|((.)+(lfcr)(.)*))
quote           (")
not_good        (lfcr_whole|bs|quote)
bsq             (bs)(quote)
bst             ((bs)[t])
bsz             ((bs)[0])
esc             (dbs|bsq|bst|bsz|hexa_exp|bsnr)
whitespace		([\t\n ])

%%

{void}                                  return VOID;
{int}                                   return INT;
{byte}                                  return BYTE;
{b}                                     return B;
{bool}                                  return BOOL;
{and}                                   return AND;
{or}                                    return OR;
{not}                                   return NOT;
{true}                                  return TRUE;
{false}                                 return FALSE;
{return}                                return RETURN;
{if}                                    return IF;
{else}                                  return ELSE;
{while}                                 return WHILE;
{break}                                 return BREAK;
{continue}                              return CONTINUE;
{sc}                                    return SC;
{comma}                                 return COMMA;
{lparen}                                return LPAREN;
{rparen}                                return RPAREN;
{lbrace}                                return LBRACE;
{rbrace}                                return RBRACE;
{assign}                                return ASSIGN;
{eq}|{neq}|{st}|{lt}|{seq}|{leq}        return RELOP;
{plus}|{minus}|{mul}|{div}              return BINOP;
{ds}.*                                  return COMMENT;
{letter}{letter_|digit}*                return ID;
{pos_digit}{digit}*          			return NUM;
{quote}{^not_good|esc}{quote}           return STRING;
{whitespace}				;
.		printf("Lex doesn't know what that is!\n");

%%