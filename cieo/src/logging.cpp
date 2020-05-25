#include "cieo/logging.hpp"

#include <iostream>
#include <memory>
#include <pthread.h>
#include <spdlog/logger.h>
#include <string>
#include <unordered_map>

#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

#include <spdlog/sinks/base_sink.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/null_sink.h>
#include <spdlog/sinks/ostream_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/stdout_sinks.h>

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
