#pragma once
#include "logger/Log.h"

#include <GL/glew.h>


#if APP_DEBUG
	#define APP_CONFIGURATION "debug"
	#define ASSERT(x) if(!(x)) __debugbreak()
	#define RELEASE(x) x
	#define DEBUG(x) x
	#define GL_CALL(x) glClearErrors(); x; ASSERT(glLogCall(#x, __FILE__, __LINE__))
#elif APP_RELEASE
	#define APP_CONFIGURATION "release"
	#define ASSERT(x) if(!(x)) __debugbreak()
	#define RELEASE(x) x
	#define DEBUG(x)
	#define GL_CALL(x) glClearErrors(); x; glLogCall(#x, __FILE__, __LINE__)
#elif APP_DIST
	#define APP_CONFIGURATION "dist"
	#define ASSERT(x)
	#define RELEASE(x)
	#define DEBUG(x)
	#define GL_CALL(x) x	
#else
	#error(Unknown configuration)
	#define ASSERT(x) if(!(x)) {}
	#define APP_CONFIGURATION "unknown"
	#define RELEASE(x) x
	#define DEBUG(x) x
	#define GL_CALL(x) x
#endif

inline void glClearErrors()
{
	while (glGetError() != GL_NO_ERROR);
}

inline bool glLogCall(const char* function, const char* file, long line)

{
	bool noErr = true;
	while (GLenum error = glGetError())
	{
		APP_CORE_ERROR("[OpenGL Error] {}: in {}.{}:{}\n", error, function, file, line);
		noErr = false;
	}
	return noErr;
}