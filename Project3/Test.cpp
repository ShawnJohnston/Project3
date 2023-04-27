#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <catch2/catch_session.hpp>

#include "Menu.h"

TEST_CASE("Hash Table") {

}


int main(int argc, char* argv[]) {
	// your setup ...

	int result = Catch::Session().run(argc, argv);

	// your clean-up...

	return result;
}