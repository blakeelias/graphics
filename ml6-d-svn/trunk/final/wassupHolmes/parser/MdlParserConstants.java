/* Generated By:JavaCC: Do not edit this line. MdlParserConstants.java */
package parser;


/**
 * Token literal values and constants.
 * Generated by org.javacc.parser.OtherFilesGen#start()
 */
public interface MdlParserConstants {

  /** End of File. */
  int EOF = 0;
  /** RegularExpression Id. */
  int SINGLE_LINE_COMMENT = 4;
  /** RegularExpression Id. */
  int BOX = 6;
  /** RegularExpression Id. */
  int SPHERE = 7;
  /** RegularExpression Id. */
  int TORUS = 8;
  /** RegularExpression Id. */
  int LINE = 9;
  /** RegularExpression Id. */
  int MESH = 10;
  /** RegularExpression Id. */
  int ROTATE = 11;
  /** RegularExpression Id. */
  int MOVE = 12;
  /** RegularExpression Id. */
  int SCALE = 13;
  /** RegularExpression Id. */
  int PUSH = 14;
  /** RegularExpression Id. */
  int POP = 15;
  /** RegularExpression Id. */
  int BASENAME = 16;
  /** RegularExpression Id. */
  int SET = 17;
  /** RegularExpression Id. */
  int SETKNOBS = 18;
  /** RegularExpression Id. */
  int GENRAYS = 19;
  /** RegularExpression Id. */
  int SHADING = 20;
  /** RegularExpression Id. */
  int FOCAL = 21;
  /** RegularExpression Id. */
  int DISPLAY = 22;
  /** RegularExpression Id. */
  int LIGHT = 23;
  /** RegularExpression Id. */
  int AMBIENT = 24;
  /** RegularExpression Id. */
  int CONSTANTS = 25;
  /** RegularExpression Id. */
  int SAVECS = 26;
  /** RegularExpression Id. */
  int CAMERA = 27;
  /** RegularExpression Id. */
  int SAVEKNOBS = 28;
  /** RegularExpression Id. */
  int TWEEN = 29;
  /** RegularExpression Id. */
  int FRAMES = 30;
  /** RegularExpression Id. */
  int VARY = 31;
  /** RegularExpression Id. */
  int SAVE = 32;
  /** RegularExpression Id. */
  int DOUBLE = 33;
  /** RegularExpression Id. */
  int INT = 34;
  /** RegularExpression Id. */
  int DIGIT = 35;
  /** RegularExpression Id. */
  int ID = 36;
  /** RegularExpression Id. */
  int FN = 37;

  /** Lexical state. */
  int DEFAULT = 0;
  /** Lexical state. */
  int IN_SINGLE_LINE_COMMENT = 1;

  /** Literal token values. */
  String[] tokenImage = {
    "<EOF>",
    "\" \"",
    "\"\\t\"",
    "\"//\"",
    "<SINGLE_LINE_COMMENT>",
    "<token of kind 5>",
    "\"box\"",
    "\"sphere\"",
    "\"torus\"",
    "\"line\"",
    "\"mesh\"",
    "\"rotate\"",
    "\"move\"",
    "\"scale\"",
    "\"push\"",
    "\"pop\"",
    "\"basename\"",
    "\"set\"",
    "\"setknobs\"",
    "\"generate_rayfiles\"",
    "\"shading\"",
    "\"focal\"",
    "\"display\"",
    "\"light\"",
    "\"ambient\"",
    "\"constants\"",
    "\"save_coord_system\"",
    "\"camera\"",
    "\"save_knobs\"",
    "\"tween\"",
    "\"frames\"",
    "\"vary\"",
    "\"save\"",
    "<DOUBLE>",
    "<INT>",
    "<DIGIT>",
    "<ID>",
    "\":\"",
    "\"\\n\"",
  };

}
