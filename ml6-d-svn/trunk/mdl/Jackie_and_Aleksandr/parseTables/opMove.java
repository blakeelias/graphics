package parseTables;
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

	public String run( opPointMatrix m, opFrame f, Stack <opPointMatrix> s, HashMap opknoblist,int currentframe)
	{

	opPointMatrix temp = new opPointMatrix();
	opKnob tempknob=new opKnob();
	
	if(knob!=null)
	{
	temp.ident();
	tempknob=(opKnob)opknoblist.get(knob);
	temp.makeTranslate(t[0]*tempknob.values.get(currentframe),t[1]*tempknob.values.get(currentframe),t[2]*tempknob.values.get(currentframe));
	s.peek().matrixMult(temp); 
	}
	else{temp.makeTranslate(t[0],t[1],t[2]);
	
	//temp.matrixMult(s.peek());
	s.peek().matrixMult(temp);}

	
	return null;



}

}


