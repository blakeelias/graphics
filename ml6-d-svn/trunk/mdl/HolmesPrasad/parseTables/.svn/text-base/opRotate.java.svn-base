package parseTables;

import nonMDL.*;
import java.util.*;

public class opRotate extends opTrans
{
    
    double deg;
    char axis;

    public opRotate(char axis, double deg, String knob)
    {
	this.axis = axis;
	this.deg = deg;
	this.knob = knob;
    }

    public String toString()
    {
	return "Rotate: Axis - "+axis+" Deg - "+deg;
    }
    public char getAxis(){return axis;}
    public double getDeg(){return deg;}
    public String getKnob(){return knob;}

    public void doIt(PointMatrix pm, Frame f, Stack<nonMDL.Matrix> originsList){
	nonMDL.Matrix temp = new nonMDL.Matrix();
	switch (axis){
	case 'x': case 'X':
	    temp.MakeRotX(deg*Math.PI/180);
	    break;
	case 'y': case 'Y':
	    temp.MakeRotY(deg*Math.PI/180);
	    break;
	case 'z': case 'Z':
	    temp.MakeRotZ(deg*Math.PI/180);
	    break;
	}
	originsList.peek().matrixMult(temp);
    }
}


