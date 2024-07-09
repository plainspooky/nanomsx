{fillvram.inc}
Procedure FillVram (VramBlockUsed: Byte; VramAddr: Integer;
            FillValue: Byte; ByteCount: Integer);

{ VramBlockUsed =   0 = first 64 Kb
                    1 = second 64 Kb
                    2 = Expansion Vram 64 Kb }

Begin
  If VramBlockUsed = 2 Then
    Expansion := $40 { Set the bit 6 (MXC) }
  Else
    Expansion := 0; { No expansion vram used  }

  AddrHi := Hi(VramAddr) Div $40;

  If VramBlockUsed = 1 Then
    AddrHi := AddrHi + 4 ;

  { Set addr bit 16 in reg 14 = bit 2 }
  AddrLo := Lo(VramAddr);
  AddrMid := Hi(Vramaddr) And 63 ;
  Inline(
    $F3/                        { di                                   }
    $3A/ Expansion /            { ld a,(`Expansion`)                   }
    $D3/$99/                    { out ($99),a                          }
    $3E/$2D/                    { ld a,$2d                             }
    $F6/$80/                    { or $80                               }
    $D3/$99/                    { out ($99),a                          }
    $3A/ AddrHi /               { ld a,(`AddrHi`)                      }
    $D3/$99/                    { out ($99),a                          }
    $3E/$0E/                    { ld a,$0e                             }
    $F6/$80/                    { or $80                               }
    $D3/$99/                    { out ($99),a                          }
    $3A/ AddrLo /               { ld a,(`AddrLo`)                      }
    $00/                        { nop                                  }
    $D3/$99/                    { out ($99),a                          }
    $3A/ AddrMid /              { ld a,(`AddrMid`)                     }
    $F6/$40/                    { or $40                               }
    $D3/$99/                    { out ($99),a                          }
    $ED/$4B/ ByteCount /        { ld bc,(`ByteCount`)                  }
    $3A/FillValue /             { ld a,(`FillValue`)                   }
    $D3/$98/                    { out ($98),a                          }
    $0B/$79/                    { dec bc                               }
    $B0/                        { ld a,c                               }
    $20/$F6/                    { jr nz,-8                             }
    $F3/                        { di                                   }
    $3e/ 0  /                   { ld a,$0                              }
    $D3/$99/                    { out ($99),a                          }
    $3E/$2D/                    { ld a,$2d                             }
    $F6/$80/                    { or $80                               }
    $D3/$99/                    { out ($99),a                          }
  );
End;
