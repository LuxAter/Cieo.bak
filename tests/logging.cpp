#include <catch2/catch.hpp>
#include <cieo/logging.hpp>

#include <sstream>

TEST_CASE("Core Logger") {
  LTRACE("Trace msg");
  LDEBUG("Debug msg");
  LINFO("Info msg");
  LWARN("Warning msg");
  LERROR("Error msg");
  LCRITICAL("Critical msg");
}

TEST_CASE("Client Logger") {
  cieo::logger::initialize_client_logger("stdout-test");
  LCTRACE("stdout-test", "Trace msg");
  LCDEBUG("stdout-test", "Debug msg");
  LCINFO("stdout-test", "Info msg");
  LCWARN("stdout-test", "Warning msg");
  LCERROR("stdout-test", "Error msg");
  LCCRITICAL("stdout-test", "Critical msg");
}
