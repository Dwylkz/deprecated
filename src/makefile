#Source makefile
#Variables
CFLAG		=	-Wall #-ldtl
INCLUDE		=	-I ../Class
LIBRARY		=	#-L ../lib
name		=	$(basename $(wildcard *.c))
head		=	$(addsuffix .h, $(name))
header  = *.h
dif_interf  = *.i
source		=	$(addsuffix .c, $(name))
object		=	$(addsuffix .o, $(name))
backup		=	*~
exe			=	*.exe
tag			=	tags
#Test
input		=	../test.dlex
output		=	../test.h
#Rules
main		:	$(source) $(header) $(dif_interf)
	cc $(INCLUDE) $(LIBRARY) $(source) -o main $(CFLAG) 
#$(object)	:	$(head) $(source)
#Phony
.PHONY		:	run clean
clean:
	-rm -rf $(backup) $(object) $(exe) $(name) $(tag)
run:
	./main
