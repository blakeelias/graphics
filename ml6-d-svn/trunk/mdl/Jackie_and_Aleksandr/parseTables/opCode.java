package parseTables;
import java.util.*;
//import opwork.*;

public class opCode
{
public int num=100;
    protected String triple(double[] s)
    {
	if (s==null)
	    return "";
	else
	    return ""+s[0]+","+s[1]+","+s[2];
    }

    public String toString()
    {
	return "GENERIC OPCODE";
    }

	public String run( opPointMatrix m, opFrame f, Stack <opPointMatrix> s,HashMap opknoblist,int currentframe)
	{System.out.print("."); return null;}

}

