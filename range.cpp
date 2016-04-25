
#include <iostream>
#include <initializer_list>

using namespace std;

typedef struct mytype_s
{
	string aaa;
	string bbb;
} mytype_t;

void test(initializer_list<mytype_t> il)
{
	for (const auto x : il)
	{
		cout << x.aaa << endl;
		cout << x.bbb << endl;
	}
}

int main()
{
	test({
		{ "aaa", "bbb" },
		{ "ccc", "ddd" }
	});
}

