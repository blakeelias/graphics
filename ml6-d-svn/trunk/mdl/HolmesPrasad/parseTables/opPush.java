package parseTables;

import parseTables.*;
import java.util.*;
import nonMDL.*;

public class opPush extends opCode
{
    public String toString()
    {
	return "PUSH";
    }

    public void doIt(PointMatrix pm, Frame f, Stack<nonMDL.Matrix> originsList){
	nonMDL.Matrix temp;
	if (originsList.empty()){
	    temp = new nonMDL.Matrix();
	    temp.ident();
	}
	else{
	    temp = originsList.peek().copy();
	}
	originsList.push(temp);
    }
}
