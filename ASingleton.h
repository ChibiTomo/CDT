#ifndef ASINGLETON_H
#define ASINGLETON_H

#include <cstdio>

#include "MemManagerOn.h"

#define SINGLETON(class) friend class ASingleton<class>

namespace cdt {

	template<class T>
	class ASingleton {
		public:
			static T& instance();
			static void destroy();

		protected:
			ASingleton() {};
			virtual ~ASingleton() {};

		private:
			static T* m_instance;

			ASingleton(ASingleton&);
			void operator= (ASingleton&);
	};

	template<class T> T* ASingleton<T>::m_instance = NULL;

	/**
	 * Return the current instance or a new instance with the empty constructor
	**/
	template<class T>
	T& ASingleton<T>::instance() {
		if (!m_instance) {
			m_instance = new T();
		}
		return *m_instance;
	}

	/**
	 * Destroy the current instance
	**/
	template<class T>
	void ASingleton<T>::destroy() {
		delete m_instance;
		m_instance = NULL;
	}
}

#include "MemManagerOff.h"

#endif // ASINGLETON_H
