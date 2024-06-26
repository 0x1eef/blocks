#include <blocks/command.h>
#include <blocks/block.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sysexits.h>

static void print_usage(void);
static int parse_optstr(int, char *const *, const char *);

int
main(int argc, char *argv[])
{
  if (argc < 2)
  {
    print_usage();
    return (EX_USAGE);
  }
  else if (strcmp(argv[1], "get") == 0)
  {
    return (get_command());
  }
  else if (strcmp(argv[1], "emit") == 0)
  {
    return (emit_command());
  }
  else
  {
    switch (parse_optstr(argc, argv, "v"))
    {
    case -2:
      print_usage();
      return (EX_USAGE);
    case -1:
      return (EX_USAGE);
    case 0:
      fprintf(stdout, "%s\n", BLOCKLIST_VERSION);
      return (EX_OK);
    }
  }
}

static int
parse_optstr(int argc, char *const *argv, const char *optstr)
{
  int j, k;
  j = -2;
  while ((k = getopt(argc, argv, optstr)) != -1)
  {
    if (k == '?')
    {
      j = -1;
      break;
    }
    else
    {
      j = 0;
    }
  }
  return j;
}

static void
print_usage(void)
{
  fprintf(stderr,
          "Usage: blocks COMMAND [OPTIONS]\n"
          "\n"
          "Commands:\n"
          "  get  \t      Downloads blocklists\n"
          "  emit \t      Emits pf.conf(5) tables\n");
}
