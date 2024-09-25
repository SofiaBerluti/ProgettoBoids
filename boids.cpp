#include "Boids.hpp"

#include <SFML/Graphics.hpp>

#include "rules.hpp"
//#include <cassert>
//#include <cmath>
//#include <fstream>
//#include <iostream>
//#include <random>

Flock::Flock(auto distance, auto separation, auto InfluenceRange,
             double alignment, double cohesion, double view_angle,
             double distance_separation, double window_width,
             double window_height)
    : distance_{distance},
      separation_{separation},
      InfluenceRange_{InfluenceRange},
      alignment_{alignment},
      cohesion_{cohesion},
      view_angle_{view_angle},
      distance_separation_{distance_separation},
      window_width_{window_width},
      window_height_{window_height} {};

// std::vector<Bird> Flock::get_flock() const { return flock_; };

/*void Bird::update(float deltaTime, std::vector<Bird> flock, Bird &bird,
            double distance_, double view_angle_, double distance_separation_,
            double separation_, double alignment_, double cohesion_) {
  std::for_each(
      flock.begin(), flock.end(),
      [&](Bird &bird) {
        std::vector<Bird> neighbours =
            get_neighbours(flock, bird, distance_, view_angle_);
        if (neighbours.size() != 0) {
          bird.velocity +=
              (separation(neighbours, bird, distance_separation_, separation_));
          bird.velocity += (alignment(neighbours, bird, alignment_));
          bird.velocity += (cohesion(neighbours, bird, cohesion_));
        }
        avoid_speeding(flock);
        boundaries_behavior(bird, window_width, window_height, space);
        bird.position += bird.velocity *
                         deltaTime;  // Scala la velocità per il tempo trascorso
      }

  );
}*/
void Flock::start() {
  std::random_device rd;  // set seed
  std::default_random_engine gen(rd());
  std::uniform_real_distribution<double> pos_x(0, window_width_);
  std::uniform_real_distribution<double> pos_y(0, window_height_);
  std::uniform_real_distribution<double> speed(-5, 5);

  std::generate(flock_.begin(), flock_.end(), [&]() -> Bird {
    return {Vector2D{pos_x(gen), pos_y(gen)}, Vector2D{speed(gen), speed(gen)}};
  });
}

void Flock::evolve() {
  sf::Clock clock;
  sf::Time elapsed =
      clock.restart();  // Restarta il clock e ottiene il delta time
  float deltaTime = elapsed.asSeconds();
  std::for_each(
      flock_.begin(), flock_.end(),
      [&](Bird &bird) {
        std::vector<Bird> neighbours =
            get_neighbours(flock_, bird, distance_, view_angle_);
        if (neighbours.size() != 0) {
          bird.velocity +=
              (separation(neighbours, bird, distance_separation_, separation_));
          bird.velocity += (alignment(neighbours, bird, alignment_));
          bird.velocity += (cohesion(neighbours, bird, cohesion_));
        }
        avoid_speeding(flock_);
        boundaries_behavior(bird, window_width_, window_height_, flock_,
                            space_);
        bird.position += bird.velocity *
                         deltaTime;  // Scala la velocità per il tempo trascorso
      }

  );
};

void Flock::draw(sf::RenderWindow &window) {
  sf::CircleShape triangle(6, 3);
  triangle.setFillColor(sf::Color::Black);
  triangle.setOrigin(sf::Vector2f{3, 3});

  std::for_each(flock_.begin(), flock_.end(), [&](Bird &bird, sf::RenderWindow window) {
    double angle = get_angle(bird.velocity, Vector2D{0, 1}) * 180 / 3.1415;
    if (bird.velocity.get_x() < 0 && bird.velocity.get_y() < 0) angle -= 180;
    if (bird.velocity.get_x() < 0 && bird.velocity.get_y() > 0) angle = -90 - angle;
    if (bird.velocity.get_x() > 0 && bird.velocity.get_y() < 0) angle = 180 - angle;

    triangle.setRotation(angle);
    triangle.setPosition(sf::Vector2f(bird.position.get_x(), bird.position.get_y()));
    window.draw(triangle);
  });
};