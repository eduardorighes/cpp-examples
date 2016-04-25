

#include <iostream>


#if defined(__cplusplus)

#define M(x) \
do { std::cout << x << std::endl; } while(false)

#else

#define M(x) do { } while(false);

#endif

int main()
{
	M("blah");
	return 0;
}