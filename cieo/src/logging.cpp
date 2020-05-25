#include "cieo/logging.hpp"

#include <iostream>
#include <memory>
#include <pthread.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/logger.h>
#include <spdlog/spdlog.h>
#include <string>
#include <unordered_map>

#include <spdlog/sinks/base_sink.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/null_sink.h>
#include <spdlog/sinks/ostream_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/stdout_sinks.h>

#include "cieo/compiler.hpp"
#include "cieo/os.hpp"
#include "cieo/version.hpp"

static std::vector<spdlog::sink_ptr> sinks;
static std::shared_ptr<spdlog::logger> core_logger;
static std::unordered_map<std::string, std::shared_ptr<spdlog::logger>>
    client_logger;

void cieo::logger::push_sink(const spdlog::sink_ptr &sink,
                             const LogLevel &sink_level) {
  sink->set_level(static_cast<spdlog::level::level_enum>(sink_level));
  sinks.push_back(sink);
}

bool cieo::logger::initialize_core_logger() {
  try {
    core_logger =
        std::make_shared<spdlog::logger>("cieo", begin(sinks), end(sinks));
#ifdef NDEBUG
    core_logger->set_level(spdlog::level::info);
    spdlog::set_level(spdlog::level::info);
#else
    core_logger->set_level(spdlog::level::trace);
    spdlog::set_level(spdlog::level::trace);
#endif // NDEBUG

    log_version();
    log_os();
    log_compiler();

    return true;
  } catch (const spdlog::spdlog_ex &ex) {
    std::cerr << "Core logger initialization failed: " << ex.what()
              << std::endl;
    return false;
  }
}
bool cieo::logger::initialize_client_logger(const std::string &name) {
  try {
    client_logger[name] =
        std::make_shared<spdlog::logger>(name, begin(sinks), end(sinks));
#ifdef NDEBUG
    client_logger[name]->set_level(spdlog::level::info);
#else
    client_logger[name]->set_level(spdlog::level::trace);
#endif // NDEBUG

    return true;
  } catch (const spdlog::spdlog_ex &ex) {
    std::cerr << "Client logger initialization failed: " << ex.what()
              << std::endl;
    return false;
  }
}

bool cieo::logger::terminate_core_logger() {
  if (core_logger) {
    core_logger.reset();
    return true;
  }
  std::cerr << "Failed to free core logger, it was never created, or was "
               "already terminated."
            << std::endl;
  return false;
}
bool cieo::logger::terminate_client_logger(const std::string &name) {
  if (!client_logger.empty() &&
      client_logger.find(name) != client_logger.end()) {
    client_logger.erase(client_logger.find(name));
    return true;
  }
  std::cerr << "Failed to remvoe client logger \"" << name
            << "\", it was never created, or was already removed." << std::endl;
  return false;
}

std::shared_ptr<spdlog::logger> cieo::logger::get_core() { return core_logger; }
std::shared_ptr<spdlog::logger>
cieo::logger::get_client(const std::string &name) {
  return client_logger.at(name);
}

void cieo::logger::log_os() {
#if CIEO_OS_IS_Windows
  get_core()->log(spdlog::level::info, "OS: {}", "Windows");
#elif CIEO_OS_IS_Android
  get_core()->log(spdlog::level::info, "OS: {}", "Android");
#elif CIEO_OS_IS_Linux
  get_core()->log(spdlog::level::info, "OS: {}", "Linux");
#elif CIEO_OS_IS_BSD
  get_core()->log(spdlog::level::info, "OS: {}", "BSD");
#elif CIEO_OS_IS_HP_UX
  get_core()->log(spdlog::level::info, "OS: {}", "HP_UX");
#elif CIEO_OS_IS_AIX
  get_core()->log(spdlog::level::info, "OS: {}", "AIX");
#elif CIEO_OS_IS_IOS
  get_core()->log(spdlog::level::info, "OS: {}", "IOS");
#elif CIEO_OS_IS_OSX
  get_core()->log(spdlog::level::info, "OS: {}", "OSX");
#elif CIEO_OS_IS_Solaris
  get_core()->log(spdlog::level::info, "OS: {}", "Solaris");
#else
  get_core()->log(spdlog::level::info, "OS: {}", "(null)");
#endif
}
void cieo::logger::log_compiler() {
#if CIEO_COMPILER_IS_Comeau
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "Comeau",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_Intel
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "Intel",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_PathScale
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "PathScale",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_Embarcadero
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "Embarcadero",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_Borland
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "Borland",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_Watcom
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "Watcom",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_OpenWatcom
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "OpenWatcom",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_SunPro
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "SunPro",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_HP
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "HP",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_Compaq
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "Compaq",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_zOS
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "zOS",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_XLClang
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "XLClang",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_XL
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "XL",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_VisualAge
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "VisualAge",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_PGI
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "PGI",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_Cray
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "Cray",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_TI
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "TI",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_Fujitsu
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "Fujitsu",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_GHS
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "GHS",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_SCO
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "SCO",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_ARMCC
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "ARMCC",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_AppleClang
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "AppleClang",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_ARMClang
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "ARMClang",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_Clang
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "Clang",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_GNU
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "GNU",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_MSVC
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "MSVC",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_ADSP
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "ADSP",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_IAR
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "IAR",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#elif CIEO_COMPILER_IS_MIPSpro
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "MIPSpro",
                  CIEO_COMPILER_VERSION_MAJOR, CIEO_COMPILER_VERSION_MINOR,
                  CIEO_COMPILER_VERSION_PATCH);
#else
  get_core()->log(spdlog::level::info, "Compiler: {} {}.{}.{}", "(null)", 0, 0,
                  0);
#endif
}
void cieo::logger::log_version() {
  get_core()->log(spdlog::level::info, "Version: {}.{}.{} {}", CIEO_VERSION_MAJOR,
                  CIEO_VERSION_MINOR, CIEO_VERSION_PATCH, CIEO_VERSION_GIT_HASH);
}
