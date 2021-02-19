package parseTables;
import java.io.*;
import java.util.*;

public class opKnob
{
	public String name;
	int place=0;
	public ArrayList<Double> values=new ArrayList<Double>();

	public opKnob()
	{values.ensureCapacity(101);
	for(int k=0;k<values.size();k++)
	{values.set(k,1.0);}	
	}
	public opKnob(String nam,int minsize)
	{name=nam;
	values.ensureCapacity(minsize+1);
	for(int k=0;k<values.size();k++)
	{values.set(k,1.0);}	 }

	public String getName()
	{return name;}
	
	public void setValue(int location,Double value)
	{values.add(location,value); }
	public double getValue(int location)
	{return values.get(location);}

	public String toString()
	{
	return("OPKNOB- NAME: "+name);
	}





}

