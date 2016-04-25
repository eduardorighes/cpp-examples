
#include <stdio.h>

typedef struct
{
	long a;
	long b;
} TestT;

void test
(
	TestT (*a)[], // array of unknown bound error in C++11
	size_t size
)
{
	for (size_t i = 0; i < size; ++i)
	{
		printf("a=%ld, b=%ld\n", (*a)[i].a, (*a)[i].b);
	}
}

void test_pointers
(
	TestT* a,
	size_t size
)
{
	TestT* current = a;

	for (size_t i = 0; i < size; ++i)
	{
		printf("a=%ld, b=%ld\n", current->a, current->b);
		++current;
	}
}


int main()
{
	TestT a = {1, 2};
	TestT b = {3, 4};

	TestT aa[] = { a, b };

	test((TestT*)&aa, 2);
	test_pointers((TestT*)&aa, 2);
}

