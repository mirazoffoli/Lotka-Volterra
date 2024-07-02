#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <stdexcept>

#include "../src/Simulation.hpp"
#include "doctest.h"

TEST_CASE("Test costruttore Simulazione con parametri validi") {
  SimulationParameters params;
  params.initial_x = 2000;
  params.initial_y = 10;
  params.A = 0.1;
  params.B = 0.02;
  params.C = 0.05;
  params.D = 0.1;
  params.dt = 0.01;

  Simulation sim(params);

  CHECK(sim.get_relative_x() == 1);
  CHECK(sim.get_relative_y() == 1);
  CHECK(sim.get_H() == 0);
}

TEST_CASE("Test costruttore Simulazione con parametri validi") {
  SimulationParameters params;
  params.initial_x = 0;
  params.initial_y = 0;
  params.A = 1;
  params.B = 1;
  params.C = 1;
  params.D = 1;
  params.dt = 0.001;

  Simulation sim(params);

  CHECK(sim.get_relative_x() == 0);
  CHECK(sim.get_relative_y() == 0);
  CHECK(sim.get_H() == 0);
}

TEST_CASE("Test costruttore Simulazione con parametri NON validi") {
  SimulationParameters params;
  params.initial_x = -1;
  params.initial_y = 0;
  params.A = 1;
  params.B = 1;
  params.C = 1;
  params.D = 1;
  params.dt = 0.1;

  CHECK_THROWS_AS(Simulation sim(params), std::invalid_argument);
}

TEST_CASE("Test costruttore Simulazione con parametri NON validi") {
  SimulationParameters params;
  params.initial_x = 0;
  params.initial_y = -1;
  params.A = 1;
  params.B = 1;
  params.C = 1;
  params.D = 1;
  params.dt = 0.1;

  CHECK_THROWS_AS(Simulation sim(params), std::invalid_argument);
}

TEST_CASE("Test costruttore Simulazione con parametri NON validi") {
  SimulationParameters params;
  params.initial_x = 0;
  params.initial_y = 0;
  params.A = -1;
  params.B = 1;
  params.C = 1;
  params.D = 1;
  params.dt = 0.1;

  CHECK_THROWS_AS(Simulation sim(params), std::invalid_argument);
}

TEST_CASE("Test costruttore Simulazione con parametri NON validi") {
  SimulationParameters params;
  params.initial_x = 0;
  params.initial_y = 0;
  params.A = 1;
  params.B = -1;
  params.C = 1;
  params.D = 1;
  params.dt = 0.1;

  CHECK_THROWS_AS(Simulation sim(params), std::invalid_argument);
}

TEST_CASE("Test costruttore Simulazione con parametri NON validi") {}

TEST_CASE("Test costruttore Simulazione con parametri strani") {}

TEST_CASE(
    "Test che la simulazione si evolva mantenendo un X e Yrelativo positivo o "
    "nullo ") {}
