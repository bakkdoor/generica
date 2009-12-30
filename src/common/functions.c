#include "includes.h"

gobject* car(gobject *obj)
{
  if(obj) {
    switch(obj->type) {
    case OBJ_CONS:
      return obj->value.ccell.car;
    default:
      warn("Warning: calling 'car' on non-list object!\n");
      return nil;
    }
  }
  return nil;
}

gobject* cdr(gobject *obj)
{
  if(obj) {
    switch(obj->type) {
    case OBJ_CONS:
      return obj->value.ccell.cdr;
    default:
      warn("Warning: calling 'cdr' on non-list object!\n");
      return nil;
    }
  }
  return nil;
}
