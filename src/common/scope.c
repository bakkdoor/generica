#include "includes.h"

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
