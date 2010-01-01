%{
#include "includes.h"

int yyerror(char *s);
int yylex(void);
%}

%union{
  gobject*   object;
  key_val_node *key_val_list;
}

%start	programm

%token                  LPAREN
%token                  RPAREN
%token                  QUOTEPAREN
%token                  LCURLY
%token                  RCURLY
%token                  ARROW

%token <object>         INTEGER_LITERAL
%token <object>         DOUBLE_LITERAL
%token <object>         STRING_LITERAL
%token <object>         SYMBOL_LITERAL
%token <object>         IDENTIFIER
%type  <object>         atom
%type  <object>         hash_literal
%type  <key_val_list>   key_value_list

%type  <object>         empty_list
%type  <object>         empty_quote
%type  <object>         sexp
%type  <object>         sexp_list

%%

programm:       /* empty */
                | programm sexp { print_object(eval($2), stdout); printf("\n"); }
                ;

sexp:           empty_list
                | empty_quote
                | LPAREN sexp_list RPAREN { 
                    $$ = cons_obj(car($2), cdr($2));
                }
                | QUOTEPAREN sexp_list RPAREN {
                    $$ = cons_obj(car($2), cdr($2));
                };

empty_list:     LPAREN RPAREN { 
                    $$ = cons_obj(NULL, NULL); 
                };

empty_quote:    QUOTEPAREN RPAREN { 
                    gobject *obj = cons_obj(NULL, NULL);
                    obj->quoted = true;
                    $$ = obj;
                };

sexp_list:      /* empty */ { $$ = nil }
                | sexp sexp_list { $$ = cons_obj($1, $2); }
                | atom sexp_list { $$ = cons_obj($1, $2); };

atom:           INTEGER_LITERAL	{ $$ = $1; }
                | DOUBLE_LITERAL { $$ = $1; }
                | STRING_LITERAL { $$ = $1; }
                | SYMBOL_LITERAL { $$ = $1; }
                | IDENTIFIER { $$ = $1; }
                | hash_literal { $$ = $1}
                ;

hash_literal: LCURLY key_value_list RCURLY { $$ = hash_obj($2) };

key_value_list: SYMBOL_LITERAL ARROW sexp { $$ = key_val_obj($1, $3, NULL); }
                | SYMBOL_LITERAL ARROW atom { $$ = key_val_obj($1, $3, NULL); }
                | SYMBOL_LITERAL ARROW sexp key_value_list { 
                  $$ = key_val_obj($1, $3, $4); 
                }
                | SYMBOL_LITERAL ARROW atom key_value_list { 
                  $$ = key_val_obj($1, $3, $4);
                };

%%

int yyerror(char *s)
{
  extern int yylineno;
  extern char *yytext;
  
  fprintf(stderr, "ERROR: %s at symbol %s on line %d\n", s, yytext, yylineno);
  exit(1);
}
