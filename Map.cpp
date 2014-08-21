#include "Map.h"

namespace cdt {

	UnknownKeyException::UnknownKeyException(File file, int line, const std::string& key) :
		Exception(file, line) {
			std::stringstream ss;
			ss << "Unknown key: " << key;
			m_msg = ss.str();
		}

}
