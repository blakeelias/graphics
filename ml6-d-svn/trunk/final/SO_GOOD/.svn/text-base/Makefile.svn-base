all: parser

parser: lex.yy.c y.tab.c y.tab.h symtab.o print_pcode.o stack.o matrix.o my_main.o draw.o display.o
	gcc -o mdl -g -lm lex.yy.c y.tab.c symtab.o print_pcode.o stack.o matrix.o my_main.o draw.o display.o

lex.yy.c: mdl.l y.tab.h 
	flex -I mdl.l

y.tab.c: mdl.y symtab.h parser.h
	bison -d -y mdl.y

y.tab.h: mdl.y 
	bison -d -y mdl.y


symtab.o: symtab.c
	gcc -c -Wall -g symtab.c

print_pcode.o: print_pcode.c
	gcc -c -Wall -g print_pcode.c

stack.o: stack.c
	gcc -c -Wall -g stack.c

matrix.o: matrix.c
	gcc -c -Wall -g matrix.c

my_main.o: my_main.c
	gcc -c -Wall -g my_main.c
	
draw.o: draw.c
	gcc -c -Wall -g draw.c
	
display.o: display.c
	gcc -c -Wall -g display.c

clean:
	rm matrix.o print_pcode.o symtab.o my_main.o
	rm y.tab.c y.tab.h
	rm lex.yy.c
