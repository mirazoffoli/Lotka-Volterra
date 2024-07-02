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
g++ -std=c++11 src/algorithm.cpp src/main_algorithm.cpp -o main_algorithm
./main_algorithm
``` 

Per i test:
```bash
g++ -std=c++11 test/test_simulazione.cpp src/algorithm.cpp -o test_simulazione
``` 
           