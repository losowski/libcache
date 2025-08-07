#ifndef CACHEBASE_HPP
#define CACHEBASE_HPP

// Container
#include <map>
#include <memory>


using namespace std;

namespace cache {

// Class to actually run the code
template<typename _Key, typename _Value>
class Cache
{
	// Types
	typedef typename map<_Key, _Value>::iterator		_tItMap;

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
		void add(const _Key & key, const _Value & value)
			{
				if (mStorage.size() < mObjectLimit)
				{
					mStorage.insert(std::pair{key, value});
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
		_Value & get(const _Key & key)
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
				for (_tItMap it = mStorage.begin(); it < mStorage.end(); it++)
				{
					// TODO: Algorithm to perform housekeeping
				}
			}
	protected:
		// Object Limit
		unsigned int						mObjectLimit;
		// Object Storage
		std::map<_Key, _Value>				mStorage;
		// Return type
		static shared_ptr<_Value>			cNULL;
}; // class

} // namespace

#endif //CACHEBASE_HPP
