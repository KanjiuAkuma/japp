#pragma once

#include <spdlog/spdlog.h>

namespace JApp {

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

}

#if APP_DEBUG

// Core log macros
#define APP_CORE_TRACE(...)    JApp::Log::getCoreLogger()->trace(__VA_ARGS__)
#define APP_CORE_INFO(...)     JApp::Log::getCoreLogger()->info(__VA_ARGS__)
#define APP_CORE_WARN(...)     JApp::Log::getCoreLogger()->warn(__VA_ARGS__)
#define APP_CORE_ERROR(...)    JApp::Log::getCoreLogger()->error(__VA_ARGS__)
#define APP_CORE_CRITICAL(...) JApp::Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define APP_TRACE(...)      JApp::Log::getClientLogger()->trace(__VA_ARGS__)
#define APP_INFO(...)       JApp::Log::getClientLogger()->info(__VA_ARGS__)
#define APP_WARN(...)       JApp::Log::getClientLogger()->warn(__VA_ARGS__)
#define APP_ERROR(...)      JApp::Log::getClientLogger()->error(__VA_ARGS__)
#define APP_CRITICAL(...)   JApp::Log::getClientLogger()->critical(__VA_ARGS__)

#elif APP_RELEASE

// Core log macros
#define APP_CORE_TRACE(...)
#define APP_CORE_INFO(...)		JApp::Log::getCoreLogger()->info(__VA_ARGS__)
#define APP_CORE_WARN(...)		JApp::Log::getCoreLogger()->warn(__VA_ARGS__)
#define APP_CORE_ERROR(...)		JApp::Log::getCoreLogger()->error(__VA_ARGS__)
#define APP_CORE_CRITICAL(...)	JApp::Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define APP_TRACE(...)
#define APP_INFO(...)			JApp::Log::getClientLogger()->info(__VA_ARGS__)
#define APP_WARN(...)			JApp::Log::getClientLogger()->warn(__VA_ARGS__)
#define APP_ERROR(...)			JApp::Log::getClientLogger()->error(__VA_ARGS__)
#define APP_CRITICAL(...)		JApp::Log::getClientLogger()->critical(__VA_ARGS__)

#else

// Core log macros
#define APP_CORE_TRACE(...)
#define APP_CORE_INFO(...)
#define APP_CORE_WARN(...)
#define APP_CORE_ERROR(...)		JApp::Log::getCoreLogger()->error(__VA_ARGS__)
#define APP_CORE_CRITICAL(...)  JApp::Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define APP_TRACE(...)
#define APP_INFO(...)
#define APP_WARN(...)
#define APP_ERROR(...)		JApp::Log::getClientLogger()->error(__VA_ARGS__)
#define APP_CRITICAL(...)	JApp::Log::getClientLogger()->critical(__VA_ARGS__)
#endif

