# ##############################################################################
# PROJECT
# ##############################################################################
cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(
  Cieo
  VERSION 0.0.0
  LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  set(CIEO_MAIN_PROJECT TRUE)
  set(CMAKE_VERBOSE_MAKEFILE OFF)
endif()
set(CIEO_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CIEO_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

# ##############################################################################
# BUILD TYPE
# ##############################################################################
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE
      "Debug"
      CACHE STRING "Build Mode" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
                                               "MinSizeRel" "RelWithDebInfo")
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(BUILD_TYPE_DEBUG ON)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(BUILD_TYPE_RELEASE ON)
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
  set(BUILD_TYPE_MIN_SIZE_REL ON)
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
  set(BUILD_TYPE_REL_WITH_DEB_INFO ON)
endif()

# ##############################################################################
# OPTIONS
# ##############################################################################
option(CIEO_BUILD_INTERACTIVE "Compiles interactive executable" ${CIEO_MAIN_PROJECT})
option(CIEO_BUILD_DOCS "Compiles documentation" ${CIEO_MAIN_PROJECT})
option(CIEO_BUILD_EXAMPLES "Compiles example projects" ${CIEO_MAIN_PROJECT})
option(CIEO_BUILD_TESTS "Compiles Unit Test exectuable" ${CIEO_MAIN_PROJECT})
option(CIEO_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" FALSE)

option(CIEO_ENABLE_PCH "Enable Precompiled Headers" OFF)
option(CIEO_ENABLE_IPO "Enable Interporcedural Optimization, aka Link Time Optimization (LTO)" OFF)

if(BUILD_TYPE_DEBUG OR REL_WITH_DEB_INFO)
  option(CIEO_PROFILING "Enable profiling" ${CIEO_MAIN_PROJECT})
  option(CIEO_STATIC_ANALYSIS "Use static analysis tools"
         ${CIEO_MAIN_PROJECT})
else()
  option(CIEO_PROFILING "Enable profiling" FALSE)
  option(CIEO_STATIC_ANALYSIS "Use static analysis tools" FALSE)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL
                                           "Clang")
  option(CIEO_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" FALSE)
  option(CIEO_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" FALSE)
  option(CIEO_ENALBE_SANITIZER_UNDEFINED_BEHAVIOR
         "Enable undefined behavior sanitizer" FALSE)
  option(CIEO_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" FALSE)

  if(CIEO_ENABLE_SANITIZER_ADDRESS
     OR CIEO_ENABLE_SANITIZER_MEMORY
     OR CIEO_ENALBE_SANITIZER_UNDEFINED_BEHAVIOR
     OR CIEO_ENABLE_SANITIZER_THREAD)
    set(CIEO_ENABLE_SANITIZERS)
  endif()
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  option(CIEO_BUILD_SHARED_LIBS "Compile shared libraries" FALSE)
  option(CIEO_BUILD_STATIC_LIBS "Compile static libraries" TRUE)
else()
  option(CIEO_BUILD_STATIC_LIBS "Compile static libraries" FALSE)
  option(CIEO_BUILD_SHARED_LIBS "Compile shared libraries" TRUE)
endif()

if(CIEO_STATIC_ANALYSIS)
  option(CIEO_ENABLE_CPPCHECK "Enable cppcheck" TRUE)
  option(CIEO_ENABLE_CLANG_TIDY "Enable clang-tidy" TRUE)
  option(CIEO_ENABLE_FIXER "Apply available static analysis fixes" FALSE)
endif()

# ##############################################################################
# CCACHE
# ##############################################################################
find_program(CCACHE ccache)
if(CCACHE)
  message(STATUS "using ccache")
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
else()
  message(STATUS "ccache not found cannot use")
endif()

# ##############################################################################
# IPO
# ##############################################################################
if(CIEO_ENABLE_IPO)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT IPO_SUPPORT OUTPUT IPO_SUPPORT_MSG)
  if(IPO_SUPPORT)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
  else()
    message(SEND_ERROR "IPO is not supported: ${IPO_SUPPORT_MSG}")
  endif()
endif()

# ##############################################################################
# CONFIG TARGETS
# ##############################################################################
add_library(cieo-options INTERFACE)
add_library(cieo::options ALIAS cieo-options)
target_compile_features(cieo-options INTERFACE cxx_std_17)
add_library(cieo-warnings INTERFACE)
add_library(cieo::warnings ALIAS cieo-warnings)

# ##############################################################################
# COMPILE COMMANDS
# ##############################################################################
if(BUILD_TYPE_DEBUG OR BUILD_TYPE_REL_WITH_DEB_INFO)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)
  endif()
endif()

# ##############################################################################
# SANITIZERS
# ##############################################################################
if(CIEO_ENABLE_SANITIZERS)
  set(SANITIZERS "")
  if(CIEO_ENABLE_SANITIZER_ADDRESS)
    list(APPEND SANITIZERS "address")
  endif()
  if(CIEO_ENABLE_SANITIZER_MEMORY)
    list(APPEND SANITIZERS "memory")
  endif()
  if(CIEO_ENABLE_SANITIZER_UNDEFINED_BEHAVIOR)
    list(APPEND SANITIZERS "undefined")
  endif()
  if(CIEO_ENABLE_SANITIZER_THREAD)
    list(APPEND SANITIZERS "thread")
  endif()
  list(JOIN SANITIZERS "," SANITIZERS)
  if(NOT "${SANITIZERS}" STREQUAL "")
    target_compile_options(cieo-options INTERFACE -fsanitize=${SANITIZERS})
    target_link_libraries(cieo-options INTERFACE -fsanitize=${SANITIZERS})
  endif()
endif()

# ##############################################################################
# WARNINGS
# ##############################################################################
set(MSVC_WARNINGS /W4 /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619 /w14640 /w14826 /w14905 /w14906 /w14928)
set(CLANG_WARNINGS -Wall -Wextra -Wno-shadow -Wnon-virtual-dtor -Wno-old-style-cast -Wno-cast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wno-implicit-int-conversion -Wno-sign-conversion -Wno-sign-compare -Wnull-dereference -Wno-double-promotion -Wno-implicit-float-conversion -Wno-shorten-64-to-32 -Wno-float-conversion -Wno-unused-parameter -Wno-macro-redefined -Wformat=2)
if(CIEO_WARNINGS_AS_ERRORS)
  set(CLANG_WARNINGS ${CLANG_WARNINGS} -Werror)
  set(MSVC_WARNIGNS ${MSVC_WARNINGS} /Wx)
endif()
set(GCC_WARNINGS ${CLANG_WARNINGS} -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast)
if(MSVC)
  target_compile_options(cieo-warnings INTERFACE ${MSVC_WARNINGS})
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(cieo-warnings INTERFACE ${GCC_WARNINGS})
else()
  target_compile_options(cieo-warnings INTERFACE ${CLANG_WARNINGS})
endif()

# ##############################################################################
# STATIC ANALYSIS
# ##############################################################################
if(CIEO_STATIC_ANALYSIS)
  if(CIEO_ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE "clang-tidy")
    if(CLANG_TIDY_EXE)
      message(STATUS "Found clang-tidy ${CLANG_TIDY_EXE}")
      set(CLANG_TIDY_CMD "${CLANG_TIDY_EXE}"
                         "--checks=*,-modernize-use-trailing-return-type")
      if(CIEO_FIX)
        list(APPEND CLANG_TIDY_CMD "--fix")
      endif()
    else()
      message(STATUS "Could not find clang-tidy")
    endif()
  endif()
  if(CIEO_ENABLE_CPPCHEC)
    find_program(CPPCHECK_EXE "cppcheck")
    if(CPPCHECK_EXE)
      message(STATUS "Found cppcheck ${CPPCHECK_EXE}")
      set(CPPCHECK_CMD "${CPPCHECK_EXE}" "--suppress=missingInclude"
                       "--enable=all" "--inconclusive")
    else()
      message(STATUS "Could not find cppcheck")
    endif()
  endif()
endif()

# ##############################################################################
# PCH
# ##############################################################################
if(CIEO_ENABLE_PCH)
  target_precompile_headers(
    cieo-options
    INTERFACE
    <algorithm>
    <cassert>
    <cinttypes>
    <cmath>
    <cstdint>
    <cstring>
    <limits>
    <memory>
    <string>
    <type_traits>
    <vector>)
endif()

# ##############################################################################
# TARGETS
# ##############################################################################


# DEPENDENCIES
add_subdirectory(thirdparty)

# DOCUMENTATION
if(CIEO_BUILD_DOCS)
  add_subdirectory(docs)
endif()

# EXAMPLES
if(CIEO_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

# INTERACTIVE
if(CIEO_BUILD_INTERACTIVE)
  add_subdirectory(interactive)
endif()

# LIBRARY
add_subdirectory(cieo)

# TESTING
if(CIEO_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

# ##############################################################################
# REPORTING
# ##############################################################################
if(CIEO_MAIN_PROJECT)
  message(STATUS "CMAKE_BINARY_DIR:      ${CMAKE_BINARY_DIR}")
  message(STATUS "CMAKE_SOURCE_DIR:      ${CMAKE_SOURCE_DIR}")
  message(STATUS "CMAKE_VERSION:         ${CMAKE_VERSION}")
  message(STATUS "CMAKE_GENERATOR:       ${CMAKE_GENERATOR}")
  message(STATUS "CMAKE_C_COMPILER_ID:   ${CMAKE_C_COMPILER_ID}")
  message(STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
  message(STATUS "CMAKE_BUILD_TYPE:      ${CMAKE_BUILD_TYPE}")
endif()

# ##############################################################################
# PACKAGING
# ##############################################################################
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CPACK_GENERATOR "TGZ;ZIP")
  set(CPACK_PACKAGE_VENDOR "LuxAter")
  set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
  set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
  set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
  set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
  set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
  set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${CMAKE_SYSTEM_NAME}")
  set(CPACK_MONOLITHIC_INSTALL TRUE)
  include(CPack)
endif()
