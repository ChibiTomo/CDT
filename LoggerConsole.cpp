#include "LoggerConsole.h"

namespace cdt {
	void LoggerConsole::_write(const std::string& toLog) {
		std::cout << toLog;
	}
}
