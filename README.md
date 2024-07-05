# Lotka-Volterra

## Compilare con Cmake
Dalla cartella build (se non c'è, crearla):
```bash
cmake ..
make
``` 
Verranno creati dei file nella cartella build, tra cui l'eseguibile `main`.


## Compilare con g++
Per compilare il programma:

```bash
g++ src/Simulation.cpp src/main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system
``` 

Per compilare i test:
```bash
g++ test/test_simulazione.cpp src/Simulation.cpp -o test_simulazione
``` 

## Eseguire il programma e i test
Per eseguire il programma, una volta compilato:
```bash
./main 
``` 
(eventualmente, si possono specificare come argomenti di invocazione i parametri della simulazione)

Per eseguire i test, una volta compilati: 
```bash
./test_simulazione
``` 


           