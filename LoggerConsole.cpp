#include "LoggerConsole.h"

namespace ChibiDevTools {
	void LoggerConsole::_write(const std::string& toLog) {
		std::cout << toLog;
	}
}
