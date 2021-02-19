CC=gcc
CCOPTS=-c -Wall -g


all : parser


parser : lex.yy.c y.tab.c y.tab.h symtab.o print_pcode.o matrix.o my_main.o draw.o display.o stack.o
	$(CC) -o mdl -g lex.yy.c y.tab.c symtab.o print_pcode.o matrix.o my_main.o draw.o display.o stack.o

lex.yy.c : mdl.l y.tab.h 
	flex -I mdl.l

y.tab.c : mdl.y symtab.h parser.h
	bison -d -y mdl.y

y.tab.h : mdl.y 
	bison -d -y mdl.y


symtab.o : symtab.c parser.h matrix.h
	$(CC) $(CCOPTS) symtab.c

print_pcode.o : print_pcode.c parser.h matrix.h
	$(CC) $(CCOPTS) print_pcode.c

matrix.o : matrix.c matrix.h
	$(CC) $(CCOPTS) matrix.c

my_main.o : my_main.c print_pcode.c draw.h display.h ml6.h
	$(CC) $(CCOPTS) my_main.c

draw.o : draw.c ml6.h matrix.h display.h draw.h
	$(CC) $(CCOPTS) draw.c

stack.o : stack.c matrix.h
	$(CC) $(CCOPTS) stack.c

display.o : display.h ml6.h
	$(CC) $(CCOPTS) display.c


force : clean all

clean :
	rm -f parser *~ *.o y.tab.c y.tab.h lex.yy.c
