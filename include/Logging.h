#pragma once

#pragma once
#include <string>
#include <iostream>
#include <sstream>

#if __ANDROID__

#define APPNAME "RAT"
#include <android/log.h>

#endif

namespace SL {
	namespace WS_LITE {

		enum Logging_Levels {
			DEBUG_log_level,
			ERROR_log_level,
			FATAL_log_level,
			INFO_log_level,
			WARN_log_level
		};
		const std::string Logging_level_Names[] = { "DEBUG", "ERROR", "FATAL", "INFO", "WARN" };
		inline void Log(Logging_Levels level, const char* file, int line, const char* func, std::ostringstream& data)
		{
#if __ANDROID__

			std::ostringstream buffer;
			buffer << Logging_level_Names[level] << ": FILE: " << file << " Line: " << line << " Func: " << func << " Msg: " << data.str();
			auto msg = buffer.str();
			switch (level) {
			case(Debug_log_level):
				__android_log_print(ANDROID_LOG_DEBUG, APPNAME, "%s", msg.c_str());
				break;
			case(ERROR_log_level):
				__android_log_print(ANDROID_LOG_ERROR, APPNAME, "%s", msg.c_str());
				break;
			case(FATAL_log_level):
				__android_log_print(ANDROID_LOG_FATAL, APPNAME, "%s", msg.c_str());
				break;
			case(INFO_log_level):
				__android_log_print(ANDROID_LOG_INFO, APPNAME, "%s", msg.c_str());
				break;
			case(WARN_log_level):
				__android_log_print(ANDROID_LOG_WARN, APPNAME, "%s", msg.c_str());
				break;
			default:
				__android_log_print(ANDROID_LOG_INFO, APPNAME, "%s", msg.c_str());

			}
#else
			std::cout << Logging_level_Names[level] << ": FILE: " << file << " Line: " << line << " Func: " << func << " Msg: " << data.str() << std::endl;

#endif
		}

	}
}
#define UNUSED(x) (void)(x)
#define S(x) #x
#define S_(x) S(x)

#if NDEBUG
#define SL_WS_LITE_LOG(level, msg) 
#else

#define SL_WS_LITE_LOG(level, msg) {\
std::ostringstream buffersl134nonesd; \
buffersl134nonesd << msg; \
SL::WS_LITE::Log(level, __FILE__, __LINE__, __func__, buffersl134nonesd);\
}

#endif
