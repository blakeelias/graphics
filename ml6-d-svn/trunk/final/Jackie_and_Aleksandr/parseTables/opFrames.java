package parseTables;

import parseTables.*;

public class opFrames extends opCode
{
    public int num;
    public opFrames(int num)
    {
	this.num = num;
	//System.out.println("The amount of frames is: "+num);
    }
    public int getNum()
    {
	return num;
    }
    public String toString()
    {
	return "Frames: "+num;
    }
}
