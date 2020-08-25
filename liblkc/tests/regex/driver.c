#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <liblkc/lkc.h>

int main (int argc, const char* argv[])
{
  if (argc != 3)
  {
    fprintf (stderr, "usage: %s <kconfig-file> <regex>\n", argv[0]);
    return 1;
  }

  const char* kf = argv[1];
  const char* re = argv[2];

  conf_parse (kf);

  struct symbol** sym = sym_re_search (re);
  if (sym != NULL)
  {
    size_t i;
    for (i = 0; sym[i] != NULL; i++)
      printf ("%s\n", sym[i]->name);

    free (sym);
  }

  conf_free ();
  return 0;
}
