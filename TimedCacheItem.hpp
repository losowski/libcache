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
		// Cache refresh
		void setTTL(std::chrono::duration<int> ttl)
			{
				mTTL = (std::chrono::duration<int>) ttl;
			}
	public:
		// get
		_Value * get(void)
			{
				return CacheItem<_Value>::get();
			}
		// Cache refresh
		void refresh(void)
			{
				// Expiry is now plus time
				mExpiry = std::chrono::steady_clock::now() + mTTL;
			}
		// Last Acccess
		std::chrono::time_point<std::chrono::steady_clock> getExpiry(void)
			{
				return mExpiry;
			}
	private:
		// Timed details
		std::chrono::duration<int>									mTTL;
		std::chrono::time_point<std::chrono::steady_clock>			mExpiry;
}; // class


} // namespace

#endif //TIMEDCACHEITEM_HPP
