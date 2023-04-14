Semestrální práce Šachy.

Mým cílem bylo realizovat šachový program, založený na principu polimorfismu. 
Realizoval jsem to v terminálu s využitím jenom ASCI symbolů.
Můj program implementuje všechny povinné body :
Jsou dodrženy všechna pravidla klasické varianty : Rošáda, Braní mimochodem a proměna pěšce.
Implementoval jsem rovněž tři druhy složitosti počítače: lehký (náhodné tahy), průměrný (vždy sní figuru soupeře při možnosti) a "umělá inteligence" (minimax algoritmus).
Také realizoval jsem možnost ukládání rozehrané hry a možnost pak hru načíst a pokračovat. 
K tomu jsem využil binární kódování které jsem si sám vymyslel. V ukázkových save filech mám začátek hry dvou počítačů aby bylo vidět, který je "chytřeji".
Polymorfismus jsem využil v realizaci pohybu figurek - všechny figury dědí od abstraktní třídy Figure a následně implementují virtuální metodu canMove a také jsem využil polymorfismus v ovládání hráčů - všechny hrače dědí od abstraktní třídy Player a implementují virtuální metodu move.

Semester project Chess.

My goal was to implement a chess program based on the principle of polymorphism.
I implemented the program in the terminal using only ASCII symbols.
My program implements all mandatory features: Castling, En Passant, and Pawn Promotion.
I also implemented three levels of computer difficulty: Easy (random moves), Medium (always captures opponent's piece when possible), and "Artificial Intelligence" (minimax algorithm).
I also implemented the ability to save and load a game in progress using a binary encoding I created myself. In the sample save files, I have the beginning of a game between two computers to demonstrate which one is "smarter".
I used polymorphism in implementing the movement of pieces - all pieces inherit from the abstract class Figure and subsequently implement the virtual method canMove, and I also used polymorphism in player control - all players inherit from the abstract class Player and implement the virtual method move.
