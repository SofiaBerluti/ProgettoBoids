#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP
#include <cmath>
#include <vector>

class Vector2D {
 private:
  float x_;
  float y_;

 public:
  Vector2D(auto x, auto y) : x_{x}, y_{y} {};
  float magnitude() const;
  float get_x() const {};
  float get_y() const {};
  void set_x(float new_x){};
  void set_y(float new_y){};
};
// overload degli operatori
bool operator==(Vector2D const& v1, Vector2D const& v2){};
bool operator!=(Vector2D const& v1, Vector2D const& v2){};
Vector2D operator+(Vector2D const& v1, Vector2D const& v2){};
void operator+=(Vector2D& v1, Vector2D const& v2){};
Vector2D operator-(Vector2D const& v1, Vector2D const& v2){};
void operator-=(Vector2D& v1, Vector2D const& v2){};
auto operator*(Vector2D const& v1, Vector2D const& v2){};
Vector2D operator*(Vector2D& v1, float scalar){};
void operator*=(Vector2D& v1, float scalar){};
Vector2D operator/(Vector2D const& v1, float scalar){};
void operator/=(Vector2D& v1, float scalar){};
float get_angle(Vector2D const& v1, Vector2D const& v2){};

#endif