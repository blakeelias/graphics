 JCC=javac
JFLAGS=-classpath ".."

.SUFFIXES: .java .class

.java.class:
	$(JCC) $(JFLAGS) $<

all: classes

classes: Matrix.class Frame.class PointMatrix.class

clean:
	rm *class
