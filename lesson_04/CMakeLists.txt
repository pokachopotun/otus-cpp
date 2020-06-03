cmake_minimUm_required(VERSION 3.2)

project(print_ip VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

add_executable(print_ip_cli main.cpp)

add_subdirectory(print_ip)
set_target_properties(print_ip_cli PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(print_ip_cli PRIVATE
    print_ip
)

target_include_directories(print_ip_cli
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/print_ip"
)

if (MSVC)
    target_compile_options(print_ip_cli PRIVATE
        /W4
    )
else ()
    target_compile_options(print_ip_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()


install(TARGETS print_ip_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT mr.salixnew@gmail.com)

include(CPack)

enable_testing()
