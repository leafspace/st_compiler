include_directories(${INCLUDE_DIR})
include_directories(${ADAPTER_DIR})

FILE(GLOB STCompiler_Test_Src *.h *.cpp *.st)

##############################################################################
# 主工程
add_executable(STCompiler_Test ${STCompiler_Test_Src})

# 设置输出路径
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
  string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
  set_target_properties(STCompiler_Test PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${OUT_DIR})
  set_target_properties(STCompiler_Test PROPERTIES
                        ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${LIB_DIR})
  set_target_properties(STCompiler_Test PROPERTIES
                        PDB_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PDB_DIR})
endforeach()

# 设置附加依赖项
target_link_libraries(STCompiler_Test deci_scan_parse.lib)
target_link_libraries(STCompiler_Test deci.lib)
