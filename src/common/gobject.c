#include "includes.h"

gobject* new_object(int type)
{
  gobject *obj = (gobject*)malloc(sizeof(gobject));
  assert(obj);
  obj->type = type;
  obj->quoted = false; /* default to false */
  return obj;
}

gobject* integer_obj(int val)
{
  gobject *obj = new_object(OBJ_INTEGER);
  obj->value.intval = val;
  printf("int: %d\n", val);
  return obj;
}

gobject* double_obj(double val)
{
  gobject *obj = new_object(OBJ_DOUBLE);
  obj->value.doubleval = val;
  printf("double: %f\n", val);
  return obj;
}

gobject* string_obj(char *val)
{
  gobject *obj = new_object(OBJ_STRING);
  obj->value.string = malloc(sizeof(strlen(val)));
  strcpy(obj->value.string, val);
  printf("string: %s\n", val);
  return obj;
}

gobject* identifier_obj(char *val)
{
  gobject *obj = new_object(OBJ_IDENTIFIER);
  obj->value.identifier = malloc(sizeof(strlen(val)));
  strcpy(obj->value.identifier, val);
  printf("ident: %s\n", val);
  return obj;
}

gobject* cons_obj(gobject *car, gobject *cdr)
{
  gobject *obj = new_object(OBJ_CONS);
  obj->value.ccell.car = car;
  obj->value.ccell.cdr = cdr;
  printf("ccell!\n");
  return obj;
}
