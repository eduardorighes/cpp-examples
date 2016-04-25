
#include <iostream>

using namespace std;

typedef struct
{
	long a;
	long b;
} TestT;

void test
(
	TestT*  a,
	size_t  size
)
{	
	TestT* ptCurrent = a;
	for (size_t i = 0; i < size; ++i)
	{
		cout << ptCurrent->a << endl;
		cout << ptCurrent->b << endl;
		++ptCurrent;
	}
}

int main()
{
	TestT a {1, 2};
	TestT b {3, 4};

	TestT aa[] { a, b };

	test((TestT*)&aa, 2);
}
