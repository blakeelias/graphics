package parseTables;

import parseTables.*;
import java.util.*;
public class opShape extends opCode
{
    protected String cs;
    protected String constants;
    public String toString()
    {
	return "GENERIC OPSHAPE";
    }
    public String getCs()
    {
	return cs;
    }
    public String getConstants()
    {
	return constants;
    }

  /*  public void doIt(opPointMatrix pm2, opFrame f, Stack<opPointMatrix> list){
	f.drawLines(pm2, Color.GREEN);
	f.save(name);
    }*/
}
