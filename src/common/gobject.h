#ifndef _GOBJECT_H_
#define _GOBJECT_H_

/**
 * This file contains the definition of the gobject structure, as well
 * as some useful creator-functions for the built-in object types.
 */

/* forward declaration */
typedef struct gobject_t gobject;

/* cons cell consists of car & cdr */
typedef struct cons_cell_t {
  gobject *car;
  gobject *cdr;
} cons_cell;

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
  } value;

  gobject *next;
};

/* global generica object ids */
#define OBJ_NIL			0
#define OBJ_T			1
#define OBJ_INTEGER		10
#define OBJ_DOUBLE		11
#define OBJ_IDENTIFIER		12
#define OBJ_STRING		13
#define OBJ_HASH		14
#define OBJ_CONS		20


/**
 * nil & t objects 
 */
extern gobject *nil;
extern gobject *t;

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
gobject* new_object(int type);

/**
 * Creates a new integer object with a given value.
 * @param val Value for integer object.
 * @return New integer object.
 */
gobject* integer_obj(int val);

/**
 * Creates a new double object with a given value.
 * @param val Value for double object.
 * @return New double object.
 */ 
gobject* double_obj(double val);

/**
 * Creates a new string object with a given value.
 * @param val Value for string object.
 * @return New string object.
 */ 
gobject* string_obj(char *val);

/**
 * Creates a new identifier object with a given value.
 * @param val Value for identifier object.
 * @return New identifier object.
 */ 
gobject* identifier_obj(char *val);

/**
 * Creates a new hash object with a given list of key value pairs.
 * @param val Value for hash object.
 * @return New hash object.
 */ 
gobject* hash_obj(key_val_node *key_val_list);

/**
 * Creates a new cons cell object with a given value.
 * @param car Car value for cons cell object.
 * @param cdr Cdr value for cons cell object.
 * @return New cons cell object.
 */ 
gobject* cons_obj(gobject *car, gobject *cdr);

/**
 * (Pretty)prints a given object to a given file stream.
 * @param obj Object to print to stream.
 * @param stream File stream to print to.
 */ 
void print_object(gobject *obj, FILE *stream);

/**
 * (Pretty)prints a given hash object to a given file stream.
 * @param hash Hash object to print to stream.
 * @param stream File stream to print to.
 */ 
void print_hash_obj(gobject *hash, FILE *stream);

/**
 * Indicates, if two given cons cells are equal.
 * @param a First cons cell.
 * @param b Second cons cell.
 * @return true, if equal, false otherwise.
 */
bool ccell_equals(cons_cell a, cons_cell b);

#endif /* _GOBJECT_H_ */
