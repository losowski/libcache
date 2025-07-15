#include "CacheBase.hpp"

namespace eventapi {
// Logging
log4cxx::LoggerPtr CacheBase::mLogger = log4cxx::Logger::getLogger("cache.CacheBase");

// Functions
CacheBase::CacheBase(void)
{
}



CacheBase::~CacheBase(void)
{
}

// Get
tValue &CacheBase::get(tKey & key)
{
	return this->mStorage.at(key);
}

// Add
void CacheBase::_add(tKey & key, tValue & value)
{
	this->mStorage.insert(std::pair{key, value});
}


// Remove
void CacheBase::_remove(tKey & key)
{
	this->mStorage.erase(key);
}




} // namespace
