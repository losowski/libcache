#ifndef CACHEITEM_HPP
#define CACHEITEM_HPP

// Standard Library
#include <memory>


// Required libraries
#include <chrono>
#include <ctime>
#include <algorithm>


using namespace std;

namespace cache {

template<typename _Value>
class CacheItem : public shared_ptr<_Value>
{
	// Class functions
	public:
		// Default
		CacheItem(void)
			{
			}
		// With object
		CacheItem(shared_ptr<_Value> ptr):
			shared_ptr<_Value>::shared_ptr(ptr)
		{
			// Last Access is now
			mLastAccess =  std::chrono::steady_clock::now();
		}
	public:
		~CacheItem(void)
			{
			}
	public:
		// get
		_Value * get(void)
			{
				mLastAccess = std::chrono::steady_clock::now();
				return shared_ptr<_Value>::get();
			}
		// Last Acccess
		std::chrono::time_point<std::chrono::steady_clock> getLastAccess(void)
			{
				return mLastAccess;
			}
	private:
		// Timed details
		std::chrono::time_point<std::chrono::steady_clock>					mLastAccess;
}; // class


} // namespace

#endif //CACHEITEM_HPP
