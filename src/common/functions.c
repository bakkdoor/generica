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
