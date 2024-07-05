#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <stdexcept>

#include "../src/Simulation.hpp"
#include "doctest.h"

// Definizione della macro per i test case
#define TEST_CASE(name) DOCTEST_TEST_CASE(name)

// Test per verificare il controllo dei parametri iniziali
TEST_CASE("Check initial parameters") {
  SimulationParameters params;

  SUBCASE("Valid parameters") {
    params.initial_x = 1.8;
    params.initial_y = 4.3;
    params.A = 0.1;
    params.B = 0.02;
    params.C = 0.05;
    params.D = 0.1;
    params.dt = 0.1;

    CHECK_NOTHROW({
      Simulation s = Simulation(params);
      (void)s;  // faccio cast esplicito a void
    });
  }

  SUBCASE("Negative initial_x") {
    params.initial_x = -1.0;
    params.initial_y = 4.3;
    params.A = 0.1;
    params.B = 0.02;
    params.C = 0.05;
    params.D = 0.1;
    params.dt = 0.1;

    CHECK_THROWS_AS(
        {
          Simulation s = Simulation(params);
          (void)s;  // faccio cast esplicito a void
        },
        std::invalid_argument);
  }

  SUBCASE("Negative initial_y") {
    params.initial_x = 1.8;
    params.initial_y = -4.3;
    params.A = 0.1;
    params.B = 0.02;
    params.C = 0.05;
    params.D = 0.1;
    params.dt = 0.1;

    CHECK_THROWS_AS(
        {
          Simulation s = Simulation(params);
          (void)s;  // faccio cast esplicito a void
        },
        std::invalid_argument);
  }

  // test parametri invalidi
  SUBCASE("Zero A") {
    params.initial_x = 1.8;
    params.initial_y = 4.3;
    params.A = 0.0;
    params.B = 0.02;
    params.C = 0.05;
    params.D = 0.1;
    params.dt = 0.1;

    CHECK_THROWS_AS(
        {
          Simulation s = Simulation(params);
          (void)s;  // faccio cast esplicito a void
        },
        std::invalid_argument);
  }

  SUBCASE("Zero B") {
    params.initial_x = 1.8;
    params.initial_y = 4.3;
    params.A = 0.1;
    params.B = 0.0;
    params.C = 0.05;
    params.D = 0.1;
    params.dt = 0.1;

    CHECK_THROWS_AS(
        {
          Simulation s = Simulation(params);
          (void)s;  // faccio cast esplicito a void
        },
        std::invalid_argument);
  }

  SUBCASE("Zero C") {
    params.initial_x = 1.8;
    params.initial_y = 4.3;
    params.A = 0.1;
    params.B = 0.02;
    params.C = 0.0;
    params.D = 0.1;
    params.dt = 0.1;

    CHECK_THROWS_AS(
        {
          Simulation s = Simulation(params);
          (void)s;  // faccio cast esplicito a void
        },
        std::invalid_argument);
  }

  SUBCASE("Zero D") {
    params.initial_x = 1.8;
    params.initial_y = 4.3;
    params.A = 0.1;
    params.B = 0.02;
    params.C = 0.05;
    params.D = 0.0;
    params.dt = 0.1;

    CHECK_THROWS_AS(
        {
          Simulation s = Simulation(params);
          (void)s;  // faccio cast esplicito a void
        },
        std::invalid_argument);
  }

  SUBCASE("Negative dt") {
    params.initial_x = 1.8;
    params.initial_y = 4.3;
    params.A = 0.1;
    params.B = 0.02;
    params.C = 0.05;
    params.D = 0.1;
    params.dt = -0.1;

    CHECK_THROWS_AS(
        {
          Simulation s = Simulation(params);
          (void)s;  // faccio cast esplicito a void
        },
        std::invalid_argument);
  }
}

// Test per verificare l'evoluzione delle popolazioni nel tempo
TEST_CASE("Evolution of populations") {
  SimulationParameters params;
  params.initial_x = 1.8;
  params.initial_y = 4.3;
  params.A = 0.1;
  params.B = 0.02;
  params.C = 0.05;
  params.D = 0.1;
  params.dt = 0.1;

  Simulation simulation(params);

  // Verifica che l'evoluzione non lanci eccezioni
  CHECK_NOTHROW(simulation.evolve());

  // Verifica che le popolazioni non diventino negative o infinite
  for (int i = 0; i < 100; ++i) {
    simulation.evolve();
    CHECK(simulation.get_current_x() >= 0.0);
    CHECK(simulation.get_current_y() >= 0.0);
    CHECK_FALSE(std::isinf(simulation.get_current_x()));
    CHECK_FALSE(std::isinf(simulation.get_current_y()));
  }
}

// Test per verificare il calcolo dei valori relativi
TEST_CASE("Relative values calculation") {
  SimulationParameters params;
  params.initial_x = 1.8;
  params.initial_y = 4.3;
  params.A = 0.1;
  params.B = 0.02;
  params.C = 0.05;
  params.D = 0.1;
  params.dt = 0.1;

  Simulation simulation(params);

  double x_eq = params.D / params.C;
  double y_eq = params.A / params.B;

  CHECK(simulation.get_relative_x() ==
        doctest::Approx(params.initial_x / x_eq));
  CHECK(simulation.get_relative_y() ==
        doctest::Approx(params.initial_y / y_eq));
}

// Test per verificare il calcolo dell'integrale primitivo H(x, y)
TEST_CASE("Primitive integral H(x, y)") {
  SimulationParameters params;
  params.initial_x = 1.8;
  params.initial_y = 4.3;
  params.A = 0.1;
  params.B = 0.02;
  params.C = 0.05;
  params.D = 0.1;
  params.dt = 0.1;

  Simulation simulation(params);

  double expected_H =
      -params.D * std::log(params.initial_x) + params.C * params.initial_x +
      params.B * params.initial_y - params.A * std::log(params.initial_y);

  CHECK(simulation.get_H() == doctest::Approx(expected_H).epsilon(0.01));
}

// Test per verificare la stringa di stato della simulazione
TEST_CASE("Simulation state string") {
  SimulationParameters params;
  params.initial_x = 1.8;
  params.initial_y = 4.3;
  params.A = 0.1;
  params.B = 0.02;
  params.C = 0.05;
  params.D = 0.1;
  params.dt = 0.1;

  Simulation simulation(params);
  std::string state = simulation.print_info();

  CHECK(state.find("x(0) = 1.8") != std::string::npos);
  CHECK(state.find("y(0) = 4.3") != std::string::npos);
}

// Test per verificare la validità dei parametri nel metodo evolve
TEST_CASE("Evolve method parameter validity") {
  SimulationParameters params;
  params.initial_x = 1.8;
  params.initial_y = 4.3;
  params.A = 0.1;
  params.B = 0.02;
  params.C = 0.05;
  params.D = 0.1;
  params.dt = 0.1;

  // Caso di valori negativi
  params.initial_x = -1.0;
  params.initial_y = -1.0;

  // Controlla che il costruttore lanci una eccezione per parametri  non validi
  CHECK_THROWS_AS(Simulation simNegative(params), std::invalid_argument);
}
