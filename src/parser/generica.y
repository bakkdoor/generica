%{
#include "includes.h"

int yyerror(char *s);
int yylex(void);
%}

%union{
  struct gobject*   object;
}

%start	programm

%token                  LPAREN
%token                  RPAREN
%token                  QUOTEPAREN

%token <object>         INTEGER_LITERAL
%token <object>         FLOAT_LITERAL
%token <object>         STRING_LITERAL
%token <object>         SYMBOL_LITERAL
%token <object>         IDENTIFIER
%type  <object>         atom

%%

programm:       /* empty */
                | programm sexp
                ;

sexp:           atom
                | list
                ;
list:           empty_list
                | LPAREN sexp_list RPAREN
                | quoted_list;


empty_list:     LPAREN RPAREN
                | QUOTEPAREN RPAREN;

quoted_list:    QUOTEPAREN sexp RPAREN;

sexp_list:      sexp 
                | sexp_list sexp;

atom:           INTEGER_LITERAL	{ $$ = $1; }
                | FLOAT_LITERAL	{ $$ = $1; }
                | STRING_LITERAL { $$ = $1; }
                | SYMBOL_LITERAL { $$ = $1; }
                | IDENTIFIER { $$ = $1; }
                ;

%%

int yyerror(char *s)
{
  extern int yylineno;
  extern char *yytext;
  
  fprintf(stderr, "ERROR: %s at symbol %s on line %d\n", s, yytext, yylineno);
  exit(1);
}
