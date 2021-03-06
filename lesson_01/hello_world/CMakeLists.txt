cmake_minimum_required(VERSION 3.2)

project(hello_world VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

configure_file(version.h.in version.h)

add_library(hello_world hello_world.cpp)
add_executable(hello_world_ut hello_world_ut.cpp)
add_executable(hello_world_gtest hello_world_gtest.cpp)

set_target_properties(hello_world hello_world_ut hello_world_gtest PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(hello_world
    PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
)

set_target_properties(hello_world_ut PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(hello_world_ut
    ${Boost_LIBRARIES}
    hello_world
)

set_target_properties(hello_world_gtest PROPERTIES
	INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(hello_world_gtest
	${GTEST_LIBRARIES} Threads::Threads
	hello_world
)

if (MSVC)
    target_compile_options(hello_world PRIVATE
        /W4
    )
    target_compile_options(hello_world_ut PRIVATE
        /W4
    )
    target_compile_options(hello_world_gtest PRIVATE
        /W4
    )
else ()
    target_compile_options(hello_world PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(hello_world_ut PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
	target_compile_options(hello_world_gtest PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

enable_testing()

add_test(hello_world_ut hello_world_ut)
add_test(hello_world_gtest hello_world_gtest)
