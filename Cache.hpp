#ifndef CACHEBASE_HPP
#define CACHEBASE_HPP

// Standard Library
#include <map>
#include <memory>

// Cache item
#include "CacheItem.hpp"

using namespace std;

namespace cache {

// Class to actually run the code
template<typename _Key, typename _Value>
class Cache
{
	// Types
	typedef CacheItem<_Value>						_tValue;
	typedef map<_Key, _tValue>						_tMap;
	typedef typename _tMap::iterator				_tItMap;

	// Class functions
	public:
		Cache(const unsigned int objectLimit = 1000):
			mObjectLimit(objectLimit)
			{
			}
	public:
		~Cache(void)
			{
			}
	public:
		// Add
		void add(const _Key & key, const _tValue & value)
			{
				if (mStorage.size() < mObjectLimit)
				{
					if (value)
					{
						mStorage.insert(std::pair{key, value});
					}
				}
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
		// Get
		_tValue get(const _Key & key)
			{
				_tItMap it = mStorage.find(key);
				if (it != mStorage.end())
				{
					return mStorage.at(key);
				}
				else
				{
					housekeeping();
					return cNULL;
				}
			}
		// Housekeeping
		void housekeeping(void)
			{
				for (_tItMap it = mStorage.begin(); it != mStorage.end(); it++)
				{
					// TODO: Algorithm to perform housekeeping
				}
			}
	protected:
		// Return type
		_tValue								cNULL;
		// Object Storage
		_tMap								mStorage;
	private:
		// Object Limit
		const unsigned int					mObjectLimit;
}; // class

} // namespace

#endif //CACHEBASE_HPP
