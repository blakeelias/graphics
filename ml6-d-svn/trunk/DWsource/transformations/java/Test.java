import java.io.*;
import java.util.*;
import java.lang.Math.*;

public class Test {
    public static void main(String[] args) {
	
	Parser p = new Parser();
	
       	try {
	    
	//InputStreamReader in = new InputStreamReader(System.in);
	    FileReader in = new FileReader("script");
	    BufferedReader bin = new BufferedReader( in );
	    p.parseFile(bin);
	}
	catch (IOException e) {}
    }
}