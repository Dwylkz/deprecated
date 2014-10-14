bin_PROGRAMS = mylang
include_HEADERS = 
mylang_SOURCES = $(include_HEADERS) \
								 comm.h \
								 lexer.h \
								 main.c \
								 lexer.c
mylang_CFLAGS = -ltdsl -static

.PHONY: run
run:
	@./mylang test.bnf

.PHONY: debug
debug:
	@valgrind --leak-check=full ./mylang test.bnf
