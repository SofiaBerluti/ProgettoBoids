#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

struct Vector2D {
  float x;
  float y;

  float magnitude() const;
};

float get_angle(Vector2D const& v1, Vector2D const& v2);

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

#endif