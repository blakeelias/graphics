package parseTables;

import java.util.*;
import nonMDL.*;

public class opBox extends opShape
{
    
    private double[] p1;
    private double[] p2;
    private String cs2;

    public opBox(double[] p1, String cs, double[] p2,String cs2, String constants)
    {
	this.p1 = p1;
	this.p2 = p2;
	this.cs = cs;
	this.cs2= cs2;
	this.constants=constants;
    }

    public String toString()
    {
	return "Box: "+"p1 - "+triple(p1)+
	    "p2 - "+triple(p2)+
	    " cs1 - "+cs+" cs2 - "+cs2+" Contsants - "+constants;
    }
    public double[] getP1(){return p1;}
    public double[] getP2(){return p2;}
    public String getCs2(){return cs2;}

    public void doIt(PointMatrix pm, Frame f, Stack<nonMDL.Matrix> originsList){
	nonMDL.PointMatrix temp = new nonMDL.PointMatrix();
	temp.generateBox(p1[0], p1[1], p1[2], p2[0], p2[1], p2[2]);
	temp.matrixMult(originsList.peek());
	pm.append(temp.backfaceCulling());
    }

}


