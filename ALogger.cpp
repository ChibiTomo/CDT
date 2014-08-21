#include <ctime>

#include "ALogger.h"

namespace cdt {
	ALogger::ALogger() {}
	ALogger::~ALogger() {}

	ALogger& ALogger::operator<< (std::ostream& (*f)(std::ostream&)) {
		std::stringstream ss;
		f(ss);
		_write(ss.str());
		return *this;
	};

	std::string ALogger::_date() const {
		char sTime[24];
		time_t currTime = time(NULL);
		strftime(sTime, sizeof(sTime), "%d/%m/%Y", localtime(&currTime));

		return sTime;
	}

	std::string ALogger::_time() const {
		char sTime[24];
		time_t currTime = time(NULL);
		strftime(sTime, sizeof(sTime), "%H:%M:%S", localtime(&currTime));

		return sTime;
	}
}
