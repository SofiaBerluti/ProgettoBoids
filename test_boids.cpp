#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "boids.hpp"
#include "rules.hpp"

#include "doctest.h" 
 


  TEST_CASE("Avoid boundaries, toroidal space") {
    Bird b1{{-20, 500}, {0, 0}};
    Bird b2{{1001, 500}, {5, 0}};
    Bird b3{{500, -20}, {5, 0}};
    Bird b4{{500, 1000}, {5, 0}};
    boundaries_behavior(b1, 1000, 1000, toroidal);
    CHECK(b1.position.get_x() == 1000);
    boundaries_behavior(b2, 1000, 1000, toroidal);
    CHECK(b2.position.get_x() == 0);
    boundaries_behavior(b3, 1000, 1000, toroidal);
    CHECK(b3.position.get_y() == 1000);
    boundaries_behavior(b4, 1000, 1000, toroidal);
    CHECK(b4.position.get_y() == 0);
  }