#include "catch.hpp"
#include "eventpp/eventpp.hpp"

enum EVENT {
	VALUE_EVENT,
};

TEST_CASE("Test Data Class", "[data]") {
	using eventpp::data;

	GIVEN("a data instance") {
		data d;

		SECTION("setting a value") {
			WHEN("a value is set") {
				d.set("val", 5);

				THEN("we can retrieve that value") {
					REQUIRE(d.get<int>("val") == 5);
				}
			}
		}

		SECTION("updating a value") {
			WHEN("changing an existing key") {
				d.set("val", 9);

				THEN("the value change is reflected") {
					REQUIRE(d.get<int>("val") == 9);
				}
			}
		}

		SECTION("chaining set calls") {
			WHEN("using .set()") {
				data& s = d.set("val", 8);

				THEN("the returned reference is the same as the original data object") {
					REQUIRE(&s == &d);
				}
			}
		}
	}
}

TEST_CASE("Test Manager", "[manager]") {
	using eventpp::manager, eventpp::data, eventpp::token;

	GIVEN("an event manager and a token") {
		manager m;
		token tok;

		SECTION("Subscribing/Unsubscribing") {
			int x;
			size_t sub_id;

			WHEN("subscribing to an event and raising it") {
				sub_id = m.subscribe(tok, VALUE_EVENT, [&x](const data& d) {
					x = d.get<int>("val");
				});

				m.raise(VALUE_EVENT, data().set("val", 5));

				THEN("the event handler is called") {
					REQUIRE(x == 5);
				}
			}

			WHEN("unsubscribing from that event and then raising it") {
				x = 3;

				m.unsubscribe(sub_id);

				m.raise(sub_id, data().set("val", 5));

				THEN("the event handler is not called") {
					REQUIRE(x == 3);
				}
			}

			WHEN("resubscribing") {
				m.subscribe(tok, VALUE_EVENT, [&x](const data& d) {
					x = d.get<int>("val");
				});

				m.raise(VALUE_EVENT, data().set("val", 5));

				THEN("the event handler is again called") {
					REQUIRE(x == 5);
				}
			}

			WHEN("the token is destructed") {
				x = 3;

				tok = token();

				m.raise(VALUE_EVENT, data().set("val", 5));

				THEN("the event handler is not called") {
					REQUIRE(x == 3);
				}
			}
		}
	}
}
