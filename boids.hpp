#ifndef BOIDS_HPP
#define BOIDS_HPP
#include <SFML/Graphics.hpp>
#include <random>

//#include "game.hpp"
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

struct Settings { //quasi quasi posso eliminarla
  double window_width;
  double window_height;
  double max_speed{150.};
  double min_speed{30.};
};

struct Statistic {
  double mean_speed;
  double std_dev_speed;
  double mean_distance;
  double std_dev_distance;
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
  // double InfluenceRange_;
  double alignment_;
  double cohesion_;
  double view_angle_;
  double distance_separation_;
  double window_width_;
  double window_height_;
  // double max_speed_;
  Space space_;
  // Game window_;
  // Bird bird_;
 public:
  Flock(Parameters &parameters);
  void start(Settings settings);
  // std::vector<Bird> get_flock() const {};
  void evolve(float deltaTime, Settings settings);
  void draw(sf::RenderWindow &window);
  std::string get_statistics();  // VAI QUI E FINISCI
};

#endif