noinst_PROGRAMS = test
test_SOURCES = main.c
LDADD = ../libdac2.la
AM_CFLAGS = -I../

run:
	clear
	./test

debug:
	clear
	valgrind --leak-check=full --show-leak-kinds=all ./test

.PHONY: run debug
