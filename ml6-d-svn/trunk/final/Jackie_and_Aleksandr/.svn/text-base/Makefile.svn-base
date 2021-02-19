all: subs mdl.class MDLReader.class


subs:
	$(MAKE) -C parseTables
	$(MAKE) -C parser

mdl.class: mdl.java
	javac -classpath "." mdl.java

MDLReader.class: MDLReader.java
	javac -classpath "." MDLReader.java

clean:
	$(MAKE) -C parseTables clean
	$(MAKE) -C parser clean
	rm mdl.class
