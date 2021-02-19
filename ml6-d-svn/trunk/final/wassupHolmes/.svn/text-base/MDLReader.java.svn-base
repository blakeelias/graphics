/*========== MDLReader.java ==========
  MDLReader objects minimally contain an ArrayList<opCode> containing
  the opCodes generated when an mdl file is run through the java created
  lexer/parser, as well as the associated SymTab (Symbol Table).

  The provided methods are a constructor, and methods to print out the
  entries in the symbol table and command ArrayList.

  =========================*/

import java.util.*;
import java.io.*;

import parser.*;
import parseTables.*;
import nonMDL.*;

public class  MDLReader {

    ArrayList<opCode> opcodes;
    SymTab symbols;
    Set symKeys;

    public MDLReader(ArrayList<opCode> o, SymTab s) {

	opcodes = o;
	symbols = s;
	symKeys = s.keySet();
    }

    public void printCommands() {
	
	Iterator i = opcodes.iterator();

	while (i.hasNext()) {
	    System.out.println(i.next());
	}
    }

    public void printSymbols(SymTab s) {

	Iterator<String> i;
	Set symKeys = s.keySet();

	i = symKeys.iterator();
	System.out.println("Symbol Table:");

	while (i.hasNext()) {
	    String key = i.next();
	    Object value=symbols.get(key);
	    System.out.println(""+key+"="+value);
	}
    }

    public void processCommands() {
	/*
	  'Matrix placeholderMatrix' is a generic placeholder for a matrix from originsList
	  'Matrix origin' is the standard origin (0,0,0) and the first member of the stack
	*/
        Stack<nonMDL.Matrix> originsList = new Stack();
	//	Matrix placeholderMatrix = new Matrix();
	nonMDL.Matrix origin = new nonMDL.Matrix();
	origin.ident();
	originsList.push(origin);  // this is so that the user can have a drawing routine as the first line of a script

	/*
	  create structures necessary to store the points and write to a file
	 */
	nonMDL.Frame f = new nonMDL.Frame();
	nonMDL.PointMatrix pm = new nonMDL.PointMatrix();

	// process commands
	Iterator<opCode> i = opcodes.iterator();
	while (i.hasNext())
	    i.next().doIt(pm, f, originsList);

    }
}