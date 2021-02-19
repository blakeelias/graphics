import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.awt.image.*;
import javax.swing.event.*;
import javax.imageio.*;

import java.io.*;
import java.util.*;

public class gui implements ActionListener,MouseListener, MouseMotionListener, ChangeListener {
  
  public static final int LINE_MODE = 0;
  public static final int CIRCLE_MODE = 1;
  public static final int SPHERE_MODE = 2;
  public static final int TORUS_MODE = 3;
  public static final int HERMITE_MODE = 4;
  public static final int BEZIER_MODE = 5;
  public static final int BOX_MODE = 6;
  public static final int TRIPRISM_MODE = 7;
  
  public static final int POLY_CIRCLE_MODE = 11;
  public static final int POLY_BOX_MODE = 12;
  public static final int POLY_SPHERE_MODE = 13;
  public static final int POLY_TORUS_MODE = 14;
  public static final int POLY_TRIANGLE_MODE = 15;
  public static final int POLY_TRIPRISM_MODE = 16;
  public static final int POLY_RECTANGLE_MODE = 17;
  public static final int POLY_QUAD_MODE = 18;
  
  
  JFrame frame;
  Canvas canvas;
  JPanel iface;
  
  JButton quit;
  JButton clear;
  JButton save;
  JButton camera;
  JButton light;
  JButton select;
  JButton shade;
  JLabel fnamelabel;
  JTextField fnamefield;
  JComboBox drawmode;
  JComboBox drawmode2;
  JLabel two;
  JLabel three;
  JComboBox transformation;
  JComboBox threeD;
  JTextField xarg;
  JTextField yarg;
  JTextField zarg;
  JLabel xlab;
  JLabel ylab;
  JLabel zlab;
  JButton apply;
  JSlider ambient;
  JSlider diffuse;
  JSlider specular;
  JSlider red;
  JSlider green;
  JSlider blue;
  
  JLabel amb;
  JLabel dif;
  JLabel spec;
  JLabel rd;
  JLabel gr;
  JLabel bl;
  
  int clickcount=0;
  int[] xes = new int[10];
  int[] ys = new int[10];
  
  int camcount = 0;
  int xcam = 0;
  int ycam = 0;
  int zcam = -35;
  
  int lightup = 0;
  int xlight = 0;
  int ylight = 0;
  int zlight = -35;
  double ambConstant = 0;
  double difConstant = 0;
  double specConstant = 0;
  
  int selector = 0;
  int xselect = 0;
  int yselect = 0;
  int shades = 0;
  
  int[] rgb = new int[3];
  
 /* int tricount = 0;
  int quadcount = 0; */
  
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
    
    frame.setTitle("Cool Graphics!!");
    
    //set up the interface area
    iface = new JPanel();
    iface.setLayout(new GridLayout(20,1));
    
    //add each interface element
    threeD = new JComboBox();
    threeD.addItem("2D");
    threeD.addItem("3D");
    iface.add(threeD);
    
    two = new JLabel("2D non-Polygon Below");
    three = new JLabel("3D Polygon Stuff Below");
    
    transformation = new JComboBox();
    transformation.addItem("translate");
    transformation.addItem("scale");
    transformation.addItem("x rotation");
    transformation.addItem("y rotation");
    transformation.addItem("z rotation");
    iface.add(transformation);
    
    iface.add(two);
    iface.add(three);
    
    drawmode = new JComboBox();
    drawmode.addItem("line");
    drawmode.addItem("circle");
    drawmode.addItem("box");
    drawmode.addItem("sphere");
    drawmode.addItem("torus");
    drawmode.addItem("hermite");
    drawmode.addItem("bezier");
    drawmode.addItem("triangular prism");
    iface.add(drawmode);
    
    drawmode2 = new JComboBox();
    drawmode2.addItem("circle");
    drawmode2.addItem("box");
    drawmode2.addItem("sphere");
    drawmode2.addItem("torus");
    drawmode2.addItem("triangle");
    drawmode2.addItem("triangular prism");
    drawmode2.addItem("rectangle");
    drawmode2.addItem("quadrilateral");
    iface.add(drawmode2);
    
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
    
    apply = new JButton("Apply Transformation");
    quit = new JButton("Quit");
    clear = new JButton("Clear All");
    save = new JButton("Save File");
    camera = new JButton("Set Camera");
    light = new JButton("Set Light Source");
    select = new JButton("Select Point");
    shade = new JButton("Shading On/Off");
    
