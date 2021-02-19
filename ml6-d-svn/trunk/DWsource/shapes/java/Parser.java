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


    public void parseFile( BufferedReader in ) {
	
	String s;
	String[] p = new String[1];
	Matrix tmp = new Matrix();

	try {

	    s = in.readLine();

	    while ( s != null ) {

		if ( s.length() != 1 ) {
		    System.out.println("Invalid file line: " + s);
		    return;
		}
		
		char c = s.charAt(0);

		if ( c == 'l' || c == 's' || c == 't' || 
		     c == 'c' || c == 'm' || c == 'd' ) {
	    
		    s = in.readLine();
		    p = s.split(" ");
		}
		else if ( c == 'l' ) { 
		    if ( p.length != 6 ) {
			System.out.println("Line requires 6 parameters");
			return;
		    }

		    pm.addEdge(Double.parseDouble(p[0]), 
			       Double.parseDouble(p[1]),
			       Double.parseDouble(p[2]), 
			       Double.parseDouble(p[3]), 
			       Double.parseDouble(p[4]), 
			       Double.parseDouble(p[5]) );
		}
		else if ( c == 's' ) {

		    if ( p.length != 3 ) 
			System.out.println("Scale requires 3 parameters");

		    tmp.makeScale( Double.parseDouble(p[0]),
			       Double.parseDouble(p[1]),
			       Double.parseDouble(p[2]) );

		    transform.matrixMult(tmp);
		}
		else if ( c == 't' ) {

		    if ( p.length != 3 ) 
			System.out.println("translation requires 3 parameters");

		    tmp.makeTranslate( Double.parseDouble(p[0]),
				     Double.parseDouble(p[1]),
				     Double.parseDouble(p[2]) );

		    transform.matrixMult(tmp);
		}
		else if ( c == 'x' || c == 'y' || c == 'z' ) {
	    
		    s = in.readLine();
		    double angle = Double.parseDouble(s);
		    angle = angle * ( Math.PI / 180 );
		    if ( c == 'x')
			tmp.makeRotX( angle );
		    else if ( c == 'y' )
			tmp.makeRotY( angle );
		    else
			tmp.makeRotZ( angle );
		    transform.matrixMult( tmp );
		}
		else if ( c == 'i' )
		    transform.ident();

		else if ( c == 'a' )
		    pm.matrixMult( transform );
		else if ( c == 'r' )
		    pm.clear();
		else if ( c == 'g' ) {
	   
		    s = in.readLine();
		    s = s + ".png";
		    f.drawLines(pm, new Color(0, 255, 255));
		    f.save(s);
		}
		else if ( c == 'q' )
		    System.exit(0);
		else 
		    System.out.println("unrecognized command");
		
		s = in.readLine();
	    }
	}
	catch (IOException e) {}	    
    }
}