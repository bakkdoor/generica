#include "includes.h"

void init_global_scope()
{
  /* init to NULL */
  global_scope->builtins = NULL;

  /* scope_define_builtin("define", define); */
  scope_define_builtin(global_scope, "car", car);
  scope_define_builtin(global_scope, "cdr", cdr);
  scope_define_builtin(global_scope, "empty", empty);
  scope_define_builtin(global_scope, "print", print_object_stdout);
  scope_define_builtin(global_scope, "println", println_object_stdout);
}

void scope_define_builtin(scope *sc, char *ident, gobject* (*func)(gobject* args))
{
  builtin *new_b = malloc(sizeof(builtin));
  builtin *tmp;

  assert(new_b);
  assert(ident);
  assert(func);

  new_b->identifier = ident;
  new_b->func = func;

  tmp = sc->builtins;
  new_b->next = tmp;
  sc->builtins = new_b;
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

gobject* scope_get_ident(scope *sc, gobject *identifier)
{
  hash_entry *entry;
  if((entry = hash_lookup(sc->scope_ht, identifier))) {
    if(entry->value)
      return entry->value;
    return nil;
  } else {
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
  return NULL;
}
