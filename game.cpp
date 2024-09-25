#include "game.hpp"

#include <SFML/Graphics.hpp>

#include "rules.hpp"

/*Game::Game(std::string const& title, sf::Texture const texture)
    : title{title} {};

      void Game::run() {
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
  }*/