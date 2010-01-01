#include "common/includes.h"
#include "parser/includes.h"

/* prototype of bison-generated parser function */
int yyparse();

scope *global_scope;

int main(int argc, char **argv)
{
  if ((argc > 1) && (freopen(argv[1], "r", stdin) == NULL))
  {
    fprintf(stderr, "%s: File %s cannot be opened.\n", argv[0], argv[1]);
    exit(1);
  }
  
  global_scope = new_scope(NULL);
  
  yyparse();

  return 0;
}

