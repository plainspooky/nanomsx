{fillvram.inc}
procedure FillVram (VramBlockUsed: Byte; VramAddr: Integer;
            FillValue: Byte; ByteCount: Integer);

{ VramBlockUsed =   0 = first 64 Kb
                    1 = second 64 Kb
                    2 = Expansion Vram 64 Kb }

begin
  if VramBlockUsed = 2 Then
    Expansion := $40 { Set the bit 6 (MXC) }
  else
    Expansion := 0; { No expansion vram used  }

  AddrHi := Hi(VramAddr) Div $40;

  if VramBlockUsed = 1 Then
    AddrHi := AddrHi + 4 ;

  { Set addr bit 16 in reg 14 = bit 2 }
  AddrLo := Lo(VramAddr);
  AddrMid := Hi(Vramaddr) And 63;

  inline(
    $F3/                        { DI                                   }
    $3A/ Expansion /            { LD A,(`Expansion`)                   }
    $D3/$99/                    { OUT ($99),A                          }
    $3E/$2D/                    { LD A,$2D                             }
    $F6/$80/                    { OR $80                               }
    $D3/$99/                    { OUT ($99),A                          }
    $3A/ AddrHi /               { LD A,(`AddrHi`)                      }
    $D3/$99/                    { OUT ($99),A                          }
    $3E/$0E/                    { LD A,$0E                             }
    $F6/$80/                    { OR $80                               }
    $D3/$99/                    { OUT ($99),A                          }
    $3A/ AddrLo /               { LD A,(`AddrLo`)                      }
    $00/                        { NOP                                  }
    $D3/$99/                    { OUT ($99),A                          }
    $3A/ AddrMid /              { LD A,(`AddrMid`)                     }
    $F6/$40/                    { OR $40                               }
    $D3/$99/                    { OUT ($99),A                          }
    $ED/$4B/ ByteCount /        { LD BC,(`ByteCount`)                  }
    $3A/FillValue /             { LOOP: LD A,(`FillValue`)             }
    $D3/$98/                    {       OUT ($98),A                    }
    $0B/$79/                    {       DEC BC                         }
    $B0/                        {       LD A,C                         }
    $20/$F6/                    {       JR NZ,LOOP                     }
    $F3/                        { DI                                   }
    $3e/ 0  /                   { LD A,$0                              }
    $D3/$99/                    { OUT ($99),A                          }
    $3E/$2D/                    { LD A,$2D                             }
    $F6/$80/                    { OR $80                               }
    $D3/$99/                    { OUT ($99),A                          }
  );
end;