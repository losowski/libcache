/*
	Timed Cache
*/

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <string>


// Actual libraries
#include "../../TimedCacheItem.hpp"
#include "../../TimedCache.hpp"


using namespace std;
using namespace cache;


int main (int argc, char * argv[])
{
	// Start application
	std::cout << "Cache" << std::endl;
	// Create the Timed Cache
	cache::TimedCache<int, cache::TimedCacheItem<int> > timedCache(1000, 30);
	// Create data
	shared_ptr<int>sPtr( new int(12));
	cache::TimedCacheItem<int> cItem0(sPtr);
	cache::TimedCacheItem<int> cItem1;
	// Store data
	timedCache.add(1, cItem0);
	timedCache.add(2, cItem1);
	// retrieve data
	cache::TimedCacheItem<int> & val = timedCache.get(1);
	shared_ptr<int>sPtr1( val.get() );
	// exit
}

