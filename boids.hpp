#ifndef BOIDS_HPP
#define BOIDS_HPP
#include <SFML/Graphics.hpp>
#include <random>

#include "vector2D.hpp"

enum Space { toroidal, rectangular };

struct Parameters {
  int number;
  double separation;
  double alignment;
  double cohesion;
  double distance;
  double distance_separation;
  double view_angle;
  Space space;
};

struct Settings {
  double window_width;
  double window_height;
  double max_speed;
  double min_speed;
};

struct Bird {
  Vector2D position{0, 0};
  Vector2D velocity{0, 0};
};

class Flock {
 private:
  std::vector<Bird> flock_;
  int number_;
  double distance_;
  double separation_;
  double alignment_;
  double cohesion_;
  double view_angle_;
  double distance_separation_;
  double window_width_;
  double window_height_;
  Space space_;

 public:
  Flock(Parameters &parameters);
  void start(Settings settings);
  void evolve(float deltaTime, Settings settings);
  void draw(sf::RenderWindow &window);
  std::string get_statistics();
};

/*struct Statistic {
  double mean_speed;
  double std_dev_speed;
  double mean_distance;
  double std_dev_distance;
};*/

#endif