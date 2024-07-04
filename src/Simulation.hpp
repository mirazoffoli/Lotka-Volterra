#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <string>

struct SimulationParameters {
  double initial_x;
  double initial_y;
  double A;
  double B;
  double C;
  double D;
  double dt;
};

class Simulation {
 private:
  // x prede, y predatori
  double current_x, current_y;

  // A: quanto le prede si riproducono (senza predatori, le prede aumentano di
  // Ax a iterazione)
  // B: tasso mortalità prede (che probabilità ha ogni predatore di uccidere
  // una preda)
  // C: quanto i predatori si riproducono
  // D: tasso mortalità predatori
  double A, B, C, D;

  // Valori di equilibrio
  // (Quando il sistema è in equilibrio, dovrebbero stabilizzarsi a 1)

  // Tempo globale e passo temporale della simulazione
  double t;
  double dt;

 public:
  Simulation(SimulationParameters const& params);

  // TODO Capire se aggiungere const
  double get_relative_x() const;
  double get_relative_y() const;
  double get_current_x() const;
  double get_current_y() const;
  double get_H() const;

  void evolve();
  std::string print_info() const;
};

#endif