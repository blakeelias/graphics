package nonMDL;

/*========== Lighting.java ==========

represents the light illuminating the space

  =========================*/

import java.io.*;
import java.util.*;
import javax.swing.*;
import java.awt.*;
import java.awt.image.*;
import javax.imageio.*;

public class Lighting {

    public double
	kAmbR, kAmbG, kAmbB,  // ambient
     	kDifR, kDifG, kDifB,  // diffuse (matte-ness)
	kSpeR, kSpeG, kSpeB;  // specular (shininess)
    public PointMatrix source;

    public Lighting(
	double kAmbR, double kAmbG, double kAmbB,  // ambient
     	double kDifR, double kDifG, double kDifB,  // diffuse (matte-ness)
	double kSpeR, double kSpeG, double kSpeB,  // specular (shininess)
	PointMatrix source){

	this.kAmbR = kAmbR; this.kAmbG = kAmbG; this.kAmbB = kAmbB;
	this.kDifR = kDifR; this.kDifG = kDifG; this.kDifB = kDifB;
	this.kSpeR = kSpeR; this.kSpeG = kSpeG; this.kSpeB = kSpeB;

	this.source = source;  // WARNING:  referst to original object
    }

    public Lighting(){
	this(.55, .55, .55,
	     .5, .5, .5,
	     .1, .1, .1,
	     new PointMatrix(0, 0, 0));
    }

}