#include "lib/Dlex.h"

static const char* usage = "usage: %s "
  "[-o <output_dir>] "
  "[-s] "
  "[-t <test_file>] "
  "<input_file>\n";

static int do_show_dfa = 0;

static int do_test = 0;
static char test_str[BUFSIZ];

static char ifile_str[BUFSIZ];
static char odir_str[BUFSIZ];

static int ParseOpt(int argc, char** argv)
{
  odir_str[0] = '\0';
	for (int o; (o = getopt(argc, argv, "o:st:")) != -1; ) {
		switch (o) {
      case 'o': {
        if (!optarg) return -1;
        strcpy(odir_str, optarg);
        break;
      }
      case 's': {
        do_show_dfa = 1;
        break;
      }
      case 't': {
        do_test = 1;
        if (!optarg) return -1;
        strcpy(test_str, optarg);
        break;
      }
			default:
				return -1;
		}
	}
	if (optind == argc) {
		return -1;
	}
  strcpy(ifile_str, argv[optind]);
  if (odir_str[0] == '\0')
    strcpy(odir_str, dirname(argv[optind]));
	return 0;
}

int main(int argc, char** argv)
{
	if (ParseOpt(argc, argv) < 0) {
		fprintf(stderr, usage, argv[0]);
		exit(-1);
	}
  if (do_show_dfa) return ShowDFA(ifile_str);
  if (do_test) return TestDFA(ifile_str, test_str);
  return Dlex(ifile_str, odir_str, NULL);
}
