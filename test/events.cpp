#include <catch2/catch.hpp>

#include <eventpp.hpp>

TEST_CASE("Events", "[emitter][observer]") {
	enum events {
		INC,
		DEC,
	};

	using namespace epp;

	GIVEN("An emitter and observer") {
		emitter e;
		observer o(e);
		int x = 0;

		WHEN("Subscribing to an event") {
			o.hook(INC, [&x](data d) {
				x += d.get<int>("by");
			});
			o.hook(DEC, [&x](data d) {
				x -= d.get<int>("by");
			});
			THEN("Emitting it works") {
				e.emit(INC, data({ { "by", 2 } }));
				REQUIRE(x == 2);
			}

			THEN("Unsubscribing works") {
				REQUIRE(x == 0);
				e.emit(DEC, data({ { "by", 2 } }));
				REQUIRE(x == -2);
				o.unhook(DEC);
				e.emit(DEC, data({ { "by", 2 } }));
				REQUIRE(x == -2);
			}
		}
	}
}
