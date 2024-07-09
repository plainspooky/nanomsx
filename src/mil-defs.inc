program dummy;
{ mil-defs.inc - constants, types and global variables used by milli }

Const
  (* Keystrokes. *)
  CONTROLA = 1;
  CONTROLB = 2;
  CONTROLC = 3;
  CONTROLD = 4;
  CONTROLE = 5;
  CONTROLF = 6;
  CONTROLG = 7;
  CONTROLJ = 10;
  CONTROLN = 14;
  CONTROLO = 15;
  CONTROLP = 16;
  CONTROLQ = 17;
  CONTROLS = 19;
  CONTROLT = 20;
  CONTROLV = 22;
  CONTROLW = 23;
  CONTROLY = 25;
  CONTROLZ = 26;
  BS = 8;
  TAB = 9;
  HOME = 11;
  CLS = 12;
  ENTER = 13;
  INSERT = 18;
  SELECT= 24;
  ESC = 27;
  RightArrow = 28;
  LeftArrow = 29;
  UpArrow = 30;
  DownArrow = 31;
  Space = 32;
  DELETE = 127;

  (*  Used in milli - limits. *)
  maxlines                        = 1568;
  maxcols                         = 80;
  maxwidth                        = 78;
  maxlength                       = 21;

  (*  Used in milli - VRAM limits. *)
  startvram                       = 5120;
  limitvram                       = 65280;

  (*  These variables are used by milli itself. *)
  textlines:                          array [1..maxlines] of TVRAMText;
  emptylines:                         array [1..maxlines] of boolean;
  temp:                               TString;
  NoPrint, Print, AllChars:           ASCII;

  currentline, highestline:           integer;
  key, screenline, column,
  BlinkLength:                        byte;
  tabset:                             array [1..maxwidth] of boolean;
  textfile, backuptextfile:           text;
  filename, searchstring, line, Path,
  tempsearchstring, replacestring,
  Line1, Line2:                       TString;
  savedfile, insertmode, iscommand,
  blockmarked, Found, LastPosition:   boolean;
  tempnumber0, tempnumber1,
  tempnumber2:                        string[5];
  tabnumber, newline, rtcode, aux,
  newcolumn, stopsearch, point:       integer;
  c:                                  char;
  counter:                            real;

  BlockStart, BlockEnd, BlockDest,
  NewBeginBlock, totalwords:          integer;

  abovechar, totalchar, percentchar:  real;

  lengthmessage, ranking:             byte;
  BlinkSequence:                      array [1..6] of byte;
  destline, destcolumn:               integer;

  ScreenStatus:                       TScreenStatus;
  EditWindowPtr:                      Pointer;
  MSXDOSversion:                      TypeMSXDOSVersion;
  end.