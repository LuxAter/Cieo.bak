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
// #include <spdlog/pattern_formatter.h>

#include <spdlog/sinks/base_sink.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/null_sink.h>
#include <spdlog/sinks/ostream_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/sink.h>
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

template <typename ConsoleMutex>
class ansicolor_icon_sink : public spdlog::sinks::sink {
public:
  using mutex_t = typename ConsoleMutex::mutex_t;
  ansicolor_icon_sink(FILE *target_file, spdlog::color_mode mode)
      : target_file_(target_file), mutex_(ConsoleMutex::mutex()),
        formatter_(spdlog::details::make_unique<spdlog::pattern_formatter>()) {
    set_color_mode(mode);
    colors_[spdlog::level::trace] = white;
    colors_[spdlog::level::debug] = cyan;
    colors_[spdlog::level::info] = green;
    colors_[spdlog::level::warn] = yellow_bold;
    colors_[spdlog::level::err] = red_bold;
    colors_[spdlog::level::critical] = bold_on_red;
    colors_[spdlog::level::off] = reset;
  }
  ~ansicolor_icon_sink() override = default;

  ansicolor_icon_sink(const ansicolor_icon_sink &other) = delete;
  ansicolor_icon_sink(ansicolor_icon_sink &&other) = delete;

  ansicolor_icon_sink &operator=(const ansicolor_icon_sink &other) = delete;
  ansicolor_icon_sink &operator=(ansicolor_icon_sink &&other) = delete;

  void set_color(spdlog::level::level_enum color_level,
                 spdlog::string_view_t color) {
    std::lock_guard<mutex_t> lock(mutex_);
    colors_[color_level] = color;
  }
  void set_color_mode(spdlog::color_mode mode) {
    switch (mode) {
    case spdlog::color_mode::always:
      should_do_colors_ = true;
      break;
    case spdlog::color_mode::automatic:
      should_do_colors_ = spdlog::details::os::in_terminal(target_file_) &&
                          spdlog::details::os::is_color_terminal();
      return;
    case spdlog::color_mode::never:
      should_do_colors_ = false;
      return;
    }
  }
  bool should_color() { return should_do_colors_; }

  void log(const spdlog::details::log_msg &msg) override {
    std::lock_guard<mutex_t> lock(mutex_);
    msg.color_range_start = 0;
    msg.color_range_end = 0;
    spdlog::memory_buf_t formatted;
    formatter_->format(msg, formatted);
    if (should_do_colors_ && msg.color_range_end > msg.color_range_start) {
      print_range_(formatted, 0, msg.color_range_start);
      print_ccode_(colors_[msg.level]);
      print_range_(formatted, msg.color_range_start, msg.color_range_end);
      print_ccode_(reset);
      print_range_(formatted, msg.color_range_end, formatted.size());
    } else {
      print_range_(formatted, 0, formatted.size());
    }
    fflush(target_file_);
  }
  void flush() override {
    std::lock_guard<mutex_t> lock(mutex_);
    fflush(target_file_);
  }
  void set_pattern(const std::string &pattern) final {
    std::lock_guard<mutex_t> lock(mutex_);
    formatter_ = std::unique_ptr<spdlog::formatter>(
        new spdlog::pattern_formatter(pattern));
  }
  void
  set_formatter(std::unique_ptr<spdlog::formatter> sink_formatter) override {
    std::lock_guard<mutex_t> lock(mutex_);
    formatter_ = std::move(sink_formatter);
  }

  // Formatting codes
  const spdlog::string_view_t reset = "\033[m";
  const spdlog::string_view_t bold = "\033[1m";
  const spdlog::string_view_t dark = "\033[2m";
  const spdlog::string_view_t underline = "\033[4m";
  const spdlog::string_view_t blink = "\033[5m";
  const spdlog::string_view_t reverse = "\033[7m";
  const spdlog::string_view_t concealed = "\033[8m";
  const spdlog::string_view_t clear_line = "\033[K";

