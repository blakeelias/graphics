import java.io.*;
import java.util.*;
import java.lang.Math.*;

public class PointMatrix extends Matrix {

    private int lastCol;

    public PointMatrix() {
	super();
	lastCol = 0;
    }

    public PointMatrix( int c ) {
	super( c );
	lastCol = 0;
    }

    //Don't worry about this method yet
 public void renderCurve(double x1, double y1, double x2, double y2,
                            double x3, double y3, double x4, double y4, double step) {
 }

    public void renderTorusMesh(double r1, double r2, 
				double offx, double offy) {

//Despite the wiki claiming this works as a taurus, it just makes a circle =.= 

//not commented out code is original, works
	for(double phi =0;phi<=(1*Math.PI);phi+=(.1*Math.PI))
	{ 
	 for(double theta=0;theta<=(2*Math.PI);theta+=(.1*Math.PI))
	 {
	addPoint(r1*Math.cos(phi)+r2*Math.cos(theta)*Math.cos(phi)+offx,r2*Math.sin(theta)+offy,-1*r1*Math.sin(phi)-r2*Math.cos(theta)*Math.sin(phi));	
/*
addEdge((r1+r2*Math.cos(phi))*Math.cos(theta)+offx,(r1+r2*Math.cos(phi))*Math.sin(theta)+offy,r2*Math.sin(phi),(r1+r2*Math.cos((phi+.1*Math.PI)))*Math.cos(theta)+offx,(r1+r2*Math.cos((phi+.1*Math.PI)))*Math.sin(theta)+offy,r2*Math.sin((phi+.1*Math.PI)));
      addEdge((r1+r2*Math.cos(phi))*Math.cos(theta)+offx,(r1+r2*Math.cos(phi))*Math.sin(theta)+offy,r2*Math.sin(phi),(r1+r2*Math.cos(phi))*Math.cos((theta+.1*Math.PI))+offx,(r1+r2*Math.cos(phi))*Math.sin((theta+.1*Math.PI))+offy,r2*Math.sin(phi));*/
	 } 	
	}

    
    

    }		

    public void generateTorus(double r1, double r2, 
			      double offx, double offy) {
//not commented out code is modified from a classmate; I understand the concept behind it though
	for(double phi =0;phi<=(2*Math.PI);phi+=(.1*Math.PI))
	{ 
	 for(double theta=0;theta<=(2*Math.PI);theta+=(.1*Math.PI))
	 {
	//addPoint(r1*Math.cos(phi)+r2*Math.cos(theta)*Math.cos(phi)+offx,r2*Math.sin(theta)+offy,-1*r1*Math.sin(phi)-r2*Math.cos(theta)*Math.sin(phi));	

addEdge((r1+r2*Math.cos(phi))*Math.cos(theta)+offx,(r1+r2*Math.cos(phi))*Math.sin(theta)+offy,r2*Math.sin(phi),(r1+r2*Math.cos((phi+.1*Math.PI)))*Math.cos(theta)+offx,(r1+r2*Math.cos((phi+.1*Math.PI)))*Math.sin(theta)+offy,r2*Math.sin((phi+.1*Math.PI)));
      addEdge((r1+r2*Math.cos(phi))*Math.cos(theta)+offx,(r1+r2*Math.cos(phi))*Math.sin(theta)+offy,r2*Math.sin(phi),(r1+r2*Math.cos(phi))*Math.cos((theta+.1*Math.PI))+offx,(r1+r2*Math.cos(phi))*Math.sin((theta+.1*Math.PI))+offy,r2*Math.sin(phi));
	 } 	
	}
    }


    public void renderSphereMesh(double r, double offx, double offy ) {
	
	int count = 1;
	
	for(double phi =0;phi<=(1*Math.PI);phi+=(.1*Math.PI))
	{ 
	 for(double theta=0;theta<=(2*Math.PI);theta+=(.1*Math.PI))
	 {
	
	addPoint(r*Math.cos(theta)*Math.cos(phi)+offx,r*Math.sin(theta)+offy,-r*Math.cos(theta)*Math.sin(phi));
	//addEdge(r*Math.sin(phi)*Math.cos(theta)+offx,r*Math.sin(phi)*Math.sin(theta)+offy,r*Math.cos(phi),r*Math.sin((phi+.1*Math.PI))*Math.cos((theta))+offx,r*Math.sin((phi+.1*Math.PI))*Math.sin(theta)+offy,r*Math.cos((phi+.1*Math.PI)));
        //  addEdge(r*Math.sin(phi)*Math.cos(theta)+offx,r*Math.sin(phi)*Math.sin(theta)+offy,r*Math.cos(phi),r*Math.sin((phi))*Math.cos((theta+.1*Math.PI))+offx,r*Math.sin((phi))*Math.sin((theta+.1*Math.PI))+offy,r*Math.cos((phi)));
	
	 } 
	//theta=0;
	}
    }		
		
