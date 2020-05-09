#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <interpolate/linear_lookup.h>

using namespace interp;

TEST_CASE("Simply linear lookup tests", "[linear_lookup]")
{
	LinearLookup straight_line;
	straight_line.addDataPoint(0., 0.);
	straight_line.addDataPoint(1., 1.);
	straight_line.addDataPoint(2., 2.);

	SECTION("Querying a point precisely returns the exact value in the table")
	{
		REQUIRE(straight_line(0.) == Approx(0.));
		REQUIRE(straight_line(1.) == Approx(1.));
		REQUIRE(straight_line(2.) == Approx(2.));
	}

	SECTION("Check that the interpolation is linear")
	{
		REQUIRE(straight_line(.25) == Approx(.25));
		REQUIRE(straight_line(.5) == Approx(.5));
		REQUIRE(straight_line(.75) == Approx(.75));
		REQUIRE(straight_line(1.5) == Approx(1.5));
	}

	SECTION("Check that we can extrapolate smaller values")
	{
		REQUIRE(straight_line(-2.) == Approx(-2.));
		REQUIRE(straight_line(-1.) == Approx(-1.));
	}

	SECTION("Check that we can extrapolate larger values")
	{
		REQUIRE(straight_line(3.) == Approx(3.));
		REQUIRE(straight_line(8.) == Approx(8.));
	}

	SECTION("Stress the system")
	{
		double xMin = -3.;
		double xMax = 3.;
		double xStep = 0.1;

		double x = xMin;
		while (x < xMax)
		{
			REQUIRE(straight_line(x) == Approx(1.));
			x += xStep;
		}
	}

}