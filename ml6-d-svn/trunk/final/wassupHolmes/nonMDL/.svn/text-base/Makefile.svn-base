 JCC=javac
JFLAGS=-classpath ".."

.SUFFIXES: .java .class

.java.class:
	$(JCC) $(JFLAGS) $<

all: classes

classes: Matrix.class Frame.class PointMatrix.class Lighting.class Vector.class

clean:
	rm *class
