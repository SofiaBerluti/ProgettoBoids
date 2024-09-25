#ifndef BOIDS_HPP
#define BOIDS_HPP
#include <SFML/Graphics.hpp>
#include <random>;

#include "vector2D.hpp"
#include "game.hpp"

enum Space { toroidal, rectangular };

struct Bird {
  Vector2D position{0, 0};
  Vector2D velocity{0, 0};
  /*void update(float deltaTime, std::vector<Bird> flock, Bird &bird,
            double distance_, double view_angle_, double distance_separation_,
            double separation_, double alignment_, double cohesion_) {}; POSSIAMO TOGLIERLO*/
};

class Flock {
 private:
  std::vector<Bird> flock_;
  double distance_;
  double separation_;
  double InfluenceRange_;
  double alignment_;
  double cohesion_; 
  double view_angle_;
  double distance_separation_;
  double window_width_;
  double window_height_;
  Space space_;
  //Game window_;
  //Bird bird_;
 public:
  Flock(auto distance, auto separation, auto InfluenceRange,
      double alignment, double cohesion, double view_angle,
      double distance_separation, double window_width, double window_height) {};
  void start(){};
  //std::vector<Bird> get_flock() const {};
  void evolve(){}; 
  void draw(sf::RenderWindow &window){};
  void get_statistics() {}; //VAI QUI E FINISCI
};


#endif