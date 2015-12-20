cmake_minimum_required(VERSION 2.8.9)
project(map2json)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -stdlib=libc++")
find_package(Boost REQUIRED COMPONENTS program_options system filesystem regex)
if(Boost_FOUND)
    include_directories(include ${Boost_INCLUDE_DIRS})
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
    install(TARGETS map2json DESTINATION /usr/bin)
endif()
