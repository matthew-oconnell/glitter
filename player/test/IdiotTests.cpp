#include <catch.hpp>
#include <Idiot.h>

using namespace Glitter;
using namespace Player;

TEST_CASE("Idiot does stupid things"){
    Idiot idiot;
    auto a = idiot.acceleration(); // we don't care what he does.  He's a moron.
    float m = idiot.mass();
    REQUIRE(m == 10.0);
}