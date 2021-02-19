/*========== MDLReader.java ==========
  MDLReader objects minimally contain an ArrayList<opCode> containing
  the opCodes generated when an mdl file is run through the java created
  lexer/parser, as well as the associated SymTab (Symbol Table).

  The provided methods are a constructor, and methods to print out the
  entries in the symbol table and command ArrayList.

=========================*/
import parseTables.*;
import java.util.*;
import java.io.*;
//import opwork.*;
import parser.*;
import java.awt.*; 

public class MDLReader{

    ArrayList<opCode> opcodes;
    HashMap opknoblist;//=new HashMap();
   //opknoblist.ensureCapacity(100);
	ArrayList<String> keylist = new ArrayList<String>();
    int currentframe=0;
    String basename="";
    SymTab symbols;
    Set symKeys;
	int numframes=5;
	boolean anyframes=false;
	opCode tempcode;
	

    public MDLReader(ArrayList<opCode> o, SymTab s){

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
		//opknoblist.add(key);
	}
    }
	public void addKnobs()
	{Iterator i;
	Iterator m;
	int count=0;

	i = symKeys.iterator();
	m = symKeys.iterator();
	while (i.hasNext()) {
		String key = (String)i.next();
		Object value=symbols.get(key);
		keylist.add(key);
		count++;
	 }
	opknoblist=new HashMap(count);
	while (m.hasNext()) {
		String key = (String)m.next();
		Object value=symbols.get(key);
		opKnob k =new opKnob(key,numframes+1);
		opknoblist.put(key,k);
	 
	}
   }
	public void setknobs()
	{
	 Iterator i;
	 /*Set st = opknoblist.entrySet();
	i= st.iterator();*/
	i=keylist.iterator();
	opKnob tempknob= new opKnob();
	while(i.hasNext())
	 {
		//Map.Entry me = (Map.Entry)i.next();
		tempknob =(opKnob)opknoblist.get(i.next());//me.getValue();
		symbols.setValue(tempknob.getName(),tempknob.values.get(currentframe));
	//System.out.print(""+tempknob.getName()+"  "+tempknob.values.get(currentframe)+";  ");
	System.out.print(""+tempknob.getName()+"  "+symbols.get(tempknob.getName())+";  ");
	 }


	}
public void processCommands(){

Iterator<opCode> i = opcodes.iterator();
Iterator<opCode> framecheck = opcodes.iterator();
Iterator<opCode> frameextract = opcodes.iterator();
Iterator<opCode> varyrunner = opcodes.iterator();

 Stack<opPointMatrix> list = new Stack();
 opPointMatrix start= new opPointMatrix();
 start.ident();
 list.push(start);
 opPointMatrix pm = new opPointMatrix();
 opFrame f = new opFrame();

 String knobname="";
 double knobvalue=0;

//System.out.println("Check1 \n");
if(framecheck.hasNext()&& framecheck.next() instanceof opFrames)
{opFrames tempf = (opFrames)frameextract.next();
//System.out.println("we got frames: "+tempf.getNum());
numframes=tempf.num;
anyframes=true; 
//System.out.println("Yes we are checking for frames:"+numframes+"\n");
//System.out.println("Check2 \n");
	}
if(anyframes)
{
printSymbols();
addKnobs();
int o=0;
for(;o<opknoblist.size();o++)
{//System.out.println(""+opknoblist.get(o).getName());}
while(varyrunner.hasNext())
 {
  tempcode =varyrunner.next();
  if(tempcode instanceof opVary)
   {
	//System.out.println("Check5 \n");
	tempcode.run(pm, f, list,opknoblist,currentframe);
	//System.out.println("Check6 \n");
   }

 }
}}
//System.out.println("Check7 \n");
/* Scanner sc=new Scanner(System.in);
InputStreamReader input = new InputStreamReader(System.in);
	BufferedReader reader = new BufferedReader(input);

// while(knobname!="-1")
 //{
 System.out.println("input a knob name:");
try{ knobname=reader.readLine();}
catch(IOException e){System.out.println("ERRORROROROROROROROROROR");}
	//reader.readLine();
 System.out.println("input a knob value to set:");
 //knobvalue=sc.nextDouble();
//try {sc.next();}
//catch(Exception e){System.out.println("ERRORROROROROROROROROROR TROLOLOLOLOLOL");}
 //} */
	if(anyframes)
	{System.out.println("YES frames\n\n\n");
	  while(currentframe<numframes)
	{
Stack<opPointMatrix> newlist = new Stack();
 opPointMatrix newstart= new opPointMatrix();
 newstart.ident();
 newlist.push(newstart);
 opPointMatrix newpm = new opPointMatrix();
 opFrame newf = new opFrame();
	Iterator<opCode> newi = opcodes.iterator();
	Iterator<opCode> basenamecheck = opcodes.iterator();
	 setknobs();
	 while(basenamecheck.hasNext()){
	tempcode=(opCode)basenamecheck.next();
	if(tempcode instanceof opBasename)
         {basename=tempcode.run(newpm, newf, newlist,opknoblist,currentframe);}}
 	while(newi.hasNext()){
 newi.next().run(newpm, newf, newlist,opknoblist,currentframe);
 }
	Random r=new Random();	
	if(r.nextDouble() > .5)
	{newf.drawLines(newpm, Color.RED);}
	else {newf.drawLines(newpm, Color.GREEN);}
	newf.save(""+basename+currentframe);
	//System.out.println("current frame"+currentframe);
	currentframe++;
 	}
	}
	else
 {System.out.println("no frames\n\n\n");
while(i.hasNext()){
 i.next().run(pm, f, list,opknoblist,currentframe);
 }}
	//System.out.println("HGWQEGHZDJSNXADKEM>");
 
    
 }
}
