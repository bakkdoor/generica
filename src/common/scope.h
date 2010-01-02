#ifndef _SCOPE_H_
#define _SCOPE_H_

/**
 * This file contains the definition of the scope structure and its
 * functions. A scope defines an environment in which identifiers &
 * functions are stored for evaluation purposes.
 */

typedef struct scope_s scope;
typedef struct builtin_s builtin;

struct builtin_s {
  char *identifier;
  gobject* (*func)(gobject* args, scope *sc);
  unsigned int n_args;
  bool special;
  builtin *next;
};

/**
 * A scope contains a hashtable, in which all identifiers etc. are
 * stored, as well as a potential reference to its parent scope.
 *
 * For example, a function scope has a reference to a parent scope
 * (the scope, in which the function is defined).
 */
struct scope_s {
  builtin *builtins;
  hashtable *scope_ht;
  scope *parent;
};

/**
 * Global scope defined in src/main.c
 */
extern scope *global_scope;

/**
 * Sets up the global scope with predefined functions etc.
 */
void init_global_scope();

void scope_define_builtin(scope *sc, char *ident, gobject* (*func)(gobject* args, scope *sc), unsigned int n_args);

void scope_define_builtin_special(scope *sc, char *ident, gobject* (*func)(gobject* args, scope *sc), unsigned int n_args);

/**
 * Creates a new scope with a given parent scope.
 * @param parent The parent scope of the new scope. Can be NULL, if no
 * parent exists.
 * @return The newly created scope.
 */
scope* new_scope(scope *parent);

/**
 * Looks for an identifier and returns the corresponding object, if in
 * scope (or in parent scope, if a parent is set).
 * @param sc Scope in which to look for identifier.
 * @param identifier The object, that is the identifier.
 * @return The (value) object represented by the identifier within the
 * scope
 */
gobject* scope_get_ident(scope *sc, gobject *identifier);

builtin* scope_get_builtin(scope *sc, char *identifier);

bool scope_define(scope *sc, gobject *identifier, gobject *value);

#endif /* _SCOPE_H_ */
