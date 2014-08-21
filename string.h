#ifndef STRING_H
#define STRING_H

#include <string>

namespace cdt {

	bool strStartsWith(const std::string& str, const std::string& needle);
	bool strEndsWith(const std::string& str, const std::string& needle);
	std::string makeString(const std::string& format, ...);

}

#endif // STRING_H
