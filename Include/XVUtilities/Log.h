#pragma once

#include "../../Dep/spdlog/include/spdlog/spdlog.h"
#include "../../Dep/spdlog/include/spdlog/sinks/stdout_color_sinks.h"
#include "../../Dep/spdlog/include/spdlog/sinks/rotating_file_sink.h"

#include "Types.h"

namespace XV
{
  class Log
  {
    inline static SharedPtr<spdlog::logger> core_logger;
    inline static SharedPtr<spdlog::logger> app_logger;

  public:
    inline static SharedPtr<spdlog::logger> GetCoreLogger()
    {
      return core_logger;
    }

    inline static SharedPtr<spdlog::logger> GetAppLogger()
    {
      return app_logger;
    }

    inline static void Init()
    {
      std::vector<spdlog::sink_ptr> sinks;
      spdlog::set_level(spdlog::level::trace);

      sinks.emplace_back(MakeShared<spdlog::sinks::stdout_color_sink_mt>()); // For Debug
      sinks[0]->set_pattern("%^[%T] %n (%l): %v%$");

      core_logger = MakeShared<spdlog::logger>("Core", sinks.begin(), sinks.end());
      core_logger->set_level(spdlog::level::trace);
      core_logger->flush_on(spdlog::level::trace);
      spdlog::register_logger(core_logger);

      app_logger = MakeShared<spdlog::logger>("Application", sinks.begin(), sinks.end());
      app_logger->set_level(spdlog::level::trace);
      app_logger->flush_on(spdlog::level::trace);
      spdlog::register_logger(app_logger);
    }

    inline static void SetFileSink(const std::string &filename,
                                   const std::string &pattern = "%^[%T] %n (%l): %v%$",
                                   u32 log_size = 1048576u * 5,
                                   u32 log_file_count = 3)
    {
      constexpr u32 MB = 1048576u;
      constexpr u32 LOG_SIZE = MB * 5;
      constexpr u32 LOG_FILES_COUNT = 3;
      auto sref = MakeShared<spdlog::sinks::rotating_file_sink_mt>(filename, log_size, log_file_count);
      sref->set_pattern(pattern);
      core_logger->sinks().push_back(sref);
      app_logger->sinks().push_back(sref);
    }
  };
}

// Core log macros
#define XV_CORE_TRACE(...) ::Xivi::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define XV_CORE_INFO(...) ::Xivi::Log::GetCoreLogger()->info(__VA_ARGS__)
#define XV_CORE_WARN(...) ::Xivi::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define XV_CORE_ERROR(...) ::Xivi::Log::GetCoreLogger()->error(__VA_ARGS__)
#define XV_CORE_CRITICAL(...) ::Xivi::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define XV_TRACE(...) ::Xivi::Log::GetAppLogger()->trace(__VA_ARGS__)
#define XV_INFO(...) ::Xivi::Log::GetAppLogger()->info(__VA_ARGS__)
#define XV_WARN(...) ::Xivi::Log::GetAppLogger()->warn(__VA_ARGS__)
#define XV_ERROR(...) ::Xivi::Log::GetAppLogger()->error(__VA_ARGS__)
#define XV_CRITICAL(...) ::Xivi::Log::GetAppLogger()->critical(__VA_ARGS__)