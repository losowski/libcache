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
	shared_ptr<int>sPtr( new int(12));
	cache::CacheItem<int> item0(sPtr);
	cache::CacheItem<int> item1;
	cache::Cache<int, cache::CacheItem<int> > basicCache(2);
	basicCache.add(1, item0);
	basicCache.add(1, item1);
	// exit
}

