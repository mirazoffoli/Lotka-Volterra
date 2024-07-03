#include "Simulation.hpp"

#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>

void check_parameters(SimulationParameters& params) {
  if (params.initial_x < 0) {
    std::cerr << "Il numero iniziale di prede deve essere >= 0" << std::endl;
    throw std::invalid_argument("Invalid parameter value initial_x");
  }

  if (params.initial_y < 0) {
    std::cerr << "Il numero iniziale di predatori deve essere >= 0"
              << std::endl;
    throw std::invalid_argument("Invalid parameter value initial_y");
  }

  if (params.A <= 0) {
    std::cerr << "Il parametro A deve essere > 0" << std::endl;
    throw std::invalid_argument("Invalid parameter value A");
  }

  if (params.B <= 0) {
    std::cerr << "Il parametro B deve essere > 0" << std::endl;
    throw std::invalid_argument("Invalid parameter value B");
  }

  if (params.C <= 0) {
    std::cerr << "Il parametro C deve essere > 0" << std::endl;
    throw std::invalid_argument("Invalid parameter value C");
  }

  if (params.D <= 0) {
    std::cerr << "Il parametro D deve essere > 0" << std::endl;
    throw std::invalid_argument("Invalid parameter value D");
  }

  if (params.dt <= 0) {
    std::cerr << "Il passo temporale dt deve essere > 0" << params.dt
              << std::endl;
    throw std::invalid_argument("Invalid parameter value dt");
  }
}

// Metodo costruttore
Simulation::Simulation(SimulationParameters params) {
  // Controllo dei parametri
  check_parameters(params);

  // Inizializzazione
  this->current_x = params.initial_x;
  this->current_y = params.initial_y;
  this->A = params.A;
  this->B = params.B;
  this->C = params.C;
  this->D = params.D;
  this->t = 0.0;
  this->dt = params.dt;
}

// Calcolo di x e y relativi al punto di equilibrio
// Gestisco il caso in cui il punto di equilibrio sia 0
double Simulation::get_relative_x() {
  double x_eq = D / C;
  return (x_eq != 0) ? (current_x / x_eq) : 0;
}
double Simulation::get_relative_y() {
  double y_eq = A / B;
  return (y_eq != 0) ? (current_y / y_eq) : 0;
}

double Simulation::get_current_x() { return current_x; }
double Simulation::get_current_y() { return current_y; }

// Calcolo dell'integrale primitivo H(x, y)
double Simulation::get_H() {
  return -D * log(current_x) + C * current_x + B * current_y -
         A * log(current_y);
}

void Simulation::evolve() {
  t += dt;

  // Aggiorno i valori di x e y
  double old_x = current_x;
  double old_y = current_y;

  current_x += (A * old_x - B * old_x * old_y) * dt;
  current_y += (C * old_x * old_y - D * old_y) * dt;

  // Controllo che il valore corrente di x e y non sia negativo
  if (current_x <= 0 || current_y <= 0) {
    std::cerr << "Errore: i valori di x e y non possono diventare zero o "
                 "negativi.\n";
    throw std::runtime_error(
        "Invalid state: x and y cannot be zero or negative");
  }

  // Controllo che il valore corrente di x e y non sia infinito
  if (std::isinf(current_x) || std::isinf(current_y)) {
    std::cerr << "Errore: overflow durante la simulazione.\n";
    throw std::runtime_error("Overflow during simulation");
  }
}

std::string Simulation::to_string() {
  std::ostringstream oss;

  oss << "x(" << t << ") = " << current_x
      << ", x_rel = " << this->get_relative_x() << std::endl;

  oss << "y(" << t << ") = " << current_y
      << ", y_rel = " << this->get_relative_y() << std::endl;

  oss << "H(" << current_x << ", " << current_y << ") = " << this->get_H()
      << std::endl
      << std::endl;

  return oss.str();
}
