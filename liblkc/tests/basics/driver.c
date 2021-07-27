#include <liblkc/lkc.h>
#include <liblkc/version.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static int
compare_symbols (const void* x, const void* y)
{
  return strcmp ((*(const struct symbol**)x)->name,
                 (*(const struct symbol**)y)->name);
}

int main (int argc, const char* argv[])
{
  if (argc < 3 && argc > 4)
  {
    fprintf (stderr,
             "usage: %s <kconfig-file> <config-file> [<iterations>]\n",
             argv[0]);
    return 1;
  }

  const char* kf = argv[1];
  const char* cf = argv[2];
  unsigned long itn = (argc == 4 ? strtoul (argv[3], NULL, 10) : 1);

  unsigned long it;
  for (it = 0; it != itn; ++it)
  {
    conf_parse (kf);

    if (conf_read (cf) != 0)
    {
      fprintf (stderr, "unable to load configuration values from %s\n", cf);
      return 1;
    }

    // Get a sorted list of symbols.
    //
    size_t n = 0;
    const struct symbol** symbols = NULL;
    {
      size_t i;
      const struct symbol* s;
      for_all_symbols (i, s)
      {
        // See kconfig-dump for semantics of these tests.
        //
        if (s->name == NULL      ||
            s->type == S_UNKNOWN ||
            (s->flags & SYMBOL_CONST) != 0)
          continue;

        n++;
      }

      if (n == 0)
        continue;

      symbols = calloc (n, sizeof (*symbols));
      if (symbols == NULL)
      {
        fprintf (stderr, "unable to allocate memory to sort symbols\n");
        return 1;
      }

      size_t j = 0;
      for_all_symbols (i, s)
      {
        // See kconfig-dump for semantics of these tests.
        //
        if (s->name == NULL      ||
            s->type == S_UNKNOWN ||
            (s->flags & SYMBOL_CONST) != 0)
          continue;

        symbols[j++] = s;
      }

      qsort ((void*)symbols, n, sizeof(*symbols), compare_symbols);
    }

    size_t i;
    for (i = 0; i != n; i++)
    {
      const struct symbol* s = symbols[i];

      assert (s->flags & SYMBOL_VALID);
      const struct symbol_value* c = &s->curr;

      const char* t = NULL;
      switch (s->type)
      {
      case S_UNKNOWN:  t = "unknown";  break;
      case S_BOOLEAN:  t = "bool";     break;
      case S_TRISTATE: t = "tristate"; break;
      case S_INT:      t = "int";      break;
      case S_HEX:      t = "hex";      break;
      case S_STRING:   t = "string";   break;
      }

      const char* v = NULL;
      switch (s->type)
      {
      case S_UNKNOWN:
        {
          v = "<unknown>";
          break;
        }
      case S_BOOLEAN:
        {
          v = (c->tri == no ? "n" : "y");
          break;
        }
      case S_TRISTATE:
        {
          v = (c->tri == no ? "n" : c->tri == mod ? "m" : "y");
          break;
        }
      case S_INT:
      case S_HEX:
      case S_STRING:
        {
          // These are all represented as strings.
          //
          // Note that in case of S_STRING it seems the string may contain
          // escapes but what we get is unescaped.
          //
          // The NULL semantics is in effect when the option is disabled
          // because one of its dependencies is not satisfied (note that this
          // does not apply to bool and tristate because they are set to false
          // if disabled).
          //
          int null = (!(s->flags & SYMBOL_WRITE) &&
                      !(s->flags & SYMBOL_NO_WRITE));

          v = (null ? "<null>" : (const char*)c->val);
          break;
        }
      }

      fprintf (stdout, "%s %s %s\n", s->name, t, v);
    }

    free ((void*)symbols);
    conf_free ();
  }

  return 0;
}
