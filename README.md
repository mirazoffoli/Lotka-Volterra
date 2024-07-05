# Lotka-Volterra

## Compilare con Cmake
Dalla cartella build (se non c'è, crearla):
```bash
cmake ..
make
``` 
Verranno creati del file nella cartella build

Nella cartella build verrà compilato l'eseguibile `main`.


## Compilare con g++

```bash
g++ src/Simulation.cpp src/main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system

./main
``` 

Per i test:
```bash
g++ test/test_simulazione.cpp src/Simulation.cpp -o test_simulazione

./test_simulazione
``` 
           