//
// Tested with GCC 5.2.1, g++ -std=c++11
//

#include <future>
#include <chrono>
#include <ios>
#include <iostream>
#include <string>

using namespace std;

bool is_prime(int value)
{
	for (int i = 2; i < value; ++i)
		if (value%i == 0)
			return false;

	return true;
}

string future_status_str(future_status s)
{
	if (s == future_status::timeout)
		return "timeout";
	if (s == future_status::deferred)
		return "deferred";
	if (s == future_status::ready)
		return "ready";

	return "unknown";
}

int main()
{
	//
	// Need to use std::launch::async otherwise 
	// future_status::deferred is always returned
	//
	future<bool> f = async(std::launch::async, is_prime, 444444443);

#if 1
	future_status s;
	do
	{
		s = f.wait_for(chrono::milliseconds(200));
		cout << future_status_str(s) << endl;
	} while (s != future_status::ready);
#endif	

	cout << "number is prime: " << boolalpha << f.get() << endl;

	return 0;
}
