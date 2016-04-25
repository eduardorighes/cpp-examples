#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
  string s = R"###(
select logmessage.*
)###";

  stringstream ss;

  ss << s;
  
  s = R"(from logmessage where messageid))))%%%%%))";

  ss << s;
  
  cout << ss.str() << endl;
  
  return 0;
}
