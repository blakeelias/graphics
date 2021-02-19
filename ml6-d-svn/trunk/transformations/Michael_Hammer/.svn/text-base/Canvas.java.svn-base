import java.io.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.awt.image.*;
import javax.imageio.*;

public class Canvas extends JPanel implements ActionListener, MouseListener, MouseMotionListener 
{
  private PointMatrix edges;
  private BufferedImage img, img2;
  private PointMatrix tmpline;
  private Color c;
  boolean drawing = false;
  
  boolean entered = false;
  boolean pressed = false;
  
  private JComboBox combo;
  private JEditorPane epane, epane2, epane3;
  private JButton butt;
  
  public Canvas() 
  {
    super(null);
    edges = new PointMatrix();
    tmpline = new PointMatrix(2); 
    c = Color.blue;
    this.createInteractions();
    
  }
    
  public void createInteractions()
  {
    String[] trans = new String[5];
    trans[0] = "X-Rotate"; trans[1] = "Y-Rotate"; trans[2] = "Z-Rotate"; trans[3] = "Scale"; trans[4] = "Translate";
    combo = new JComboBox(trans);
    combo.setSelectedIndex(0);
    /*combo.setHorizontalAlignment(300);
    combo.setVerticalAlignment(300);*/
    combo.addActionListener(this);
    String comboS = "transformers";
    add(combo);
    
    epane = new JEditorPane();
    epane2 = new JEditorPane();
    epane3 = new JEditorPane();
    
  /*  epane.addActionListener(this);
    epane2.addActionListener(this);
    epane3.addActionListener(this);*/
    
    add(epane);
    add(epane2);
    add(epane3);
    
    String button = "Transform";
    String buttonAction = "Button";
    butt = new JButton(button);
    butt.addActionListener(this);
    butt.setMnemonic(KeyEvent.VK_T);
    butt.setActionCommand(buttonAction);
    
    add(butt);
    
    Insets in = this.getInsets();
    Dimension d = new Dimension();
    d = combo.getPreferredSize();
    combo.setBounds(455 + in.left, 15 + in.top, d.width + 10, d.height);
    
    d = epane.getPreferredSize();
    epane.setBounds(455 + in.left, 55 + in.top, d.width - 30, d.height);
    
    d = epane2.getPreferredSize();
    epane2.setBounds(455 + in.left, 95 + in.top, d.width - 30, d.height);
    
    d = epane3.getPreferredSize();
    epane3.setBounds(455 + in.left, 135 + in.top, d.width - 30, d.height);
    
    d = butt.getPreferredSize();
    butt.setBounds(325 + in.left, 75 + in.top, d.width, d.height);
    
    addMouseListener(this);
    addMouseMotionListener(this);

  }

  /*======== public void setDrawing() ==========
   Inputs:  
   int x0
   int y0
   int x1
   int y1 
   Returns: 
   sets drawing to true and adds a line to the tmpLine PointMatrix
   
   ====================*/
  public void setDrawing(int x0, int y0, int x1, int y1) 
  {
    drawing = true;
    edges.addEdge(x0, y0, 0, x1, y1, 0);
   // tmpline.setval
  }
  
  public void startDrawing()
  {
    drawing = true;
  }
    
  public void stopDrawing() 
  {
    drawing = false;
  }
  
  public BufferedImage getBufferedImage() 
  {
    return img;
  }

  public Dimension getPreferredSize() 
  {
    return new Dimension(560, 406); // Width, Height
  }


