milli
=====
A [GNU nano](https://nano-editor.org/)-like text editor for MSX2. It is based on [Qed-Pascal](http://texteditors.org/cgi-bin/wiki.pl?action=browse&diff=1&id=Qed-Pascal), and our main approach is to have almost all useful GNU nano funcionalities. There is a beautiful presentation [here](http://ricardojpinheiro.github.io/nanomsx/), if you want to see a more comprehensive explanation, and some screenshots too (we love screenshots, don't we?).


### Command-line parameters

| Parameter | Description                                                      |
| :-------: | :--------------------------------------------------------------- |
|   `/h `   | Show command line help.                                          |
|   `/v `   | Show nanoMSX version.                                            |
|   `/la`   | Start at line _a_.                                               |
|   `/cb`   | Start at column _b_.                                             |
|   `/tn`   | Make a tab this number (_n_) of columns wide.                    |
|   `/zn`   |	Tell **milli** the maximum number of lines that will be used*.   |

(*) It will speeds up the launch process

### Keystrokes already created

| Keystroke                                    | Function                       |
| :------------------------------------------: | :----------------------------- |
| <kbd>Ctrl</kbd>+<kbd>S</kbd> / <kbd>F3</kbd> | Save current file              |
| <kbd>Ctrl</kbd>+<kbd>O</kbd>                 | Save as file                   |
| <kbd>Ctrl</kbd>+<kbd>P</kbd>                 | Read new file                  |
| <kbd>Ctrl</kbd>+<kbd>Z</kbd> / <kbd>F2</kbd> | Close and exit from nano       |
| <kbd>Ctrl</kbd>+<kbd>G</kbd> / <kbd>F1</kbd> | Display help text              |
| <kbd>Ctrl</kbd>+<kbd>C</kbd> / <kbd>F5</kbd> | Report cursor position         |
| <kbd>Ctrl</kbd>+<kbd>A</kbd>                 | To start of line               |
| <kbd>Ctrl</kbd>+<kbd>Y</kbd>                 | One page up                    |
| <kbd>Ctrl</kbd>+<kbd>E</kbd>                 | To end of line                 |
| <kbd>Ctrl</kbd>+<kbd>V</kbd>                 | One page down                  |
| <kbd>Ctrl</kbd>+<kbd>F</kbd>                 | One word backward              |
| <kbd>Ctrl</kbd>+<kbd>D</kbd>                 | One word forward               |
| <kbd>Tab</kbd>                               | Indent marked region           |
| <kbd>Select</kbd> <kbd>Tab</kbd>             | Unindent marked region         |
| <kbd>→</kbd> (cursor right)                  | Character forward              |
| <kbd>←</kbd> (cursor up)                     | One line up                    |
| <kbd>↑</kbd> (cursor left)                   | Character backward             |
| <kbd>↓</kbd> (cursor down)                   | One line down                  |
| <kbd>Home</kbd>                              | To start of file               |
| <kbd>Shift</kbd>+<kbd>Home</kbd>             | To end of file                 |
| <kbd>Ctrl</kbd>+<kbd>J</kbd> / <kbd>F4</kbd> | Align line                     |
| <kbd>Ctrl</kbd>+<kbd>W</kbd> / <kbd>F6</kbd> | Start forward search           |
| <kbd>Ctrl</kbd>+<kbd>N</kbd>                 | Start a replacing session      |
| <kbd>Ctrl</kbd>+<kbd>Q</kbd> / <kbd>F8</kbd> | Start backward search          |
| <kbd>Ctrl</kbd>+<kbd>T</kbd> / <kbd>F7</kbd> | Go to specified line           |
| <kbd>Backspace</kbd>                         | Delete character before cursor |
| <kbd>Delete</kbd>                            | Delete character under cursor  |
| <kbd>Select</kbd> <kbd>Q</kbd>               | Next occurrence backward       |
| <kbd>Select</kbd> <kbd>DEL</kbd>             | Delete current line            |
| <kbd>Select</kbd> <kbd>D</kbd>               | Report line/word/char count    |
| <kbd>Select</kbd> <kbd>B</kbd>               | Mark beginning of text block   |
| <kbd>Select</kbd> <kbd>E</kbd>               | Mark end of text block         |
| <kbd>Select</kbd> <kbd>C</kbd>               | Copy block to line             |
| <kbd>Select</kbd> <kbd>V</kbd>               | Move block to line             |
| <kbd>Select</kbd> <kbd>F</kbd>               | Delete block                   |
| <kbd>Select</kbd> <kbd>H</kbd>               | Unhide block                   |
| <kbd>Select</kbd> <kbd>W</kbd>               | Next occurrence forward        |
| <kbd>Select</kbd> <kbd>Y</kbd>               | Remove current line            |

## To the future (features that I'm thinking about).
- ~~Fix problems regarding the use of MSX 2's VRAM.~~
- ~~Block routines, like copy/move/delete text blocks.~~
- ~~Visual references of marked blocks.~~
- Open two files simultaneously, and cut-copy-paste from one file to another.
- Line numbering, which would be easier to everybody who wants to write some code.
- Hide all elements of the interface (title bar, status bar, and help lines) and use all rows of the screen in order to see the buffer's contents. The status bar appears only when there is any m, and disappears slightly after or upon the next keystroke.

---
MSX version by Ricardo Jurczyk Pinheiro - 2020/2024.