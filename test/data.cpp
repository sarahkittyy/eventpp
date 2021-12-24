#include <catch2/catch.hpp>

#include <cmath>
#include <eventpp.hpp>

TEST_CASE("data class", "[data]") {
	using namespace epp;

	data d;

	SECTION("can be constructed with an initializer list") {
		d = data({ { "x", 5.2 }, { "y", 3 } });
		REQUIRE(d.get<double>("x") == 5.2);
		REQUIRE(d.get<int>("y") == 3);
	}

	SECTION("can set and get values properly") {
		d.set("x", 5).set("y", 2.8);
		REQUIRE(d.get<int>("x") == 5);
		REQUIRE(d.get<double>("y") == 2.8);
		REQUIRE(d.has("x"));
		REQUIRE_THROWS(d.get<double>("x") == 5.0);
	}

	SECTION("can be cleared") {
		d.set("x", 3.28f);
		REQUIRE(d.get<float>("x") == 3.28f);
		d.clear();
		REQUIRE_THROWS(d.get<float>("x") == 3.28f);
		REQUIRE(!d.has("x"));
	}
}
