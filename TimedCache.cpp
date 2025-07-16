#include "TimedCache.hpp"

// Required libraries
#include <chrono>
#include <ctime>
#include <algorithm>

/*
	URLS:
		https://cppreference.com/w/cpp/chrono.html#Calendar
		https://cppreference.com/w/cpp/chrono/system_clock/now.html
*/


namespace cache {
// Logging
log4cxx::LoggerPtr TimedCache::mLogger = log4cxx::Logger::getLogger("cache.TimedCache");

// Functions
TimedCache::TimedCache(unsigned int expirySeconds):
	mExpirySeconds(expirySeconds)
{
}



TimedCache::~TimedCache(void)
{
}

// Add
void TimedCache::add(tKey & key, tValue & value)
{
	const std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
	this->mStorage.insert(std::pair{key, value});
	
}


// Remove
void TimedCache::remove(tKey & key)
{
	this->mStorage.erase(key);
}


// Housekeeping
void TimedCache::housekeeping(void)
{
}

} // namespace
