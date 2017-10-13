//clang++ -std=c++03 localclass.cpp

#include <iostream>
#include <string>
#include <boost/function.hpp>
#include <boost/functional.hpp>
#include <boost/bind.hpp>


void fetchProperties(boost::function<void(const std::string&)> handlerFn)
{
	handlerFn("message from fetchProperties");
}

void doAnotherStuff(const std::string& aMessage)
{
	std::cout << __PRETTY_FUNCTION__ << " " << aMessage << std::endl;
}

void doMoreStuff(int& rCounter, const std::string& aMessage)
{
	std::cout << __PRETTY_FUNCTION__ << " " << aMessage << std::endl;	
	++rCounter;
}

// In C++03, cannot use struct ConfigManagerHandler defined inside 
// fn() because templates fail to instanciate. It works in C++11 but 
// in that case I would use a lambda.

struct ConfigManagerHandler
{
	explicit ConfigManagerHandler() : mCounter(0) {}

	void doStuff(const std::string& aMessage)
	{
		std::cout << __PRETTY_FUNCTION__ << " " << aMessage << std::endl;
		++mCounter;	
	}

	int mCounter;
};

// Another struct for "Config"...

void fn()
{
	fetchProperties(doAnotherStuff); // doAnotherStuff is just a function pointer

	ConfigManagerHandler configManager;

	boost::function<void (const std::string&)> handlerFn =
		boost::bind(&ConfigManagerHandler::doStuff, boost::ref(configManager), _1);

	fetchProperties(handlerFn);
	fetchProperties(handlerFn);

	std::cout << "configManager.counter = " << configManager.mCounter << std::endl;

	int counter = 5;

	boost::function<void (const std::string&)> moreStuffHandlerFn =
		boost::bind(doMoreStuff, boost::ref(counter), _1);

	fetchProperties(moreStuffHandlerFn);

	std::cout << "moreStuffHandlerFn.counter = " << counter << std::endl;
}

int main()
{
	fn();
	return 0;
}
