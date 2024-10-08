#ifndef RULES_HPP
#define RULES_HPP

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>

#include "boids.hpp"
#include "vector2D.hpp"
// aggiungere opzione if neighbours.size()=0
//  Boid Position
inline std::vector<Bird> get_neighbours(std::vector<Bird> const& birds,
                                        Bird const& bird, double distance,
                                        double view_angle) {
  std::vector<Bird> neighbours;
  std::for_each(birds.begin(), birds.end(), [&](Bird const& other) {
    const double distance_birds = (bird.position - other.position).magnitude();

    if (distance_birds < distance && distance_birds != 0) {
      double angle = get_angle(bird.position - other.position, bird.velocity);
      if (angle < view_angle) return neighbours.push_back(other);
    }
  });
  return neighbours;
}

inline Vector2D separation(std::vector<Bird>& neighbours, Bird& bird,
                           double distance_separation, double separation) {
  if (neighbours.size() == 0) return Vector2D{0, 0};
  Vector2D sum_position = std::accumulate(
      neighbours.begin(), neighbours.end(), Vector2D{0, 0},
      [&](Vector2D& sum, Bird& neighbour) {
        bool are_close = (bird.position - neighbour.position).magnitude() <
                         distance_separation;
        return are_close ? sum + (bird.position - neighbour.position) : sum;
      });

  return sum_position * separation;
}

inline Vector2D alignment(std::vector<Bird>& neighbours, Bird& bird,
                          double alignment) {
  if (neighbours.size() == 0) return Vector2D{0, 0};
  Vector2D sum_neighbours_velocity = std::accumulate(
      neighbours.begin(), neighbours.end(), Vector2D{0, 0},
      [&](Vector2D sum, Bird& neighbour) { return sum + neighbour.velocity; });
  sum_neighbours_velocity /=
      (neighbours.size());  // qui c'era neighbours.size()-1, ma questo da dei
                            // problemi ovviamente, perchè non posso dividere
                            // per zero, per ora l'ho tolto
  sum_neighbours_velocity -= bird.velocity;
  return sum_neighbours_velocity * alignment;
}

inline Vector2D cohesion(std::vector<Bird>& neighbours, Bird& bird,
                         double cohesion) {
  if (neighbours.size() == 0) return Vector2D{0, 0};
  Vector2D sum_neighbours_position = std::accumulate(
      neighbours.begin(), neighbours.end(), Vector2D{0, 0},
      [&](Vector2D sum, Bird& neighbour) { return sum + neighbour.position; });
  Vector2D mass_center = sum_neighbours_position / (neighbours.size());
  mass_center -= bird.position;
  return mass_center * cohesion;
}

inline void boundaries_behavior(Bird& bird, double window_width,
                                double window_height, Space space) {
  // std::transform(birds.begin(), birds.end(), birds.begin(), [&](Bird& bird) {
  if (space == toroidal) {
    if (bird.position.x <= 0.) {
      bird.position.x = window_width;
    } else if (bird.position.x >= window_width) {
      bird.position.x = 0.;
    }
    if (bird.position.y <= 0.) {
      bird.position.y = window_height;
    } else if (bird.position.y >= window_height) {
      bird.position.y = 0.;
    }
  } else if (space == rectangular) {
    if (bird.position.x <= 0.) {
      bird.velocity.x = - (bird.velocity.x * 2);
    } else if (bird.position.x >= window_width) {
      bird.velocity.x = - (bird.velocity.x * 2);
    }
    if (bird.position.y <= 0.) {
      bird.velocity.y = - (bird.velocity.y * 2);
    } else if (bird.position.y >= window_height) {
      bird.velocity.y = - (bird.velocity.y * 2);
    }
  }
  // });
}

/*inline Vector2D avoid_speeding(Bird &bird, double max_speed = 6) {
    auto speed = bird.velocity.magnitude();
    if (speed > max_speed) {

    }
}*/
inline void avoid_speeding(Bird& bird, Settings settings /*, double max_speed*/) {
  // std::transform(birds.begin(), birds.end(), birds.begin(),
  //[&]() {
  if (bird.velocity == Vector2D{0, 0}) return bird.velocity += Vector2D{0, 10};
  auto speed = bird.velocity.magnitude();
  if (speed > settings.max_speed) {
    bird.velocity /= speed;
    return bird.velocity *= settings.max_speed;
  } else if (speed < settings.min_speed) {
    bird.velocity /= speed;
    bird.velocity *= settings.min_speed;
  }
}
//     });

#endif