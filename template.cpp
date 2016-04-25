
#include <memory>

using namespace std;

template<typename Type> class Base
{
public:
	Base(Type* m):
		mpMem(m)
	{}
protected:
	shared_ptr<Type> mpMem;
};

class Derived : public Base<char>
{
public:
	Derived(char* m): 
		Base(m)
	{}
};

int main()
{
	Derived d(new char[10]);
	return 0;
}