#ifndef TIMEDCACHEITEM_HPP
#define TIMEDCACHEITEM_HPP

// Data
#include <memory>

// Required libraries
#include <chrono>
#include <ctime>
#include <algorithm>

// Base Class
#include "CacheItem.hpp"


using namespace std;

namespace cache {

template<typename _Value>
class TimedCacheItem : public CacheItem<_Value>
{
	// Class functions
	public:
		// Default
		TimedCacheItem(void)
			{
			}
		// With object
		TimedCacheItem(shared_ptr<_Value> ptr):
			CacheItem<_Value>::CacheItem(ptr)
			{
			}
	public:
		~TimedCacheItem(void)
			{
			}
	public:
		// get
		_Value * get(void)
			{
				return CacheItem<_Value>::get();
			}
		// Cache refresh
		void refresh(const std::chrono::duration<int> ttl)
			{
				// Expiry is now plus time
				mExpiry = std::chrono::steady_clock::now() + ttl;
			}
		// Last Acccess
		std::chrono::time_point<std::chrono::steady_clock> getExpiry(void)
			{
				return mExpiry;
			}
	private:
		// Timed details
		std::chrono::time_point<std::chrono::steady_clock>					mExpiry;
}; // class


} // namespace

#endif //TIMEDCACHEITEM_HPP
