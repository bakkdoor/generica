#ifndef _GOBJECT_H_
#define _GOBJECT_H_

/* forward declaration */
typedef struct gobject gobject;

/* cons cell consists of car & cdr */
typedef struct cons_cell {
  struct gobject *car;
  struct gobject *cdr;
} cons_cell;

struct gobject {
  int type;

  union {
    /* identifier value */
    char *identifier;
    
    /* string value */
    char *string;
    
    /* int value */
    int intval;

    /* float value */
    float floatval;
    
    /* cons cell value */
    cons_cell ccell;
  } value;

  gobject *next;
};

/* global generica object ids */
#define OBJ_NIL			0
#define OBJ_T			1
#define OBJ_INTEGER		10
#define OBJ_FLOAT		11
#define OBJ_IDENTIFIER		12
#define OBJ_STRING		13
#define OBJ_CONS		20


/* 
   functions
*/

gobject* new_object(int type);

gobject* integer_obj(int val);

gobject* float_obj(float val);

gobject* string_obj(char *val);

gobject* identifier_obj(char *val);

#endif /* _GOBJECT_H_ */
