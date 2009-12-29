#include "includes.h"

gobject* new_object(int type)
{
  gobject *obj = (gobject*)malloc(sizeof(struct gobject));
  assert(obj);
  obj->type = type;
  return obj;
}

gobject* integer_obj(int val)
{
  gobject *obj = new_object(OBJ_INTEGER);
  obj->value.intval = val;
  printf("int: %d\n", val);
  return obj;
}

gobject* float_obj(float val)
{
  gobject *obj = new_object(OBJ_FLOAT);
  obj->value.floatval = val;
  printf("float: %f\n", val);
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
