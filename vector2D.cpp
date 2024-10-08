#include "vector2D.hpp"

//#include <vector>
#include <cmath>
#include <iostream>

//Vector2D::Vector2D(float x, float y) : x_{x}, y_{y} {};
float Vector2D::magnitude() const { return std::sqrt(x * x + y * y); }
/*float Vector2D::x const { return x_; };
float Vector2D::y const { return y_; };
void Vector2D::set_x(float new_x) { x_ = new_x; };
void Vector2D::set_y(float new_y) { y_ = new_y; };*/

bool operator==(Vector2D const& v1, Vector2D const& v2) {
  return v1.x == v2.x && v1.y == v2.y;
}
bool operator!=(Vector2D const& v1, Vector2D const& v2) { return !(v1 == v2); }
Vector2D operator+(Vector2D const& v1, Vector2D const& v2) {
  return Vector2D{v1.x + v2.x, v1.y + v2.y};
}
void operator+=(Vector2D& v1, Vector2D const& v2) {
  v1.x = v1.x + v2.x;
  v1.y = v1.y + v2.y;
}
Vector2D operator-(Vector2D const& v1, Vector2D const& v2) {
  return Vector2D{v1.x - v2.x, v1.y - v2.y};
}
void operator-=(Vector2D& v1, Vector2D const& v2) {
  v1.x = v1.x - v2.x;
  v1.y = v1.y - v2.y;
}
float operator*(Vector2D const& v1, Vector2D const& v2) {
  return v1.x * v2.x + v1.y * v2.y;
}
Vector2D operator*(Vector2D& v1, float scalar) {
  return Vector2D{v1.x * scalar, v1.y * scalar};
}
void operator*=(Vector2D& v1, float scalar) {
  v1.x = v1.x * scalar;
  v1.y = v1.y * scalar;
}
Vector2D operator/(Vector2D const& v1, float scalar) {
  if (scalar == 0) throw std::runtime_error{"Can't divide by zero"};

  return Vector2D{v1.x / scalar, v1.y / scalar};
}
void operator/=(Vector2D& v1, float scalar) {
  if (scalar == 0) throw std::runtime_error{"Can't divide by zero"};

  v1.x = v1.x / scalar;
  v1.y = v1.y / scalar;
}

float get_angle(Vector2D const& v1, Vector2D const& v2) {
  if (v1.magnitude() == 0 || v2.magnitude() == 0) return 0;

  return std::acos((v1 * v2) /
                   (v1.magnitude() * v2.magnitude()));  // in radianti
}  // qua non gli andava bene, avevo dimenticato return a riga 57