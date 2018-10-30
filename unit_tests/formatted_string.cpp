#include "catch2.hpp"
#include "formatted_string.h"
#include <cstring>

TEST_CASE( "size", "[formatted_string]" ) {
	auto fs = make_formatted_string("%d", 3);
    REQUIRE( std::strcmp(fs.c_str(),"3") == 0);
}

TEST_CASE( "copy", "[formatted_string]" ) {
	char const* s = "Hello, world!\n";
	auto fs = make_formatted_string("%s", s);
    REQUIRE( std::strcmp(fs.c_str(),s) == 0);
}

TEST_CASE( "move assign", "[formatted_string]" ) {
	char const* s = "Hello, world!\n";
	auto fs = make_formatted_string("%s", s);
	auto fs2 = make_formatted_string("%d", 3);
	fs2 = std::move(fs);
    REQUIRE( std::strcmp(fs2.c_str(),s) == 0);
}

TEST_CASE( "move construct", "[formatted_string]" ) {
	char const* s = "Hello, world!\n";
	auto fs = make_formatted_string("%s", s);
	auto fs2{std::move(fs)};
    REQUIRE( std::strcmp(fs2.c_str(),s) == 0);
}
