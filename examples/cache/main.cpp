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
	cache::Cache<int, int> basicCache(2);
	// Create data
	
	shared_ptr<int>sPtr0( new int(12));
	std::cout << "Input: " << *sPtr0.get() << std::endl;
	cache::CacheItem<int> item0(sPtr0);
	basicCache.add(1, item0);

	shared_ptr<int>sPtr1( new int(14));
	std::cout << "Input: " << *sPtr1.get() << std::endl;
	cache::CacheItem<int> item1(sPtr1);
	basicCache.add(2, item1);

	// retrieve data
	cache::CacheItem<int> val1 = basicCache.get(1);
	std::cout << *val1.get() << std::endl;
	cache::CacheItem<int> val2 = basicCache.get(2);
	std::cout << *val2.get() << std::endl;
	// exit
}
