/* Generated By:JavaCC: Do not edit this line. MdlParser.java */

import java.util.*;
import java.io.*;

import parser.*;
import parseTables.*;

public class mdl 
{
  public static void main(String args[]) throws ParseException 
    {
	ArrayList<opCode> a;
	MdlParser parser = new MdlParser(System.in);
	parser.start(); //takes the commands from source and turns them into an array of opCodes
	a = parser.getOps();

	SymTab s = parser.getSymTab();
	MDLReader reader = new MDLReader(a, s);

	reader.printSymbols(s);
	InputStreamReader isr = new InputStreamReader(System.in);
	BufferedReader buffer = new BufferedReader(isr);
	int knobKey = 0;
	while(knobKey != -1){
	    System.out.println("Please enter the int corresponding to the knob you would like to set.  To exit, enter -1");
	    try{knobKey = Integer.parseInt(buffer.readLine());}
	    catch (IOException e){}
	}

	reader.printCommands();
	reader.processCommands();
  }
}
