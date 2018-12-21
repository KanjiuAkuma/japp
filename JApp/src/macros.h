#pragma once

#if APP_DEBUG
	#define APP_CONFIGURATION "debug"
	#define RELEASE(x) x
	#define DEBUG(x) x
	#define GL_CALL(x) x
#elif APP_RELEASE
	#define APP_CONFIGURATION "release"
	#define RELEASE(x) x
	#define DEBUG(x)
	#define GL_CALL(x) x
#elif APP_DIST
	#define APP_CONFIGURATION "dist"
	#define RELEASE(x)
	#define DEBUG(x)
	#define GL_CALL(x) x	
#else
	#error(Unknown configuration)
	#define APP_CONFIGURATION "unknown"
	#define RELEASE(x) x
	#define DEBUG(x) x
	#define GL_CALL(x) x
#endif