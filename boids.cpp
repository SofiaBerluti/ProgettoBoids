#include "boids.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>

#include "rules.hpp"
#include "vector2D.hpp"

Flock::Flock(Parameters &parameters)
    : number_{parameters.number},
      distance_{parameters.distance},
      separation_{parameters.separation},
      alignment_{parameters.alignment},
      cohesion_{parameters.cohesion},
      view_angle_{parameters.view_angle},
      distance_separation_{parameters.distance_separation},
      space_{parameters.space} {};

// generazione random dei Bird
void Flock::start(Settings settings) {
  std::random_device rd;  // set seed
  std::default_random_engine gen(rd());
  std::uniform_real_distribution<float> pos_x(0, settings.window_width);
  std::uniform_real_distribution<float> pos_y(0, settings.window_height);
  std::uniform_real_distribution<float> vel_x(-settings.max_speed,
                                              settings.max_speed);
  std::uniform_real_distribution<float> vel_y(-settings.max_speed,
                                              settings.max_speed);

  flock_.reserve(number_);
  std::generate_n(back_inserter(flock_), number_, [&]() {
    return Bird{Vector2D{pos_x(gen), pos_y(gen)},
                Vector2D{vel_x(gen), vel_y(gen)}};
  });
}

// evoluzione di flock secondo le regole di volo
void Flock::evolve(float deltaTime, Settings settings) {
  std::for_each(flock_.begin(), flock_.end(),
                [&](Bird &bird) {
                  std::vector<Bird> neighbours =
                      get_neighbours(flock_, bird, distance_, view_angle_);
                  if (neighbours.size() != 0) {
                    bird.velocity += (separation(
                        neighbours, bird, distance_separation_, separation_));
                    bird.velocity += (alignment(neighbours, bird, alignment_));
                    bird.velocity += (cohesion(neighbours, bird, cohesion_));
                  }
                  avoid_speeding(bird, settings);
                  boundaries_behavior(bird, settings.window_width,
                                      settings.window_height, space_);
                  bird.position += (bird.velocity * deltaTime);
                }

  );
};

//rappresentazione grafica dei Bird
void Flock::draw(sf::RenderWindow &window) {
  sf::CircleShape triangle(6, 3);
  triangle.setFillColor(sf::Color::Black);
  triangle.setOrigin(sf::Vector2f{3, 3});
  std::for_each(flock_.begin(), flock_.end(), [&](Bird &bird) {
    double angle = get_angle(bird.velocity, Vector2D{0, 1}) * 180 / 3.1415;
    if (bird.velocity.x < 0 && bird.velocity.y < 0) angle -= 180;
    if (bird.velocity.x < 0 && bird.velocity.y > 0) angle -= 180;
    if (bird.velocity.x > 0 && bird.velocity.y < 0) angle += 180;
    if (bird.velocity.x > 0 && bird.velocity.y > 0) angle += 180;
    triangle.setRotation(angle);
    triangle.setPosition(sf::Vector2f(bird.position.x, bird.position.y));
    window.draw(triangle);
  });
};

// calcolo distanza e velocità media
std::string Flock::get_statistics() {
  double sum_speed = std::accumulate(
      flock_.begin(), flock_.end(), 0.,
      [&](double sum, Bird &bird) { return sum + bird.velocity.magnitude(); });
  double sum_speed2 = std::accumulate(
      flock_.begin(), flock_.end(), 0., [&](double sum, Bird &bird) {
        return sum + std::pow(bird.velocity.magnitude(), 2);
      });

  double mean_speed = sum_speed / number_;
  double std_dev_speed = std::sqrt(sum_speed2 / number_ - pow(mean_speed, 2));

  double sum_distance = 0;
  double sum_distance2 = 0;
  std::for_each(flock_.begin(), flock_.end(), [&](Bird &bird) {
    std::vector<double> distances;
    std::for_each(flock_.begin(), flock_.end(), [&](Bird &other) {
      if (&bird != &other) {
        double distance = (other.position - bird.position).magnitude();
        distances.push_back(distance);
      }
    });
    auto min_iter = std::min_element(distances.begin(), distances.end());
    double min_distance = *min_iter;
    sum_distance += min_distance;
    sum_distance2 += std::pow(min_distance, 2);
  });

  double mean_distance = sum_distance / number_;
  double std_dev_distance =
      std::sqrt(sum_distance2 / number_ - pow(mean_distance, 2));

  std::ofstream file;
  file.open("data.csv", std::ios::app);
  file << mean_distance << " , " << std_dev_distance << " , " << mean_speed
       << " , " << std_dev_speed << "\n";
  file.close();

  return "Mean distance and standard deviation: " +
         std::to_string(mean_distance) + " +/- " +
         std::to_string(std_dev_distance) + '\n' +
         "Mean speed and standard deviation: " + std::to_string(mean_speed) +
         " +/- " + std::to_string(std_dev_speed) + '\n';
}