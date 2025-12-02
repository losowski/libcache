#ifndef TIMEDCACHE_HPP
#define TIMEDCACHE_HPP


// Standard Library
#include <map>
#include <list>

// Required libraries
#include <chrono>
#include <ctime>
#include <algorithm>

/*
	URLS:
		https://cppreference.com/w/cpp/chrono.html#Calendar
		https://cppreference.com/w/cpp/chrono/system_clock/now.html
*/


// Item
#include "TimedCacheItem.hpp"


using namespace std;

namespace cache {

// Class to actually run the code
template<typename _Key, typename _Value>
class TimedCache
{
	// Types
	typedef TimedCacheItem<_Value>						_tValue;
	typedef map<_Key, _tValue>							_tMap;
	typedef typename _tMap::iterator					_tItMap;

	// Internal
	typedef list<_Key>									_tList;
	typedef typename _tList::iterator					_tItList;

	// Class functions
	public:
		TimedCache(const unsigned int expirySeconds = 600):
				mExpirySeconds(expirySeconds)
			{
			}
	public:
		~TimedCache(void)
			{
			}
	public:
		// Add
		void add(const _Key & key, _tValue value)
			{
				if (value)
				{
					mStorage.insert(std::pair{key, value});
				}
				// Set TTL for the value object to be a uniform time
				value.setTTL(mExpirySeconds);
			}
		// Remove
		void remove(const _Key & key)
			{
				_tItMap it = mStorage.find(key);
				if (it != mStorage.end())
				{
					mStorage.erase(key);
				}
				else
				{
					housekeeping();
				}
			}
		// Get the object
		_tValue get(const _Key & key)
			{
				_tItMap it = mStorage.find(key);
				if (it != mStorage.end())
				{
					_tValue value = mStorage.at(key);
					std::chrono::time_point<std::chrono::steady_clock> expiry = it->second.getExpiry();
					std::chrono::time_point<std::chrono::steady_clock> tNow = std::chrono::steady_clock::now();
					if (tNow < expiry)
					{
						return value;
					}
					else
					{
						housekeeping();
						return cNULL;
					}
				}
				else
				{
					return cNULL;
				}
			}
		// Get the object and refresh
		_tValue refreshGet(const _Key & key)
			{
				// Get the object
				_tValue value = get(key);
				// Perform the refresh
				refresh(value);
				// Return the object
				return value;
			}
	private:
		// Refresh the object
		void refresh(_tValue value)
			{
				if (value)
				{
					value.refresh();
				}
			}
		// Perform houseKeeping
		void housekeeping(void)
			{
				// Check Expiry
				std::chrono::time_point<std::chrono::steady_clock> dNow = std::chrono::steady_clock::now();
				if (dNow > mHousekeeping)
				{
					_tList removeList;
					for (_tItMap it = mStorage.begin(); it != mStorage.end(); it++)
					{
						std::chrono::time_point<std::chrono::steady_clock> expiry = it->second.getExpiry();
						if (dNow > expiry)
						{
							removeList.push_back(it->first);
						}
					}
					// Clear expiry list
					for (_tItList it = removeList.begin(); it != removeList.end(); it++)
					{
						remove(*it);
					}
					// Reset Housekeeping timeout
					mHousekeeping = dNow + mExpirySeconds;
				}
			}

	protected:
		// Return type
		_tValue								cNULL;
		// Object Storage
		_tMap								mStorage;
	private:
		// Timed details
		std::chrono::time_point<std::chrono::steady_clock>			mHousekeeping;
		// Timeout
		const std::chrono::duration<int>							mExpirySeconds;
}; // class

} // namespace

#endif //TIMEDCACHE_HPP
