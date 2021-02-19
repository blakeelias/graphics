/* Generated By:JavaCC: Do not edit this line. MdlParser.java */
package opwork;
import java.util.*;

import parser.*;
import parseTables.*;

public class opmdl 
{
  public static void main(String args[]) throws ParseException 
    {
	ArrayList a;
	

	MdlParser parser = new MdlParser(System.in);
	parser.start();
	a = parser.getOps();

	System.out.println("Opcodes:");
	Iterator i = a.iterator();

System.out.println("\n\n");
        SymTab s = parser.getSymTab();
        Set kset = s.keySet();

	MDLReader r=new MDLReader(a,s);	

	while (i.hasNext())
	    {
		System.out.println(i.next());
		r.processCommands();
	    }
	
        i=kset.iterator();
	
	//MDLReader r=new MDLReader(a,s);	

	System.out.println("Symbol Table:");
	while (i.hasNext())
	    {
		String key = (String)i.next();
		Object value=s.get(key);
		System.out.println(""+key+"="+value);
	    }
	r.processCommands();
  }
}
