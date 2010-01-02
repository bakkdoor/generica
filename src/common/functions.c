#include "includes.h"

gobject* car(gobject *args, scope *sc)
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

gobject* cdr(gobject *obj, scope *sc)
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

gobject* empty(gobject *obj, scope *sc)
{
  if(obj && obj->type == OBJ_CONS) {
    if(!obj->value.ccell.car || obj->value.ccell.car == nil) {
      return t;
    } else {
      return nil;
    }
  } else {
    warn("Calling 'empty' on non-list object!");
    return nil;
  }
}

gobject* print_object_stdout(gobject *obj, scope *sc)
{
  print_object(eval(obj, sc), sc, stdout);
  return nil;
}

gobject* println_object_stdout(gobject *obj, scope *sc)
{
  print_object(eval(obj, sc), sc, stdout);
  printf("\n");
  return nil;
}

gobject* equal(gobject *args, scope *sc)
{
  gobject *arg1 = eval(car(args, sc), sc);
  gobject *arg2 = eval(car(cdr(args, sc), sc), sc);
  return obj_equals(arg1, arg2);
}

gobject* add(gobject *args, scope *sc)
{
  bool any_double = false;
  double val = 0;
  gobject *arg1, *arg2;

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

gobject* subtract(gobject *args, scope *sc)
{
  bool any_double = false;
  double val = 0;
  gobject *arg1, *arg2;

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

gobject* multiply(gobject *args, scope *sc)
{
  bool any_double = false;
  double val = 0;
  gobject *arg1, *arg2;

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

gobject* divide(gobject *args, scope *sc)
{
  bool isdouble = false;
  bool any_double = false;
  double val = 0;
  gobject *arg1, *arg2;

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
