cmake_minimum_required(VERSION 3.2)

project(print_ip VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_library(print_ip print_ip.cpp)
add_executable(print_ip_gtest print_ip_gtest.cpp)

target_include_directories(print_ip
    PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
)

set_target_properties(print_ip print_ip_gtest PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(print_ip_gtest PROPERTIES
	INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(print_ip_gtest
	${GTEST_LIBRARIES} Threads::Threads
	print_ip
)

if (MSVC)
    target_compile_options(print_ip PRIVATE
        /W4
    )
    target_compile_options(print_ip_gtest PRIVATE
        /W4
    )
else ()
    target_compile_options(print_ip PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(print_ip_gtest PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

enable_testing()

add_test(print_ip_gtest print_ip_gtest)
