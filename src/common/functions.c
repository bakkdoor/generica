#include "includes.h"

gobject car(gobject args, scope *sc)
{
  if(args) {
    switch(args->type) {
    case OBJ_CONS:
      if(args->value.ccell.car)
        return args->value.ccell.car;
      break;
    default:
      /* warn("Warning: calling 'car' on non-list object!\n"); */
      return nil;
    }
    return nil;
  }
  return nil;
}

gobject cdr(gobject obj, scope *sc)
{
  if(obj) {
    switch(obj->type) {
    case OBJ_CONS:
      if(obj->value.ccell.cdr)
        return obj->value.ccell.cdr;
      break;
    default:
      /* warn("Warning: calling 'cdr' on non-list object!\n"); */
      return nil;
    }
    return nil;
  }
  return nil;
}

gobject cons(gobject args, scope *sc)
{
  gobject arg1 = eval(car(args, sc), sc);
  gobject arg2 = eval(car(cdr(args, sc), sc), sc);
  return cons_obj(arg1, arg2);
}

gobject length(gobject cons, scope *sc)
{
  int length = 0;
  gobject tmp = cons;
  while(tmp != nil && car(tmp, sc) != nil) {
    length += 1;
    tmp = cdr(tmp, sc);
  }

  return integer_obj(length);
}

gobject print_object_stdout(gobject obj, scope *sc)
{
  print_object(eval(obj, sc), sc, stdout);
  return nil;
}

gobject println_object_stdout(gobject obj, scope *sc)
{
  print_object(eval(obj, sc), sc, stdout);
  printf("\n");
  return nil;
}

gobject equal(gobject args, scope *sc)
{
  gobject arg1 = eval(car(args, sc), sc);
  gobject arg2 = eval(car(cdr(args, sc), sc), sc);
  return obj_equals(arg1, arg2);
}

gobject add(gobject args, scope *sc)
{
  bool any_double = false;
  double val = 0;
  gobject arg1, arg2;

  arg1 = eval(car(args, sc), sc);
  arg2 = eval(car(cdr(args, sc), sc), sc);

  if(arg1->type == OBJ_DOUBLE) {
    val += arg1->value.doubleval;
    any_double = true;
  } else {
    val += arg1->value.intval;
  }
  
  if(arg2->type == OBJ_DOUBLE) {
    val += arg2->value.doubleval;
    any_double = true;
  } else {
    val += arg2->value.intval;
  }

  if(!any_double) {
    return integer_obj((int) val);
  } else {
    return double_obj(val);
  }
}

gobject subtract(gobject args, scope *sc)
{
  bool any_double = false;
  double val = 0;
  gobject arg1, arg2;

  arg1 = eval(car(args, sc), sc);
  arg2 = eval(car(cdr(args, sc), sc), sc);

  if(arg1->type == OBJ_DOUBLE) {
    val = arg1->value.doubleval;
    any_double = true;
  } else {
    val = arg1->value.intval;
  }
  
  if(arg2->type == OBJ_DOUBLE) {
    val -= arg2->value.doubleval;
    any_double = true;
  } else {
    val -= arg2->value.intval;
  }

  if(!any_double) {
    return integer_obj((int) val);
  } else {
    return double_obj(val);
  }
}

gobject multiply(gobject args, scope *sc)
{
  bool any_double = false;
  double val = 0;
  gobject arg1, arg2;

  arg1 = eval(car(args, sc), sc);
  arg2 = eval(car(cdr(args, sc), sc), sc);

  if(arg1->type == OBJ_DOUBLE) {
    val = arg1->value.doubleval;
    any_double = true;
  } else {
    val = arg1->value.intval;
  }
  
  if(arg2->type == OBJ_DOUBLE) {
    val *= arg2->value.doubleval;
    any_double = true;
  } else {
    val *= arg2->value.intval;
  }

  if(!any_double) {
    return integer_obj((int) val);
  } else {
    return double_obj(val);
  }
}

