#include "argv.h"
void argCheck(int argc, char *argv[]) {
	if (argc < 6
			|| strcmp(argv[1], CFLAG)
			|| strcmp(argv[2], DLEXFILEFLAG)
			|| strcmp(argv[4], OFILEFLA)) {
		Usage();
		throwErro("Illegal format, man.", 1);
	}
	if (!(ifile = fopen(argv[3], "r"))) {
		throwErro("Can't open dlexfile.", 2);
	}
	ofile = fopen(argv[5], "w");
}
void argFree() {
	fclose(ifile);
	fclose(ofile);
}
