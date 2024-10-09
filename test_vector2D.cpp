#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector2D.hpp"

TEST_CASE("Testing Vector2D") {
  SUBCASE("testing +") {
    Vector2D v1{1., 2.};
    Vector2D v2{2., 3.};
    Vector2D v3{4., 3.};
    Vector2D res1{3., 5.};
    Vector2D res2{6., 6.};
    CHECK(v1 + v2 == res1);
    CHECK(v2 + v3 == res2);
  }
  SUBCASE("testing +=") {
    Vector2D v1{1., 2.};
    Vector2D v2{2., 3.};
    Vector2D v3{4., 3.};
    Vector2D res1{3., 5.};
    Vector2D res2{6., 6.};
    v1 += v2;
    v2 += v3;
    CHECK(v1 == res1);
    CHECK(v2 == res2);
  }
  SUBCASE("testing -") {
    Vector2D v1{1., 2.};
    Vector2D v2{2., 3.};
    Vector2D v3{4., 3.};
    Vector2D res1{-1., -1.};
    Vector2D res2{-2., 0.};
    CHECK(v1 - v2 == res1);
    CHECK(v2 - v3 == res2);
  }
  SUBCASE("testing *") {
    Vector2D v1{1., 2.};
    Vector2D v2{2., 3.};
    Vector2D res1{2., 4.};
    CHECK(v1 * 2. == res1);
    CHECK(v2 * 1. == v2);
  }
  SUBCASE("testing *") {
    Vector2D v1{1., 2.};
    Vector2D v2{2., 3.};
    Vector2D v3{4., 3.};
    CHECK(v1 * v2 == 8.);
    CHECK(v2 * v3 == 17.);
    CHECK(v1 * v3 == 10.);
  }
  SUBCASE("testing /") {
    Vector2D v1{1., 2.};
    Vector2D v2{2., 3.};
    Vector2D v3{4., 3.};
    Vector2D res1{1., 1.5};
    Vector2D res2{-4., -3.};
    CHECK(v1 / 1. == v1);
    CHECK(v2 / 2. == res1);
    CHECK(v3 / -1. == res2);
    CHECK_THROWS_WITH_AS(v1 / 0., "Can't divide by zero", std::runtime_error);
  }
  SUBCASE("testing /=") {
    Vector2D v1{1., 2.};
    Vector2D v2{2., 3.};
    Vector2D v3{4., 3.};
    Vector2D res1{1., 1.5};
    Vector2D res2{-4., -3.};
    v2 /= 2.;
    v3 /= -1.;
    CHECK(v2 == res1);
    CHECK(v3 == res2);
    CHECK_THROWS_WITH_AS(v1 / 0., "Can't divide by zero", std::runtime_error);
  }

  SUBCASE("testing magnitude") {
    Vector2D v1{1., 2.};
    Vector2D v2{2., 3.};
    Vector2D v3{4., 0.};
    CHECK(doctest::Approx(v2.magnitude()).epsilon(0.01) == sqrt(13.));
    CHECK(v3.magnitude() == 4.);
    CHECK(doctest::Approx(v1.magnitude()).epsilon(0.01) == sqrt(5.));
  }

  SUBCASE("Testing get angle") {
    Vector2D a{1, 1};
    Vector2D b{1, 0};
    Vector2D c{4, 10};
    Vector2D d{0, 0};
    Vector2D e{-1, 1};
    CHECK(doctest::Approx(get_angle(a, b)) == 0.785398);
    CHECK(doctest::Approx(get_angle(b, b)) == 0);
    CHECK(doctest::Approx(doctest::Approx(get_angle(b, Vector2D{-1, 0})))
              .epsilon(0.001) == 3.1415);
    CHECK(doctest::Approx(get_angle(a, c)) == 0.40489);
    CHECK(doctest::Approx(get_angle(a, d)) == 0);
    CHECK(get_angle(a, e) == doctest::Approx(3.1415 / 2).epsilon(0.01));
  }
}