# Hello!

I got bored one day and made minesweeper to cure that boredom.
to make, simply run `gcc main.c -o minesweeper` in a linux terminal, and it will output a binary named `minesweeper.`
Each cell has an index starting from 0 0 on the top left, to 8 8 on the bottom right, making a 9x9 grid.
To play:
- run the executable.
- flag a cell by running `X Y f`, where `X` is the X coordinate ranging from 0 to 8, and `Y` is the Y coordinate ranging from 0 to 8.
  - flagged cells cannot be revealed.
- reveal a cell by running `X Y b`, where `X` and `Y` are the X and Y coordinates ranging from 0 to 8 respectively.
You can change the size of the board by modifying the source file. At the top of the file, there are constants `WIDTH` and `HEIGHT` that change the width and height of the board respectively. Good luck and may the force be with you! or something. I never watched star trek before.  
