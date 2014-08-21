#include <sstream>
#include <string>

#include "FileLogger.h"

namespace cdt {
	FileLogger::FileLogger(const std::string& filePath, const std::string& title, bool overwrite)
			: m_file(filePath), m_title(title) {
		if (overwrite) {
			m_file.rm();
		}

		if (!m_file.exists()) {
			m_file.create();
		}

		m_file.open("ab");

		std::stringstream ss;
		ss	<< "************************************************" << std::endl
			<< " Start " << m_title << " - " << _date() << " at " << _time() << std::endl
			<< "************************************************" << std::endl;

		_write(ss.str());
	}

	FileLogger::~FileLogger() {
		std::stringstream ss;
		ss	<< "************************************************" << std::endl
			<< " End " << m_title << " - " << _date() << " at " << _time() << std::endl
			<< "************************************************" << std::endl;

		_write(ss.str());
	}

	void FileLogger::_write(const std::string& toLog) {
		const char *str = toLog.c_str();
		m_file.write(str, strlen(str), 1);
	}
}
