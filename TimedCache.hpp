#ifndef TIMEDCACHE_HPP
#define TIMEDCACHE_HPP


// Container
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


// Base Class
#include "Cache.hpp"

using namespace std;

namespace cache {

// Class to actually run the code
template<typename _Key, typename _Value>
class TimedCache: public Cache<_Key, _Value>
{
	// Types
	typedef map<_Key, _Value>					_tMap;
	typedef typename _tMap::iterator			_tItMap;

	typedef list<_Key>							_tList;
	typedef typename _tList::iterator			_tItList;

	// Class functions
	public:
		TimedCache(const unsigned int objectLimit = 1000, const unsigned int expirySeconds = 600):
				Cache<_Key, _Value>::Cache(objectLimit),
				mExpirySeconds(expirySeconds)
			{
			}
	public:
		~TimedCache(void);
	public:
		// Add
		void add(const _Key & key, const _Value & value)
			{
				Cache<_Value, _Value>::add(key, value);
			}
		// Remove
		void remove(const _Key & key)
			{
				Cache<_Value, _Value>::remove(key);
			}
		// Get the object
		_Value & get(const _Key & key)
			{
				_tItMap it = Cache<_Value, _Value>::mStorage.find(key);
				if (it != Cache<_Value, _Value>::mStorage.end())
				{
					_Value & value = Cache<_Value, _Value>::mStorage.at(key);
					std::chrono::time_point<std::chrono::steady_clock> expiry = it->second.getExpiry();
					std::chrono::time_point<std::chrono::steady_clock> tNow = std::chrono::steady_clock::now();
					if (tNow < expiry)
					{
						return value;
					}
					else
					{
						housekeeping();
						return Cache<_Value, _Value>::cNULL;
					}
				}
				else
				{
					return Cache<_Value, _Value>::cNULL;
				}
			}
		// Get the object and refresh
		_Value & refreshGget(const _Key & key)
			{
				// Get the object
				_Value & value = get(key);
				// Perform the refresh
				refresh(value);
				// Return the object
				return value;
			}

		// Perform houseKeeping
		void housekeeping(void)
			{
				// Check Expiry
				std::chrono::time_point<std::chrono::steady_clock> dNow = std::chrono::steady_clock::now();
				if (dNow > mHousekeeping)
				{
					_tList removeList;
					for (_tItMap it = Cache<_Value, _Value>::mStorage.begin(); it != Cache<_Value, _Value>::mStorage.end(); it++)
					{
						std::chrono::time_point<std::chrono::steady_clock> expiry = it->second.getExpiry();
						if (dNow > expiry)
						{
							removeList.push(it->first);
						}
					}
					// Clear expiry list
					for (_tItList it = removeList.begin(); it < removeList.end(); it++)
					{
						remove(*it);
					}
					// Reset Housekeeping timeout
					mHousekeeping = dNow + mExpirySeconds;
				}
			}
	private:
		// Refresh the object
		void refresh(_Value * value)
			{
				if (value)
				{
					value->refresh(mExpirySeconds);
				}
			}
	private:
		// Timed details
		std::chrono::time_point<std::chrono::steady_clock>			mHousekeeping;
		// Timeout
		const std::chrono::duration<int>							mExpirySeconds;
}; // class

} // namespace

#endif //TIMEDCACHE_HPP
