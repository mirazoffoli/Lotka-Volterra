#include <SFML/Graphics.hpp>
#include <cmath>
#include <fstream>
#include <iostream>

#include "Simulation.hpp"

// Inserimento dei parametri da riga di comando a tempo di esecuzione
void insert_parameters(SimulationParameters& params) {
  std::cout << "Inserisci il numero iniziale di prede (x): ";
  std::cin >> params.initial_x;
  std::cout << "Inserisci il numero iniziale di predatori (y): ";
  std::cin >> params.initial_y;
  std::cout << "Inserisci il valore del parametro A: ";
  std::cin >> params.A;
  std::cout << "Inserisci il valore del parametro B: ";
  std::cin >> params.B;
  std::cout << "Inserisci il valore del parametro C: ";
  std::cin >> params.C;
  std::cout << "Inserisci il valore del parametro D: ";
  std::cin >> params.D;
  std::cout << "Inserisci il passo temporale dt: ";
  std::cin >> params.dt;
}

int main(int argc, char *argv[]) {
  SimulationParameters params;

  // Numero di passi da simulare
  int steps;

  // Numero sbagliato di parametri
  if (argc != 8 && argc != 1) {
    std::cerr << "Inserire 0 o 7 parametri da riga di comando" << std::endl;
    return 1;
  }

  // Parametri specificati come argomenti di invocazione
  if (argc == 8) {
    params.initial_x = std::stod(argv[1]);
    params.initial_y = std::stod(argv[2]);
    params.A = std::stod(argv[3]);
    params.B = std::stod(argv[4]);
    params.C = std::stod(argv[5]);
    params.D = std::stod(argv[6]);
    params.dt = std::stod(argv[7]);
  }
  // Parametri specificati da riga di comando
  else if (argc == 1) {
    insert_parameters(params);
  }

  std::cout << "Quanti passi vuoi simulare? ";
  std::cin >> steps;

  Simulation simulation(params);

  // Apro il file di testo su cui salvare i risultati
  std::ofstream file("simulation_output.txt");
  if (!file.is_open()) {
    std::cerr << "Errore nell'apertura del file dei risultati" << std::endl;
    return 1;
  }

  // Salvo i parametri della simulazione separati da spazi
  /* file << params.dt << " ";
  file << params.A << " ";
  file << params.B << " ";
  file << params.C << " ";
  file << params.D << "\n"; */

  for (int i = 0; i < steps; ++i) {
    // Salvo lo stato della simulazione su file
    file << simulation.get_current_x() << " ";
    file << simulation.get_current_y() << std::endl;

    // Stampo a schermo lo stato
    std::cout << simulation.print_info() << std::endl;

    // Mando avanti la simulazione
    simulation.evolve();
  }

  // Chiusura del file dei risultati, gestendo eventuali errori
  file.close();
  if (file.fail()) {
    std::cerr << "Errore durante la chiusura del file dei risultati"
              << std::endl;
    return 1;
  };

  // parte grafica
  unsigned const display_height =
      0.9 * sf::VideoMode::getDesktopMode().height;  
  int const fps = 60;                                // frame per second

  sf::RenderWindow window(sf::VideoMode(display_height, display_height),
                          "Lotka.Volterra", sf::Style::Default);
  window.setFramerateLimit(fps);

  while (window.isOpen()) {
    sf::Event e;

    while (window.pollEvent(e)) {
      if (e.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color::White);

    std::ifstream input;
    input.open("simulation_output.txt");

    while (input.good()) {
      double x;
      double y;
      input >> x >> y;
      sf::CircleShape shape = sf::CircleShape(2);
      shape.setPosition((x / 3) * display_height, (y / 7) * display_height);
      shape.setFillColor(sf::Color::Black);
      window.draw(shape);
    }

    window.display();
  }
}