Questo progetto ha lo scopo di simulare, tramite un programma in C++, il comportamento di
uno stormo di boids in uno spazio bidimensionale, sulla base di tre regole: separazione, allineamento
e coesione. Sono inoltre state aggiunte delle regole finalizzate a gestire il comportamento ai confini
dello schermo e il modulo della velocità dei boids.

# Compilazione ed esecuzione con g++
Per eseguire il programma tramite g++ è necessario aver installato la libreria grafica SFML e l'XServer MOBAXTERM.
I comandi da lanciare per la compilazione e l'esecuzione sono:
```
g++ -Wall -Wextra -fsanitize=address -lsfml-graphics -lsfml-window -lsfml-system
boids.cpp vector2D.cpp main.cpp -o boids
```
```
./boids
```
Mentre per i test sono necessari i comandi:
```
g++ -Wall -Wextra -fsanitize=address vector2D.cpp test vector2D.cpp -o test vector2D
```
```
./test
```
```
g++ -Wall -Wextra -fsanitize=address -lsfml-graphics -lsfml-window -lsfml-system
boids.cpp vector2D.cpp test rules.cpp -o test rules
```
```
./test rules
```

# Compilazione ed esecuzione con CMake
In alternativa, è possibile utilizzare CMake tramite i seguenti comandi (tutte le direttive sono
specificate nel file CMakeLists.txt):
```
cmake -S . -B build -DCMAKE BUILD TYPE=Release
```
```
cmake --build build
```
```
build/boids-sfml
```
```
build/rules.t
```
```
build/vector2D.t
```
