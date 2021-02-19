import java.io.*;
import java.util.*;
import java.lang.Math.*;
import javax.swing.*;
import java.awt.*;
import java.awt.image.*;
import javax.imageio.*;

public class Test {
    public static void main(String[] args) {

	Frame f = new Frame();
	//	f.drawLine(0, 0, 234, 234, new Color (255));

	/*
	Matrix transformer = new Matrix();
	PointMatrix pm = new PointMatrix();
	pm.addPoint(0, 0, 0);
	pm.addPoint(10, 10, 10);
	pm.addEdge(100, 100, 100, 200, 200, 200);

	f.drawLines(pm, new Color(255));

	transformer.MakeTranslate(100, 10, 0);
	pm.matrixMult(transformer);
	f.drawLines(pm, Color.ORANGE);

	transformer.MakeScale(1.5, 2, 2.5);
	pm.matrixMult(transformer);
	f.drawLines(pm, Color.CYAN);
	
	transformer.MakeRotZ(Math.PI / 6);
	pm.matrixMult(transformer);
	f.drawLines(pm, Color.YELLOW);
	
	PointMatrix pm2 = new PointMatrix();
	pm2.addEdge(50, 0, 100, 50, 0, 200);

	transformer.MakeRotX( -Math.PI / 2);
	pm2.matrixMult(transformer);
	f.drawLines(pm2, Color.CYAN);
	
	transformer.MakeRotY( Math.PI / 4);
	pm2.matrixMult(transformer);
	f.drawLines(pm2, Color.MAGENTA);
	
	f.save("test.png");

	*/


	
	Parser p = new Parser();
	
       	try {
	    
	//InputStreamReader in = new InputStreamReader(System.in);
	    FileReader in = new FileReader("scripts/script");
	    BufferedReader bin = new BufferedReader( in );
	    p.parseFile(bin);
	}
	catch (IOException e) {}
	
    }
}