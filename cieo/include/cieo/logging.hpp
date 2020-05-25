#ifndef CIEO_LOGGING_HPP_
#define CIEO_LOGGING_HPP_

#include <iostream>
#include <memory>
#include <spdlog/details/pattern_formatter.h>
#include <string>

#ifndef NDEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif // NDEBUG

#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/null_sink.h>
#include <spdlog/sinks/ostream_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/stdout_sinks.h>

#define CIEO_LOGGER_CALL(logger, level, ...)                                   \
  (logger)->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION},       \
                level, __VA_ARGS__)
#define CIEO_LOGGER_SOURCE_CALL(logger, level, file, line, func, ...)          \
  (logger)->log(spdlog::source_loc(file, line, funcion), level, __VA_ARGS__)

#define CIEO_LOGGER_TRACE(logger, ...)                                         \
  CIEO_LOGGER_CALL(logger, spdlog::level::trace, __VA_ARGS__)
#define CIEO_LOGGER_DEBUG(logger, ...)                                         \
  CIEO_LOGGER_CALL(logger, spdlog::level::debug, __VA_ARGS__)
#define CIEO_LOGGER_INFO(logger, ...)                                          \
  CIEO_LOGGER_CALL(logger, spdlog::level::info, __VA_ARGS__)
#define CIEO_LOGGER_WARN(logger, ...)                                          \
  CIEO_LOGGER_CALL(logger, spdlog::level::warn, __VA_ARGS__)
#define CIEO_LOGGER_ERROR(logger, ...)                                         \
  CIEO_LOGGER_CALL(logger, spdlog::level::err, __VA_ARGS__)
#define CIEO_LOGGER_CRITICAL(logger, ...)                                      \
  CIEO_LOGGER_CALL(logger, spdlog::level::critical, __VA_ARGS__)

#define CIEO_LOGGER_SOURCE_TRACE(logger, ...)                                  \
  CIEO_LOGGER_SOURCE_CALL(logger, spdlog::level::trace, __VA_ARGS__)
#define CIEO_LOGGER_SOURCE_DEBUG(logger, ...)                                  \
  CIEO_LOGGER_SOURCE_CALL(logger, spdlog::level::debug, __VA_ARGS__)
#define CIEO_LOGGER_SOURCE_INFO(logger, ...)                                   \
  CIEO_LOGGER_SOURCE_CALL(logger, spdlog::level::info, __VA_ARGS__)
#define CIEO_LOGGER_SOURCE_WARN(logger, ...)                                   \
  CIEO_LOGGER_SOURCE_CALL(logger, spdlog::level::warn, __VA_ARGS__)
#define CIEO_LOGGER_SOURCE_ERROR(logger, ...)                                  \
  CIEO_LOGGER_SOURCE_CALL(logger, spdlog::level::err, __VA_ARGS__)
#define CIEO_LOGGER_SOURCE_CRITICAL(logger, ...)                               \
  CIEO_LOGGER_SOURCE_CALL(logger, spdlog::level::critical, __VA_ARGS__)

#define CIEO_CORE_LOGGER_TRACE(...)                                            \
  CIEO_LOGGER_TRACE(cieo::logger::get_core(), __VA_ARGS__)
#define CIEO_CORE_LOGGER_DEBUG(...)                                            \
  CIEO_LOGGER_DEBUG(cieo::logger::get_core(), __VA_ARGS__)
#define CIEO_CORE_LOGGER_INFO(...)                                             \
  CIEO_LOGGER_INFO(cieo::logger::get_core(), __VA_ARGS__)
#define CIEO_CORE_LOGGER_WARN(...)                                             \
  CIEO_LOGGER_WARN(cieo::logger::get_core(), __VA_ARGS__)
#define CIEO_CORE_LOGGER_ERROR(...)                                            \
  CIEO_LOGGER_ERROR(cieo::logger::get_core(), __VA_ARGS__)
#define CIEO_CORE_LOGGER_CRITICAL(...)                                         \
  CIEO_LOGGER_CRITICAL(cieo::logger::get_core(), __VA_ARGS__)

#define CIEO_CLIENT_LOGGER_TRACE(client, ...)                                  \
  CIEO_LOGGER_TRACE(cieo::logger::get_client(client), __VA_ARGS__)
#define CIEO_CLIENT_LOGGER_DEBUG(client, ...)                                  \
  CIEO_LOGGER_DEBUG(cieo::logger::get_client(client), __VA_ARGS__)
#define CIEO_CLIENT_LOGGER_INFO(client, ...)                                   \
  CIEO_LOGGER_INFO(cieo::logger::get_client(client), __VA_ARGS__)