    apply.addActionListener(this);
    quit.addActionListener(this);
    clear.addActionListener(this);
    save.addActionListener(this);
    camera.addActionListener(this);
    light.addActionListener(this);
    select.addActionListener(this);
    shade.addActionListener(this);
    iface.add(apply);
    iface.add(clear);
    iface.add(save);
    iface.add(quit);
    iface.add(camera);
    iface.add(light);
    iface.add(select);
    iface.add(shade);
    
    amb = new JLabel("Set Ambient Light: ");
    dif = new JLabel("Set Diffuse Light: ");
    spec = new JLabel("Set Specular Light: ");
    
    ambient = new JSlider(0, 100, 80);
    diffuse = new JSlider(0, 100, 50);
    specular = new JSlider(0, 100, 20);
    ambient.addChangeListener(this);
    diffuse.addChangeListener(this);
    specular.addChangeListener(this);
    
    rd = new JLabel("Choose Color: Red ");
    gr = new JLabel("Choose Color: Green ");
    bl = new JLabel("Choose Color: Blue ");
    
    red = new JSlider(0, 255, 0);
    green = new JSlider(0, 255, 0);
    blue = new JSlider(0, 255, 255);
    red.addChangeListener(this);
    green.addChangeListener(this);
    blue.addChangeListener(this);
    
    rgb[0] = 0; rgb[1] = 0; rgb[2] = 0;
    
    iface.add(amb);
    iface.add(ambient);
    iface.add(dif);
    iface.add(diffuse);
    iface.add(spec);
    iface.add(specular);
    
    iface.add(rd);
    iface.add(red);
    iface.add(gr);
    iface.add(green);
    iface.add(bl);
    iface.add(blue);
    
    //add interface
    frame.getContentPane().add(iface);
    
