#include <sstream>
#include <cstdio>
#include <cerrno>
#include <dirent.h>
#include <unistd.h>

#include "File.h"
#include "Exceptions.h"
#include "string.h"

namespace ChibiDevTools {

	File::File(const std::string& name) : m_name(name) {
		_init();
	}

	File::File(const char* name) : m_name(std::string(name)) {
		_init();
	}

	void File::_init() {
		m_file = NULL;
		m_exists = -1;
		while (strEndsWith(m_name, "/") || strEndsWith(m_name, "\\")) {
			m_name = m_name.substr(0, m_name.length() - 1);
		}
		_stat();
	}

	void File::_stat() {
		memset(&m_stat, 0, sizeof(struct stat));
		m_exists = stat(m_name.c_str(), &m_stat);
	}

	File::~File() {
		if (isOpen()) {
			close();
		}
	}

	std::string File::fullname() const {
		return m_name;
	}

	std::string File::dirname() const {
		unsigned pos = m_name.find(basename());
		std::string str = m_name.substr(0, pos);
		if (str.empty()) {
			str = ".";
		}
		return str;
	}

	std::string File::basename() const {
		std::string c = _basename(m_name, '\\');
		return _basename(c, '/');
	}

	std::string File::_basename(std::string path, const char separator) const {
		char* c = strrchr(path.c_str(), separator);
		return (c)? c + 1 : path;
	}

	std::string File::simpleName() const {
		std::string str = basename();
		unsigned pos = str.find('.' + extention());
		return str.substr(0, pos);
	}

	std::string File::extention() const {
		char* c = strrchr(m_name.c_str(), '.');
		return (c)? c + 1 : "";
	}

	bool File::exists() {
		_stat();
		return (m_exists == 0);
	}

	bool File::isFile() {
		_stat();
		return exists() && S_ISREG(m_stat.st_mode);
	}

	bool File::isDir() {
		_stat();
		return exists() && S_ISDIR(m_stat.st_mode);
	}

	bool File::isWritable() {
		_stat();
		return S_IWUSR & m_stat.st_mode;
	}
	bool File::isReadable() {
		_stat();
		return S_IRUSR & m_stat.st_mode;
	}

	void File::create(bool isFile) {
		if (exists()) {
			return;
		}

		std::string dir = fullname();
		if (isFile) {
			dir = dirname();
		}

		_mkdir(dir);

		if (!isFile) {
			return;
		}

		FILE* fd = NULL;
		fd = fopen(fullname().c_str(), "wb");
		ASSERT_MSG(fd, makeString("Cannot create \"%s\": (%d) %s", fullname().c_str(), errno, strerror(errno)));
		ASSERT_MSG(fclose(fd) == 0, makeString("Cannot finalize the creation of file \"%s\"", fullname().c_str()));

		_init();
	}

	void File::_mkdir(const std::string& path) {
		File dir(path);
		File parent(dir.dirname());
		if (!parent.exists()) {
			_mkdir(parent.fullname());
		}

		if (!dir.exists()) {
			ASSERT_MSG(mkdir(path.c_str()) == 0,
						makeString("Cannot open \"%s\": (%d) %s", fullname().c_str(), errno, strerror(errno)));
		}
	}

	void File::open(const std::string& mode) {
		ASSERT_MSG(exists(), makeString("File does not exists: %s", fullname().c_str()));
		ASSERT_MSG(!isOpen(), makeString("File is already opened: %s", fullname().c_str()));
		m_file = fopen(fullname().c_str(), mode.c_str());
		ASSERT_MSG(m_file, makeString("Cannot open \"%s\": (%d) %s", fullname().c_str(), errno, strerror(errno)));
	}

	bool File::isOpen() {
		return !isDir() && isFile() && m_file != NULL;
	}

	void File::close() {
		ASSERT(isOpen());
		ASSERT_MSG(fclose(m_file) == 0, makeString("Cannot close the file \"%s\"", fullname().c_str()));
		m_file = NULL;
	}

	void File::rm() {
		if (!exists()) {
			return;
		}

		if (isOpen()) {
			close();
		}

		if (isFile()) {
			ASSERT_MSG(remove(fullname().c_str()) == 0,
						makeString("Cannot remove \"%s\": (%d) %s", fullname().c_str(), errno, strerror(errno)));
		} else if (isDir()) {
			this->_rmdir(fullname());
		}
	}

	void File::_rmdir(const std::string& path) {
		DIR *dir = NULL;
		dir = opendir(path.c_str());
		ASSERT_MSG(dir != NULL,
					makeString("Cannot open dir \"%s\": (%d) %s", path.c_str(), errno, strerror(errno)));

		struct dirent *dir_s = NULL;
		while ((dir_s = readdir(dir)) != NULL) {
			char *fname = dir_s->d_name;
			if (strcmp(fname, ".") == 0 || strcmp(fname, "..") == 0) {
				continue;
			}

			std::stringstream fullpath;
			fullpath << path << "/" << fname;
			File file(fullpath.str());
			file.rm();
		}

		closedir(dir);

		rmdir(path.c_str());
	}

	size_t File::write(const void* ptr, size_t size, size_t count) {
		ASSERT(isOpen());
		size_t written = fwrite(ptr, size, count, m_file);
		ASSERT_MSG(written == count,
					makeString("Cannot write to file \"%s\": (%d) %s", fullname().c_str(), errno, strerror(errno)));
		return written;
	}

}
