package parseTables;

import nonMDL.*;
import java.util.*;

public class opMove extends opTrans
{
    
    private double[] t;

    public opMove(double[] t, String knob)
    {
	this.t = t;
	this.knob = knob;
    }

    public String toString()
    {
	return "Move: "+"t - "+triple(t)+
	    " Knob - "+knob;
    }
    public double[] getValues(){return t;}
    public String getKnob(){return knob;}

    public void doIt(PointMatrix pm, Frame f, Stack<nonMDL.Matrix> originsList){
	nonMDL.Matrix temp = new nonMDL.Matrix();
	temp.MakeTranslate(t[0], t[1], t[2]);
	originsList.peek().matrixMult(temp);
    }

}


