#include "includes.h"

gobject* car(gobject *args)
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

gobject* cdr(gobject *obj)
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

gobject* empty(gobject *obj)
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

gobject* print_object_stdout(gobject *obj)
{
  print_object(eval(obj, global_scope), stdout);
  return nil;
}

gobject* println_object_stdout(gobject *obj)
{
  print_object(eval(obj, global_scope), stdout);
  printf("\n");
  return nil;
}

gobject* equal(gobject *args)
{
  gobject *arg1 = eval(car(args), global_scope);
  gobject *arg2 = eval(car(cdr(args)), global_scope);
  return obj_equals(arg1, arg2);
}

gobject* add(gobject *args)
{
  bool any_double = false;
  double val = 0;
  gobject *arg1, *arg2;

  arg1 = eval(car(args), global_scope);
  arg2 = eval(car(cdr(args)), global_scope);

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

gobject* subtract(gobject *args)
{
  bool any_double = false;
  double val = 0;
  gobject *arg1, *arg2;

  arg1 = eval(car(args), global_scope);
  arg2 = eval(car(cdr(args)), global_scope);

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

gobject* multiply(gobject *args)
{
  bool any_double = false;
  double val = 0;
  gobject *arg1, *arg2;

  arg1 = eval(car(args), global_scope);
  arg2 = eval(car(cdr(args)), global_scope);

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

gobject* divide(gobject *args)
{
  bool isdouble = false;
  bool any_double = false;
  double val = 0;
  gobject *arg1, *arg2;

  arg1 = eval(car(args), global_scope);
  arg2 = eval(car(cdr(args)), global_scope);

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
