#ifndef TIMEDCACHE_HPP
#define TIMEDCACHE_HPP

// Base Class
#include <CacheBase.hpp>

// include log4cxx header files.
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>

using namespace std;

namespace cache {

// Class to actually run the code
class template<tKey, tValue>TimedCache: public CacheBase
{
	public:
		TimedCache(unsigned int expirySeconds);
	public:
		~TimedCache(void);
	public:
		// Add
		void add(tKey & key, tValue & value);
		// Remove
		void remove(tKey & key);
	protected:
		void housekeeping(void);
	protected:
		// Timeout
		unsigned int							mExpirySeconds;
		map<tKey, unsigned int>					mExpiry;
	private:
		static log4cxx::LoggerPtr				mLogger;
}; // class

} // namespace

#endif //TIMEDCACHE_HPP
