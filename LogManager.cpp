#include "LogManager.h"

#include "MemManagerOn.h"

namespace ChibiDevTools {

	LogManager::LogManager() : m_last(NULL) {}

	LogManager::~LogManager() {
		while (!m_map.isEmpty()) {
			remove(m_map.begin()->first);
		}
	}

	void LogManager::add(const std::string& name, ALogger* logger) {
		if (m_map.contains(name)) {
			m_map.erase(name);
		}
		m_map.put(name, logger);
	}

	void LogManager::remove(const std::string& name) {
		if (!m_map.contains(name)) {
			return;
		}

		ALogger* logger = m_map.get(name);
		if (m_last == logger) {
			m_last = NULL;
		}
		delete logger;
		logger = NULL;
		m_map.erase(name);
	}

	ALogger& LogManager::log() {
		ASSERT(m_last != NULL);
		return *m_last;
	}

	ALogger& LogManager::log(const std::string& name) {
		ALogger* logger = NULL;
		try {
			logger = m_map.get(name);
		} catch (UnknownKeyException e) {}
		ASSERT(logger != NULL);
		m_last = logger;
		return *logger;
	}

}
