#ifndef REFRESHCACHE_HPP
#define REFRESHCACHE_HPP

// Base Class
#include <TimedCache.hpp>

// include log4cxx header files.
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>

using namespace std;

namespace cache {

// Class to actually run the code
class template<tKey, tValue>RefreshCache: public TimedCache
{
	public:
		RefreshCache(unsigned int expirySeconds, unsigned int refreshForSeconds);
	public:
		~RefreshCache(void);
	public:
		// Add
		void add(tKey & key, tValue & value);
		// Remove
		void remove(tKey & key);
	protected:
		void housekeeping(void);
	protected:
		// Refresh Interval
		unsigned int							mRefreshForSeconds;
	private:
		static log4cxx::LoggerPtr				mLogger;
}; // class

} // namespace

#endif //REFRESHCACHE_HPP
