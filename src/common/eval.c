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
  case OBJ_LAMBDA:
    return obj;
  case OBJ_IDENTIFIER:
    return eval_identifier(obj, sc);
  case OBJ_CONS:
    return eval_cons(obj, sc, false);
  default:
    return nil;
  }
}

gobject eval_identifier(gobject obj, scope *sc)
{
  gobject val = scope_get_ident(sc, obj);
  return val;
}

gobject eval_cons(gobject obj, scope *sc, bool is_first)
{
  gobject ident_val = NULL;
  gobject inline_lambda = NULL;

  if(obj->type == OBJ_CONS) {
    /* TODO: fix this! */
    /* return eval(car(obj), sc); */
    switch(car(obj, sc)->type) {
    case OBJ_IDENTIFIER:
      if(obj->quoted == false) {
        /* first, try to get a value */
        if((ident_val = scope_get_ident(sc, car(obj, sc))) != nil) {
          if(ident_val->type != OBJ_LAMBDA) {
            /* return new cons cell object with first item evaluated */
            return cons_obj(ident_val, eval(cdr(obj, sc), sc));
          } else {
            /* it's a funcall (lambda call) ! */
            return eval_lambda_call(ident_val, cdr(obj, sc), sc);
          }
        } else {
          /* then, handle funcall */
          return eval_funcall(car(obj, sc), cdr(obj, sc), sc);
        }
      } else {
        return obj;
      }
      break;
    case OBJ_CONS:
      if(is_first) {
        inline_lambda = eval(car(obj, sc), sc);
        /* check, if we have an inline-defined lambda object here */
        if(inline_lambda && IS_LAMBDA(inline_lambda)) {
          return eval_lambda_call(inline_lambda, cdr(obj, sc), sc);
        }
      }
      return obj;
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
  
  if(func_ident->type == OBJ_LAMBDA)
    return eval_lambda_call(func_ident, args, sc);

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
    warn("probably couldn't find function: %s", func_ident->value.identifier);
    /* TODO: to actual eval of function */
    return func_obj;
  }
}

gobject eval_lambda_call(gobject lambda, gobject args, scope *sc)
{
  gobject formal_arg;
  gobject arg;
  gobject retval;
  scope *call_scope;
  int arg_diff;
  int i;
  gobject remaining_args;
  gobject normal_args;

  int n_args = length(args, sc)->value.intval;
  int n_formal_args = length(lambda->value.lambdaval.args, sc)->value.intval;

  if(n_args != n_formal_args && !IS_SPECIAL_LAMBDA(lambda)){
    warn("Formal arg count is wrong: %d instead of %d", n_args, n_formal_args);
    return nil;
  }

  call_scope = new_scope(sc);

  if(IS_SPECIAL_LAMBDA(lambda)) {
    /* create cons cell with all remaining args in one */
    arg_diff = n_args - n_formal_args;
    remaining_args = args;
    normal_args = NULL;
    if(arg_diff >= 0) {
      for(i = 0; i < arg_diff; i++) {
        normal_args = cons_obj(car(remaining_args, sc), normal_args);
        remaining_args = cdr(remaining_args, sc);
      }
      remaining_args = cons_obj(remaining_args, nil);
      args = cons_obj(car(normal_args, sc), remaining_args);
    } else { 
      /* OK, something's wrong! */
      warn("Less arguments given (%d) than at least required (%d) for special lambda!", n_args, n_formal_args);
      return nil;
    }
  }

  /* set args in call_scope */
  formal_arg = lambda->value.lambdaval.args;
  arg = args;
  while(formal_arg != nil && arg != nil) {
    scope_define(call_scope, car(formal_arg, sc), eval(car(arg, call_scope), call_scope));
    /* move on in lists */
    formal_arg = cdr(formal_arg, sc);
    arg = cdr(arg, sc);
  }

  retval = eval(lambda->value.lambdaval.body, call_scope);
  free(call_scope);
  return retval;
}
