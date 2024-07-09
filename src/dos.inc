(*<dos.inc> CopyLeft (c) since 1995 by PopolonY2k. *)
procedure MSXBDOS( var regs : TRegs );
var
  nA, nF         : Byte;
  nHL, nDE, nBC  : Integer;
  nIX, nIY       : Integer;
begin
  nA  := regs.A;
  nHL := regs.HL;
  nDE := regs.DE;
  nBC := regs.BC;
  nIX := regs.IX;
  nIY := regs.IY;

  inline( $F5/                  { PUSH AF      ; Push all registers  }
    $C5/                  { PUSH BC                            }
    $D5/                  { PUSH DE                            }
    $E5/                  { PUSH HL                            }
    $DD/$E5/              { PUSH IX                            }
    $FD/$E5/              { PUSH IY                            }
    $3A/nA/               { LD A , (nA )                       }
    $ED/$4B/nBC/          { LD BC, (nBC)                       }
    $ED/$5B/nDE/          { LD DE, (nDE)                       }
    $2A/nHL/              { LD HL, (nHL)                       }
    $DD/$2A/nIX/          { LD IX, (nIX)                       }
    $FD/$2A/nIY/          { LD IY, (nIY)                       }
    $CD/$05/$00/          { CALL 0005H - BDOS call             }
    $32/nA/               { LD (nA ), A                        }
    $ED/$43/nBC/          { LD (nBC), BC                       }
    $ED/$53/nDE/          { LD (nDE), DE                       }
    $22/nHL/              { LD (nHL), HL                       }
    $DD/$22/nIX/          { LD (nIX), IX                       }
    $FD/$22/nIY/          { LD (nIY), IY                       }
    $F5/                  { PUSH AF                            }
    $E1/                  { POP HL                             }
    $22/nF/               { LD (nF), HL                        }
    $FD/$E1/              { POP YI       ; Pop all registers   }
    $DD/$E1/              { POP IX                             }
    $E1/                  { POP HL                             }
    $D1/                  { POP DE                             }
    $C1/                  { POP BC                             }
    $F1                   { POP AF                             }
  );

  (* Update caller register struct *)
  regs.A  := nA;
  regs.F  := nF;
  regs.BC := nBC;
  regs.DE := nDE;
  regs.HL := nHL;
  regs.IY := nIY;
  regs.IX := nIX;
end;

procedure GetMSXDOSVersion( var version : TMSXDOSVersion );
begin
  FillChar( regs, SizeOf( regs ), 0 );
  regs.C:= ctGetMSXDOSVersionNumber;
  MSXBDOS( regs );

  if( regs.A = 0 )  then
    with version do
    begin
      nKernelMajor := regs.B;
      nKernelMinor := regs.C;
      nSystemMajor := regs.D;
      nSystemMinor := regs.E;
    end;
end;