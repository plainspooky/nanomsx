{TxtWin.inc by Kari Lammassaari 1997 }

function MakeWindow (Col, Row, Width, Height: Byte; Header: TString):  Pointer;
{
   MakeWindow stores the underlying screen onto heap.
   The structure of heap record:  offset 0  = column of the upper left corner
                                         1  = row    of the upper left corner
                                         2  = length of the window
                                         3  = height of the window
                                         4  = the cursor column of the window
                                         5  = the cursor row of the window
                                         6  = underlying screen data
                                         .
}
const
  ULC = #24;
  URC = #25; {UpperLefCorner ..Charnumbers for the Frame}
  DLC = #26;
  DRC = #27;
  VERTICAL = #22;
  HORIZONTAL = #23;

var
  a, b: Byte;

begin
  GetMem(pt, Width * Height + 6);
  Mem[at] := Col;
  Mem[at+1] := Row;
  Mem[at+2] := Width;
  Mem[at+3] := Height;
  Mem[at+4] := 1;
  Mem[at+5] := 1;
  Vram := (Row - 1) * 80 + Col;
  Ram := At+6;
  for Count := 1 to Height do
  begin
    ReadVram(0, Vram, Ram, Width);
    Vram    := Vram + 80;
    Ram     := Ram  + Width;
  end;

  FillChar(line, 81, chr(32)); {Fill with horizontal line }

  a := (Width - Length(Header)) div 2;
  for b:= 1 to Length(Header) do
    line[a+b] := Header[b];
  line[1]     := ULC;
  line[Width] := URC;
  Vram        := (Row - 1) * 80 + Col;
  WriteVram(0, Vram, Addr(line[1]), Width);

  FillChar(line, 81, 32); {Fill with space }
  line[1]     := Vertical;
  line[Width] := Vertical;
  Vram        := Vram + 80;
  for Count   := 2 to height-1 do
  begin
    WriteVram(0, Vram, Addr(line[1]), Width);
    Vram    := Vram + 80;
  end;

  FillChar(line, 81, Horizontal); {Fill with horizontal line }
  line[1]     := DLC;
  line[Width] := DRC;
  WriteVram(0, Vram, Addr(line[1]), Width);

  MakeWindow := pt;
end;  {MakeWindow}

procedure EraseWindow(WindowPtr: Pointer);
begin
  pt := WindowPtr;
  Vram := (Mem[at+1]-1)*80 + Mem[at];
  Width := Mem[at+2];
  Height := Mem[at+3];
  Ram := at + 6;

  for Count := 1 to Height do
  begin
    WriteVram(0,Vram,Ram,Width);
    Ram := Ram + width;
    Vram := Vram + 80;
  end;
  FreeMem(WindowPtr,Width*Height+6);
end; { EraseWindow }

procedure ScrollWindowUp(WindowPtr: Pointer);
var
  i:  Byte;

begin
  pt := WindowPtr;
  Ram := Addr(Line1);
  Vram := mem[at] + 1 + Mem[at+1]*80 ;
  Byt := Mem[at+2]-2;

  for i := 1 to Mem[at+3]-3 do
  begin
    ReadVram(0,vram+80,Ram,Byt);
    WriteVram(0,Vram,Ram,Byt);
    Vram := Vram + 80;
  end;

  FillChar(Line1,80,32);
  WriteVram(0,Vram,Ram,Byt);

end; {ScrollWindowUp }

procedure ScrollWindowDown(WindowPtr:Pointer);
var
  i:  Byte;

begin
  pt := WindowPtr;
  Ram := Addr(Line1);
  Vram := mem[at] + 1 + (Mem[at+1]+mem[at+3]-3) *80 ;
  Byt := Mem[at+2]-2;

  for i := 1 to Mem[at+3]-3 do
  begin
    ReadVram(0,vram-80,Ram,Byt);
    WriteVram(0,Vram,Ram,Byt);
    Vram := Vram - 80;
  end;

  FillChar(Line1,80,32);
  WriteVram(0,Vram,Ram,Byt);

