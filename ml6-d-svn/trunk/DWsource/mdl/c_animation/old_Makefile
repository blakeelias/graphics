all: parser

parser: lex.yy.c y.tab.c y.tab.h symtab.o print_pcode.o matrix.o my_main.o
	gcc -o mdl -g lex.yy.c y.tab.c symtab.o print_pcode.o matrix.o my_main.o

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

my_main.o: my_main.c print_pcode.c
	gcc -c -Wall -g my_main.c

clean:
	rm matrix.o print_pcode.o symtab.o my_main.o
	rm y.tab.c y.tab.h
	rm lex.yy.c
