cmake_minimum_required(VERSION 2.8.9)
project(map2json)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -stdlib=libc++")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(MAJOR_VERSION 1)
set(MINOR_VERSION 0)
set(PATCH_VERSION 1)
set(VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})

find_package(Boost REQUIRED COMPONENTS program_options system filesystem regex)
if(Boost_FOUND)
    include_directories(include ${Boost_INCLUDE_DIRS})
    configure_file(include/config.h.in include/config.h @ONLY)
    file(GLOB SOURCES "src/*.cpp")

    add_executable(map2json ${SOURCES})
    target_link_libraries(
        map2json
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_REGEX_LIBRARY}
    )

    # Set the location for binary installation -- i.e., /usr/bin in this case
    install(TARGETS map2json DESTINATION /usr/local/bin)
endif()
