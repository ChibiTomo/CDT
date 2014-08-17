#ifndef ALOGMANAGER_H
#define ALOGMANAGER_H

#include <string>

#include "ASingleton.h"
#include "ALogger.h"
#include "Map.h"

namespace ChibiDevTools {

	class LogManager : public ASingleton<LogManager> {
		friend class ASingleton<LogManager>;
		public:
			void add(const std::string& name, ALogger* logger);
			void remove(const std::string& name);

			ALogger& log();
			ALogger& log(const std::string& name);
		protected:
		private:
			LogManager();
			virtual ~LogManager();

			Map<std::string, ALogger *> m_map;
			ALogger* m_last;
	};

}

#endif // ALOGMANAGER_H
