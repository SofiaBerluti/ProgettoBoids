#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <random>

#include "vector2D.hpp"
#include "Boids.hpp"
#include "rules.hpp"

void main() {

double window_height = sf::VideoMode::getDesktopMode().height * 0.9;
double window_width = sf::VideoMode::getDesktopMode().width * 0.9;

sf::Texture texture;
  texture.loadFromFile("sky.jpg");
  background_.setTexture(texture);

  background_.setScale(
      static_cast<float>(window_.getSize().x) / texture.getSize().x,
      static_cast<float>(window_.getSize().y) / texture.getSize().y);

  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window_.close();
    }
    window_.clear();
    window_.draw(background_);
    flock_.start();
    flock_.evolve();
    flock_.draw(window_);
    window_.display();

  return 0;

}