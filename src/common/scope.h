#ifndef _SCOPE_H_
#define _SCOPE_H_

/**
 * This file contains the definition of the scope structure and its
 * functions. A scope defines an environment in which identifiers &
 * functions are stored for evaluation purposes.
 */

typedef struct scope_s scope;

/**
 * A scope contains a hashtable, in which all identifiers etc. are
 * stored, as well as a potential reference to its parent scope.
 *
 * For example, a function scope has a reference to a parent scope
 * (the scope, in which the function is defined).
 */
struct scope_s {
  hashtable *scope_ht;
  scope *parent;
};

scope* new_scope(scope *parent);
gobject* scope_get_ident(scope *sc, gobject *identifier);

#endif /* _SCOPE_H_ */
