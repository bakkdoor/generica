#ifndef _GOBJECT_H_
#define _GOBJECT_H_

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


/* 
   functions
*/

extern gobject *nil;
extern gobject *t;

void init_global_objects();

gobject* new_object(int type);

gobject* integer_obj(int val);

gobject* double_obj(double val);

gobject* string_obj(char *val);

gobject* identifier_obj(char *val);

gobject* hash_obj(key_val_node *key_val_list);

gobject* cons_obj(gobject *car, gobject *cdr);

void print_object(gobject *obj, FILE *stream);

void print_hash_obj(gobject *hash, FILE *stream);

bool ccell_equals(cons_cell a, cons_cell b);

#endif /* _GOBJECT_H_ */
