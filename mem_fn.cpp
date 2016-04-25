#include <iostream>
#include <string>
#include <functional>

using namespace std;

using namespace std::placeholders;

class Test
{
public:
	Test()
	{ cout << __PRETTY_FUNCTION__ << endl; }
	void method()
	{ cout << __PRETTY_FUNCTION__ << endl; }
	void method(int)
	{ cout << __PRETTY_FUNCTION__ << endl; }
	void method(const std::string&)
	{ cout << __PRETTY_FUNCTION__ << endl; }
};

int main()
{
	Test p;
	auto plgmethod1 = std::mem_fn<void()>(&Test::method);
	auto plgmethod2 = std::mem_fn<void(int)>(&Test::method);
	auto plgmethod3 = std::mem_fn<void(const string&)>(&Test::method);

	auto plgmethod4 = std::bind(plgmethod3, p, "bleh");

	auto fn = [](const string&) {
		cout << "lambda: " << __PRETTY_FUNCTION__ << endl;
	};

	auto plgmethod5 = std::bind(fn, "bloh");
	auto plgmethod6 = std::bind(fn, _1);

	plgmethod1(p);
	plgmethod2(p, 10);
	plgmethod3(p, "blah");

	plgmethod4();
	plgmethod5();
	plgmethod6("bluh");

	return 0;
}
