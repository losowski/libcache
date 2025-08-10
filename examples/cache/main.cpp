/*
	Sample Cache
*/

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <string>


// Actual libraries
#include "../../CacheItem.hpp"
#include "../../Cache.hpp"


using namespace std;
using namespace cache;


int main (int argc, char * argv[])
{
	// Start application
	std::cout << "Cache" << std::endl;
	// Create the Cache
	cache::Cache<int, cache::CacheItem<int> > basicCache(2);
	// Create data
	shared_ptr<int>sPtr( new int(12));
	cache::CacheItem<int> item0(sPtr);
	cache::CacheItem<int> item1;
	// Store data
	basicCache.add(1, item0);
	basicCache.add(2, item1);
	// retrieve data
	cache::CacheItem<int> & val = basicCache.get(1);
	shared_ptr<int>sPtr1( val.get() );
	// exit
}
