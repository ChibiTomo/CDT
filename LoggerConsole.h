#ifndef LOGGERCONSOLE_H
#define LOGGERCONSOLE_H

#include <iostream>

#include "ALogger.h"

namespace cdt {
	class LoggerConsole : public ALogger {
		private:
			virtual void _write(const std::string& toLog);
	};

}

#endif // LOGGERCONSOLE_H
