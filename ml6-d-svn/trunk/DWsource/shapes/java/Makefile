OBJECTS: Matrix.class PointMatrix.class Frame.class Parser.class Test.class

all: $(OBJECTS)

Matrix.class: Matrix.java
	javac Matrix.java

PointMatrix.class: PointMatrix.java Matrix.java
	javac PointMatrix.java

Frame.class: Frame.java PointMatrix.java
	javac Frame.java

Parser.class: Parser.java Frame.java PointMatrix.java Matrix.java
	javac Parser.java

Test.class: Test.java Parser.java
	javac Test.java

run: Test.class
	java Test
clean:
	rm *~ *.class