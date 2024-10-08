#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP
#include <cmath>
#include <vector>

struct Vector2D { //struct

  float x;
  float y;

 //public:
 // Vector2D(float x, float y);
  float magnitude() const;
 // float get_x() const;
 // float get_y() const;
 // void set_x(float new_x);
 // void set_y(float new_y);
};

// overload degli operatori
bool operator==(Vector2D const& v1, Vector2D const& v2);
bool operator!=(Vector2D const& v1, Vector2D const& v2);
Vector2D operator+(Vector2D const& v1, Vector2D const& v2);
void operator+=(Vector2D& v1, Vector2D const& v2);
Vector2D operator-(Vector2D const& v1, Vector2D const& v2);
void operator-=(Vector2D& v1, Vector2D const& v2);
float operator*(Vector2D const& v1, Vector2D const& v2);
Vector2D operator*(Vector2D& v1, float scalar);
void operator*=(Vector2D& v1, float scalar);
Vector2D operator/(Vector2D const& v1, float scalar);
void operator/=(Vector2D& v1, float scalar);
float get_angle(Vector2D const& v1, Vector2D const& v2);

#endif