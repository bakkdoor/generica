#ifndef _EVAL_H_
#define _EVAL_H_

/**
 * Evaluate a obj
 */
gobject eval(gobject obj, scope *sc);
gobject eval_identifier(gobject obj, scope *sc);
gobject eval_cons(gobject obj, scope *sc);
gobject eval_funcall(gobject func_ident, gobject args, scope *sc);
gobject eval_lambda_call(gobject lamdba, gobject args, scope *sc);

#endif /* _EVAL_H_ */
