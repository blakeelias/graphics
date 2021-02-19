import java.io.*;
import java.util.*;
import java.awt.*;

public class Parser {
    
    private Matrix transform;
    private PointMatrix pm;
    private Frame f;

    public Parser() {
	
	f = new Frame();
	transform = new Matrix();
	pm = new PointMatrix();
	transform.ident();
    }


    public void parseFile( BufferedReader in ) throws IOException {
	Scanner s;
	while(in.ready()){
	    char c = (char)in.read();
	    in.readLine(); // gets rid of charriage return at end of line and whatever else there may be
	    switch(c) {
	    case 'l': case 'L':
		s = new Scanner(in.readLine());
		pm.addEdge(s.nextInt(), s.nextInt(), s.nextInt(), s.nextInt(), s.nextInt(), s.nextInt());
		break;
	    case 'i': case 'I':
		transform.ident();
		break;
	    case 's': case 'S':
		{
		    s = new Scanner(in.readLine());
		    Matrix temp = new Matrix();
		    temp.ident();
		    temp.MakeScale(s.nextDouble(), s.nextDouble(), s.nextDouble());
		    transform.matrixMult(temp);
		}
		break;
	    case 't': case 'T':
		{
		    s = new Scanner(in.readLine());
		    Matrix temp = new Matrix();
		    temp.ident();
		    temp.MakeTranslate(s.nextInt(), s.nextInt(), s.nextInt());
		    transform.matrixMult(temp);
		}
		break;
	    case 'x': case 'X':
		{
		    s = new Scanner(in.readLine());
		    Matrix temp = new Matrix();
		    temp.ident();
		    temp.MakeRotX(s.nextDouble() * Math.PI / 180);
		    transform.matrixMult(temp);
		}
		break;
	    case 'y': case 'Y':
		{
		    s = new Scanner(in.readLine());
		    Matrix temp = new Matrix();
		    temp.ident();
		    temp.MakeRotY(s.nextDouble() * Math.PI / 180);
		    transform.matrixMult(temp);
		}
		break;
	    case 'z': case 'Z':
		{
		    s = new Scanner(in.readLine());
		    Matrix temp = new Matrix();
		    temp.ident();
		    temp.MakeRotZ(s.nextDouble() * Math.PI / 180);
		    transform.matrixMult(temp);
		}
		break;
	    case 'a': case 'A':
		pm.matrixMult(transform);
		break;
	    case 'v': case 'V':  // does nothing in java
		break;
	    case 'g': case 'G':
		f.drawLines(pm, Color.MAGENTA);
		f.save(in.readLine().trim());
		break;
	    case 'c': case 'C':
		{
		    s = new Scanner(in.readLine());
		    pm.generateCircle(s.nextDouble(), s.nextDouble(), s.nextDouble(), s.nextDouble());
		    break;
		}
	    case 'm': case 'M':
		{
		    s = new Scanner(in.readLine());
		    pm.generateSphere( s.nextDouble(), s.nextDouble(), s.nextDouble());
		    break;
		}
	    case 'd': case 'D':
		{
		    s = new Scanner(in.readLine());
		    pm.generateTorus(s.nextDouble(), s.nextDouble(), s.nextDouble(), s.nextDouble());
		    break;
		}
	    case 'h': case 'H':
		{
		    s = new Scanner(in.readLine());
		    pm.hermiteCurve(s.nextDouble(), s.nextDouble(), s.nextDouble(), s.nextDouble(), s.nextDouble(), s.nextDouble(), s.nextDouble(), s.nextDouble());
		    break;
		}
	    case 'b': case 'B':
		{
		    s = new Scanner(in.readLine());
		    pm.bezierCurve(s.nextDouble(), s.nextDouble(), s.nextDouble(), s.nextDouble(), s.nextDouble(), s.nextDouble(), s.nextDouble(), s.nextDouble());
		    break;
		}
	    default: System.out.println( "This is no time for creativity; stick with the program and nobody gets hurt.");

	    }

	    // System.out.println(in.readLine());
	}
    }
}