package parseTables;

import java.util.*;
import nonMDL.*;

public class opSphere extends opShape
{
    private double[] center;
    private double r;

    public opSphere(double[] center, double r, String cs, String constants)
    {
	this.center = center;
	this.r=r;
	this.cs=cs;
	this.constants=constants;
    }
    public String toString()
    {
	return "Sphere: "+"Center - "+triple(center)+
	    " Radius - "+r+" cs - "+cs+" constants - "+constants;
    }

    public double[] getCenter()
    {
	return center;
    }
    public double getR()
    {
	return r;
    }

    public void doIt(PointMatrix pm, Frame f, Stack<nonMDL.Matrix> originsList){

	System.out.println( "constants=" + constants);

	nonMDL.PointMatrix temp = new nonMDL.PointMatrix();
	temp.generateSphere(r, center[0], center[1]);
	temp.matrixMult(originsList.peek());
	pm.append(temp.backfaceCulling());
    }

}

