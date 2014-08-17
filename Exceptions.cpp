#include "Exceptions.h"

namespace ChibiDevTools {

	Exception::Exception(File file, int line) :
		m_file(file),
		m_line(line) {};

	Exception::Exception(File file, int line, const std::string& msg) :
		m_msg(msg),
		m_file(file),
		m_line(line) {}

	Exception::~Exception() throw() {}

	const char* Exception::getMsg() const {
		std::stringstream ss;
		ss << m_file.basename() << "(" << m_line << "): " << m_msg;
		return ss.str().c_str();
	}

	AssertException::AssertException(File file, int line, const std::string& msg) :
		Exception(file, line, msg) {}

	NullPointerException::NullPointerException(File file, int line, const std::string& ptr) :
		Exception(file, line) {
			std::stringstream ss;
			ss << "Null pointer Exception: " << ptr;
			m_msg = ss.str();
		}

}
