package parseTables;
import java.io.*;
import java.util.*;
import parseTables.*;

public class opBasename extends opCode
{
    private String name;
    public opBasename(String name)
    {
	this.name = name;
    }
    public String getName()
    {
	return name;
    }
    public String toString()
    {
	return "Basename: "+name;
    }

	public String run( opPointMatrix m, opFrame f, Stack <opPointMatrix> s, HashMap opknoblist, int currentframe)
	{
	 return name;

	}

}
