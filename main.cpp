/*
	EventAPI main executable
*/

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <string>

// include log4cxx header files.
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>

// Actual libraries
//#include "EventAPIService.hpp"


using namespace std;
using namespace eventapi;

/*
	Log4cxx configuration
	https://svn.apache.org/repos/asf/incubator/log4cxx/tags/v0_9_7/xdocs/www/manual/Introduction.html
	https://svn.apache.org/repos/asf/incubator/log4cxx/tags/v0_9_7/xdocs/www/manual/classlog4cxx_1_1PropertyConfigurator.html
*/
// Logger instance
log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger("dbserver");


volatile sig_atomic_t signalStatus = 0;

zmq::context_t zContext(1);

// /usr/includex/86_64-linux-gnu/asm/signal.h
static void sigHandler_term(int signalNumber)
{
	std::cout << "Received Signal: " << signalNumber << std::endl;
	signalStatus  = signalNumber;
	// Close context
	zContext.close();
}

int main (int argc, char * argv[])
{
	// Start application
	std::cout << "EventAPI" << std::endl;
	// Initialise the log4cxx config
	log4cxx::BasicConfigurator::configure();
	// Setup the Signal Catcher (SIGTERM)
	LOG4CXX_DEBUG(logger, "Starting Server");
	// Handle Comamnd line parameters
	// argv[0] = Program name
	// argv[1] = argument 1
	if (argc > 1)
	{
		//dbURI = argv[1];
		LOG4CXX_DEBUG(logger, "Args: " << argv[1]);
	}
	// Create the service
	EventAPIService api (zContext, "tcp://*:5580", "tcp://*:5582");
	// Initialise
	api.initialise();
	// Install a signal handler
	LOG4CXX_DEBUG(logger, "Setup of singal handler");
	std::signal(SIGTERM, sigHandler_term);
	std::signal(SIGKILL, sigHandler_term);
	std::signal(SIGQUIT, sigHandler_term);
	// Start the server
	LOG4CXX_DEBUG(logger, "Starting server");
	api.start();
	// process
	api.process();
	LOG4CXX_DEBUG(logger, "Received Signal");
	// Passed signal catcher
	if (signalStatus == SIGTERM)
		std::cout << "Received SIGTERM" << std::endl;
	else if (signalStatus == SIGKILL)
		std::cout << "Received SIGKILL" << std::endl;
	else if (signalStatus == SIGQUIT)
		std::cout << "Received SIGQUIT" << std::endl;
	// Shutdown the server
	api.shutdown();
	// exit
}

