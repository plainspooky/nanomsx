{Needs wrtvram.inc }

procedure _WrtVdp(Port, Value: Byte);
begin
  inline (
    $F3/                        { DI                                   }
    $3A/ Value /                { LD A,(`Value`)                       }
    $D3/$99/                    { OUT ($99),A                          }
    $3A/ Port /                 { LD A,(`Port`)                        }
    $F6/$80/                    { OR $80                               }
    $D3/$99                     { OUT ($99),A                          }
  );
end;

procedure SetBlinkRate(OnTime, OffTime: Byte);
begin
  _WrtVdp(Vdp14,  OnTime * 16 + OffTime);
end;

procedure SetBlinkColors(ForegroundColor, BackgroundColor:  Byte);
begin
  _WrtVdp(Vdp13,  ForegroundColor * 16 + BackgroundColor);
end;

procedure SetBit(TableAddr, BitNumber: Byte; Operation: Boolean);
begin
  Byt := ColTbl[TableAddr];
  if Operation = SetB then
    Byt := Byt or MaskTable[BitNumber]
  else
    Byt := Byt and (255 - MaskTable[BitNumber]);
  ColTbl[TableAddr] := Byt;
end;

procedure BlinkChar(Col, Row: Byte);
begin
  TableAddr :=  ((Row - 1) * 80 + Col - 1) div 8;
  Byt       :=  ((Row - 1) * 80 + Col - 1) mod 8;
  SetBit(TableAddr, Byt, SetB);
  WriteVram(0, TXTCOL + TableAddr, Addr(ColTbl[TableAddr]), 1);
end;

procedure ClearBlinkChar(Col, Row: Byte);
begin
  TableAddr :=  ((Row - 1) * 80 + Col - 1) div 8;
  Byt       :=  ((Row - 1) * 80 + Col - 1) mod 8;
  SetBit(TableAddr, Byt, ResB);
  WriteVram(0, TXTCOL + TableAddr, Addr(ColTbl[TableAddr]), 1);
end;

procedure Blink(Col, Row, Len: Byte);
var
  TableAddr:  Integer;
  Byt, i:     Byte;

begin
  TableAddr := ((Row - 1) * 80 + Col - 1) div 8;
  Byt       := ((Row - 1) * 80 + Col - 1) mod 8;

  for i:= 1 to Len do
  begin
    SetBit(TableAddr, Byt, SetB);
    Byt := Byt + 1;
    if Byt = 8 then
    begin
      Byt := 0;
      TableAddr := TableAddr + 1;
    end;
  end;
  WriteVram(0, TXTCOL, Addr(ColTbl), 256);
end;

procedure ClearBlink(Col, Row, Len: Byte);
var
  Byt, i:     Byte;
  TableAddr:  Integer;

begin
  TableAddr :=  ((Row - 1) * 80 + Col - 1) div 8;
  Byt       :=  ((Row - 1) * 80 + Col - 1) mod 8;

  for i:= 1 to Len do
  begin
    SetBit(TableAddr, Byt, ResB);
    Byt := Byt + 1;
    if Byt = 8 then
    begin
      Byt := 0;
      TableAddr := TableAddr + 1;
    end;
  end;
  WriteVram(0, TXTCOL, Addr(ColTbl), 256);
end;

procedure ClearAllBlinks;
begin
  FillChar(ColTbl, 256, 0);
  WriteVram(0, TXTCOL, Addr(ColTbl), 256);
end;

procedure CursorBlink(Len: Byte);
begin
  Blink(CSRX, CSRY, Len);
end;

procedure ClearCursorBlink(Len: Byte);
begin
  ClearBlink(CSRX, CSRY, Len);
end;