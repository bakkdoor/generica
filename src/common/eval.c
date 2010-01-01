#include "includes.h"

gobject* eval(gobject *obj, scope *sc)
{
  assert(obj);

  switch(obj->type) {
  case OBJ_NIL:
  case OBJ_T:
  case OBJ_INTEGER:
  case OBJ_DOUBLE:
  case OBJ_STRING:
  case OBJ_HASH:
    return obj;
  case OBJ_IDENTIFIER:
    return eval_identifier(obj, sc);
  case OBJ_CONS:
    return eval_cons(obj, sc);
  default:
    return nil;
  }
}

gobject* eval_identifier(gobject *obj, scope *sc)
{
  gobject *val = scope_get_ident(sc, obj);
  if(val) {
    printf("found val in scope:");
    print_object(val, stdout);
    printf("\n");
  }
}

gobject* eval_cons(gobject *obj, scope *sc)
{
  /* TODO: fix this! */
  return eval(car(obj), sc);
}
