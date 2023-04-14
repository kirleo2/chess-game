# Chess Game

This is a semester project for Chess.

The goal was to implement a chess program based on the principle of polymorphism. The program was implemented in the terminal using only ASCII symbols.

The program implements all mandatory features of chess, including castling, en passant, and pawn promotion. Three levels of computer difficulty were also implemented: Easy (random moves), Medium (always captures the opponent's piece when possible), and "Artificial Intelligence" (minimax algorithm).

The program also has the ability to save and load a game in progress using a binary encoding that was created specifically for this purpose. Sample save files are included, which demonstrate the beginning of a game between two computers to showcase which one is "smarter".

Polymorphism was used in implementing the movement of pieces, with all pieces inheriting from the abstract class Figure and implementing the virtual method canMove. Polymorphism was also used in player control, with all players inheriting from the abstract class Player and implementing the virtual method move.

Documentation for the entire application and a Makefile, which is used to run it, are available. The following commands can be used with the Makefile:

- "make build" - compiles individual .cpp files.
- "make compile" - links object files and creates an executable file called "chess".
- "make run" - runs the application.
- "make clean" - clears all created files.
