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


	// //quick test of triangle drawing with scanlineTest
	// pm.addTriangle(200, 200, 0,
	// 	       100, 120, 0,
	// 	       250, 120, 0);

		       
	f.drawTriangles(pm, Color.MAGENTA);
	f.save(name);
    }
}