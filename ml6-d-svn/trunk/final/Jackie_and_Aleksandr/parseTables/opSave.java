package parseTables;

import parseTables.*;
import java.util.*;
import java.io.*;
import java.awt.*; 
public class opSave extends opCode
{
    private String name;
    public opSave(String name)
    {
	this.name = name;
    }
    public String getName()
    {
	return name;
    }
    public String toString()
    {
	return "Save: "+name;
    }


public String run( opPointMatrix m, opFrame f, Stack <opPointMatrix> s, HashMap opknoblist,int currentframe)
{
f.drawLines(m, Color.RED);
        f.save(name);

return null;}




}
