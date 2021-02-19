all: subs MDLReader.class mdl.class


subs:
	$(MAKE) -C nonMDL
	$(MAKE) -C parseTables
	$(MAKE) -C parser

mdl.class: mdl.java
	javac -classpath "." mdl.java

MDLReader.class: MDLReader.java
	javac MDLReader.java

clean:
	$(MAKE) -C parseTables clean
	$(MAKE) -C parser clean
	rm mdl.class