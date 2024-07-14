{ defs.inc - All constants, types and global variables are defined here. }
Const
  (*  Related to MSX BIOS. *)
  ctINITXT                        = $006C;    { Initialize screen for text mode (40x24) }
  ctINIFNK                        = $003E;
  ctERAFNK                        = $00CC;    { Erase the function key display   }
  ctDSPFNK                        = $00CF;    { Display the function key display }

  (*  Related to MSX-DOS. *)
  ctGetPreviousErrorCode          = $65;
  ctExplainErrorCode              = $66;
  ctSetEnvironmentItem            = $6C;
  ctGetMSXDOSVersionNumber        = $6F;

  (*  Related to MSX blink table. *)
  Vdp14                           = 13;       { Blink rate register in vdp}
  Vdp13                           = 12;       { Blink colors High nibble = foreground }
  SetB                            = True;
  ResB                            = False;    { Switch values for setbit }
  MaskTable: Array[0..7] Of Byte  = (128,64,32,16,8,4,2,1);

Type
  Pointer = ^Byte;                   { Pointer generic type }
  TString = String[maxcols];
  TStr15 = String[15];

  (*  Z80 registers. *)
  TRegs       = Record
      IX, IY:                 Integer;             { 16Bit index registers }
      Case Byte Of    { 8Bit registers and 16Bit registers - WORD_REGS }
          0:                  ( C,B,E,D,L,H,F,A:  Byte );     { 8bit registers  }
          1:                  ( BC,DE,HL,AF:      Integer );  { 16bit registers }
      End;

  (*  SCREEN 0 and 1. *)
  TTextMode = (TextMode4080, TextMode32);

  (*  Screen status. *)
  TScreenStatus = Record
    nWidth,
    nBkColor,
    nFgColor,
    nBdrColor: Byte;
    bFnKeyOn: Boolean;
    TextMode: TTextMode;
    End;

  (*  MSX-DOS version. *)
  TypeMSXDOSVersion = Record
      nKernelMajor,
      nKernelMinor,
      nSystemMajor,
      nSystemMinor: Byte;
  End;

  (*  Used in the array which know where the text are saved into VRAM. *)
  TVRAMText  = record
      VRAMBank: Byte;
      VRAMposition:  Integer;
  End;

  (*  Scalar types, in order:
  * KeystrokeLines - Used in DisplayKeys procedure.
  * Directions - Used in search procedure.
  * LocationOptions - Used to change behaviour of Position procedure.
  * BlockMarkings - Used to change behaviour of Block procedures. *)

  KeystrokeLines  = (main, search, replace, align);
  Directions      = (forwardsearch, backwardsearch);
  LocationOptions = (Position, HowMany);
  BlockMarkings   = (BlockBegin, BlockFinish);
  ASCII           = set of 0..255;

Var
  (*  These variables are related to MSX BIOS. *)
  regs:       TRegs;
  EXPTBL:     Byte Absolute $FCC1;        { Slot 0 }
  LINL40:     Byte Absolute $F3AE;        { Width for SCREEN 0 }
  LINLEN:     Byte Absolute $F3B0;        { Width for the current text mode }
  TXTNAM:     Integer Absolute $F3B3;
  TXTCOL:     Integer Absolute $F3B5;     {   Blink table addr}
  CSRY:       Byte Absolute $F3DC;
  CSRX:       Byte Absolute $F3DD;
  CNSDFG:     Byte Absolute $F3DE; { =0 when function keys are not displayed }
  CSRSW:      Byte absolute $FCA9;
  SCRMOD:     Byte Absolute $FCAF; { Current screen number }
  FORCLR:     Byte Absolute $F3E9; { Foreground color }
  BAKCLR:     Byte Absolute $F3EA; { Background color }
  BDRCLR:     Byte Absolute $F3EB; { Border color     }
  CURSAV:     Byte Absolute $FBCC;

  (*  These variables are used by include files. *)
  VramLocation, Vram, Ram, TableAddr, len:        Integer;
  Width, Height, Byt,
  Expansion, AddrHi, AddrMid, AddrLo:             Byte;
  pt:                                             Pointer;
  at:                                             Integer Absolute pt;
  ColTbl:                                         Array[0..255] Of Byte;

  i, j, k, Count:                                 Integer;