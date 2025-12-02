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
	cache::TimedCache<int, int > timedCache(30);
	// Create data

	shared_ptr<int>sPtr0( new int(12));
	std::cout << "Input: " << *sPtr0.get() << std::endl;
	cache::TimedCacheItem<int> item0(sPtr0);
	timedCache.add(1, item0);

	shared_ptr<int>sPtr1( new int(14));
	std::cout << "Input: " << *sPtr1.get() << std::endl;
	cache::TimedCacheItem<int> item1(sPtr1);
	timedCache.add(2, item1);

	// retrieve data
	cache::TimedCacheItem<int> val1 = timedCache.get(1);
	std::cout << *val1.get() << std::endl;
	cache::TimedCacheItem<int> val2 = timedCache.get(2);
	std::cout << *val2.get() << std::endl;

	// retrieve data
	cache::TimedCacheItem<int> valx = timedCache.get(1);
	std::cout << *valx.get() << std::endl;
	valx.refresh();
	shared_ptr<int>sPtrx( valx.get() );
	// exit
}