gobject divide(gobject args, scope *sc)
{
  bool isdouble = false;
  bool any_double = false;
  double val = 0;
  gobject arg1, arg2;

  arg1 = eval(car(args, sc), sc);
  arg2 = eval(car(cdr(args, sc), sc), sc);

  if(arg1->type == OBJ_DOUBLE) {
    val = arg1->value.doubleval;
    any_double = true;
  } else {
    val = arg1->value.intval;
  }
  
  if(arg2->type == OBJ_DOUBLE) {
    val /= arg2->value.doubleval;
    any_double = true;
  } else {
    val /= arg2->value.intval;
  }

  isdouble = (val - ((int)val)) != 0.0;

  if(!any_double && !isdouble) {
    return integer_obj((int) val);
  } else {
    return double_obj(val);
  }
}

gobject modulo(gobject args, scope *sc)
{
  gobject n1 = car(args, sc);
  gobject n2 = car(cdr(args, sc), sc);
  
  double val1 = NUMVAL(n1);
  double val2 = NUMVAL(n2);

  return integer_obj((int)val1 % (int)val2);
}

gobject lt(gobject args, scope *sc)
{
  gobject n1 = car(args, sc);
  gobject n2 = car(cdr(args, sc), sc);

  double val1, val2;

  if(IS_NUM(n1) && IS_NUM(n2)) {

    if(n1->type == OBJ_INTEGER) {
      val1 = n1->value.intval;
    } else {
      val1 = n1->value.doubleval;
    }

    if(n2->type == OBJ_INTEGER) {
      val2 = n2->value.intval;
    } else {
      val2 = n2->value.doubleval;
    }

    if(val1 < val2) {
      return t;
    } else {
      return nil;
    }

  } else {
    return nil;
  }
}

gobject gt(gobject args, scope *sc)
{
  gobject n1 = car(args, sc);
  gobject n2 = car(cdr(args, sc), sc);

  double val1, val2;

  if(IS_NUM(n1) && IS_NUM(n2)) {

    if(n1->type == OBJ_INTEGER) {
      val1 = n1->value.intval;
    } else {
      val1 = n1->value.doubleval;
    }

    if(n2->type == OBJ_INTEGER) {
      val2 = n2->value.intval;
    } else {
      val2 = n2->value.doubleval;
    }

    if(val1 > val2) {
      return t;
    } else {
      return nil;
    }

  } else {
    return nil;
  }
}

gobject if_f(gobject args, scope *sc)
{
  gobject cond = eval(car(args, sc), sc);

  if(cond != nil) {
    return eval(car(cdr(args, sc), sc), sc);  
  } else {
    return eval(car(cdr(cdr(args, sc), sc), sc), sc);
  }
}

gobject unless(gobject args, scope *sc)
{
  gobject cond = eval(car(args, sc), sc);

  if(cond == nil) {
    return eval(car(cdr(args, sc), sc), sc);  
  } else {
    return eval(car(cdr(cdr(args, sc), sc), sc), sc);
  }
}

gobject define(gobject args, scope *sc)
{
  gobject ident = car(args, sc);
  gobject value = eval(car(cdr(args, sc), sc), sc);

  scope_define(sc, ident, value);

  return value;
}

gobject lambda(gobject args, scope *sc)
{
  gobject arglist = car(args, sc);
  gobject body_expr = car(cdr(args, sc), sc);

  assert(arglist->type == OBJ_CONS);
  assert(body_expr->type == OBJ_CONS);

  return lambda_obj(arglist, body_expr);
}

gobject do_f(gobject args, scope *sc)
{
  gobject forms = args;
  gobject retval;
  while(forms != nil) {
    retval = eval(car(forms, sc), sc);
    forms = cdr(forms, sc);
  }
  return retval;
}

gobject special(gobject args, scope *sc)
{
  gobject arglist = car(args, sc);
  gobject forms = car(cdr(args, sc), sc);
  
  return lambda_obj(arglist, forms);
}

gobject eval_f(gobject obj, scope *sc)
{
  gobject retval;
  bool was_quoted = false;

  /* remove quotation */
  if(obj->quoted) {
    obj->quoted = false;
    was_quoted = true;
  }

  retval = eval(obj, sc);

  /* restore quotation */
  if(was_quoted) {
    obj->quoted = true;
  }

  return retval;
}

gobject not(gobject obj, scope *sc)
{
  if(obj == nil) {
    return t;
  } else {
    return nil;
  }
}
