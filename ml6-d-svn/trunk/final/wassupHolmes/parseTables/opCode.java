package parseTables;

import java.util.*;
import nonMDL.*;

public class opCode
{
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

    public void doIt(PointMatrix pm, Frame f, Stack<nonMDL.Matrix> originsList){
	System.out.println("if you see this, you're wrong; you should have overridden this in your favorite subclass.");
    }

}

