cmake_minimum_required(VERSION 3.2)

project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

configure_file(version.h.in version.h)

add_library(ip_filter ip_filter.cpp)
add_executable(ip_filter_gtest ip_filter_gtest.cpp)

set_target_properties(ip_filter ip_filter_gtest PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_filter
    PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
)

set_target_properties(ip_filter_gtest PROPERTIES
	INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(ip_filter_gtest
	${GTEST_LIBRARIES} Threads::Threads
	ip_filter
)

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(ip_filter_gtest PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ip_filter_gtest PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

enable_testing()

add_test(ip_filter_gtest ip_filter_gtest)
