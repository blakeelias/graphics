package parseTables;

import parseTables.*;
import java.util.*;
import nonMDL.*;

public class opPop extends opCode
{
    public String toString()
    {
	return "POP";
    }
    public void doIt(PointMatrix pm, Frame f, Stack<nonMDL.Matrix> originsList){
	originsList.pop();
    }
}
