#define BOOST_TEST_MODULE mperf Test
#include <boost/test/included/unit_test.hpp>

#include <cmath>
#include <chrono>
#include <thread>

#include "../parameters.hpp"
#include "../avaliation.hpp"

BOOST_AUTO_TEST_CASE( context_test )
{
  char* argv[] = { "20", "10000" };

  struct mperf::application_context context(2, argv);

  BOOST_TEST( context.avaliations_limit == 20 );
  BOOST_TEST( context.interation_limit == 10000 );
}

BOOST_AUTO_TEST_CASE( histance_test )
{
  int step = 5;
  long iteration_limit = 10000;
  long elements_amount = std::lroundl(std::pow(2, step));

  avaliation_histance histance(step, iteration_limit);

  BOOST_TEST( histance.step() == step );
  BOOST_TEST( histance.iteration_limit() == iteration_limit );
  BOOST_TEST( histance.elements_amount() == elements_amount );
}

BOOST_AUTO_TEST_CASE( result_test )
{
  using namespace std::literals;

  int step = 5;
  long iteration_limit = 10000;
  long elements_amount = std::lroundl(std::pow(2, step));

  std::chrono::milliseconds expected_average = 2000ms;

  avaliation_result result(iteration_limit, elements_amount);

  result.start();
  std::this_thread::sleep_for(expected_average);
  result.stop();

  std::chrono::duration<double, std::milli> expected = expected_average;

  BOOST_TEST( (int) expected.count() == (int) result.average());
}
