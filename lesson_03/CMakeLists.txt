cmake_minimUm_required(VERSION 3.2)

project(custom_allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

add_executable(custom_allocator_cli main.cpp)

add_subdirectory(custom_allocator)
add_subdirectory(custom_linked_list)
set_target_properties(custom_allocator_cli PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(custom_allocator_cli PRIVATE
    custom_allocator
    custom_linked_list
)

target_include_directories(custom_allocator_cli
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/custom_allocator"
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/custom_linked_list"
)

if (MSVC)
    target_compile_options(custom_allocator_cli PRIVATE
        /W4
    )
else ()
    target_compile_options(custom_allocator_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()


install(TARGETS custom_allocator_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT mr.salixnew@gmail.com)

include(CPack)

enable_testing()
