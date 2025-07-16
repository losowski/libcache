#ifndef CACHEBASE_HPP
#define CACHEBASE_HPP

// Container
#include <map>

// include log4cxx header files.
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>

using namespace std;

namespace cache {

// Class to actually run the code
 template<typename tKey, typename tValue> class CacheBase
{
	public:
		CacheBase(void);
	public:
		~CacheBase(void);
	public:
		// Add
		virtual void add(tKey & key, tValue & value) = 0;
		// Remove
		virtual void remove(tKey & key) = 0;
		// Get
		tValue & get(tKey & key);
	protected:
		// Housekeeping
		virtual void housekeeping(void) = 0;
		// Add
		void _add(tKey & key, tValue & value);
		// Remove
		void _remove(tKey & key);
	protected:
		// Object Storage
		map<tKey, tValue>						mStorage;
	private:
		static log4cxx::LoggerPtr				mLogger;
}; // class

} // namespace

#endif //CACHEBASE_HPP
