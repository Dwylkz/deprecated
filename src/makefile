target		= dpa
version		= 1.00

INCLUDE		=	-I.
LIBRARY		=	-L.
CFLAG		=	$(INCLUDE) $(LIBRARY) -Wall -g -O2 -ldac -ldlex2 -std=c99
name		=	$(basename $(wildcard *.c))
head		=	$(addsuffix .h, $(name))
source		=	$(addsuffix .c, $(name))
object		=	$(addsuffix .o, $(name))
lsource		=	$(filter-out main.c, $(source))
lhead		=	$(filter-out main.h, $(wildcard *.h))
lobject		=	*.o
temp		=	../temp

btemp		=	$(temp)/bin
ltemp		=	$(temp)/lib
itemp		=	$(temp)/include
prefix		=	/usr/local
bprefix		=	$(prefix)/bin/$(target)
lprefix		=	$(prefix)/lib/$(target)
iprefix		=	$(prefix)/include/$(target)
btarget		=	/usr/bin/$(target)
ltarget		=	/usr/lib/lib$(target).so

default: clean bin lib 

.PHONY		:	debug make_debug debugclean run clean install remove

debug				:
	gdb $(target)

make_debug	:	$(source)
	gcc $(source) -o $(target) $(CFLAG)

debugclean	:	$(source)
	-rm $(target) -f

clean:
	-rm -rf $(filter-out $(wildcard *.[ch]) makefile, $(wildcard *)) \
		$(temp)

run:
	./$(target)

dir			:
	mkdir $(temp)
	mkdir $(btemp)
	mkdir $(ltemp)
	mkdir $(itemp)

bin			:	dir $(source)
	gcc $(source) -o $(btemp)/$(target) $(CFLAG)

lib			: dir
	gcc  $(CFLAG) -fPIC -c $(lsource)
	gcc -shared -Wl,-s,-soname,lib$(target).so.$(version) \
		-o $(ltemp)/lib$(target).so.$(version) $(lobject)
	-rm $(lobject)
	cp $(lhead) $(itemp)

install		: remove default
	mkdir $(bprefix)
	mkdir $(iprefix)
	mkdir $(lprefix)
	cp -f $(btemp)/* $(bprefix)
	cp -f $(ltemp)/* $(lprefix)
	cp -f $(itemp)/* $(iprefix)
	ln -sf $(bprefix)/$(target) $(btarget)
	ln -sf $(lprefix)/lib$(target).so.$(version) $(ltarget)
	ln -sf $(lprefix)/lib$(target).so.$(version) $(ltarget).$(version)

remove		:
	rm -rf \
		$(bprefix) \
		$(iprefix) \
		$(lprefix) \
		$(btarget) \
		$(ltarget) \
		$(ltarget).$(version)
