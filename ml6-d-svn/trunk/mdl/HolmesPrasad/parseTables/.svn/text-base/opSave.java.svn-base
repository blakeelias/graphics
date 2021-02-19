package parseTables;

import parseTables.*;
import nonMDL.*;
import java.awt.*;
import java.util.*;

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

    public void doIt(PointMatrix pm, nonMDL.Frame f, Stack<nonMDL.Matrix> originsList){
	f.drawLines(pm, Color.MAGENTA);
	f.save(name);
    }
}