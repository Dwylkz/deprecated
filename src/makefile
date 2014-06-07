#Source makefile
#Variables
CFLAG		=	-std=c99
name		=	$(basename $(wildcard *.c))
head		=	$(addsuffix .h, $(name))
source		=	$(addsuffix .c, $(name))
object		=	$(addsuffix .o, $(name))
backup		=	*~
exe			=	*.exe
#Test
input		=	../test.dlex
output		=	../test.h
#Rules
#dlex		:	$(object)
#$(object)	:	$(head) $(source)
dlex		:	$(head) $(source)
#Phony
.PHONY		:	run clean
clean:
	-rm -rf $(backup) $(object) $(exe) $(name)
run:
	./dlex  --C -i ../test/test.dlex -o ../test/test.h
