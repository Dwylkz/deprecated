#include <comm.h>
#include <lexer.h>

static char* imem;

static void parse_args(int argc, char** argv)
{
  static char* usage = "usage: %s "
      "[-h] "
      "<input_file>\n";

  int ret = -1;
  for (int o; (o = getopt(argc, argv, "h")) != -1; )
    switch (o) {
      case 'h': {
        ret = 0;
        goto err_0;
      }
      default: {
        goto err_0;
      }
    }

  if (optind == argc)
    TDSL_GOTO(err_0, "missing input file");

  if ((imem = tdsl_loadfile(argv[optind])) == NULL)
    TDSL_GOTO(err_0, "load file failed");
  return ;
err_0:
  fprintf(stderr, usage, argv[0]);
  exit(ret);
}

int main(int argc, char** argv)
{
  parse_args(argc, argv);

  tokens_t* tokens = tokens_new(imem);
  free(imem);

  tokens_free(tokens);
  return 0;
}
