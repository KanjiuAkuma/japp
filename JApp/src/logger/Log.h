#pragma once

#include <spdlog/spdlog.h>

class Log
{
private:
	static std::shared_ptr<spdlog::logger> s_ClientLogger;
	static std::shared_ptr<spdlog::logger> s_CoreLogger;

public:
	static void init();

	static std::shared_ptr<spdlog::logger>& getCoreLogger() {
		return s_CoreLogger;
	}

	static std::shared_ptr<spdlog::logger>& getClientLogger() {
		return s_ClientLogger;
	}
};

#if APP_DEBUG

// Core log macros
#define APP_CORE_TRACE(...)    Log::getCoreLogger()->trace(__VA_ARGS__)
#define APP_CORE_INFO(...)     Log::getCoreLogger()->info(__VA_ARGS__)
#define APP_CORE_WARN(...)     Log::getCoreLogger()->warn(__VA_ARGS__)
#define APP_CORE_ERROR(...)    Log::getCoreLogger()->error(__VA_ARGS__)
#define APP_CORE_CRITICAL(...) Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define APP_TRACE(...)      Log::getClientLogger()->trace(__VA_ARGS__)
#define APP_INFO(...)       Log::getClientLogger()->info(__VA_ARGS__)
#define APP_WARN(...)       Log::getClientLogger()->warn(__VA_ARGS__)
#define APP_ERROR(...)      Log::getClientLogger()->error(__VA_ARGS__)
#define APP_CRITICAL(...)   Log::getClientLogger()->critical(__VA_ARGS__)

#elif APP_RELEASE

// Core log macros
#define APP_CORE_TRACE(...)
#define APP_CORE_INFO(...)		Log::getCoreLogger()->info(__VA_ARGS__)
#define APP_CORE_WARN(...)		Log::getCoreLogger()->warn(__VA_ARGS__)
#define APP_CORE_ERROR(...)		Log::getCoreLogger()->error(__VA_ARGS__)
#define APP_CORE_CRITICAL(...)	Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define APP_TRACE(...)
#define APP_INFO(...)			Log::getClientLogger()->info(__VA_ARGS__)
#define APP_WARN(...)			Log::getClientLogger()->warn(__VA_ARGS__)
#define APP_ERROR(...)			Log::getClientLogger()->error(__VA_ARGS__)
#define APP_CRITICAL(...)		Log::getClientLogger()->critical(__VA_ARGS__)

#else

// Core log macros
#define APP_CORE_TRACE(...)
#define APP_CORE_INFO(...)
#define APP_CORE_WARN(...)
#define APP_CORE_ERROR(...)		Log::getCoreLogger()->error(__VA_ARGS__)
#define APP_CORE_CRITICAL(...)  Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define APP_TRACE(...)
#define APP_INFO(...)
#define APP_WARN(...)
#define APP_ERROR(...)		Log::getClientLogger()->error(__VA_ARGS__)
#define APP_CRITICAL(...)	Log::getClientLogger()->critical(__VA_ARGS__)
#endif

