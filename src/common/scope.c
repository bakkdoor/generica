#include "includes.h"

void init_global_scope()
{
  /* init to NULL */
  global_scope->builtins = NULL;

  scope_define(global_scope, identifier_obj("nil"), nil);
  scope_define(global_scope, identifier_obj("t"), t);

  /* scope_define_builtin("define", define); */
  scope_define_builtin(global_scope, "car", car, 1);
  scope_define_builtin(global_scope, "cdr", cdr, 1);
  scope_define_builtin(global_scope, "cons", cons, 2);
  scope_define_builtin(global_scope, "length", length, 1);
  scope_define_builtin(global_scope, "print", print_object_stdout, 1);
  scope_define_builtin(global_scope, "println", println_object_stdout, 1);
  scope_define_builtin(global_scope, "=", equal, 2);
  scope_define_builtin(global_scope, "+", add, 2);
  scope_define_builtin(global_scope, "-", subtract, 2);
  scope_define_builtin(global_scope, "*", multiply, 2);
  scope_define_builtin(global_scope, "/", divide, 2);

  scope_define_builtin(global_scope, "if", if_f, 3);
  scope_define_builtin(global_scope, "unless", unless, 3);
  scope_define_builtin_special(global_scope, "define", define, 2);
  scope_define_builtin_special(global_scope, "lambda", lambda, 2);
  scope_define_builtin_special(global_scope, "do", do_f, 2);
  scope_define_builtin_special(global_scope, "special", special, 2);
  scope_define_builtin(global_scope, "eval", eval_f, 1);
}

void scope_define_builtin(scope *sc, char *ident, gobject (*func)(gobject args, scope *sc), unsigned int n_args)
{
  builtin *new_b = malloc(sizeof(builtin));
  builtin *tmp;

  assert(new_b);
  assert(ident);
  assert(func);

  new_b->identifier = ident;
  new_b->func = func;
  new_b->n_args = n_args;
  new_b->special = false;

  tmp = sc->builtins;
  new_b->next = tmp;
  sc->builtins = new_b;
}

void scope_define_builtin_special(scope *sc, char *ident, 
                                  gobject (*func)(gobject args, scope *sc), 
                                  unsigned int n_args)
{
  scope_define_builtin(sc, ident, func, n_args);
  builtin *new_b = sc->builtins;
  new_b->special = true;
}

scope* new_scope(scope *parent)
{
  scope *sc = malloc(sizeof(scope));
  assert(sc);
  sc->parent = parent;
  sc->scope_ht = new_hash(NULL);
  assert(sc->scope_ht);
  return sc;
}

gobject scope_get_ident(scope *sc, gobject identifier)
{
  hash_entry *entry;
  if((entry = hash_lookup(sc->scope_ht, identifier))) {
    if(entry->value) {
      return entry->value;
    }
    return nil;
  } else {
    if(sc->parent) {
      return scope_get_ident(sc->parent, identifier);
    }
    return nil;
  }
}

builtin* scope_get_builtin(scope *sc, char *identifier)
{
  builtin *tmp;
  for(tmp = sc->builtins; tmp; tmp = tmp->next) {
    if(strcmp(tmp->identifier, identifier) == 0) {
      return tmp;
    }
  }
  if(sc->parent) {
    return scope_get_builtin(sc->parent, identifier);
  }
  return NULL;
}

bool scope_define(scope *sc, gobject identifier, gobject value)
{
  return hash_add(sc->scope_ht, identifier, value);
}
