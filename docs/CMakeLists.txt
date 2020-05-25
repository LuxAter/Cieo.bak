find_package(Doxygen)
if(DOXYGEN)
  # ############################################################################
  # SOURCE FILES
  # ############################################################################
  file(GLOB_RECURSE SOURCES "${CIEO_SOURCE_DIR}/docs/*.md"
       "${CIEO_SOURCE_DIR}/include/*.hpp" "${CIEO_SOURCE_DIR}/cli/*.hpp")
  list(APPEND SOURCES "${CIEO_SOURCE_DIR}/README.md")

  file(GLOB_RECURSE RESOURCE "${CIEO_SOURCE_DIR}/docs/icons/*.svg")

  foreach(FILE_PATH IN LISTS SOURCES)
    set(DOXYGEN_INPUT "${DOXYGEN_INPUT} \\\n\"${FILE_PATH}\"")
  endforeach()
  foreach(FILE_PATH IN LISTS RESOURCE)
    set(DOXYGEN_RESOURCE "${DOXYGEN_RESOURCE} \\\n\"${FILE_PATH}\"")
  endforeach()
  configure_file(Doxyfile.in Doxyfile @ONLY)

  # ############################################################################
  # STYLE COMPILER
  # ############################################################################
  find_program(LESSC_EXECUTABLE "lessc")

  if(NOT LESSC_EXECUTABLE STREQUAL "LESS-NOTFOUND")
    add_custom_command(
      OUTPUT "${CIEO_SOURCE_DIR}/docs/doxygen/extra.css"
      COMMAND
        ${LESSC_EXECUTABLE} --compress
        ${CIEO_SOURCE_DIR}/docs/doxygen/extra.less >
        ${CIEO_SOURCE_DIR}/docs/doxygen/extra.css
      COMMENT "Generating extra.css"
      DEPENDS ${CIEO_SOURCE_DIR}/docs/doxygen/extra.less
      VERBATIM)
  endif()

  # ############################################################################
  # DOCUMENTATION GENERATOR
  # ############################################################################
  add_custom_target(
    docs
    "${DOXYGEN_EXECUTABLE}"
    DEPENDS ${DOXYGEN_DEPENDS} "${CIEO_SOURCE_DIR}/docs/doxygen/extra.css"
    WORKING_DIRECTORY "${CIEO_BINARY_DIR}/docs"
    COMMENT "Generating Doxygen documentation"
    VERBATIM)
endif()

# TODO: Add documentation coverage reporting using coverxygen
