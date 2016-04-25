#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <cstdio>
#include <cstdarg>

using namespace std;

class LogTagItem
{
public:
	string value;
	string display;
	long order;

	LogTagItem(const string& v, const string& d, const long o):
		value(v), display(d), order(o)
	{ }

LogTagItem(const string& v, const string& d):
		LogTagItem(v, d, 0)
	{ }

LogTagItem(const string& v):
		LogTagItem(v, "", 0)
	{ }

	LogTagItem(): 
		LogTagItem("", "", 0)
	{ }

	LogTagItem& SetValue(const string& v)
	{
		value = v;
		return *this;
	}

	string ToString() const;
};

string LogTagItem::ToString() const
{
	stringstream ss;

	ss 
		<< "{" 
		<< "\"value\":\""   << value << "\"," 
		<< "\"display\":\"" << display << "\"," 
		<< "\"order\":\""   << order << "\"" 
		<< "}";

	return ss.str();
}

void format_string(const string& format, ...)
{
	va_list args;
	va_start(args, format);
	vprintf(format.c_str(), args);
	va_end(args);
}

int main()
{
	vector<LogTagItem> logTagItems
	{
		{"value1", "display1", 1},
		{"value2", "display2", 2},
		{"value3"},
		{"value4", "display4"}
	};

	for (const auto& item : logTagItems)
	{
		cout << item.ToString() << endl;
	}

	cout << LogTagItem().SetValue("my-nice-value").ToString() << endl;

	string s = "my nice format %d %x %s\n";
	format_string(s, 10, 16, "some-string");

	return 0;
}

