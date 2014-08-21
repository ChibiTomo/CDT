#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <stack>

#include "FileLogger.h"
#include "File.h"
#include "Map.h"
#include "Exceptions.h"

namespace cdt {
	struct BadDeleteException : public Exception {
		BadDeleteException(File file, int line, void* ptr, bool isArray);
	};

	class MemoryManager {
		public:
			void* allocate(std::size_t size, const char* filename, int line, bool isArray = false);

			void nextDisallocate(const char* filename, int line);
			void disallocate(void* ptr, bool isArray = false);

			static MemoryManager& instance();

		protected:
			MemoryManager();
			virtual ~MemoryManager();

		private:
			static MemoryManager __memManager;
			void _report();

			typedef struct {
				std::size_t size;
				File file;
				int line;
				bool isArray;
			} block_t;
			typedef Map<void*, block_t> blockMap_t;

			blockMap_t m_blocks;
			std::stack<block_t> m_deleteStack;
			FileLogger m_logger;
	};
}

#endif // MEMORYMANAGER_H
