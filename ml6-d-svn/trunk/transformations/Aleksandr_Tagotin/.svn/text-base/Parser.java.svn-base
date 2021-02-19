import java.io.*;
import java.util.*;
import java.awt.*;


public class Parser {
    
    private Matrix transform;
    private PointMatrix pm;
    private Frame f;

    public Parser() {
	
	f = new Frame();
	transform = new Matrix();
	pm = new PointMatrix();
	transform.ident();
    }


    public void parseFile( BufferedReader in )  throws IOException  {

	Scanner sc ;//= new Scanner(System.in);
	while(in.ready())
	{
	char c;
	c=(char)in.read();
	in.readLine();// people say I need it <:|
		//if(c=='l'){System.out.println("NMGRM#!%#^%&#");}
		if(c=='l'||c=='L')
		{//System.out.println("before define line sc");
		sc=new Scanner(in.readLine());
		//System.out.println("after define line sc");
		 pm.addEdge(sc.nextInt(),sc.nextInt(),sc.nextInt(),sc.nextInt(),sc.nextInt(),sc.nextInt());
		//System.out.println("finshed attempting to add line");
		}
		//else{System.out.println("does not compute. c=="+c);}
		if(c=='i'||c=='I')
		{
		 transform.ident();
		}
		if(c=='s'||c=='S')
		{sc=new Scanner(in.readLine());
		 Matrix temp= new Matrix();
		 temp.MakeScale(sc.nextInt(),sc.nextInt(),sc.nextInt());
		 //temp.scalarMult(sc.nextInt())
		 transform.matrixMult(temp);
		 
	
		}
		if(c=='t'||c=='T')
		{sc=new Scanner(in.readLine());
		 Matrix temp= new Matrix();
		 temp.MakeTranslate(sc.nextInt(),sc.nextInt(),sc.nextInt());
		 //temp.scalarMult(sc.nextInt())
		 transform.matrixMult(temp);
		 
		}
		if(c=='x'||c=='X')
		{sc=new Scanner(in.readLine());
		 Matrix temp= new Matrix();
		 temp.MakeRotX(sc.nextDouble());
		 //temp.scalarMult(sc.nextInt())
		 transform.matrixMult(temp);
		 
		}
		if(c=='y'||c=='Y')
		{sc=new Scanner(in.readLine());
		 Matrix temp= new Matrix();
		 temp.MakeRotY(sc.nextDouble());
		 //temp.scalarMult(sc.nextInt())
		 transform.matrixMult(temp);
		}
		if(c=='z'||c=='Z')
		{sc=new Scanner(in.readLine());
		 Matrix temp= new Matrix();
		 temp.MakeRotZ(sc.nextDouble());
		 //temp.scalarMult(sc.nextInt())
		 transform.matrixMult(temp);
		}
		if(c=='a'||c=='A')
		{
		pm.matrixMult(transform);
		}
		if(c=='v'||c=='V')
		{
		 System.out.println("This is java silly. 'View the image (not needed for Java)'  ");
		}
		if(c=='g'||c=='G')
		{
		 f.drawLines(pm, Color.GREEN);
                f.save(in.readLine().trim());

		}
		//else{System.out.println("does not compute. c=="+c);}
		//System.out.println(pm);
	

	}
    }
}
