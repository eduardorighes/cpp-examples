#include <iostream>
#include <functional>

using namespace std;

class DatabaseConnWrapperC
{
public:

	using ConnectFnType = function<bool(bool*,char**,char*)>;
	using DisconnectFnType = function<void(char*, bool)>;

private:
		
	char* mpstrConn;
	bool  mbRelease;

	ConnectFnType    mpfnConnect;
	DisconnectFnType mpfnDisconnect;

public:

	DatabaseConnWrapperC
	(
		ConnectFnType    connect,
		DisconnectFnType disconnect
	):
		mpfnConnect(connect),
		mpfnDisconnect(disconnect),
		mpstrConn(nullptr),
		mbRelease(nullptr)
	{	
		mpfnConnect(&mbRelease, &mpstrConn, nullptr);	
	}

	DatabaseConnWrapperC(const DatabaseConnWrapperC&) = delete;
	DatabaseConnWrapperC& operator=(const DatabaseConnWrapperC&) = delete;

	DatabaseConnWrapperC(const DatabaseConnWrapperC&&) = delete;
	DatabaseConnWrapperC& operator=(const DatabaseConnWrapperC&&) = delete;

	~DatabaseConnWrapperC()
	{
		if (mpstrConn)
		{
			mpfnDisconnect(mpstrConn, mbRelease);
		}
	}

	const char* GetConn() const
	{
		return mpstrConn;
	}
};

bool ConnectFn(bool* pbRelease, char** ppstrConn, char* pstrPrior)
{
	*pbRelease = true;
	*ppstrConn = new char[5];	
}

void DisconnectFn(char* pstrConn, bool bRelease)
{
	if (pstrConn)
	{
		delete[] pstrConn;	
	}
}

int main()
{
	DatabaseConnWrapperC wrapper(ConnectFn, DisconnectFn);
	wrapper.GetConn();

	string s(nullptr);
	return 0;
}
