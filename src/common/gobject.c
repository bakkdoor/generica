#include "includes.h"

gobject nil;
gobject t;

void init_global_objects()
{
  nil = new_object(OBJ_NIL);
  t = new_object(OBJ_T);
}

gobject new_object(int type)
{
  gobject obj = (gobject)malloc(sizeof(gobject));
  assert(obj);
  obj->type = type;
  obj->quoted = false; /* default to false */
  return obj;
}

gobject integer_obj(int val)
{
  gobject obj = new_object(OBJ_INTEGER);
  obj->value.intval = val;
  debug("int: %d", val);
  return obj;
}

gobject double_obj(double val)
{
  gobject obj = new_object(OBJ_DOUBLE);
  obj->value.doubleval = val;
  debug("double: %f", val);
  return obj;
}

gobject string_obj(char *val)
{
  gobject obj = new_object(OBJ_STRING);
  obj->value.string = malloc(sizeof(strlen(val)));
  strcpy(obj->value.string, val);
  debug("string: %s", val);
  return obj;
}

gobject identifier_obj(char *val)
{
  gobject obj = new_object(OBJ_IDENTIFIER);
  obj->value.identifier = malloc(sizeof(strlen(val)));
  strcpy(obj->value.identifier, val);
  debug("ident: %s", val);
  return obj;
}

gobject cons_obj(gobject car, gobject cdr)
{
  gobject obj = new_object(OBJ_CONS);
  obj->value.ccell.car = car;
  obj->value.ccell.cdr = cdr;
  return obj;
}

gobject hash_obj(key_val_node *key_val_list)
{
  gobject obj= new_object(OBJ_HASH);
  hashtable *hash = new_hash(key_val_list);

  assert(obj);
  assert(hash);

  obj->value.hashval = hash;
  debug("new hash");

  return obj;
}

gobject lambda_obj(gobject args, gobject body)
{
  gobject lambda = new_object(OBJ_LAMBDA);

  assert(lambda);
  
  lambda->value.lambdaval.args = args;
  lambda->value.lambdaval.body = body;

  debug("new lambda expression");

  return lambda;
}

void print_object(gobject obj, scope *sc, FILE *stream)
{
  if(obj) {
    switch(obj->type) {
    case OBJ_NIL:
      fprintf(stream, "nil");
      break;
    case OBJ_T:
      fprintf(stream, "t");
      break;
    case OBJ_INTEGER:
      fprintf(stream, "%d", obj->value.intval);
      break;
    case OBJ_DOUBLE:
      fprintf(stream, "%f", obj->value.doubleval);
      break;
    case OBJ_IDENTIFIER:
      fprintf(stream, "%s", obj->value.identifier);
      break;
    case OBJ_STRING:
      fprintf(stream, "%s", obj->value.string);
      break;
    case OBJ_HASH:
      print_hash_obj(obj, sc, stream);
      break;
    case OBJ_CONS:
      fprintf(stream, "(");
      if(empty(obj, sc) == nil) {
        gobject curr_cons = obj;
        while(curr_cons != nil) {
          print_object(car(curr_cons, sc), sc, stream);          
          curr_cons = cdr(curr_cons, sc);

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

void print_hash_obj(gobject hash, scope *sc, FILE *stream)
{
  hash_entry *tmp;
  unsigned int i;

  if(hash && stream && hash->type == OBJ_HASH) {
    fprintf(stream, "{");

    for(i = 0; i < HASH_SIZE; i++) {
      if(hash->value.hashval->entries[i]) {
        for(tmp = hash->value.hashval->entries[i]; tmp; tmp = tmp->next) {
          if(tmp->key && tmp->value) {
            print_object(tmp->key, sc, stream);
            fprintf(stream, " => ");
            print_object(tmp->value, sc, stream);
          }
        }
      }
    }

    fprintf(stream, "}");
  }
}

bool ccell_equals(cons_cell a, cons_cell b)
{
  if(obj_equals(a.car, b.car) == t
     && obj_equals(a.cdr, b.cdr) == t) {
    return true;
  }
  return false;
}

gobject obj_equals(gobject a, gobject b)
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