    public void generateSphere(double r, double offx, double offy) {
//AFTER MANY FRUITLESS EFFORTS I HAVE ABANDONED MY ANNOYING UNSUCCESSFUL ATTEMPT. BELOW IS ... CONVERTED.. CODE FROM A CLASSMATE 'TXU'. I UNDERSTAND THE WORKINGS BEHIND IT THOUGH. 




/*	PointMatrix temp= new PointMatrix(); //attempt 1
	double t =0;
	int c = (int)(1/step);
	int d =0;
	int count=0;
	for(;t<=1;t+=step) //longitude?
	{
		addEdge(m[0][d],m[1][d],m[2][d],m[0][c],m[1][c],m[2][c]); //m[d]m[d-(1/step)]
		for(;d<c;d++)
		{
		addEdge(m[0][d],m[1][d],m[2][d],m[0][d+1],m[1][d+1],m[2][d+1]); //m[d-1]m[d]
		
		}	
		c+=(int)(1/step);
		*/


	PointMatrix templong= new PointMatrix();
	PointMatrix templat= new PointMatrix();
	int c=0;
	int d=0;
	
	//for(d<99;c++)
		//{
		 /*for(int g=0;g<9;g++) //longitude 'ish
		 {
	if(c%10==9)
	{
if(c!=99)
{addEdge(m[0][c],m[1][c],m[2][c],m[0][c-9],m[1][c-9],m[2][c-9]); d+=10;}
else {addEdge(m[0][c],m[1][c],m[2][c],m[0][c-99],m[1][c-99],m[2][c-99]);}
	}			
else {addEdge(m[0][c],m[1][c],m[2][c],m[0][c+1],m[1][c+1],m[2][c+1]);}
			c++;
		 }*/
		
c=0;
 
	/*for(int g=0;c<99;g++)  //fail latitude
		 {
	if(c+10>99)//if(c/10==9)
	{addEdge(m[0][c],m[1][c],m[2][c],m[0][c-90],m[1][c-90],m[2][c-90]); d+=10;
	}			
else {addEdge(m[0][c],m[1][c],m[2][c],m[0][c+10],m[1][c+10],m[2][c+10]);}
			c++;
		 }*/
		
		//}
/*int i=0; int j=0;
		 for(i=0;i<10/2;++i)
    {
      for(j=0;j<10-1;j++)
        {
          //longitude
          addEdge(m[0][10*i+j],m[1][10*i+j],
                   m[2][10*i+j],m[0][10*i+j+1],
                   m[1][10*i+j+1],m[2][10*i+j+1]);
          
          //latitude
          addEdge(m[0][10*i+j],m[1][10*i+j],
                   m[2][10*i+j],m[0][10*(i+1)+j],
                   m[1][10*(i+1)+j],m[2][10*(i+1)+j]); 
        }

    }*/
double theta=0; 
	double phi =0;	
	int count = 1;
	
	for(;phi<=(1*Math.PI);phi+=(.1*Math.PI))
	{ 
	 for(;theta<=(2*Math.PI);theta+=(.1*Math.PI))
	 {
	
	//addPoint(r*Math.cos(theta)*Math.cos(phi)+offx,r*Math.sin(theta)+offy,-r*Math.cos(theta)*Math.sin(phi));
	addEdge(r*Math.sin(phi)*Math.cos(theta)+offx,r*Math.sin(phi)*Math.sin(theta)+offy,r*Math.cos(phi),r*Math.sin((phi+.1*Math.PI))*Math.cos((theta))+offx,r*Math.sin((phi+.1*Math.PI))*Math.sin(theta)+offy,r*Math.cos((phi+.1*Math.PI)));
          addEdge(r*Math.sin(phi)*Math.cos(theta)+offx,r*Math.sin(phi)*Math.sin(theta)+offy,r*Math.cos(phi),r*Math.sin((phi))*Math.cos((theta+.1*Math.PI))+offx,r*Math.sin((phi))*Math.sin((theta+.1*Math.PI))+offy,r*Math.cos((phi)));
	
	 } 
	theta=0;
	}
    	

	//this.m=templat.m;
   }
    public void renderCircle(double r, double offx, double offy, double step) {
	double k =0;
	int c=0;
/*	PointMatrix temp= new PointMatrix();

	for(;c<(m[0].length);c+=1)//(;k<=1;k+=step)
	{
	/*if(c==0){ addEdge( m[0][0],m[0][1]],m[0][2]], m[c-1][0],m[c-1][1]],m[c-1][2]] );}
	else
	{addEdge( m[c][0],m[c][1]],m[c][2]], m[c-1][0],m[c-1][1]],m[c-1][2]] );} 
	if(c==0){}// temp.addEdge( m[0][0],m[1][0],m[2][0], m[0][lastCol],m[1][lastCol],m[2][lastCol] );}
	else
	{//System.out.println("c: "+c+" / length: "+m[0].length+"");
	//System.out.println("K: "+k+" \n");

	temp.addEdge( m[0][c],m[1][c],m[2][c], m[0][c-1],m[1][c-1],m[2][c-1] );}  //c-1 on the right side
	//temp.addEdge( m[c][0],m[c][1],m[c][2], m[c-1][0],m[c-1][1],m[c-1][2] );} 
	//c++;
	
	} 
	temp.addEdge( m[0][0],m[1][0],m[2][0], m[0][lastCol],m[1][lastCol],m[2][lastCol] );
	//self=temp.copy();


	
	this.m=temp.m;
	//double k;*/
	for(k=0;k<=1;k+=step)
	{
	addEdge(r*Math.cos(k*2*Math.PI)+ offx,r*Math.sin(k*2*Math.PI)+ offy,0, r*Math.cos((k+step)*2*Math.PI)+ offx,r*Math.sin((k+step)*2*Math.PI)+ offy,0);
	//System.out.println(""+k+" +1 ...\n");
	
	}
	
    }

