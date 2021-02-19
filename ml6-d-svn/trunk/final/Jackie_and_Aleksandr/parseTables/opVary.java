package parseTables;

import parseTables.*;
import java.util.*;

public class opVary extends opCode
{
	public Double tempd=0.0;
	public opKnob tempknob = new opKnob();
    private String knob;
    private int startframe,endframe;
    private double startval, endval;

    public opVary(String knob, int startframe, int endframe,
		  double startval, double endval)
    {
	this.knob=knob;this.startframe=startframe;this.endframe=endframe;
	this.startval=startval;this.endval=endval;
    }
    public int getStartframe(){ return startframe;}
    public int getEndframe(){ return endframe;}
    public double getStartval(){ return startval;}
    public double getEndval(){ return endval;}
    public String getKnob(){return knob;}
    public String toString()
{
	return "Vary: "+knob+" - "+startframe+" to "+endframe+
	    " values - "+startval+" to "+endval;
    }

    public String run (opPointMatrix m, opFrame f, Stack<opPointMatrix> s, HashMap opknoblist,int currentframe){
	int tstartframe=startframe;
	int tendframe=endframe;
        double tstartval=startval;
        double tendval=endval;
	for(;tstartframe<tendframe+1;tstartframe++){
	    double difference= endval-startval;
	    difference /= (endframe-startframe);
	    //tstartval+=difference;
		tempd=tstartval;
	int g=0;
/*	for(;g<opknoblist.size()-1;g++)
	{
	if(opknoblist.get(g).getName().equals(knob))
	{ System.out.println("System is finding the opknob it needs: "+knob);
break;}
	//else
	//{System.out.println(""+opknoblist.get(g).getName()+" + "+ knob);}


	if(g==opknoblist.size()-2){System.out.println("CANT FIND THE PROPER PLACE TO PUT THE VALUE IN OPKNOBLIST- called from opvary.");}
	}*/
	//System.out.println(g+", the # of the opknob it is trying to call");
	//System.out.println(tstartval+", the fram# of the opknob");
	  tempknob=(opKnob)opknoblist.get(knob);
/*System.out.println("fetching opKonb: "+knob);
System.out.println("frame: "+tstartframe);
System.out.println("knob: "+tempknob);*/
tempknob.setValue(tstartframe,tempd);
	    tstartval+=difference;
	

	}
   return null; }
}
