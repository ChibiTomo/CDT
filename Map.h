#ifndef MAP_H
#define MAP_H

#include <sstream>
#include <map>

#include "Exceptions.h"
#include "File.h"

#define THROW_UNKNOWN_KEY_EXCEPTION(key) \
	throw ChibiDevTools::UnknownKeyException(ChibiDevTools::File(__FILE__), __LINE__, #key);

namespace ChibiDevTools {

	struct UnknownKeyException : public Exception {
		UnknownKeyException(File file, int line, const std::string& key);
	};

	template <typename Key, typename Value, class Comparator = std::less<Key> >
	class Map : public std::map<Key, Value, Comparator> {
		public:
			Map() {};
			virtual ~Map() {};

			void put(const Key& key, const Value& value) {
				this->insert(keyValuePair(key, value));
			}

			bool contains(const Key& key) {
				return this->find(key) != this->end();
			}

			Value& get(const Key& key) {
				if (!this->contains(key)) {
					THROW_UNKNOWN_KEY_EXCEPTION(key);
				}
				return this->find(key)->second;
			}

			void empty() {
				this->erase(this->begin(), this->end());
			}

			bool isEmpty() {
				return this->begin() == this->end();
			}

		private:
			typedef std::pair<Key, Value> keyValuePair;
	};

}

#endif // MAP_H
