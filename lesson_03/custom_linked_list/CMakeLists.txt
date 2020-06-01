cmake_minimum_required(VERSION 3.2)

project(custom_linked_list VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

configure_file(version.h.in version.h)

add_library(custom_linked_list custom_linked_list.cpp)
add_executable(custom_linked_list_gtest custom_linked_list_gtest.cpp)

target_include_directories(custom_linked_list
    PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
)

set_target_properties(custom_linked_list custom_linked_list_gtest PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(custom_linked_list_gtest PROPERTIES
	INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(custom_linked_list_gtest
	${GTEST_LIBRARIES} Threads::Threads
	custom_linked_list
)

if (MSVC)
    target_compile_options(custom_linked_list PRIVATE
        /W4
    )
    target_compile_options(custom_linked_list_gtest PRIVATE
        /W4
    )
else ()
    target_compile_options(custom_linked_list PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(custom_linked_list_gtest PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

enable_testing()

add_test(custom_linked_list_gtest custom_linked_list_gtest)
