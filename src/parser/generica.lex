%{
#include "includes.h"
#include "tok.h"
int yyerror(char *s);
/* int yylineno = 1; */
%}

digit		[0-9]
letter          [A-Za-z]
special         [-+?!_=*/^|><]
int_lit 	-?{digit}+
double_lit      -?{digit}*.{digit}+
string_lit      \"[^\"\n]*\"
lparen          \(
rparen          \)
quoteparen      '\(
delimiter       [ \n\r\t\(\)]
identifier      ({letter}|{digit}|{special})+
symbol_lit      :{identifier}
comment         ;[^\n]*

%%

{int_lit}	{ yylval.object = integer_obj(atoi(yytext)); return INTEGER_LITERAL; }
{double_lit}    { yylval.object = double_obj(atof(yytext)); return (DOUBLE_LITERAL); }
{string_lit}	{ yylval.object = string_obj(yytext); return STRING_LITERAL; }
{lparen}        { return LPAREN; }
{rparen}        { return RPAREN; }
{quoteparen}    { return QUOTEPAREN; }
{identifier}    { yylval.object = identifier_obj(yytext); return IDENTIFIER; }
{symbol_lit}    { yylval.object = identifier_obj(yytext); return SYMBOL_LITERAL; }

{comment}       {}

[ \t]*		{}
[\n]		{ yylineno++; }

.		{ fprintf(stderr, "SCANNER %d", yyerror("")); exit(1);	}

