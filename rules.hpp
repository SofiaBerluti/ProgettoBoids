#ifndef RULES_HPP
#define RULES_HPP

#include <algorithm>
#include <numeric>
#include <vector>

#include "Boids.hpp"
#include "vector2D.hpp"

// Boid Position
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
};

inline Vector2D separation(std::vector<Bird>& neighbours, Bird& bird,
                           double distance_separation, double separation) {
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
  Vector2D sum_neighbours_velocity = std::accumulate(
      neighbours.begin(), neighbours.end(), Vector2D{0, 0},
      [&](Vector2D sum, Bird& neighbour) { return sum + neighbour.velocity; });
  sum_neighbours_velocity /= (neighbours.size() - 1);
  sum_neighbours_velocity -= bird.velocity;
  return sum_neighbours_velocity * alignment;
};

inline Vector2D cohesion(std::vector<Bird>& neighbours, Bird& bird,
                         double cohesion) {
  Vector2D sum_neighbours_position = std::accumulate(
      neighbours.begin(), neighbours.end(), Vector2D{0, 0},
      [&](Vector2D sum, Bird& neighbour) { return sum + neighbour.position; });
  Vector2D mass_center = sum_neighbours_position / (neighbours.size() - 1);
  mass_center -= bird.position;
  return mass_center * cohesion;
}

inline void boundaries_behavior(Bird& bird, double window_width,
                                double window_height, std::vector<Bird> birds, Space space) {
  std::transform(birds.begin(), birds.end(), birds.begin(),
                 [&](Bird& bird, double window_width, double window_height) {
                   if (space == toroidal) {
                     if (bird.position.get_x() < 0) {
                       bird.position.set_x(window_width);
                     } else if (bird.position.get_x() > window_width) {
                       bird.position.set_x(0);
                     }
                     if (bird.position.get_y() < 0) {
                       bird.position.set_y(window_height);
                     } else if (bird.position.get_y() > window_height) {
                       bird.position.set_y(0);
                     }
                   } else if (space == rectangular) {
                     if (bird.position.get_x() == 0) {
                       bird.velocity.set_x(-bird.velocity.get_x());
                     } else if (bird.position.get_x() == window_width) {
                       bird.velocity.set_x(-bird.velocity.get_x());
                     }
                     if (bird.position.get_y() == 0) {
                       bird.velocity.set_y(-bird.velocity.get_y());
                     } else if (bird.position.get_y() == window_height) {
                       bird.velocity.set_y(-bird.velocity.get_y());
                     }
                   }
                 });
};

/*inline Vector2D avoid_speeding(Bird &bird, double max_speed = 6) {
    auto speed = bird.velocity.magnitude();
    if (speed > max_speed) {

    }
}*/
inline Vector2D avoid_speeding(std::vector<Bird>& birds) {
  std::transform(birds.begin(), birds.end(), birds.begin(),
                 [&](Bird& bird, double max_speed) {
                   auto speed = bird.velocity.magnitude();
                   if (speed > max_speed) {
                     bird.velocity /= speed;
                     return bird.velocity *= max_speed;
                   };
                 });
}

#endif