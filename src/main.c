#include "common/includes.h"
#include "parser/includes.h"

/* prototype of bison-generated parser function */
int yyparse();

scope *global_scope;

#define STDLIB_FILES {"stdlib/lists.gna", "stdlib/math.gna"}
#define N_STDLIB_FILES 1

void parse_file(char *filename)
{
  if(freopen(filename, "r", stdin) == NULL)
  {
    fprintf(stderr, "File %s cannot be opened.\n", filename);
    exit(1);
  }
  
  yyparse();
}

int main(int argc, char **argv)
{
  int i;
  char *files[] = STDLIB_FILES;

  global_scope = new_scope(NULL);
  init_global_objects();
  init_global_scope();

  for(i = 0; i < N_STDLIB_FILES; i++) {
    parse_file(files[i]);
  }
  
  if ((argc > 1) && (freopen(argv[1], "r", stdin) == NULL))
  {
    fprintf(stderr, "%s: File %s cannot be opened.\n", argv[0], argv[1]);
    exit(1);
  }
    
  yyparse();

  return 0;
}