  // Foreground colors
  const spdlog::string_view_t black = "\033[30m";
  const spdlog::string_view_t red = "\033[31m";
  const spdlog::string_view_t green = "\033[32m";
  const spdlog::string_view_t yellow = "\033[33m";
  const spdlog::string_view_t blue = "\033[34m";
  const spdlog::string_view_t magenta = "\033[35m";
  const spdlog::string_view_t cyan = "\033[36m";
  const spdlog::string_view_t white = "\033[37m";

  /// Background colors
  const spdlog::string_view_t on_black = "\033[40m";
  const spdlog::string_view_t on_red = "\033[41m";
  const spdlog::string_view_t on_green = "\033[42m";
  const spdlog::string_view_t on_yellow = "\033[43m";
  const spdlog::string_view_t on_blue = "\033[44m";
  const spdlog::string_view_t on_magenta = "\033[45m";
  const spdlog::string_view_t on_cyan = "\033[46m";
  const spdlog::string_view_t on_white = "\033[47m";

  /// Bold colors
  const spdlog::string_view_t yellow_bold = "\033[33m\033[1m";
  const spdlog::string_view_t red_bold = "\033[31m\033[1m";
  const spdlog::string_view_t bold_on_red = "\033[1m\033[41m";

private:
  void print_ccode_(const spdlog::string_view_t &color_code) {
    fwrite(color_code.data(), sizeof(char), color_code.size(), target_file_);
  }
  void print_range_(const spdlog::memory_buf_t &formatted, size_t start,
                    size_t end) {
    fwrite(formatted.data() + start, sizeof(char), end - start, target_file_);
  }

  FILE *target_file_;
  mutex_t &mutex_;
  bool should_do_colors_;
  std::unique_ptr<spdlog::formatter> formatter_;
  std::array<spdlog::string_view_t, spdlog::level::n_levels> colors_;
};

template <typename ConsoleMutex>
class ansicolor_icon_stdout_sink : public ansicolor_icon_sink<ConsoleMutex> {
public:
  explicit ansicolor_icon_stdout_sink(
      spdlog::color_mode mode = spdlog::color_mode::automatic)
      : ansicolor_icon_sink<ConsoleMutex>(stdout, mode) {}
};
template <typename ConsoleMutex>
class ansicolor_icon_stderr_sink : public ansicolor_icon_sink<ConsoleMutex> {
public:
  explicit ansicolor_icon_stderr_sink(
      spdlog::color_mode mode = spdlog::color_mode::automatic)
      : ansicolor_icon_sink<ConsoleMutex>(stderr, mode) {}
};

using ansicolor_icon_stdout_sink_mt =
    ansicolor_icon_stdout_sink<spdlog::details::console_mutex>;
using ansicolor_icon_stdout_sink_st =
    ansicolor_icon_stdout_sink<spdlog::details::console_nullmutex>;
using ansicolor_icon_stderr_sink_mt =
    ansicolor_icon_stderr_sink<spdlog::details::console_mutex>;
using ansicolor_icon_stderr_sink_st =
    ansicolor_icon_stderr_sink<spdlog::details::console_nullmutex>;

typedef spdlog::sinks::rotating_file_sink_mt RotatingFileSink;
typedef spdlog::sinks::daily_file_sink_mt DailyFileSink;
typedef spdlog::sinks::basic_file_sink_mt BasicFileSink;
typedef spdlog::sinks::stdout_sink_mt StdoutSink;
typedef spdlog::sinks::stderr_sink_mt StderrSink;
typedef spdlog::sinks::stdout_color_sink_mt StdoutColorSink;
typedef spdlog::sinks::stderr_color_sink_mt StderrColorSink;
typedef spdlog::sinks::ostream_sink_mt OstreamSink;
typedef spdlog::sinks::null_sink_mt NullSink;

typedef ansicolor_icon_stdout_sink_mt StdoutColorIconSink;

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
