#include "includes.h"

gobject eval(gobject obj, scope *sc)
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

gobject eval_identifier(gobject obj, scope *sc)
{
  gobject val = scope_get_ident(sc, obj);
  return val;
}

gobject eval_cons(gobject obj, scope *sc)
{
  gobject ident_val = NULL;
  if(obj->type == OBJ_CONS) {
    /* TODO: fix this! */
    /* return eval(car(obj), sc); */
    switch(car(obj, sc)->type) {
    case OBJ_IDENTIFIER:
      if(obj->quoted == false) {
        /* first, try to get a value */
        if((ident_val = scope_get_ident(sc, car(obj, sc))) != nil) {
          /* return new cons cell object with first item evaluated */
          return cons_obj(ident_val, eval(cdr(obj, sc), sc));
        } else {
          /* then, handle funcall */
          return eval_funcall(car(obj, sc), cdr(obj, sc), sc);
        }
      } else {
        return obj;
      }
      break;
    default:
      return obj;
    }
  } else {
    return nil;
  }
}

gobject eval_funcall(gobject func_ident, gobject args, scope *sc)
{
  builtin *bi;
  gobject func_obj;
  gobject val;

  assert(func_ident);
  assert(args);
  assert(sc);

  bi = scope_get_builtin(sc, func_ident->value.identifier);
  if(bi) {
    if(bi->n_args == 0) {
      val = bi->func(nil, sc);
    } else if(bi->n_args > 1) {
      /* handle multiple-argument built-in function by passing it all
         arguments as a list */
      if(!args->quoted && !bi->special) {
        val = bi->func(eval(args, sc), sc);
      } else {
        val = bi->func(args, sc);
      }
    } else {
      if(!car(args, sc)->quoted && !bi->special) {
        val = bi->func(eval(car(args, sc), sc), sc);
      } else {
        val = bi->func(car(args, sc), sc);
      }
    }

    assert(val);

    return val;
  } else {
    func_obj = scope_get_ident(sc, func_ident);
    /* TODO: to actual eval of function */
    return func_obj;
  }
}
