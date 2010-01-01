#include "includes.h"

gobject* car(gobject *obj)
{
  if(obj) {
    switch(obj->type) {
    case OBJ_CONS:
      if(obj->value.ccell.car)
        return obj->value.ccell.car;
      break;
    default:
      warn("Warning: calling 'car' on non-list object!\n");
      return nil;
    }
    return nil;
  }
  return nil;
}

gobject* cdr(gobject *obj)
{
  if(obj) {
    switch(obj->type) {
    case OBJ_CONS:
      if(obj->value.ccell.cdr)
        return obj->value.ccell.cdr;
      break;
    default:
      warn("Warning: calling 'cdr' on non-list object!\n");
      return nil;
    }
    return nil;
  }
  return nil;
}

gobject* empty(gobject *obj)
{
  if(obj && obj->type == OBJ_CONS) {
    if(!obj->value.ccell.car) {
      return t;
    } else {
      return nil;
    }
  } else {
    warn("Calling 'empty' on non-list object!\n");
    return nil;
  }
}

gobject* obj_equals(gobject *a, gobject *b)
{
  assert(a);
  assert(b);

  if(a->type != b->type) {
    return nil;
  }

  switch(a->type) {
  case OBJ_NIL:
    return t;

  case OBJ_T:
    return t;

  case OBJ_INTEGER:
    return (a->value.intval == b->value.intval) ? t : nil;

  case OBJ_DOUBLE:
    return (a->value.doubleval == b->value.doubleval) ? t : nil;

  case OBJ_IDENTIFIER:
    if(strcmp(a->value.identifier, b->value.identifier) == 0)
      return t;
    break;

  case OBJ_STRING:
    if(strcmp(a->value.string, b->value.string) == 0)
      return t;
    break;

  case OBJ_HASH:
    if(hash_equals(a->value.hashval, b->value.hashval))
      return t;
    break;

  case OBJ_CONS:
    if(ccell_equals(a->value.ccell, b->value.ccell))
      return t;
    break;

  default:
    return nil;
  }
  return nil;
}
