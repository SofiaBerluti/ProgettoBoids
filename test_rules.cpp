#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "boids.hpp"
#include "doctest.h"
#include "rules.hpp"

TEST_CASE("Testing rules") {
  Bird b1{{10, 14}, {0, 0}};
  Bird b2{{23, 20}, {5, -4}};
  Bird b3{{0, 0}, {3, -2}};
  Bird b4{{300, 300}, {2, 2}};
  Bird b5{{20, 0}, {0, 0}};

  SUBCASE("Testing get_neighbors") {
    std::vector<Bird> flock_;
    flock_.push_back(b1);
    flock_.push_back(b2);
    flock_.push_back(b3);
    flock_.push_back(b4);
    flock_.push_back(b5);
    auto v = get_neighbours(flock_, b1, 150, 3);
    std::vector<Bird> flock_2;
    flock_2.push_back(b1);
    flock_2.push_back(b4);
    auto v2 = get_neighbours(flock_2, b4, 150, 2.8);
    std::vector<Bird> flock_3;
    flock_3.push_back(b5);
    auto v3 = get_neighbours(flock_3, b3, 150, 3.14);
    CHECK(v.size() == 3);
    CHECK(v2.size() == 0);
    CHECK(v3.size() == 1);
  }

  SUBCASE("Testing separation") {
    std::vector<Bird> flock_;
    flock_.push_back(b2);
    flock_.push_back(b3);
    flock_.push_back(b5);
    Vector2D v2 = separation(flock_, b1, 30, 0.3);
    Vector2D v_s2{-3.9, 6.6};
    CHECK(v2.x == doctest::Approx(v_s2.x));
    CHECK(v2.y == doctest::Approx(v_s2.y));
  }

  SUBCASE("Testing alignement") {
    std::vector<Bird> flock_;
    flock_.push_back(b2);
    flock_.push_back(b3);
    flock_.push_back(b5);
    Vector2D v2 = alignment(flock_, b1, 0.1);
    Vector2D v_a2{0.26667, -0.2};
    CHECK(v2.x == doctest::Approx(v_a2.x));
    CHECK(v2.y == doctest::Approx(v_a2.y));
  }
  SUBCASE("Testing cohesion") {
    std::vector<Bird> flock_;
    flock_.push_back(b2);
    flock_.push_back(b3);
    flock_.push_back(b5);
    Vector2D v2 = cohesion(flock_, b1, 0.005);
    Vector2D v_c2{0.0216667, -0.036667};
    CHECK(v2.x == doctest::Approx(v_c2.x));
    CHECK(v2.y == doctest::Approx(v_c2.y));
  }
  SUBCASE("Avoid speeding") {
    Bird b6{{300, 300}, {0, 0}};
    Bird b7{{300, 300}, {30, 30}};
    Bird b8{{300, 300}, {1, 1}};
    Settings settings;
    settings.max_speed = 20;
    settings.min_speed = 5;
    avoid_speeding(b6, settings);
    avoid_speeding(b7, settings);
    avoid_speeding(b8, settings);
    CHECK(b6.velocity.magnitude() == 10);
    CHECK(b7.velocity.magnitude() == 20);
    CHECK(b8.velocity.magnitude() == 5);
  }
};

TEST_CASE("Boundaries behavior") {
  SUBCASE("Toroidal space") {
    Bird b1{{-20, 500}, {0, 0}};
    Bird b2{{1001, 500}, {5, 0}};
    Bird b3{{500, -20}, {5, 0}};
    Bird b4{{500, 1000}, {5, 0}};
    boundaries_behavior(b1, 1000, 1000, toroidal);
    CHECK(b1.position.x == 1000);
    boundaries_behavior(b2, 1000, 1000, toroidal);
    CHECK(b2.position.x == 0);
    boundaries_behavior(b3, 1000, 1000, toroidal);
    CHECK(b3.position.y == 1000);
    boundaries_behavior(b4, 1000, 1000, toroidal);
    CHECK(b4.position.y == 0);
  }

  SUBCASE("Rectangular Space") {
    Bird b5{{300, 990}, {0, 3}};
    Bird b6{{-300, -50}, {0, -3}};
    Bird b7{{-20, 500}, {0, 0}};
    Bird b8{{1080, 500}, {5, 0}};
    boundaries_behavior(b5, 1000, 1000, rectangular);
    CHECK(b5.velocity.y == 3);
    boundaries_behavior(b6, 1000, 1000, rectangular);
    CHECK(b6.velocity.y == 6);
    boundaries_behavior(b7, 1000, 1000, rectangular);
    CHECK(b7.velocity.x == 0);
    boundaries_behavior(b8, 1000, 1000, rectangular);
    CHECK(b8.velocity.x == -10);
  }
}