end; {ScrollWindowDown }

function WhereXWindow (WindowPtr: Pointer): byte;
begin
  pt := WindowPtr;
  WhereXWindow := Mem[at + 4];
end;    { WhereXWindow }

function WhereYWindow (WindowPtr: Pointer): byte;
begin
  pt := WindowPtr;
  WhereYWindow := Mem[at + 5];
end;    { WhereYWindow }

procedure DelLineWindow (WindowPtr: Pointer);
var
  i, CurRow, CurCol:  byte;

begin
  pt := WindowPtr;
  Ram := Addr(Line1);
  CurRow := Mem[at + 5];
  CurCol := Mem[at + 4] ;
  Vram := Mem[at] + (Mem[at + 1] + CurRow - 1) * 80 + 1;
  Byt := Mem[at + 2] - 2;

  for i := CurRow to Mem[at + 3] - 3 do
  begin
    ReadVram(0, vram + 80, Ram, Byt);
    WriteVram(0, Vram, Ram, Byt);
    Vram := Vram + 80;
  end;

  FillChar(Line1, 80, 32);
  WriteVram(0, Vram, Ram, Byt);

end; { DelLineWindow }

procedure InsLineWindow (WindowPtr: Pointer);
var
  i, CurRow, CurCol:  byte;

begin
  pt := WindowPtr;
  Ram := Addr(Line1);
  CurRow := Mem[at + 5];
  CurCol := Mem[at + 4] ;
  Vram := Mem[at] + (Mem[at + 1] + CurRow - 1) * 80 + 1;
  Vram := mem[at] + 1 + (Mem[at + 1] + mem[at + 3] - 3) * 80;
  Byt := Mem[at + 2] - 2;

  for i := (CurRow - 1) to Mem[at + 3] - 3 do
  begin
    ReadVram(0, vram - 80, Ram, Byt);
    WriteVram(0, Vram, Ram, Byt);
    Vram := Vram - 80;
  end;

  FillChar(Line1, 80, 32);
  WriteVram(0, Vram, Ram, Byt);

end; { InsLineWindow }

procedure _WriteWindowOperation(WindowPtr: Pointer; St: TString;
  LineFeed: Boolean);
label Out;
type WindowInfoType = record
    WinCol: Byte;       {The coordinates of upper left}
    WinRow: Byte;       {corner of the window.}
    WinLen: Byte;       {Window measures including border}
    WinHeigth: Byte;    {chars.}
    CurCol: Byte;       {The cursor coordinates of }
    CurRow: Byte;       {this window}
  end;

var
  pt: Integer;
  at: WindowInfoType;
  WrtLen, LinLen,
  Bottom, StIndex, b: Byte;
  temp: String[8];

  procedure FillRow(var StringIndex:Byte);
  begin
    with at do
    begin
      if (CurRow = Bottom) and (WinHeigth > 3 ) then { No scroll for one }
      begin                                       { line window ! }
        ScrollWindowUp(WindowPtr);
        CurRow  := Bottom - 1;
        Vram    := Vram   - 80;
      end;
      Ram := Addr(St[StringIndex]);
      WrtLen := WinLen - CurCol - 1;
      StringIndex := StringIndex + WrtLen;
      WriteVram(0,Vram,Ram,WrtLen);

      CurCol := 1;
      CurRow := CurRow + 1;
      Vram := WinCol + 1 + (WinRow+CurRow-1)*80;

    end; {With}
  end;

  procedure WriteRow(var StringIndex:Byte);
  begin
    with At do
    begin
      if (CurRow = Bottom) and (WinHeigth > 3 ) then { No scroll for one }
      begin                                       { line window ! }
        ScrollWindowUp(WindowPtr);
        CurRow := Bottom -1;
        Vram := Vram - 80;
      end;
      Ram := Addr(St[StringIndex]);
      WrtLen := Length(St) - StringIndex + 1 ;
      StringIndex := StringIndex + WrtLen;
      WriteVram(0, Vram, Ram, WrtLen);

      if LineFeed then
      begin
        CurRow := CurRow + 1;
        CurCol := 1;
        Vram := Vram + 80;
      end
      else
      begin
        CurCol := CurCol + WrtLen;
        Vram := Vram + WrtLen;
      end;
    end; {with}
  end;

