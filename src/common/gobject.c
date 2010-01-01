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
  debug("int: %d", val);
  return obj;
}

gobject* double_obj(double val)
{
  gobject *obj = new_object(OBJ_DOUBLE);
  obj->value.doubleval = val;
  debug("double: %f", val);
  return obj;
}

gobject* string_obj(char *val)
{
  gobject *obj = new_object(OBJ_STRING);
  obj->value.string = malloc(sizeof(strlen(val)));
  strcpy(obj->value.string, val);
  debug("string: %s", val);
  return obj;
}

gobject* identifier_obj(char *val)
{
  gobject *obj = new_object(OBJ_IDENTIFIER);
  obj->value.identifier = malloc(sizeof(strlen(val)));
  strcpy(obj->value.identifier, val);
  debug("ident: %s", val);
  return obj;
}

gobject* cons_obj(gobject *car, gobject *cdr)
{
  gobject *obj = new_object(OBJ_CONS);
  obj->value.ccell.car = car;
  obj->value.ccell.cdr = cdr;
  return obj;
}

gobject* hash_obj(key_val_node *key_val_list)
{
  gobject *obj= new_object(OBJ_HASH);
  hashtable *hash = new_hash(key_val_list);

  assert(obj);
  assert(hash);

  obj->value.hash_val = hash;
  debug("new hash");

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
        gobject *curr_cons = obj;
        while(curr_cons != nil) {
          print_object(car(curr_cons), stream);          
          curr_cons = cdr(curr_cons);

          /* skip last space before end of list */
          if(curr_cons != nil) {
            fprintf(stream, " ");
          }
        }
      }
      fprintf(stream, ")");
    }
  }
}

bool ccell_equals(cons_cell *a, cons_cell *b)
{
  if(a && b) {
    if(obj_equals(a->car, b->car) == t
       && obj_equals(a->cdr, b->cdr) == t) {
      return true;
    }
    return false;
  } else {
    return false;
  }
}
