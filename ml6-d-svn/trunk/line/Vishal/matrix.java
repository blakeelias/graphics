import java.io.*;
import java.util.*;


//Uh I didn't realize that there was a skeleton for the matrix, so I built it all from scratch.
//I can edit this file later, but it is like 1 AM right now. But this file can do all the skeleton 
// can do and more! Notice the mv function, which moves the content of a smaller matrix to a larger
// matrix. Useful!

// - Vishal

class matrix{
    int[][] mat;
    int xdim, ydim;
    public matrix (int x, int y){
	mat = new int[x][y];
        xdim = x;
        ydim = y;
    }
   
    /*    public matrix (int[][] inputArray){
	mat = inputArray;
	xdim = inputArray.length;
	ydim = inputArray[0].length;
    }
    */

    public void fill(int x, int y, int val){
	mat[x][y] = val;
    }

    public void fill1(){
	for (int i = 0; i<xdim; i++)
	    for (int j = 0; j<ydim; j++)
                mat[i][j] = i + j;
    }


    public void print(){
        System.out.println();
	for (int i = 0; i<xdim; i++){
	    for (int j = 0; j<ydim; j++)
		System.out.print("" + mat[i][j] + "\t");
                  System.out.println();
    }
   } 

    public void mult(int m){
	for (int i = 0; i<xdim; i++)
	    for (int j = 0; j<ydim; j++)
		mat[i][j] = m * mat[i][j];
    }

    public void add(matrix m2){
	for (int i = 0; i<xdim; i++)
	    for (int j = 0; j<ydim; j++)
		mat[i][j] += m2.mat[i][j];
    }

    public void identity(){
        for (int i = 0; i<xdim; i++)
	    for (int j = 0; j<ydim; j++){
		if (i == j)
		    mat[i][j] = 1;
		else
		    mat[i][j] = 0;
	    }
    }

    public void mv(matrix dest){
	if (dest.xdim >= this.xdim && dest.ydim >= this.ydim){
	    for (int i = 0; i<this.xdim; i++)
		for (int j = 0; j<this.ydim; j++)
		    dest.mat[i][j] = this.mat[i][j];
	}
    }

    public matrix expand(int newx, int newy){
	if (newx > xdim && newy >ydim){
	    matrix newMat = new matrix(newx, newy);
	    this.mv(newMat);
	    return newMat;
	}
	return this;
    }

    public matrix mult(matrix m){
	if (this.ydim == m.xdim){
	    matrix newm = new matrix (this.xdim, m.ydim);
	    for (int i = 0; i<this.xdim; i++)
		for (int j = 0; j<m.ydim; j++){
		    int u = 0;
		    for (int k = 0; k<this.ydim; k++)
			u += this.mat[i][k] * m.mat[k][j];
		    newm.mat[i][j] = u;
		}
	    return newm;
	}
	return this;
    }

public static void main (String[] args){
    System.out.println("Hello World.");
    matrix m = new matrix(3,3);
    m.fill1();
    m.print();
    m.mult(2);
    m.print();
    m.identity();
    m.print();

    matrix m1 = new matrix (3,3);
    m.mv (m1);
    m1.print();

    matrix m2 = new matrix (1,4);
    m2.fill(0,0,2); 
    m2.fill(0,1,0); 
    m2.fill(0,2,-1); 
    m2.fill(0,3,1);
    m2.print();

    matrix m3 = new matrix (4,3);
    m3.fill(0,0,1);
    m3.fill(0,1,5);
    m3.fill(0,2,-7);
    m3.fill(1,0,1);
    m3.fill(1,1,1);
    m3.fill(1,2,0);
    m3.fill(2,0,0);
    m3.fill(2,1,-1);
    m3.fill(2,2,1);
    m3.fill(3,0,2);
    m3.fill(3,1,0);
    m3.fill(3,2,0);
    m3.print();

    m2 = m2.mult(m3);
    m2.print();

    

    
 }
}
