#include "includes.h"

gobject *nil;
gobject *t;

void init_global_objects()
{
  nil = new_object(OBJ_NIL);
  t = new_object(OBJ_T);
}

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

void print_object(gobject *obj, FILE *stream)
{
  if(obj) {
    switch(obj->type) {
    case OBJ_INTEGER:
      fprintf(stream, "%d", obj->value.intval);
      break;
    case OBJ_DOUBLE:
      fprintf(stream, "%f", obj->value.doubleval);
      break;
    case OBJ_IDENTIFIER:
    case OBJ_STRING:
      fprintf(stream, "%s", obj->value.string);
      break;
    case OBJ_CONS:
      fprintf(stream, "(");
      if(empty(obj) == nil) {
        print_object(obj->value.ccell.car, stream);
        printf(" ");
        print_object(obj->value.ccell.cdr, stream);
      }
      fprintf(stream, ")");
    }
  }
}
