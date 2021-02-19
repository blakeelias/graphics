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

    public void printSymbols() {

	Iterator i;

	i = symKeys.iterator();
	System.out.println("Symbol Table:");

	while (i.hasNext()) {
		String key = (String)i.next();
		Object value=symbols.get(key);
		System.out.println(""+key+"="+value);
	}
    }
}
