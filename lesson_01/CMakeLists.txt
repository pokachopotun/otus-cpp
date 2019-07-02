cmake_minimUm_required(VERSION 3.2)

project(hello_world VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(hello_world_cli main.cpp)

add_subdirectory(hello_world)
set_target_properties(hello_world_cli PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(hello_world_cli PRIVATE
    hello_world
)

target_include_directories(hello_world_cli
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/hello_world"
)

if (MSVC)
    target_compile_options(hello_world_cli PRIVATE
        /W4
    )
else ()
    target_compile_options(hello_world_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()


install(TARGETS hello_world_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT mr.salixnew@gmail.com)

include(CPack)

enable_testing()
