import java.awt.*;

import javax.swing.*;

import java.awt.event.*;

import java.awt.image.*;

import javax.imageio.*;



import java.io.*;

import java.util.*;



public class gui implements ActionListener,MouseListener, MouseMotionListener {

  

    public static final int LINE_MODE = 0;

    public static final int CIRCLE_MODE = 1;

    public static final int SPHERE_MODE = 2;

    public static final int TORUS_MODE = 3;

    public static final int HERMITE_MODE = 4;

    public static final int BEZIER_MODE = 5;

  

  

    JFrame frame;

    Canvas canvas;

    JPanel iface;

  

    JButton quit;

    JButton clear;

    JButton save;

    JLabel fnamelabel;

    JTextField fnamefield;

    JComboBox drawmode;

    JComboBox transformation;

    JTextField xarg;

    JTextField yarg;

    JTextField zarg;

    JLabel xlab;

    JLabel ylab;

    JLabel zlab;

    JButton apply;

  

    int clickcount=0;

    int[] xes = new int[10];

    int[] ys = new int[10];

  

    public gui() {

    

	frame = new JFrame();

	canvas = new Canvas();

	canvas.addMouseListener(this);

	canvas.addMouseMotionListener(this);

    

	//set window defaults

	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

	frame.getContentPane().setLayout(new FlowLayout());

    

	//add canvas

	frame.getContentPane().add(canvas);

    

	//set up the interface area

	iface = new JPanel();

	iface.setLayout(new GridLayout(10,1));

    

	//add each interface element

	drawmode = new JComboBox();

	drawmode.addItem("line");

	drawmode.addItem("circle");

	drawmode.addItem("sphere");

	drawmode.addItem("torus");

	drawmode.addItem("hermite");

	drawmode.addItem("bezier");

	iface.add(drawmode);

    

	transformation = new JComboBox();

	transformation.addItem("translate");

	transformation.addItem("scale");

	transformation.addItem("x rotation");

	transformation.addItem("y rotation");

	transformation.addItem("z rotation");

    

	iface.add(transformation);

    

	xlab = new JLabel("X: ");

	ylab = new JLabel("Y: ");

	zlab = new JLabel("Z: ");

	xarg = new JTextField();

	yarg = new JTextField();

	zarg = new JTextField();

    

	iface.add(xlab);

	iface.add(xarg);

	iface.add(ylab);

	iface.add(yarg);

	iface.add(zlab);

	iface.add(zarg);

    

	fnamelabel = new JLabel("Filename");

	fnamefield = new JTextField(4);

	iface.add(fnamelabel);

	iface.add(fnamefield);

    

	apply = new JButton("Apply");

	quit = new JButton("Quit");

	clear = new JButton("Clear");

	save = new JButton("Save");

    

	apply.addActionListener(this);

	quit.addActionListener(this);

	clear.addActionListener(this);

	save.addActionListener(this);

	iface.add(apply);

	iface.add(clear);

	iface.add(save);

	iface.add(quit);

    

	//add interface

	frame.getContentPane().add(iface);

    

	frame.pack();

	frame.setVisible(true);

    }



    public void mouseClicked(MouseEvent e) {

    

	int x,y;

	x = e.getX();

	y = e.getY();

    

	String mode=(String)drawmode.getSelectedItem();

    

	if ( mode.equals("torus") && clickcount == 0) {

	    xes[clickcount] = x;

	    ys[clickcount] = y;

	    clickcount++;

	}

    

	if ( mode.equals("hermite") && clickcount < 4) {

	    xes[clickcount] = x;

	    ys[clickcount] = y;

	    clickcount++;

	}

    

	if ( mode.equals("bezier") && clickcount < 4) {

	    xes[clickcount] = x;

	    ys[clickcount] = y;

	    clickcount++;

	}

    

    }

  

    public void mouseDragged(MouseEvent e) {

	int x,y;

	x = e.getX();

	y = e.getY();

	double rx, ry, rz;

	rx = 0;

	ry = 0;

	rz = 0;

    

	String mode=(String)drawmode.getSelectedItem();

    

    

	if ( !xarg.getText().equals("") )

	    rx = Double.parseDouble(xarg.getText()) * Math.PI / 180;

    

	if ( !yarg.getText().equals("") )

	    ry = Double.parseDouble(yarg.getText()) * Math.PI / 180;

 

	if ( !zarg.getText().equals("") )

	    rz = Double.parseDouble(zarg.getText()) * Math.PI / 180;

    

	if ( mode.equals("line") )      

	    canvas.setDrawing(xes[0], ys[0], x, y, 0, 0, rx, ry, rz, LINE_MODE);

    

	else if ( mode.equals("circle") ) 

	    canvas.setDrawing(xes[0], ys[0], x, y, 0, 0, rx, ry, rz, CIRCLE_MODE);

    

	else if ( mode.equals("sphere") ) 

	    canvas.setDrawing(xes[0], ys[0], x, y, 0, 0, rx, ry, rz, SPHERE_MODE);

    

	else if ( mode.equals("torus") ) 

	    canvas.setDrawing(xes[0], ys[0], xes[1], ys[1], x, y, rx, ry, rz, TORUS_MODE);

    

	canvas.update(canvas.getGraphics());

	canvas.clearTmp();

    }

  

