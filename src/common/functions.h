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
gobject* car(gobject *obj);

/**
 * Returns the cdr (rest of list) of a list object (cons cell), if any.
 * @param obj The cons cell object.
 * @return The cdr (rest of list) of the given cons cell.
 */
gobject* cdr(gobject *obj);

/**
 * Indicates, if a given object (cons cell) is empty.
 * @param The cons cell object.
 * @return t or nil, depending on if it's empty or not.
 */
gobject* empty(gobject *obj);

gobject* print_object_stdout(gobject *obj);

gobject* println_object_stdout(gobject *obj);

gobject* equal(gobject *args);

gobject* add(gobject *args);

gobject* subtract(gobject *args);

gobject* multiply(gobject *args);

gobject* divide(gobject *args);

#endif /* _COMMON_FUNCTIONS_H_ */
