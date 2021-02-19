import java.io.*;
import java.util.*;
import java.lang.*;

public class MatrixTest{
    public static void main (String[] args){
	Matrix m = new Matrix();
	m.ident();
	Matrix m2 = m.copy();
	m2.scalarMult(3);
	System.out.println(m);
	System.out.println(m2);
	m.grow();
	m.scalarMult(7);
	m.matrixMult(m2);
	System.out.println(m);
	m2.matrixMult(m);
	System.out.println(m2);
    }
}