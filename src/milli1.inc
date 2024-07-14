(*
*  milli1.inc - Pascal library which is used with the milli text editor.
*  Here we have some routines which are accessory to the program.
*)

(* Read only one key, no echoes to the screen.*)
function Readkey: char;
begin
  Readkey := chr(0);
  CSRSW := 1;
  inline (
    $F3/                        { DI                                   }
    $FD/$2A/$C0/$FC/            { LD IY,(0FCC0H)                       }
    $DD/$21/$9F/00/             { LD IX,0009FH                         }
    $CD/$1C/00/                 { CALL 0001CH                          }
    $32/ Byt /                  { LD (`Byt`),A                         }
    $FB                         { EI                                   }
  );
  Readkey := chr(Byt);
  CSRSW := 0;
end;

(* Read a string, echoes to the screen. Should tell how many chars would be read. *)
function ReadString (MaxLen: Byte): TString;
begin
  fillchar(temp, sizeof(temp), chr(32));
  i := 0;
  repeat
    c := readkey;
    case c of
      #30..#126,#128..#255:  if i < Maxlen then
        begin
          i := i + 1;
          Write(c);
          temp := temp + c;
        end
        else
          Write(#7);
      #8:           if i > 0 then
        begin
          i := i-1;
          Write(c);
          Write(' ');
          Write(c);
          temp[0] := Chr(i);
        end
        else
          Write(#7);
    end; {Case}

  until c = #13;

  ReadString := temp;
end; {ReadString}

(* Finds the last occurence of a char into a string. *)
function RPos(Character: char; Phrase: TString): integer;
begin
  i := length(Phrase);
  Found := false;
  repeat
    if Phrase[i] = Character then
    begin
      RPos := i + 1;
      Found := true;
    end;
    i := i - 1;
  until Found;
  if not Found then RPos := 0;
end;

(*  Finds the first occurence of a char which is different into a string. *)
function UnlikePos (Character: char; Phrase: TString): byte;
(* Used only into AlignText procedure. *)
begin
  i := 0;
  Found := false;

  repeat
    i := i + 1;
    if Phrase[i] <> Character then
    begin
      UnlikePos := i;
      Found := true;
    end;
  until (Found) or (i >= length(Phrase));

  if not Found then UnlikePos := 0;
end;

(*  Finds the last occurence of a char which is different into a string. *)
function RUnlikePos(Character: char; Phrase: TString): integer;
(* Used only into AlignText procedure. *)
begin
  i := length(Phrase);
  Found := false;

  repeat
    if Phrase[i] <> Character then
    begin
      RUnlikePos := i;
      Found := true;
    end;
    i := i - 1;
  until Found or (i <= 1);

  if not Found then RUnlikePos := 0;
end;

(* Updates the APPEND environment variable, in order to use subdirectories in
*  MSX-DOS 2. *)
procedure CheatAPPEND (FileName: TString);
var
  FirstTwoDotsFound, LastBackSlashFound: byte;
  APPEND: string[7];
begin
  (* Initializing some variables... *)
  fillchar(Path, sizeof(Path), ' ' );
  fillchar(temp, sizeof(temp), ' ' );
  APPEND[0] := 'A';   APPEND[1] := 'P';   APPEND[2] := 'P';
  APPEND[3] := 'E';   APPEND[4] := 'N';   APPEND[5] := 'D';
  APPEND[6] := #0;

  (*  Sees if in the path there is a ':', used with drive letter. *)
  FirstTwoDotsFound := Pos (chr(58), FileName);

  (*  If there are two dots...  *)
  if FirstTwoDotsFound <> 0 then
  begin
    (*  Let me see where is the last backslash character...  *)
    LastBackSlashFound := RPos (chr(92), FileName);
    Path := copy (FileName, 1, LastBackSlashFound);

    (*  Copy the path to the variable. *)
    for i := 1 to LastBackSlashFound - 1 do
      temp[i - 1] := Path[i];
    temp[LastBackSlashFound] := #0;
    Path := temp;

    (*  Sets the APPEND environment variable. *)
    with regs do
    begin
      B := sizeof (Path);
      C := ctSetEnvironmentItem;
      HL := addr (APPEND);
      DE := addr (Path);
    end;
    MSXBDOS (regs);
  end;
end;

(* Sets Z80 mode in MSX Turbo-R. ***CHECK*** *)
procedure TRZ80mode;
begin
  inline(
    $3E/$00/                     { LD A,$00 <-                         }
    $FD/$2A/$C0/$FC/	           { LD IY,($FCC0)                       }
    $DD/$21/$80/$01/	           { LD IX,$0180                         }
    $CD/$1C/$00/	               { CALL $001C                          }
    $FB/	                       { EI                                  }
  );
end;

(* Sets R800 mode in MSX Turbo-R. ***CHECK*** *)
procedure TRR800mode;
begin
  inline(
    $3E/$00/                     { LD A,$00 <-                         }
    $FD/$2A/$C0/$FC/	           { LD IY,($FCC0)                       }
    $DD/$21/$80/$01/	           { LD IX,$0180                         }
    $CD/$1C/$00/	               { CALL $001C                          }
    $FB/	                       { EI                                  }
  );
end;

(* Moves text from RAM to VRAM. *)
procedure FromRAMToVRAM(var tempstr: TString; linenumber: integer);
begin
  with textlines[linenumber] do
    WriteVRAM(VRAMBank, VRAMposition, addr(tempstr), maxcols);
end;

(* Moves text from VRAM to RAM. *)
procedure FromVRAMToRAM(var tempstr: TString; linenumber: integer);
begin
  with textlines[linenumber] do
    ReadVRAM(VRAMBank, VRAMposition, addr(tempstr), maxcols);
end;

(* Initializes the VRAM buffer and all structed variables which are related. *)
procedure InitVRAM(linenumber: integer; var counter: real);
begin
  with textlines[linenumber] do
  begin
    if linenumber = 1 then
    begin
      VRAMposition    := startvram;
      VRAMBank        := 0;
    end
    else
    begin
      VRAMposition    :=  textlines[linenumber - 1].VRAMposition
        + maxcols;
      VRAMBank        :=  textlines[linenumber - 1].VRAMBank;
    end;

    if counter >= limitvram then
    begin
      VRAMBank        := VRAMBank + 1;
      VRAMposition    := $0000;
      counter         := 0;
    end;
  end;
  emptylines[linenumber] := true;
end;

(* Search for a blank block into VRAM. *)
function SearchForBlankBlock(BlankLines: integer): integer;
begin
  i := 0;
  k := 0;
  LastPosition := true;

  while (i <= maxlinesforreal) and (k < BlankLines) do
  begin
    i := i + 1;
    if emptylines[i] = true then
      k := k + 1
    else
      k := 0;
  end;

  SearchForBlankBlock := i - BlankLines;
end;

(* Insert some lines into text, into VRAM. *)
procedure InsertLinesIntoText(CurrentLine   : integer;
  var TotalLines  : integer;
  BlankLines  : integer);
begin

  (*  Moves the text block, BlankLines, till the end. *)
  i := (TotalLines + 1) - CurrentLine;
  Move(textlines[CurrentLine], textlines[CurrentLine + BlankLines],
    sizeof(textlines[BlankLines]) * i);

(*  Blocks the new lines which were created, so when the program searches for
*   blank blocks, they won`t be considered. *)
  for i := (TotalLines + 1) to (TotalLines + BlankLines) do
    emptylines[i] := false;

(*  Searches for blank blocks which has the needed exact size, so the text block
*   could be redirected into the VRAM. *)
  NewBeginBlock := SearchForBlankBlock(BlankLines);

  for i := (CurrentLine + 1) to (CurrentLine + BlankLines) do
  begin

    (*  Redirects the text block into VRAM - in the allocation table. *)
    textlines[i].VRAMBank       := textlines[NewBeginBlock +
      (i - CurrentLine) + 1].VRAMBank;
    textlines[i].VRAMPosition   := textlines[NewBeginBlock +
      (i - CurrentLine) + 1].VRAMPosition;
  end;

  (*  New maximum, which has the last line, added with BlankLines. *)
  TotalLines := TotalLines + BlankLines;

  (*  In the emptylines structed variable, these lines should be blocked. *)
  for i := (CurrentLine + 1) to TotalLines do
    emptylines[i] := false;
end;

procedure DeleteLinesFromText(CurrentLine: integer;
  var TotalLines: integer;
  DeletedLines: integer);
begin

  (*  Moves the text block, DeletedLines, till the end. *)
  i := TotalLines - CurrentLine;
  Move(textlines[CurrentLine + DeletedLines], textlines[CurrentLine],
    sizeof(textlines[DeletedLines]) * i);

  (*  Frees the new lines in the end, so blank blocks can be considered. *)
  for i := (TotalLines - DeletedLines) to TotalLines do
    emptylines[i] := true;

  (*  New maximum, which has the last line, added with BlankLines. *)
  TotalLines := TotalLines - DeletedLines;
end;

(*  Copy text blocks from one region to another, into VRAM. *)

procedure CopyBlock(FirstLineBlock, LastLineBlock, FirstLineCopy: integer);
begin
  for i := FirstLineBlock to LastLineBlock do
  begin
    textlines   [FirstLineCopy + i - FirstLineBlock]    := textlines[i];
    emptylines  [FirstLineCopy + i - FirstLineBlock]    := false;
  end;
end;