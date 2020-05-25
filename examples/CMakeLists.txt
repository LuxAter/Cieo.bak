# ##############################################################################
# EXAMPLE MACRO
# ##############################################################################
macro(add_example OUTPUT SOURCES)
  add_executable(${OUTPUT} ${SOURCES})
  target_link_libraries(${OUTPUT} PUBLIC cieo::warnings cieo::options cieo::cieo)
endmacro()

# ##############################################################################
# EXAMPLES
# ##############################################################################

add_example(simple simple.cpp)


