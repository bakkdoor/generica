#ifndef _COMMON_FUNCTIONS_H_
#define _COMMON_FUNCTIONS_H_

/**
 * This file contains the declarations of the c-implemented standard
 * functions for generica.
 */

/**
 * Returns the car (first element) of a list object (cons cell), if any.
 * @param obj The cons cell object.
 * @return The car (first element) of the given cons cell.
 */
gobject* car(gobject *obj, scope *sc);

/**
 * Returns the cdr (rest of list) of a list object (cons cell), if any.
 * @param obj The cons cell object.
 * @return The cdr (rest of list) of the given cons cell.
 */
gobject* cdr(gobject *obj, scope *sc);

/**
 * Indicates, if a given object (cons cell) is empty.
 * @param The cons cell object.
 * @return t or nil, depending on if it's empty or not.
 */
gobject* empty(gobject *obj, scope *sc);

gobject* print_object_stdout(gobject *obj, scope *sc);

gobject* println_object_stdout(gobject *obj, scope *sc);

gobject* equal(gobject *args, scope *sc);

gobject* add(gobject *args, scope *sc);

gobject* subtract(gobject *args, scope *sc);

gobject* multiply(gobject *args, scope *sc);

gobject* divide(gobject *args, scope *sc);

gobject* if_f(gobject *args, scope *sc);

gobject* unless(gobject *args, scope *sc);

gobject* define(gobject *args, scope *sc);

#endif /* _COMMON_FUNCTIONS_H_ */
