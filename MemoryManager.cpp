#include <cstdlib>

#include "MemManagerOff.h"
#include "MemoryManager.h"

namespace cdt {
	MemoryManager MemoryManager::__memManager;

	BadDeleteException::BadDeleteException(File file, int line, void* ptr, bool isArray) :
		Exception(file, line) {
			std::stringstream ss;
			ss << "Wrong disallocation: " << ((isArray)? "new / delete[]" : "new[] / delete");
			m_msg = ss.str();
		}

	MemoryManager::MemoryManager() : m_logger("memory_leaks.log", "Memory leak tracker", true) {}
	MemoryManager::~MemoryManager() {
		m_logger << std::endl << "##############################" << std::endl;

		if (!m_blocks.isEmpty()) {
			m_logger << "Oops... Memory leaks detected..." << std::endl << std::endl;
			_report();
		} else {
			m_logger << "No memory leaks!" << std::endl << std::endl;
		}
	}

	MemoryManager& MemoryManager::instance() {
		return __memManager;
	}

	void MemoryManager::_report() {
		std::size_t totalSize = 0;

		for (blockMap_t::iterator i = m_blocks.begin(); i != m_blocks.end(); i++) {
			void *ptr = i->first;
			block_t block = i->second;

			totalSize += block.size;

			m_logger 	<< "--> address: 0x" << ptr << std::endl
						<< "  | size:    " << block.size << " bytes" << std::endl
						<< "  | file:    " << block.file.basename() << "(" << block.line << ")" << std::endl
						<< std::endl;
			free(ptr);
		}

		m_logger	<< "**Total leaks: " << std::endl
					<< "  | pointer amount: " << m_blocks.size() << std::endl
					<< "  | size:           " << totalSize << " bytes" << std::endl
					<< std::endl;
	}

	void* MemoryManager::allocate(std::size_t size, const char* filename, int line, bool isArray) {
		void *ptr = malloc(size);

		block_t new_block;
		new_block.size = size;
		new_block.file = File(filename);
		new_block.line = line;
		new_block.isArray = isArray;
		m_blocks.put(ptr, new_block);

		m_logger 	<< "++Allocation:" << std::endl
					<< "  | address: 0x" << ptr << std::endl
					<< "  | size:    " << new_block.size << " bytes" << std::endl
					<< "  | file:    " << new_block.file.basename() << "(" << new_block.line << ")" << std::endl
					<< std::endl;

		return ptr;
	}

	void MemoryManager::nextDisallocate(const char* filename, int line) {
		block_t deleteBlock;
		deleteBlock.file = File(filename);
		deleteBlock.line = line;

		m_deleteStack.push(deleteBlock);
	}

	void MemoryManager::disallocate(void* ptr, bool isArray) {
		blockMap_t::iterator it = m_blocks.find(ptr);

		if (it == m_blocks.end()) {
			free(ptr);
			return;
		}

		block_t block = it->second;

		if (block.isArray != isArray) {
			throw BadDeleteException(block.file, block.line, ptr, isArray);
		}

		block_t topBlock;
		if (!m_deleteStack.empty()) {
			topBlock = m_deleteStack.top();
			m_deleteStack.pop();
		}

		m_logger	<< "--Disallocation" << std::endl
					<< "  | address: 0x" << ptr << std::endl
					<< "  | size:    " << block.size << " bytes" << std::endl
					<< "  | file:    " << topBlock.file.basename()
									   << "(" << topBlock.line << ")" << std::endl
					<< std::endl;
		m_blocks.erase(it);

		free(ptr);
	}
}
