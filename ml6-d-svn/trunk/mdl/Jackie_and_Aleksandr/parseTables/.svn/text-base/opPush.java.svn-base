package parseTables;
import java.util.*;
import parseTables.*;
//import opwork.*;

public class opPush extends opCode{
   
    public String toString(){
	return "PUSH";
    }
	public String run( opPointMatrix m, opFrame f, Stack <opPointMatrix> s, HashMap opknoblist,int currentframe){
	opPointMatrix temp=new opPointMatrix();
	if(s.empty()){
	temp.ident(); s.push(temp);
	}
	else{ temp = s.peek().copy();
	s.push(temp);
	    }
	return null;}
}
