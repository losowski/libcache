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
	shared_ptr<int>sPtr( new int(12));
	cache::TimedCacheItem<int> cItem0(sPtr);
	cache::TimedCacheItem<int> cItem1;
	cache::TimedCache<int, cache::TimedCacheItem<int> > timedCache(1000, 30);
	timedCache.add(1, item0);
	timedCache.add(1, item1);
	// exit
}