    frame.pack();
    frame.setVisible(true);
  }

  public void mouseClicked(MouseEvent e) {
    
    int x,y;
    x = e.getX();
    y = e.getY();
    
    String twothree = (String)threeD.getSelectedItem();
    String mode=(String)drawmode.getSelectedItem();
    String mode2=(String)drawmode2.getSelectedItem();
    
    if ( twothree.equals("2D") )
    {
    
      if ( mode.equals("torus") && clickcount == 0) {
        xes[clickcount] = x;
        ys[clickcount] = y;
        clickcount++;
        System.out.println("You have selected " + clickcount + " points. Select another point.");
      }
      
      if ( mode.equals("hermite") && clickcount < 4) {
        xes[clickcount] = x;
        ys[clickcount] = y;
        clickcount++;
        System.out.println("You have selected " + clickcount + " points. Select another point.");
      }
      
      if ( mode.equals("bezier") && clickcount < 4) {
        xes[clickcount] = x;
        ys[clickcount] = y;
        clickcount++;
        System.out.println("You have selected " + clickcount + " points. Select another point.");
      }
      
      /* if ( mode.equals("triangular prism") && clickcount < 3) {
       xes[clickcount] = x;
       ys[clickcount] = y;
       clickcount++;
       System.out.println("You have selected " + clickcount + " points. Select another point.");
       }*/
      
      /*if ( mode.equals("triangular prism") && clickcount >= 3) {
       canvas.addTriPrism(xes[0], ys[0], xes[1], ys[1], xes[2], ys[2]);
       clickcount = 0;
       }*/
      
    }
    
    else if ( twothree.equals("3D") )
    {
      if ( mode2.equals("torus") && clickcount == 0) {
        xes[clickcount] = x;
        ys[clickcount] = y;
        clickcount++;
        System.out.println("You have selected " + clickcount + " points. Select another point.");
      }
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
    
    String twothree = (String)threeD.getSelectedItem();
    String mode=(String)drawmode.getSelectedItem();
    String mode2=(String)drawmode2.getSelectedItem();
    
    
    if ( !xarg.getText().equals("") )
      rx = Double.parseDouble(xarg.getText()) * Math.PI / 180;
    
    if ( !yarg.getText().equals("") )
      ry = Double.parseDouble(yarg.getText()) * Math.PI / 180;
 
    if ( !zarg.getText().equals("") )
      rz = Double.parseDouble(zarg.getText()) * Math.PI / 180;
    
    if ( twothree.equals("2D") )
    {
    
      if ( mode.equals("line") )      
        canvas.setDrawing(xes[0], ys[0], x, y, 0, 0, 0, 0, 0, 0, rx, ry, rz, LINE_MODE, rgb, 0);
      
      else if ( mode.equals("circle") ) 
        canvas.setDrawing(xes[0], ys[0], x, y, 0, 0, 0, 0, 0, 0, rx, ry, rz, CIRCLE_MODE, rgb, 0);
      
      else if ( mode.equals("sphere") ) 
        canvas.setDrawing(xes[0], ys[0], x, y, 0, 0, 0, 0, 0, 0, rx, ry, rz, SPHERE_MODE, rgb, 0);
      
      else if ( mode.equals("box") )
        canvas.setDrawing(xes[0], ys[0], x, y, 0, 0, 0, 0, 0, 0, rx, ry, rz, BOX_MODE, rgb, 0);
      
      else if ( mode.equals("torus") ) 
        canvas.setDrawing(xes[0], ys[0], xes[1], ys[1], x, y, 0, 0, 0, 0, rx, ry, rz, TORUS_MODE, rgb, 0);
      
      else if ( mode.equals("bezier") ) 
        canvas.setDrawing(xes[0], ys[0], xes[1], ys[1], x, y, xes[2], ys[2], 0, 0, rx, ry, rz, BEZIER_MODE, rgb, 0);
      
      else if ( mode.equals("hermite") ) 
        canvas.setDrawing(xes[0], ys[0], xes[1], ys[1], x, y, xes[2], ys[2], 0, 0, rx, ry, rz, HERMITE_MODE, rgb, 0);
      
      else if ( mode.equals("triangular prism") ) 
        canvas.setDrawing(xes[0], ys[0], x, y, 0, 0, 0, 0, 0, 0, rx, ry, rz, TRIPRISM_MODE, rgb, 0);
      
    }
    
    else if ( twothree.equals("3D") ) // TEST SHADING ON/OFF!!!!!!!
    {
      
      if ( mode2.equals("circle") ) 
        canvas.setDrawing(xes[0], ys[0], x, y, 0, 0, 0, 0, 0, 0, rx, ry, rz, POLY_CIRCLE_MODE, rgb, shades);
      
      else if ( mode2.equals("sphere") ) 
        canvas.setDrawing(xes[0], ys[0], x, y, 0, 0, 0, 0, 0, 0, rx, ry, rz, POLY_SPHERE_MODE, rgb, shades);
      
      else if ( mode2.equals("box") )
        canvas.setDrawing(xes[0], ys[0], x, y, 0, 0, 0, 0, 0, 0, rx, ry, rz, POLY_BOX_MODE, rgb, shades);
      
      else if ( mode2.equals("torus") ) 
        canvas.setDrawing(xes[0], ys[0], xes[1], ys[1], x, y, 0, 0, 0, 0, rx, ry, rz, POLY_TORUS_MODE, rgb, shades);
      
      else if ( mode2.equals("triangular prism") ) 
        canvas.setDrawing(xes[0], ys[0], x, y, 0, 0, 0, 0, 0, 0, rx, ry, rz, POLY_TRIPRISM_MODE, rgb, shades);
      
    }
    
    
    canvas.update(canvas.getGraphics());
    canvas.clearTmp();
  }
  
  public void mousePressed(MouseEvent e)    {
    int x,y;
    x = e.getX();
    y = e.getY();
    
    if (camcount > 0)
    {
      xcam = x;
      ycam = y;
      camcount = 0;
      System.out.println("Camera Location is (" + x + ", " + y +", " + zcam+ ")");
    }
    
    if (lightup > 0)
    {
      xlight = x;
      ylight = y;
      lightup = 0;
      System.out.println("Light Source is (" + x + ", " + y +", " + zlight + ")");
    }
    
    if (selector > 0)
    {
      xselect = x;
      yselect = y;
      selector = 0;
      System.out.println("Selected Point is (" + x + ", " + y + ")");
    }
    
    if (shades > 0) // should work with Polygon p; boolean p.contains(selected point);
    {
      /*Polygon p = new Polygon();
      p.addPoint(5,5);
      p.addPoint(200,5);
      p.addPoint(200,200);
      p.addPoint(5,200);
      canvas.shadePolygon(p);*/
    }
    
    String twothree = (String)threeD.getSelectedItem();
    String mode=(String)drawmode.getSelectedItem();
    String mode2=(String)drawmode2.getSelectedItem();
    
    if ( twothree.equals("2D") )
    {
    
      if ( mode.equals("line") 
            || mode.equals("circle") 
            || mode.equals("sphere")
            || mode.equals("box")
            || mode.equals("triangular prism") ) {
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
      
      /*  else if ( mode.equals("triangular prism") && clickcount < 3) {
       xes[clickcount] = x;
       ys[clickcount] = y;
       clickcount++;
       } */
      
      /* else if ( mode.equals("triangular prism") && clickcount >= 3) {
       canvas.addTriPrism(xes[0], ys[0], xes[1], ys[1], xes[2], ys[2]);
       clickcount = 0;
       } */
      
      /*  else if (mode.equals("hermite") || mode.equals("bezier")) {
       if (clickcount < 4) {
       xes[clickcount] = x;
       ys[clickcount] = y;
        clickcount++;
      }
    }*/
    
    }
    
    else if ( twothree.equals("3D") )
    {
      if ( mode2.equals("triangular prism") 
            || mode.equals("circle") 
            || mode.equals("sphere")
            || mode.equals("box") ) {
        if (clickcount == 0) {
          
          xes[clickcount] = x;
          ys[clickcount] = y;
          clickcount++;
        }
      }
      
      else if ( mode2.equals("torus") && clickcount == 1) {
        
        xes[clickcount] = x;
        ys[clickcount] = y;
        clickcount++;
      }
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

    
    String twothree = (String)threeD.getSelectedItem();
    String mode=(String)drawmode.getSelectedItem();
    String mode2=(String)drawmode2.getSelectedItem();
    
    if ( twothree.equals("2D") )
    {
      
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
        canvas.addSphere(x, y, xes[0], ys[0], rx, ry, rz);
        clickcount = 0;
      }
      else if ( mode.equals("box") ) {
        canvas.addBox(x, y, xes[0], ys[0], rx, ry, rz);
        clickcount = 0;
      }
      else if ( mode.equals("torus") /*&& clickcount == 0*/ ) {
        canvas.addTorus(xes[0], ys[0], xes[1], ys[1], x, y, rx, ry, rz);
        clickcount = 0;
      }
      else if ( mode.equals("hermite") && clickcount >= 3) {
        canvas.addHermite(xes[0], ys[0], xes[2], ys[2], xes[1], ys[1], xes[3], ys[3]);
        clickcount = 0;
      }
      else if ( mode.equals("bezier") && clickcount >= 3) {
        canvas.addBezier(xes[0], ys[0], xes[2], ys[2], xes[1], ys[1], xes[3], ys[3]);
        clickcount = 0;
      }
      
      else if ( mode.equals("triangular prism") ) {
        canvas.addTriPrism(xes[0], ys[0], x, y);
        clickcount = 0; 
      } 
      
    }
    
    else if ( twothree.equals("3D") )
    {
      Color c = new Color(rgb[0], rgb[1], rgb[2]);
      
      if ( mode2.equals("circle") ) {
        canvas.addPolyCircle(xes[0], ys[0], x, y, c);
        clickcount = 0;
      }
      else if ( mode2.equals("sphere") ) {
        canvas.addPolySphere(x, y, xes[0], ys[0], rx, ry, rz, c);
        clickcount = 0;
      }
      else if ( mode2.equals("box") ) {
        canvas.addPolyBox(x, y, xes[0], ys[0], rx, ry, rz, c);        
        clickcount = 0;
      }
      else if ( mode2.equals("torus") /*&& clickcount == 0*/ ) {
        canvas.addPolyTorus(xes[0], ys[0], xes[1], ys[1], x, y, rx, ry, rz, c);
        clickcount = 0;
      }
      else if ( mode2.equals("triangular prism") ) {
        canvas.addPolyTriPrism(xes[0], ys[0], x, y, c);
        clickcount = 0; 
      } 
      
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
    else if (e.getSource()==camera)
    {
      camcount++;
    }
    else if (e.getSource()==light)
    {
      lightup++;
    }
    else if (e.getSource()==select)
    {
      selector++;
    }
    else if (e.getSource()==shade)
    {
      if (shades == 1) { // On
        shades = 0;
        System.out.println("Shading is OFF");
      }
      else if (shades == 0) { // Off
        shades = 1;
        System.out.println("If you are in 3D mode, shading is ON");
      }
    }
  }
  
  public void stateChanged(ChangeEvent e)
  {
    ambConstant = ambient.getValue() / 100;
    difConstant = diffuse.getValue() / 100;
    specConstant = specular.getValue() / 100;
    
    rgb[0] = red.getValue();
    rgb[1] = green.getValue();
    rgb[2] = blue.getValue();
  }
  
  public static void main(String[] args) {
    
    gui g = new gui();
  }
}

