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

//#include <cassert>
//#include <cmath>
//#include <fstream>
//#include <iostream>
//#include <random>

Flock::Flock(Parameters &parameters)
    : number_{parameters.number},
      distance_{parameters.distance},
      separation_{parameters.separation},
      alignment_{parameters.alignment},
      cohesion_{parameters.cohesion},
      view_angle_{parameters.view_angle},
      distance_separation_{parameters.distance_separation},
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
void Flock::start(Settings settings) {
  std::random_device rd;  // set seed
  std::default_random_engine gen(rd());
  std::uniform_real_distribution<float> pos_x(0, settings.window_width);
  std::uniform_real_distribution<float> pos_y(0, settings.window_height);
  std::uniform_real_distribution<float> vel_x(-100, 100);
  std::uniform_real_distribution<float> vel_y(-100, 100);

  /*std::generate(flock_.begin(), flock_.end(), [&]() -> Bird {
    return {Vector2D{pos_x(gen), pos_y(gen)}, Vector2D{speed(gen), speed(gen)}};
  });*/
  flock_.reserve(number_);  // SERVE DAVVERO?
  std::generate_n(back_inserter(flock_), number_, [&]() {
    return Bird{Vector2D{pos_x(gen), pos_y(gen)},
                Vector2D{vel_x(gen), vel_y(gen)}};
  });
  // return flock_;
}

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
                  bird.position +=
                      (bird.velocity *
                       deltaTime);  // Scala la velocità per il tempo trascorso
                }

  );
};

void Flock::draw(sf::RenderWindow &window) {
  sf::CircleShape triangle(6, 3);

  triangle.setFillColor(sf::Color::Black);
  triangle.setOrigin(sf::Vector2f{3, 3});
  std::for_each(flock_.begin(), flock_.end(), [&](Bird &bird) {
    double angle = get_angle(bird.velocity, Vector2D{0, 1}) * 180 / 3.1415;
    if (bird.velocity.x < 0 && bird.velocity.y < 0) angle -= 180;
    if (bird.velocity.x < 0 && bird.velocity.y > 0) angle = -90 - angle;
    if (bird.velocity.x > 0 && bird.velocity.y < 0) angle = 180 - angle;

    triangle.setRotation(angle);
    triangle.setPosition(sf::Vector2f(bird.position.x, bird.position.y));
    window.draw(triangle);
  });
};

std::string Flock::get_statistics() {
  double sum_speed = std::accumulate(
      flock_.begin(), flock_.end(), 0.,
      [&](double sum, Bird &bird) { return sum + bird.velocity.magnitude(); });
  double sum_speed2 = std::accumulate(
      flock_.begin(), flock_.end(), 0., [&](double sum, Bird &bird) {
        return sum + std::pow(bird.velocity.magnitude(), 2);
      });

  double mean_speed = sum_speed / flock_.size();
  double std_dev_speed =
      std::sqrt(sum_speed2 * flock_.size() - pow(sum_speed, 2)) / flock_.size();

  /*double mean_distance =
      std::accumulate(flock_.begin(), flock_.end(), 0., [&](double distance2,
     Bird& bird) { auto it = flock_.begin(); auto it_2 = std::next(it); double
     sum1 = std::accumulate(it_2, flock_.end(), 0., [&](double distance1) {
              return distance1 + (bird.position - it_2->position).magnitude();
            });
        return distance2 + sum1;
      });*/
  /* double total_distance = 0;
   for (size_t i = 0; i < flock_.size(); ++i) {
         // Usare un altro ciclo per iterare solo sugli uccelli successivi
         total_distance += std::accumulate(flock_.begin() + i + 1, flock_.end(),
   0.0,
             [&](double sum, const Bird& bird2) {
                 return sum + (flock_[i].position - bird2.position).magnitude();
             });}

*/
  /* for (size_t i = 0; i < flock_.size(); ++i) {
           total_distance += std::accumulate(flock_.begin() + i + 1,
    flock_.end(), 0.0,
               [&](double sum, const Bird& bird2) {
                   return sum + flock_[i].distanceTo(bird2);
               });
       }

       size_t num_pairs = (flock_.size() * (flock_.size() - 1)) / 2;
       return total_distance / num_pairs;
    }*/
  double mean_distance = 0;
  std::for_each(flock_.begin(), flock_.end(), [&](Bird &bird) {
    auto it = flock_.begin();
    auto it_2 = std::next(it);
    mean_distance += std::accumulate(
        it_2, flock_.end(), 0., [&](double sum_dist, Bird &bird2) {
          double distance = (bird2.position - bird.position).magnitude();
          return sum_dist + distance;
        });
    return mean_distance;
  });
  mean_distance /= (flock_.size() * (flock_.size() - 1) /
                    2);  // divido per il numero di coppie
  double std_dev_distance = 0;
  std::for_each(flock_.begin(), flock_.end(), [&](Bird &bird) {
    auto it = flock_.begin();
    auto it_2 = std::next(it);
    std_dev_distance += std::accumulate(
        it_2, flock_.end(), 0., [&](double sum_dist, Bird &bird2) {
          double distance = std::pow(
              (bird2.position - bird.position).magnitude() - mean_distance, 2);
          return sum_dist + distance;
        });
    return std_dev_distance;
  });
  std_dev_distance =
      std::sqrt(std_dev_distance / (flock_.size() * (flock_.size() - 1) / 2));

  std::ofstream file;
  file.open("data.csv", std::ios::app);
  file << mean_distance << " , " << std_dev_distance << " , " << mean_speed
       << " , " << std_dev_speed << "\n";
  file.close();

  // return Statistic{mean_distance, std_dev_distance, mean_speed,
  // std_dev_speed};
  return "Mean distance and standard deviation: " +
         std::to_string(mean_distance) + " +/- " +
         std::to_string(std_dev_distance) + '\n' +
         "Mean speed and standard deviation: " + std::to_string(mean_speed) +
         " +/- " + std::to_string(std_dev_speed) + '\n';
}