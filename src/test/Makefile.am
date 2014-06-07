noinst_PROGRAMS = test
test_SOURCES = main.c
test_LDADD = ../libdac.la
test_CFLAGS = -I../ -I../v2

.PHONY: run
run:
	valgrind ./test
