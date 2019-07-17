cmake_minimUm_required(VERSION 3.2)

project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

add_executable(ip_filter_cli main.cpp)

add_subdirectory(ip_filter)
set_target_properties(ip_filter_cli PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(ip_filter_cli PRIVATE
    ip_filter
)

target_include_directories(ip_filter_cli
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/ip_filter"
)

if (MSVC)
    target_compile_options(ip_filter_cli PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()


install(TARGETS ip_filter_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT mr.salixnew@gmail.com)

include(CPack)

enable_testing()
