all: subs mdl.class


subs:
	$(MAKE) -C parseTables
	$(MAKE) -C parser

mdl.class: mdl.java
	javac -classpath "." mdl.java

clean:
	$(MAKE) -C parseTables clean
	$(MAKE) -C parser clean
	rm mdl.class