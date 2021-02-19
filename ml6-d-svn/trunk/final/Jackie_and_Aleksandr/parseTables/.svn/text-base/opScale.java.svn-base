package parseTables;
import java.io.*;
import java.util.*;

public class opScale extends opTrans
{
    
    private double[] t;

    public opScale(double[] t, String knob)
    {
	this.t = t;
	this.knob = knob;
    }

    public String toString()
    {
	return "Scale: "+"t - "+triple(t)+
	    " Knob - "+knob;
    }
    public double[] getValues(){return t;}
    public String getKnob(){return knob;}

 	public String run( opPointMatrix m, opFrame f, Stack <opPointMatrix> s, HashMap opknoblist, int currentframe)
	{
	opPointMatrix temp = new opPointMatrix();
	opKnob tempknob=new opKnob();
	if(knob!=null)
	{temp.ident();
	tempknob=(opKnob)opknoblist.get(knob);
	temp.makeScale(t[0]*tempknob.values.get(currentframe),t[1]*tempknob.values.get(currentframe),t[2]*tempknob.values.get(currentframe));
	s.peek().matrixMult(temp); 
	System.out.print("yes");
}
	else{temp.ident();
	temp.makeScale(t[0],t[1],t[2]);
	s.peek().matrixMult(temp);
	System.out.print("no");
	}
	
	return null;}
}