    public void generateCircle(double r, double offx, double offy, double step) {
	double k;
	for(k=0;k<=1;k+=step)
	{
	addPoint(r*Math.cos(k*2*Math.PI)+ offx,r*Math.sin(k*2*Math.PI)+ offy,0);
	//System.out.println(""+k+" +1 ...\n");
	
	}

    }

    /*======== public void addPoint() ==========
      Inputs:  int x
      int y
      int z 
      Returns: 
      adds (x, y, z) to the calling object
      if lastcol is the maxmium value for this current matrix, 
      call grow
      ====================*/
    public void addPoint(double x, double y, double z) {

	if ( lastCol == m[0].length ) 
	    grow();
	
	m[0][lastCol] = x;
	m[1][lastCol] = y;
	m[2][lastCol] = z;
	m[3][lastCol] = 1;
	lastCol++;
    }

    /*======== public void addEdge() ==========
      Inputs:  int x0
      int y0
      int z0
      int x1
      int y1
      int z1 
      Returns: 
      adds the line connecting (x0, y0, z0) and (x1, y1, z1)
      to the calling object
      should use addPoint
      ====================*/
    public void addEdge(double x0, double y0, double z0, 
			double x1, double y1, double z1) {

	addPoint(x0, y0, z0);
	addPoint(x1, y1, z1);
    }



    /*======== accessors ==========
      ====================*/
    public int getLastCol() {
	return lastCol;
    }
    public int  getX(int c) {
	return (int)m[0][c];
    }
    public int  getY(int c) {
	return (int)m[1][c];
    }
    public int  getZ(int c) {
	return (int)m[2][c];
    }
    public void clear() {
	super.clear();
	lastCol = 0;
    }
   
    public PointMatrix copy() {
	
	PointMatrix n = new PointMatrix( m[0].length );
	for (int r=0; r<m.length; r++)
	    for (int c=0; c<m[r].length; c++)
		n.m[r][c] = m[r][c];
	n.lastCol = lastCol;
	return n;
    }

}
