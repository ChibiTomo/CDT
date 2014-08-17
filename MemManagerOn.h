#ifdef __DEBUG

#ifndef MEMMANAGERON_H
#define MEMMANAGERON_H

#include "MemoryManager.h"
#include "File.h"

#include <cstdlib>
#include <iostream>

inline void* operator new(std::size_t size, const char* filename, int line) {
	return ChibiDevTools::MemoryManager::instance().allocate(size, filename, line);
}

inline void* operator new[](std::size_t size, const char* filename, int line) {
	return ChibiDevTools::MemoryManager::instance().allocate(size, filename, line, true);
}

inline void operator delete(void* ptr) {
	ChibiDevTools::MemoryManager::instance().disallocate(ptr);
}

inline void operator delete[](void* ptr) {
	ChibiDevTools::MemoryManager::instance().disallocate(ptr, true);
}

inline void operator delete(void* ptr, const char* filename, int line) {
	std::cout << "disallocate: 0x" << ptr << std::endl;
	ChibiDevTools::MemoryManager::instance().nextDisallocate(filename, line);
	ChibiDevTools::MemoryManager::instance().disallocate(ptr);
}

inline void operator delete[](void* ptr, const char* filename, int line) {
	ChibiDevTools::MemoryManager::instance().nextDisallocate(filename, line);
	ChibiDevTools::MemoryManager::instance().disallocate(ptr, true);
}

#endif // MEMMANAGERON_H

#ifndef new

#define new new(__FILE__, __LINE__)
#define delete ChibiDevTools::MemoryManager::instance().nextDisallocate(__FILE__, __LINE__), delete

#endif // new

#endif // __DEBUG
