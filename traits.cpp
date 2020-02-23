#include <memory>
#include <iostream>

//#define TEST_TRAITS 1

class Parser;
class ConcreteParser1;
class ConcreteParser2;

template <typename P, typename D>
struct is_parser_compatible {
	static const bool value = false;
};

template <>
struct is_parser_compatible<ConcreteParser1, int*> {
	static const bool value = true;
};

template <>
struct is_parser_compatible<ConcreteParser2, double*> {
	static const bool value = true;
};

template <typename ParserType>
class ParserFactory
{
public:
	virtual ~ParserFactory() {}

	template <typename ParserData>
	std::shared_ptr<ParserType> makeParser(ParserData* d)
	{
		static_assert(is_parser_compatible<ParserType,ParserData*>::value, 
			"ParserData* d is incompatible with ParserType");

		std::cout << __PRETTY_FUNCTION__ << "\n";
		return std::make_shared<ParserType>(d);
	}
};

class Parser
{
public:
	virtual ~Parser() {}
	virtual bool parse() = 0;
};

class ConcreteParser1 : public Parser
{
public:
	int* _d = nullptr;

	ConcreteParser1(int* d) : _d(d)
	{}

	bool parse() override { 
		*_d = 10;
		std::cout << __PRETTY_FUNCTION__ << "\n"; 
		return true; 
	}
};

class ConcreteParser2 : public Parser
{
public:
	double* _d = nullptr;

	ConcreteParser2(double* d) : _d(d)
	{}

	bool parse() override {
	       	*_d = 20.2;	
		std::cout << __PRETTY_FUNCTION__ << "\n"; 
		return true; 
	}
};

void parse1(ParserFactory<ConcreteParser1>* f)
{
	int d = 5;
	auto p1 = f->makeParser(&d);
	p1->parse();

	std::cout << d << "\n";

#ifdef TEST_TRAITS
	double d = 7.7;
	auto p2 = f->makeParser(&d);
	p2->parse();
#endif

}

void parse2(ParserFactory<ConcreteParser2>* f)
{
	double d = 7.7;
	auto p2 = f->makeParser(&d);
	p2->parse();

	std::cout << d << "\n";

#ifdef TEST_TRAITS
	int d = 5;
	auto p1 = f->makeParser(&d);
	p1->parse();
#endif
}

int main()
{
	auto f1(std::make_shared<ParserFactory<ConcreteParser1>>());
	parse1(f1.get());
	
	auto f2(std::make_shared<ParserFactory<ConcreteParser2>>());
	parse2(f2.get());

	return 0;
}


