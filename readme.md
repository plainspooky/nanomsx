﻿
# milli
A GNU nano-like text editor for MSX 2.
It is based on [Qed-Pascal](http://texteditors.org/cgi-bin/wiki.pl?action=browse&diff=1&id=Qed-Pascal), and our main approach is to have almost all useful GNU nano funcionalities.
## Command-line parameters
 - /h 		- Show command line help.
 - /v 		- Show nanoMSX version.
 - /la          - Start at line a.
 - /cb          - Start at column b.
 - /tn          - Make a tab this number (n) of columns wide.

## Keystrokes already created
 - Control-S - Save current file
 - Control-O - Save as file (F3)
 - Control-P - Read new file
 - Control+Z - Close and exit from nano (F2)
 - Control+G - Display help text (F1)
 - Control+C - Report cursor position (F5)
 - Control+A - To start of line
 - Control+Y - One page up
 - Control+E - To end of line
 - Control+V - One page down
 - Control+F - One word backward
 - Control+D - One word forward
 - TAB - Indent marked region
 - SELECT+TAB - Unindent marked region
 - Cursor right - Character forward
 - Cursor up   - One line up
 - Cursor left  - Character backward
 - Cursor down - One line down
 - HOME - To start of file
 - CLS (SHIFT-HOME) - To end of file
 - Control+J - Align line (F4)
 - Control+W - Start forward search (F6)
 - Control+N - Start a replacing session
 - Control+Q - Start backward search (F8)
 - BS - Delete character before cursor
 - SELECT+W - Next occurrence forward
 - DEL - Delete character under cursor
 - SELECT+Q - Next occurrence backward
 - SELECT-DEL - Delete current line
 - SELECT-Y - Remove current line
 - Control+T - Go to specified line (F7)
 - SELECT-D - Report line/word/char count
 - SELECT+B - Mark beginning of text block
 - SELECT+E - Mark end of text block
 - SELECT+C - Copy block to line
 - SELECT+V - Move block to line
 - SELECT+F - Delete block

## To the future.
- ~~Fix problems regarding the use of MSX 2's VRAM.~~
- ~~Block routines, like copy/move/delete text blocks.~~
- Maybe a way of opening two files simultaneously.

MSX version by Ricardo Jurczyk Pinheiro - 2020/2022.
