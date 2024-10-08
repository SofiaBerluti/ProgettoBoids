#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>

#include "boids.hpp"
//#include "game.hpp"
#include "rules.hpp"
#include "vector2D.hpp"

int main() {
  Parameters parameters;

  std::cout << "\n \n SIMULATING FLOCK WITH BOIDS ALGORITHM \n \n"
            << "Do you want to proceed with default parameters? (Y/N)" << '\n';
  char choice;
  std::cin >> choice;
  if (choice == 'Y') {
    parameters.number = 170;
    parameters.separation = 0.4;
    parameters.alignment = 0.6;
    parameters.cohesion = 0.008;
    parameters.distance = 170;
    parameters.distance_separation = 30;
    parameters.view_angle = 2.5;
    parameters.space = toroidal;
    // parameters.window_width = window_width;
    // parameters.window_height = window_height};
  } else {
    try {
      std::cout << "Insert Number of Birds: ";
      std::cin >> parameters.number;

      if (parameters.number <= 0)
        throw std::runtime_error{"Number of birds is invalid"};

      std::cout << "Insert Separation Parameter: ";
      std::cin >> parameters.separation;

      if (parameters.separation < 0)
        throw std::runtime_error{"Separation coefficient is invalid"};

      std::cout << "Insert Alignment Parameter: ";
      std::cin >> parameters.alignment;

      if (parameters.alignment < 0)
        throw std::runtime_error{"Alignment coefficient is invalid"};

      std::cout << "Insert Cohesion Parameter: ";
      std::cin >> parameters.cohesion;

      if (parameters.cohesion < 0)
        throw std::runtime_error{"Cohesion coefficient is invalid"};

      std::cout << "Insert Distance: ";
      std::cin >> parameters.distance;

      if (parameters.distance < 0)
        throw std::runtime_error{"Distance is invalid"};

      std::cout << "Insert Separation Distance: ";
      std::cin >> parameters.distance_separation;

      if (parameters.distance_separation < 0)
        throw std::runtime_error{"Separation Distance is invalid"};

      std::cout << "Insert View Angle (0-3.14): ";
      std::cin >> parameters.view_angle;

      if (parameters.view_angle < 0)
        throw std::runtime_error{"Invalid angle value"};

      std::cout << "Select Space Type: \n (0) - Toroidal "
                   "\n (1) - Rectangular\n";
      int space_type;
      std::cin >> space_type;

      if (space_type < 0 || space_type > 1)
        throw std::runtime_error{"Invalid space type"};

      switch (space_type) {
        case 0:
          parameters.space = toroidal;
          break;
        case 1:
          parameters.space = rectangular;
          break;
      }
    } catch (const std::exception& e) {
      std::cerr << e.what() << '\n';
      return EXIT_FAILURE;
    }
  }

  Settings settings;
  settings.window_height = sf::VideoMode::getDesktopMode().height * 0.9;
  settings.window_width = sf::VideoMode::getDesktopMode().width * 0.9;
  settings.max_speed = 10.;
  settings.min_speed = 1.;

  int const fps = 60;

  sf::Sprite background;
  sf::Texture texture;
  sf::RenderWindow window(
      sf::VideoMode(settings.window_width, settings.window_height),
      "Boids simulation");

  window.setFramerateLimit(fps);
  // float steps_per_evolution = (1000 / fps);
  sf::Clock clock;

  Flock flock(parameters);

  texture.loadFromFile("sky.jpg");
  background.setTexture(texture);

  background.setScale(
      static_cast<float>(window.getSize().x) / texture.getSize().x,
      static_cast<float>(window.getSize().y) / texture.getSize().y);

  flock.start(settings);
  sf::Text stats;
  sf::Font font;
  font.loadFromFile("cmuntt.ttf");
  stats.setFont(font);
  stats.setCharacterSize(15);
  stats.setPosition(sf::Vector2f(0., 0.f));
  sf::RectangleShape box;
  box.setPosition(sf::Vector2f(0., 0.));
  box.setSize(sf::Vector2f(520., 40));
  box.setFillColor(
      sf::Color::Black);  // deve stare fuori dal ciclo principale del programma

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    window.clear();
    window.draw(background);

    sf::Time elapsed =
        clock.restart();  // Restarta il clock e ottiene il delta time
    float deltaTime = elapsed.asMilliseconds();
    // double const dt = deltaTime.asSeconds();
    if (deltaTime > 1.f) {
      deltaTime = 1.f;  // Limita il deltaTime se superiore a 1 secondo
    }

    flock.evolve(deltaTime, settings);

    flock.draw(window);
    stats.setString(flock.get_statistics());
    window.draw(box);
    window.draw(stats);
    window.display();
  }
  // Game game ("Boids Simulation", parameters, background);
  // game.run();

  return 0;
}

/* PARAMETRI CARINI
Insert Number of Birds: 300
Insert Separation Parameter: 0.3
Insert Alignment Parameter: 0.2
Insert Cohesion Parameter: 0.005
Insert Distance: 170
Insert Separation Distance: 30
Insert View Angle (0-3.14): 3
Select Space Type:
 (0) - Toroidal
 (1) - Rectangular
0 */