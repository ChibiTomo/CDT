#include <cstdio>
#include <cstdarg>

#include "string.h"

namespace cdt {
	bool strStartsWith(const std::string& str, const std::string& needle) {
		size_t pos = str.find(needle);
		return pos == 0;
	}

	bool strEndsWith(const std::string& str, const std::string& needle) {
		size_t pos = str.find_last_of(needle);
		return pos == (str.length() - 1);
	}

	std::string makeString(const std::string& format, ...) {
		char buff[1024];
		va_list arguments;
		va_start(arguments, format);
		vsnprintf(buff, 1024, format.c_str(), arguments);
		va_end(arguments);
		return std::string(buff);
	}
}
