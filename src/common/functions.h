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
gobject car(gobject obj, scope *sc);

/**
 * Returns the cdr (rest of list) of a list object (cons cell), if any.
 * @param obj The cons cell object.
 * @return The cdr (rest of list) of the given cons cell.
 */
gobject cdr(gobject obj, scope *sc);

gobject cons(gobject args, scope *sc);

gobject length(gobject cons, scope *sc);

gobject print_object_stdout(gobject obj, scope *sc);

gobject println_object_stdout(gobject obj, scope *sc);

gobject equal(gobject args, scope *sc);

gobject add(gobject args, scope *sc);

gobject subtract(gobject args, scope *sc);

gobject multiply(gobject args, scope *sc);

gobject divide(gobject args, scope *sc);

gobject modulo(gobject args, scope *sc);

gobject lt(gobject args, scope *sc);

gobject gt(gobject args, scope *sc);

gobject if_f(gobject args, scope *sc);

gobject unless(gobject args, scope *sc);

gobject define(gobject args, scope *sc);

gobject lambda(gobject args, scope *sc);

gobject do_f(gobject args, scope *sc);

gobject special(gobject args, scope *sc);

gobject eval_f(gobject obj, scope *sc);

gobject not(gobject obj, scope *sc);

gobject while_f(gobject args, scope *sc);

#endif /* _COMMON_FUNCTIONS_H_ */
