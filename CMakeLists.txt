cmake_minimum_required(VERSION 3.28...4.0)

project(catch2-module-example)

include(FetchContent)

set(fetch_catch2 ON CACHE BOOL "Get Catch2 with FetchContent")
if(fetch_catch2)
  FetchContent_Declare(
    catch
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.1)
else()
  find_package(Catch2 CONFIG REQUIRED)
endif()

set(msvc_options)
list(APPEND msvc_options "/W4" "/MP")

list(APPEND msvc_options "/experimental:module")

list(APPEND msvc_options "/utf-8")

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:${msvc_options}>")

add_subdirectory(catch2)

add_executable(example)
target_sources(example
  PRIVATE FILE_SET CXX_MODULES FILES
    src/example.ixx
)
target_link_libraries(example
  PRIVATE
    Catch2::module
)
target_compile_features(example PRIVATE cxx_std_23)

add_executable(compat_example)
target_sources(compat_example
  PRIVATE FILE_SET CXX_MODULES FILES
    src/compat_example.ixx
)
target_link_libraries(compat_example
  PRIVATE
    Catch2::module
)
target_compile_features(compat_example PRIVATE cxx_std_23)
