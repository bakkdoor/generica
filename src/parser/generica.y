%{
#include "includes.h"

int yyerror(char *s);
int yylex(void);
%}

%union{
  gobject*   object;
}

%start	programm

%token                  LPAREN
%token                  RPAREN
%token                  QUOTEPAREN

%token <object>         INTEGER_LITERAL
%token <object>         DOUBLE_LITERAL
%token <object>         STRING_LITERAL
%token <object>         SYMBOL_LITERAL
%token <object>         IDENTIFIER
%type  <object>         atom
%type  <object>         list
%type  <object>         empty_list
%type  <object>         quoted_list
%type  <object>         sexp
%type  <object>         sexp_list

%%

programm:       /* empty */
                | programm sexp { eval($2) }
                ;

sexp:           atom
                | list
                ;
list:           empty_list
                | LPAREN sexp_list RPAREN { 
                    $$ = cons_obj(car($2), cdr($2));
                  }
                | quoted_list;


empty_list:     LPAREN RPAREN { $$ = cons_obj(NULL, NULL); }
                | QUOTEPAREN RPAREN { $$ = cons_obj(NULL, NULL); };

quoted_list:    QUOTEPAREN sexp RPAREN { 
                    gobject *obj = cons_obj(car($2), cdr($2));
                    obj->quoted = true;
                    $$ = obj;
                };

sexp_list:      sexp { $$ = $1 }
                | sexp_list sexp;

atom:           INTEGER_LITERAL	{ $$ = $1; }
                | DOUBLE_LITERAL { $$ = $1; }
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
