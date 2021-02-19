all: parser

parser: lex.yy.c y.tab.c y.tab.h symtab.o print_pcode.o matrix.o my_main.o stack.o draw.o display.o
	gcc -o mdl -g -lm lex.yy.c y.tab.c my_main.o symtab.o print_pcode.o matrix.o stack.o draw.o display.o

lex.yy.c: mdl.l y.tab.h 
	flex -I mdl.l

y.tab.c: mdl.y symtab.h parser.h
	bison -d -y mdl.y

y.tab.h: mdl.y 
	bison -d -y mdl.y

symtab.o: symtab.c parser.h matrix.h
	gcc -c -Wall -g symtab.c

print_pcode.o: print_pcode.c parser.h matrix.h
	gcc -c -Wall -g print_pcode.c

matrix.o: matrix.c matrix.h
	gcc -c -Wall -g matrix.c

my_main.o: my_main.c matrix.h parser.h stack.h draw.h display.h
	gcc -c -Wall -g my_main.c

stack.o: stack.c matrix.h
	gcc -c stack.c

draw.o: draw.c draw.h matrix.h ml6.h display.h
	gcc -c draw.c

display.o: display.c display.h ml6.h
	gcc -c display.c

clean:
	rm matrix.o print_pcode.o symtab.o stack.o my_main.o draw.o display.o
	rm y.tab.c y.tab.h
	rm lex.yy.c

test: test.c stack.o matrix.o
	gcc test.c stack.o matrix.o
