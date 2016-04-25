#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#define COLUMN_TAG "tag"

#define DB_JSON_PATH(column, path) \
	std::string(column) 			\
		.append("#>>'")				\
		.append(path) 				\
		.append("'")

#define DB_JSON(column, json_field) \
	std::string(column) 			\
		.append("->>'")  			\
		.append(json_field) 		\
		.append("'")

#define DB_JSON_IN(json_field,json_value) \
	std::string(" (") 				\
		.append(json_field) 		\
		.append(")::jsonb @> (") 	\
		.append(json_value) 		\
		.append(")::jsonb ")

int main()
{
	cout << 
	DB_JSON_IN(DB_JSON(COLUMN_TAG, "tags"), "[{\"value\":\"ccc\"}]")
	<< endl;

	cout <<
	DB_JSON_PATH(COLUMN_TAG,"{tags,0,value}")
	<< endl;

	return 0;
}
