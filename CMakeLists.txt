cmake_minimum_required(VERSION 3.28...4.0)

project(catch2-module-example)

find_package(Catch2 CONFIG REQUIRED)

set(msvc_options)
list(APPEND msvc_options "/W4" "/MP")

list(APPEND msvc_options "/experimental:module")

list(APPEND msvc_options "/utf-8")

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:${msvc_options}>")

set(catch2_module catch2_module)
add_library(${catch2_module})
target_sources(${catch2_module}
  PRIVATE FILE_SET CXX_MODULES FILES
    src/catch2.ixx
    src/catch2.session.ixx)
target_include_directories(${catch2_module} PUBLIC include)
target_link_libraries(${catch2_module} PUBLIC Catch2::Catch2)
target_compile_features(${catch2_module} PRIVATE cxx_std_23)

set(main main)
add_executable(${main})
target_sources(${main}
  PRIVATE
    src/main.cpp
  PRIVATE FILE_SET CXX_MODULES FILES
    src/main.ixx
)
target_link_libraries(${main} PRIVATE catch2_module)
target_compile_features(${main} PRIVATE cxx_std_23)
