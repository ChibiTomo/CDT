#ifndef ALOGGER_H
#define ALOGGER_H

#include <string>
#include <sstream>

namespace ChibiDevTools {

	class ALogger {
		public:
			ALogger();
			virtual ~ALogger();

			template <typename T>
			ALogger& operator<<(const T& toLog);

			ALogger& operator<<(std::ostream& (*f)(std::ostream&));
		protected:
			std::string _date() const;
			std::string _time() const;
		private:
			virtual void _write(const std::string& toLog) = 0;
	};

	template <typename T>
	ALogger& ALogger::operator<<(const T& toLog) {
		std::stringstream ss;
		ss << toLog;
		_write(ss.str());
		return *this;
	}

}

#endif // ALOGGER_H
