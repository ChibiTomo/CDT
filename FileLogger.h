#ifndef FILELOGGER_H
#define FILELOGGER_H

#include "ALogger.h"
#include "File.h"

namespace ChibiDevTools {
	class FileLogger : public ALogger
	{
		public:
			FileLogger(const std::string& filePath, const std::string& title = "Log", bool overwrite = false);
			virtual ~FileLogger();
		protected:
		private:
			virtual void _write(const std::string& toLog);
			File m_file;
			std::string m_title;
	};
}

#endif // FILELOGGER_H
