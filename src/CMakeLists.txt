include_directories(${INCLUDE_DIR})
include_directories(${INCLUDE_DIR}/deci)

add_library(deci_scan_parse
  iec61131.y.hpp
  iec61131.y.cpp
  iec61131.l.cpp
  iec61131.l
  iec61131.y
)

target_include_directories(deci_scan_parse
  PRIVATE include/ ${CMAKE_CURRENT_BINARY_DIR}
  SYSTEM INTERFACE include/
)

add_library(deci
  deci.cpp
  compiler_t.cpp
  ast_t.cpp
  ast_number_t.cpp
  symbol_table.cpp

  ../../include/deci/deci.hpp
  ../../include/deci/type.hpp
  ../../include/deci/compiler_t.hpp
  ../../include/deci/ast_t.hpp
  ../../include/deci/ast_number_t.hpp
  ../../include/deci/symbol_table.hpp
  ../../include/deci/SyntaxError.hpp
)

target_link_libraries(deci PRIVATE 
  deci_scan_parse
)

target_include_directories(deci
  PRIVATE include/ ${CMAKE_CURRENT_BINARY_DIR}
  SYSTEM INTERFACE include/
)

target_compile_options(deci PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
  $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -pedantic -ggdb>
  $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -pedantic -ggdb>
)

# 设置输出路径
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
  string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
  set_target_properties(deci_scan_parse PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${OUT_DIR})
  set_target_properties(deci_scan_parse PROPERTIES
                        ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${LIB_DIR})
  set_target_properties(deci_scan_parse PROPERTIES
                        PDB_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PDB_DIR})

  set_target_properties(deci PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${OUT_DIR})
  set_target_properties(deci PROPERTIES
                        ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${LIB_DIR})
  set_target_properties(deci PROPERTIES
                        PDB_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PDB_DIR})
endforeach()

set_target_properties(deci_scan_parse PROPERTIES FOLDER "third_party")
set_target_properties(deci PROPERTIES FOLDER "third_party")
