#include "Boids.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include "rules.hpp"
#include "vector2D.hpp"

//#include <cassert>
//#include <cmath>
//#include <fstream>
//#include <iostream>
//#include <random>

Flock::Flock(Parameters &parameters)
    : number_{parameters.number},
      distance_{parameters.distance},
      separation_{parameters.separation},
      InfluenceRange_{parameters.InfluenceRange},
      alignment_{parameters.alignment},
      cohesion_{parameters.cohesion},
      view_angle_{parameters.view_angle},
      distance_separation_{parameters.distance_separation},
      window_width_{parameters.window_width},
      window_height_{parameters.window_height},
      max_speed_{parameters.max_speed},
      space_{parameters.space} {};

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
  std::uniform_real_distribution<float> pos_x(0, window_width_);
  std::uniform_real_distribution<float> pos_y(0, window_height_);
  std::uniform_real_distribution<float> speed(-15, 15);

  /*std::generate(flock_.begin(), flock_.end(), [&]() -> Bird {
    return {Vector2D{pos_x(gen), pos_y(gen)}, Vector2D{speed(gen), speed(gen)}};
  });*/
  flock_.reserve(number_);
  std::generate_n(back_inserter(flock_), number_, [&]() {
    return Bird{Vector2D{pos_x(gen), pos_y(gen)},
                Vector2D{speed(gen), speed(gen)}};
  });
  // return flock_;
}

void Flock::evolve(float deltaTime) {
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
        avoid_speeding(bird /*, max_speed_*/);
        boundaries_behavior(bird, window_width_, window_height_, space_);
        bird.position +=
            (bird.velocity *
             deltaTime);  // Scala la velocità per il tempo trascorso
      }

  );
};

void Flock::draw(sf::RenderWindow &window) {
  sf::CircleShape triangle(3, 3);

  triangle.setFillColor(sf::Color::Black);
  triangle.setOrigin(sf::Vector2f{3, 3});
  std::for_each(flock_.begin(), flock_.end(), [&](Bird &bird) {
    double angle = get_angle(bird.velocity, Vector2D{0, 1}) * 180 / 3.1415;
    if (bird.velocity.get_x() < 0 && bird.velocity.get_y() < 0) angle -= 180;
    if (bird.velocity.get_x() < 0 && bird.velocity.get_y() > 0)
      angle = -90 - angle;
    if (bird.velocity.get_x() > 0 && bird.velocity.get_y() < 0)
      angle = 180 - angle;

    triangle.setRotation(angle);
    triangle.setPosition(
        sf::Vector2f(bird.position.get_x(), bird.position.get_y()));
    window.draw(triangle);
  });
};