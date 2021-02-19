all: subs mdl.class Matrix.java PointMatrix.java Frame.java MDLReader.java


subs:
	$(MAKE) -C parseTables
	$(MAKE) -C parser

mdl.class: mdl.java
	javac -classpath "." mdl.java

MDLReader.class: MDLReader.java
	javac -classpath "." MDLReader.java

Matrix.class: Matrix.java
	javac Matrix.java

PointMatrix.class: PointMatrix.java Matrix.java
	javac PointMatrix.java

Frame.class: Frame.java PointMatrix.java
	javac Frame.java

clean:
	$(MAKE) -C parseTables clean
	$(MAKE) -C parser clean
	rm mdl.class
