#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
std::shared_ptr<spdlog::logger> Log::s_CoreLogger;

void Log::init()
{
	// log pattern
	spdlog::set_pattern("%^[%T] %n: %v%$");

	// core logger
	s_CoreLogger = spdlog::stdout_color_mt("CORE");
	s_CoreLogger->set_level(spdlog::level::trace);
	s_CoreLogger->info("Initialized core log system");

	// client logger
	s_ClientLogger = spdlog::stdout_color_mt("APP");
	s_ClientLogger->set_level(spdlog::level::trace);
	s_ClientLogger->info("Initialized client log system");
}
