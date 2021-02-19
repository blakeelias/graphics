all: parser

parser: lex.yy.c y.tab.c y.tab.h symtab.o cmd_processor.o matrix_skeleton.o my_main.o display.o draw.o parametrics.o splines.o matrix_stack.o
	gcc -o mdl -lm -g lex.yy.c y.tab.c symtab.o cmd_processor.o matrix_skeleton.o my_main.o display.o draw.o parametrics.o splines.o matrix_stack.o

lex.yy.c: mdl.l y.tab.h 
	flex -I mdl.l

y.tab.c: mdl.y symtab.h parser.h
	bison -d -y mdl.y

y.tab.h: mdl.y 
	bison -d -y mdl.y


symtab.o: symtab.c parser.h matrix.h
	gcc -c -Wall -g symtab.c

cmd_processor.o: cmd_processor.c parser.h matrix.h
	gcc -c -Wall -g cmd_processor.c

matrix_stack.o: matrix_stack.c
	gcc -c -Wall -g matrix_stack.c

my_main.o: my_main.c cmd_processor.c
	gcc -c -Wall -g my_main.c

clean:
#	rm matrix.o print_pcode.o symtab.o my_main.o
	rm *.o *~
	rm y.tab.c y.tab.h
	rm lex.yy.c


#all: main.o display.o draw.o matrix_skeleton.o parametrics.o splines.o#
#	gcc -o main -lm main.o display.o draw.o matrix_skeleton.o parametrics.o splines.o

#main.o: main.c ml6.h draw.h display.h matrix.h
#	gcc -c main.c

display.o: display.c display.h ml6.h
	gcc -c display.c

draw.o: draw.c draw.h ml6.h display.h
	gcc -c draw.c

matrix_skeleton.o : matrix.h matrix_skeleton.c
	gcc -c matrix_skeleton.c

parametrics.o : parametrics.h parametrics.c
	gcc -c parametrics.c

splines.o : splines.h splines.c
	gcc -c splines.c