begin
  FillChar(temp, sizeof(temp), chr(32));

  for b := 1 to 8 do
    temp := temp + chr(32);

  b := pos(chr(9), St);

  while b <> 0 do
  begin
    delete(St, b, 1);
    delete(St, sizeof(St) - length(temp), length(temp));
    insert(temp, St, b);
    b := pos(chr(9), St);
  end;

  pt := Addr(at);
  inline($f3/$01/6/0/ $2a/WindowPtr/ $ed/$5b/ pt/$ed/$b0 );
  with at do
  begin
    Bottom := WinHeigth - 1;
    Vram := WinCol + CurCol + (WinRow + CurRow - 1) * 80;
    if St = '' then
    begin
      CurRow := CurRow+1;
      CurCol := 1;
      if (CurRow >= Bottom) and (WinHeigth > 3 ) then { No scroll for one }
      begin                                           { line window ! }
        ScrollWindowUp(WindowPtr);
        CurRow := Bottom-1;
      end;
      goto Out;
    end;

    StIndex := 1;
    WrtLen := WinLen  - CurCol - 1;
    LinLen := WinLen - 2;

    if Length(St) > WrtLen then     {String long,exceeds to next row}
    begin
      FillRow(StIndex);
      while (Length(st)-StIndex+1) >= LinLen do
        FillRow(StIndex);
      if Length(St) - StIndex >= 0 then
        WriteRow(StIndex);
    end
    else
    if Length(St) < WrtLen then  {Str short, doesn`t exceed to next row}
      WriteRow(StIndex)
    else
      FillRow(StIndex){Str just fills the line};
  end; {With}
  Out:
    inline($f3/$01/6/0/ $2a/pt / $ed/$5b/ WindowPtr/$ed/$b0/$fb );
end; {WritelnWindow}

procedure WritelnWindow(WindowPtr: Pointer; St: TString);
begin
  _WriteWindowOperation(WindowPtr,St,True); {True -> do linefeed }
end;

procedure WriteWindow(WindowPtr: Pointer; St: TString);
begin
  _WriteWindowOperation(WindowPtr,St,False);
end;

procedure GotoWindowXY(WindowPtr:Pointer; Col, Row: Byte);
begin
  pt  := WindowPtr;
  GotoXY(Mem[at] + Col + 1, Mem[at+1] + Row);
  Mem[at+4] := Col;
  Mem[At+5] := Row;
end;

procedure ClrEolWindow(WindowPtr:Pointer);
var
  CurCol,CurRow:  Byte;
  WrtLen:         Byte;

begin
  pt      := WindowPtr;
  CurRow  := Mem[at+5];
  CurCol  := Mem[at+4] ;
  Vram    := Mem[at] + (Mem[at+1] + CurRow - 1) * 80 + CurCol;
  WrtLen  := Mem[at+2] - 1 - CurCol;
  FillVram(0, Vram, 32, WrtLen);
  CURSAV  := 32;
end;

procedure ClrWindow (WindowPtr: Pointer);
var
  i:  Byte;
begin
  pt := WindowPtr;
  Vram := Mem[at] + 1 + (Mem[at+1]) * 80;
  for i := 1 to Mem[at+3]-2 do
  begin
    FillVram(0,Vram,32,Mem[at+2]-2);
    Vram := Vram + 80;
  end;
  Mem[at+4] := 1;
  Mem[at+5] := 1;
end;