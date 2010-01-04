#ifndef _GOBJECT_H_
#define _GOBJECT_H_

/**
 * This file contains the definition of the gobject structure, as well
 * as some useful creator-functions for the built-in object types.
 */

/* forward declaration */
typedef struct gobject_t* gobject;
struct scope_s;

/* cons cell consists of car & cdr */
typedef struct cons_cell_t {
  gobject car;
  gobject cdr;
} cons_cell;

typedef struct lambda_t {
  gobject args;
  gobject body;
} lambda_expression;

struct gobject_t {
  int type;
  bool quoted;

  union {
    /* identifier value */
    char *identifier;
    
    /* string value */
    char *string;
    
    /* int value */
    int intval;

    /* double value */
    double doubleval;

    hashtable *hashval;
    
    /* cons cell value */
    cons_cell ccell;

    /* lambda value (lambda expression as cons cell) */
    lambda_expression lambdaval;
  } value;

  gobject next;
};

/* global generica object ids */
#define OBJ_NIL			0
#define OBJ_T			1
#define OBJ_INTEGER		10
#define OBJ_DOUBLE		11
#define OBJ_IDENTIFIER		12
#define OBJ_STRING		13
#define OBJ_HASH		14
#define OBJ_LAMBDA		15
#define OBJ_CONS		20

/**
 * some helper macros
 */

#define IS_NIL(obj) \
  obj->type == OBJ_NIL

#define IS_T(obj) \
  obj->type == OBJ_T

#define IS_INT(obj) \
  obj->type == OBJ_INTEGER

#define IS_DOUBLE(obj) \
  obj->type == OBJ_DOUBLE

#define IS_NUM(obj) \
  (IS_INT(obj) || IS_DOUBLE(obj))

#define IS_IDENT(obj) \
  obj->type == OBJ_IDENTIFIER

#define IS_STRING(obj) \
  obj->type == OBJ_STRING

#define IS_HASH(obj) \
  obj->type == OBJ_HASH

#define IS_LAMBDA(obj) \
  obj->type == OBJ_LAMBDA

#define IS_CONS(obj) \
  obj->type == OBJ_CONS

#define NUMVAL(obj) \
  IS_NUM(obj) ? (IS_INT(obj) ? obj->value.intval : obj->value.doubleval) : 0

/**
 * nil & t objects 
 */
extern gobject nil;
extern gobject t;

/** 
 * functions
 */

/**
 * Initializes the global objects (e.g. t & nil).
 */
void init_global_objects();

/**
 * Creates (allocates) a new object of a given type.
 * @param type The type (see below) of the new object.
 * @return The newly created object.
 */
gobject new_object(int type);

/**
 * Creates a new integer object with a given value.
 * @param val Value for integer object.
 * @return New integer object.
 */
gobject integer_obj(int val);

/**
 * Creates a new double object with a given value.
 * @param val Value for double object.
 * @return New double object.
 */ 
gobject double_obj(double val);

/**
 * Creates a new string object with a given value.
 * @param val Value for string object.
 * @return New string object.
 */ 
gobject string_obj(char *val);

/**
 * Creates a new identifier object with a given value.
 * @param val Value for identifier object.
 * @return New identifier object.
 */ 
gobject identifier_obj(char *val);

/**
 * Creates a new hash object with a given list of key value pairs.
 * @param val Value for hash object.
 * @return New hash object.
 */ 
gobject hash_obj(key_val_node *key_val_list);

/**
 * Creates a new cons cell object with a given value.
 * @param car Car value for cons cell object.
 * @param cdr Cdr value for cons cell object.
 * @return New cons cell object.
 */ 
gobject cons_obj(gobject car, gobject cdr);

/**
 * Creates a lambda_expression object with a given argument list & body.
 * @param args Argument list cons cell.
 * @param body Lambda body cons cell.
 * @return New lambda_expression object.
 */ 
gobject lambda_obj(gobject args, gobject body);

/**
 * (Pretty)prints a given object to a given file stream.
 * @param obj Object to print to stream.
 * @param stream File stream to print to.
 */ 
void print_object(gobject obj, struct scope_s *sc, FILE *stream);

/**
 * (Pretty)prints a given hash object to a given file stream.
 * @param hash Hash object to print to stream.
 * @param stream File stream to print to.
 */ 
void print_hash_obj(gobject hash, struct scope_s *sc, FILE *stream);

/**
 * Indicates, if two given cons cells are equal.
 * @param a First cons cell.
 * @param b Second cons cell.
 * @return true, if equal, false otherwise.
 */
bool ccell_equals(cons_cell a, cons_cell b);

/**
 * Indicates, two given objects are equal in value.
 * @param a First object.
 * @param b Second object.
 * @return t if equal, nil otherwise.
 */
gobject obj_equals(gobject a, gobject b);

#endif /* _GOBJECT_H_ */
