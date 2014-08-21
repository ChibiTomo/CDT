#ifndef FILE_H
#define FILE_H

#include <sys/stat.h>
#include <cstring>

namespace cdt {

	class File {
		public:
			File(const std::string& name = "unknown");
			File(const char* name);
			virtual ~File();
			std::string fullname() const;
			std::string dirname() const;
			std::string basename() const;
			std::string simpleName() const;
			std::string extention() const;
			bool exists();
			bool isFile();
			bool isDir();
			bool isWritable();
			bool isReadable();

			void create(bool isFile = true);
			void open(const std::string& mode);
			bool isOpen();
			void close();
			void rm();
			size_t write(const void* ptr, size_t size, size_t count = 1);
			void seek();

			template<typename T> size_t write(const T& obj) {
				return write(&obj, sizeof(obj));
			};

		private:
			std::string m_name;
			int m_exists;
			struct stat m_stat;
			FILE* m_file;

			void _init();
			void _stat();
			std::string _basename(std::string path, const char separator) const;
			void _mkdir(const std::string& path);
			void _rmdir(const std::string& path);
	};

}

#endif // FILE_H
