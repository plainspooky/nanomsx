procedure ReadVram (VramBlockUsed:Byte; VramAddr, RamAddr, ByteCount: Integer);

{ VramBlockUsed  =  0 = first 64 Kb
                    1 = second 64 Kb
                    2 = Expansion Vram 64 Kb }
begin
  if VramBlockUsed = 2 then
    Expansion := $40 {Set the bit 6 (MXC) }
  else
    Expansion := 0 ; {No expansion vram used}
  AddrHi := Hi(VramAddr) div $40;
  if VramBlockUsed = 1 then
    AddrHi := AddrHi + 4 ;  {Set addr bit 16 in reg 14 = bit 2 }
  AddrLo := Lo(VramAddr);
  AddrMid := Hi(Vramaddr) and 63;
  inline(
    $F3/$3A/ Expansion /$D3/$99/$3E/$2D/$F6/$80/$D3/$99/$3A/ AddrHi /$D3/
    $99/$3E/$0E/$F6/$80/$D3/$99/$3A/ AddrLo /$D3/$99/$3A/ AddrMid /$F6/
    $00/$D3/$99/$ED/$5B/ RamAddr /$ED/$4B/ ByteCount /$DB/$98/$12/$13/$0B/
    $79/$B0/$20/$F7/$3E/ 0 /$D3/$99/$3E/$2D/$F6/$80/$D3/$99
  );
end;