    public void mousePressed(MouseEvent e)    {

	int x,y;

	x = e.getX();

	y = e.getY();
	String mode=(String)drawmode.getSelectedItem();

	if ( mode.equals("line") 

	     || mode.equals("circle") 

	     || mode.equals("sphere") ) {

	    if (clickcount == 0) {

        

		xes[clickcount] = x;

		ys[clickcount] = y;

		clickcount++;

	    }

	}       

    

	else if ( mode.equals("torus") && clickcount == 1) {

      

	    xes[clickcount] = x;

	    ys[clickcount] = y;

	    clickcount++;

	}

    }

  

    public void mouseReleased(MouseEvent e) {

	int x,y;

	x = e.getX();

	y = e.getY();

	double rx, ry, rz;

	rx = 0;

	ry = 0;

	rz = 0;

    

	if ( !xarg.getText().equals("") )

	    rx = Double.parseDouble(xarg.getText()) * Math.PI / 180;

    

	if ( !yarg.getText().equals("") )

	    ry = Double.parseDouble(yarg.getText()) * Math.PI / 180;

    

	if ( !zarg.getText().equals("") )

	    rz = Double.parseDouble(zarg.getText()) * Math.PI / 180;



    

	String mode=(String)drawmode.getSelectedItem();

	if (mode.equals("line")) {

	    if (clickcount==1) {

		canvas.addLine(xes[0], ys[0], 0, x, y, 0);

		clickcount=0;

	    }

	}

	else if ( mode.equals("circle") ) {

	    canvas.addCircle(xes[0], ys[0], x, y);

	    clickcount = 0;

	}

	else if ( mode.equals("sphere") ) {

	    canvas.addSphere(xes[0], ys[0], x, y, rx, ry, rz);

	    clickcount = 0;

	}

	else if ( mode.equals("torus") && clickcount == 2 ) {

	    canvas.addTorus(xes[0], ys[0], xes[1], ys[1], x, y, rx, ry, rz);

	    clickcount = 0;

	}

	else if ( mode.equals("hermite") && clickcount == 4) {

	    canvas.addHermite(xes[0], ys[0], xes[2], ys[2], xes[1], ys[1], xes[3], ys[3]);

	    clickcount = 0;

	}

	else if ( mode.equals("bezier") && clickcount == 4) {

	    canvas.addBezier(xes[0], ys[0], xes[2], ys[2], xes[1], ys[1], xes[3], ys[3]);

	    clickcount = 0;

	}

    

    

	canvas.stopDrawing();

    }

  

    //needed to implement MouseListener and MouseMotionListener

    public void mouseMoved(MouseEvent e) {}  

    public void mouseEntered(MouseEvent e) {}

    public void mouseExited(MouseEvent e) {}

  

  

    public void actionPerformed(ActionEvent e) {

	if (e.getSource()==quit) {

	    System.exit(0);

	}

	else if (e.getSource() == apply) {

      

	    String mode=(String)transformation.getSelectedItem();

	    if ( mode.equals("translate") ) {

        

		canvas.translate( Double.parseDouble( xarg.getText() ),

				  Double.parseDouble( yarg.getText() ),

				  Double.parseDouble( zarg.getText() ) );

	    }

	    else if ( mode.equals("scale") ) {

        

		canvas.scale( Double.parseDouble( xarg.getText() ),

			      Double.parseDouble( yarg.getText() ),

			      Double.parseDouble( zarg.getText() ) );

	    }

	    else if ( mode.equals("x rotation") ) {

        

		canvas.rotX( Double.parseDouble( xarg.getText() ));

	    }

	    else if ( mode.equals("y rotation") ) {

        

		canvas.rotY( Double.parseDouble( yarg.getText() ));

	    }

	    else if ( mode.equals("z rotation") ) {

        

		canvas.rotZ( Double.parseDouble( zarg.getText() ));

	    }

	}

    

	else if (e.getSource()==save) {

	    // save

	    System.out.println("Saving: "+ fnamefield.getText() );

	    BufferedImage bi = canvas.getBufferedImage();

	    try {

		File fn = new File(fnamefield.getText());

		ImageIO.write(bi,"png",fn);

	    }

	    catch (IOException ex) { }

	}

	else if (e.getSource()==clear) {

	    canvas.clearPoints();

	}

    }

  

    public static void main(String[] args) {

    

	gui g = new gui();

    }

}
    
