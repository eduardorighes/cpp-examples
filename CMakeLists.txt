project ( CppExamples )

cmake_minimum_required( VERSION 3.13 )

add_executable ( auto auto.cpp )
add_executable ( cplusplus cplusplus.cpp )
add_executable ( fn fn.cpp )
add_executable ( future future.cpp )
add_executable ( iterators iterators.cpp )
add_executable ( mem_fn mem_fn.cpp )
add_executable ( pointers pointers.cpp )
add_executable ( range range.cpp )
add_executable ( rawstring rawstring.cpp )
add_executable ( ss ss.cpp )
add_executable ( tags tags.cpp )
add_executable ( template template.cpp )
add_executable ( readfile readfile.cpp )
add_executable ( traits traits.cpp )

add_definitions ( -O3 -std=c++11 )

target_link_libraries( future pthread )

install(
	TARGETS 
	auto 
	cplusplus 
	fn 
	future 
	iterators 
	mem_fn 
	pointers 
	range
	rawstring
	ss
	tags
	template
	readfile
	
	DESTINATION 
	bin
)

set_source_files_properties(TAGS PROPERTIES GENERATED true)
add_custom_target(TAGS
    COMMAND ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
find_program(CTAGS_PATH ctags)
if(CTAGS_PATH)
    message(STATUS "Found ctags: ${CTAGS_PATH}")
    add_dependencies(auto TAGS)
endif(CTAGS_PATH)