#define CIEO_CLIENT_LOGGER_WARN(client, ...)                                   \
  CIEO_LOGGER_WARN(cieo::logger::get_client(client), __VA_ARGS__)
#define CIEO_CLIENT_LOGGER_ERROR(client, ...)                                  \
  CIEO_LOGGER_ERROR(cieo::logger::get_client(client), __VA_ARGS__)
#define CIEO_CLIENT_LOGGER_CRITICAL(client, ...)                               \
  CIEO_LOGGER_CRITICAL(cieo::logger::get_client(client), __VA_ARGS__)

#define CIEO_CORE_LOGGER_SOURCE_TRACE(file, line, func, ...)                   \
  CIEO_LOGGER_SOURCE_TRACE(cieo::logger::get_core(), file, line, func,         \
                           __VA_ARGS__)
#define CIEO_CORE_LOGGER_SOURCE_DEBUG(file, line, func, ...)                   \
  CIEO_LOGGER_SOURCE_DEBUG(cieo::logger::get_core(), file, line, func,         \
                           __VA_ARGS__)
#define CIEO_CORE_LOGGER_SOURCE_INFO(file, line, func, ...)                    \
  CIEO_LOGGER_SOURCE_INFO(cieo::logger::get_core(), file, line, func,          \
                          __VA_ARGS__)
#define CIEO_CORE_LOGGER_SOURCE_WARN(file, line, func, ...)                    \
  CIEO_LOGGER_SOURCE_WARN(cieo::logger::get_core(), file, line, func,          \
                          __VA_ARGS__)
#define CIEO_CORE_LOGGER_SOURCE_ERROR(file, line, func, ...)                   \
  CIEO_LOGGER_SOURCE_ERROR(cieo::logger::get_core(), file, line, func,         \
                           __VA_ARGS__)
#define CIEO_CORE_LOGGER_SOURCE_CRITICAL(file, line, func, ...)                \
  CIEO_LOGGER_SOURCE_CRITICAL(cieo::logger::get_core(), file, line, func,      \
                              __VA_ARGS__)

#define CIEO_CLIENT_LOGGER_SOURCE_TRACE(client, file, line, func, ...)         \
  CIEO_LOGGER_SOURCE_TRACE(cieo::logger::get_client(client), file, line, func, \
                           __VA_ARGS__)
#define CIEO_CLIENT_LOGGER_SOURCE_DEBUG(client, file, line, func, ...)         \
  CIEO_LOGGER_SOURCE_DEBUG(cieo::logger::get_client(client), file, line, func, \
                           __VA_ARGS__)
#define CIEO_CLIENT_LOGGER_SOURCE_INFO(client, file, line, func, ...)          \
  CIEO_LOGGER_SOURCE_INFO(cieo::logger::get_client(client), file, line, func,  \
                          __VA_ARGS__)
#define CIEO_CLIENT_LOGGER_SOURCE_WARN(client, file, line, func, ...)          \
  CIEO_LOGGER_SOURCE_WARN(cieo::logger::get_client(client), file, line, func,  \
                          __VA_ARGS__)
#define CIEO_CLIENT_LOGGER_SOURCE_ERROR(client, file, line, func, ...)         \
  CIEO_LOGGER_SOURCE_ERROR(cieo::logger::get_client(client), file, line, func, \
                           __VA_ARGS__)
#define CIEO_CLIENT_LOGGER_SOURCE_CRITICAL(client, file, line, func, ...)      \
  CIEO_LOGGER_SOURCE_CRITICAL(cieo::logger::get_client(client), file, line,    \
                              func, __VA_ARGS__)

#define LTRACE(...) CIEO_CORE_LOGGER_TRACE(__VA_ARGS__)
#define LDEBUG(...) CIEO_CORE_LOGGER_DEBUG(__VA_ARGS__)
#define LINFO(...) CIEO_CORE_LOGGER_INFO(__VA_ARGS__)
#define LWARN(...) CIEO_CORE_LOGGER_WARN(__VA_ARGS__)
#define LERROR(...) CIEO_CORE_LOGGER_ERROR(__VA_ARGS__)
#define LCRITICAL(...) CIEO_CORE_LOGGER_CRITICAL(__VA_ARGS__)

#define LCTRACE(client, ...) CIEO_CLIENT_LOGGER_TRACE(client, __VA_ARGS__)
#define LCDEBUG(client, ...) CIEO_CLIENT_LOGGER_DEBUG(client, __VA_ARGS__)
#define LCINFO(client, ...) CIEO_CLIENT_LOGGER_INFO(client, __VA_ARGS__)
#define LCWARN(client, ...) CIEO_CLIENT_LOGGER_WARN(client, __VA_ARGS__)
#define LCERROR(client, ...) CIEO_CLIENT_LOGGER_ERROR(client, __VA_ARGS__)
#define LCCRITICAL(client, ...) CIEO_CLIENT_LOGGER_CRITICAL(client, __VA_ARGS__)

