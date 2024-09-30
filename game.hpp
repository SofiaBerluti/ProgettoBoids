#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <string>

#include "Boids.hpp"

class Game {
 private:
  sf::RenderWindow window_;
  Flock flock_;
  sf::Sprite background_;

 public:
  Game(std::string const& title, Parameters &parameters, sf::Sprite const& background);
  void run();
};

#endif