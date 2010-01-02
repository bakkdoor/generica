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
  return val;
}

gobject* eval_cons(gobject *obj, scope *sc)
{
  /* TODO: fix this! */
  /* return eval(car(obj), sc); */
  switch(car(obj)->type) {
  case OBJ_IDENTIFIER:
    /* handle funcall */
    if(obj->quoted == false) {
      return eval_funcall(car(obj), cdr(obj), sc);
    } else {
      return obj;
    }
  }
  return nil;
}

gobject* eval_funcall(gobject *func_ident, gobject *args, scope *sc)
{
  builtin *bi;
  gobject *func_obj;
  gobject *val;

  assert(func_ident);
  assert(args);
  assert(sc);

  bi = scope_get_builtin(sc, func_ident->value.identifier);
  if(bi) {
    if(!car(args)->quoted) {
      val = bi->func(eval(car(args), sc));
    } else {
      val = bi->func(car(args));
    }
    assert(val);
    return val;
  } else {
    func_obj = scope_get_ident(sc, func_ident);
    /* TODO: to actual eval of function */
    return func_obj;
  }
}
