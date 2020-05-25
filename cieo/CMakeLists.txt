# ##############################################################################
# DEPENDENCIES
# ##############################################################################
add_library(cieo-dependencies INTERFACE)
target_link_libraries(
  cieo-dependencies
  INTERFACE spdlog
            fmt::fmt
            units)

# ##############################################################################
# SOURCES
# ##############################################################################
include(WriteCompilerDetectionHeader)
set(SOURCES src/cieo.cpp src/logging.cpp)
configure_file("${CIEO_SOURCE_DIR}/cieo/include/cieo/version.hpp.in"
               "${CIEO_SOURCE_DIR}/cieo/include/cieo/version.hpp")
set(CIEO_COMPILERS MSVC GNU Clang Intel AppleClang)
write_compiler_detection_header(
  FILE
  ${CIEO_SOURCE_DIR}/cieo/include/cieo/compiler.hpp
  PREFIX
  CIEO
  COMPILERS
  ${CIEO_COMPILERS}
  FEATURES
  cxx_constexpr
  cxx_deleted_functions
  cxx_extern_templates
  cxx_final
  cxx_noexcept
  cxx_override
  cxx_alignas
  cxx_alignof
  cxx_nullptr
  cxx_static_assert
  cxx_attribute_deprecated
  cxx_thread_local)

# ##############################################################################
# STATIC LIBRARY
# ##############################################################################
if(CIEO_BUILD_STATIC_LIBS)
  add_library(cieo-static STATIC ${SOURCES})
  add_library(cieo::static ALIAS cieo-static)

  target_include_directories(cieo-static PUBLIC ${CIEO_SOURCE_DIR}/cieo/include)
  set_target_properties(cieo-static PROPERTIES CXX_CLANG_TIDY "${CLANGTIDY_CMD}" CXX_CPPCHECK "${CPPCHECK_CMD}")

  target_link_libraries(cieo-static PUBLIC cieo-dependencies cieo-options cieo-warnings)
  install(TARGETS cieo-static ARCHIVE DESTINATION lib)
endif()

# ##############################################################################
# SHARED LIBRARY
# ##############################################################################
if(CIEO_BUILD_SHARED_LIBS)
  add_library(cieo-shared SHARED ${SOURCES})
  add_library(cieo::shared ALIAS cieo-shared)

  target_include_directories(cieo-shared PUBLIC ${CIEO_SOURCE_DIR}/cieo/include)

  set_target_properties(cieo-shared PROPERTIES CXX_CLANG_TIDY "${CLANGTIDY_CMD}" CXX_CPPCHECK "${CPPCHECK_CMD}")

  target_link_libraries(cieo-shared PUBLIC cieo-dependencies cieo-options cieo-warnings)
  install(TARGETS cieo-shared LIBRARY DESTINATION lib)
endif()

# ##############################################################################
# ALIASED LIBRARY
# ##############################################################################
if(CIEO_BUILD_SHARED_LIBS)
  add_library(cieo::cieo ALIAS cieo-shared)
else()
  add_library(cieo::cieo ALIAS cieo-static)
endif()
