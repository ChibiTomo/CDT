#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>
#include <sstream>

#include "File.h"

namespace ChibiDevTools {

	class Exception : std::exception {
		public:
			Exception(File file, int line);
			Exception(File file, int line, const std::string& msg);
			virtual ~Exception() throw ();
			const char* getMsg() const;

		protected:
			std::string m_msg;

		private:
			File m_file;
			int m_line;
	};

	struct AssertException : public Exception {
		AssertException(File file, int line, const std::string& msg);
	};

	struct NullPointerException : public Exception {
		NullPointerException(File file, int line, const std::string& msg);
	};

}

#define ASSERT(condition) ASSERT_MSG(condition, "Assertion exception: " #condition)

#define ASSERT_MSG(condition, msg) \
	if (!(condition)) \
		throw ChibiDevTools::AssertException( \
							ChibiDevTools::File(__FILE__), \
							__LINE__, \
							msg)

#define ASSERT_NOT_NULL(ptr) \
	if (ptr == NULL) \
		throw ChibiDevTools::AssertException( \
							ChibiDevTools::File(__FILE__), \
							__LINE__, \
							#ptr)


#endif // EXCEPTIONS_H
