package parseTables;
import java.io.*;
import java.util.*;

public class opRotate extends opTrans{
    
    double deg;
    char axis;

    public opRotate(char axis, double deg, String knob){
	this.axis = axis;
	this.deg = deg;
	this.knob = knob;
    }

    public String toString() {
	return "Rotate: Axis - "+axis+" Deg - "+deg;
    }
    public char getAxis(){return axis;}
    public double getDeg(){return deg;}
    public String getKnob(){return knob;}

	public String run( opPointMatrix m, opFrame f, Stack <opPointMatrix> s, HashMap opknoblist, int currentframe)
	{
	 opPointMatrix temp = new opPointMatrix();
 	 opKnob tempknob = new opKnob();
if(knob!=null)
{
	 tempknob=(opKnob)opknoblist.get(knob);
	/*System.out.println(""+currentframe);
	System.out.println(""+knob);
	System.out.println(""+tempknob.getName());
	 System.out.println(""+tempknob.values.get(currentframe));*/
	//System.out.println("YES WE USING KNOBS SILLY");
	 if(axis =='x')
	 {temp.makeRotX(tempknob.values.get(currentframe)*deg*Math.PI/180);}
	 if(axis =='y')
	 {temp.makeRotY(deg*Math.PI/180*tempknob.values.get(currentframe));}
	 if(axis =='z')
	 {temp.makeRotZ(deg*Math.PI/180*tempknob.values.get(currentframe));}
	s.peek().matrixMult(temp);}
else
	{
if(axis =='x')
	 {temp.makeRotX(deg*Math.PI/180);}
	 if(axis =='y')
	 {temp.makeRotY(deg*Math.PI/180);}
	 if(axis =='z')
	 {temp.makeRotZ(deg*Math.PI/180);}
	s.peek().matrixMult(temp);
	}
	return null;}

}


