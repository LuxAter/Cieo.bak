#include <cieo/logging.hpp>
#include <cieo/units.hpp>

int main() {
  cieo::logger::register_sink<cieo::logger::StdoutColorSink>();
  cieo::logger::register_sink<cieo::logger::DailyFileSink>("logs/simple", 2, 0);
  cieo::logger::initialize_core_logger();

  return 0;
}
