OBJECTS: Matrix.class PointMatrix.class Canvas.class gui.class

all: $(OBJECTS)

Matrix.class: Matrix.java
	javac Matrix.java

PointMatrix.class: PointMatrix.java Matrix.java
	javac PointMatrix.java

Canvas.class: Canvas.java PointMatrix.java Matrix.java
	javac Canvas.java

gui.class: gui.java Canvas.java PointMatrix.java Matrix.java
	javac gui.java

clean:
	rm *~ *.class