#define LSTRACE(file, line, func, ...)                                         \
  CIEO_CORE_LOGGER_SOURCE_TRACE(__VA_ARGS__)
#define LSDEBUG(file, line, func, ...)                                         \
  CIEO_CORE_LOGGER_SOURCE_DEBUG(__VA_ARGS__)
#define LSINFO(file, line, func, ...) CIEO_CORE_LOGGER_SOURCE_INFO(__VA_ARGS__)
#define LSWARN(file, line, func, ...) CIEO_CORE_LOGGER_SOURCE_WARN(__VA_ARGS__)
#define LSERROR(file, line, func, ...)                                         \
  CIEO_CORE_LOGGER_SOURCE_ERROR(__VA_ARGS__)
#define LSCRITICAL(file, line, func, ...)                                      \
  CIEO_CORE_LOGGER_SOURCE_CRITICAL(__VA_ARGS__)

#define LCSTRACE(client, file, line, func, ...)                                \
  CIEO_CLIENT_LOGGER_SOURCE_TRACE(client, __VA_ARGS__)
#define LCSDEBUG(client, file, line, func, ...)                                \
  CIEO_CLIENT_LOGGER_SOURCE_DEBUG(client, __VA_ARGS__)
#define LCSINFO(client, file, line, func, ...)                                 \
  CIEO_CLIENT_LOGGER_SOURCE_INFO(client, __VA_ARGS__)
#define LCSWARN(client, file, line, func, ...)                                 \
  CIEO_CLIENT_LOGGER_SOURCE_WARN(client, __VA_ARGS__)
#define LCSERROR(client, file, line, func, ...)                                \
  CIEO_CLIENT_LOGGER_SOURCE_ERROR(client, __VA_ARGS__)
#define LCSCRITICAL(client, file, line, func, ...)                             \
  CIEO_CLIENT_LOGGER_SOURCE_CRITICAL(client, __VA_ARGS__)

namespace cieo {
namespace logger {

enum LogLevel {
  TRACE = spdlog::level::trace,
  DEBUG = spdlog::level::debug,
  INFO = spdlog::level::info,
  WARN = spdlog::level::warn,
  ERR = spdlog::level::err,
  CRITICAL = spdlog::level::critical,
  OFF = spdlog::level::off
};

typedef spdlog::sinks::rotating_file_sink_mt RotatingFileSink;
typedef spdlog::sinks::daily_file_sink_mt DailyFileSink;
typedef spdlog::sinks::basic_file_sink_mt BasicFileSink;
typedef spdlog::sinks::stdout_sink_mt StdoutSink;
typedef spdlog::sinks::stderr_sink_mt StderrSink;
typedef spdlog::sinks::stdout_color_sink_mt StdoutColorSink;
typedef spdlog::sinks::stderr_color_sink_mt StderrColorSink;
typedef spdlog::sinks::ostream_sink_mt OstreamSink;
typedef spdlog::sinks::null_sink_mt NullSink;

template <typename Sink, typename... Args>
void register_sink(const LogLevel &sink_level, const Args &... args) {
  push_sink(std::make_shared<Sink>(args...), sink_level);
}
template <typename Sink, typename A0, typename... Args>
typename std::enable_if<!std::is_same<A0, LogLevel>::value, void>::type
register_sink(const A0 &a0, const Args &... args) {
#ifdef NDEBUG
  push_sink(std::make_shared<Sink>(a0, args...), LogLevel::INFO);
#else
  push_sink(std::make_shared<Sink>(a0, args...), LogLevel::TRACE);
#endif // NDEBUG
}
template <typename Sink> void register_sink() {
#ifdef NDEBUG
  push_sink(std::make_shared<Sink>(), LogLevel::INFO);
#else
  push_sink(std::make_shared<Sink>(), LogLevel::TRACE);
#endif // NDEBUG
}

void push_sink(const spdlog::sink_ptr &sink, const LogLevel &sink_level);

bool initialize_core_logger();
bool initialize_client_logger(const std::string &name);

bool terminate_core_logger();
bool terminate_client_logger(const std::string &name);

std::shared_ptr<spdlog::logger> get_core();
std::shared_ptr<spdlog::logger> get_client(const std::string &name);

} // namespace logger
} // namespace cieo

#endif // CIEO_LOGGING_HPP_
