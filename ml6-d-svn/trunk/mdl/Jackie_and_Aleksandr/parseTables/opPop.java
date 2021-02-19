package parseTables;
import java.util.*;
import parseTables.*;

public class opPop extends opCode
{
    public String toString()
    {
	return "POP";
    }
	public String run( opPointMatrix m, opFrame f, Stack <opPointMatrix> s, HashMap opknoblist,int currentframe)
	{
	s.pop();
	return null;}
}