  /*======== public void addLine() ==========
   Inputs:  
   int x0
   int y0
   int z0
   int x1
   int y1
   int z1 
   Returns: 
   Adds the specified line to the edges PointMatrix
   ====================*/
  public void addLine(int x0, int y0, int z0, int x1, int y1, int z1) 
  {
      edges.addEdge(x0, y0, z0, x1, y1, z1);
  }

  
  /*======== public void addPoint() ==========
   Inputs:  int x0
   int y0
   int z0 
   Returns: 
   add a single point to the edges PointMatrix
   ====================*/
  public void addPoint(int x0, int y0, int z0) 
  {
      edges.addPoint(x0, y0, z0);
  }
  
  
  public void clearTmp() 
  {
    tmpline.clear();
  }

  
  /*======== public void paintComponent() ==========
   Inputs:  Graphics g 
   Returns: 
   draws the edges stored in tmpLine or edges to the canvas
   you must update this to work with matricies instead of an 
   array of Line objects   
   ====================*/
  public void paintComponent(Graphics g) 
  {  
    super.paintComponent(g);
    img = (BufferedImage)this.createImage(400,400); // Width, Height
    Graphics2D g2 = img.createGraphics();
    
    img2 = (BufferedImage)this.createImage(400, 400);
    Graphics2D g2d = img2.createGraphics();
    
    //this.createInteractions();
    
    String s1 = "Select Transformation:";
    String s2 = "X";
    String s3 = "Y";
    String s4 = "Z";
    Font f = new Font("Arial", Font.BOLD, 88);
    FontMetrics fm = this.getFontMetrics(f);
    g2d.setColor(Color.blue);
    g2d.drawString(s1, 25, 30); // String, Width, Height
    g2d.drawString(s2, 135, 70);
    g2d.drawString(s3, 135, 110);
    g2d.drawString(s4, 135, 150);
    
    //this should only be the temporary lines
    if (drawing) 
    {
      g2.setColor(c.red);
      g2.drawLine(tmpline.getX(0), tmpline.getY(0), tmpline.getX(1), tmpline.getY(1));
      //draw tmpline, the java drawLine call is as follows:
      //g2.drawLine( x0, y0, x1, y1);
    }
    
    g2.setColor(c);
    
    //use java's drawline to draw the lines in the edges PointMatrix
    int i;
    for (i = 0; i < edges.getLastCol()-1; i+=2)
    {
       g2.drawLine(edges.getX(i), edges.getY(i), edges.getX(i+1), edges.getY(i+1));
    }
        
    ((Graphics2D)g).drawImage(img,null,0,0); // Width, Height
    ((Graphics2D)g).drawImage(img2,null,300,0); // Buttons & Stuff
    
    //Toolkit.getDefaultToolkit().sync();
    //g.dispose();
  }
  
  // Transformations
  public Matrix xRotate(Matrix p, int r)
  {
    Matrix x = new Matrix();
    x.setRotateX(r);
    p.matrixMult(x);
    return p;
  }
  
  public Matrix yRotate(Matrix p, int r)
  {
    Matrix y = new Matrix();
    y.setRotateY(r);
    p.matrixMult(y);
    return p;
  }
  
  public Matrix zRotate(Matrix p, int r, char a)
  {
    
    Matrix z = new Matrix();
    z.setRotateZ(r, a);
    p.matrixMult(z);
    return p;
  }
  
  public Matrix scale(Matrix p, int x, int y, int z)
  {
    Matrix sc = new Matrix();
    sc.setScale(x, y, z);
    p.matrixMult(sc);
    return p;
  }
  
  public Matrix translate(Matrix p, int x, int y, int z)
  {
    Matrix tr = new Matrix();
    tr.setTranslate(x, y, z);
    p.matrixMult(tr);
    return p;
  }
  
  
  // Action Listener
  public void actionPerformed(ActionEvent e)
  {
    if (e.getActionCommand().equals("Button"))
    {
      if (combo.getSelectedIndex()==0)
      {
        //this.xRotate(edges, /*get Text from epane);
      }
    }

    //this.startDrawing();
    revalidate();
    repaint();
  }
  
  // Mouse Listener Methods
  public void mouseClicked(MouseEvent e)
  {
    edges.addPoint((int)e.getX(), (int)e.getY(), 0);
    tmpline.addPoint((int)e.getX(), (int)e.getY(), 0, 0);
    repaint();
  }
  
  public void mouseEntered(MouseEvent e)
  {
    entered = true;
  }
  
  public void mouseExited(MouseEvent e)
  {
    entered = false;
  }
  
  public void mousePressed(MouseEvent e)
  {
    if (entered)
    {
      pressed = true;
      //edges.addPoint(e.getX(), e.getY(), 0);
      addPoint(e.getX(), e.getY(), 0);
      tmpline.addPoint(e.getX(), e.getY(), 0, 0);
      this.startDrawing();
    }
    //repaint();
  }
  
  public void mouseReleased(MouseEvent e)
  {
    this.stopDrawing();
    if (entered && pressed)
    {
	// edges.addPoint(e.getX(), e.getY(), 0);
	addPoint(e.getX(), e.getY(), 0);
      //this.stopDrawing();
      pressed = false;
    }
    repaint();
  }
  
  // Mouse Motion Listener Methods
  public void mouseDragged(MouseEvent e)
  {
    tmpline.addPoint(e.getX(), e.getY(), 0, 1);
  }
  
  public void mouseMoved(MouseEvent e)
  {
    if (entered && pressed)
    {
      repaint();
    }
  }
    
}