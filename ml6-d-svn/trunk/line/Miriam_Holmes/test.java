import java.io.*;
import java.util.*;

import java.awt.*;

public class test {
    public static void main(String[] args) {

	Frame f = new Frame();
	Color c = new Color(f.MAXCOLOR, 0, 0);

	f.clear_screen();

	// horizontal lines l->r and r->l
	f.drawLine(new Point(0, f.YRES/2), new Point(300, f.YRES/2), c);
	f.drawLine(new Point(f.XRES-1, f.YRES/2), new Point(300, f.YRES/2), c);

	// vertical lines, up and down
	f.drawLine(new Point(f.XRES/2, 0), new Point(f.XRES/2, 300), c);
	f.drawLine(new Point(f.XRES/2, f.YRES-1), new Point(f.XRES/2, 300), c);

	// slope == 1
	f.drawLine(new Point (0, 0), new Point (f.XRES-1, f.YRES-1), c);

	// slope == -1
	f.drawLine(new Point (0, f.YRES-1), new Point (f.XRES-1, 0), c);

	// octants 1 and 5
	f.drawLine(new Point(0, 0), new Point (f.XRES-1, f.YRES-75), new Color (0, f.MAXCOLOR, 0));
	f.drawLine(new Point(0, 75), new Point (f.XRES-1, f.YRES-1), new Color (0, 0, f.MAXCOLOR));

	// octants 2 and 6 (6 r->l)
	f.drawLine(new Point (0, 0), new Point (f.XRES-75, f.YRES-1), new Color (0, f.MAXCOLOR, 0));
	f.drawLine(new Point (75, 0), new Point (f.XRES-1, f.YRES-1), new Color (0, 0, f.MAXCOLOR));

	// octants 4 and 8
	f.drawLine(new Point (f.XRES-1, 0), new Point (0, f.YRES-75), new Color (0, 0, f.MAXCOLOR));
	f.drawLine(new Point (0, f.YRES-1), new Point (f.XRES-1, 75), new Color (0, f.MAXCOLOR, 0));

	// octants 3 and 
	f.drawLine(new Point(f.XRES-1, 0), new Point(75, f.YRES-1), new Color (0, 0, f.MAXCOLOR));
	f.drawLine(new Point(0, f.YRES-1), new Point(f.XRES-75, 0), new Color (0, f.MAXCOLOR, 0));


	f.save("pic.ppm");
    }
}
